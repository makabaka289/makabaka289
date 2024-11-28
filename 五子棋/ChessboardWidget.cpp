#include "ChessboardWidget.h"
#include <QPushButton>
#include <QPainter>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMouseEvent>
#include <QFile>


#define SIZE 19
#define BORDERSIZE 40
int border[SIZE+1][SIZE+1]={{0}};

namespace GameState{
     bool inturn=true;

}


ChessboardWidget::ChessboardWidget(QWidget *parent):
    QWidget(parent) {

    int extraMarginHeight=40;
    int extraMarginWeight=40;
    int extra=150;
    setFixedSize(SIZE * BORDERSIZE+extraMarginWeight+extra, SIZE * BORDERSIZE+extraMarginHeight);
    // 设置固定大小
    setStyleSheet("background-color:white");

    //按钮生产地

    QPushButton *sort=new QPushButton("save", this);
    sort->setStyleSheet(
        "QPushButton{"
        "background-color:pink;"
        "color:white;"
        "border: 3px solid 	#F0FFFF;"
        "border-radius:5px;"
        "}"
        "QPushButton:pressed{"
        "background-color:lightpink"
        "}"
        );
    sort->setFixedSize(100,50);


    QPushButton * backButton=new QPushButton("返回界面",this);
    backButton->setStyleSheet(
        "QPushButton{"
        "background-color:#00BFFF;"
        "color:white;"
        "border: 3px solid 	#F0FFFF;"
        "border-radius:5px;"
        "}"
        "QPushButton:pressed{"
        "background-color:#1E90FF"
        "}"
        );
    backButton->setFixedSize(100,50);



    QPushButton * loadfile=new QPushButton("load",this);
    loadfile->setStyleSheet(
        "QPushButton{"
        "background-color:#BC5AEA;"
        "color:white;"
        "border: 3px solid 	#F0FFFF;"
        "border-radius:5px;"
        "}"
        "QPushButton:pressed{"
        "background-color:#6F2EAB"
        "}"
        );
    loadfile->setFixedSize(100,50);

    QPushButton * clearButton=new QPushButton("clear",this);
    clearButton->setStyleSheet(
        "QPushButton{"
        "background-color:#BC5AEA;"
        "color:white;"
        "border: 3px solid 	#F0FFFF;"
        "border-radius:5px;"
        "}"
        "QPushButton:pressed{"
        "background-color:#6F2EAB"
        "}"
        );
    clearButton->setFixedSize(100,50);





    QVBoxLayout *vLayout=new QVBoxLayout(this);

    QHBoxLayout *hLayout1 = new QHBoxLayout();
    hLayout1->addStretch();  // 左侧弹性空白
    hLayout1->addWidget(loadfile);  // 将按钮添加到布局


    QHBoxLayout *hLayout2 = new QHBoxLayout();
    hLayout2->addStretch();  // 左侧弹性空白
    hLayout2->addWidget(sort);  // 将按钮添加到布局

    QHBoxLayout *hLayout3 = new QHBoxLayout();
    hLayout3->addStretch();  // 左侧弹性空白
    hLayout3->addWidget(backButton);  // 将按钮添加到布局

    QHBoxLayout *hLayout4 = new QHBoxLayout();
    hLayout4->addStretch();  // 左侧弹性空白
    hLayout4->addWidget(clearButton);


    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addLayout(hLayout4);
    vLayout->addLayout(hLayout3);
    // 设置父控件的布局为垂直布局
    vLayout->setSpacing(10);

    setLayout(vLayout);


    connect(backButton, &QPushButton::clicked, this, &ChessboardWidget::restGame);
    connect(backButton, &QPushButton::clicked, this, &QWidget::close);

    connect(sort,&QPushButton::clicked,this,&ChessboardWidget::setfile);

    connect(loadfile,&QPushButton::clicked,this,&ChessboardWidget::LoadFile);

    connect(clearButton,&QPushButton::clicked,this,&ChessboardWidget::Clear);
}


void ChessboardWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    // 设置棋盘线条的颜色和宽度
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    // 绘制棋盘
    for (int i = 0; i < SIZE+1; ++i) {
        // 绘制横线
        painter.drawLine(i * BORDERSIZE+ MARGIN,  MARGIN, i * BORDERSIZE+ MARGIN, SIZE * BORDERSIZE+ MARGIN);
        // 绘制竖线
        painter.drawLine( MARGIN, i * BORDERSIZE+ MARGIN, SIZE * BORDERSIZE+ MARGIN, i * BORDERSIZE+ MARGIN);
    }
    for(int i=0;i<SIZE+1;i++)
    {
        for(int j=0;j<SIZE+1;j++)
        {
            if(border[i][j]==1)
            {
                painter.setBrush(Qt::white);
                painter.drawEllipse(i * BORDERSIZE + MARGIN - BORDERSIZE / 2, j * BORDERSIZE + MARGIN - BORDERSIZE / 2, BORDERSIZE, BORDERSIZE);
            }
            else if(border[i][j]==-1)
            {
                painter.setBrush(Qt::black);
                painter.drawEllipse(i * BORDERSIZE + MARGIN - BORDERSIZE / 2, j * BORDERSIZE + MARGIN - BORDERSIZE / 2, BORDERSIZE, BORDERSIZE);
            }
        }
    }
}
//棋盘+棋子
void ChessboardWidget:: restGame(){
    for (int i = 0; i < SIZE+1; ++i) {
        for (int j = 0; j < SIZE+1; ++j) {
            border[i][j] = 0;
        }
    }
    GameState::inturn = true;
    update();
}
//刷新

