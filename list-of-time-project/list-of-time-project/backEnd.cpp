#include "backEnd.h"

LinkedList::LinkedList() 
	: head(nullptr),
	  tail(nullptr),
	  eventsCount(0)
{

}

//Append Node in Linked List

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

	eventsCount++;
}

//Read events data from data file

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

//Write event data to data file

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

Manager::~Manager()
{
	for (NODE* _event : eventsForDisplayment)
	{
		delete _event;
	}

	for (NODE* _event : EventsForDisplayment_sorted)
	{
		delete _event;
	}
}

//Add event through Linked List
void Manager::addEvent(DATA eventData)
{
	m_linkedList->addNode(eventData.day, eventData.month, eventData.year, eventData.name, eventData.description);

	m_linkedList->writeData(eventData);
}

//Establish the events that have to be displayed
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

//Get all events
void Manager::getAllEvents()
{
	NODE* tmp = m_linkedList->head;

	while (tmp->next != nullptr)
	{
		m_linkedList->allEvents.push_back(tmp);
	}
}

//Export events to Excel
void Manager::exportEvents()
{
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y", &timeinfo);
	std::string str(buffer);


	m_linkedList->m_eventsData.open("../data/Table_" + str + ".csv", std::fstream::out);

	int counter = 0;

	m_linkedList->m_eventsData << "ID:,NAME:,DAY:,MONTH:,YEAR:,DESCRIPTION:" << std::endl;


	NODE* tmp = m_linkedList->head;

	while (tmp->next != nullptr)
	{
		m_linkedList->m_eventsData << counter << "," << tmp->data.name << "," << tmp->data.day << ',' << tmp->data.month << ',' << tmp->data.year << ',' << tmp->data.description << std::endl;
		counter++;
		tmp = tmp->next;
	}
	

	m_linkedList->m_eventsData.close();

}

//Search through events, using date key
void Manager::search_byDate(std::string key)
{
	for (NODE* _event : eventsForDisplayment)
	{
		if (_event->data.day == stoi(key) || _event->data.month == stoi(key) || _event->data.year == stoi(key))
			EventsForDisplayment_sorted.push_back(_event);
	}
}

//Search through events, using day key
void Manager::search_byDay(std::string key)
{
	for (NODE* _event : eventsForDisplayment)
	{
		if (_event->data.day == stoi(key))
			EventsForDisplayment_sorted.push_back(_event);
	}
}

//Search through events, using month key
void Manager::search_byMonth(std::string key)
{
	for (NODE* _event : eventsForDisplayment)
	{
		if (_event->data.month == stoi(key))
			EventsForDisplayment_sorted.push_back(_event);
	}
}

//Search through events, using year key
void Manager::search_byYear(std::string key)
{
	for (NODE* _event : eventsForDisplayment)
	{
		if (_event->data.year == stoi(key))
			EventsForDisplayment_sorted.push_back(_event);
	}
}

//Search through events, using name key
void Manager::search_byName(std::string key)
{
	for (NODE* _event : eventsForDisplayment)
	{
		if (_event->data.name.find(key) != std::string::npos)
			EventsForDisplayment_sorted.push_back(_event);
	}
}

//Sort events by newest year
void Manager::sort_Newest()
{
	for (NODE* _event : eventsForDisplayment)
	{
		EventsForDisplayment_sorted.push_back(_event);
	}

	std::sort(EventsForDisplayment_sorted.begin(), EventsForDisplayment_sorted.end(), [](NODE* a, NODE* b)->bool {return a->data.year > b->data.year; });
}

//Sort events by oldest year
void Manager::sort_Oldest()
{
	for (NODE* _event : eventsForDisplayment)
	{
		EventsForDisplayment_sorted.push_back(_event);
	}

	std::sort(EventsForDisplayment_sorted.begin(), EventsForDisplayment_sorted.end(), [](NODE* a, NODE* b)->bool {return a->data.year < b->data.year; });
}

//Sort events by latest time added
void Manager::sort_LatestAdded()
{
	for (NODE* _event : eventsForDisplayment)
	{
		EventsForDisplayment_sorted.push_back(_event);
	}

	std::reverse(EventsForDisplayment_sorted.begin(), EventsForDisplayment_sorted.end());
}

//Sort events by oldest time added
void Manager::sort_OldestAdded()
{
	for (NODE* _event : eventsForDisplayment)
	{
		EventsForDisplayment_sorted.push_back(_event);
	}
}

