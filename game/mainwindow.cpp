#include "mainwindow.h"
#include "ui_mainwindow.h"

QVector<QVector<QLabel*>> labels;
QVector<QVector<QFrame*>> frames;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(time(0));
    ui->setupUi(this);
}

void MainWindow::showEvent( QShowEvent* event ) {
    QWidget::showEvent( event );
    obj.new_game();
    Form_matrix();
    Print_matrix();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Form_matrix()
{
    QVector<QLabel*> temp;
    QVector<QFrame*> f_temp;
    temp.push_back(ui->label_1_1);  f_temp.push_back(ui->frame_1_1);
    temp.push_back(ui->label_1_2);  f_temp.push_back(ui->frame_1_2);
    temp.push_back(ui->label_1_3);  f_temp.push_back(ui->frame_1_3);
    temp.push_back(ui->label_1_4);  f_temp.push_back(ui->frame_1_4);
    labels.push_back(temp);         frames.push_back(f_temp);
    temp.clear();                   f_temp.clear();
    temp.push_back(ui->label_2_1);  f_temp.push_back(ui->frame_2_1);
    temp.push_back(ui->label_2_2);  f_temp.push_back(ui->frame_2_2);
    temp.push_back(ui->label_2_3);  f_temp.push_back(ui->frame_2_3);
    temp.push_back(ui->label_2_4);  f_temp.push_back(ui->frame_2_4);
    labels.push_back(temp);         frames.push_back(f_temp);
    temp.clear();                   f_temp.clear();
    temp.push_back(ui->label_3_1);  f_temp.push_back(ui->frame_3_1);
    temp.push_back(ui->label_3_2);  f_temp.push_back(ui->frame_3_2);
    temp.push_back(ui->label_3_3);  f_temp.push_back(ui->frame_3_3);
    temp.push_back(ui->label_3_4);  f_temp.push_back(ui->frame_3_4);
    labels.push_back(temp);         frames.push_back(f_temp);
    temp.clear();                   f_temp.clear();
    temp.push_back(ui->label_4_1);  f_temp.push_back(ui->frame_4_1);
    temp.push_back(ui->label_4_2);  f_temp.push_back(ui->frame_4_2);
    temp.push_back(ui->label_4_3);  f_temp.push_back(ui->frame_4_3);
    temp.push_back(ui->label_4_4);  f_temp.push_back(ui->frame_4_4);
    labels.push_back(temp);         frames.push_back(f_temp);
}

void MainWindow::on_pushButton_new_game_clicked()
{
   Clear_screen();

   obj.new_game();

   Form_matrix();

   Print_matrix();
}

void MainWindow::Print_matrix()
{
    QString color;
    int b = 230, g = 230;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(obj.get_board_value(i,j) != 0)
            {
                if(obj.get_board_value(i,j) == 2)
                    frames[i][j]->setStyleSheet(".QFrame { background-color:rgb(245, 245, 245); }");
                 if(obj.get_board_value(i,j) >= 4)
                 {
                     if(b - 5*obj.get_board_value(i,j) >= 0)
                     {
                         color = "rgb(245, 245," % QString::number(b - 5*obj.get_board_value(i,j)) % " );";
                     }
                     else if(g - 0.5*obj.get_board_value(i,j) >= 0)
                     {
                          color = "rgb(245," % QString::number(g - 0.5*obj.get_board_value(i,j)) % ", 100);";
                     }
                     else
                         color = "rgb(245, 90, 50);";

                     frames[i][j]->setStyleSheet(".QFrame { background-color:" % color % "}");
                 }

                labels[i][j]->setText(QString::number(obj.get_board_value(i,j)));
                ui->score_number_label->setText(QString::number(obj.get_score()));
            }
        }
    }
}

void MainWindow::Clear_screen()
{
    if(!(frames.empty() && labels.empty()))
    {
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                frames[i][j]->setStyleSheet(".QFrame { background-color:rgb(200, 200, 200); }");
                labels[i][j]->setText("");
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int direction = -1;

    if(event->key() == Qt::Key_S)
    {
        direction = 0;
    }

    else if(event->key() == Qt::Key_D)
    {
        direction = 1;
    }

    else if(event->key() == Qt::Key_W)
    {
        direction = 2;
    }

    else if(event->key() == Qt::Key_A)
    {
        direction = 3;
    }
    else if(event->key() == Qt::Key_Z)
    {
        Clear_screen();
        obj.restore_to_prev_move();
        Print_matrix();
    }

    if(direction != -1)
    {
        Clear_screen();
        obj.apply_move(direction);
        Print_matrix();
    }
}

void MainWindow::on_actionQuit_triggered()
{
    QCoreApplication::exit();
}

