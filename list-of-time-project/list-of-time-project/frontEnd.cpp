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


void printLogInForm()
{
	std::cout << "Username"<<std::endl;
	std::cout << "Password" << std::endl;
	getUserInput();
}

void printDataBaseBorder()
{
	char horizontalLine = 196;
	char verticalLine = 179;

	char topLeftCorner = 218;
	char topRightCorner = 191;
	char downLeftCorner = 192;
	char downRightCorner = 217;

	system("cls");
	std::cout << std::endl;

	for (int i = 0; i < 50; i++)
	{
		if (i == 0)
		{
			std::cout << topLeftCorner;
		}
		else if (i == 49)
		{
			std::cout << topRightCorner;
		}
		else {
			std::cout << horizontalLine;
		}
		
	}

	std::cout << std::endl;
	for (int i = 0; i < 23; i++)
	{
		std::cout << verticalLine;
		for (int i = 0; i < 48; i++)
		{
			std::cout << " ";
		}
		std::cout << verticalLine;
		std::cout << std::endl;
	}
	for (int i = 0; i < 50; i++)
	{
		if(i==0)
		{
			std::cout << downLeftCorner;
		}
		else if (i == 49)
		{
			std::cout << downRightCorner;
		}
		else {
			std::cout << horizontalLine;
		}

	}

}

void printDataBase()
{
	printDataBaseBorder();
}

void getUserInput()
{
	std::string usernameInput;
	char userInput = _getch();
	if (userInput == 'a')
	{
		std::cout << "Entering database";
		printDataBase();
	}
	else getUserInput();


}

