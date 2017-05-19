#include "stdafx.h"
#include "GS.hpp"


GS::GS(const uint16_t& arg)
{
	for (gs.emplace_back(arg, 2); *gs.back().to_mpz_class() > 0; gs.emplace_back(std::move(*gs.back().next())))
		std::cout << *gs.back().to_mpz_class() << '\n';
}


GS::~GS()
{
	gs.clear();
}

std::ostream& operator<<(std::ostream& os, const GS& gs)
{
	//for (const auto& i : gs.gs)
	//	os << *i.to_mpz_class() << '\n';
	return os;
}