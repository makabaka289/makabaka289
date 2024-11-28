#include "StartWindow.h"
#include "ChessboardWidget.h"
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>
#include <QThread>

namespace GameState{
  extern bool inturn;
}

#define SIZE 19
extern int border[SIZE+1][SIZE+1];


StartWindow::StartWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("五子棋");
    setFixedSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("欢迎来到五子棋(这里没有万宁)", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold;");

    QPushButton *startButton = new QPushButton("线下模式", this);
    startButton->setFixedSize(120, 40);

    QPushButton *aiButton = new QPushButton("入机模式", this);
    aiButton->setFixedSize(120, 40);

    QPushButton *connectButton = new QPushButton("线上模式", this);
    connectButton->setFixedSize(120, 40);

    layout->addWidget(title);
    layout->addSpacing(20);
    layout->addWidget(startButton, 0, Qt::AlignCenter);
    layout->addWidget(aiButton, 0, Qt::AlignCenter);


    layout->addWidget(connectButton, 0, Qt::AlignCenter);

    connect(startButton, &QPushButton::clicked, this, &StartWindow::startGame);
    connect(aiButton, &QPushButton::clicked, this, &StartWindow::startAiGame);
    connect(connectButton, &QPushButton::clicked, this, &StartWindow::startconnectGame);
}

StartWindow::~StartWindow(){
}

void StartWindow::startGame() {
    ChessboardWidget *chessboard = new ChessboardWidget();
    chessboard->show();
    StartWindow::Clear();
}

void StartWindow::startAiGame() {
    this->hide();

    if (!this->difficultyWindow) { // 防止重复创建
        this->difficultyWindow = new QWidget();
        this->difficultyWindow->setWindowTitle("选择难度");
        this->difficultyWindow->setFixedSize(400, 300);

        QVBoxLayout *layout = new QVBoxLayout(this->difficultyWindow);

        QPushButton *easyButton = new QPushButton("简单(一点都不会下棋的)", this->difficultyWindow);
        QPushButton *mediumButton = new QPushButton("中等（有基本的下棋能力）", this->difficultyWindow);
        QPushButton *backButton = new QPushButton("返回", this->difficultyWindow);

        easyButton->setFixedSize(150, 40);
        mediumButton->setFixedSize(150, 40);
        backButton->setFixedSize(120, 40);

        layout->addWidget(easyButton, 0, Qt::AlignCenter);
        layout->addWidget(mediumButton, 0, Qt::AlignCenter);
        layout->addWidget(backButton, 0, Qt::AlignCenter);

        connect(easyButton, &QPushButton::clicked, this, &StartWindow::startAiEasyGame);
        connect(mediumButton, &QPushButton::clicked, this, &StartWindow::startAiMediumGame);
        connect(backButton, &QPushButton::clicked, this, &StartWindow::functionback);
    }

    this->difficultyWindow->show(); // 显示难度选择窗口
}

void StartWindow::startconnectGame() {
    QMessageBox::information(nullptr, "提示", "联机模式还没出，下次一定");
}

void StartWindow::Clear() {
    for (int i = 0; i < SIZE+1; ++i) {
        for (int j = 0; j < SIZE+1; ++j) {
            border[i][j] = 0;
        }
    }
    GameState::inturn = true;
    for (QObject *child : children()) {
        QTimer *timer = qobject_cast<QTimer *>(child);
        if (timer) {
            timer->stop();
            timer->deleteLater();
        }
    }
    update();
}

void StartWindow::functionback() {
    if (this->difficultyWindow) {
        this-> difficultyWindow->hide();
    }
    Clear();
    this->show();
}

void StartWindow:: restGame(){
    for (int i = 0; i < SIZE+1; ++i) {
        for (int j = 0; j < SIZE+1; ++j) {
            border[i][j] = 0;
        }
    }
    GameState::inturn = true;
    update();
}

bool checkWin1(int x, int y, int player) {
    const int dx[4] = {1, 0, 1, 1}; // 水平、垂直、主对角线、副对角线方向的 x 增量
    const int dy[4] = {0, 1, 1, -1}; // 水平、垂直、主对角线、副对角线方向的 y 增量

    for (int dir = 0; dir < 4; dir++) {
        int count = 1;  // 当前棋子

        // 检查正方向的连续棋子
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        while (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && border[nx][ny] == player) {
            count++;
            nx += dx[dir];
            ny += dy[dir];
        }

        // 检查反方向的连续棋子
        int opnx = x - dx[dir];
        int opny = y - dy[dir];
        while (opnx >= 0 && opnx < SIZE && opny >= 0 && opny < SIZE && border[opnx][opny] == player) {
            count++;
            opnx -= dx[dir];
            opny -= dy[dir];
        }

        // 如果在某个方向上连续棋子数达到 5，则胜利
        if (count >= 5) {
            qDebug() << "胜利方向：" << dir << " 连续棋子数：" << count;
            return true;
        }
    }

    return false;
}




