#include "cbdd.h"

CBdd::CBdd(pa * therpi)
{
    rpi = therpi;

    Aies_bdd =QSqlDatabase::addDatabase(rpi->getBddType());
    Aies_bdd.setDatabaseName(rpi->getBddName());
    Aies_bdd.setHostName(rpi->getBddHostname());
    Aies_bdd.setUserName(rpi->getBddUsername());
    Aies_bdd.setPassword(rpi->getBddPassword());
    if(!Aies_bdd.open())
    {
        qDebug("Ouverture de la base de donnée impossible");
        system("/sbin/reboot");
        exit(1);
    }
}
CBdd::~CBdd()
{
    delete rpi;
    Aies_bdd.close();
}

int CBdd::getNbRowDiff(QString date_actu)
{
    QSqlQuery aiesquery("SELECT COUNT(*) as nb FROM rpi_update WHERE id=2 and date <= " + date_actu);
    aiesquery.next();
    return aiesquery.value(0).toInt();
}

void CBdd::moveDiff()
{
    QSqlQuery data("SELECT * FROM rpi_update WHERE id=2");
    data.next();
    QSqlQuery updatequery("UPDATE rpi_update SET version = '" + data.value(1).toString() + "', date = '" + data.value(2).toString() + "', date_create = '" + data.value(3).toString() + "', path = '" + data.value(4).toString() + "', size = " + data.value(5).toInt() + " WHERE id=1");
    QSqlQuery deletequery("DELETE FROM rpi_update WHERE id=2");
}

float CBdd::getVersionPerma()
{
    QSqlQuery aiesquery("SELECT version FROM rpi_update WHERE id=1");
    aiesquery.next();
    return aiesquery.value(0).toFloat();
}

QString CBdd::getPathPerma()
{
    QSqlQuery aiesquery("SELECT path FROM rpi_update WHERE id=1");
    aiesquery.next();
    return aiesquery.value(0).toString();
}

int CBdd::getSizePerma()
{
    QSqlQuery aiesquery("SELECT size FROM rpi_update WHERE id=1");
    aiesquery.next();
    return aiesquery.value(0).toInt();
}
