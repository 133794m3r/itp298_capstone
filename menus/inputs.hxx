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
unsigned int valid_option(unsigned int min,unsigned int max){
	unsigned int option;
	//infinite loop is best way to enforce the options.
	int res;
	while(1) {
		res = proper_input(option);
		if(res == -1)
			exit(0);
		if(option > 0 && option < max)
			break;
		std::cout << "Enter valid option from " << min << " to " << max-1 << std::endl;
		pause();
		move_and_clear_terminal(4);
		std::cout << "\x1b[1mSelection: \x1b[22m";
	}
	return option;
}

void text_wrap(std::string &input,unsigned int position,char wrap_char=' '){
	if(input.size() < position)
		return;
	size_t found;
	while( (found = input.find_last_of(wrap_char,position)) != input.npos && position < input.size()){
		input.at(found) = '\n';
		position += found;
	}
}

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
#endif //ITP298_CAPSTONE_INPUTS_HXX
