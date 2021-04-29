/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
* Created on 4/27/21.
*
*/

#ifndef ITP298_CAPSTONE_MENU_HXX
#define ITP298_CAPSTONE_MENU_HXX

#include <algorithm>
#include "inputs.hxx"

class Menu {
  private:
	static void _show_menu_message(const std::string& message,unsigned short start_y,unsigned short num_lines){

		std::string new_str = message;
		//the padding string we'll use to pad all inputs until the end.
		std::string padding(53, ' ');
		move_cursor(start_y, 3);
		size_t message_len = message.size();
		//lots of complex text-wrapping ensues.
		if (message_len < 55) {
			std::replace(new_str.begin(), new_str.end(), ';', ' ');
			std::cout << new_str << padding.substr(0, 53 - message_len);
			move_cursor(start_y+1, 3);
			std::cout << padding;
		}
		else {
			text_wrap(new_str, 53, ';');
			std::replace(new_str.begin(), new_str.end(), ';', ' ');
			size_t new_line = new_str.find('\n');
			std::cout << new_str.substr(0, new_line - 1) << padding.substr(0, 53 - new_line);
			move_cursor(start_y+1, 3);
			size_t line_2 = new_str.find('\n', new_line + 1);
			if (line_2 != std::string::npos) {
				std::cout << new_str.substr(new_line + 1, line_2 - (new_line + 1))
						  << padding.substr(0, 53 - (line_2 - new_line));
				move_cursor(start_y+2, 3);
				std::cout << new_str.substr(line_2 + 1) << padding.substr(0, 53 - (message_len - line_2));
			}
			else {
				std::cout << new_str.substr(new_line + 1)
						  << padding.substr(0, 53 - (message_len - new_line + 1));
			}
		}
		move_cursor(start_y+num_lines+1, 1);
		clear_current_line();
	}
  protected:
	unsigned short menu_start;
	unsigned short menu_lines;
  public:
	Menu(unsigned short start, unsigned short lines){
		this->menu_start = start;
		this->menu_lines = lines;
	}
	/**
 	* Static method to print the strings in the text-box.
	 * Make make this part of the base Menu class once I get to it.
	 *
	 * @param message The message to be displayed.
	 */
	void show_menu_message(const std::string& message) const {
		_show_menu_message(message,this->menu_start, this->menu_lines);
	}
};


#endif //ITP298_CAPSTONE_MENU_HXX
