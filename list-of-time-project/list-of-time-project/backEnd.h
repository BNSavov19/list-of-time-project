#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

#define MAX_EVENTS_FOR_DISPAYMENT 10


struct DATA {
	int day;
	int month;
	int year;
	std::string name;
	std::vector<std::string> participants;
	std::string description;
};

struct NODE {
	DATA data;
	NODE* next = nullptr;
};

class LinkedList {

	public:
		NODE* head;
		NODE* tail;

	public:
		LinkedList();

		void addEvent(int day, int month, int year, std::string name, std::vector<std::string> participants, std::string description);
		
		void display();

};

class Manager {

	public:
		Manager(LinkedList* linkedList);
	
	public:
		LinkedList* events;
		std::vector<NODE*> eventsForDisplayment;

	public:
		void update();

	public:
		void eventsToBeDisplayed(unsigned int startIndex);
};