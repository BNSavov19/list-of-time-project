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

bool check(std::string username, std::string password)
{
	return(username == "admin" && password == "adminadmin");
}

void printLogIn()
{
	std::string username, password;

	system("cls");

	std::cout << "Username:              " << std::endl;
	std::cout << "Password:              " << std::endl;

	gotoxy(11, 0); getline(std::cin, username, '\n');

	gotoxy(11, 1);

	int x = 11;
	while (true)
	{
		char c = _getch();

		if (c == '\r') { break; }

		else if (c == '\b')
		{
			if (x - 1 != 10)
			{
				std::cout << "\b";
				std::cout << " ";
				gotoxy(x - 1, 1);
				x--;
			}
		}
		else
		{
			password += c;
			x++;
			std::cout << "*";
		}
	}

	system("cls");

	if (check(username, password)) { std::cout << "data"; }
	else { printLogIn(); }
}

DataBase::DataBase(Manager& manager, std::vector<NODE*>& events)
	: m_Manager(&manager),
	m_events(&events),
	m_userSelection(SELECTED_FIELD::ADD),
	m_selectedSort(),
	m_selectedEvent(0),
	m_queryIsOn(false),
	m_sortIsOn(false)
{

}


std::pair<std::string, std::string> DataBase::getKey()
{
	gotoxy(14, 1);
	for (int i = 0; i < 13; i++) { std::cout << " "; }
	gotoxy(14, 1);

	std::string queryInput;

	std::getline(std::cin, queryInput);

	std::string key, value;

	std::string::size_type key_pos = queryInput.find(':');

	key = queryInput.substr(0, key_pos);
	value = queryInput.substr(key_pos + 1, queryInput.length());

	return std::make_pair(key, value);

}

void DataBase::getEventInput()
{

	system("cls");

	std::string name, day, month, year, description;

	std::cout << "Name:              " << std::endl;
	std::cout << "Day:              " << std::endl;
	std::cout << "Month:              " << std::endl;
	std::cout << "Year:              " << std::endl;
	std::cout << "Description:              " << std::endl;

	gotoxy(19, 0); getline(std::cin, name, '\n');
	gotoxy(5, 1);  getline(std::cin, day, '\n');
	gotoxy(7, 2);  getline(std::cin, month, '\n');
	gotoxy(6, 3);  getline(std::cin, year, '\n');
	gotoxy(13, 4); getline(std::cin, description, '\n');

	DATA eventData = { stoi(day), stoi(month), stoi(year), name, description };

	m_Manager->addEvent(eventData);

	m_Manager->eventsToBeDisplayed(0);

}



void DataBase::innitDataBase()
{
	system("cls");

	buttonsTable = new tabulate::Table;

	if (!m_queryIsOn && !m_sortIsOn)
	{

		buttonsTable->add_row({ "add", "sort", "           ", "export"});
	}
	else if(m_queryIsOn)
	{
		buttonsTable->add_row({ "add", "sort", "           ", "reset", "export"});
	}
	else if(m_sortIsOn)
	{

		if (m_selectedSort == SELECTED_SORT::NEWEST)
		{
			buttonsTable->add_row({ "add", "most recent", "           ", "reset", "export" });
		}

		if (m_selectedSort == SELECTED_SORT::OLDEST)
		{
			buttonsTable->add_row({ "add", "most old", "           ", "reset", "export" });
		}

		if (m_selectedSort == SELECTED_SORT::LATEST_ADDED)
		{
			buttonsTable->add_row({ "add", "latest added", "           ", "reset", "export" });
		}

		if (m_selectedSort == SELECTED_SORT::OLDEST_ADDED)
		{
			buttonsTable->add_row({ "add", "oldest added", "           ", "reset", "export" });
		}
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
	for (NODE* Event : m_queryIsOn || m_sortIsOn ? m_Manager->EventsForDisplayment_sorted : *m_events)
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
			m_userSelection = int(m_userSelection) == (m_queryIsOn || m_sortIsOn ? 3 : 2) ? SELECTED_FIELD::ADD : SELECTED_FIELD(int(m_userSelection) + 1);

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
			m_userSelection = int(m_userSelection) == 0 ?  (m_queryIsOn || m_sortIsOn ? SELECTED_FIELD::RESET : SELECTED_FIELD::SEARCH) : SELECTED_FIELD(int(m_userSelection) - 1);

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

		if (m_userSelection == SELECTED_FIELD::ADD)
		{
			getEventInput();
		}

		if (m_userSelection == SELECTED_FIELD::SORT)
		{
			m_sortIsOn = true;
			m_selectedSort = (m_selectedSort == SELECTED_SORT::UNDEFINED) ? SELECTED_SORT::NEWEST : (m_selectedSort == SELECTED_SORT::OLDEST_ADDED) ? SELECTED_SORT::NEWEST : SELECTED_SORT(int(m_selectedSort) + 1);

			if (!m_Manager->EventsForDisplayment_sorted.empty())
				m_Manager->EventsForDisplayment_sorted.clear();

			void(Manager:: * func)() = m_Manager->m_sortMap.at(int(m_selectedSort));
			(m_Manager->*func)();

		}


		else if (m_userSelection == SELECTED_FIELD::SEARCH)
		{
			if (!m_Manager->EventsForDisplayment_sorted.empty())
				m_Manager->EventsForDisplayment_sorted.clear();
	
			std::pair<std::string, std::string> query = getKey();
			
			void(Manager:: *func)(std::string) = m_Manager->m_queryMap.at(query.first);
			(m_Manager->*func)(query.second);

			m_queryIsOn = true;
			m_selectedEvent = 0;
			m_userSelection = SELECTED_FIELD::EVENTS;

		}



		else if (m_userSelection == SELECTED_FIELD::RESET)
		{

			if (m_queryIsOn)
			{
				m_queryIsOn = false;
			}

			if (m_sortIsOn)
			{
				m_sortIsOn = false;
			}

			m_Manager->EventsForDisplayment_sorted.clear();
			m_selectedEvent = 0;
			
		}

		delete buttonsTable;
		delete eventsTable;
		innitDataBase();

	}

	else getInput();

}