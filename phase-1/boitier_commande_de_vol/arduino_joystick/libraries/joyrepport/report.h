/**
 * \file	report.h
 * \author	calbatorix
 * \version 1.0
 * \date    7 mai 2016 
 * \brief   Creation de la class JoyReport.
 *
 * \details todo.
 *
 */
#ifndef REPPORT_H_
#define REPPORT_H_

#include <Arduino.h>
#include <SoftwareSerial.h>
#define NUM_AXES    4 
/*#define NUM_BUTTONS 8*/
#define RXPIN 2
#define TXPIN 3

typedef struct joyReport_t {
    int16_t axis[NUM_AXES];
  /*int8_t button[NUM_BUTTONS+7)/8];*/
} joyReport_t;

typedef struct comm {
    int16_t axis[12];
} comm;

class JoyReport{
	public:
		JoyReport(int num_axes/*, int num_buttons*/);
		void init();
		void setJoyReport(int tabValue[]);
		void sendJoyReport();
	private:
		joyReport_t joyReport;
		int numAxes;
	  /*int numButtons;*/
};

#endif
