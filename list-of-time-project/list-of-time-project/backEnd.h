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
	NEWEST,
	OLDEST,
	LATEST_ADDED,
	OLDEST_ADDED
};


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

	const std::map<SELECTED_SORT, void(Manager::*)()> m_soryMap{
		{SELECTED_SORT::NEWEST, &Manager::sort_Newest},
		{SELECTED_SORT::OLDEST, &Manager::sort_Oldest},
		{SELECTED_SORT::LATEST_ADDED, &Manager::sort_LatestAdded},
		{SELECTED_SORT::OLDEST_ADDED, &Manager::sort_OldestAdded},
	}

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

	void sort_Newest();
	void sort_Oldest();
	void sort_LatestAdded();
	void sort_OldestAdded();


};