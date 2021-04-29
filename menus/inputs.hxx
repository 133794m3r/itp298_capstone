/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/5/21.
*
*/

#ifndef ITP298_CAPSTONE_INPUTS_HXX
#define ITP298_CAPSTONE_INPUTS_HXX
#include "../includes.hxx"
/**
 * Checks that hte user's input is a valid one within the options.
 *
 * @param min Lowest possible
 * @param max Highest possible
 * @param prefix Prefix message to show before player input.
 * @return The option that they chose.
 */
unsigned int valid_option(unsigned int min=1,unsigned int max=1,std::string prefix="Selection"){
	unsigned int option;
	//infinite loop is best way to enforce the options.
	int res;
	//this way it can be called with a single argument
	if(max < min)
		std::swap(min,max);
	//infinite loop until it's good
	while(true) {
		res = proper_input(option,prefix);
		//-1 means EOF was noticed
		if(res == -1)
			//so die
			exit(1);
		//if their option is valid
		if(option >= min && option <= max)
			break;
		//otherwise tell them the valid range
		std::cout << "Enter valid option from " << min << " to " << max << std::endl;
		//make sure they know this
		pause();
		move_and_clear_up(2);
		//show the prefix message
		std::cout << "\x1b[1m" << prefix << "\x1b[22m: ";
	}
	return option;
}

/**
 * Quick and dirty text wrapper
 *
 * @param input The input string
 * @param position The maximum width we can use for each step
 * @param wrap_char
 */
void text_wrap(std::string &input,unsigned int position,char wrap_char=' '){
	if(input.size() < position)
		return;
	size_t found;
	while( (found = input.find_last_of(wrap_char,position)) != input.npos && position < input.size()){
		//change it to a new line
		input.at(found) = '\n';
		//make the starting position be increased by the current found position
		position += found;
	}
}

/**
 * Simple print wrapper
 * @param input Input string
 * @param position position to search for
 * @param end_line call std::endl at the end or not.
 */
void print_wrap(const std::string &input, unsigned int position,bool end_line=false){
	std::string new_string = input;
	if(input.size() < position)
		std::cout << input;
	size_t found;
	while((found = new_string.find_last_of(32,position)) != std::string::npos && position < input.size()){
		new_string.at(found-2) = '\n';
		position += found;
	}
	std::cout << new_string;

	if(end_line)
		std::cout << std::endl;
}

/**
 * Clear the text-box menu
 *
 * @param top The line at which the text menu appears
 * @param lines how many lines tall it is.
 */
void clear_textbox(unsigned short top, unsigned short lines){
	const char blank[54] ={32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
						32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
						32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
						32, 32, 32, 32, 32, 32, 32, 32, 32, 32};

	for(unsigned short i=0;i<lines;i++){
		move_cursor(top+i,2);
		std::cout << blank;
	}
}
#endif //ITP298_CAPSTONE_INPUTS_HXX
