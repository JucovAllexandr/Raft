#ifndef RAFTREPLICA_H
#define RAFTREPLICA_H

#include "rep_RaftProtocol_merged.h"
#include <raftsource.h>
#include <QTableWidgetItem>

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
signals:
    void connected(RaftReplica *rp);
};

#endif // RAFTREPLICA_H
