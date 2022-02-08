#pragma once

#include "backEnd.h"
#include "Tabulate.h"
//function to print Log In form
//function to check Log In form

//function to start displaying DataBase
//function to awaitUserInput
//function to respond to userInput
	//"+" - add event
	//"search" - search for events based on input
	//"sort" - sort events based on criteria0



void displayTextField();
void displayLogInForm();



class DataBase {
	public:
		DataBase(unsigned int selectedEvent);

	public:
		unsigned int m_selectedEvent;

	public:
		void innitDataBase(std::vector<NODE*> events);


};