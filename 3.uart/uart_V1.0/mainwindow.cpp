#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

// 香橙派GPIO编程库
#include <wiringPi.h>
#include <wiringSerial.h>

// 串口文件描述符号，标识打开的串口
int serialPort;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

////////////////////////////////////////////////////////////

    // 指定串口设备的文件路径以及波特率
    serialPort = serialOpen("/dev/ttyS1",115200);
    // 清空串口缓存区
    serialFlush(serialPort);



    // 需要发送的字符串
    std::string sendBuffer = "abcdefg";
    // 转换为c语言的字符串指针（为了兼容wiringpi库）
    const char* cString = sendBuffer.c_str();
    // 通过串口发送
    serialPuts(serialPort,cString);
    std::cout << "send data: " << cString << std::endl;


    // 声明接收字符串数组
    char buffer[128];
    // 持续监听串口缓存区
    while(1){

        // 等待数据发送
        delay(1000);
        // 有数据就接收
        if(serialDataAvail(serialPort)>0)
        {
            // 清空字符串数组
            memset(buffer, 0, sizeof(buffer));
            // 按字符读取串口缓存区
            int index = 0;
            while (serialDataAvail(serialPort)>0)
            {
                buffer[index++] = serialGetchar(serialPort);
            }
            std::cout << "Received data: " << buffer << std::endl;
        }

    }

    // 关闭串口
    serialClose(serialPort);

////////////////////////////////////////////////////////////


}

MainWindow::~MainWindow()
{
    delete ui;
}

