#include "raftreplica.h"
#include <QDebug>

RaftReplica::RaftReplica(RaftProtocolReplica *replica, RaftSource *source):QObject(nullptr), source(source), replica(replica)
{
    connect(replica, &RaftProtocolReplica::RequestVote, this, &RaftReplica::requestVote);
    connect(replica, &RaftProtocolReplica::AppendEntries, this, &RaftReplica::AppendEntries);
    connect(replica, &RaftProtocolReplica::stateChanged, this, &RaftReplica::stateChanged);
    oldTerm = 0;
    //connect()
}

QUuid RaftReplica::sourceId()
{
    // QSignalSpy spy(replica, &RaftProtocolReplica::idChanged);
    ///qDebug()<<"id"<<replica->getId().returnValue();
    return replica->id();
}

void RaftReplica::requestVote(QUuid candidateId, uint term)
{
    qDebug() << "Rquest vote: candidateId "<<candidateId.toString()<<" term"<<term;

    if(source->getRole() == Follower){
        if(term > oldTerm){
            votedFor = candidateId;
            oldTerm = term;
        }

        source->setCurrentTerm(term);
        source->timer.stop();

        if(votedFor == candidateId){
            replica->ResponseVote(source->id(), term, true);
            source->timer.start(static_cast<int>(source->electionTimeout));
        }else{
            replica->ResponseVote(source->id(), term, false);
        }
    }else if (source->getRole() == Candidate){
        replica->ResponseVote(source->id(), term, false);
    }
}

void RaftReplica::AppendEntries(uint term, QUuid leaderId)
{
    qDebug()<<"AppendEntries "<<term<<" "<<leaderId;
    source->setCurrentTerm(term);
    oldTerm = term;
    votedFor = leaderId;

    if(source->getRole() == Candidate){
        source->setRole(Follower);
    }

   // source->timerStop();
    source->timerStart();
}


void RaftReplica::stateChanged(QRemoteObjectReplica::State state, QRemoteObjectReplica::State oldState)
{
    qDebug() <<"Sate changed from "<<oldState<<" to "<< state;
    if(state == QRemoteObjectReplica::State::Valid){
        //qDebug()<<"get id"<<replica->getId().returnValue();
        source->addReplica(this);
        emit connected(this);

    }else if (state == QRemoteObjectReplica::Suspect){
        source->removeReplica(this);
    }

}

