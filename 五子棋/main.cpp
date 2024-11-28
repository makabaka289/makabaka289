#include <bits/stdc++.h>
#include "QMainWindow"
#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>
#include <QMouseEvent>
#include <QDropEvent>
#include <QPainter>
#include <QDebug>
#include <QWidget>
#include <QPixmap>
#include <QSoundEffect>
#include <QLabel>
#include <qpushbutton.h>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include  "StartWindow.h"

using namespace std;

#define SIZE 19
#define BORDERSIZE 40
extern int border[SIZE+1][SIZE+1];
extern bool inturn;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWindow s;
    QSoundEffect *music = new QSoundEffect();
    music->setSource(QUrl::fromLocalFile(":/new/prefix1/bgm.wav"));
    music->setLoopCount(QSoundEffect::Infinite);  //设置无限循环
    music->setVolume(0.5f);  //设置音量，在0到1之间
    music->play();
    s.show();
    return a.exec();
}
