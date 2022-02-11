#include "frontEnd.h"

//display Log in Form

	//if(login) -> enterDataBase

		//print DataBase
			//call dbManager.eventsToBeDisplayed();
				//print events returned from the function^

		//wait for Input
		//do something based on input
			//"+" -> call dbManager->events.addEvent(userInput);
			//"search" -> call dbManager->search(userInput);
			//"sort" -> establish what sorting criteria to use -> call dbManager->sort(criteria);

void gotoxy(short x, short y)
{
	COORD coordinates = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

DataBase::DataBase(Manager& manager, std::vector<NODE*>& events)
	: m_Manager(&manager),
	m_events(&events),
	m_userSelection(SELECTED_FIELD::ADD),
	m_selectedEvent(0),
	m_queryIsOn(false)
{

}


std::pair<std::string, std::string> DataBase::getKey()
{
	gotoxy(14, 1);
	for (int i = 0; i < 13; i++) { std::cout << " "; }
	gotoxy(14, 1);

	std::string queryInput;

	while (true)
	{
		char c = _getch();

		if (c == KEY_ENTER)
		{
			break;
		}
		else
		{
			queryInput += c;
			std::cout << c;
		}
	}

	std::string key, value;

	std::string::size_type key_pos = queryInput.find(':');

	key = queryInput.substr(0, key_pos);
	value = queryInput.substr(key_pos + 1, queryInput.length());

	return std::make_pair(key, value);

}



void DataBase::innitDataBase()
{
	system("cls");

	buttonsTable = new tabulate::Table;

	if (!m_queryIsOn)
	{
		buttonsTable->add_row({ "add", "sort", "           " });
	}
	else
	{
		buttonsTable->add_row({ "add", "sort", "           ", "reset"});
	}

	

	if (m_userSelection != SELECTED_FIELD::EVENTS)
	{
		//style selected cell
		(*buttonsTable)[0][int(m_userSelection)].format()
			.font_background_color(tabulate::Color::white)
			.font_color(tabulate::Color::grey);
	}
		

	//innit Table for database
	eventsTable = new tabulate::Table;

	int rowCounter = 0;

	//for each event -> add a row
	for (NODE* Event : m_queryIsOn ? m_Manager->EventsForDisplayment_sorted : *m_events)
	{
		eventsTable->add_row({ Event->data.name,
				std::to_string(Event->data.day),
				std::to_string(Event->data.month),
				std::to_string(Event->data.year),
							   Event->data.description });

		rowCounter++;
	}

	if (rowCounter < 9)
	{
		for (int i = 0; i < 10 - rowCounter; i++)
		{
			eventsTable->add_row({ " " });
		}
	}

	//style the rows
	if (m_userSelection == SELECTED_FIELD::EVENTS)
	{
		(*eventsTable)[m_selectedEvent].format()
			.font_background_color(tabulate::Color::white)
			.font_color(tabulate::Color::grey);
	}
		
		

	//print table

	std::cout << *buttonsTable << std::endl;
	std::cout << *eventsTable;

	getInput();
}


void DataBase::getInput()
{
	char input = _getch();

	if (input == KEY_DOWN)
	{
		if (m_userSelection != SELECTED_FIELD::EVENTS)
		{
			m_userSelection = SELECTED_FIELD::EVENTS;
		}
		else
		{
			m_selectedEvent = m_selectedEvent == 9 ? 0 : m_selectedEvent + 1;
		}

		delete buttonsTable;
		delete eventsTable;
		innitDataBase();
	}

	else if (input == KEY_UP)
	{
		if (m_selectedEvent == 0)
		{
			m_userSelection = SELECTED_FIELD::ADD;
		}
		else
		{
			m_selectedEvent = m_selectedEvent - 1;
		}

		delete buttonsTable;
		delete eventsTable;
		innitDataBase();
	}

	else if (input == KEY_RIGHT)
	{
		if (m_userSelection != SELECTED_FIELD::EVENTS)
		{
			m_userSelection = int(m_userSelection) == (m_queryIsOn ? 3 : 2) ? SELECTED_FIELD::ADD : SELECTED_FIELD(int(m_userSelection) + 1);

		}
		else
		{
			//enter event;
		}
		delete buttonsTable;
		delete eventsTable;
		innitDataBase();
	}

	else if (input == KEY_LEFT)
	{
		if (m_userSelection != SELECTED_FIELD::EVENTS)
		{
			m_userSelection = int(m_userSelection) == 0 ?  (m_queryIsOn ? SELECTED_FIELD::RESET : SELECTED_FIELD::SEARCH) : SELECTED_FIELD(int(m_userSelection) - 1);

		}
		else
		{
			//enter event;
		}
		delete buttonsTable;
		delete eventsTable;
		innitDataBase();
	}

	else if (input == KEY_ENTER)
	{
		if (m_userSelection == SELECTED_FIELD::SEARCH)
		{

			if (!m_Manager->EventsForDisplayment_sorted.empty())
				m_Manager->EventsForDisplayment_sorted.clear();
	
			std::pair<std::string, std::string> query = getKey();
			
			void(Manager:: *func)(std::string) = m_Manager->m_queryMap.at(query.first);
			(m_Manager->*func)(query.second);

			m_queryIsOn = true;
			m_selectedEvent = 0;
			m_userSelection = SELECTED_FIELD::EVENTS;

			delete buttonsTable;
			delete eventsTable;
			innitDataBase();

		}
		else if (m_userSelection == SELECTED_FIELD::RESET)
		{
			m_Manager->EventsForDisplayment_sorted.clear();
			m_queryIsOn = false;
			m_selectedEvent = 0;
			m_userSelection = SELECTED_FIELD::ADD;

			delete buttonsTable;
			delete eventsTable;
			innitDataBase();
		}
	}

	else getInput();

}