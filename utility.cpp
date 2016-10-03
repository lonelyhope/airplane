#ifndef ERROR_CODE
#define ERROR_CODE
#include <iostream>
#include <cmath>
#include <time.h>

enum Error_code { success, fail, range_error, underflow, overflow, fatal,
not_present, duplicate_error, entry_inserted, entry_found,
internal_error };

class Random {
	public:
	// Declare random-number generation methods here.
	private:
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
        if (pseudo) seed = 1;
        else seed = time(NULL) % max_int;
        multiplier = 2743;
        add_on = 5923;
        max_int = 88;
    }
	int poisson(double mean) {
		double limit = exp(-mean);
		double product = random_real();
		int count = 0;
		while(product >limit) {
			count++;
			product += random_real();
			
		}
		return count;
	}
	double random_real() {
		double max = max_int + 1.0;
		double temp = reseed();
		if (temp<0) temp = temp+max;
		return temp/max;
	}
}; 
#endif


