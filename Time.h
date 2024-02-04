#ifndef Time_h 
#define Time_h 

#include <chrono>

namespace Time
{

	extern std::chrono::steady_clock::time_point start; 
	extern double time; 
	extern double dt;
};

#endif