#include "qaltimeter.h"
#include <QDebug>
#include <QPoint>
#include <QPainter>
#include <QFont>
#include <QtMath>


QAltimeter::QAltimeter(QWidget* parent ) : QamFlightInstrument(parent) , m_isUnitmB ( true )
{
    // ALTIMETRE

    setLabel(QString("ALTIMETER"), ALTIMETER ) ;
    setUnit(QString("x 1000"), ALTIMETER ) ;

    setMinMax(-2000, 30000, ALTIMETER ) ;
    setValue(0, ALTIMETER ) ;

    m_radius[ALTIMETER] = QFI_RADIUS ;
    m_start[ALTIMETER]  = 270 ;
    m_span[ALTIMETER]   = 360 ;
    m_min[ALTIMETER]    =   0 ;
    m_max[ALTIMETER]    =  50 ;
    m_step[ALTIMETER]   = m_span[ALTIMETER] / ( m_max[ALTIMETER] - m_min[ALTIMETER] ) ;


    // QNH

    setLabel(QString("QNH"), QNH ) ;
    setUnit(QString("IN.Hg"), QNH ) ;

    setMinMax(0, 1000, QNH ) ;
    setValue(0, QNH ) ;

    m_radius[QNH] = 0.59 * QFI_RADIUS ;
    m_start[QNH]  = 0 ;
    m_span[QNH]   = 360 ;
    m_min[QNH]    =   0 ;
    m_max[QNH]    = 155;
    m_step[QNH]   = m_span[QNH] / ( m_max[QNH] - m_min[QNH] ) ;


    fo1 = QFont("arial.ttf",60);
    fo2 = QFont("arial.ttf",50);
    fo3 = QFont("arial.ttf",20);
    fo4 = QFont("arial.ttf",30);
    fo5 = QFont("arial.ttf",28);

    //	animation des aiguilles (pour tests)

    //setAdjustable(20, 0, ALTIMETER ) ;
    setAdjustable(100, 0, QNH ) ;
    adjustementChanged(QNH,0); // QNH mb= 648 ; QNH IN.Hg

}

/*void QAltimeter::qfiText(QPainter& painter, QFont& font, QColor& color, const QPoint& center, const QString& s )
{
    painter.save() ;
    painter.setFont( font ) ;
    painter.setPen( color ) ;
    QRect rText = painter.fontMetrics().boundingRect( s ) ;
    rText.moveCenter( center ) ;
    painter.drawText( rText, Qt::AlignLeft | Qt::AlignVCenter , s ) ;
    painter.restore() ;
}*/

void QAltimeter::adjustementChanged(int num, float value){
    if (num != QNH)return ;
    setValue(value,num);
    updateWithBackground();

}
void QAltimeter::selectPressed(int num, bool longClic){
    m_isUnitmB = !m_isUnitmB  ;
    updateWithBackground() ;
}



void QAltimeter::drawBackground(QPainter& painter )
{


    // fond
    QConicalGradient	cg(QPointF(0.0, 0.0 ), 360 ) ;
    cg.setColorAt(0.0, Qt::black ) ;
    cg.setColorAt(0.25, Qt::black ) ;
    cg.setColorAt(0.65, Qt::black ) ;
    cg.setColorAt(1.0, Qt::black ) ;

    painter.setBrush(QBrush( cg ) ) ;
    painter.drawEllipse( drawingRect() ) ;
    QFont font = painter.font() ;
    font.setPixelSize(100);
    painter.setFont(font);
    //28.0 -> 31.0


    QColor	black1(15,13,11) ;
    QColor	black2(34,32,27) ;
    QColor	white(210,200,190) ;
    QColor	red(221,65,57) ;
    QColor	yellow(205,185,83) ;
    QColor	green(101,149,112) ;

    painter.save() ;
    painter.setBrush( white ) ;
    painter.rotate( m_start[ALTIMETER] ) ;

    qfiBackground(painter, m_radius[ALTIMETER], 10 ) ;
    float h, w ;		// épaisseur et longueur du trait de graduation
    QRect gRect ;		// rectangle "trait graduation"
    float gRadius ;		// arrondi sommets rectangle gRect
    float r = m_radius[ALTIMETER] ;	// rayon de départ


    for ( int i = 0 ; i <= ( m_max[ALTIMETER] - m_min[ALTIMETER] ) ; ++i ) {

        if ( i % 5 == 0 ) {		h = 10 ; w = 60 ; }
        else {						h =  4 ; w = 40 ; }



        gRect = QRect(m_radius[ALTIMETER] - w - 10, -h / 2, w, h) ;
        gRadius = w / 3 ;
        painter.drawRoundedRect(gRect, gRadius, gRadius ) ;
        painter.rotate( m_step[ALTIMETER] ) ;

    }
    painter.restore() ;




    for ( int i = 0 ; i < ( m_max[ALTIMETER] - m_min[ALTIMETER] ) ; i += 5 ) {
        float alpha = qDegreesToRadians( m_start[ALTIMETER] + i * m_step[ALTIMETER] ) ;
        float r = m_radius[ALTIMETER] - 120 ;
        qfiText(painter, fo1, white, QPoint( r * qCos(alpha), r * qSin(alpha) ), QString("%1").arg(i/5) ) ;

    }


    painter.save() ;
    painter.rotate(10) ;
    qfiText(painter, fo3, white, QPoint( 10, r - 920 ), QString("FEET") ) ;
    painter.rotate(-20) ;
    qfiText(painter, fo3, white, QPoint( 10, r - 920 ), QString("100") ) ;
    painter.restore() ;



}

