#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <wiringPi.h>
#define led 5

/*
引脚监测shell命令：
watch -n 1 gpio readall
*/


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // GPIO引脚测试
    wiringPiSetup();
    pinMode(led,OUTPUT);

    for(int i=0;i<5;i++)
    {
        digitalWrite(led,HIGH);
        delay(1000);
        digitalWrite(led,LOW);
        delay(1000);
    }

    printf("Blink finish!\n");

}

MainWindow::~MainWindow()
{
    delete ui;
}



