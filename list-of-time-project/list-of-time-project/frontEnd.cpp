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


DataBase::DataBase(std::vector<NODE*>& events)
	: m_events(&events), 
	  m_selectedEvent(0)
{

}

void DataBase::innitDataBase()
{
	system("cls");

	//innit Table for database
	eventsTable = new tabulate::Table;

	int rowCounter = 0;

	//for each event -> add a row
	for (NODE* Event : *m_events)
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
			eventsTable->add_row({" "});
		}
	}

	//style the rows
	(*eventsTable)[m_selectedEvent].format()
		.font_background_color(tabulate::Color::white)
		.font_color(tabulate::Color::grey);

	//style the rows
	for (int i = 0; i < 5; i++)
	{
		if (i == 0)
		{
			(*eventsTable)[m_selectedEvent][i].format()
				.border_right_color(tabulate::Color::white)
				.border_right_background_color(tabulate::Color::white);
		}
		else if (i == 4)
		{
			(*eventsTable)[m_selectedEvent][i].format()
				.border_left_color(tabulate::Color::white)
				.border_left_background_color(tabulate::Color::white);
		}
		else
		{
			(*eventsTable)[m_selectedEvent][i].format()
				.border_left_color(tabulate::Color::white)
				.border_left_background_color(tabulate::Color::white)
				.border_right_color(tabulate::Color::white)
				.border_right_background_color(tabulate::Color::white);
		}

	}

	//print table

	std::cout << *eventsTable;

	getInput();
}


void DataBase::getInput()
{
	char input = _getch();

	if (input == KEY_DOWN)
	{
		m_selectedEvent = m_selectedEvent == 9 ? 0 : m_selectedEvent+1;
		delete eventsTable;
		innitDataBase();
	}

	else if (input == KEY_UP)
	{
		m_selectedEvent = m_selectedEvent == 0 ? 9 : m_selectedEvent-1;
		delete eventsTable;
		innitDataBase();
	}

	//add ENTER

	else getInput();

}