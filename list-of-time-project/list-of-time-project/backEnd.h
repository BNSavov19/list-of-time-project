#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <map>

#define MAX_EVENTS_FOR_DISPAYMENT 10

struct DATA {
	int day;
	int month;
	int year;
	std::string name;
	std::string description;
};

struct NODE {
	DATA data;
	NODE* next = nullptr;
};

enum class SELECTED_SORT {
	UNDEFINED,
	NEWEST,
	OLDEST,
	LATEST_ADDED,
	OLDEST_ADDED
};

class Manager;


class LinkedList {

	friend class Manager;

public:
	NODE* head;
	NODE* tail;

private:
	const char* path = "../data/eventsData.csv";
	std::fstream m_eventsData;

public:
	LinkedList();

	void addNode(int day, int month, int year, std::string name, std::string description);

private:
	void readData();
	void writeData(DATA eventData);

};

class Manager {

public:
	Manager(LinkedList* linkedList);
	~Manager();


public:
	LinkedList* m_linkedList;
	std::vector<NODE*> eventsForDisplayment;
	std::vector<NODE*> EventsForDisplayment_sorted;

	const std::map<std::string, void(Manager::*)(std::string)> m_queryMap {
		{"date", &Manager::search_byDate},
		{"day", &Manager::search_byDay},
		{"month", &Manager::search_byMonth},
		{"year", &Manager::search_byYear},
		{"name", &Manager::search_byName},
	};

	/*const std::map<int, void(Manager::*)()> m_soryMap{
		{1, &Manager::sort_Newest},
		{2, &Manager::sort_Oldest},
		{3, &Manager::sort_LatestAdded},
		{4, &Manager::sort_OldestAdded},
	};*/

public:
	//void update();
	void addEvent(DATA eventData);
	void eventsToBeDisplayed(unsigned int startIndex);


	//search functions
	void search_byDate (std::string key);
	void search_byDay  (std::string key);
	void search_byMonth(std::string key);
	void search_byYear (std::string key);
	void search_byName (std::string key);

	//sort functions
	/*void sort_Newest();
	void sort_Oldest();
	void sort_LatestAdded();
	void sort_OldestAdded();*/


};