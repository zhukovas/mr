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

    int temperature;
    int t1;
    int t2;
    int t0;
    int t_err;

    QTimer *serialTimer;
    QTimer *temperTimer;

signals:
    void temperSignal(int);
    void temperEeeorSignal(int);

private slots:
    void openSerialPort();
    void closeSerialPort();
    void readData();
    void handleError(QSerialPort::SerialPortError error);
    void writeData();

    void openSlot();
    void save_asSlot();
    void saveSlot();

    void temperControl();


    void addPump();
    void addReactor();
    void addCollector();



    void pump1slot(QString str);
    void pump2slot(QString str);
    void pump3slot(QString str);
    void pump4slot(QString str);

    void reactor_t_slot(QString str);

    void startSlot();



private:

    int termistorToTemperature(int t);
    Ui::MainWindow *ui;
    SettingsDialog *settings;
    QSerialPort *serial;
    Pump *pump;
    Reactor *reactor;
    Collector *collector;
    QGraphicsScene  *scene;


};

#endif // MAINWINDOW_H
