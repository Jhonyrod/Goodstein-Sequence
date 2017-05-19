#include "stdafx.h"
#include "IBNN.hpp"

void IBNN::change_base(bool arg = false)
{
	if (!arg)
		++base;
	else
		--base;
	for (auto& i : ibnn)
		i.second.change_base(arg);
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
	if (ibnn.empty())
		return ret;

	for (const auto& i : ibnn)
	{
		mpz_class j{ 1 };
		for (mpz_class k{ 0 }; k < i.second.to_mpz_class(); ++k)
			j *= base;
		ret += i.first*j;
	}
	return ret;
}

IBNN IBNN::next()
{
	change_base();
	IBNN ret{ to_mpz_class() - 1, base };
	change_base(true);
	return ret;
}