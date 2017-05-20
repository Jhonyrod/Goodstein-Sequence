// Goodstein Sequence.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IBNN.hpp"

void usage(char* argv[])
{
	std::cout << "Usage: " << argv[0] << " [-h|--help] seed(<65536) [iterations]\n";
}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		usage(argv);
		return 0;
	}

	std::stringstream sa{ std::string{ argv[1] } };
	uint16_t arg;
	sa >> arg;

	if (!sa)
	{
		usage(argv);
		return 0;
	}

	if (argc == 3)
	{
		std::stringstream si{ std::string{ argv[2] } };
		si << std::string{ argv[2] };
		uint64_t iter;
		si >> iter;
		if (!si)
		{
			usage(argv);
			return 0;
		}
		decltype(iter) i = 0;
		for (IBNN ibnn{ arg }; ibnn.to_mpz_class() > 0 && i < iter; ++i, ibnn = ibnn.next())
			std::cout << ibnn.to_mpz_class() << '\n';
	}
	else if (argc == 2)
		for (IBNN ibnn{ arg }; ibnn.to_mpz_class() > 0; ibnn = ibnn.next())
			std::cout << ibnn.to_mpz_class() << '\n';
	else
		usage(argv);
    return 0;
}