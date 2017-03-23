#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H

#include <QObject>
#include <QMap>

class MessageProcessor : public QObject
{
    Q_OBJECT
public:
    MessageProcessor(QObject *parent = NULL);
    void process(QString message);
private:
    QMap<int, QString> commandList;

    int translate(QString message);
    void addCommands();
signals:
    void signalAnswerPing();
};

#endif // MESSAGEPROCESSOR_H
