#include "llffs.h"
using namespace std ;


llffs::llffs(QObject *parent) :
    QObject(parent) ,
    configFile(QString("conf.csv")),
    m_pullPer(500)

{
    qfiDisplay = new QFIPanel() ;
    mainDialog = new MainDialog() ;

    m_tcpworker = new ModbusTcpWorker() ;
    connect( m_tcpworker, SIGNAL(modbusMapInfo(QString,QString)), this, SLOT(modbusMapInfo(QString,QString)) ) ;

    loadConf(configFile);

    m_udpWorker = new XPlaneUdpWorker("192.168.0.1", 49000, 49001, QListDat ) ;
    connect(m_udpWorker, SIGNAL(rrefReceived(int,float)), this, SLOT(exploitRref(int,float))) ;
    m_udpWorker->start();

    pullPer = new QTimer(this) ;
    connect(pullPer, SIGNAL(timeout()), this, SLOT(pullInputs())) ;
    pullPer->setInterval(m_pullPer);
    pullPer->start();


    m_tcpworker->setRemoteValue("LedA-9",0);
}


void llffs::setQFI(int x, int y, int width, int height, QamFlightInstrument* QFI, int id)
{
    QRect rect(x,y,width,height) ;
    QFI->setId(id) ;
    QFI->setGeometry(rect);
    QFI->setParent(qfiDisplay) ;
    QFI->show();
}

bool llffs::loadConf(QString &csv){

    QFile file( csv ) ;

    if ( file.open( QIODevice::ReadOnly) ) {
//      cout << "Ouverture du CSV" << endl ;
        QByteArray fileBytes = file.readAll();
        fileBytes.replace("\r\n", "\n") ;
        fileBytes.replace("\r", "\n") ;
        QTextStream in (fileBytes) ;

        in.setCodec("UTF-8");

        QString line = in.readLine() ;
        int nline = 1 ;

        while (!line.isNull()) {
            if ( (line.isEmpty() )||( line.startsWith("#"))) {
                line = in.readLine() ;
                nline++ ;
                continue ;
            }

            QStringList parse = line.split(";") ;
            for (int i = 0; i < parse.size(); i++){
                parse[i]=parse[i].trimmed() ;
            }

            if (parse[0] == "QFIPANEL")
            {
                qfiDisplay->setPanel(parse[1].toInt(),parse[2].toInt(),parse[3].toInt(),parse[4].toInt());
                qfiDisplay->show() ;
            }

            /*if (parse[0] == "XPLANE"){
                m_udpWorker = new XPlaneUdpWorker(parse[1], 49000, 49001, QListDat ) ;
                connect(m_udpWorker, SIGNAL(rrefReceived(int,float)), this, SLOT(exploitRref(int,float))) ;
                m_udpWorker->start();
                qDebug() << parse[0] ;
            }*/
            if ( parse.size() == 7) {
                if ( parse[0] == "QFI") {
                    if (parse[2] == "QAirSpeed")
                        createAirSpeed(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt());
                    if (parse[2] == "QamTachymeter")
                        createTachymeter(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt());
                    if (parse[2] == "QamChronograph")
                        createChronograph(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt());
                    if (parse[2] == "QamTurnCoordinator")
                        createTurnCoordinator(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt());
                    if (parse[2] == "QAltimeter")
                        createAltimeter(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt());
                    if ( parse[2] == "QVariometer")
                        createVariometer(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt()) ;
                    if ( parse[2] == "QGyro")
                        createGyroDir(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt()) ;
                    if (parse[2]== "QHA")
                        createQHA(parse[1].toInt(),parse[3].toInt(),parse[4].toInt(),parse[5].toInt(),parse[6].toInt());

                }
            }

            if (parse[0] == "MODIPSLAVE"){
                m_tcpworker->addModbusSlave(parse[1]) ;
                m_tcpworker->slaveCommand(0, ModbusTcpWorker::CONNECT);

                m_tcpworker->setRemoteValue("LedA-9",2);

            }

            if (parse[0] == "RREF_QFI"){

                DataRef *dataref = new DataRef(parse[3],parse[4].toInt()) ;

                if (parse.size() == 5)
                    dataref->bindToInstrument(parse[1].toInt(),parse[2].toInt());

                if ( parse.size() == 7)
                    dataref->bindToInstrument(parse[1].toInt(),parse[2].toInt(),parse[5].toFloat(),parse[6].toFloat());


                QListDat << dataref ;

            }
            if (parse[0] == "PULL_PER"){
                m_pullPer = parse[1].toInt() ;

            }

            if (parse[0] == "TOR_QFI")
            {
                DataRef *dataref = new DataRef(parse[2].toInt(), parse[3].toInt(),true) ;
                dataref->bindToDigitalIo(parse[1]);

                QListDat << dataref ;
            }
            if (parse[0] == "ANA_QFI")
            {
                DataRef * dataref = new DataRef(parse[2].toInt(), parse[3].toInt(),true) ;
                dataref->bindToAnalogIo(parse[1]) ;

                QListDat << dataref ;
            }

            line = in.readLine() ;
            nline++ ;
        }

        file.close();

        return true ;
    }
    return false ;


}
void llffs::createAirSpeed(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qairspeed = new QAirSpeed() ;
    setQFI( x,  y,  widht,  height, qairspeed, id) ;
    QListQFI << qairspeed ;
    qairspeed->show() ;

}

