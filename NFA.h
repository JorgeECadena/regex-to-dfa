#pragma once

#include <iostream>
#include <map>
#include <set>
#include <unordered_set>

class State {
public:
	int id;
	std::map<char, std::set<int>> transitions;

	State(int id);
	~State();

	bool operator==(const State& other) const;
};

// Define the hash function for unordered_set<State>
namespace std {
	template<>
	struct hash<State> {
		size_t operator()(const State& s) const {
			return hash<int>()(s.id);
		}
	};
}

class NFA {
private:
	std::unordered_set<State> states;
	int initialState;
	std::unordered_set<int> finalStates;
public:
	NFA();
	~NFA();

	void addState(int id);
	bool addTransition(int from, char symbol, int to);
	void setInitialState(int id);
	void addFinalState(int id);
	void print();
};
