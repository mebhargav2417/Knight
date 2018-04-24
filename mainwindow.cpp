#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
#include <QDebug>
#include <QJsonObject>
#include <forserverconnection.h>
#include <QJsonDocument>
#include <QVariantMap>
#include<QtNetwork>
#include<qjsonobject.h>
#include<QString>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QFileDialog>
#include "xlsxdocument.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    constants->entryType = 0;
    constants->registrationType = 0;
    setGui();
    QSettings settings("D:/settings.ini",QSettings::IniFormat);
//    settings.beginGroup("settings");
//    qDebug()<<settings.value("url").toString();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLogin_clicked()
{
    if(ui->lineEditUserId->text().length() != 0){
        if(ui->lineEditPwd->text().length() != 0) {
            ui->stackedWidget->setCurrentWidget(ui->homeWidget);
        } else {
            ui->label_status_mainpage->setText("Password required");
        }
    } else {
        ui->label_status_mainpage->setText("Userid required");
    }
}

void MainWindow::makeConnection(QString url, QJsonObject data)
{
//    QJsonObject json;
//    json.insert("businessType","individual");
//    json.insert("fistName","knight");
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QObject::connect(manager, SIGNAL(finished(QNetworkReply *)),SLOT(slotRequestFinished(QNetworkReply *)));

        QNetworkRequest request;
        request.setUrl(QUrl(url)); //"http://localhost:8080/KnightMessaging/rest/registrationService/registration"
//        request.setRawHeader("Authorization", "Basic " +
//                             QByteArray(QString("%1:%2").arg("user").arg("asas").toAscii()).toBase64());
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QNetworkReply *reply = 0;
        reply = manager->post(request,QJsonDocument(data).toJson());

//        QObject::connect(manager, SIGNAL(finished(QNetworkReply *)),SLOT(slotRequestFinished(QNetworkReply *)));
}

void MainWindow::slotRequestFinished(QNetworkReply *reply)
{
    if (reply->error() > 0) {
        qDebug()<<reply->errorString();
    }
    else {
        qDebug()<<reply->readAll();
    }
}

void MainWindow::on_pushButtonLogout_clicked()
{
    setGuiForMainPage();
}

void MainWindow::setGui()
{
    // init all gui here
    listYesNo<<"Select"<<"Yes"<<"No";
    listBusinessType<<"Select Business Type"<<"Individual"<<"Other";
    listGender<<"Select Sex"<<"Male"<<"Female";
    listBankAcc<<"Select"<<"Savings"<<"Current"<<"OD";
    ui->stackedWidget->setCurrentWidget(ui->mainWidget);
    ui->stackedWidgetHome->setCurrentWidget(ui->pageHomePlain);
    ui->lineEditUserId->setText("");
    ui->lineEditPwd->setText("");
    ui->label_status_mainpage->setText("");
}

void MainWindow::setGuiForRegistration()
{
    ui->stackedWidgetHome->setCurrentWidget(ui->pageNewReg1);
    ui->comboBoxBusinessType->addItems(listBusinessType);
    ui->editBusinessTypeName->setText("");
    ui->editBusinessName->setText("");
    ui->editFirstName->setText("");
    ui->editSurName->setText("");
//    ui->dateEditDob->setDate("");
    ui->comboBoxSex->addItems(listGender);
    ui->editDoorNo->setText("");
    ui->editLocality->setText("");
    ui->editStreet->setText("");
    ui->editCity->setText("");
    ui->editState->setText("");
    ui->editPinCode->setText("");
    ui->editPanno->setText("");
    ui->editAadhasrNo->setText("");
    ui->editMobileNo->setText("");
    ui->editAltMobileNo->setText("");
    ui->editMail->setText("");
    ui->comboBoxSeniorCtznapp->addItems(listYesNo);
    ui->editSrCtznClause->setText("");
    ui->editCinUinNo->setText("");
    ui->editSignatory1->setText("");
    ui->editSig1Mobile->setText("");
    ui->editSignatory2->setText("");
    ui->editSig2Mobile->setText("");
    ui->editTurnOver->setText("");
    ui->comboBoxReverse->addItems(listYesNo);
    ui->comboBoxGSTApp->addItems(listYesNo);;
    ui->editGSTNo->setText("");
    ui->editGSTType->setText("");
    ui->comboBoxSEZSTPIApp->addItems(listYesNo);
    ui->comboBoxExportApp->addItems(listYesNo);
    ui->lineEditExportRegNo->setText("");
    ui->comboBoxAccountType1->addItems(listBankAcc);
    ui->ediBankName1->setText("");
    ui->editAccNo1->setText("");
    ui->editIFSC1->setText("");
    ui->comboBoxAccountType2->addItems(listBankAcc);
    ui->ediBankName2->setText("");
    ui->editAccNo2->setText("");
    ui->editIFSC2->setText("");
    ui->comboBoxAccountType3->addItems(listBankAcc);
    ui->ediBankName3->setText("");
    ui->editAccNo3->setText("");
    ui->editIFSC3->setText("");
    ui->comboBoxAccountType4->addItems(listBankAcc);
    ui->ediBankName4->setText("");
    ui->editAccNo4->setText("");
    ui->editIFSC4->setText("");
}