void QAltimeter::drawForeground(QPainter& painter )
{

    float len ;						// longueur de l'aiguille orientée 0X+
    QVector<QPointF> pts ;			// points de construction dans demi-plan 0Y+
    QColor white(230,230,230) ;		// couleur de la pointe
    QColor transparent (230,250,40,255) ;
    QColor	black1(15,13,11) ;
    QColor	black2(34,32,27) ;



    if(!m_isUnitmB){

    // graduations "QNH"

    float w, h ;		// épaisseur et longueur du trait de graduation
    QRect gRect ;		// rectangle "trait graduation"
    float gRadius ;		// arrondi sommets rectangle gRect
    //float r = m_radius[QNH] ;	// rayon de départ

    painter.save() ;

    QPen pen( white ) ;
    pen.setWidth(5) ;
    painter.setPen( pen ) ;

    painter.setBrush( white ) ;
    pen.setWidth(1) ;
    painter.setPen( pen ) ;

    painter.rotate( m_start[QNH]);
    painter.rotate(-(value(QNH)*348.38/1000));
    int j = 280 ;
    for ( int i = 0 ; i <= ( m_max[QNH] - m_min[QNH] -1 ) ; ++i ) {

        if ( i % 5 == 0 ) {	w = 5 ; h = 30 ; }
        else {				w =  3 ; h = 20 ; }

        gRect = QRect(m_radius[QNH] - h, -w / 2, h, w) ;
        if  ( i % 5 == 0 ){
            float r = m_radius[QNH] - 67 ;
            qfiText(painter, fo5, white, QPoint( r ,0 ), QString("%1").arg(j*0.1) ) ;
            j++ ;
        }

        gRadius = w / 4 ;
        painter.drawRoundedRect(gRect, gRadius, gRadius ) ;
        painter.rotate( m_step[QNH]) ;

    }
    updateWithBackground();

    painter.restore() ;
    painter.save();
    painter.setBrush(black1);
    painter.drawPie(-0.6*QFI_RADIUS,-0.6*QFI_RADIUS,1.6*0.75*QFI_RADIUS,1.6*0.75*QFI_RADIUS,-18*16,-324*16);
    //painter.drawPie(-0.56*0.75*QFI_RADIUS,-0.56*0.75*QFI_RADIUS,1.4*0.6*QFI_RADIUS,1.4*0.6*QFI_RADIUS,-18*16,36*16);
    painter.drawPie(-0.2*1.82*QFI_RADIUS,-0.2*1.82*QFI_RADIUS,1.2*0.6*QFI_RADIUS,1.22*0.6*QFI_RADIUS,-18*16,36*16);
    painter.restore();

    // aiguille "ALTIMETER"


    painter.save();
    painter.setBrush( white ) ;
    painter.rotate(90);
    painter.drawPie(-0.3*QFI_RADIUS,-0.3*QFI_RADIUS,0.6*QFI_RADIUS,0.6*QFI_RADIUS,-30*16,90*16 ) ;
    painter.restore() ;


    //aiguille "ALTIMETER" dixième de miller

    len = 1.025 * 0.77 * QFI_RADIUS ;
    pts.clear() ;
    pts <<  QPointF( 0, 15 ) << QPointF( 100, 15 ) << QPointF( 120, 5 ) << QPointF( 400, 5 ) << QPointF( 460 , 40 ) ;

    painter.save() ;
    painter.rotate( -90 + value(ALTIMETER) * 36.0 / 10000 ) ;
    qfiNeedle(painter, white, pts, 30, 0, 0.5 * len ) ;


    painter.setBrush(black1);
    painter.drawPie(-0.3*QFI_RADIUS,-0.3*QFI_RADIUS,0.6*QFI_RADIUS,0.6*QFI_RADIUS,-18*16,-140*16);
    painter.drawPie(-0.3*QFI_RADIUS,-0.3*QFI_RADIUS,0.6*QFI_RADIUS,0.6*QFI_RADIUS,18*16,140*16);
    painter.restore();



    // aiguille "ALTIMETER" centaines

    len = 0.7 * m_radius[ALTIMETER] ;
    pts.clear() ;
    pts << 	QPointF( -0.3, 20 ) << QPointF( len - 80, 35 ) << QPointF( len , 0 ) ;

    painter.save() ;
    painter.rotate( 270 + value(ALTIMETER) * 36.0 /1000 );
    qfiNeedle(painter, white, pts, 35, 0, 0.35 * len ) ;
    painter.restore() ;


    // aiguille "longue" milliers

    len = 0.9 * m_radius[ALTIMETER] ;
    pts.clear() ;
    pts << QPointF( -0.3 * m_radius[ALTIMETER], 10 ) << QPointF( 0.8 * len, 10 ) << QPointF( len, 5 ) ;

    painter.save() ;
    painter.rotate( 270 + value(ALTIMETER) * 36.0 / 100 );
    qfiNeedle(painter, white, pts, 30, 30, 0.27 * len ) ;
    painter.restore() ;
    painter.save();

    setLabel(QString("in.Hg"), ALTIMETER ) ;
    qfiText(painter, fo4, white, QPoint( 0, 0.5 * m_radius[ALTIMETER] ), label(ALTIMETER) ) ;



    } else {

    // graduations "QNH"

    float w, h ;		// épaisseur et longueur du trait de graduation
    QRect gRect ;		// rectangle "trait graduation"
    float gRadius ;		// arrondi sommets rectangle gRect

    painter.save() ;

    QPen pen( white ) ;
    pen.setWidth(5) ;
    painter.setPen( pen ) ;

    painter.setBrush( white ) ;
    pen.setWidth(1) ;
    painter.setPen( pen ) ;

    painter.rotate( m_start[QNH] ) ;
    painter.rotate(-(value(QNH)*343.35/1000));
    int j = 945 ;
    for ( int i = 0 ; i <= ( 109 ) ; ++i ) {

        if ( i % 5 == 0 ) {	w = 5 ; h = 30 ; }

        else {				w =  3 ; h = 20 ; }

        gRect = QRect(m_radius[QNH] - h, -w / 2, h, w) ;
        if  ( i % 5 == 0 ){
            float r = m_radius[QNH] -70 ;
            qfiText(painter, fo5, white, QPoint( r ,0 ), QString("%1").arg(j) ) ;
            j = j + 5 ;
        }

        gRadius = w / 4 ;
        painter.drawRoundedRect(gRect, gRadius, gRadius ) ;
        painter.rotate( 3.27) ;

    }
    updateWithBackground();


    painter.restore() ;
    painter.save();
    painter.setBrush(black1);
    painter.drawPie(-0.6*QFI_RADIUS,-0.6*QFI_RADIUS,1.6*0.75*QFI_RADIUS,1.6*0.75*QFI_RADIUS,-18*16,-324*16);
    //painter.drawPie(-0.56*0.75*QFI_RADIUS,-0.56*0.75*QFI_RADIUS,1.4*0.6*QFI_RADIUS,1.4*0.6*QFI_RADIUS,-18*16,36*16);
        painter.drawPie(-0.2*1.82*QFI_RADIUS,-0.2*1.82*QFI_RADIUS,1.2*0.6*QFI_RADIUS,1.22*0.6*QFI_RADIUS,-18*16,36*16);
    painter.restore();


   // if ( value(QNH)== 648){
     //   value(ALTIMETER) == 0;
    //} else if (value(QNH)<648) {
      //  painter.rotate(value(ALTIMETER)-7.2);
    //}else if (value(QNH)>648){
      //  painter.rotate(value(ALTIMETER)+7.2);
    //}



    // aiguille "ALTIMETER"
    painter.save();
    painter.setBrush( white ) ;
    painter.rotate(90);
    painter.drawPie(-0.3*QFI_RADIUS,-0.3*QFI_RADIUS,0.6*QFI_RADIUS,0.6*QFI_RADIUS,-30*16,90*16 ) ;
    painter.restore() ;


    //aiguille "ALTIMETER" dixième de miller

    len = 1.025 * 0.77 * QFI_RADIUS ;
    pts.clear() ;
    pts <<  QPointF( 0, 15 ) << QPointF( 100, 15 ) << QPointF( 120, 5 ) << QPointF( 400, 5 ) << QPointF( 460 , 40 ) ;

    painter.save() ;
    painter.rotate( -90 + value(ALTIMETER) * 36.0 / 10000 ) ;
    qfiNeedle(painter, white, pts, 30, 0, 0.5 * len ) ;


    painter.setBrush(black1);
    painter.drawPie(-0.3*QFI_RADIUS,-0.3*QFI_RADIUS,0.6*QFI_RADIUS,0.6*QFI_RADIUS,-18*16,-140*16);
    painter.drawPie(-0.3*QFI_RADIUS,-0.3*QFI_RADIUS,0.6*QFI_RADIUS,0.6*QFI_RADIUS,18*16,140*16);
    painter.restore();



    // aiguille "ALTIMETER" centaines

    len = 0.7 * m_radius[ALTIMETER] ;
    pts.clear() ;
    pts << 	QPointF( -0.3, 20 ) << QPointF( len - 80, 35 ) << QPointF( len , 0 ) ;

    painter.save() ;
    painter.rotate( 270 + value(ALTIMETER) * 36.0 /1000 );
    qfiNeedle(painter, white, pts, 35, 0, 0.35 * len ) ;
    painter.restore() ;


    // aiguille "longue" milliers

    len = 0.9 * m_radius[ALTIMETER] ;
    pts.clear() ;
    pts << QPointF( -0.3 * m_radius[ALTIMETER], 10 ) << QPointF( 0.8 * len, 10 ) << QPointF( len, 5 ) ;

    painter.save() ;
    painter.rotate( 270 + value(ALTIMETER) * 36.0 / 100 );
    qfiNeedle(painter, white, pts, 30, 30, 0.27 * len ) ;
    painter.restore() ;
    painter.save();

    setLabel(QString("Millibar"), ALTIMETER ) ;
    qfiText(painter, fo4, white, QPoint( 0, 0.5 * m_radius[ALTIMETER] ), label(ALTIMETER) ) ;


}

    QConicalGradient	cg(QPointF(0.0, 0.0 ), 360 ) ;
    cg.setColorAt(0.0, Qt::white ) ;
    cg.setColorAt(0.5, Qt::black ) ;
    cg.setColorAt(1.0, Qt::white ) ;
    int axeRadius = 25 ;
    int i ;
    float h = 20 ;
    float r = m_radius[QNH] ;	// rayon de départ
    float hbis = h + 5 ;
    QPolygon triangle ;

    triangle << QPoint ( r,0) << QPoint (r + 1.5 * hbis, - 0.75 * hbis) << QPoint(r + 1.5 * hbis,0.75* hbis);

    painter.setBrush(white);
    if ( i == 0) painter.drawConvexPolygon(triangle);
    painter.restore();


    painter.save() ;
    painter.rotate(-135 ) ;
    painter.setPen(Qt::black ) ;
    painter.setBrush(QBrush( cg ) ) ;
    painter.drawEllipse(-axeRadius, -axeRadius, 2 * axeRadius, 2 * axeRadius ) ;
    axeRadius /= 3 ;
    painter.rotate(180 ) ;
    painter.setPen(Qt::NoPen ) ;
    painter.drawEllipse(-axeRadius, -axeRadius, 2 * axeRadius, 2 * axeRadius ) ;
    painter.restore() ;


}

