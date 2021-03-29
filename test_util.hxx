//This file will contain all of the testing functions/templates we might need.
#ifndef ITP298_CAPSTONE_TEST_UTIL_HXX
#define ITP298_CAPSTONE_TEST_UTIL_HXX
template <typename T> void test_print(std::string input,T expected,T result){
	if(expected != result){
		std::cout << input << " test failed expected "<< std::to_string(expected) << " but got " << std::to_string(result) << "."  << std::endl;
	}
	else{
		std::cout << input << " test succeeded." << std::endl;
	}
}
#endif //ITP298_CAPSTONE_TEST_UTIL_HXX
