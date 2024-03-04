/* 与主程序同步运行的线程池, 写成类可以用构造函
 * 数进行初始化，无需修改主程序，导入本头文件即可 */


#ifndef THREAD_H
#define THREAD_H


#include <iostream>
#include <thread> // 线程库
#include <chrono> // 延时库


// 导入串口库，实例化对象
#include "uart.h"
UART uart("/dev/ttyS3",115200);

// 子线程,用于接收串口数据
class THREAD1 {
public:
    THREAD1() : thread_(&THREAD1::threadFun1, this) {
        thread_.detach();
    }

private:
    std::thread thread_;
    // 子线程线程函数
    void threadFun1() {
        while (true) {
            // 打印运行状态
            std::cout << "thread_1 is running... " << std::endl;
            // 等待电脑发过来的数据
            std::this_thread::sleep_for(std::chrono::seconds(1));
            // 读取串口缓存区数据
            uart.rcev();
            // 数据会赋值给data属性
            //std::cout << "接收到数据: " << uart.data << std::endl;
        }
    }
};

// 创建对象，启用子线程，线程会默认为分离状态
THREAD1 thread1;






// 类似的，可以创建更多子线程
class THREAD2 {
public:
    THREAD2() : thread_(&THREAD2::threadFun2, this) {
        thread_.detach();
    }

private:
    std::thread thread_;

    void threadFun2() {
        while (true) {
            std::cout << "thread_2 is running... " << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }
};

THREAD2 thread2;













#endif // THREAD_H
