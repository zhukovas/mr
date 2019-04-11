#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"

#include <QtSerialPort/QSerialPort>
#include <QtCore/QtGlobal>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    settings = new SettingsDialog;

    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MainWindow::handleError);


    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);

    //connect(console, &Console::getData, this, &MainWindow::writeData);

    scene = new QGraphicsScene();

    connect(ui->pumpButton, &QPushButton::clicked, this, &MainWindow::addPump);
    connect(ui->reactorButton, &QPushButton::clicked, this, &MainWindow::addReactor);



    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
    //ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по вертикали
    //ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали

    scene->setSceneRect(-250,-250,500,500);

    //scene->addLine(-250,0,250,0,QPen(Qt::black));
    //scene->addLine(0,-250,0,250,QPen(Qt::black));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings;

}

void MainWindow::addPump()
{
    pump = new Pump();
    scene->addItem(pump);
    pump->setPos(0,0);
}

void MainWindow::addReactor()
{
    reactor = new Reactor();
    scene->addItem(reactor);
    reactor->setPos(0,0);
}

//****************************************************Serisl*************************************
//***********************************************************************************************
//***********************************************************************************************

void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {

    } else {

    }
}

void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();

}

void MainWindow::readData()
{
    QByteArray data = serial->readAll();
}

void MainWindow::writeData(QString data)
{
    serial->write(data.toLocal8Bit());
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}


