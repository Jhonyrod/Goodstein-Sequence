#pragma once
#include "IBNN.hpp"

class GS
{
	std::vector<IBNN>	gs;
public:
	GS(const uint16_t&);
	~GS();

	friend std::ostream& operator<<(std::ostream&, const GS&);
};