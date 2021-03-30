/*
* LibCiphers Project
* By Macarthur Inbody <admin-contact@transcendental.us> 2020
* Licensed LGPLv3
*/
#ifndef XOR_RANDOM_LIB
#define XOR_RANDOM_LIB
#ifndef uint64
typedef unsigned long long uint64;
#endif
bool XOR_SHIFT_128_SEEDED=false;


uint64 XOR_SHIFT_128_STATE[2]={0LL,0LL};
//not going to explain the math behind this. It's up to you figure out on your own.
//i'm done commenting.
unsigned long long splitmix64(uint64 seed){
	uint64 z=(seed+0x9E3779B97F4A7C15LL);
	z=(z^(z>>30))*0xBF58476D1CE4E5B9LL;
	z=(z^(z >> 27))*0x94D049BB133111EBLL;
	return z ^ (z >> 32);
}

#ifdef __cplusplus
#include <chrono>
/*
 * templated xorshift128 function.
 *
 * It's type is based upon what the user passes it.
 * Low and high are set to 0 by default so that it can be called with a single argument.
 * And that argument will be the highest value with 0 being the low automatically.
 *
 * If it's included in a C program this won't be called thus making sure that this header works for both C++ and C.
 */
template <typename T> T xorshift128(T low=0, T high=0){
	//get the current state.
	uint64 s1=XOR_SHIFT_128_STATE[0];
	uint64 s0=XOR_SHIFT_128_STATE[1];
	//set the result of the values.
	uint64 result=XOR_SHIFT_128_STATE[0]+XOR_SHIFT_128_STATE[1];
	//set state[0] to s0.
	XOR_SHIFT_128_STATE[0]=s0;
	//set the value of s1 to be s^ (s1 << 23)
	s1 ^= s1 << 23;
	/*
	* We are taking s1 shifting it to the right by 18.
	* take s0 shift it to the right by 5.
	* Then take s1 xor it with s0.
	* then take that intermediate value and xor it with the (s1 >> 18)
	* then take that value and xor it with (s0 >> 5).
	* finall take that value and set it to the state1.
	* s1 XOR s0 XOR (s1 >> 18) XOR (s0 >> 5)
	*/
	XOR_SHIFT_128_STATE[1]=s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5);
	//if high is equal to low then set high to low and keep low  as zero.
	if(high == 0 && low != 0){
		high=low;
		low=0;
	}
	else if(high == 0 && low == 0){
		high = (T)UINT64_MAX;
	}
	return low+((high-low)*((double)result/ UINT64_MAX));
}
template <typename T, typename U> U xorshift128(T low=0, U high=0){
	//get the current state.
	uint64 s1=XOR_SHIFT_128_STATE[0];
	uint64 s0=XOR_SHIFT_128_STATE[1];
	//set the result of the values.
	uint64 result=XOR_SHIFT_128_STATE[0]+XOR_SHIFT_128_STATE[1];
	//set state[0] to s0.
	XOR_SHIFT_128_STATE[0]=s0;
	//set the value of s1 to be s^ (s1 << 23)
	s1 ^= s1 << 23;
	XOR_SHIFT_128_STATE[1]=s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5);
	if(high == 0 && low != 0){
		high=low;
		low=0;
	}
	else if(high == 0 && low == 0){
		high = UINT64_MAX;
	}
	return low+((high-low)*((double)result/ UINT64_MAX));
}

//this is the C++ version because I'm using chrono. The C version using the same function.
void s_xor_128(uint64 seed=0){
	//if we've already seeded it, there's no reason to do it again, if the seed is 0 then they're just calling it to make
	//sure that it's seeded. But if the seed is not
	if(!XOR_SHIFT_128_SEEDED || seed != 0) {
		//make the seed be the current time since epoch in milliseconds.
		seed = (seed == 0) ? static_cast<uint64>(std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1))
						   : seed;
		//initalize the state with the seed through the splitmix64 function.
		XOR_SHIFT_128_STATE[0] = splitmix64(seed);
		//take the seed and modify it by a bit and reuse it again.
		XOR_SHIFT_128_STATE[1] = splitmix64(seed << 1);
		//select how many times we're going to "warm-up" our PRNG. It's from 4->32. This adds a tiny bit of extra randomness.
		size_t iters = ((seed & 7) + 1) << 2;
		//unsigned long long rnd;
		for (size_t i = 0; i < iters; i++) {
			//i'm just capturing it just so that I don't get that warning.
			xorshift128(1,1);
		}
		XOR_SHIFT_128_SEEDED=true;
	}

}


#else //__cplusplus
#include <time.h>
//non templated version for the full width uint64 always.
//not recommenting this bit.
//this is the C++ version because I'm using chrono. The C version using the same function.
void s_xor_128(uint64 seed=0){

	//if we've already seeded it, there's no reason to do it again, if the seed is 0 then they're just calling it to make
	//sure that it's seeded. But if the seed is not
	if(!XOR_SHIFT_128_SEEDED || seed != 0) {
		if(seed == 0){
			struct timeval tv;
			gettimeofday(&tv,NULL);
			seed = (tv.sec << 16) | tv.tv_usec;
		}
		//initalize the state with the seed through the splitmix64 function.
		XOR_SHIFT_128_STATE[0] = splitmix64(seed);
		//take the seed and modify it by a bit and reuse it again.
		XOR_SHIFT_128_STATE[1] = splitmix64(seed << 1);
		//select how many times we're going to "warm-up" our PRNG. It's from 4->32. This adds a tiny bit of extra randomness.
		size_t iters = ((seed & 7) + 1) << 2;
		//unsigned long long rnd;
		for (size_t i = 0; i < iters; i++) {
			//i'm just capturing it just so that I don't get that warning.
			xorshift128();
		}
		XOR_SHIFT_128_SEEDED=true;
	}

}
uint64 xorshift128(){
	//same as above except we dont' change the values and clamp the range down.
	uint64 s1=XOR_SHIFT_128_STATE[0];
	uint64 s0=XOR_SHIFT_128_STATE[1];
	uint64 result=XOR_SHIFT_128_STATE[0]+XOR_SHIFT_128_STATE[1];
	XOR_SHIFT_128_STATE[0]=s0;
	s1 ^= s1 << 23;
	XOR_SHIFT_128_STATE[1]=s1;
	XOR_SHIFT_128_STATE[1]=s1 ^ s0 ^ (s1 >> 17) ^ (s0 >> 26);

	return result;
}
#endif

#endif