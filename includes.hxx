/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*
*/

//this file will contain all of the common includes in a single header.
#ifndef ITP298_CAPSTONE_INCLUDES_HXX
#define ITP298_CAPSTONE_INCLUDES_HXX
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#ifdef _WIN32
#include <Windows.h>
#else
//#include <unistd.h>
#endif
#include "terminal.hxx"
#include <string>
#include <iostream>


//only works with a single layer of iterator
template<typename C, typename T = typename C::value_type> unsigned long gen_hash(C const &container){
	//always use the fast types to make sure we don't waste cpu time
	uint_fast32_t prime = 1000000007;
	uint_fast32_t multiplier = 263;
	//has to be an unsigned long long to avoid integer overflow issues.
	uint_fast64_t h = 0;

	for(int i = static_cast<int>(container.size());i >= 0; --i){
		h = ((h * multiplier) + container[i]) % prime;
	}
	return static_cast<unsigned long>(h);
}

template <typename T> std::enable_if_t<std::is_scalar<T>::value,unsigned long> gen_hash(T x){
	unsigned long prime = 1000000007;
	unsigned long multiplier = 263;
	//have to make sure that the value is large enough to avoid overflow issues.
	//also make sure we keep the speed of them.
	uint_fast64_t h = 0;
	uint_fast32_t t = 0;
	uint_fast32_t i = 0;
	//always make sure that the thing is made into the largest possible normal scalar.
	auto num = static_cast<uint_fast64_t>(x);
	while(num > 0){
		h = (h*multiplier + i) % prime;
		num >>=(t*8);
		i = num & 0xff;
		t++;
	}
	return  static_cast<unsigned long>(num % prime);
}
#endif //ITP298_CAPSTONE_INCLUDES_HXX
