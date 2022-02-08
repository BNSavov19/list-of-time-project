//#define OOF_IMPL
//#include "oof.h"

#include "frontEnd.h"

	//struct DATE {
	//	int day;
	//	int month;
	//	int year;
	//};

	//struct DATA {

	//	DATE date;
	//	std::string name;
	//	std::vector<std::string> participants;
	//	std::string description;

	//};


int main()
{
	system("chcp 437");
	system("cls");
	
	LinkedList* events = new LinkedList;
	Manager manager(events);
	DataBase db(0);

	for (int i = 1; i <= 15; i++)
	{
		events->addEvent(i, 12, 1969, "Yes", {}, "Hello");
	}

	manager.eventsToBeDisplayed(0);

	db.innitDataBase(manager.eventsForDisplayment);

}