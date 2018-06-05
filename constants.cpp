#include "constants.h"
#include <QRegExp>
#include <QDebug>

Constants::Constants()
{

}

bool Constants::checkMail(QString mailData)
{
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    return mailREX.exactMatch(mailData);
}

QString Constants::reverseString(QString actual)
{
    QString reverse = actual;
    int j = actual.length();
    for(int i=0; i<actual.length(); i++){
        j--;
        reverse[i] = actual[j];
    }
    return reverse;
}

QString Constants::forDateFormat(QString actual)
{
    QStringList dates = actual.split("-");
    return dates[2]+"-"+dates[0]+"-"+dates[1];
}
