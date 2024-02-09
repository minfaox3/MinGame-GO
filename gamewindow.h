#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDebug>
#include <QPoint>
#include <QTimer>
#include <QPainter>
#include <QShowEvent>
#include <QPaintEvent>
#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void setGameMode(unsigned mode);
    void setInitialValue();
    void setGameData(unsigned b,unsigned h,double k,double t);
    void setServerData();

signals:
    void windowWillClose();
    void windowWillShow();
    void setPaintSchedule();

protected:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

private slots:
    void updateTime();

private:
    bool placeChecker(QPoint coordinate);
    Ui::GameWindow *ui;
    bool isPlaying;
    bool clicked;
    bool candidate;
    double sep;
    //
    double window_width;
    double window_height;
    QPoint mousePoint;
    QPoint candidatePoint;
    //
    unsigned board9[9][9];
    unsigned board13[13][13];
    unsigned board19[19][19];
    //
    unsigned gamemode;
    unsigned turn;
    unsigned boardSize;
    unsigned handicap;
    double komi;
    unsigned timeW;
    unsigned timeB;
    //
};

#endif // GAMEWINDOW_H
