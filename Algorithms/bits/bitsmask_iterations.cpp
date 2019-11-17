#include <gtest/gtest.h>
#include <common.h>

// increasing order, useful for DP
template<typename T>
void init_bits(vector<T>& vals, vector<T>& bit_vals, int bits_count, int offset = 0) {
	for (T b = 0; b < (T)bits_count; b++) {
		vals[T(1) << b] = bit_vals[b + offset];
	}
}

template<typename T>
void mask_recalc(int mask_len, vector<T>& vals) {
	T all_bits_mask = ((T(1) << mask_len) - 1);
	for (T v = 1; v < (T(1) << mask_len); v++) {
		for (T b = 0; b < (T)mask_len; b++) {
			if (v & (T(1) << b)) {
				vals[v] = vals[(v & ~(T(1) << b)) & all_bits_mask] + vals[(T(1) << b)];
				break;
			}
		}
	}
}

// all submasks of the mask - http://e-maxx.ru/algo/all_submasks

namespace {
	TEST(bitmask_iterations_tests, increase_test) {



	}
}