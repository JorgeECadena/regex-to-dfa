#pragma once

#include <iostream>
#include "NFA.h"

class Parser {
private:
	const std::string& regex;
	NFA& nfa;
	size_t position;

	void parseExpression();
	void parseTerm();
	void parseFactor();
	void parseCharacter();
public:
	Parser(const std::string& regex, NFA& nfa);
	~Parser();

	void parse();
};
