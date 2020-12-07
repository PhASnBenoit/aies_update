#ifndef FIHM_H
#define FIHM_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QProcess>
#include <QFile>
#include <string>
#include <QString>
#include "cbdd.h"
#include "pa.h"

namespace Ui {
class fihm;
}

class fihm : public QMainWindow
{
    Q_OBJECT

public:
    explicit fihm(QWidget *parent = 0);
    ~fihm();
    void getUpdate();

public slots:
    void ontimerui();
    void ontimer_download();

private:
    bool diffExist();
    bool compConfig();
    void dwnldZip();
    void makeUpdate();


    QTimer * timerui;
    QTimer * timer_download;
    CBdd * bdd;
    pa * rpi;
    Ui::fihm *ui;

    int sizePerma;
};

#endif // FIHM_H
