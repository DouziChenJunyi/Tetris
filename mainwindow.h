#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include "tetris.h"

#include "wall.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    friend class Wall;

    QLabel *lbl_score_text, *lbl_score_num;
    QPushButton *start_btn;
    QPainter *painter;

    Wall *wall;
    Tetris *tetris;
    QTimer *timer;
    int time;
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent* event) override;
    void drawWall();
    void drawRecordFinished();
    void drawRecordFalling();
    void startGame();

public slots:
    void autoMove();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
