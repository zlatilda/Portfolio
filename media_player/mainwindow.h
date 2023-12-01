#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QtMultimedia>
#include <QtMultimediaWidgets/QtMultimediaWidgets>
#include <QtMultimedia/QMediaObject>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include <QMediaMetaData>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QSqlError>
#include <QFileInfo>
#include <string>
#include "media_thread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Media_thread* trd;
    //static void get_available_media();

public slots:
    void on_get_available_media(QString file);

private slots:

    void on_actionOpen_video_triggered();

    void on_horizontalSlider_Duration_valueChanged(int value);

    void on_pushButton_Play_Pause_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Volume_clicked();

    void on_horizontalSlider_Volume_valueChanged(int value);

    void on_actionOpen_music_triggered();

    void on_pushButton_Seek_Forward_clicked();

    void on_pushButton_Seek_Backward_clicked();

    void on_Add_media_clicked();

    void onTableClicked(const QModelIndex &index);

    void on_Add_library_clicked();

    void on_save_new_lib_clicked();

    void on_new_lib_add_cancel_clicked();

    void on_search_media_clicked();

    void on_search_cancel_clicked();

    void on_search_clicked();

private:
    Ui::MainWindow* ui;
    QMediaPlayer* Player;
    QVideoWidget* Video;
    QAudioOutput* Audio;
    bool is_Pause = true;
    bool is_Muted = false;
    QMediaPlaylist * Playlist;
    int Play_list_index;
    int Play_list_size;
    QSqlDatabase media_libs;
    QModelIndex media_lib_index;
    QModelIndex media_index;

    void updateDuration(quint64 duration);
    void onCurrentMusicIndexChanged();
    void show_media_libs();
    void show_media_in_curr_lib(QString cellText);
    void add_from_lib_to_playlist();
    void add_to_playlist(QString qry_res);
};
#endif // MAINWINDOW_H
