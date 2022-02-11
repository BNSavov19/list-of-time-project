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


public:
	LinkedList* m_linkedList;
	std::vector<NODE*> eventsForDisplayment;
	std::vector<NODE*> EventsForDisplayment_sorted;
	const std::map<std::string, void(Manager::*)(std::string)> m_queryMap {
		{"date", &Manager::byDate},
		{"day", &Manager::byDay},
		{"month", &Manager::byMonth},
		{"year", &Manager::byYear},
		{"name", &Manager::byName},
	};

public:
	//void update();
	void addEvent(DATA eventData);
	void eventsToBeDisplayed(unsigned int startIndex);

	void byDate (std::string key);
	void byDay  (std::string key);
	void byMonth(std::string key);
	void byYear (std::string key);
	void byName (std::string key);

};