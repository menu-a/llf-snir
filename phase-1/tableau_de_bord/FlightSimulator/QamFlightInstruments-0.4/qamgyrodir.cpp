/*  ---------------------------------------------------------------------------
 *  filename    :   QamGyroDir.cpp
 *  description :   IMPLEMENTATION de la classe QamGyroDir
 *
 *	project     :	Widgets "Flight Instrument"
 *  start date  :   octobre 2015
 *  ---------------------------------------------------------------------------
 *  Copyright 2015-2016 by Alain Menu   <alain.menu@ac-creteil.fr>
 *
 *  This file is part of "Qam Flight Instruments Widgets Library"
 *
 *  This program is free software ;  you can  redistribute it and/or  modify it
 *  under the terms of the  GNU General Public License as published by the Free
 *  Software Foundation ; either version 3 of the License, or  (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY ; without even the  implied  warranty  of  MERCHANTABILITY  or
 *  FITNESS FOR  A PARTICULAR PURPOSE. See the  GNU General Public License  for
 *  more details.
 *
 *	You should have  received  a copy of the  GNU General Public License  along
 *	with this program. If not, see <http://www.gnu.org/licenses/>.
 *  ---------------------------------------------------------------------------
 */

#include "qamgyrodir.h"
#include <QtMath>
#include <QPixmap>

QamGyroDir::QamGyroDir(QWidget* parent ) : QamFlightInstrument(parent)
{
    m_class = "QamGyroDir" ;
	
    //setLabel(QString("GYRDIR"), GYRDIR ) ;
    //setUnit(QString("x 1000"), GYRDIR ) ;
    //setMinMax(-100000 , 100000, GYRDIR ) ;
    //setThresholds(32000, 35000, GYRDIR ) ;
    //setValue(0, GYRDIR ) ;

    m_radius[GYRDIR] = QFI_RADIUS ;
    m_start[GYRDIR]  = 90 ;
    m_span[GYRDIR]   = 360 ;
    m_min[GYRDIR]    =   0 ;
    m_max[GYRDIR]    =  72 ;
    m_step[GYRDIR]   = m_span[GYRDIR] / ( m_max[GYRDIR] - m_min[GYRDIR] ) ;


	//	animation des aiguilles (pour tests)
	
    //setAdjustable(3, 0, GYRDIR ) ;
}

// interception clic sur BP coin inférieur droit

void QamGyroDir::adjustmentChanged(int num, float value )
{
    setValue( value, num ) ;
}

void QamGyroDir::drawBackground(QPainter& painter )
{
	float w, h ;		// épaisseur et longueur du trait de graduation
    QRect gRect ;		// rectangle "trait graduation"
    float gRadius ;		// arrondi sommets rectangle gRect
	QColor	black1(15,13,11) ;
	QColor	black2(34,32,27) ;	
	QColor	white(210,200,190) ;
	QColor	red(221,65,57) ;
	QColor	yellow(205,185,83) ;
	QColor	green(101,149,112) ;

    QFont	fo1("arial.ttf", 60 ) ;
    QFont	fo2("arial.ttf", 50 ) ;

    // fond

    qfiBackground(painter, m_radius[GYRDIR], 10 ) ;

    // avion

    float wi = 700 ;
// image width
        float hi = 700  ;
// image height
        float si = 2000 ;
// scale
        //QRectF target(-0.65*QFI_RADIUS,-0.65*QFI_RADIUS, 5.1*(QFI_RADIUS), 5.1*QFI_RADIUS) ;
        //QRectF source(1.0, 1.0, wi, hi ) ;
        QPixmap p(":/avion.png");
        painter.drawPixmap( -0.7*QFI_RADIUS,-0.7*QFI_RADIUS, wi, hi, p);


}

void QamGyroDir::drawForeground(QPainter& painter )
{

    float w, h ;		// épaisseur et longueur du trait de graduation
    QRect gRect ;		// rectangle "trait graduation"
    float gRadius ;		// arrondi sommets rectangle gRect
    QColor	black1(15,13,11) ;
    QColor	black2(34,32,27) ;
    QColor	white(210,200,190) ;
    QColor	red(221,65,57) ;
    QColor	yellow(205,185,83) ;
    QColor	green(101,149,112) ;

    QFont	fo1("Arial", 60 ) ;
    QFont	fo2("Arial", 50 ) ;

    // graduations "GYRDIR"

    painter.save() ;
    painter.setBrush( white ) ;

    painter.rotate( m_start[GYRDIR] + value(GYRDIR) - 90) ;


    for ( int i = 0 ; i < ( (m_max[GYRDIR] - m_min[GYRDIR])  ) ; ++i ) {

        if ( i % 2 == 0 ) {		w = 8 ; h = 60 ; }
        else {						w =  5 ; h = 35 ; }

        gRect = QRect(m_radius[GYRDIR] - h - 10, -w / 2, h, w) ;
        gRadius = w / 3 ;
        painter.drawRoundedRect(gRect, gRadius, gRadius ) ;

        // sérigraphie

        if (i%6 == 0){
            float alpha = qDegreesToRadians( m_start[GYRDIR] + m_step[GYRDIR] ) ;
            float r = m_radius[GYRDIR] - 115 ;
            qfiText(painter, fo1, white, QPoint( r * qCos(alpha)+35, r * -qSin(alpha) ), QString("%1").arg(i/2) ) ;
        }
        painter.rotate( m_step[GYRDIR] ) ;

    }
    painter.restore() ;




    //qfiText(painter, fo1, white, QPoint( 0, 0.8 * m_radius[GYRDIR] ), label(GYRDIR) ) ;
    //qfiText(painter, fo2, white, QPoint( 0, 0.9 * m_radius[GYRDIR] ), unit(GYRDIR) ) ;
}

