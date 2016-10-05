#ifndef ERROR_CODE
#define ERROR_CODE
#include <iostream>
#include <cmath>
#include <time.h>
#include <random>
using namespace std;
enum Error_code { success, fail, range_error, underflow, overflow, fatal,
not_present, duplicate_error, entry_inserted, entry_found,
internal_error };
#define GEN_SEED 12
class Random {
	public:
	// Declare random-number generation methods here.
	private:
	    std::mt19937 gen;
	int seed, multiplier, add_on; // constants for use in arithmetic operations
    int max_int;
	public:
	int reseed()
	/* Post: The seed is replaced by a pseudorandom successor. */
	{
	seed = seed * multiplier + add_on;
	return seed;
	}
	Random(bool pseudo = true)
/* Post: The values of seed, add_on, and multiplier are initialized. The seed is
initialized randomly only if pseudo == false. */
    {
        multiplier = 2743;
        add_on = 5923;
        max_int = 88;
        std::mt19937 gen(GEN_SEED);
        if (pseudo) seed = 1;
        else{
            seed = time(NULL) % max_int;
        }

    }
	int poisson(double mean) {
		std::poisson_distribution<> d(mean);
		int t = d(gen);
		gen();
		return t;
	}


	double random_real() {
		double max = max_int + 1.0;
		double temp = reseed();
		if (temp<0) temp = temp+max;
		return temp/max;
	}
};
#endif


