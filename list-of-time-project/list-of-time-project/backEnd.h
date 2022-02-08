#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <conio.h>

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
		std::ifstream m_eventsData;

	public:
		LinkedList();

		void addEvent(int day, int month, int year, std::string name, std::string description);

	private:
		void readData();

};

class Manager {

	public:
		Manager(LinkedList* linkedList);
	
	public:
		LinkedList* m_linkedList;
		std::vector<NODE*> eventsForDisplayment;

	public:
		//void update();
		void eventsToBeDisplayed(unsigned int startIndex);
		
};