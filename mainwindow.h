#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtSerialPort/QSerialPort>
#include <QPushButton>

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

private slots:
    void openSerialPort();
    void closeSerialPort();
    void readData();
    void handleError(QSerialPort::SerialPortError error);

    void addPump();
    void addReactor();

private:
    void writeData(QString data);

    Ui::MainWindow *ui;
    SettingsDialog *settings;
    QSerialPort *serial;
    Pump *pump;
    Reactor *reactor;
    QGraphicsScene  *scene;
};

#endif // MAINWINDOW_H
