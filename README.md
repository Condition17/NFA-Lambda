# NFA-Lambda
My NFA-Lambda implementation for school
Nondeterministic finite automaton - http://en.wikipedia.org/wiki/Nondeterministic_finite_automaton
Given a NFA that can also have lambda transitions, and a set of words, the program outputs whether or not those words are recognized by the automaton or not.
Input: LNFA.in
	5            -> number of states
	1 2 3 4 5    -> set of symbols that represents the states
	2            -> number of letters of the accepted alphabet
	a b          -> letters of the accepted alphabet
	1
	2
	4 5
	6
	1 . 2
	1 . 3
	2 a 2
	2 b 4
	3 b 3
	3 a 5
	3
	aaa
	aaab
	ba
