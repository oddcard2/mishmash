#include "bits/stdc++.h"

using namespace std;

static uint8_t scramble(char bit, uint8_t* state, int len, int& start) {
	uint8_t z7 = state[start];
	uint8_t z4 = state[(start + 4) % len];

	uint8_t z7z4xor = z7 ^ z4;
	uint8_t res = z7z4xor ^ bit;

	state[start] = res;

	start = (start + 6) % len;
	return res;
}

static uint8_t descramble(char bit, uint8_t* state, int len, int& start) {
	uint8_t z7 = state[start];
	uint8_t z4 = state[(start + 4) % len];

	uint8_t z7z4xor = z7 ^ z4;
	uint8_t res = z7z4xor ^ bit;

	state[start] = bit;

	start = (start + 6) % len;
	return res;
}

int main(int argc, char **argv) {
	/*
	The initial state of the scrambler (seed) shall be
	[1101100], where the leftmost bit specifies the value to put in the first delay element (Z1) in Figure 18-5 (in
	18.2.4), and the rightmost bit specifies the value to put in the last delay element in the scrambler.*/
	//const uint8_t init_state[7] = { 1,1,0,1,1,0,0 };

	uint8_t long_seq[256];
	uint8_t short_seq[256];
	uint8_t res[256];

	for (int i = 0; i < 128; i++) {
		long_seq[i] = 1;
		short_seq[i] = 0;
	}
#if 1
	int start_long = 6;
	uint8_t state_long[7] = { 1,1,0,1,1,0,0 };
	//uint8_t state[7] = { 0,0,0,0,0,0,0 };
	for (int i = 0; i < 128; i++) {
		res[i] = scramble(long_seq[i], state_long, 7, start_long);
	}

	cout << "After scrambling long:" << endl;
	for (int i = 0; i < 128; i++) {
		cout << to_string(res[i]) << endl;
	}


	//uint8_t descr[] = { 1,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   1,   0,   1,   1,   1,   0,   0,   0,   1,  1,   0,   0,   0,   0,   1,   1,   0,   1,   0,   0,   0 };
/*
	uint8_t descr[] = { 1,   1,   1,   1,   1,   0,   0,   1,
		1,   0,   0,   1,   0,   1,   0,   0,
		1,   1,   1,   0,   0,   0,   0,   0,
		1,   0,   0,   0,   0,   1,   0,   0,
		1,   1,   0,   0,   0,   1,   0,   0,
		0,   1,   0,   1,   0,   1,   1,   1,
		0,   0,   0,   1,   1,   0,   0,   0,
		0,   1,   1,   0,   1,   0,   0,   0 };
*/
	/*
	uint8_t descr[] = { 1,   1,   0,   0,   0,   1,   1,   1,



		0,   0,   1,   1,   1,   0,   0,   0,



		0,   0,   0,   1,   0,   0,   1,   0,



		0,   0,   1,   1,   0,   1,   1,   1,



		1,   1,   0,   0,   0,   0,   1,   0,



		1,   0,   0,   0,   0,   0,   0,   0,



		0,   1,   0,   1,   1,   1,   1,   0,



		0,   0,   1,   0,   1,   1,   0,   0,



		1,   0,   0,   1,   1,   1,   1,   1,



		1,   0,   0,   1,   1,   0,   0,   1,



		0,   1,   0,   0,   1,   1,   1,   0,



		0,   0,   0,   0,   1,   0,   0,   0,



		0,   1,   0,   0,   1,   1,   0,   0,



		0,   1,   0,   0,   0,   1,   0,   1,


		0,   1,   1,   1,   0,   0,   0,   1,


		1,   0,   0,   0,   0,   1,   1,   0 };
*/
/*
uint8_t descr[] = { 1,   0,   1,   0,   1,   0,   1,   1,


	0,   1,   0,   0,   1,   0,   0,   0,


	1,   0,   1,   1,   0,   0,   0,   0,


	1,   1,   0,   0,   0,   1,   1,   1,


	0,   1,   0,   1,   0,   0,   0,   1,


	0,   0,   0,   1,   1,   0,   0,   1,


	0,   0,   0,   0,   1,   0,   0,   0,


	0,   0,   1,   1,   1,   0,   0,   1,


	0,   1,   0,   0,   1,   1,   0,   0,


	1,   1,   1,   1,   1,   1,   0,   0,


	1,   0,   0,   1,   1,   0,   1,   0,


	0,   0,   1,   1,   1,   1,   0,   1,


	0,   0,   0,   0,   0,   0,   0,   0,


	1,   0,   1,   0,   0,   0,   0,   1,


	1,   1,   1,   1,   0,   1,   1,   0,


	0,   0,   1,   0,   0,   1,   0,   0 };
*/


uint8_t descr[] = { 1,   0,   1,   0,   1,   0,   1,   1,


0,   1,   0,   0,   1,   0,   0,   0,


1,   0,   1,   1,   0,   0,   0,   0,


1,   1,   0,   0,   0,   1,   1,   1,


0,   1,   0,   1,   0,   0,   0,   1,


0,   0,   0,   1,   1,   0,   0,   1,


0,   0,   0,   0,   1,   0,   0,   0,


0,   0,   1,   1,   1,   0,   0,   1,


0,   1,   0,   0,   1,   1,   0,   0,


1,   1,   1,   1,   1,   1,   0,   0,


1,   0,   0,   1,   1,   0,   1,   0,


0,   0,   1,   1,   1,   1,   0,   1,


0,   0,   0,   0,   0,   0,   0,   0,


1,   0,   1,   0,   0,   0,   0,   1,


1,   1,   1,   1,   0,   1,   1,   0,


0,   0,   1,   0,   0,   1,   0,   0,


0,   0,   0,   0,   1,   1,   1,   0,


0,   1,   1,   1,   0,   0,   0,   1,


1,   0,   0,   1,   1,   0,   1,   0,


1,   0,   1,   0,   0,   0,   0,   0, };
#if 1
	uint8_t descr2[256];
	for (int i = 0; i < sizeof(descr); i++) {
		//descr[i] = !descr[i];
		//descr2[i] = descr[sizeof(descr) - i - 1];
	}
#endif

	uint8_t descr_res[256];
	int start_descrambling_long = 6;
	uint8_t state2[7] = { 0,0,0,0,0,0,0 };
	for (int i = 0; i < sizeof(descr); i++) {
		descr_res[i] = descramble(/*res[i]*/descr[i], state2, 7, start_descrambling_long);
	}

	cout << "After descrambling:" << endl;
	for (int i = 0; i < sizeof(descr); i++) {
		cout << i << " = " << to_string(descr_res[i]) << endl;
	}

	//126 (from 0) 
	uint8_t scrambleRes[] = { 1, 0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		0,
		1,
		0,
		0,
		0,
		1,
		0,
		1 };

	uint8_t scrambling_input[256];
	memcpy(scrambling_input + 1, descr_res, 160);

	scrambling_input[0] = 0;
	scrambling_input[5] = 1;
	scrambling_input[7] = 1;

	uint8_t seq[] = { 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0,
		1,   1,   0,   0,   0,   1,   1,   1,


		0,   1,   0,   1,   0,   0,   0,   1,
	};
	//memcpy(seq, descr + 126, 16);

	int s = 118;
	uint8_t state_curr2[7] = { s & 1,
		(s >> 1) & 1,
		(s >> 2) & 1,
		(s >> 3) & 1,
		(s >> 4) & 1,
		(s >> 5) & 1,
		(s >> 6) & 1 };

	for (int s = 0; s <= 127; s++) {
		int start_pos = 6;
		
		uint8_t state_curr[7] = { s & 1,
								  (s >> 1) & 1,
			(s >> 2) & 1,
			(s >> 3) & 1,
			(s >> 4) & 1,
			(s >> 5) & 1,
			(s >> 6) & 1 };
		
		//uint8_t state_curr[7] = { 1,1,0,1,1,0,0 };

		for (int i = 0; i < sizeof(descr_res); i++) {
			res[i] = scramble(scrambling_input[i], state_curr, 7, start_pos);
		}

		for (int k = 0; k < 10; k++) {
			if (memcmp(res + k, seq, sizeof(seq)) == 0) {
				cout << "Found, seed = " << s << endl;
			}
		}
	}
#else
	int start_short = 6;
	uint8_t state_short[7] = { 0,0,1,1,0,1,1 };
	//uint8_t state[7] = { 0,0,0,0,0,0,0 };
	for (int i = 0; i < 56; i++) {
		res[i] = scramble(short_seq[i], state_short, 7, start_short);
	}

	cout << "After scrambling short:" << endl;
	for (int i = 0; i < 56; i++) {
		cout << to_string(res[i]) << endl;
	}


	int start_descrambling_short = 6;
	uint8_t state3[7] = { 0,0,0,0,0,0,0 };
	for (int i = 0; i < 128; i++) {
		res[i] = descramble(res[i], state3, 7, start_descrambling_short);
	}
#endif


	
	return 0;
}