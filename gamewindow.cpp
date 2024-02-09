#include "gamewindow.h"
#include "ui_gamewindow.h"

QTimer *timer;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    timer=new QTimer(this);
    timer->setInterval(1000);
    timer->setSingleShot(false);
    ui->setupUi(this);
    connect(this,SIGNAL(setPaintSchedule()),this,SLOT(update()));
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::setGameMode(unsigned mode){
    gamemode = mode;
}

void GameWindow::setInitialValue(){
    isPlaying = true;
    clicked = false;
    candidate = false;
    turn = 1;
    gamemode = 0;
    window_width = this->width();
    window_height = this->height();
}

void GameWindow::setGameData(unsigned b,unsigned h,double k,double t){
    boardSize = b;
    handicap = h;
    komi = k;
    timeB = t*60*60;
    timeW = t*60*60;
    switch (boardSize) {
    case 0:
        sep=8;
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                board9[i][j]=0;
            }
        }
        break;
    case 1:
        sep=12;
        for(int i=0;i<13;i++){
            for(int j=0;j<13;j++){
                board13[i][j]=0;
            }
        }
        break;
    case 2:
        sep=18;
        for(int i=0;i<19;i++){
            for(int j=0;j<19;j++){
                board19[i][j]=0;
            }
        }
        break;
    }
}

void GameWindow::setServerData(){
    //
}

void GameWindow::closeEvent(QCloseEvent *event){
    if(isPlaying&&QMessageBox::question(this,tr("Are you sure to close?"),tr("You're playing game now!\nAre you sure to close?"))==QMessageBox::No)event->ignore();
    else {timer->stop();windowWillClose();event->accept();}
}

void GameWindow::showEvent(QShowEvent *event){
    windowWillShow();
    QMessageBox::information(this,tr("Can you start?"),tr("Game will start, you press the OK button."));
    timer->start();
    event->accept();
}

void GameWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    ui->LabelTurnValue->setText(QString::number(turn));
    ui->LabelKomiValue->setText(QString::number(komi));
    ui->LabelHandicapValue->setText(QString::number(handicap));
    QPainter painter(this);
    painter.setPen(QPen(QBrush(QColor(0,0,0)),1));
    painter.setBrush(QBrush(QColor(231,202,139)));
    painter.drawRect(0,0,window_height-10,window_height-10);
    painter.drawRect(5.0,5.0,window_height-20.0,window_height-20.0);
    double posX=5.0,posY=5.0;
    QPoint coordinate;
    bool loop=true;
    for(double i=1;i<sep;i++){
        painter.drawLine(5.0+(i*((window_height-20.0)/sep)),5.0,5.0+(i*((window_height-20.0)/sep)),window_height-15.0);
        painter.drawLine(5.0,5.0+(i*((window_height-20.0)/sep)),window_height-15.0,5.0+(i*((window_height-20.0)/sep)));
    }
    for(int i=0;i<sep+1;i++){
        for(int j=0;j<sep+1;j++){
            switch (boardSize) {
            case 0:
                if(board9[i][j]!=0){
                    if(board9[i][j]==1)painter.setBrush(QBrush(QColor(255,255,255)));
                    else if(board9[i][j]==2)painter.setBrush(QBrush(QColor(0,0,0)));
                    painter.drawEllipse(QPoint(5.0+((double)j*((window_height-20.0)/sep)),5.0+((double)i*((window_height-20.0)/sep))),int((window_height-20.0)/sep/2),int((window_height-20.0)/sep/2));
                }
                break;
            case 1:
                if(board13[i][j]!=0){
                    if(board13[i][j]==1)painter.setBrush(QBrush(QColor(255,255,255)));
                    else if(board13[i][j]==2)painter.setBrush(QBrush(QColor(0,0,0)));
                    painter.drawEllipse(QPoint(5.0+((double)j*((window_height-20.0)/sep)),5.0+((double)i*((window_height-20.0)/sep))),int((window_height-20.0)/sep/2),int((window_height-20.0)/sep/2));
                }
                break;
            case 2:
                if(board19[i][j]!=0){
                    if(board19[i][j]==1)painter.setBrush(QBrush(QColor(255,255,255)));
                    else if(board19[i][j]==2)painter.setBrush(QBrush(QColor(0,0,0)));
                    painter.drawEllipse(QPoint(5.0+((double)j*((window_height-20.0)/sep)),5.0+((double)i*((window_height-20.0)/sep))),int((window_height-20.0)/sep/2),int((window_height-20.0)/sep/2));
                }
                break;
            }
        }
    }
    if(clicked&&candidate&&mousePoint.x()>candidatePoint.x()-int((window_height-20.0)/sep/2)+5&&mousePoint.x()<candidatePoint.x()+int((window_height-20.0)/sep/2)-5&&mousePoint.y()>candidatePoint.y()-int((window_height-20.0)/sep/2)+5&&mousePoint.y()<candidatePoint.y()+int((window_height-20.0)/sep/2)-5){
        if(turn%2==0)painter.setBrush(QBrush(QColor(255,255,255)));
        else painter.setBrush(QBrush(QColor(0,0,0)));
        for(double i=0;i<sep+1&&loop;i++){
            for(double j=0;j<sep+1&&loop;j++){
                if(posX>candidatePoint.x()-int((window_height-20.0)/sep/2)+5&&posX<candidatePoint.x()+int((window_height-20.0)/sep/2)-5&&posY>candidatePoint.y()-int((window_height-20.0)/sep/2)+5&&posY<candidatePoint.y()+int((window_height-20.0)/sep/2)-5){coordinate=QPoint(j,i);loop=false;}
                posX+=(window_height-20.0)/sep;
            }
            posX=5.0;
            posY+=(window_height-20.0)/sep;
        }
        if(!loop){
            if(placeChecker(coordinate)){
                switch (boardSize) {
                case 0:
                    if(board9[coordinate.y()][coordinate.x()]==0)board9[coordinate.y()][coordinate.x()]=turn%2+1;
                    break;
                case 1:
                    if(board13[coordinate.y()][coordinate.x()]==0)board13[coordinate.y()][coordinate.x()]=turn%2+1;
                    break;
                case 2:
                    if(board19[coordinate.y()][coordinate.x()]==0)board19[coordinate.y()][coordinate.x()]=turn%2+1;
                    break;
                }
                painter.drawEllipse(QPoint(5.0+((double)coordinate.x()*((window_height-20.0)/sep)),5.0+((double)coordinate.y()*((window_height-20.0)/sep))),int((window_height-20.0)/sep/2),int((window_height-20.0)/sep/2));
                turn++;
            }
            else ui->LabelMessage->setText(tr("You can not place there."));
        }
        candidate=false;
        clicked=false;
    }
    else if(clicked&&mousePoint.x()>0&&mousePoint.x()<window_height-10.0&&mousePoint.y()>0&&mousePoint.y()<window_height-10.0){
        ui->LabelMessage->setText("");
        if(turn%2==0)painter.setBrush(QBrush(QColor(255,255,255,200)));
        else painter.setBrush(QBrush(QColor(0,0,0,150)));
        painter.drawEllipse(mousePoint,int((window_height-20.0)/sep/2)-5,int((window_height-20.0)/sep/2)-5);
        candidatePoint = mousePoint;
        clicked = false;
        candidate = true;
    }
    else if(clicked){
        ui->LabelMessage->setText("");
        candidate=false;
        clicked=false;
    }
    painter.end();
}

void GameWindow::mousePressEvent(QMouseEvent *event){
    mousePoint = event->pos();
    clicked = true;
    update();
    event->accept();
}

