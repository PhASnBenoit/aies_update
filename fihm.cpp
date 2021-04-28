#include "fihm.h"
#include "ui_fihm.h"

fihm::fihm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fihm)
{
    ui->setupUi(this);
    timerui = new QTimer();
    timerui->connect(timerui, SIGNAL(timeout()), this, SLOT(ontimerui()));
    timerui->start(500);

    timer_download = new QTimer();
    timer_download->connect(timer_download, SIGNAL(timeout()), this, SLOT(ontimer_download()));

    ui->lb_title->setText("Mise à jour du point d'affichage .");
    ui->lb_operation->setText("Etape : Récupération de la configuration actuelle..");

    rpi = new pa();

    ui->progressBar->setValue(10);
    ui->lb_operation->setText("Etape : Connexion à la base de données..");

    bdd = new CBdd(rpi);

    ui->progressBar->setValue(20);
    ui->lb_operation->setText("Etape : Recherche d'une mise à jour differée..");

    if(diffExist())
    {
        ui->progressBar->setValue(25);
        ui->lb_operation->setText("Etape : Déplacement de la mise à jour differée..");
        bdd->moveDiff();
    }

    ui->progressBar->setValue(30);
    ui->lb_operation->setText("Etape : Comparaison avec la mise à jour permanente..");

    if(compConfig())
    {
        ui->progressBar->setValue(50);
        ui->lb_operation->setText("Etape : Téléchargement de la mise à jour...");

        dwnldZip();
    }
    else
    {
        qDebug("System: Pas de mise à jour dans la BDD.");
        exit(0);
    }
}

fihm::~fihm()
{
    delete rpi;
    delete bdd;
    delete timerui;
    delete ui;
}


void fihm::dwnldZip()
{
    qDebug() << "fihm::dwnldZip création du répertoire /tmp/aies";
    system("mkdir /tmp/aies/");
    QString command = "wget --limit-rate=10k -b -O /tmp/aies/updateAIES.tgz http://" + rpi->getBddHostname() +
            "/2018/htdocs" + bdd->getPathPerma() + " -o /tmp/aies/log_update.txt";
    qDebug() << "fihm::dwnldZip téléchargement... " << command;
    system(command.toStdString().c_str());
    sizePerma = bdd->getSizePerma();
    timer_download->start(1000);
}

void fihm::makeUpdate()
{
    qDebug() << "fihm::makeUpdate effacement du répertoire /opt/aies";
    system("rm /opt/aies/*.* -R");
    qDebug() << "fihm::makeUpdate décompresse dans le dossier /opt/aies";
    system("tar xzf /tmp/aies/updateAIES.tgz -C /opt/aies/");
    qDebug() << "fihm::makeUpdate effacement du dossier /tmp/aies";
    system("rm /tmp/aies -R");
    qDebug() << "fihm::makeUpdate changement des droits";
    system("chmod -R 755 /opt/aies");

    ui->progressBar->setValue(100);
    ui->lb_operation->setText("Installation terminée !");
    //qApp->exit(); // ferme l'application pour le moment
    system("/sbin/reboot");
}


void fihm::ontimerui()
{
    if(ui->lb_title->text() == "Mise à jour du point d'affichage .")
    {
        ui->lb_title->setText("Mise à jour du point d'affichage ..");
    }
    else if(ui->lb_title->text() == "Mise à jour du point d'affichage ..")
    {
        ui->lb_title->setText("Mise à jour du point d'affichage ...");
    }
    else if(ui->lb_title->text() == "Mise à jour du point d'affichage ...")
    {
        ui->lb_title->setText("Mise à jour du point d'affichage .");
    }
}

bool fihm::diffExist()
{
    QDateTime dateTime;
    dateTime = QDateTime::currentDateTime();
    QString date_actu = dateTime.toString("yyyyMMddhhmm");

    if(bdd->getNbRowDiff(date_actu) == 1) return true;
    else return false;
}

bool fihm::compConfig()
{
    if(bdd->getVersionPerma() > rpi->getNumVersion()) return true;
    else return false;
}


void fihm::ontimer_download()
{
    system("du -b /tmp/aies/updateAIES.tgz | cut -d '/' -f1 > /tmp/aies/log_size.txt");

    QFile log_update("/tmp/aies/log_update.txt");
    log_update.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux_log_update(&log_update);
    QString data_log_update = flux_log_update.readAll();
    if(data_log_update.indexOf("100%", 0) != -1)
    {
        timer_download->stop();
        ui->progressBar->setValue(80);
        ui->lb_operation->setText("Etape : Installation de la mise a jour..");
        makeUpdate();
    }
    else
    {
        QFile log_size("/tmp/aies/log_size.txt");
        log_size.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream flux_log_size(&log_size);
        QString data_log_size = flux_log_size.readAll();
        int sizeActu = data_log_size.toInt();

        ui->progressBar->setValue(int(((sizeActu * 30) / sizePerma) + 50));
    }
}

