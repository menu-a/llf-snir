/**
 * \file	report.cpp
 * \author	calbatorix
 * \version 1.0
 * \date    7 mai 2016
 * \brief   Fichier de definition pour la class JoyReport.
 *
 * \details Ce fichier a pour but de definir les methodes et le(s) constucteur(s) de la class JoyReport.
 *
 */
#include "report.h"

JoyReport::JoyReport(int num_axes/*, int num_buttons*/){
	numAxes = num_axes;
	/*numButtons =  num_buttons;*/
}

void JoyReport::init(){
	Serial.begin(115200);
	delay(200);
}

void JoyReport::setJoyReport(int tabValue[]){
	//bit* p = (bit*)(void*)&tabValues[numAxes];
	for (uint8_t ind=0; ind<numAxes; ind++){
	    joyReport.axis[ind] = tabValue[ind];
        }	
     /*for (uint8_t ind=0; ind<numButtons; ind++){
        	*(p+i) = tabValue[ind];
    }*/
}

void JoyReport::sendJoyReport(){
	struct joyReport_t *report = &joyReport;
	Serial.write((uint8_t*)report, sizeof(joyReport_t));
}
