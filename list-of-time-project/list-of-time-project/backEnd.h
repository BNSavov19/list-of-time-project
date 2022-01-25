#pragma once

#include <string>
#include <vector>
#include <Windows.h>

struct DATA;

struct NODE;

enum SORT_CRITERIA;

class LinkedList
{
	public:
		LinkedList();

	public:
		NODE* head;
		NODE* tail;

	public:
		void addEvent(DATA data, std::string name, std::vector<std::string> participants, std::string description);

};

class dbManager
{
	public:
		LinkedList* events;

	public:
		dbManager();

	public:
		std::vector<NODE> eventsToBeDisplayed();
		std::vector<NODE> search(std::string query);
		std::vector<NODE> sort(SORT_CRITERIA criteria);

};