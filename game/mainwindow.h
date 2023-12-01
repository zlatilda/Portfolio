#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QtGui>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Print_matrix();
    void Clear_screen();
    void Form_matrix();

private slots:
    void on_pushButton_new_game_clicked();
    void keyPressEvent(QKeyEvent *event) override;
    void on_actionQuit_triggered();
    void showEvent( QShowEvent* event ) override;

private:
    Ui::MainWindow *ui;
    game obj;
};
#endif // MAINWINDOW_H
