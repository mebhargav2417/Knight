#ifndef CONSTANTS_H
#define CONSTANTS_H

#include<QString>


class Constants
{
public:
    Constants();

    int entryType;  // 0 for nothing, 1 for sales, 2 for purchases, 3 for net profit, 4 for return status, 5 for blank fields
    int registrationType; // 0 for nothing, 1 for registration, 2 for update or edit

    const int SUCCESS = 100;
    const int ERROR = 101;
    const int EXCEPTION = 102;

    const QString dateFormat = "yyyy-MM-dd";
};

#endif // CONSTANTS_H
