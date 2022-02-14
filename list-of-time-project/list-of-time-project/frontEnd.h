#pragma once

#include "backEnd.h"
#include "Tabulate.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

//function to print Log In form
//function to check Log In form

//function to start displaying DataBase
//function to awaitUserInput
//function to respond to userInput
	//"+" - add event
	//"search" - search for events based on input
	//"sort" - sort events based on criteria0

enum class SELECTED_FIELD {
	ADD,
	SORT,
	SEARCH,
	RESET,
	EVENTS
};

bool check();
void printLogIn();

class DataBase {
	public:
		DataBase(Manager& manager, std::vector<NODE*>& events);

	public:
		Manager* m_Manager;
		SELECTED_FIELD m_userSelection;
		SELECTED_SORT m_selectedSort;
		short int m_selectedEvent; 
		std::vector<NODE*>* m_events;
		tabulate::Table* buttonsTable;
		tabulate::Table* eventsTable;

	private:
		bool m_queryIsOn;
		bool m_sortIsOn;


	public:
		void innitDataBase();
		void getInput();

	private:
		std::pair<std::string, std::string> getKey();
		void getEventInput();

};