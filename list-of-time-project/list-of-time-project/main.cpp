//#define OOF_IMPL
//#include "oof.h"

#include "frontEnd.h"
#include "backEnd.h"

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

	for (int i = 0; i < 15; i++)
	{
		events->addEvent(i, 12, 1969, "Yes", {}, "Hello");
	}

	manager.eventsToBeDisplayed();

	for (NODE* Event : manager.eventsForDisplayment)
	{
		std::cout << Event->data.day << std::endl;
	}

}