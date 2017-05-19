// Goodstein Sequence.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GS.hpp"


int main(int argc, char* argv[])
{
	std::cout << "Enter the number to calculate...\n";
	uint16_t arg;
	std::cin >> arg;
	GS gs{ arg };
	std::cout << "\nHere's the Goodstein sequence:\n" << gs;
	system("pause");
    return 0;
}

