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

#ifndef SERIAL_H
#define SERIAL_H

#include <iostream>

// 香橙派GPIO编程库
#include <wiringPi.h>
#include <wiringSerial.h>

// 串口文件描述符号，标识打开的串口
int serialPort;

// 接收到的字符串
std::string data;


void serial_init(std::string device_path,int baudrate)
{

    // 转换为c语言的字符串指针（为了兼容serialOpen()函数的输入参数）
    const char* device = device_path.c_str();
    // 转换为整形常量（为了兼容serialOpen()函数的输入参数）
    const int baud= baudrate;

    // 指定串口设备的文件路径以及波特率
    serialPort = serialOpen(device,baud);
    // 清空串口缓存区
    serialFlush(serialPort);
}

void serial_send(std::string sendBuffer)
{
    // 转换为c语言的字符串指针（为了兼容serialPuts()函数的输入参数）
    const char* buffer = sendBuffer.c_str();
    // 通过串口发送
    serialPuts(serialPort,buffer);
    std::cout << "send data: " << buffer << std::endl;
}

void serial_rcev()
{
    // 等待数据发送
    delay(1000);
    // 有数据就接收
    if(serialDataAvail(serialPort)>0)
    {
        // 声明接收字符串数组
        char buffer[128];
        // 清空字符串数组
        memset(buffer, 0, sizeof(buffer));
        // 按字符读取串口缓存区
        int index = 0;
        while (serialDataAvail(serialPort)>0)
        {
            buffer[index++] = serialGetchar(serialPort);
        }
        std::cout << "rcev data: " << buffer << std::endl;
        // 接收数据到字符串
        data = buffer;
    }
}

void serial_close()
{
    // 关闭串口
    serialClose(serialPort);
}

#endif // SERIAL_H
