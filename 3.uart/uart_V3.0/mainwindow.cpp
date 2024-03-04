#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "uart.h"
UART uart("/dev/ttyS3",115200);
//UART *uart = new UART("/dev/ttyS1",115200);

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

