#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include "moduls.h"

#include <QtSerialPort/QSerialPort>
#include <QtCore/QtGlobal>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    settings = new SettingsDialog;
    serialTimer = new QTimer;
    temperTimer = new QTimer;

    connect(ui->actionSettings, &QAction::triggered, settings, &MainWindow::show);
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::openSerialPort);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::closeSerialPort);
    connect(ui->actionOpen, &QAction::triggered,this, &MainWindow::openSlot);
    connect(ui->actionSave, &QAction::triggered,this, &MainWindow::saveSlot);
    connect(ui->actionSave_as, &QAction::triggered,this, &MainWindow::save_asSlot);

    ui->actionConnect->setDisabled(false);
    ui->actionDisconnect->setDisabled(true);

    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MainWindow::handleError);

    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);

    connect(temperTimer, &QTimer::timeout, this, &MainWindow::temperControl);

    connect(serialTimer, &QTimer::timeout, this, &MainWindow::writeData);

    scene = new QGraphicsScene();

    connect(ui->pumpButton, &QPushButton::clicked, this, &MainWindow::addPump);
    connect(ui->reactorButton, &QPushButton::clicked, this, &MainWindow::addReactor);
    connect(ui->collectorButton, &QPushButton::clicked, this, &MainWindow::addCollector);



    connect(ui->start,&QPushButton::clicked,this,&MainWindow::startSlot);



    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
    ui->graphicsView->setMouseTracking(true);
    //ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по вертикали
    //ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали

    scene->setSceneRect(-250,-250,500,500);

    speed_1= 0;
    speed_2= 0;
    speed_3= 0;
    speed_4= 0;
    temperature=0;
    t0=0;
    t1=0;
    t2=0;
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
    connect(pump,&Pump::pump1signal,this,&MainWindow::pump1slot);
    connect(pump,&Pump::pump2signal,this,&MainWindow::pump2slot);
    connect(pump,&Pump::pump3signal,this,&MainWindow::pump3slot);
    connect(pump,&Pump::pump4signal,this,&MainWindow::pump4slot);
}

void MainWindow::addReactor()
{
    reactor = new Reactor();
    scene->addItem(reactor);
    reactor->setPos(0,0);
    connect(reactor,&Reactor::reactor_t_signal,this,&MainWindow::reactor_t_slot);
    connect(this,&MainWindow::temperSignal, reactor, &Reactor::temperSlot);
    connect(this,&MainWindow::temperEeeorSignal, reactor, &Reactor::temperEeeorSlot);
}

void MainWindow::addCollector()
{
    collector = new Collector();
    scene->addItem(collector);
    collector->setPos(0,0);
}

void MainWindow::pump1slot(QString str)
{
    speed_1 = str.toInt();
    qDebug() << QString("1."+str);
}

void MainWindow::pump2slot(QString str)
{
    speed_2 = str.toInt();
}

void MainWindow::pump3slot(QString str)
{
    speed_3 = str.toInt();
}

void MainWindow::pump4slot(QString str)
{
    speed_4 = str.toInt();
}

void MainWindow::reactor_t_slot(QString str)
{
    temperature = str.toInt();
}

void MainWindow::startSlot()
{
    if(serial->isOpen())
            {
        serialStack.append(QString("1.%1").arg(speed_1));
        serialStack.append(QString("2.%1").arg(speed_2));
        serialStack.append(QString("3.%1").arg(speed_3));
        serialStack.append(QString("4.%1").arg(speed_4));

        serialTimer->start(300);

        temperTimer->start(5000);
    } else {
   QMessageBox::information(0,"Error","Всё в говне");
    }

}

void MainWindow::openSlot()
{
    QString f = QFileDialog::getOpenFileName(0,"Open file","","*.dat");
}

void MainWindow::save_asSlot()
{
    QString f = QFileDialog::getSaveFileName(0,"Save as...","","*.dat");

       QFile file( f );
       if ( file.open(QIODevice::ReadWrite) )
       {
           QTextStream stream( &f );
           stream << "something" << endl;
       }
}

void MainWindow::saveSlot()
{

}

void MainWindow::temperControl()
{
    t0 = (t1+t2)/2;
    t_err = t1-t0;

    emit temperSignal(t0);
    emit temperEeeorSignal(t_err);

    serialStack.append(QString("6.0"));
    serialStack.append(QString("6.1"));

    if(temperature>t0)
    {
        serialStack.append(QString("7.%1").arg(200));
    }
    if(temperature<t0)
    {
        serialStack.append(QString("7.%1").arg(0));
    }
    if(temperature==t0)
    {
        serialStack.append(QString("7.%1").arg(130));
    }
}

int MainWindow::termistorToTemperature(int t)
{
   return int(-t*t*t*0.000000537 + 0.000951782*t*t - 0.687553341*t +287.453100415);

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

        ui->actionConnect->setDisabled(true);
        ui->actionDisconnect->setDisabled(false);

    } else {

        QMessageBox::information(this,"Ups...","Error opening serial port");
    }
}

void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    ui->actionConnect->setDisabled(false);
    ui->actionDisconnect->setDisabled(true);
}

void MainWindow::readData()
{
    QByteArray data = serial->readAll();
    QString str(data);
    QStringList list;
    qDebug() << str;
    list = QString(str).split(QRegExp("\\."));
    if(list.size()==2)
    {
        if(list.at(0)=="t0")
        {
            t1 = termistorToTemperature(list.at(1).toInt());
        }
        if(list.at(0)=="t1")
        {
            t2 = termistorToTemperature(list.at(1).toInt());
        }
    }

}

void MainWindow::writeData()
{
    serial->write(serialStack.pop().toLocal8Bit());
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}


