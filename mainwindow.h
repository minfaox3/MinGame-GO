#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "gamewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_PlayButton_clicked();
    void gameEnd();
    void on_ComboGameMode_currentIndexChanged(int index);
    void on_ComboRole_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    GameWindow *gw;
};
#endif // MAINWINDOW_H
