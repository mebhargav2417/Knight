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
#include<QMessageBox>
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
    constants->apiType = 0;
    setGui();
    if(QFileInfo("D:/settings.ini").exists() && QFileInfo("D:/settings.ini").isFile()){
        QSettings settings("D:/settings.ini",QSettings::IniFormat);
        settings.beginGroup("settings");
        qDebug()<<settings.value("url").toString();
    } else {
        QMessageBox::information(this,tr("Alert"),tr("Configuration file not found") );
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLogin_clicked()
{
    if(ui->lineEditMailLogin->text().length() != 0){
        if(constants->checkMail(ui->lineEditMailLogin->text()) == true) {
            if(ui->lineEditUserId->text().length() != 0){
                if(ui->lineEditPwd->text().length() != 0 && ui->lineEditPwd->text().length() >= 8) {
                    QJsonObject json;
                    json.insert("mail",ui->lineEditMailLogin->text());
                    json.insert("userName",ui->lineEditUserId->text());
                    qDebug()<<ui->lineEditPwd->text().toUtf8().toBase64();
                    json.insert("dwp",QString(ui->lineEditPwd->text().toUtf8().toBase64()));
                    QSettings settings("D:/settings.ini",QSettings::IniFormat);
                    settings.beginGroup("settings");
                    QString url = settings.value("url").toString() + settings.value("mainUrl").toString() + settings.value("peopleLogin").toString();
                    constants->apiType = 1;
                    updateLabel("<font color='blue'>Connecting to server. Please wait...");
                    makeConnection(url,json);
                } else {
                    ui->label_status_mainpage->setText("<font color='red'>Password should be minimum 8 characters length</font>");
                    ui->lineEditPwd->setFocus();
                }
            } else {
                ui->label_status_mainpage->setText("<font color='red'>User name required</font>");
                ui->lineEditUserId->setFocus();
            }
        } else {
            ui->label_status_mainpage->setText("<font color='red'>Invalid mail id</font>");
            ui->lineEditMailLogin->setFocus();
        }
    } else {
        ui->label_status_mainpage->setText("<font color='red'>Mail id required</font>");
        ui->lineEditMailLogin->setFocus();
    }
}

void MainWindow::makeConnection(const QString url, QJsonObject data)
{
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QObject::connect(manager, SIGNAL(finished(QNetworkReply *)),SLOT(slotRequestFinished(QNetworkReply *)));
        QNetworkRequest request;
        request.setUrl(QUrl(url)); //"http://localhost:8080/KnightMessaging/rest/registrationService/registration"
//        request.setRawHeader("Authorization", "Basic " + QByteArray(QString("%1:%2").arg("user").arg("asas").toAscii()).toBase64());
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");    
        QNetworkReply *reply = 0;
        QCoreApplication::processEvents();
        reply = manager->post(request,QJsonDocument(data).toJson());
        updateLabel("<font color='blue'>Receiving response from server. Please wait...");
        //        QObject::connect(manager, SIGNAL(finished(QNetworkReply *)),SLOT(slotRequestFinished(QNetworkReply *)));
}

void MainWindow::updateLabel(const QString labelMessage)
{
    ui->label_status_mainpage->setText(labelMessage);
    ui->label_status_mainpage->repaint();
}

void MainWindow::slotRequestFinished(QNetworkReply *reply)
{
    int error = 0;
    if (reply->error() > 0) {
        qDebug()<<reply->errorString();
        error = 1; // error occured
        parseResponse(error, reply->errorString(), reply->readAll());
    }
    else {
        QByteArray response = reply->readAll();
        qDebug()<< response;
        error = 2; // error not occured
        parseResponse(error, reply->errorString(), response);
    }
}

void MainWindow::setGui()
{
    // init all gui here
    listYesNo<<"Select"<<"Yes"<<"No";
    listBusinessType<<"Select Business Type"<<"Individual"<<"Other";
    listGender<<"Select Sex"<<"Male"<<"Female";
    listBankAcc<<"Select"<<"Savings"<<"Current"<<"OD";
    listRole<<"Select"<<"Admin"<<"Manager"<<"Other";
    ui->stackedWidget->setCurrentWidget(ui->mainWidget);
    ui->stackedWidgetHome->setCurrentWidget(ui->pageHomePlain);
    ui->lineEditUserId->setText("");
    ui->lineEditPwd->setText("");
    ui->label_status_mainpage->setText("");
}

void MainWindow::setGuiForRegistration()
{
    ui->stackedWidgetHome->setCurrentWidget(ui->pageNewReg1);
    ui->comboBoxBusinessType->clear();
    ui->comboBoxBusinessType->addItems(listBusinessType);
    ui->editBusinessTypeName->setText("");
    ui->editBusinessName->setText("");
    ui->editFirstName->setText("");
    ui->editSurName->setText("");
//    ui->dateEditDob->setDate("");
    ui->comboBoxSex->clear();
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
    ui->comboBoxSeniorCtznapp->clear();
    ui->comboBoxSeniorCtznapp->addItems(listYesNo);
    ui->editSrCtznClause->setText("");
    ui->editCinUinNo->setText("");
    ui->editSignatory1->setText("");
    ui->editSig1Mobile->setText("");
    ui->editSignatory2->setText("");
    ui->editSig2Mobile->setText("");
    ui->editTurnOver->setText("");
    ui->comboBoxReverse->clear();
    ui->comboBoxReverse->addItems(listYesNo);
    ui->comboBoxGSTApp->clear();
    ui->comboBoxGSTApp->addItems(listYesNo);;
    ui->editGSTNo->setText("");
    ui->editGSTType->setText("");
    ui->comboBoxSEZSTPIApp->clear();
    ui->comboBoxSEZSTPIApp->addItems(listYesNo);
    ui->comboBoxExportApp->clear();
    ui->comboBoxExportApp->addItems(listYesNo);
    ui->lineEditExportRegNo->setText("");
    ui->comboBoxAccountType1->clear();
    ui->comboBoxAccountType1->addItems(listBankAcc);
    ui->ediBankName1->setText("");
    ui->editAccNo1->setText("");
    ui->editIFSC1->setText("");
    ui->comboBoxAccountType2->clear();
    ui->comboBoxAccountType2->addItems(listBankAcc);
    ui->ediBankName2->setText("");
    ui->editAccNo2->setText("");
    ui->editIFSC2->setText("");
    ui->comboBoxAccountType3->clear();
    ui->comboBoxAccountType3->addItems(listBankAcc);
    ui->ediBankName3->setText("");
    ui->editAccNo3->setText("");
    ui->editIFSC3->setText("");
    ui->comboBoxAccountType4->clear();
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
    ui->lineEditMailLogin->setText("");
    ui->labelusernewreg->setText("");
    ui->stackedWidget->setCurrentWidget(ui->mainWidget);
}

void MainWindow::on_buttonRegistrationPage1_clicked()
{
    validateRegPage1();
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

void MainWindow::on_pushButtonAdd_clicked()
{
    ui->lineEditRegUserEmp->setText("");
    ui->lineEditRegEmpPwd->setText("");
    ui->lineEditRegMailEmp->setText("");
    ui->comboBoxSelectRole->clear();
    ui->label_status_mainpage->setText("");
    ui->comboBoxSelectRole->addItems(listRole);
    ui->stackedWidget->setCurrentWidget(ui->pageAddNew);
}

void MainWindow::on_pushButtonRegNewEMp_clicked()
{
    if(ui->lineEditRegUserEmp->text().length() != 0) {
        if(ui->lineEditRegMailEmp->text().length() != 0) {
            if(constants->checkMail(ui->lineEditRegMailEmp->text()) == true) {
                if(ui->lineEditRegEmpPwd->text().length() != 0 && ui->lineEditRegEmpPwd->text().length() >= 8) {
                    if(ui->comboBoxSelectRole->currentText() != "Select") {
                        QJsonObject json;
                        json.insert("mail",ui->lineEditRegMailEmp->text());
                        json.insert("userName",ui->lineEditRegUserEmp->text());
                        json.insert("role",ui->comboBoxSelectRole->currentText());
//                        qDebug()<<ui->lineEditRegEmpPwd->text().toUtf8().toBase64();
                        json.insert("dwp",QString(ui->lineEditRegEmpPwd->text().toUtf8().toBase64()));
    //                    QString hash = ui->lineEditRegEmpPwd->text() + "|" + ui->lineEditRegMailEmp->text() + "|" + ui->lineEditRegUserEmp->text();
    //                    QByteArray hashString = QCryptographicHash::hash(hash.toLocal8Bit(), QCryptographicHash::Sha512);
    //                    qDebug()<< hashString;
                        QString encodedPass = QString(QCryptographicHash::hash(("my string"),QCryptographicHash::Sha256));
                        qDebug()<< encodedPass;
                        QSettings settings("D:/settings.ini",QSettings::IniFormat);
                        settings.beginGroup("settings");
                        QString url = settings.value("url").toString() + settings.value("mainUrl").toString() + settings.value("peopleReg").toString();
                        constants->apiType = 2;
                        updateLabel("<font color='blue'>Connecting to server. Please wait...</font>");
                        makeConnection(url,json);
                    } else {
                        ui->label_status_mainpage->setText("<font color='red'>Select role</font>");
                        ui->comboBoxSelectRole->setFocus();
                    }
                } else {
                    ui->label_status_mainpage->setText("<font color='red'>Password should be minimum 8 characters length</font>");
                    ui->lineEditRegEmpPwd->setFocus();
                }
            } else {
                ui->label_status_mainpage->setText("<font color='red'>Invalid mail id</font>");
                ui->lineEditRegMailEmp->setFocus();
            }
        } else {
            ui->label_status_mainpage->setText("<font color='red'>Mail required</font>");
            ui->lineEditRegMailEmp->setFocus();
        }
    } else {
        ui->label_status_mainpage->setText("<font color='red'>User name required</font>");
        ui->lineEditRegUserEmp->setFocus();
    }
}

void MainWindow::on_pushButton_clicked()
{
    setGuiForMainPage();
}

void MainWindow::on_listWidgetHomeMenu_itemClicked(QListWidgetItem *item)
{
    if(item->text() == "New User"){
        setGuiForRegistration();
    } else if(item->text() == "Edit User") {
        ui->stackedWidgetHome->setCurrentWidget(ui->pageEdit);
    } else if(item->text() == "Delete User") {
        ui->stackedWidgetHome->setCurrentWidget(ui->pageDelete);
    } if(item->text() == "New Data"){
        ui->stackedWidgetHome->setCurrentWidget(ui->pageNewEntry);
    } else if(item->text() == "Edit Data") {

    } else if(item->text() == "View Data") {

    } else if(item->text() == "Logout") {
        setGuiForMainPage();
    }
}

void MainWindow::parseResponse(int e,const QString message, QByteArray response) {
    if(e == 1) {
        if(constants->apiType == 1 || constants->apiType == 2) {
            updateLabel("<font color='red'>"+message+"</font>");
        } else {
            QMessageBox::information(this,tr("Alert"),"<font color='red'>"+message+"</font>");
        }
    } else if(e == 2) {
        if(constants->apiType == 1) {
            QJsonDocument jsdoc = QJsonDocument::fromJson(response);
            QJsonObject json = jsdoc.object();
            if(json.value("code").toString() == "100" && json.value("message").toString().contains("success")){
                updateLabel("");
                ui->labelusernewreg->setText(json.value("username").toString() + " logged in...");
                ui->stackedWidget->setCurrentWidget(ui->homeWidget);
            } else if(json.value("code").toString() == "101") {
                updateLabel("");
                QMessageBox::information(this,tr("Alert"),"<font color='red'>"+json.value("message").toString()+"</font>");
            }
        } else if(constants->apiType == 2) {
            QJsonDocument jsdoc = QJsonDocument::fromJson(response);
            QJsonObject json = jsdoc.object();
            if(json.value("code").toString() == "100" && json.value("message").toString().contains("success")){
                updateLabel("<font color='green'>Registration success with username <b>" + json.value("username").toString() + "</b>.</font>");
                ui->lineEditRegUserEmp->setText("");
                ui->lineEditRegEmpPwd->setText("");
                ui->lineEditRegMailEmp->setText("");
                ui->comboBoxSelectRole->clear();
                ui->comboBoxSelectRole->addItems(listRole);
            } else if(json.value("code").toString() == "101") {
                updateLabel("");
                QMessageBox::information(this,tr("Alert"),"<font color='red'>"+json.value("message").toString()+"</font>");
            }
        }
    }

//    QJsonDocument jsdoc;
//    jsdoc = QJsonDocument::fromJson(reply->readAll());
//    QJsonObject jsobj = jsdoc.object();
//    QJsonArray jsarr = jsobj[“feeds”].toArray();
//    foreach (const QJsonValue &value, jsarr) {
//    QJsonObject jsob = value.toObject();
//    qDebug() << jsob[“entry_id”].toInt();
//    qDebug() << jsob[“field1”].toString();
//    qDebug() << jsob[“field2”].toString();
//    qDebug() << jsob[“field3”].toString();
//    qDebug() << jsob[“created_at”].toString();
//    }
    //    reply->deleteLater();
}

void MainWindow::validateRegPage1()
{
    if(ui->comboBoxBusinessType->currentText() != "Select Business Type") {
        if(ui->editBusinessTypeName->text() != 0) {
            if(ui->editBusinessName->text() != 0) {
                if(ui->editFirstName->text() != 0) {
                    if(ui->comboBoxBusinessType->currentText() == "Individual" && ui->editSurName->text() != 0) {
                        QDateTime date = QDateTime::fromString(ui->dateEditDob->text());
                            qDebug()<<constants->forDateFormat(ui->dateEditDob->text().replace("/","-"));
                    } else {
                        updateLabel("<font color='red'>Please enter sur name</font>");
                    }
                } else {
                    updateLabel("<font color='red'>Please enter first name</font>");
                }
            } else {
                updateLabel("<font color='red'>Please enter business name</font>");
            }
        } else {
           updateLabel("<font color='red'>Please enter business type name</font>");
        }
    } else {
        updateLabel("<font color='red'>Select business type</font>");
    }
//    ui->stackedWidgetHome->setCurrentWidget(ui->pageNewReg2);
}

void MainWindow::on_comboBoxBusinessType_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Individual"){
        ui->label_surname->setText("Sur Name*");
        ui->label_sex->setText("Sex*");
        ui->label_dob->setText("Date of Birth*");
    } else {
        ui->label_surname->setText("Sur Name");
        ui->label_sex->setText("Sex");
        ui->label_dob->setText("Date of Birth");
    }
}
