#include "raftreplica.h"
#include <QDebug>

RaftReplica::RaftReplica(RaftProtocolReplica *replica, RaftSource *source):QObject(nullptr), source(source), replica(replica)
{


    connect(replica, &RaftProtocolReplica::RequestVote, this, &RaftReplica::requestVote);
    connect(replica, &RaftProtocolReplica::stateChanged, this, &RaftReplica::stateChanged);
}

QUuid RaftReplica::Id()
{
    return replica->id();
}

void RaftReplica::requestVote(QUuid id, uint term)
{
   qDebug() << "Rquest "<<id.toString()<<" term"<<term;

   if(source->getRole() == Follower){
       replica->ResponseVote(1, true);
   }
}


void RaftReplica::stateChanged(QRemoteObjectReplica::State state, QRemoteObjectReplica::State oldState)
{
    qDebug() <<"Sate changed from "<<oldState<<" to "<< state;
}
