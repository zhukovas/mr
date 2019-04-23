#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtSerialPort/QSerialPort>
#include <QPushButton>
#include <QStack>
#include <QTimer>

#include "moduls.h"

namespace Ui {
class MainWindow;
}

class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStack<QString> serialStack;

    int speed_1;
    int speed_2;
    int speed_3;
    int speed_4;

    QTimer *serialTimer;

private slots:
    void openSerialPort();
    void closeSerialPort();
    void readData();
    void handleError(QSerialPort::SerialPortError error);
    void writeData();


    void addPump();
    void addReactor();



    void pump1slot(QString str);
    void pump2slot(QString str);
    void pump3slot(QString str);
    void pump4slot(QString str);

    void startSlot();

private:


    Ui::MainWindow *ui;
    SettingsDialog *settings;
    QSerialPort *serial;
    Pump *pump;
    Reactor *reactor;
    QGraphicsScene  *scene;
};

#endif // MAINWINDOW_H
