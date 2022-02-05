#include "frontEnd.h"

//display Log in Form

	//if(login) -> enterDataBase

		//print DataBase
			//call dbManager.eventsToBeDisplayed();
				//print events returned from the function^

		//wait for Input
		//do something based on input
			//"+" -> call dbManager->events.addEvent(userInput);
			//"search" -> call dbManager->search(userInput);
			//"sort" -> establish what sorting criteria to use -> call dbManager->sort(criteria);


auto displayTextField() -> void
{
	std::cout << "|---------|";
}

auto displayLogInForm() -> void
{
	std::cout << "Username: " << std::endl;
	displayTextField();

	std::cout << std::endl;
	
	std::cout << "Password: " << std::endl;
	displayTextField();
}