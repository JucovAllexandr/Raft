#include "raftsource.h"
#include <QDebug>
#include <helper.h>

uint RaftSource::getCurrentTerm() const
{
    return currentTerm;
}

Role RaftSource::getRole() const
{
    return role;
}

uint RaftSource::getElectionTimeout() const
{
    return electionTimeout;
}

void RaftSource::timerStart()
{
    timer.start(static_cast<int>(electionTimeout));
}

void RaftSource::setRole(Role role)
{
    this->role = role;
    emit roleChanged(role);
}

void RaftSource::timeOut()
{
    setRole(Candidate);
    setCurrentTerm(currentTerm + 1);
    emit RequestVote(id(), currentTerm);
}

void RaftSource::setCurrentTerm(const uint &value)
{
    currentTerm = value;
    emit termChanged(value);
}

RaftSource::RaftSource(QObject *parent):
    RaftProtocolSimpleSource(parent)
{
    setId(QUuid::createUuid());
    electionTimeout = static_cast<uint>(Helper::randomBetween(100, 300));
    connect(&timer, &QTimer::timeout, this, &RaftSource::timeOut);
}


void RaftSource::AppendEntries(QString id)
{
    qDebug()<<"AppendEntries "<<id;
}

void RaftSource::ResponseVote(uint term, bool granted)
{
    qDebug()<<"Response vote "<<term<<" "<<granted;
    timer.stop();
}
