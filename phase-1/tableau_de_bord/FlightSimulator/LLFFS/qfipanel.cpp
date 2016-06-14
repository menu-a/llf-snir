#include "qfipanel.h"

QFIPanel::QFIPanel(QWidget *parent) : QWidget(parent)
{
    //setupUi(this);
    title = "Lycée La Fayette - Flight Simulator - SM 2016" ;
    this->setWindowTitle(title) ;

    this->setStyleSheet("background-color:black ;") ;
    this->setWindowFlags(Qt::FramelessWindowHint);
}

void QFIPanel::setPanel(int x, int y, int height, int width)
{
    this->setGeometry(x, y, height, width) ;
}
