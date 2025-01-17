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
bool validateAlphabet(const std::string& alphabet, std::unordered_set<char>& vC) {
	for (char c : alphabet) {
		if (!isalpha(c)) {
			std::cerr << "Character: " << c << " is not valid!\n";
			return false;
		}

		if (vC.find(c) != vC.end()) {
			std::cerr << "Character: " << c << " cannot be repeated!\n";
			return false;
		}

		vC.insert(c);
	}

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

	std::string alphabet;
	std::string regex;

	std::cout << "\nAlphabet: ";
	std::cin >> alphabet;

	if (!validateAlphabet(alphabet, validChars))
		return 1;

	return 0;
}
