#ifndef MEDIA_THREAD_H
#define MEDIA_THREAD_H

#include <QThread>
#include <QObject>

class Media_thread : public QThread
{
    Q_OBJECT
public:
    explicit Media_thread(QObject *parent = nullptr);
    void run();
    void get_available_media_linux(const char* dirname);
    void get_available_media_windows();

signals:

    void get_available_media(QString file);
};

#endif // MEDIA_THREAD_H