// 主评估函数：考虑防守和进攻
int evaluateMove(int x, int y, int player) {
    int score = 0;
    const int dx[4] = {1, 0, 1, 1}; // 水平、垂直、主对角线、副对角线方向的 x 增量
    const int dy[4] = {0, 1, 1, -1}; // 水平、垂直、主对角线、副对角线方向的 y 增量

    int opponent = (player == 1) ? -1 : 1; // 如果当前是玩家(1)，那么对手是AI(-1)，反之亦然

    for (int dir = 0; dir < 4; dir++) {
        int count = 1;  // 当前棋子的连子数
        int opCount = 0;  // 对方棋子的连子数
        bool canBlock = false;  // 是否有需要防守的位置

        // 检查正方向
        int nx = x + dx[dir], ny = y + dy[dir];
        while (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && border[nx][ny] == player) {
            count++;
            nx += dx[dir];
            ny += dy[dir];
        }

        // 检查反方向
        int opnx = x - dx[dir], opny = y - dy[dir];
        while (opnx >= 0 && opnx < SIZE && opny >= 0 && opny < SIZE && border[opnx][opny] == player) {
            count++;
            opnx -= dx[dir];
            opny -= dy[dir];
        }

        // 检查对方的连子
        // 正方向
        opnx = x + dx[dir], opny = y + dy[dir];
        while (opnx >= 0 && opnx < SIZE && opny >= 0 && opny < SIZE && border[opnx][opny] == opponent) {
            opCount++;
            opnx += dx[dir];
            opny += dy[dir];
        }

        // 反方向
        opnx = x - dx[dir], opny = y - dy[dir];
        while (opnx >= 0 && opnx < SIZE && opny >= 0 && opny < SIZE && border[opnx][opny] == opponent) {
            opCount++;
            opnx -= dx[dir];
            opny -= dy[dir];
        }

        // 防守优先：如果对方形成威胁
        if (opCount >= 4) {
            score -= 1000;  // 强烈防守，阻止对方获胜
        } else if (opCount == 3) {
            canBlock = true; // 需要防守
        } else if (opCount == 2) {
            canBlock = true; // 可能形成活三，继续防守
        }

        if (canBlock) {
            score -= 200;  // 防守位置给予更高的负分，优先防守
        }

        // 自己进攻：连子数
        if (count >= 4) {
            score += 1000;  // 连成4子，进攻强烈
        } else if (count == 3) {
            score += 100;  // 连成3子
        } else if (count == 2) {
            score += 10;  // 连成2子
        }
    }

    // 防守优先：增加距离敌方棋子威胁区域的距离的评分
    int centerDist = abs(x - SIZE / 2) + abs(y - SIZE / 2);  // 距离棋盘中心的距离
    if (centerDist <= 2) {
        score += 50;  // 中心附近的位置优先
    }

    return score;
}




void ChessboardWidget::updateChess(){
    update();
}


void StartWindow::startAiEasyGame() {
    startGame();
    QTimer *timer = new QTimer(this); // 创建一个定时
    int  interval=20000;
    timer->setInterval(interval);

    connect(timer, &QTimer::timeout, this, [this]() {
        if (!GameState::inturn) {
            int x = std::rand() % SIZE;
            int y = std::rand() % SIZE;

            if (border[x][y] == 0) {
                border[x][y] = -1;
                GameState::inturn = true;
                update();
                if(checkWin1(x,y,-1)){
                    QMessageBox::information(this,"提示","ai胜利（你怎么连他都没下过？？）");

                }
            }
        }
    });
    timer->start(0);
}

void StartWindow::startAiMediumGame() {
    startGame();  // 初始化游戏
    QTimer *timer = new QTimer(this);  // 创建一个定时器
    int interval = 0;  // 设置定时器间隔为 0 毫秒，即每次立即触发
    timer->setInterval(interval);  // 设置定时器的时间间隔

    connect(timer, &QTimer::timeout, this, [this]() {
        // 在每次定时器超时时，进行 AI 落子
        if (!GameState::inturn) {  // 如果是 AI 的回合
            // 寻找最佳落子位置
            int bestScore = -1;
            int bestX = -1, bestY = -1;

            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    if (border[i][j] == 0) {  // 只有空位置才考虑
                        int score = evaluateMove(i, j, -1);  // 评估当前空位
                        if (score > bestScore) {
                            bestScore = score;
                            bestX = i;
                            bestY = j;
                        }
                    }
                }
            }

            // 如果找到了最佳位置，AI 在此位置落子
            if (bestX != -1 && bestY != -1) {
                border[bestX][bestY] = -1;  // AI 落子
                GameState::inturn = true;  // 更新回合
                update();  // 刷新显示

                // 检查玩家是否胜利
                if (checkWin1(bestX, bestY, 1)) {
                    QMessageBox::information(this, "胜利", "玩家 白棋胜利！");
                    update();
                    StartWindow::restGame();
                }

                // 检查 AI 是否胜利
                if (checkWin1(bestX, bestY, -1)) {
                    QMessageBox::information(this, "胜利", "AI 黑棋胜利！");
                    update();
                    StartWindow::restGame();
                }
            }
        }
    });

    timer->start(0);  // 启动定时器
}

