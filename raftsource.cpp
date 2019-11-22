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
    setRole(Follower);
    for(int i=0; i<votes.size();i++){
        qDebug()<<votes.at(i);
    }
    timer.start(static_cast<int>(electionTimeout));
}

void RaftSource::timerStop()
{
    timer.stop();
}

void RaftSource::addReplica(RaftReplica *rp)
{
    replics.push_back(rp);
    votes.push_back(QPair<QUuid, bool>(rp->sourceId(), false));
}

void RaftSource::removeReplica(RaftReplica *rp)
{
    replics.removeOne(rp);
    votes.clear();
    for(int i = 0; i < replics.size(); ++i){
        votes.push_back(QPair<QUuid, bool>(replics.at(i)->sourceId(), false));
    }
}

void RaftSource::setRole(Role role)
{
    this->role = role;
    emit roleChanged(role);
}

void RaftSource::timeOut()
{
    for(int i = 0; i <votes.size(); ++i){
        votes[i].second = false;
    }

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

void RaftSource::ResponseVote(QUuid senderId, uint term, bool granted)
{
    qDebug()<<"Response vote sender "<<senderId<<" term "<< term<<" "<<granted;
    int voted = 0;

    for(int i = 0; i < votes.size(); ++i){
        if(votes.at(i).first == senderId){
            votes[i].second = granted;
            voted++;
            break;
        }else if (votes.at(i).second){
            voted++;
        }
    }

    if(!votes.isEmpty()){
        if(votes.size() == 2){
            if(voted >= votes.size() / 2){
                timer.stop();
                setRole(Leader);
                setCurrentTerm(currentTerm+1);
                emit AppendEntries(currentTerm, id());
            }
        }
        else if(voted > votes.size() / 2){
            timer.stop();
            setRole(Leader);
            setCurrentTerm(currentTerm+1);
            emit AppendEntries(currentTerm, id());
        }
    }

}