void GameWindow::resizeEvent(QResizeEvent *event){
    window_width=event->size().width();
    window_height=event->size().height();
    ui->LabelTurn->setGeometry(window_height-12.0+((window_height-20.0)/sep/2),0,ui->LabelTurn->width(),ui->LabelTurn->height());
    ui->LabelTurnValue->setGeometry(window_height-12.0+((window_height-20.0)/sep/2)+ui->LabelTurn->width(),0,ui->LabelTurnValue->width(),ui->LabelTurnValue->height());
    ui->LabelKomi->setGeometry(window_height-12.0+((window_height-20.0)/sep/2),16,ui->LabelKomi->width(),ui->LabelKomi->height());
    ui->LabelKomiValue->setGeometry(window_height-12.0+((window_height-20.0)/sep/2)+ui->LabelKomi->width(),16,ui->LabelKomiValue->width(),ui->LabelKomiValue->height());
    ui->LabelHandicap->setGeometry(window_height-12.0+((window_height-20.0)/sep/2),32,ui->LabelHandicap->width(),ui->LabelHandicap->height());
    ui->LabelHandicapValue->setGeometry(window_height-12.0+((window_height-20.0)/sep/2)+ui->LabelHandicap->width(),32,ui->LabelHandicapValue->width(),ui->LabelHandicapValue->height());
    ui->LabelBlack->setGeometry(window_height-12.0+((window_height-20.0)/sep/2),48,ui->LabelBlack->width(),ui->LabelBlack->height());
    ui->LabelTimeB->setGeometry(window_height-12.0+((window_height-20.0)/sep/2),64,ui->LabelTimeB->width(),ui->LabelTimeB->height());
    ui->LabelTimeBValue->setGeometry(window_height-12.0+((window_height-20.0)/sep/2)+ui->LabelTimeB->width(),64,ui->LabelTimeBValue->width(),ui->LabelTimeBValue->height());
    ui->LabelGetB->setGeometry(window_height-12.0+((window_height-20.0)/sep/2),80,ui->LabelGetB->width(),ui->LabelGetB->height());
    ui->LabelGetBValue->setGeometry(window_height-12.0+((window_height-20.0)/sep/2)+ui->LabelGetB->width(),80,ui->LabelGetBValue->width(),ui->LabelGetBValue->height());
    ui->LabelWhite->setGeometry(window_height-12.0+((window_height-20.0)/sep/2),96,ui->LabelWhite->width(),ui->LabelWhite->height());
    ui->LabelTimeW->setGeometry(window_height-12.0+((window_height-20.0)/sep/2),112,ui->LabelTimeW->width(),ui->LabelTimeW->height());
    ui->LabelTimeWValue->setGeometry(window_height-12.0+((window_height-20.0)/sep/2)+ui->LabelTimeW->width(),112,ui->LabelTimeWValue->width(),ui->LabelTimeWValue->height());
    ui->LabelGetW->setGeometry(window_height-12.0+((window_height-20.0)/sep/2),128,ui->LabelGetW->width(),ui->LabelGetW->height());
    ui->LabelGetWValue->setGeometry(window_height-12.0+((window_height-20.0)/sep/2)+ui->LabelGetW->width(),128,ui->LabelGetWValue->width(),ui->LabelGetWValue->height());
    ui->LabelMessage->setGeometry(window_height-12.0+((window_height-20.0)/sep/2),144,ui->LabelMessage->width(),ui->LabelMessage->height());
    event->accept();
}

void GameWindow::updateTime(){
    if(turn%2==0){
        timeW--;
        ui->LabelTimeWValue->setText(QString(QString::number(timeW/3600)+tr("H")+QString::number((timeW-((timeW/3600)*3600))/60)+tr("M")+QString::number(timeW-((timeW/3600)*3600)-(((timeW-((timeW/3600)*3600))/60)*60))+tr("S")));
    }
    else {
        timeB--;
        ui->LabelTimeBValue->setText(QString(QString::number(timeB/3600)+tr("H")+QString::number((timeB-((timeB/3600)*3600))/60)+tr("M")+QString::number(timeB-((timeB/3600)*3600)-(((timeB-((timeB/3600)*3600))/60)*60))+tr("S")));
    }
}

bool GameWindow::placeChecker(QPoint coordinate){
    switch (boardSize) {
    case 0:
        if(board9[coordinate.y()][coordinate.x()]!=0)return false;
        break;
    case 1:
        if(board13[coordinate.y()][coordinate.x()]!=0)return false;
        break;
    case 2:
        if(board19[coordinate.y()][coordinate.x()]!=0)return false;
        break;
    }
    return true;
}
