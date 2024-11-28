#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include <QWidget>

class ChessboardWidget : public QWidget
{
public:
    ChessboardWidget(QWidget *parent = nullptr) ;
    void mousePressEvent(QMouseEvent *e) override;
    void restGame();
    void setfile();
    void LoadFile();
    void Clear();
    void aimod();
    void updateChess();
protected:
    void paintEvent(QPaintEvent *event) override ;
private:
    static constexpr int MARGIN=20;
};



#endif // CHESSBOARDWIDGET_H
