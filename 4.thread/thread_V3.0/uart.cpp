#include "uart.h"

UART::UART(std::string device_path,int baudrate)
{
    init(device_path,baudrate);
}

UART::~UART()
{
    close();
}

void UART::init(std::string device_path,int baudrate)
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

void UART::send(std::string sendBuffer)
{
    // 转换为c语言的字符串指针（为了兼容serialPuts()函数的输入参数）
    const char* buffer = sendBuffer.c_str();
    // 通过串口发送
    serialPuts(serialPort,buffer);
    std::cout << "send data: " << buffer << std::endl;
}

void UART::rcev()
{
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

void UART::close()
{
    // 关闭串口
    serialClose(serialPort);
}