int judgement(int X){
    if(X==5)
        return 1;
    else
        return 0;
}

bool checkWin(int x, int y, int player) {
    const int dx[4] = {1, 0, 1, 1}; // 水平、垂直、主对角线、副对角线方向的 x 增量
    const int dy[4] = {0, 1, 1, -1}; // 水平、垂直、主对角线、副对角线方向的 y 增量

    for (int dir = 0; dir < 4; dir++) {
        int count = 1;

        // 检查正方向
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        while (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && border[nx][ny] == player) {
            count++;
            nx += dx[dir];
            ny += dy[dir];
        }

        // 检查反方向
        nx = x - dx[dir];
        ny = y - dy[dir];
        while (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && border[nx][ny] == player) {
            count++;
            nx -= dx[dir];
            ny -= dy[dir];
        }

        // 如果在某个方向上累计到 5 个棋子，则胜利
        if (count >= 5) {
            qDebug() << "胜利方向：" << dir << " 连续棋子数：" << count;
            return true;
        }
    }

    return false;
}
//ai改 判断胜负
void getmouse(int x, int y) {
    int X = y / BORDERSIZE; // 将鼠标 Y 坐标转换为网格 Y 坐标
    int Y = x / BORDERSIZE; // 将鼠标 X 坐标转换为网格 X 坐标
    qDebug() << "对应的X:" << X;
    qDebug() << "对应的Y:" << Y;

    if (X <= 19 && Y <= 19) { // 确保坐标合法
        if (border[X][Y] == 0) { // 当前位置无棋子
            if (GameState::inturn) {
                border[X][Y] = 1; // 玩家落子
                qDebug() << "白棋落子：" << border[X][Y];
            } else {
                border[X][Y] = -1; // AI 或另一方落子
                qDebug() << "黑棋落子：" << border[X][Y];
            }
            GameState::inturn = !GameState::inturn; // 切换回合
            qDebug()<<"ChessBoardWidget:"<<GameState::inturn<<Qt::endl;
        } else {
            QMessageBox::warning(nullptr, "Warning", "这里已有棋子，换个地方下！");
            return;
        } 
        // 胜负判断逻辑
        if (checkWin(X, Y, border[X][Y])) {
            if (border[X][Y] == 1) {
                QMessageBox::information(nullptr, "游戏结束", "白棋获胜");
            } else if (border[X][Y] == -1) {
                QMessageBox::information(nullptr, "游戏结束", "黑棋获胜");
            }
            ChessboardWidget board;
            board.restGame(); // 重置游戏
        }
    }
}

// 统一的胜负判断函数

void ChessboardWidget::mousePressEvent(QMouseEvent *e)
{

    if (e->button() == Qt::LeftButton)  // 如果按下的是左键
    {
        // 获取鼠标点击的坐标
        int x = e->y();
        int y = e->x();
        // 调用 getmouse 函数，传入坐标
        qDebug()<<"原来的x:"<<x;
        qDebug()<<"原来的y:"<<y;

        getmouse(x, y);
        update();
    }
}

void ChessboardWidget::setfile(){
    QFile file("game_save.txt");

    if(!file.open(QIODevice::ReadWrite|QIODevice::Text)){
        QMessageBox::warning(this,"存档丢失","无法保存游戏");
        return ;
    }
    QTextStream in(&file);
    QStringList allSaves;

    while(!in.atEnd()){
        allSaves.append(in.readLine());
    }
    if(allSaves.size()>=5)
    {
        allSaves.removeFirst();
    }

    QString currentSave;
    for (int i = 0; i < SIZE; ++i) {  // 假设棋盘大小为 15x15
        for (int j = 0; j < SIZE; ++j) {
            currentSave += QString::number(border[i][j]) + " ";  // 保存每个棋盘位置的状态（1 为黑子，-1 为白子，0 为空）
        }
        currentSave += "\n";
    }

    // 将当前棋盘状态添加到存档列表中
    allSaves.append(currentSave);

    // 移动文件指针到文件开头，清空文件内容，准备重新写入
    file.resize(0);
    QTextStream out(&file);

    // 将所有存档（最多5个）写回文件
    for (const QString& save : allSaves) {
        out << save;
    }

    file.close();
    QMessageBox::information(this, "成功", "期待你的胜利~");
}

void ChessboardWidget::LoadFile(){
    QFile file("game_save.txt");  // 打开存档文件

    // 尝试打开文件进行读取
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "加载失败", "无法加载游戏状态。");
        return;
    }

    QTextStream in(&file);  // 创建 QTextStream 对象用于读取文件内容
    QString line;
    int row = 0;

    // 逐行读取文件内容
    while (!in.atEnd() && row <SIZE) {  // 假设棋盘大小为 15x15
        line = in.readLine();  // 读取一行数据
        QStringList pieces = line.split(" ");  // 按空格拆分字符串，得到每个棋盘位置的状态

        for (int col = 0; col < pieces.size() && col < SIZE; ++col) {
            border[row][col] = pieces[col].toInt();  // 将读取的棋盘状态存入 board 数组
        }

        row++;
    }

    file.close();  // 关闭文件
    update();

    // 如果文件中的行数不足 15，可能需要做额外的处理
    if (row < SIZE) {
        QMessageBox::warning(this, "加载警告", "存档文件格式不正确或数据不完整。");
    } else {
        QMessageBox::information(this, "加载成功", "游戏已成功加载。");
    }
}

void ChessboardWidget::Clear(){


    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认", "确定要清除所有存档吗？",
                                  QMessageBox::Yes | QMessageBox::No);

    ChessboardWidget:: restGame();
    update();
    ChessboardWidget::setfile();
}

