/*
* Basic Terminal Setup stuff.
* By Macarthur Inbody <admin-contact@transcendental.us> 2020
* Licensed AGPLv3
*/
#ifndef _TERMINAL_SETUP_
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
	void pause(){
//		//clear the rest of cin.
		std::cin.clear();
//		//ignore everything else in the stream including the new line.
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Press any key to continue... " << std::endl;
		getchar();
	}

#endif //_WIN32

#include <limits>
#include <cstdio>

//text styles.
enum TEXT_STYLES{RESET,BOLD,DIM,ITALIC,UNDERLINE,REVERSED,DOUBLE_UNDERLINE=21,UN_BOLD=22,UN_DIM=22,UN_ITALIC,UN_UNDERLINE,UN_REVERSED=27};
//the colors.
enum TEXT_COLORS{RESET_COLOR,
//foreground colors.
	BLACK_TXT = 30,RED_TXT,GREEN_TXT,YELLOW_TXT,BLUE_TXT,MAGENTA_TXT,CYAN_TXT,WHITE_TXT,
//background colors.
	BLACK_BG = 40,RED_BG,GREEN_BG,YELLOW_BG,BLUE_BG,MAGENTA_BG,CYAN_BG,WHITE_BG
};

void move_and_clear_terminal(unsigned int lines_up){
	printf("\x1b[%dF\x1b[0J", lines_up);
}

void clear_and_move_top(){
	printf("\x1b[2J\x1b[1H");
}

#ifdef __cplusplus
//to make it still work as a C style header. I'll have a version for C eventually.
template <typename T> int proper_input(T &variable){
	/* I'm checking to see if the return code is set to anything.
	* if it fails to coerce the input into the type that's passed
	* then I'll negate the response code so that it'll loop forever.
	* So if it can't convert the input into the type that's needed it'll fail
	* thus it'll continue the loop.
	*/
	while(!(std::cin >> variable)){
		if(std::cin.eof()){
			variable = T();
			std::cin.clear();
			return -1;
		}
		else {
			//tell them that the input is invalid.
			std::cout << "You have entered invalid input please try again." << std::endl;
			pause();
			move_and_clear_terminal(4);
			std::cout << "\x1b[1mSelection\x1b[22m: ";
		}
	}
	return 0;
}
#else
//this'll be the C version of the function sometime in the future.
#endif //__cplusplus
#endif //_TERMINAL_SETUP_