#include "backEnd.h"

LinkedList::LinkedList() 
	: head(nullptr),
	  tail(nullptr)
{

}

void LinkedList::addNode(int day, int month, int year, std::string name, std::string description)
{

	NODE* newEvent = new NODE;

	newEvent->data = { day, month, year, name, description };

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

void LinkedList::readData()
{
	m_eventsData.open("../data/eventsData.csv", std::fstream::in | std::fstream::out);

	std::string day, month, year, name, description;

	while (std::getline(m_eventsData, day, ','))
	{
		std::getline(m_eventsData, month, ',');
		std::getline(m_eventsData, year, ',');
		std::getline(m_eventsData, name, ',');
		std::getline(m_eventsData, description, '\n');

		addNode(stoi(day), stoi(month), stoi(year), name, description);
	}

	m_eventsData << std::endl;

	m_eventsData.close();

}

void LinkedList::writeData(DATA eventData)
{
	m_eventsData.open("../data/eventsData.csv", std::ios::app);

	m_eventsData << eventData.day << ',' << eventData.month << ',' << eventData.year << ',' << eventData.name << ',' << eventData.description << std::endl;

	m_eventsData.close();
}

Manager::Manager(LinkedList* linkedList) : m_linkedList(linkedList)
{
	m_linkedList->readData();
}

void Manager::addEvent(DATA eventData)
{
	m_linkedList->addNode(eventData.day, eventData.month, eventData.year, eventData.name, eventData.description);

	m_linkedList->writeData(eventData);
}


void Manager::eventsToBeDisplayed(unsigned int startIndex)
{

	if (!eventsForDisplayment.empty())
		eventsForDisplayment.clear();

	unsigned int counter = 0;

	NODE* tmp;
	
	tmp = m_linkedList->head;

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

void Manager::byDate(std::string key)
{
	for(NODE* _event : eventsForDisplayment)
	{
		if (_event->data.day == stoi(key) || _event->data.month == stoi(key) || _event->data.year == stoi(key))
			EventsForDisplayment_sorted.push_back(_event);
	}
}

void Manager::byDay(std::string key)
{
	for (NODE* _event : eventsForDisplayment)
	{
		if (_event->data.day == stoi(key))
			EventsForDisplayment_sorted.push_back(_event);
	}
}

void Manager::byMonth(std::string key)
{
	for (NODE* _event : eventsForDisplayment)
	{
		if (_event->data.month == stoi(key))
			EventsForDisplayment_sorted.push_back(_event);
	}
}

void Manager::byYear(std::string key)
{
	for (NODE* _event : eventsForDisplayment)
	{
		if (_event->data.year == stoi(key))
			EventsForDisplayment_sorted.push_back(_event);
	}
}

void Manager::byName(std::string key)
{
	for (NODE* _event : eventsForDisplayment)
	{
		if (_event->data.name.find(key) != std::string::npos)
			EventsForDisplayment_sorted.push_back(_event);
	}
}