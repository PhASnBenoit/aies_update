#ifndef PA_H
#define PA_H

#include <QString>
#include <QDebug>
#include <QSettings>
#include <fstream>
#include <iostream>
#include <istream>

class pa
{
private:
    QString BddType;
    QString BddHostname;
    QString BddName;
    QString BddUsername;
    QString BddPassword;
    float NumVersion;
    QString MacAdress;

public:
    pa(); //recupere les info dans le fichier config
    ~pa();
    QString getBddType();
    QString getBddHostname();
    QString getBddName();
    QString getBddUsername();
    QString getBddPassword();
    float getNumVersion();
    QString getMacAdress();
};

#endif // PA_H
