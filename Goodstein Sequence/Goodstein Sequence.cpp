// Goodstein Sequence.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IBNN.hpp"


int main(int argc, char* argv[])
{
	std::cout << "Enter the number to calculate...\n";
	unsigned short arg;
	std::cin >> arg;
	std::cout << "\nHere's the Goodstein sequence:\n";
#pragma loop( hint parallel( 8 ) )
	for (IBNN ibnn{ arg };ibnn.to_mpz_class() > 0; ibnn=ibnn.next())
		std::cout << ibnn.to_mpz_class() << '\n';
    return 0;
}