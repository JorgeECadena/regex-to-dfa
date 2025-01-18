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
	std::string regex;

	std::cout << "\nAlphabet: ";
	std::cin >> alphabet;

	if (!validateAlphabet(alphabet, alpha))
		return 1;

	std::cout << "RegEx: ";
	std::cin >> regex;

	return 0;
}
