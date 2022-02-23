#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 此句的意思是，启动程序后，就将鼠标与键盘的焦点置于当前窗口
    setFocusPolicy(Qt::StrongFocus);
    this->setWindowTitle("俄罗斯方块");


    // 设置不可拉伸窗口
    QSizePolicy policy_00_Fixed_Fixed;
    policy_00_Fixed_Fixed.setHorizontalStretch(0);
    policy_00_Fixed_Fixed.setVerticalStretch(0);
    policy_00_Fixed_Fixed.setHorizontalPolicy(QSizePolicy::Fixed);
    policy_00_Fixed_Fixed.setVerticalPolicy(QSizePolicy::Fixed);
    this->setMinimumSize(950, 700);


    lbl_score_text = new QLabel(this);
    lbl_score_text->setObjectName(QStringLiteral("lbl_score_text"));
    lbl_score_text->setSizePolicy(policy_00_Fixed_Fixed);
    lbl_score_text->move(700, 200);
    lbl_score_text->setText("score：");
    lbl_score_text->setFont(QFont("Microsoft Yahei",18,60));

    lbl_score_num = new QLabel(this);
    lbl_score_num->setObjectName(QStringLiteral("lbl_score_num"));
    lbl_score_num->setSizePolicy(policy_00_Fixed_Fixed);
    lbl_score_num->move(760, 200);
    lbl_score_num->setText("0");
    lbl_score_num->setFont(QFont("Microsoft Yahei",18,60));

    start_btn = new QPushButton(this);
    start_btn->setObjectName(QStringLiteral("start_btn"));
    start_btn->setSizePolicy(policy_00_Fixed_Fixed);
    start_btn->move(695, 250);
    start_btn->resize(100, 50);
    start_btn->setText("开始");
    start_btn->setFont(QFont("Microsoft Yahei",15,60));

    connect(start_btn,  &QPushButton::clicked, this, [=]{
        qDebug() << "click the start button";
        startGame();
    });

    int wallPixelNum = 1;
    int pixelWid = 10;
    int board_rowNum = 50, board_colNum = 30;
    int block_rowNum = 3, block_colNum = 3;
    wall= new Wall(wallPixelNum, pixelWid, board_rowNum, board_colNum);
    tetris = new Tetris(block_rowNum, block_colNum, pixelWid, board_rowNum, board_colNum);

    time = 300;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(autoMove()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::autoMove()
{
    qDebug() << "autoMove";
    if(tetris->isGameOver())
    {
        timer->stop();
        QMessageBox::information(this, "game over", "game over");
    }
    if (tetris->canMoveDown())  // 若能继续向下移动方块
    {
        tetris->block.board_rowOrdinate += 1;
        tetris->update_recordFalling();
        update();
    }
    else {  // 若不能继续向下移动方块
        tetris->update_recordFinished();
        update();   // 调用画图程序
        tetris->tryClear(); // 尝试清行
        this->lbl_score_num->setText(QString::number(tetris->score));
        tetris->genRandomBlock();  // 生成新的方块
        tetris->update_recordFalling();  // 更新记录
        update();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "event->key()";
    switch (event->key()) {
    case Qt::Key_Left:
        if (tetris->canMoveLeft())
        {
            tetris->block.board_colOrdinate -= 1;
            qDebug() << "tetris->block.board_colOrdinate:" << tetris->block.board_colOrdinate;
            tetris->update_recordFalling();
            update();
        }
        break;
    case Qt::Key_Right:
        if (tetris->canMoveRight())
        {
            tetris->block.board_colOrdinate += 1;
            tetris->update_recordFalling();
            update();
        }
        break;
    case Qt::Key_Down:
        if (tetris->canMoveDown())
        {
            tetris->block.board_rowOrdinate += 1;
            tetris->update_recordFalling();
            update();
        }
        break;
    case Qt::Key_Up:
        if (tetris->canRotate())
        {
            tetris->block.rotate();
            tetris->update_recordFalling();
            update();
        }
        break;
    default:
        break;
    }
}


void MainWindow::paintEvent(QPaintEvent *)
{
    qDebug() << "Once start the programe will call the paintEvent Function.";
    painter = new QPainter;
    drawWall();
    drawRecordFalling();
    drawRecordFinished();
}


void MainWindow::drawWall()  // 画图的时候x轴方向向右平移了10，y轴方向向下平移了100
{
    painter->begin(this);
    painter->setBrush(QBrush(Qt::Dense7Pattern));
    //画上下两行墙
    for(int i=0;i< wall->board_colNum+2*wall->wallPixelNum;i++)
    {
        painter->drawRect(10 + i*wall->pixelWid, 100,
                          wall->pixelWid, wall->pixelWid);
        painter->drawRect(10 + i*wall->pixelWid,100 + wall->pixelWid*(wall->board_rowNum+1),
                          wall->pixelWid, wall->pixelWid);
    }

    //画左右两列墙
    for(int i=0;i<wall->board_rowNum+2*wall->wallPixelNum;i++)
    {
        painter->drawRect(10, 100 + i*wall->pixelWid,
                          wall->pixelWid,wall->pixelWid);
        painter->drawRect(10+wall->pixelWid*(wall->board_colNum+1), 100 + i*wall->pixelWid,
                          wall->pixelWid,wall->pixelWid);
    }

    painter->end();
}

void MainWindow::drawRecordFinished()  // 画图的时候x轴方向向右平移了10，y轴方向向下平移了100
{
    painter->begin(this);
    painter->setBrush(QBrush(Qt::gray));
    for(int j=0; j<tetris->board_colNum; ++j)
    {
        for(int i=0; i<tetris->board_rowNum; ++i)
        {
            if(tetris->recordFinished[i][j])
            {
                painter->drawRect(10+(j+wall->wallPixelNum)*wall->pixelWid,
                                  100+(i+wall->wallPixelNum)*wall->pixelWid,
                                  wall->pixelWid, wall->pixelWid);
            }
        }
    }
    painter->end();
}

void MainWindow::drawRecordFalling()  // 画图的时候x轴方向向右平移了10，y轴方向向下平移了100
{
    painter->begin(this);
    painter->setBrush(QBrush(Qt::gray));
    for(int j=0; j<tetris->board_colNum; ++j)
    {
        for(int i=0; i<tetris->board_rowNum; ++i)
        {
            if(tetris->recordFalling[i][j])
            {
                painter->drawRect(10+(j+wall->wallPixelNum)*wall->pixelWid,
                                  100+(i+wall->wallPixelNum)*wall->pixelWid,
                                  wall->pixelWid, wall->pixelWid);
            }
        }
    }
    painter->end();
}

void MainWindow::startGame()
{
    qDebug() << "Game begins!";
    tetris->recordFinished = QVector<QVector<int>>(tetris->board_rowNum, QVector<int>(tetris->board_colNum, 0));
    tetris->recordFalling = QVector<QVector<int>>(tetris->board_rowNum, QVector<int>(tetris->board_colNum, 0));
    tetris->score = 0;
    tetris->genRandomBlock();
    tetris->update_recordFalling();
    update();
    timer->start(time);
}
