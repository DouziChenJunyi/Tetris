#include "blocklshape.h"

blockLShape::blockLShape(int board_rowNum, int board_colNum)
{
    this->block_rowNum = 3;
    this->block_colNum = 3;
    this->board_rowNum = board_rowNum;
    this->board_colNum = board_colNum;
    initialize();
}

void blockLShape::initialize()
{
    board_rowOrdinate = -block_rowNum + 1;
    board_colOrdinate = board_colNum / 2 - 1 ;

    blockPixel.push_back({1,0,0});
    blockPixel.push_back({1,0,0});
    blockPixel.push_back({1,1,0});
}
