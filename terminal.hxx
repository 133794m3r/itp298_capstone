/*
* Basic Terminal Setup stuff.
* By Macarthur Inbody <admin-contact@transcendental.us> 2020
* Licensed AGPLv3
*/
#ifndef _TERMINAL_SETUP_
#include <limits>
void move_and_clear_terminal(unsigned int lines_up){
	printf("\x1b[%dF\x1b[0J", lines_up);
}

void move_and_clear_down(unsigned short line){
	printf("\x1b[%dF\x1b[0J",line);
}

void clear_current_line(){
	printf("\x1b[2K");
}
void clear_lines(unsigned short start_line, unsigned short lines){
	printf("\x1b[%d;1H",start_line);
	for(unsigned short i=0;i<=lines;i++){
		fputs("\x1b[2K",stdout);
		fputs("\x1b[1B",stdout);
	}
	printf("\x1b[%d;1H",start_line);
}

#ifdef _WIN32
#include <windows.h>
		//windows has the system pause command.
		void pause(){
			system("pause");
		}
		//complained that I wasn't capturing the output. So this is just here for that.
		WINBOOL test = SetConsoleMode(GetStdHandle(static_cast<DWORD>(-11)), 7);

#else
	//all other devices I have use to the crappy getchar() version but it works.
	int pause(){
		//clear the rest of cin.
		std::cin.clear();
		std::cout << "press enter/return key to continue... ";
		std::getchar();
		std::cin.clear();
		move_and_clear_terminal(1);
		return 0;
	}

#endif //_WIN32

#include <limits>
#include <cstdio>

//text styles.
enum TEXT_STYLES{RESET ,BOLD,DIM,ITALIC,UNDERLINE,REVERSED,DOUBLE_UNDERLINE=21,UN_BOLD=22,UN_DIM=22,UN_ITALIC,UN_UNDERLINE,UN_REVERSED=27};
//the colors.
enum TEXT_COLORS{RESET_COLOR,
	//foreground colors.
	BLACK_TXT = 30,RED_TXT,GREEN_TXT,YELLOW_TXT,BLUE_TXT,MAGENTA_TXT,CYAN_TXT,WHITE_TXT,
	//"bright" variants
	GRAY_TXT=90,BRIGHT_RED_TXT, BRIGHT_GREEN_TXT, BRIGHT_YELLOW_TXT, BRIGHT_BLUE_TXT, BRIGHT_MAGENTA_TXT, BRIGHT_CYAN_TXT, BRIGHT_WHITE_TXT,
	//background colors.
	BLACK_BG = 40,RED_BG,GREEN_BG,YELLOW_BG,BLUE_BG,MAGENTA_BG,CYAN_BG,WHITE_BG,
	//"bright" variants
	GRAY_BG = 100, BRIGHT_RED_BG, BRIGHT_GREEN_BG, BRIGHT_YELLOW_BG, BRIGHT_BLUE_BG, BRIGHT_MAGENTA_BG, BRIGHT_CYAN_BG, BRIGHT_WHITE_BG
};

void clear_and_move_top(){
	printf("\x1b[2J\x1b[1H");
}

void move_cursor(unsigned int row, unsigned int column){
	printf("\x1b[%d;%dH",row,column);
}

#ifdef __cplusplus
//to make it still work as a C style header. I'll have a version for C eventually.
template <typename T> int proper_input(T &variable, std::string prefix){
	/* I'm checking to see if the return code is set to anything.
	* if it fails to coerce the input into the type that's passed
	* then I'll negate the response code so that it'll loop forever.
	* So if it can't convert the input into the type that's needed it'll fail
	* thus it'll continue the loop.
	*/
//	while(!(std::cin >> variable)){
	while(1){
		std::cin >> variable;
		if(std::cin.eof()){
			variable = T();
			std::cin.clear();
			return -1;
		}
		else if(std::cin.fail()){
			//tell them that the input is invalid.
			std::cout << "You have entered invalid input please try again." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			std::cout << "press enter/return key to continue... ";
			std::getchar();
			std::cin.clear();
			move_and_clear_terminal(3);
			std::cout << "\x1b[1m" << prefix << "\x1b[22m: ";
		}
		else{
			break;
		}
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//	std::cin.clear();
	return 0;
}
#else
//this'll be the C version of the function sometime in the future.
#endif //__cplusplus
#endif //_TERMINAL_SETUP_