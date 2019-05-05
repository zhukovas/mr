#ifndef MODULS_H
#define MODULS_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class reactorDialog;
class Reactor : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Reactor(QObject *parent= 0);
    ~Reactor();

private:
    reactorDialog *reactorD;

    QString temper;
    QString coil;

    bool pointIn;
    bool pointOut;

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);


};

class pumpDialog;
class Pump : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Pump(QObject *parent = 0);
    ~Pump();
signals:
    void pump1signal(QString str);
    void pump2signal(QString str);
    void pump3signal(QString str);
    void pump4signal(QString str);

private:

    pumpDialog *pumpD;
    QList<QGraphicsItem *> pumpList;
    QString name;
    QString conc;
    QString feed;
    QString pump;

    bool pointPump;

protected:
    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) ;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) ;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) ;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) ;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) ;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) ;
};

#endif // MODULS_H
