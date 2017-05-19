#include "stdafx.h"
#include "PowWrap.hpp"

std::unique_ptr<const mpz_class> mpz_pow(const mpz_class& base, const mpz_class& exp)
{
	static const mpz_class mod_max{ MODMAX };	//Calculations are limited to 2^64^2.
	auto ret{ std::make_unique<mpz_class>(0) };
	mpz_powm(ret->get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod_max.get_mpz_t());
	return ret;
}