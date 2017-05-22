#include "stdafx.h"
#include "IBNN.hpp"

void IBNN::change_base(bool arg)
{
	if (!arg)
		++base;
	else
		--base;
	for (auto& i : ibnn)
		i.second.change_base(arg);
}

std::string IBNN::to_LaTeX_pre() const
{
	std::ostringstream tmp;
	if (!ibnn.empty())
		for (const auto& i : ibnn)
		{
			if (i.first > 1)
				tmp << i.first << "*";
			tmp << base << "^{" << i.second.to_LaTeX_pre() << "}+";
		}
	return tmp.str();
}

IBNN::IBNN(const mpz_class& num, const uint& base)
{
	this->base = base;
	for (auto i{ num }, j{ 0_mpz }, k{ 0_mpz }; i > 0; i /= base, ++j)
		if ((k = i%base) > 0)
			ibnn.push_back(std::make_pair(k, IBNN{ j, base }));
}

IBNN::~IBNN()
{
	ibnn.clear();
}

mpz_class IBNN::to_mpz_class() const
{
	mpz_class ret{ 0 };
	if (!ibnn.empty())
		for (const auto& i : ibnn)										//Iterate throught ibnn.
		{
			mpz_class j{ 1 };
			for (mpz_class k{ 0 }; k < i.second.to_mpz_class(); ++k)	//Simple exponentiation routine.
				j *= base;
			ret += i.first*j;
		}
	return ret;
}

IBNN IBNN::next()
{
	change_base();
	auto ret{ IBNN{ to_mpz_class() - 1, base } };						//Constructs new IBNN. Easier to implement than processing an IBNN natively.
	change_base(true);
	return ret;															//Returning by value might be more computationaly expensive, but compiler optimizations should alleviate that.
}

std::string IBNN::to_LaTeX() const										//Cleanup.
{
	static const std::regex	rea{ "\\d+\\^\\{\\}" },
							reb{ "\\+\\}" },
							rec{ "\\^\\{1\\}" },
							red{ "\\*1(?!\\d)" };

	auto ret
	{
		std::regex_replace(
			std::regex_replace(
				std::regex_replace(
					std::regex_replace(to_LaTeX_pre(),rea,"1"),reb,"}"),rec,""),red,"")
	};
	ret.pop_back();
	return ret;
}