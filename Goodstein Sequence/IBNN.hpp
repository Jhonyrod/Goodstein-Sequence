#pragma once

class IBNN
{
	mpz_class								base;	//Base of the number (Duh).
	std::vector<std::pair<mpz_class, IBNN>>	ibnn;	//Vector holding the multiplier and the exponents (of the exponents of the...).

	void change_base(bool);
public:
	IBNN(const mpz_class&, const mpz_class& = 2);
	~IBNN();

	mpz_class to_mpz_class() const;
	IBNN next();
};

