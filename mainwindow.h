#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include<QNetworkReply>
#include<forserverconnection.h>
#include<constants.h>

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

    void on_pushButtonLogout_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_listWidget_2_itemClicked(QListWidgetItem *item);


    void slotRequestFinished(QNetworkReply *);

    void on_buttonRegistrationPage1_clicked();

    void on_btnPreviousRegPage2_clicked();

    void on_btnNextRegPage2_clicked();

    void on_btnPreviousNewPage3_clicked();

    void on_pushButtonFileNewentry_clicked();

private:
    Ui::MainWindow *ui;

    void setGui();

    void makeConnection(QString,QJsonObject);

public:
    void setGuiForRegistration();
    void setGuiForProfileEdit();
    void setGuiForProfileDelete();
    void setGuiForNewEntry();
    void setGuiForEditEntry();
    void setGuiForViewEntry();
    void setGuiForMainPage();


    QStringList listYesNo;
    QStringList listBusinessType;
    QStringList listGender;
    QStringList listBankAcc;
};

#endif // MAINWINDOW_H
