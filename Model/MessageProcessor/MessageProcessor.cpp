#include "Model/MessageProcessor/MessageProcessor.h"

MessageProcessor::MessageProcessor(QObject *parent) : QObject(parent)
{
    addCommands();
}

void MessageProcessor::addCommands()
{
    commandList.insert(1, QString("REQ_PING"));
}

void MessageProcessor::process(QString message)
{
    int test = translate(message);
    switch (test) {
    case 1:
        emit signalAnswerPing();
        break;
    default:
        break;
    }
}

int MessageProcessor::translate(QString message)
{
    return commandList.key(message);
}
