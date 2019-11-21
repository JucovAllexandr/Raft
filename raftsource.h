#ifndef RAFTPROTOCOL_H
#define RAFTPROTOCOL_H

#include <rep_RaftProtocol_source.h>
#include <QUuid>
#include <Role.h>
#include <QTimer>

class RaftSource: public RaftProtocolSimpleSource
{
    Q_OBJECT
    uint currentTerm = 1;
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
private:
    void setRole(Role role);
signals:
    void roleChanged(Role role);
public slots:
    void getId() override;
private slots:
    void timeOut();
};

#endif // RAFTPROTOCOL_H
