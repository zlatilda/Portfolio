#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDir databasePath;
    QString path = databasePath.currentPath()+"/media_libs.db";
    media_libs = QSqlDatabase::addDatabase("QSQLITE");
    media_libs.setDatabaseName(path);
    QSqlQuery qry;
    if(media_libs.open())
    {
        qry.prepare("create table media(id integer primary key, path text, name text, lib_name text)");
        qry.exec();
    }

    show_media_libs();

    ui->Add_media->setEnabled(false);
    ui->new_lib_input->setVisible(false);
    ui->save_new_lib->setVisible(false);
    ui->new_lib_add_cancel->setVisible(false);
    ui->search_media->setEnabled(false);
    ui->search_text_edit->setVisible(false);
    ui->search_cancel->setVisible(false);
    ui->search->setVisible(false);

    Player = new QMediaPlayer();

    ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_Seek_Backward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_Seek_Forward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    ui->save_new_lib->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->new_lib_add_cancel->setIcon(style()->standardIcon(QStyle::SP_DialogCancelButton));
    ui->search_cancel->setIcon(style()->standardIcon(QStyle::SP_DialogCancelButton));

    ui->horizontalSlider_Volume->setMinimum(0);
    ui->horizontalSlider_Volume->setMaximum(100);
    ui->horizontalSlider_Volume->setValue(30);

    Player->setVolume(ui->horizontalSlider_Volume->value());

    Playlist = new QMediaPlaylist(Player);

    trd = new Media_thread();
    connect(trd, SIGNAL(get_available_media(QString)), this, SLOT(on_get_available_media(QString)));
    trd->start();

    connect(Player, &QMediaPlayer::durationChanged, ui->horizontalSlider, &QSlider::setMaximum);
    connect(Player, &QMediaPlayer::positionChanged, ui->horizontalSlider, &QSlider::setValue);
    connect(ui->horizontalSlider, &QSlider::sliderMoved, Player, &QMediaPlayer::setPosition);

    connect(Player, &QMediaPlayer::currentMediaChanged, this, &MainWindow::onCurrentMusicIndexChanged);
    connect(ui->media_libs, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));

    ui->media_in_current_lib->setContextMenuPolicy(Qt::CustomContextMenu);

    QAction *pAddAction = new QAction("Add to playlist",this);
    QAction *pDelAction = new QAction("Delete from library",this);

    QObject::connect(ui->media_in_current_lib, &QTableWidget::customContextMenuRequested, [=](const QPoint& pos)
    {
        media_index = ui->media_in_current_lib->indexAt(pos);

        qDebug() << media_index << "      "  << ui->media_in_current_lib->indexAt(pos);

        QMenu rightClickMenu(ui->media_in_current_lib);
        rightClickMenu.addAction(pAddAction);
        rightClickMenu.addAction(pDelAction);
        rightClickMenu.exec(ui->media_in_current_lib->viewport()->mapToGlobal(pos));

     });

    connect(pAddAction, &QAction::triggered, [&](){qDebug() << "add to playlist"; add_from_lib_to_playlist();});
    connect(pDelAction, &QAction::triggered, [&](){qDebug() << "Delete from library";});

    ui->availabe_media->setContextMenuPolicy(Qt::CustomContextMenu);
    QAction *pAddMedia= new QAction("Add to playlist",this);
    QObject::connect(ui->availabe_media, &QListWidget::customContextMenuRequested, [=](const QPoint& pos)
    {
        media_index = ui->availabe_media->indexAt(pos);

        qDebug() << media_index << "      "  << ui->availabe_media->indexAt(pos);

        QMenu rightClickMenu(ui->media_in_current_lib);
        rightClickMenu.addAction(pAddMedia);
        rightClickMenu.exec(ui->availabe_media->viewport()->mapToGlobal(pos));
     });

#ifdef _WIN64
     connect(pAddMedia, &QAction::triggered, [&](){qDebug() << "add to playlist"; add_to_playlist(media_index.data().toString());});

#elif __linux
     connect(pAddMedia, &QAction::triggered, [&](){qDebug() << media_index.data().toString().remove(0, 1); add_to_playlist(media_index.data().toString().remove(0, 1));});
#endif
}


MainWindow::~MainWindow()
{
    trd->exit();
    delete Player;
    delete Video;
    delete Audio;
    delete Playlist;
    delete ui;
}


void MainWindow::onTableClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        media_lib_index = index;
        QString cellText = index.data().toString();
        show_media_in_curr_lib(cellText);
        ui->Add_media->setEnabled(true);
        ui->search_media->setEnabled(true);
    }
}

