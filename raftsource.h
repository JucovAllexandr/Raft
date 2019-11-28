#ifndef RAFTPROTOCOL_H
#define RAFTPROTOCOL_H

#include "rep_RaftProtocol_merged.h"
#include <QUuid>
#include <Role.h>
#include <QTimer>
#include <raftreplica.h>


class RaftReplica;
class RaftSource: public RaftProtocolSimpleSource
{
    friend class RaftReplica;

    struct Entity{
        uint term;
        QString msg;
        Entity(){term = 0;}
        Entity(uint term, QString msg):term(term), msg(msg){}
    };

    Q_OBJECT
    uint currentTerm = 0;
    uint electionTimeout = 0;
    Role role = Follower;
    QTimer timer;
    QVector<RaftReplica*> replics;
    QVector<QPair<QUuid, bool>> votes;
    QVector<Entity> entries;
    uint prevLogTerm = 0;
    uint prevIndex = 0;
    uint commitedIndex = 0;

public:
    RaftSource(QObject *parent = nullptr);
    void ResponseVote(QUuid senderId,uint term, bool granted) override;

    uint getCurrentTerm() const;

    Role getRole() const;
    uint getElectionTimeout() const;
    void timerStart();
    void timerStop();

private:
    void setRole(Role role);
    void setCurrentTerm(const uint &value);
    void addReplica(RaftReplica *rp);
    void removeReplica(RaftReplica *rp);

    void AppendString(QString str) override;
    void checkLeader() override;

signals:
    void roleChanged(Role role);
    void termChanged(uint term);

private slots:

    void timeOut();
};

#endif // RAFTPROTOCOL_H
