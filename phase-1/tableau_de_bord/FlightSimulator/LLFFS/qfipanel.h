#ifndef QFIPANEL_H
#define QFIPANEL_H

#include <QWidget>
#include <QString>
#include <QTextStream>

class QFIPanel : public QWidget
{
    Q_OBJECT
public:
    explicit QFIPanel(QWidget *parent = 0);
    void setPanel(int x, int y, int height, int width) ;

signals:
private :
    QString title ;

public slots:
};

#endif // QFIPANEL_H
