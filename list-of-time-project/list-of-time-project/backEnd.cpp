#include "backEnd.h"

struct DATA {

	struct date{
		int day;
		int moth;
		int year;
	};

	std::string name;
	std::vector<std::string> participants;
	std::string description;

};

struct NODE {
	DATA data;
	NODE* next;
};

enum SORT_CRITERIA {
	BY_DATE,
	BY_NAME,
	BY_PARTICIPANTS
};

LinkedList::LinkedList()
{
	head = NULL;
	tail = NULL;
}

void LinkedList::addEvent(DATA data, std::string name, std::vector<std::string> participants, std::string description)
{
	//iterate while tail->next == NULL
	//TAIL-next = new Node
	//new Node = TAIL;
}

dbManager::dbManager()
{
	events = new LinkedList;
}

