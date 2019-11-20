#ifndef HELPER_H
#define HELPER_H

#include <QtGlobal>
#include <Role.h>
#include <QDateTime>

class Helper
{
public:
    static int randomBetween(int low, int high);
    static QString roleToString(const Role &role) ;
};

#endif // HELPER_H
