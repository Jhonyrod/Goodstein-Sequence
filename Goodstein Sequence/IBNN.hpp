#pragma once

using uint = mpz_class;

class IBNN
{
	uint									base;	//Base of the number (Duh).
	std::vector<std::pair<mpz_class, IBNN>>	ibnn;	//Vector holding the multiplier and the exponents (of the exponents of the...).

	void change_base(bool = false);					//Helper method for next(). Way less expensive than coptuing this object ad returning the new copy.
	std::string to_LaTeX_pre() const;				//Helper method for to_LaTeX().
public:
	IBNN(const mpz_class&, const uint& = 2);		//Only constructor explicitly needed, integers implicitly converts to mpz_class and the rest are fine as defaults.
	~IBNN();										//Just clears ibnn, technically not needed.

	mpz_class to_mpz_class() const;					//Converts the number to plain form.
	IBNN next();									//Calculates the next number in a goodstein sequence.

	std::string to_LaTeX() const;					//Returns a LaTeX compatible string by cleaning the result of to_LaTeX_pre().			
};