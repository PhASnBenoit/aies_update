#include "pa.h"


pa::pa()
{ // info du config
    QSettings settings("/opt/aies/aies.ini", QSettings::IniFormat);

    BddType = settings.value("Bdd/type", "QMYSQL").toString();
    BddHostname = settings.value("Serveur/ip", "10.73.254.1").toString();
    BddName = settings.value("Bdd/name", "aies2018").toString();
    BddUsername = settings.value("Bdd/username", "aies2016").toString();
    BddPassword = settings.value("Bdd/password", "aies2016").toString();
    NumVersion = settings.value("Rpi/version", "2.0").toFloat();

    char buffer[1000];
    FILE *file_macAddress;
    if((file_macAddress=fopen("/sys/class/net/eth0/address", "r")) == NULL)
    {
        exit(1);
    }
    fscanf(file_macAddress, "%[^\n]", buffer);
    fclose(file_macAddress);

    MacAdress = buffer;
}

pa::~pa()
{

}

QString pa::getBddType()
{
    return BddType;
}

QString pa::getBddHostname()
{
    return BddHostname;
}

QString pa::getBddName()
{
    return BddName;
}

QString pa::getBddUsername()
{
    return BddUsername;
}

QString pa::getBddPassword()
{
    return BddPassword;
}

float pa::getNumVersion()
{
    return NumVersion;
}

QString pa::getMacAdress()
{
    return MacAdress;
}
