#include "NFA.h"

/* Definitions for State class */

/**
 * @brief Creates a new instance of State
 * 
 * @param int id Id of the new state instance
 * */
State::State(int id) : id(id) {}

/**
 * @brief State class destructor
 * */
State::~State() {}

// Operator overload
bool State::operator==(const State& other) const {
	return id == other.id;
}

/* Definitions for NFA class */

/**
 * @brief Creates a new instance of NFA
 * */
NFA::NFA() : initialState(-1), finalState(-1) {}

/**
 * @brief NFA class destructor
 * */
NFA::~NFA() {}

/**
 * @brief Get an immutable reference to the class attribute 'states'
 *
 * @return const std::unordered_set<State>&
 * */
const std::unordered_set<State>& NFA::getStates() const {
	return states;
}

/**
 * @brief Get the value of the initial state
 *
 * @return int 
 * */
int NFA::getInitialState() {
	return initialState;
}

/**
 * @brief Get the value of the final state
 *
 * @return int
 * */
int NFA::getFinalState() {
	return finalState;
}

/**
 * @brief Adds a new state into the NFA
 *
 * @param int id State's id
 * */
void NFA::addState(int id) {
	states.insert(State(id));
}

/**
 * @brief Adds a new transition from states
 *
 * @param int from Id of the state that transitions from
 * @param char symbol Symbol to use for the transition
 * @param int to Id of the state to transition into
 *
 * @return bool
 * */
bool NFA::addTransition(int from, char symbol, int to) {
	std::unordered_set<State>::iterator it = states.find(State(from));

	// Return false if element doesn't exists
	if(it == states.end())
		return false;

	// Make a copy state
	State copyState = *it;
	copyState.transitions[symbol].insert(to);

	// Replace old state with new one
	states.erase(it);
	states.insert(copyState);

	return true;
}

/**
 * @brief Sets the initial state of the NFA
 *
 * @param int id State id
 * */
void NFA::setInitialState(int id) {
	initialState = id;
}

/**
 * @brief Sets the final state attribute
 *
 * @param int id State id
 * */
void NFA::setFinalState(int id) {
	finalState = id;
}

/**
 * @brief Prints the information of the NFA
 * */
void NFA::print() {
	std::cout << "Initial State: " << initialState << std::endl;
	std::cout << "Final State: " << finalState << std::endl;
	std::cout << "\nTransitions:\n";

	for (const State& state : states) {
		for (const std::pair<char, std::set<int>>& trans : state.transitions) {
			for(int nextState : trans.second) {
				std::cout << "State: " << state.id << " -- "
					<< (trans.first ? trans.first : '#') << " --> "
					<< nextState << std::endl;
			}
		}
	}
}