void MainWindow::onCurrentMusicIndexChanged()
{
    if(Playlist->currentIndex() <= Playlist->mediaCount())
        ui->play_list->item(Playlist->currentIndex())->setSelected(true);
}

void MainWindow::on_actionOpen_video_triggered()
{
    Playlist->clear();
    ui->play_list->clear();
    Play_list_index = 0;
    Play_list_size = 0;
    QFileInfo* fi;
    QStringList filenames = QFileDialog::getOpenFileNames(this, "Open a File","","Video File(*.mp4)");
    for(const QString & filename: filenames){
        Playlist->addMedia(QMediaContent(QUrl::fromLocalFile(filename)));
        fi = new QFileInfo(QUrl::fromLocalFile(filename).toString());
        ui->play_list->addItem(fi->fileName());
        Play_list_size++;
    }

    Video = new QVideoWidget();
    Video->setGeometry(5, 5, ui->groupBox_Video->width()-10, ui->groupBox_Video->height()-10);
    Video->setParent(ui->groupBox_Video);
    Player->setVideoOutput(Video);
    Player->setPlaylist(Playlist);
    Video->setVisible(true);
    Video->show();

    ui->play_list->item(Play_list_index)->setSelected(true);
}

void MainWindow::on_horizontalSlider_Duration_valueChanged(int value)
{
    Player->setPosition(value*1000);
}

