#ifndef AJCHAPAR_H
#define AJCHAPAR_H

#include <QObject>
#include "aj_exec.h"
#include "aj_channel.h"

class AjChapar : public QObject
{
    Q_OBJECT
public:
    explicit AjChapar(QString path, QStringList arguments=QStringList(),
                      QObject *parent = nullptr);
    AjChapar(QStringList paths, QObject *parent = nullptr);
    int hasNamedPipe();

signals:
    void startChannel();

private slots:
    void testTimeout();
    void execNPipe(QString np_name, QStringList arguments);

private:
    void execScript(QString path, QStringList arguments=QStringList());

    AjTreeParser *tree_parser;
    QVector<AjApp *> apps;
    QVector<AjApp *> nps;
    AjChannel *channel;
    QThread *channel_thread;
    QTimer *test_timer;
};

#endif // AJCHAPAR_H
