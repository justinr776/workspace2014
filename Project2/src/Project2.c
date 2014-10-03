/*
 ============================================================================
 Name        : Project2.c
 Author      : Justin Rohr & Kyle Niewiada
 Version     : 1.1
 Description : FSM Scanner
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef enum {
	start,
	identifier,
	number,
	addop,
	minusop,
	multop,
	divop,
	assignop,
	stmttermop,
	//operator,
	build_id,
	build_num,
	stop
} state;
state transition(state current, char transition) {
	if (current == start) {
		if (isdigit(transition))
			return build_num;
		if (isalpha(transition))
			return build_id;
		if (transition == '+')
			return addop;
		if (transition == '-')
			return minusop;
		if (transition == '*')
			return multop;
		if (transition == '/')
			return divop;
		if (transition == '=')
			return assignop;
		if (transition == ';')
			return stmttermop;
		if (transition == '.')
			return stop;
		if (transition == ' ')
			return start;
	}

	if (current == build_id) {
		if (isdigit(transition))
			return build_id;
		if (isalpha(transition) || transition == '_')
			return build_id;
		if (transition == ' ')
			return identifier;
	}

	if (current == build_num) {
		if (isdigit(transition))
			return build_num;
		if (transition == ' ')
			return number;
		//if (transition == '+' || transition == '-' || transition == '*' || transition == '/')
	}
	return stop;
}

int main(void) {
	state current_state = start;
	char transition_char = ' ';
	do {
		if (current_state == identifier) {
			printf(" � Identifier\n");
			current_state = start;
		} else if (current_state == number) {
			printf(" � Number\n");
			current_state = start;
		} else if (current_state == addop) {
			printf(" � Add Operator\n");
			current_state = start;
		} else if (current_state == minusop) {
			printf(" � Minus Operator\n");
			current_state = start;
		} else if (current_state == multop) {
			printf(" � Multiplication Operator\n");
			current_state = start;
		} else if (current_state == divop) {
			printf(" � Division Operator\n");
			current_state = start;
		} else if (current_state == assignop) {
			printf(" � Assignment Operator\n");
			current_state = start;
		} else if (current_state == stmttermop) {
			printf(" � Statement Termination Operator\n");
			current_state = start;
		}
		scanf("%c", &transition_char);

		if (transition_char != ' ')
			printf("%c", transition_char);

		current_state = transition(current_state, transition_char);

	} while (current_state != stop);

	return EXIT_SUCCESS;
}