void MainWindow::on_pushButton_Play_Pause_clicked()
{
    if(is_Pause == true)
    {
        is_Pause = false;
        Player->play();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else
    {
        is_Pause = true;
        Player->pause();
        ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

void MainWindow::on_pushButton_Stop_clicked()
{
    Player->stop();
    is_Pause = true;
    ui->pushButton_Play_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
}

void MainWindow::on_pushButton_Volume_clicked()
{
    if(is_Muted == false)
    {
        is_Muted = true;
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        Player->setMuted(true);
    }
    else
    {
        is_Muted = false;
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        Player->setMuted(false);

    }
}

void MainWindow::on_horizontalSlider_Volume_valueChanged(int value)
{
    Player->setVolume(value);
}


void MainWindow::on_actionOpen_music_triggered()
{   
    Playlist->clear();
    ui->play_list->clear();
    Play_list_index = 0;
    Play_list_size = 0;
    QFileInfo* fi;
    QStringList filenames = QFileDialog::getOpenFileNames(this, "Open a File","","Music File(*.mp3)");
    for(const QString & filename: filenames){
        Playlist->addMedia(QMediaContent(QUrl::fromLocalFile(filename)));
        fi = new QFileInfo(QUrl::fromLocalFile(filename).toString());
        ui->play_list->addItem(fi->fileName());
        Play_list_size++;
    }

    Audio = new QAudioOutput();
    Player->setPlaylist(Playlist);

    ui->play_list->item(Play_list_index)->setSelected(true);
}

void MainWindow::on_pushButton_Seek_Forward_clicked()
{
    Playlist->next();

    Play_list_index = (Play_list_index+1) % Play_list_size;
    //ui->play_list->item(Play_list_index)->setSelected(true);
    ui->play_list->item(Playlist->currentIndex())->setSelected(true);
    std::cout << Playlist->currentIndex() << " " << Playlist->mediaCount();
}


void MainWindow::on_pushButton_Seek_Backward_clicked()
{
    Playlist->previous();
    ui->play_list->item(Playlist->currentIndex())->setSelected(true);
}

void MainWindow::on_Add_media_clicked()
{
    QFileInfo* fi;
    QString lib_name;
    if (media_lib_index.isValid())
        lib_name = media_lib_index.data().toString();

    QString path = QFileDialog::getOpenFileName(this, "Open a File","","Music or Video File(*.*)");
    QString id = QString::number(rand());
    fi = new QFileInfo(QUrl::fromLocalFile(path).toString());
    QString name = fi->fileName();

    if(name != "")
    {
        QSqlQuery qry;
        if(media_libs.open())
        {
            qry.prepare("insert into media(id, path, name, lib_name) values(:id, :path, :name, :lib_name)");
            qry.bindValue(":id", id);
            qry.bindValue(":path", path);
            qry.bindValue(":name", name);
            qry.bindValue(":lib_name", lib_name);
            qry.exec();
        }

        media_libs.close();
    }
    show_media_in_curr_lib(lib_name);
}

void MainWindow::show_media_libs()
{
    media_libs.open();
    QSqlQuery qry;
    QSqlQueryModel* modal = new QSqlQueryModel();
    qry.prepare("select distinct lib_name from media");
    qry.exec();

    modal->setQuery(qry);

    ui->media_libs->setModel(modal);

    media_libs.close();
}

void MainWindow::show_media_in_curr_lib(QString cellText)
{
    media_libs.open();
    QSqlQuery qry;
    QSqlQueryModel* modal = new QSqlQueryModel();
    qry.prepare("select name from media where lib_name = :lbnm");
    qry.bindValue(":lbnm", cellText);
    qry.exec();

    modal->setQuery(qry);

    ui->media_in_current_lib->setModel(modal);

    media_libs.close();
}

void MainWindow::on_Add_library_clicked()
{
    ui->new_lib_input->setVisible(true);
    ui->save_new_lib->setVisible(true);
    ui->new_lib_add_cancel->setVisible(true);
    ui->Add_library->setEnabled(false);
}


void MainWindow::on_save_new_lib_clicked()
{
    QFileInfo* fi;
    QString lib_name = ui->new_lib_input->toPlainText();

    if(lib_name != "")
    {
        QString path = QFileDialog::getOpenFileName(this, "Open a File","","Music or Video File(*.*)");
        QString id = QString::number(rand());
        fi = new QFileInfo(QUrl::fromLocalFile(path).toString());
        QString name = fi->fileName();

        QSqlQuery qry;
        if(media_libs.open())
        {
            qry.prepare("insert into media(id, path, name, lib_name) values(:id, :path, :name, :lib_name)");
            qry.bindValue(":id", id);
            qry.bindValue(":path", path);
            qry.bindValue(":name", name);
            qry.bindValue(":lib_name", lib_name);
            qry.exec();
        }

        ui->new_lib_input->clear();
        ui->new_lib_input->setVisible(false);
        ui->save_new_lib->setVisible(false);
        ui->new_lib_add_cancel->setVisible(false);
    }
    show_media_libs();
    ui->Add_library->setEnabled(true);
    media_libs.close();
}


void MainWindow::on_new_lib_add_cancel_clicked()
{
    ui->new_lib_input->clear();
    ui->new_lib_input->setVisible(false);
    ui->save_new_lib->setVisible(false);
    ui->new_lib_add_cancel->setVisible(false);
    ui->Add_library->setEnabled(true);
}

void MainWindow::add_to_playlist(QString qry_res)
{
    Playlist->addMedia(QMediaContent(QUrl::fromLocalFile(qry_res)));
    QFileInfo* fi = new QFileInfo(QUrl::fromLocalFile(qry_res).toString());
    ui->play_list->addItem(fi->fileName());
    Play_list_size++;
    Player->setPlaylist(Playlist);

    if((qry_res.toStdString()).substr((qry_res.toStdString()).find_last_of(".") + 1) == "mp4")
    {
        Video = new QVideoWidget();
        Video->setGeometry(5, 5, ui->groupBox_Video->width()-10, ui->groupBox_Video->height()-10);
        Video->setParent(ui->groupBox_Video);
        Player->setVideoOutput(Video);
        Video->setVisible(true);
        Video->show();
    }
}


void MainWindow::add_from_lib_to_playlist()
{
    QString qry_res;
    QSqlQuery qry;

    qDebug() << media_index.data().toString();

    if(media_libs.open())
    {
        qry.prepare("select distinct path from media where name = :nm");
        qry.bindValue(":nm", media_index.data().toString());
        if(qry.exec())
            qDebug() << "qry executed";
    }
    while(qry.next())
        qry_res = qry.value(0).toString();
    qDebug() << qry_res;
    media_libs.close();

    add_to_playlist(qry_res);
}


void MainWindow::on_get_available_media(QString file)
{
    ui->availabe_media->addItem(file);
}

void MainWindow::on_search_media_clicked()
{
    ui->search_text_edit->setVisible(true);
    ui->search_cancel->setVisible(true);
    ui->search->setVisible(true);
    ui->search_media->setEnabled(false);
}


void MainWindow::on_search_cancel_clicked()
{
    ui->search_text_edit->setVisible(false);
    ui->search_text_edit->clear();
    ui->search_cancel->setVisible(false);
    ui->search->setVisible(false);
    ui->search_media->setEnabled(true);
    show_media_in_curr_lib(media_lib_index.data().toString());
}


void MainWindow::on_search_clicked()
{
    QSqlQuery qry;
    if(media_libs.open())
    {
        qry.prepare("select distinct name from media where name like '%"%ui->search_text_edit->toPlainText()%"%' and lib_name = :lbnm");
        qry.bindValue(":lbnm", media_lib_index.data().toString());
        qry.exec();
    }

    QSqlQueryModel* modal = new QSqlQueryModel();
    modal->setQuery(qry);

    ui->media_in_current_lib->setModel(modal);

    media_libs.close();

}

