#ifndef BLOCKSQUARE_H
#define BLOCKSQUARE_H
#include<QVector>


class blockSquare
{
public:
    blockSquare();
    blockSquare(int board_rowNum, int board_colNum);
    QVector<QVector<int>> blockPixel;
    virtual void initialize();
    void rotate();
    void unrotate();
    int board_rowOrdinate, board_colOrdinate;  // 以第1行为坐标行
    int board_rowNum, board_colNum;
    int block_rowNum, block_colNum;
};

#endif // BLOCKSQUARE_H
