   /**
 * \file	potar.h
 * \author	calbatorix
 * \version 1.0
 * \date    26 mars 2016
 * \brief   Creation de la class potar.
 *
 * \details todo.
 *
 */
#ifndef POTAR_H_
#define POTAR_H_

#include <Arduino.h>
#include <EEPROM.h>

class Potar{
	public:
		/*!
     	*  \brief Constructeur
     	*
     	*  Constructeur de la classe potar.
     	*
     	*  \param Pin : pin où est branché la sortie du potentiometre.
	    */
		Potar(int Pin);
		void init();
		void resetEeprom();

		/*!
     	*  \brief lecture de la valeur de sortie du potentiometre.
     	*
     	*  Methode qui permet de recuperer la valeur  de sortie du potentiometre a
     	* transmetre au rapport du joystick.
     	*  \return la valeur de l'axe.
     	*/
		int value();
		int getmin();
		int getmax();
		int getValueAnalog();
	private:
		void writeEeprom();
		void update();
		int in;
		int Valueanalog;
		int Value;
		int min;
		int max;
		bool flags;
		unsigned long millisflag;
};

#endif
