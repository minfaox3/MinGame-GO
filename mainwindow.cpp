#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ComboGameMode->setCurrentIndex(0);
    ui->LineServerIP->setDisabled(true);
    ui->ComboRole->setDisabled(true);
    ui->ComboStone->setDisabled(true);
    gw = new GameWindow(this);
    connect(gw,SIGNAL(windowWillClose()),this,SLOT(gameEnd()));
}

MainWindow::~MainWindow()
{
    delete gw;
    delete ui;
}

void MainWindow::gameEnd(){
    ui->PlayButton->setText(tr("Play!"));
    ui->PlayButton->setEnabled(true);
}

void MainWindow::on_PlayButton_clicked()
{
    if(gw->isHidden()){
        gw->setInitialValue();
        gw->setGameMode(ui->ComboGameMode->currentIndex());
        if(ui->ComboGameMode->currentIndex()==0||(ui->ComboGameMode->currentIndex()==1&&ui->ComboRole->currentIndex()==0)){
            gw->setGameData(ui->ComboBoardSize->currentIndex(),ui->SpinHandicap->value(),ui->SpinKomi->value(),ui->SpinTime->value());
        }
        gw->show();
        ui->PlayButton->setText(tr("Playing!"));
        ui->PlayButton->setDisabled(true);
    }
}

void MainWindow::on_ComboGameMode_currentIndexChanged(int index)
{
    if(index==0){
        ui->LineServerIP->setDisabled(true);
        ui->ComboRole->setDisabled(true);
        ui->ComboStone->setDisabled(true);
        ui->ComboBoardSize->setEnabled(true);
        ui->SpinHandicap->setEnabled(true);
        ui->SpinKomi->setEnabled(true);
        ui->SpinTime->setEnabled(true);
    }
    else if(index==1){
        ui->LineServerIP->setEnabled(true);
        ui->ComboRole->setEnabled(true);
        if(ui->ComboRole->currentIndex()==0){
            ui->ComboStone->setEnabled(true);
            ui->ComboBoardSize->setEnabled(true);
            ui->SpinHandicap->setEnabled(true);
            ui->SpinKomi->setEnabled(true);
            ui->SpinTime->setEnabled(true);
        }
        else if(ui->ComboRole->currentIndex()==1){
            ui->ComboStone->setDisabled(true);
            ui->ComboBoardSize->setDisabled(true);
            ui->SpinHandicap->setDisabled(true);
            ui->SpinKomi->setDisabled(true);
            ui->SpinTime->setDisabled(true);
        }
    }
}

void MainWindow::on_ComboRole_currentIndexChanged(int index)
{
    if(index==0){
        ui->ComboStone->setEnabled(true);
        ui->ComboBoardSize->setEnabled(true);
        ui->SpinHandicap->setEnabled(true);
        ui->SpinKomi->setEnabled(true);
        ui->SpinTime->setEnabled(true);
    }
    else if(index==1){
        ui->ComboStone->setDisabled(true);
        ui->ComboBoardSize->setDisabled(true);
        ui->SpinHandicap->setDisabled(true);
        ui->SpinKomi->setDisabled(true);
        ui->SpinTime->setDisabled(true);
    }
}
