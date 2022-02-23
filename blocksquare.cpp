#include "blocksquare.h"

blockSquare::blockSquare()
{

}

blockSquare::blockSquare(int board_rowNum, int board_colNum)
{
    this->block_rowNum = 3;
    this->block_colNum = 3;
    this->board_rowNum = board_rowNum;
    this->board_colNum = board_colNum;
    initialize();
}

void blockSquare::initialize()
{

    board_rowOrdinate = -block_rowNum + 1;  // 初始时，board只露出block的最后1行
    board_colOrdinate = board_colNum / 2 - 1;

    for (int i=0; i< block_rowNum; ++i)
        blockPixel.push_back({1,1,1});
}

void blockSquare::rotate()  // 逆时针旋转
{
    int r_idx = 0;
    int c_n = 2;
    for (int c_idx = 0; c_idx < c_n; ++c_idx) {
        int tmp = blockPixel[r_idx][c_idx];
        blockPixel[r_idx][c_idx] = blockPixel[c_idx][2-r_idx];
        blockPixel[c_idx][2-r_idx] = blockPixel[2-r_idx][2-c_idx];
        blockPixel[2-r_idx][2-c_idx] = blockPixel[2-c_idx][r_idx];
        blockPixel[2-c_idx][r_idx] = tmp;
    }
}


