#ifndef RAFTREPLICA_H
#define RAFTREPLICA_H

#include "rep_RaftProtocol_replica.h"

class RaftReplica: public QObject
{
    Q_OBJECT
public:
    QString id;

    RaftReplica();
    void setId(QString id){
        this->id = id;
    }
    void showId(QString msg);
};

#endif // RAFTREPLICA_H
