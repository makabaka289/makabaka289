#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>


class StartWindow : public QWidget {
public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
    void startGame();
    void startAiGame();
    void startAiEasyGame();
    void startAiMediumGame();
    void startAiDifficultyGame();
    void startconnectGame();
    void Clear();
    void functionback();
    void restGame();
private:
QWidget *difficultyWindow = nullptr;
    };
#endif // STARTWINDOW_H
