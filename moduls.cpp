#include "moduls.h"
//#include "mainwindow.h"
#include "pumpdialog.h"
#include "reactordialog.h"
#include "qdebug.h"
#include <QMessageBox>


Pump::Pump(QObject *parent) : QObject (), QGraphicsItem()

{

    this->setAcceptHoverEvents(true);
    pointPump = false;
}

Pump::~Pump()
{

}

QRectF Pump::boundingRect() const
{
    return QRectF(-80,-80,160,160);
}



Reactor::Reactor(QObject *parent) : QObject(), QGraphicsItem()
{
    this->setAcceptHoverEvents(true);
    pointIn = false;
    pointOut = false;
}

Reactor::~Reactor()
{

}

QRectF Reactor::boundingRect() const
{
    return QRectF(-110,-70,220,140);
}

void Reactor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));

    painter->drawRect(-101,-55,190,110);

    qreal S=0;

    for(int i=0;i<120;i++)
        {
            QPointF p1(-100 + S/2 * 10,100 * sin(S)/2);
            S += 3.14/10;
            QPointF p2(-100 + S/2 * 10,100 * sin(S)/2);
            painter->drawLine(p1, p2);
        }

    if(pointIn)
        {
            painter->setPen(QPen(Qt::green, 2, Qt::SolidLine, Qt::FlatCap));
            painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));
            painter->drawEllipse(-105, 0, 10, 10);
        } else
        {
            painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
            painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
            painter->drawEllipse(-105, 0, 10, 10);
        }


        if(pointOut)
        {
            painter->setPen(QPen(Qt::green, 2, Qt::SolidLine, Qt::FlatCap));
            painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));
            painter->drawEllipse(84, 0, 10, 10);
        } else
        {
            painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
            painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
            painter->drawEllipse(84, 0, 10, 10);
        }
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

    if(pointPump)
    {
        painter->setPen(QPen(Qt::green, 2, Qt::SolidLine, Qt::FlatCap));
        painter->setBrush(QBrush(Qt::green, Qt::SolidPattern));
        painter->drawEllipse(45, -5, 10, 10);
    } else
    {
        painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
        painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
        painter->drawEllipse(45, -5, 10, 10);
    }



    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));

    if(QString("%1").arg(name) !="")
    {
        painter->drawText(-70,60,QString("Сompound: %1").arg(name));
    }

    if(QString("%1").arg(feed) !="")
    {
        painter->drawText(-70,70,QString("Feed rate: %1 mL/min ").arg(feed));
    }

    if(QString("%1").arg(conc) !="")
    {
        painter->drawText(-70,80,QString("Сoncentration: %1 mmol/l").arg(conc));
    }


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
        name = pumpD->getName();
        conc = pumpD->getConc();
        feed = pumpD->getFeed();
        pump = pumpD->getPump();

        if(pump == "Pump 1")
        {
           emit pump1signal(feed);
        }

        if(pump == "Pump 2")
        {
           emit pump2signal(feed);
        }

        if(pump == "Pump 3")
        {
           emit pump3signal(feed);
        }

        if(pump == "Pump 4")
        {
           emit pump4signal(feed);
        }

    } delete pumpD;

    Q_UNUSED(event);
}

void Pump::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    int x = event->pos().x();
        int y = event->pos().y();

        QRectF r(45, -5, 10, 10);

        if (r.contains(event->pos().x(),event->pos().y()))
        {
            pointPump=true;
            this->update(boundingRect());

        } else
        {
           pointPump=false;
           this->update(boundingRect());
        }

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

void Reactor::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    reactorD = new reactorDialog;
     if (reactorD->exec() == QDialog::Accepted) {
         temper = reactorD->getTemper();
         coil = reactorD->getCoil();
     }
    Q_UNUSED(event);
}

void Reactor::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    int x = event->pos().x();
       int y = event->pos().y();
       QRectF r1(-105, 0, 10, 10);
       QRectF r2(84, 0, 10, 10);


       if (r1.contains(event->pos().x(),event->pos().y()))
       {
           pointIn=true;
           this->update(boundingRect());

       } else
       {
          pointIn=false;
          this->update(boundingRect());
       }
       if (r2.contains(event->pos().x(),event->pos().y()))
       {
           pointOut=true;
           this->update(boundingRect());

       } else
       {
          pointOut=false;
          this->update(boundingRect());
       }
    Q_UNUSED(event);
}
