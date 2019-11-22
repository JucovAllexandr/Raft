#ifndef RAFTREPLICA_H
#define RAFTREPLICA_H

#include "rep_RaftProtocol_merged.h"
#include <raftsource.h>
#include <QTableWidgetItem>
class RaftSource;
class RaftReplica: public QObject
{
    Q_OBJECT
    RaftSource *source;
    RaftProtocolReplica *replica;
    QUuid votedFor;
    uint oldTerm;

public:
    RaftReplica(RaftProtocolReplica* replica, RaftSource *source);
    QUuid sourceId();

private:
    void requestVote(QUuid candidateId, uint term);
    void AppendEntries(uint term, QUuid leaderId);
    void stateChanged(QRemoteObjectReplica::State state, QRemoteObjectReplica::State oldState);

signals:
    void connected(RaftReplica *rp);
};

#endif // RAFTREPLICA_H
