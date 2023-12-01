#include "mainwindow.h"
#include <thread>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //std::thread t1(MainWindow::get_available_media);
    w.show();
    return a.exec();

    //t1.join();
}
