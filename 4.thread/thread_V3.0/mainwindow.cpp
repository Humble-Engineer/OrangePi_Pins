#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "thread.h"

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







void MainWindow::on_uartButton_clicked()
{
    // 发送一串字符给电脑（uart对象在thread.h中实例化）
    uart.send("Hello world,I'm OrangePi!");

}






