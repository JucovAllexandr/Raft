#include "raftsource.h"
#include <QDebug>

RaftSource::RaftSource(QObject *parent):
    RaftProtocolSource(parent)
{
    connect(&timer, &QTimer::timeout, [this]{
        emit RequestVote("id1");
    });
    timer.start(2000);

}

void RaftSource::connectToSignal()
{
    timer.stop();
    connect(this, SIGNAL(RequestVote(QString)), this, SLOT(AppendEntries(QString)));

}

void RaftSource::AppendEntries(QString id)
{
    qDebug()<<"AppendEntries "<<id;
}
