/*
 参考文献：1 https://blog.csdn.net/weixin_54429787/article/details/126068669?
         2 用户手册V1.6 P212

 引脚监测shell命令：watch -n 1 gpio readall

 +------+-----+----------+--------+---+ PI5 PLUS +---+--------+----------+-----+------+
 | GPIO | wPi |   Name   |  Mode  | V | Physical | V |  Mode  | Name     | wPi | GPIO |
 +------+-----+----------+--------+---+----++----+---+--------+----------+-----+------+
 |      |     |     3.3V |        |   |  1 || 2  |   |        | 5V       |     |      |
 |   16 |   0 |    SDA.2 |   ALT9 | 0 |  3 || 4  |   |        | 5V       |     |      |
 |   15 |   1 |    SCL.2 |   ALT9 | 0 |  5 || 6  |   |        | GND      |     |      |
 |   62 |   2 |    PWM14 |     IN | 1 |  7 || 8  | 0 | IN     | GPIO1_A1 | 3   | 33   |
 |      |     |      GND |        |   |  9 || 10 | 0 | IN     | GPIO1_A0 | 4   | 32   |
 |   36 |   5 | GPIO1_A4 |     IN | 0 | 11 || 12 | 1 | IN     | GPIO3_A1 | 6   | 97   |
 |   39 |   7 | GPIO1_A7 |     IN | 1 | 13 || 14 |   |        | GND      |     |      |
 |   40 |   8 | GPIO1_B0 |     IN | 1 | 15 || 16 | 1 | ALT10  | GPIO3_B5 | 9   | 109  |
 |      |     |     3.3V |        |   | 17 || 18 | 1 | ALT10  | GPIO3_B6 | 10  | 110  |
 |   42 |  11 | SPI0_TXD |     IN | 0 | 19 || 20 |   |        | GND      |     |      |
 |   41 |  12 | SPI0_RXD |     IN | 0 | 21 || 22 | 0 | IN     | GPIO1_A2 | 13  | 34   |
 |   43 |  14 | SPI0_CLK |     IN | 0 | 23 || 24 | 1 | IN     | SPI0_CS0 | 15  | 44   |
 |      |     |      GND |        |   | 25 || 26 | 1 | IN     | SPI0_CS1 | 16  | 45   |
 |   47 |  17 | GPIO1_B7 |  ALT10 | 1 | 27 || 28 | 1 | ALT10  | GPIO1_B6 | 18  | 46   |
 |   63 |  19 | GPIO1_D7 |     IN | 1 | 29 || 30 |   |        | GND      |     |      |
 |   96 |  20 | GPIO3_A0 |     IN | 1 | 31 || 32 | 0 | IN     | GPIO1_A3 | 21  | 35   |
 |  114 |  22 | GPIO3_C2 |     IN | 0 | 33 || 34 |   |        | GND      |     |      |
 |   98 |  23 | GPIO3_A2 |     IN | 1 | 35 || 36 | 0 | IN     | GPIO3_A5 | 24  | 101  |
 |  113 |  25 | GPIO3_C1 |     IN | 0 | 37 || 38 | 0 | IN     | GPIO3_A4 | 26  | 100  |
 |      |     |      GND |        |   | 39 || 40 | 1 | IN     | GPIO3_A3 | 27  | 99   |
 +------+-----+----------+--------+---+----++----+---+--------+----------+-----+------+
 | GPIO | wPi |   Name   |  Mode  | V | Physical | V |  Mode  | Name     | wPi | GPIO |
 +------+-----+----------+--------+---+ PI5 PLUS +---+--------+----------+-----+------+

 可用串口：uart1（rx:27,tx:28） uart3（rx:18,tx:16） uart4（rx:19,tx:23）
          uart6（rx:10,tx:8） uart7（rx:24,tx:26） uart8（rx:40,tx:35）

 注意：需要先在orangepi-config中启用串口，设置完成后gpio readall命令会显示对应引脚mode为ALT10
*/

#ifndef UART_H
#define UART_H

// c语言标准头文件
#include <stdio.h>
// 包含一些通用的函数工具
#include <stdlib.h>
// 字符串处理相关头文件
#include <string.h>
// POSIX标准函数库头文件
#include <unistd.h>
// POSIX线程库头文件
#include <pthread.h>
// 香橙派GPIO编程库
#include <wiringPi.h>
#include <wiringSerial.h>

// 串口文件描述符合，标识打开的串口
int uart1;
// 字符串收发存储数组长度
#define StringSize 128

/* 发送数据线程 */
void *sendDatas(void *arg){

    // 分配了一个特定字节长度的字符数组，储存用户输入
    char *sendBuffer = (char *)malloc(StringSize);
    while(1){
        // 将字符数组的内容全部清除，用于存储新的输入
        memset(sendBuffer,'\0',StringSize);
        // 打印提示信息
        printf("Send -> ");
        // 获取用户输入的字符串并保存到字符数组
        scanf("%s",sendBuffer);
        // 字符数组内容输出到串口
        serialPuts(uart1,sendBuffer);
    }
}

/* 接收数据线程 */
void *recvDatas(void *arg){

    // 字符数组，存储串口缓存区数据
    char *recvBuffer = (char *)malloc(StringSize);
    // 用于记录缓存区可用字节数
    int cnt;
    while(1){
        // 获取缓存区可用字符数
        cnt = serialDataAvail(uart1);
        // 如果缓存区有数据
        if(cnt > 0){
            // 把字符存储数组清空
            memset(recvBuffer,'\0',StringSize);
            // 从串口缓存区中读取所有字符并存储
            read(uart1,recvBuffer,cnt);
            // 打印接收到的数据
            printf("receive -> %s\n",recvBuffer);
        }
    }
}

/* 数据收发线程初始化 */
int uartInit(){

    // 指定串口设备的文件路径以及波特率
    uart1 = serialOpen("/dev/ttyS1",115200);

    // 检查串口是否成功打开
    if (uart1 < 0){
        printf("serial open error\n");
        return -1;
    }
    // 启用引脚初始化方法，并检查是否成功
    if (wiringPiSetup () == -1){
        perror("wiringPi setup");
        return -1;
    }

    // 使用线程标识符建立一个新的发送线程
    pthread_t sendThread;
    // 将新线程与线程函数进行绑定
    pthread_create(&sendThread,NULL,sendDatas,NULL);

    // 使用线程标识符建立一个新的接收线程
    pthread_t recvThread;
    // 将新线程与线程函数进行绑定
    pthread_create(&recvThread,NULL,recvDatas,NULL);

    return 0;
}


#endif // UART_H
