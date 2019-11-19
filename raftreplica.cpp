#include "raftreplica.h"
#include <QDebug>

RaftReplica::RaftReplica():QObject(nullptr)
{
}

void RaftReplica::showId(QString msg)
{
    qDebug() <<"Show "<<id<<" msg: "<< msg;
}
