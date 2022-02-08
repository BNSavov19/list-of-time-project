#include "frontEnd.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

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


DataBase::DataBase(unsigned int selectedEvent)
{
	m_selectedEvent = selectedEvent;
}

void DataBase::innitDataBase(std::vector<NODE*> events)
{
	//innit Table for database
	tabulate::Table eventsTable;

	//for each event -> add a row
	for (NODE* Event : events)
	{
		eventsTable.add_row({ Event->data.name, std::to_string(Event->data.day), std::to_string(Event->data.month),  std::to_string(Event->data.year), Event->data.description });
	}

	//style the rows
	eventsTable[m_selectedEvent].format()
		.font_background_color(tabulate::Color::white)
		.font_color(tabulate::Color::grey);

	//style the rows
	for (int i = 0; i < 5; i++)
	{
		if (i == 0)
		{
			eventsTable[m_selectedEvent][i].format()
				.border_right_color(tabulate::Color::white)
				.border_right_background_color(tabulate::Color::white);
		}
		else if (i == 4)
		{
			eventsTable[m_selectedEvent][i].format()
				.border_left_color(tabulate::Color::white)
				.border_left_background_color(tabulate::Color::white);
		}
		else
		{
			eventsTable[m_selectedEvent][i].format()
				.border_left_color(tabulate::Color::white)
				.border_left_background_color(tabulate::Color::white)
				.border_right_color(tabulate::Color::white)
				.border_right_background_color(tabulate::Color::white);
		}

	}

	//print table
	std::cout << eventsTable;
}


//void getInput()
//{
//	char input = _getch();
//
//	switch (input)
//	{
//		case KEY_UP:
//			//selectUpYes
//			break;
//		case KEY_DOWN:
//			//if selected menu boutouns, select data attributes yes
//			break;
//		case KEY_LEFT:
//			//select left boutou
//			break;
//		case KEY_RIGHT:
//			//select right boutou
//			break;
//
//		default:
//			break;
//	}
//
//	getInput();
//
//}