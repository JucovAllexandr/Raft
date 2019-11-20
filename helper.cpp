#include "helper.h"

int Helper::randomBetween(int low, int high)
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    return (qrand() % ((high + 1) - low) + low);
}

QString Helper::roleToString(const Role &role)
{
    QString tmp;

    switch (role) {
    case Follower:
        tmp = "Follower";
        break;
    case Candidate:
        tmp = "Candidate";
        break;
    case Leader:
        tmp = "Leader";
        break;
    default:
        tmp = "Error";
        break;
    }
    return  tmp;
}
