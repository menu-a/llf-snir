#ifndef LLFFS
#define LLFFS

#include <QObject>
#include <modbustcpworker.h>
#include <QamFlightInstruments>
#include <MainDialog.h>
#include <qairspeed.h>
#include <qaltimeter.h>
#include <qamchronograph.h>
#include <qamtachymeter.h>
#include <qamturncoordinator.h>
#include <qvariometer.h>
#include <dataref.h>
#include <qfipanel.h>
#include <qamgyrodir.h>
#include <QHA.h>
#include <qamudpsocket.h>
#include <xplaneudpworker.h>
#include <QTextStream>
#include <QString>
#include <QDebug>

class llffs : public QObject
{
    Q_OBJECT


public:
    explicit llffs( QObject* parent = 0 ) ;

    void createAirSpeed(int id, int x, int y, int widht, int height) ;
    void createAltimeter(int id, int x, int y, int widht, int height) ;
    void createChronograph(int id, int x, int y, int widht, int height) ;
    void createTurnCoordinator(int id, int x, int y, int widht, int height) ;
    void createTachymeter(int id, int x, int y, int widht, int height) ;
    void createVariometer(int id, int x, int y, int widht, int height) ;
    void createGyroDir(int id, int x, int y, int widht, int height) ;
    void createQHA(int id, int x, int y, int width, int height) ;
    void setQFI(int x, int y, int width, int height, QamFlightInstrument* QFI,int id) ;
    bool loadConf(QString& file) ;

public slots:
     void modbusMapInfo(QString,QString) ;
     void exploitRref(int id, float value) ;
     void pullInputs() ;

private :
//  void udpClientInit(QHostAddress address = QHostAddress::Null ) ;

    XPlaneUdpWorker * m_udpWorker ;
    ModbusTcpWorker * m_tcpworker ;
    QString configFile ;
    QList<QamFlightInstrument *> QListQFI ;
    QList<DataRef *> QListDat ;
    QFIPanel * qfiDisplay;
    MainDialog * mainDialog ;
    QTimer* pullPer ;
    int m_pullPer ;

};

#endif // TEST_H


