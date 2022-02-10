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
	DataBase db(manager, manager.eventsForDisplayment);

	manager.eventsToBeDisplayed(0);

	db.innitDataBase();
}