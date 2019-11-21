#ifndef RAFTPROTOCOL_H
#define RAFTPROTOCOL_H

#include "rep_RaftProtocol_merged.h"
#include <QUuid>
#include <Role.h>
#include <QTimer>

class RaftSource: public RaftProtocolSimpleSource
{
    Q_OBJECT
    uint currentTerm = 0;
    uint electionTimeout = 0;
    Role role = Follower;
    QTimer timer;

public:
    RaftSource(QObject *parent = nullptr);
    void AppendEntries(QString id) override;
    void ResponseVote(uint term, bool granted) override;

    uint getCurrentTerm() const;

    Role getRole() const;
    uint getElectionTimeout() const;
    void timerStart();

private:
    void setRole(Role role);
    void setCurrentTerm(const uint &value);

signals:
    void roleChanged(Role role);
    void termChanged(uint term);

private slots:

    void timeOut();
};

#endif // RAFTPROTOCOL_H