void llffs::createAltimeter(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qaltimeter = new QAltimeter() ;
    setQFI( x,  y,  widht,  height, qaltimeter, id ) ;
    QListQFI << qaltimeter ;
    qaltimeter->show() ;
}

void llffs::createChronograph(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qamchronograph = new QamChronograph() ;
    dynamic_cast<QamChronograph*>(qamchronograph)->setAutoTime(false) ;
    setQFI( x,  y,  widht,  height, qamchronograph, id) ;
    QListQFI << qamchronograph ;
    qamchronograph->show() ;
}

void llffs::createTurnCoordinator(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qamturncoordinator = new QamTurnCoordinator();
    setQFI( x,  y,  widht,  height, qamturncoordinator, id) ;
    QListQFI << qamturncoordinator ;
    qamturncoordinator->show();
}

void llffs::createTachymeter(int id, int x, int y, int widht, int height){
    QamFlightInstrument *qamtachymeter = new QamTachymeter() ;
    setQFI( x,  y,  widht,  height, qamtachymeter, id) ;
    QListQFI << qamtachymeter ;
    qamtachymeter->show() ;
}

void llffs::createVariometer(int id, int x, int y, int widht, int height)
{
    QamFlightInstrument * v = new QamVariometer() ;
    setQFI(x , y, widht, height, v, id) ;
    QListQFI <<  v ;
    v->show();
}

void llffs::createGyroDir(int id, int x, int y, int widht, int height)
{
    QamFlightInstrument * gyro = new QamGyroDir() ;
    setQFI(x, y, widht, height, gyro, id) ;
    QListQFI << gyro ;
    gyro->show() ;
}

void llffs::createQHA(int id, int x, int y, int width, int height){
    QamFlightInstrument *qha = new QHA() ;
    setQFI( x, y, width, height, qha, id) ;

    QListQFI << qha ;
    qha->show();
}
void llffs::modbusMapInfo(QString s1,QString s2){
}

void llffs::exploitRref(int id, float value)
{
    for (int i = 0; i < QListDat.size(); i++)
    {
       if(QListDat[i]->id() == id)
       {
           if(QListDat[i]->isRrefQfi())
           {
               int a = QListDat[i]->instrumentId() ;
               int b = QListDat[i]->instrumentAxis() ;
               for (int j = 0; j < QListQFI.size(); j++)
               {
                   if(QListQFI[j]->id() == a)
                   {
                       value = QListDat[i]->scaled(value) ;
                       QListQFI[j]->setValue(value, b) ;
                   }
               }
           }
        }
    }
}
void llffs::pullInputs()
{

    for ( int i =0 ; i < QListDat.size(); ++i )
    {
        DataRef* dr = QListDat.at(i) ;

        if ( dr->isDref()) {
            float v = m_tcpworker->remoteValue(dr->sourceName()) ;
            if (v != dr->lastValue()) {
                m_udpWorker->send(dr->xplaneDref( dr->scaled(v)));

            }
        }
        else if (dr->isDigitalQfiInput()) {
            for ( int i = 0 ; i < QListQFI.size() ; ++i){
                if ( QListQFI.at(i)->id() == dr->instrumentId()) {
                    QamFlightInstrument* qfi = QListQFI.at(i) ;
                    float v = m_tcpworker->remoteValue(dr->sourceName()) ;


                    if ( v == dr->lastValue()) break ;

                    dr->setLastValue( v );

                    if ( dr->sourceName().startsWith("Sel")) {
                        if (dr->scaled(v))
                            m_tcpworker->setRemoteValue(dr->sourceName(), dr->scaled( 0 ));
                        else break ;
                    }
                    qfi->selectPressed(dr->instrumentAxis());
                    break ;
                }
            }
        }
        else if ( dr->isAnalogQfiInput() ){
            for (int i = 0 ; i < QListQFI.size(); ++i ){
                if (QListQFI.at(i)->id() == dr->instrumentId()){
                    QamFlightInstrument * qfi = QListQFI.at(i) ;
                    float v = m_tcpworker->remoteValue(dr->sourceName()) ;

                    if ( v != dr->lastValue()){
                        qfi->adjustmentChanged(dr->instrumentAxis(), dr->scaled(v));
                        dr->setLastValue( v );
                    }
                    break ;
                }
            }
        }
        else if( dr->isDigitalToDigital()){
            float v = m_tcpworker->remoteValue(dr->sourceName()) ;
            if ( v != dr->lastValue())
                m_tcpworker->setRemoteValue(dr->targetName(), dr->scaled( v ));
                dr->setLastValue( v );
        }
    }
}
