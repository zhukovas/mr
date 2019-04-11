#ifndef MODULS_H
#define MODULS_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class Reactor : public QGraphicsItem
{
public:
    Reactor();
    ~Reactor();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

class pumpDialog;
class Pump : public QGraphicsItem
{
public:
    Pump();
    ~Pump();
private:
    pumpDialog *pumpD;
    QList<QGraphicsItem *> pumpList;
    QStringList nameList;
    QStringList concList;
    QStringList feedList;

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MODULS_H
