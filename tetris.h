#ifndef TETRIS_H
#define TETRIS_H

#include<QVector>
#include<QQueue>
#include<QTimer>
#include<QPainter>
#include<QPaintEvent>
#include "blocksquare.h"
#include "blocklshape.h"
#include "blocksshape.h"
#include "blocktshape.h"

#include <QDebug>

class Tetris
{
public:
    Tetris();
    Tetris(int block_rowNum, int block_colNum, int pixelWid, int board_rowNum, int board_colNum);
    int board_rowNum, board_colNum;
    int block_rowNum, block_colNum;
    int pixelWid;
    int score;

    QVector<QVector<int>> recordFinished;
    QVector<QVector<int>> recordFalling;
    blockSquare block;

    void update_recordFinished();
    void update_recordFalling();
    void genRandomBlock();
    void tryClear();
    bool canMoveDown();
    bool canRotate();
    bool canMoveLeft();
    bool canMoveRight();
    bool isGameOver();


private:

    void clearOneRow(int curRow);
    bool canClear(int curRow);
};

#endif // TETRIS_H
