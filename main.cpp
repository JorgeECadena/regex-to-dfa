#include <iostream>
#include <cctype>
#include <unordered_set>

/**
 * @brief Validates that alphabet is does not have any non-alphabetical
 * characters. If it does not have non-alphabetical characters returns
 * true. If it has non-alphabetical characters returns false
 *
 * @param const std::string& alphabet Reference to a string value
 * @param std::unordered_set<char>& vC Reference to an unordered set
 *
 * @return bool
 * */
bool validateAlphabet(const std::string& alphabet, std::unordered_set<char>& alpha) {
	for (char c : alphabet) {
		if (!isalpha(c)) {
			std::cerr << "Character: " << c << " is not valid!\n";
			return false;
		}

		if (alpha.find(c) != alpha.end()) {
			std::cerr << "Character: " << c << " cannot be repeated!\n";
			return false;
		}

		alpha.insert(c);
	}

	return true;
}

/**
 * @brief Return a state depending on the received character's value
 *
 * @param const& char c Character to validate
 * @param const std::unordered_set<char>& alpha Alphabet of the expression
 *
 * @return unsigned short
 * */
unsigned short convert(const char& c, const std::unordered_set<char>& alpha) {
	// State 0 is for any character that's part of the alpha set
	// State 1 is for '*' or '+' characters only
	// State 2 is for '|' character
	// State 3 is for '(' character
	// State 4 is for ')' character
	// State 5 is for ' ' or '\0' characters
	// State 6 is for any other character not displayed here
	if(alpha.find(c) != alpha.end()) return 0;
	switch (c) {
		case '*' :
		case '+' : return 1;
		case '|' : return 2;
		case '(' : return 3;
		case ')' : return 4;
		case ' ' : 
		case '\0': return 5;
		default  : return 6;
	}
}

bool validateRegex(const std::string& regex) {
	return true;
}

int main() {
	std::unordered_set<char> validChars = {
		'(', 
		')', 
		'+', 
		'*',
		'|'
	};
	std::unordered_set<char> alpha;

	std::string alphabet;
	char regex[256];

	std::cout << "\nAlphabet: ";
	std::cin >> alphabet;

	if (!validateAlphabet(alphabet, alpha))
		return 1;

	std::cout << "RegEx: ";
	std::cin >> regex;

	return 0;
}
