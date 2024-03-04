#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "serial.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

////////////////////////////////////////////////////////////

    serial_init("/dev/ttyS1",115200);
    serial_send("hello world!");

    while(1)
    {
        serial_rcev();
    }

    serial_close();


////////////////////////////////////////////////////////////


}

MainWindow::~MainWindow()
{
    delete ui;
}

