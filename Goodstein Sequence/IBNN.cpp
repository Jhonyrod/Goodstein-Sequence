#include "stdafx.h"
#include "IBNN.hpp"
#include "PowWrap.hpp"

void IBNN::change_base(bool arg = false)
{
	if (!arg)
		++base;
	else
		--base;
	for (auto& i : ibnn)
		i.second.change_base(arg);
}

IBNN::IBNN(const mpz_class& num, const mpz_class& base = 2)
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

std::unique_ptr<const mpz_class>	IBNN::to_mpz_class()	const
{
	if (ibnn.empty())
		return std::make_unique<const mpz_class>(1);

	auto ret{ std::make_unique<mpz_class>(0) };
	for (const auto& i : ibnn)
		*ret += i.first**mpz_pow(base, *i.second.to_mpz_class());
	return ret;
}

std::unique_ptr<const IBNN>			IBNN::next()
{
	change_base();
	auto ret{ std::make_unique<IBNN>(*to_mpz_class() - 1, base) };
	change_base(true);
	return ret;
}
