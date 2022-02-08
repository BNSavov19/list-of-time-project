#pragma once

#include "backEnd.h"
#include "Tabulate.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

//function to print Log In form
//function to check Log In form

//function to start displaying DataBase
//function to awaitUserInput
//function to respond to userInput
	//"+" - add event
	//"search" - search for events based on input
	//"sort" - sort events based on criteria0

template<typename char_type>
auto fast_print(const std::basic_string<char_type>& sss) -> void
{
	HANDLE const output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	const auto char_count = static_cast<DWORD>(sss.length());
	if constexpr (std::is_same_v<char_type, char>)
		WriteConsoleA(output_handle, sss.c_str(), char_count, nullptr, nullptr);
	else
		WriteConsoleW(output_handle, sss.c_str(), char_count, nullptr, nullptr);
}


class DataBase {
	public:
		DataBase(std::vector<NODE*> &events);

	public:
		unsigned int m_selectedEvent;
		std::vector<NODE*>* m_events;
		tabulate::Table* eventsTable;

	public:
		void innitDataBase();
		void getInput();
};