#ifndef STRINGCONSTANT_H
#define STRINGCONSTANT_H

#include <QString>

class StringConstant
{
public:

    //DATE
    static const QString DATE_FORMAT;
    static const QString TIME_FORMAT;
    static const QString DATE_TIME_FORMAT;

    //IP ADDRESS
    static const QString REGEX_IPV4;

    //ERROR MESSAGES
    static const QString ERROR_FORMAT_NOT_IPV4;
    static const QString ERROR_SERVER_UNABLE_TO_START;
    static const QString ERROR_OUT_OF_RANGE_PORT;

};

#endif // STRINGCONSTANT_H
