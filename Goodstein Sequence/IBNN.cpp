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
				tmp << i.first << "\\cdot";
			tmp << base << "^{" << i.second.to_LaTeX() << "}+";
		}
	return tmp.str();
}

IBNN::IBNN(const mpz_class& num, const mpz_class& base)
{
	this->base = base;

	for (mpz_class i{ num }, j = 0, k; i > 0; i /= base, ++j)
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
	IBNN ret{ to_mpz_class() - 1, base };								//Constructs new IBNN. Easier to implement than processing an IBNN natively.
	change_base(true);
	return ret;															//Returning by value might be more computationaly expensive, but compiler optimizations should alleviate that.
}

std::string IBNN::to_LaTeX() const										//Cleanup.
{
	static const std::regex	rega{ "[0-9]+\\^\\{\\}" },
							regb{ "\\+\\}" },
							regc{ "\\\\cdot1\\+" },
							regd{ "\\^\\{1\\}" };

	auto ret{
		std::regex_replace(
			std::regex_replace(
				std::regex_replace(
					std::regex_replace(to_LaTeX_pre(), rega, "1"), regb, "}"), regc, "+"), regd, "") };
	//ret.pop_back();
	return ret;
}