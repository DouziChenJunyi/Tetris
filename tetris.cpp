#include "tetris.h"

Tetris::Tetris(int block_rowNum, int block_colNum, int pixelWid,
               int board_rowNum, int board_colNum)
{
    this->pixelWid = pixelWid;
    this->block_rowNum = block_rowNum;
    this->block_colNum = block_rowNum;
    this->board_rowNum = board_rowNum;
    this->board_colNum = board_colNum;

    recordFinished = QVector<QVector<int>>(board_rowNum, QVector<int>(board_colNum, 0));
    recordFalling = QVector<QVector<int>>(board_rowNum, QVector<int>(board_colNum, 0));
    score = 0;
    genRandomBlock();  // 仅仅是初始化出1个block
}

void Tetris::update_recordFinished()
{
    for (int i=0; i<block_rowNum; ++i)
    {
        for (int j=0; j<block_colNum; ++j)
        {
            if (block.blockPixel[i][j])
            {
                int pixel_board_rowOrdinate = block.board_rowOrdinate + i;
                int pixel_board_colOrdinate = block.board_colOrdinate + j;
                if (pixel_board_rowOrdinate>=0 && pixel_board_rowOrdinate<board_rowNum
                    && pixel_board_colOrdinate>=0 && pixel_board_colOrdinate<board_colNum)
                {
                    recordFinished[pixel_board_rowOrdinate][pixel_board_colOrdinate] = 1;
                }
            }
        }
    }
}

void Tetris::update_recordFalling()
{
    QVector<QVector<int>> tmp_recordFalling = QVector<QVector<int>>(board_rowNum, QVector<int>(board_colNum, 0));
    for (int i=0; i<block_rowNum; ++i)
    {
        for (int j=0; j<block_colNum; ++j)
        {
            if (block.blockPixel[i][j])
            {
                int pixel_board_rowOrdinate = block.board_rowOrdinate + i;  // board_rowOrdinate出了问题
                int pixel_board_colOrdinate = block.board_colOrdinate + j;
                qDebug() << "pixel_board_rowOrdinate" << pixel_board_rowOrdinate;
                qDebug() << "pixel_board_colOrdinate" << pixel_board_colOrdinate;


                if (pixel_board_rowOrdinate>=0 && pixel_board_rowOrdinate<board_rowNum
                    && pixel_board_colOrdinate>=0 && pixel_board_colOrdinate<board_colNum)
                {
                    tmp_recordFalling[pixel_board_rowOrdinate][pixel_board_colOrdinate] = 1;
                }
            }
        }
    }
    recordFalling = tmp_recordFalling;



}

// 每一次当前方块触底了，都对board每行进行判断，判断该行是否可以消除
void Tetris::tryClear()
{
    int cur_row = board_rowNum - 1; // 从最底层往上尝试消行
    while (cur_row >= 0) {
        while (canClear(cur_row)) { // 若当前行能一直消
            clearOneRow(cur_row);
            score += 10;
        }
        --cur_row;
    }

}

void Tetris::clearOneRow(int curRow)
{
    for (int i=curRow; i>0; --i)
    {
        recordFinished[i] = recordFinished[i-1];
    }
    recordFinished[0] = QVector<int>(board_colNum, 0);  // 首行置0
}

void Tetris::genRandomBlock()
{
    int randIdx = rand() % 4;
    switch (randIdx) {
    case 0:
        block = blockSquare(board_rowNum, board_colNum);
        break;
    case 1:
        block = blockLShape(board_rowNum, board_colNum);
        break;
    case 2:
        block = blockSShape(board_rowNum, board_colNum);
        break;
    case 3:
        block = blockTShape(board_rowNum, board_colNum);
        break;
    default:
        break;
    }
}

