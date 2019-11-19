#ifndef RAFTPROTOCOL_H
#define RAFTPROTOCOL_H

#include <rep_RaftProtocol_source.h>
#include <QTimer>

class RaftSource: public RaftProtocolSource
{
    Q_OBJECT
    QTimer timer;
public:
    RaftSource(QObject *parent = nullptr);
    void connectToSignal();
    void AppendEntries(QString id) override;
};

#endif // RAFTPROTOCOL_H
