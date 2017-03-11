#include "stringconstant.h"

//Date format
const QString StringConstant::DATE_FORMAT = "yyyy-MM-dd";
const QString StringConstant::TIME_FORMAT = "hh:mm:ss";
const QString StringConstant::DATE_TIME_FORMAT = "yyyy-MM-dd hh:mm:ss";

//IP ADDRESS
const QString StringConstant::REGEX_IPV4 = "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$";

//ERROR MESSAGES
const QString StringConstant::ERROR_FORMAT_NOT_IPV4 = "Error: Not valid Ipv4.";
const QString StringConstant::ERROR_SERVER_UNABLE_TO_START = "Error: The server failed to start listening.";
const QString StringConstant::ERROR_SERVER_IS_ALREADY_RUNNING = "Error: The server is already running";
const QString StringConstant::ERROR_SERVER_NOT_EVEN_STARTED = "Error: The server isn't even running, failed to shut down.";
const QString StringConstant::ERROR_OUT_OF_RANGE_PORT = "Error: The port is out of range.";

//SERVER MESSAGES
const QString StringConstant::SERVER_RUNNING = "The server is running.";
const QString StringConstant::SERVER_NOT_RUNNING = "The server is not running.";
