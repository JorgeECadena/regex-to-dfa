#include "Parser.h"
#include "NFA.h"

/**
 * @brief Create a new Parser instance
 *
 * @param const std::string& regex Regex to parse
 * @param NFA& nfa NFA to modify
 * */
Parser::Parser(const std::string& regex, NFA& nfa) : regex(regex), nfa(nfa), position(0) {}

/**
 * @brief Parser destructor
 * */
Parser::~Parser() {}

/**
 * @brief Start the parsing process
 * */
void Parser::parse() {
	parseExpression();
}

/**
 * @brief 
 * */
void Parser::parseExpression() {
	parseTerm();

	while (position < regex.length() && regex[position] == '|') {
		position++;

		int secondBranchStart = nfa.getFinalState() + 1;
		int firstBranchFinal = nfa.getFinalState();

		parseTerm();

		int newInitial = nfa.getStates().size();
		int newFinal = newInitial + 1;

		nfa.addState(newInitial);
		nfa.addState(newFinal);

		nfa.addTransition(newInitial, '#', nfa.getInitialState());
		nfa.addTransition(newInitial, '#', secondBranchStart);

		nfa.addTransition(firstBranchFinal, '#', newFinal);
		nfa.addTransition(nfa.getFinalState(), '#', newFinal);

		nfa.setInitialState(newInitial);
		nfa.setFinalState(newFinal);
	}
}

/**
 * @brief 
 * */
void Parser::parseTerm() {
	parseFactor();

	while (position < regex.length() && regex[position] != '|' && regex[position] != ')') {
		parseFactor();
	}
}

/**
 * @brief Create the necessary transitions for the operators '*' and '+'
 * */
void Parser::parseFactor() {
	parseCharacter();

	if (position < regex.length() && (regex[position] == '*' || regex[position] == '+')) {
		char op = regex[position++];
		int newInitial = nfa.getStates().size();
		int newFinal = newInitial + 1;
		nfa.addState(newInitial);
		nfa.addState(newFinal);

		if(op == '*') {
			nfa.addTransition(newInitial, '#', nfa.getInitialState());
			nfa.addTransition(nfa.getFinalState(), '#', newFinal);
			nfa.addTransition(newInitial, '#', newFinal);
			nfa.addTransition(nfa.getFinalState(), '#', nfa.getInitialState());
		}
		else if (op == '+') {
			nfa.addTransition(newInitial, '#', nfa.getInitialState());
			nfa.addTransition(nfa.getFinalState(), '#', nfa.getInitialState());
			nfa.addTransition(nfa.getFinalState(), '#', newFinal);
		}

		nfa.setInitialState(newInitial);
		nfa.setFinalState(newFinal);
	}
}

/**
 * @brief Parses concatenation characters
 * */
void Parser::parseCharacter() {
	if (position >= regex.length())
		return;

	char current = regex[position++];

	if (current == '(') {
		parseExpression();
		if(position < regex.length() && regex[position] == ')') 
			position++;
	}
	else {
		// Create states
		int start, end;

		if (nfa.getStates().empty()) {
			start = nfa.getStates().size();
			end = start + 1;
			
			nfa.addState(start);

			nfa.setInitialState(start);
		}
		else if (position >= 3 && regex[position - 2] == '|') {
			start = nfa.getStates().size();
			end = start + 1;

			nfa.addState(start);
		}
		else {
			start = nfa.getFinalState();
			end = nfa.getStates().size();
		}

		nfa.addState(end);

		// Add states transitions
		nfa.addTransition(start, current, end);

		nfa.setFinalState(end);
	}
}
