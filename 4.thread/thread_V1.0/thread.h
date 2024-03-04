// 与主程序同步运行的线程池

#ifndef THREAD_H
#define THREAD_H


#include <iostream>
#include <thread> // 线程库
#include <chrono> // 延时库

// 定义一个线程函数
void thread_function_1()
{
    while(1){
        // 打印运行状态
        std::cout << "thread_1 is running... " << std::endl;
        // 单独令此线程延时一段时间
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
// 启用一个新线程
std::thread thread_1(thread_function_1);



// 定义一个线程函数
void thread_function_2()
{
    while(1){
        // 打印运行状态
        std::cout << "thread_2 is running... " << std::endl;
        // 单独令此线程延时一段时间
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}
// 启用一个新线程
std::thread thread_2(thread_function_2);









#endif // THREAD_H
