#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QtGui>
#include <QtCore>
#include <QListWidgetItem>
#include <QNetworkReply>
#include <forserverconnection.h>
#include <constants.h>
#include <QSettings>
#include <QLabel>
#include <QJsonObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    Constants *constants;

private slots:
    void on_pushButtonLogin_clicked();
    void slotRequestFinished(QNetworkReply *);
    void on_buttonRegistrationPage1_clicked();
    void on_btnPreviousRegPage2_clicked();
    void on_btnNextRegPage2_clicked();
    void on_btnPreviousNewPage3_clicked();
    void on_pushButtonFileNewentry_clicked();
    void on_pushButtonAdd_clicked();
    void on_pushButtonRegNewEMp_clicked();
    void on_pushButton_clicked();
    void on_listWidgetHomeMenu_itemClicked(QListWidgetItem *item);

    void on_comboBoxBusinessType_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    void setGui();
    void makeConnection(const QString,QJsonObject);
    void updateLabel(const QString);

public:
    void setGuiForRegistration();
    void setGuiForProfileEdit();
    void setGuiForProfileDelete();
    void setGuiForNewEntry();
    void setGuiForEditEntry();
    void setGuiForViewEntry();
    void setGuiForMainPage();
    void parseResponse(int,const QString,QByteArray);
    void validateRegPage1();


    QStringList listYesNo;
    QStringList listBusinessType;
    QStringList listGender;
    QStringList listBankAcc;
    QStringList listRole;
    static QString callType;
};

#endif // MAINWINDOW_H
