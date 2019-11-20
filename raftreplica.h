#ifndef RAFTREPLICA_H
#define RAFTREPLICA_H

#include "rep_RaftProtocol_replica.h"
#include <raftsource.h>

class RaftReplica: public QObject
{
    Q_OBJECT
    RaftSource *source;
    RaftProtocolReplica *replica;
public:
    RaftReplica(RaftProtocolReplica* replica, RaftSource *source);
    QUuid Id();
    void requestVote(QUuid id, uint term);
    void stateChanged(QRemoteObjectReplica::State state, QRemoteObjectReplica::State oldState);
};

#endif // RAFTREPLICA_H
