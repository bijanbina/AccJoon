#ifndef AJCHANNEL_H
#define AJCHANNEL_H

#include <QObject>
#include <QTimer>
#include <Windows.h>

#define PIPE_PATH       "\\\\.\\pipe\\com_binaee_rebound"
#define AJ_NP_SEPARATOR ","
#define BUFFER_SIZE (1024 * 8)

class AjChannel : public QObject
{
    Q_OBJECT
public:
    explicit AjChannel(QObject *parent = nullptr);
    void testTimeout();

public slots:
    void ListenPipe();

signals:
    void npReceived(QString np_name, QStringList fields);

private:
    void createPipe();
    void processLine(QString line);

    HANDLE hPipe;
};

#endif // AJCHANNEL_H
