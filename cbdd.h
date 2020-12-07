#ifndef CBDD_H
#define CBDD_H

#include <stdio.h>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QVariant>
#include <QDebug>
#include "pa.h"

class CBdd
{
public:
    CBdd(pa * rpi);
    ~CBdd();

    //getter and setter bdd (ordre chrono d'appel)

    int getNbRowDiff(QString date_actu);
    void moveDiff();
    float getVersionPerma();
    QString getPathPerma();
    int getSizePerma();

    //fin getter and sett  bdd
private:
    pa * rpi;
    QSqlDatabase Aies_bdd;
};

#endif // CBDD_H
