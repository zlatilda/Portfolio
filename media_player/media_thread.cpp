#include "media_thread.h"
#include <QtCore>
#include <functional>
#include <dirent.h>
#include <string>
#include <stdio.h>

Media_thread::Media_thread(QObject *parent) : QThread(parent)
{

}

void Media_thread::run()
{
#ifdef _WIN64

    get_available_media_windows();

#elif __linux
    get_available_media_linux("/home");
#endif
}

void Media_thread::get_available_media_windows()
{
    QDirIterator it("C://", QStringList() << "*.mp3", QDir::Files, QDirIterator::Subdirectories);
        QDirIterator it1("C://", QStringList() << "*.mp4", QDir::Files, QDirIterator::Subdirectories);

        while (it.hasNext() || it1.hasNext())
        {
            if(it.next()!=NULL)
            {
                qDebug() << it.next();
                emit get_available_media(it.next());
            }
            if(it1.next()!=NULL)
            {
                qDebug() << it1.next();
                emit get_available_media(it1.next());
            }
        }
}

void Media_thread::get_available_media_linux(const char* dirname)
{
    DIR* dir = opendir(dirname);
    if (dir == NULL) {
        return;
    }

    //printf("Reading files in: %s\n", dirname);
    std::string s;

    struct dirent* entity;
    entity = readdir(dir);
    while (entity != NULL) {
        //printf("%hhd %s/%s\n", entity->d_type, dirname, entity->d_name);
        s = entity->d_type;
        std::string str(dirname);
        s += str + "/";
        s += entity->d_name;
        QFileInfo fi(QString::fromStdString(s));
        QString ext = fi.suffix();

        if(ext == "mp4" || ext == "mp3")
            emit get_available_media(QString::fromStdString(s));

        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            char path[100] = { 0 };
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);
            get_available_media_linux(path);
        }
        entity = readdir(dir);
    }

    closedir(dir);
}

