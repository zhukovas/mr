#include "moduls.h"
#include "mainwindow.h"
#include "pumpdialog.h"
#include "reactordialog.h"
#include "collectordialog.h"
#include "qdebug.h"
#include <QMessageBox>


Pump::Pump(QObject *parent) : QObject (), QGraphicsItem()

{

    this->setAcceptHoverEvents(true);
    pointRed = false;
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
    in = false;
    out = false;
}

Reactor::~Reactor()
{

}


Collector::Collector(QObject *parent) : QObject(), QGraphicsItem()
{

    this->setAcceptHoverEvents(true);
    point = false;
}


Collector::~Collector()
{

}

QRectF Collector::boundingRect() const
{
    return QRectF(-80,-80,160,160);
}

void Collector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter->drawEllipse(-70, -70, 140, 140);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Collector::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
    Q_UNUSED(event);
}

void Collector::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void Collector::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void Collector::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void Collector::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
}


QRectF Reactor::boundingRect() const
{
    return QRectF(-110,-90,220,180);
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

    if(QString("%1").arg(temper) !="")
    {
        painter->drawText(-70,67,QString("Temperature: /%1 C  Error").arg(temper));
    }

    if(QString("%1").arg(coil) !="")
    {
        painter->drawText(-70,80,QString("Coil volume: %1 mkl").arg(coil.toInt()*7.85));
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

    if(pointRed)
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

    if ((x==46 || x==47 || x==48 || x==49 || x==50 || x==51 || x==52 || x==53) &&
           (y == -4 ||  y == -3 ||  y == -2 ||  y == -1 ||  y == 0 ||  y == 1 ||  y == 2 || y == 3)  )
    {
        pointRed=true;
        this->update(boundingRect());

    } else
    {
       pointRed=false;
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
         emit reactor_t_signal(temper);
     }
    Q_UNUSED(event);
}

void Reactor::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{

    Q_UNUSED(event);
}

void Reactor::temperSlot(int t)
{

}

void Reactor::temperEeeorSlot(int t)
{

}


