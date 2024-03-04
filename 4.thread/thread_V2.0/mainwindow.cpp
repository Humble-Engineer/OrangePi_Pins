#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "thread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    // 将线程设置为分离状态
//    thread_1.detach();
//    thread_2.detach();
}

MainWindow::~MainWindow()
{
    delete ui;
}





#include "uart.h"
UART uart("/dev/ttyS3",115200);

void MainWindow::on_uartButton_clicked()
{
    // 发送一串字符给电脑
    uart.send("Hello world,I'm OrangePi!");

    // 等待电脑发过来的数据
    delay(3000);
    // 读取串口缓存区数据
    uart.rcev();
    // 数据会赋值给data属性
    //std::cout << "接收到数据: " << uart.data << std::endl;
}






