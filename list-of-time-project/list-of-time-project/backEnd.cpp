#include "backEnd.h"

LinkedList::LinkedList() 
	: head(nullptr),
	  tail(nullptr)
{
	
}

void LinkedList::addEvent(int day, int month, int year, std::string name, std::vector<std::string> participants, std::string description)
{

	NODE* newEvent = new NODE;

	newEvent->data = { day, month, year, name, participants, description };

	if (head == nullptr)
	{
		head = tail = newEvent;
	}
	else
	{
		tail->next = newEvent;
		tail = tail->next;
	}
}

//void LinkedList::display()
//{
//	NODE* tmp = head;
//
//	while (tmp != nullptr)
//	{
//		std::cout << tmp->data.day << " | " << tmp->data.month << " | " << tmp->data.year << " | " << tmp->data.name << " | " << tmp->data.description << std::endl;
//		std::cout << "____________________________________________________________________________________________________________" << std::endl;
//		tmp = tmp->next;
//	}
//}

Manager::Manager(LinkedList* linkedList) : events(linkedList)
{

}

void Manager::eventsToBeDisplayed(unsigned int startIndex)
{
	unsigned int counter = 0;

	NODE* tmp;
	
	tmp = events->head;

	for (int i = 0; i < startIndex; i++)
	{
		tmp = tmp->next;
	}

	while (tmp != nullptr && counter < MAX_EVENTS_FOR_DISPAYMENT)
	{
		eventsForDisplayment.push_back(tmp);
		tmp = tmp->next;
		counter++;
	}
}