bool Tetris::canMoveDown()
{
    // 若触底，则不能往下移动
    bool blockLastRowHasPixel = false;
    for (int j=0; j<block_colNum; ++j)
    {
       if(block.blockPixel[block_rowNum-1][j])
       {
           blockLastRowHasPixel = true;
           break;
       }
    }
    int theMostBottomRow = block_rowNum-1;
    if (!blockLastRowHasPixel)   // 若block最底行为空行
    {
        theMostBottomRow -= 1;
    }
    if (block.board_rowOrdinate+theMostBottomRow == board_rowNum-1)
    {
       return false;
    }

    // 若未触底，尝试令其往下，看看是否会与其他块相撞 ———— 此处用到回退的思想
    QVector<QVector<int>> tmp_recordFalling =  QVector<QVector<int>>(board_rowNum, QVector<int>(board_colNum, 0));;
    for (int i=board_rowNum-1; i>0; --i)
    {
        tmp_recordFalling[i] = recordFalling[i-1];
    }

    for (int i=0; i<board_rowNum; ++i)
    {
        for (int j=0; j<board_colNum; ++j)
        {
            if (tmp_recordFalling[i][j] && recordFinished[i][j])
            {
                return false;  // 若会相撞
            }
        }
    }
    recordFalling = tmp_recordFalling;  // 若不会相撞，则保持更改

    return true;
}

bool Tetris::canRotate()
{
    if (canMoveDown())
    {
        // 考虑L-shape方块靠墙不能翻转
        if (block.board_colOrdinate>=0 && block.board_colOrdinate<board_colNum)
        {
            return true;
        }
    }
    return false;
}

bool Tetris::canMoveLeft()
{
    if (!canMoveDown())
        return false;

    // 若触壁，则不能往左移动
    bool blockLeftColHasPixel = false;
    for (int i=0; i<block_rowNum; ++i)
    {
       if(block.blockPixel[i][0])
       {
           blockLeftColHasPixel = true;
           break;
       }
    }

    int theMostLeftCol = 0;
    if (!blockLeftColHasPixel)  // 若block最左列为空列
    {
        theMostLeftCol = 1;
    }
    if (block.board_colOrdinate + theMostLeftCol == 0)  // 若最左列已经触壁，则无法继续向左
    {
        return false;
    }

    // 若未触壁，尝试令其往下，看看是否会与其他块相撞 ———— 此处用到回退的思想
    QVector<QVector<int>> tmp_recordFalling =  QVector<QVector<int>>(board_rowNum, QVector<int>(board_colNum, 0));;
    for (int j=0; j<block.block_colNum-1; ++j)
    {
        tmp_recordFalling[j] = recordFalling[j+1];
    }

    for (int i=0; i<board_rowNum; ++i)
    {
        for (int j=0; j<board_colNum; ++j)
        {
            if (tmp_recordFalling[i][j] && recordFinished[i][j])
            {
                return false;  // 若会相撞
            }
        }
    }
    recordFalling = tmp_recordFalling;  // 若不会相撞，则保持更改
    return true;
}


bool Tetris::canMoveRight()
{
    if (!canMoveDown())
        return false;

    // 若触壁，则不能往右移动
    bool blockRightColHasPixel = false;
    for (int i=0; i<3; ++i)
    {
      if(block.blockPixel[i][2])
      {
          blockRightColHasPixel = true;
          break;
      }
    }

    int theMostRightCol = block_colNum-1;
    if (!blockRightColHasPixel)  // 若block最右列为空列
    {
        theMostRightCol -= 1;
    }

    if (block.board_colOrdinate+theMostRightCol == board_colNum-1)  // 若block最右边列已经触壁，则无法继续向右
    {
        return false;
    }

    // 若未触壁，尝试令其往下，看看是否会与其他块相撞 ———— 此处用到回退的思想
    QVector<QVector<int>> tmp_recordFalling =  QVector<QVector<int>>(board_rowNum, QVector<int>(board_colNum, 0));;
    for (int j=block.block_colNum-1; j>0; --j)
    {
        tmp_recordFalling[j] = recordFalling[j-1];
    }

    for (int i=0; i<board_rowNum; ++i)
    {
        for (int j=0; j<board_colNum; ++j)
        {
            if (tmp_recordFalling[i][j] && recordFinished[i][j])
            {
                return false;  // 若会相撞
            }
        }
    }
    recordFalling = tmp_recordFalling;  // 若不会相撞，则保持更改
    return true;
}

bool Tetris::canClear(int cur_row)
{
    for (int j=0; j<board_colNum; ++j)
    {
        if (recordFinished[cur_row][j] == 0)  // 只要有1个缺口，就不能消除
        {
            return false;
        }
    }
    return true;
}

bool Tetris::isGameOver()
{

    for (int j=0; j<board_colNum; ++j)
    {
        if (recordFinished[0][j])
        {
            return true;
        }
    }
    return false;
}