void MainWindow::setGuiForMainPage()
{
    ui->lineEditUserId->setText("");
    ui->lineEditPwd->setText("");
    ui->label_status_mainpage->setText("");
    ui->stackedWidget->setCurrentWidget(ui->mainWidget);
}




void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if(item->text() == "New"){
        setGuiForRegistration();
    } else if(item->text() == "Edit") {
        ui->stackedWidgetHome->setCurrentWidget(ui->pageEdit);
    } else if(item->text() == "Delete") {
        ui->stackedWidgetHome->setCurrentWidget(ui->pageDelete);
    }

}

void MainWindow::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    if(item->text() == "New"){
        ui->stackedWidgetHome->setCurrentWidget(ui->pageNewEntry);
    } else if(item->text() == "Edit") {

    } else if(item->text() == "View") {

    }
}

void MainWindow::on_buttonRegistrationPage1_clicked()
{
    ui->stackedWidgetHome->setCurrentWidget(ui->pageNewReg2);
}

void MainWindow::on_btnPreviousRegPage2_clicked()
{
    ui->stackedWidgetHome->setCurrentWidget(ui->pageNewReg1);
}

void MainWindow::on_btnNextRegPage2_clicked()
{
    ui->stackedWidgetHome->setCurrentWidget(ui->pageNewRef3);
}

void MainWindow::on_btnPreviousNewPage3_clicked()
{
    ui->stackedWidgetHome->setCurrentWidget(ui->pageNewReg2);
}

void MainWindow::on_pushButtonFileNewentry_clicked()
{
//    QString filename =  QFileDialog::getOpenFileName(
//              this,
//              "Open Document",
//              QDir::currentPath(),
//              "All files (*.*) ;; Document files (*.xlsx *.rtf);; PNG files (*.png)");
    QString filename =  QFileDialog::getOpenFileName(
              this,
              "Open Document",
              QDir::currentPath(),
              "Document files (*.xlsx)");

        if( !filename.isNull() )
        {
          qDebug() << "selected file path : " << filename.toUtf8();
          QXlsx::Document xlsx(filename.toUtf8());
//          qDebug()<<xlsx.read("A1");
//          qDebug()<<xlsx.read("A2");
//          qDebug()<<xlsx.read("A3");
//          qDebug()<<xlsx.read("A4");
//          qDebug()<<xlsx.read("A5");
//          qDebug()<<xlsx.read("A6");
//          qDebug()<<xlsx.read("A7");

                QXlsx::CellRange *range;
                 qDebug()<<range->rowCount();
          for (int row=1; row<10; ++row) {
                  if (QXlsx::Cell *cell=xlsx.cellAt(row, 1))
                      qDebug()<<cell->value();
                  if (QXlsx::Cell *cell=xlsx.cellAt(row, 2))
                      qDebug()<<cell->value();
              }

//              xlsx.write("A1", "Hello Qt!");
//              xlsx.saveAs("Test.xlsx");
        }
}
