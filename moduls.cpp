#include "moduls.h"
#include "pumpdialog.h"



Pump::Pump() :
    QGraphicsItem()
{

}

Pump::~Pump()
{

}

QRectF Pump::boundingRect() const
{
    return QRectF(-55,-55,110,110);
}



Reactor::Reactor() :
    QGraphicsItem()
{

}

Reactor::~Reactor()
{

}

QRectF Reactor::boundingRect() const
{
    return QRectF(-75,-35,150,70);
}

void Reactor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));

    painter->drawRect(-75,-35,150,70);


        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Pump::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter->drawEllipse(-50, -50, 100, 100);
    painter->drawLine(-30,-40,50,0);
    painter->drawLine(-30,40,50,0);

    painter->drawEllipse(-35, -23, 20, 20);
    painter->drawEllipse(-16, -10, 20, 20);
    painter->drawEllipse(-35, 3, 20, 20);
    painter->drawEllipse(-40, -20, 40, 40);

    painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter->drawEllipse(45, -5, 10, 10);



        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Pump::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}

void Pump::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Pump::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void Pump::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    pumpD = new pumpDialog;
    if (pumpD->exec() == QDialog::Accepted) {


    } delete pumpD;

    Q_UNUSED(event);
}

void Reactor::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}

void Reactor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void Reactor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}