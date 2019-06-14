#include <gtest/gtest.h>

#include <cstdint>
#include <map>
#include <functional>
#include <algorithm>

typedef int64_t ll;

using namespace std;

namespace {

	struct suffix_auttomation {
		struct node {
			int len; //max len of suffix at this state
			int link; //suffix link
			map<int, int> c; //TODO: template for character type?
		};

		vector<node> v;
		int last = 0;
		int sz;

		suffix_auttomation (int n) {
			v.resize(2 * n); //2*n-1?
			v[0].link = -1;
			v[0].len = 0;
			sz = 0;
		}

		void add(int c) {
			int curr = ++sz;
			v[curr].len = v[last].len + 1;
			v[last].c[c] = curr;
			
			int i = v[last].link;
			while (i >= 0) {
				auto p = &v[i];
				if (p->c.count(c) == 0) {
					p->c[c] = curr;
				}
				else { //cloning
					int copy_ix = ++sz;

					int orig_ix = p->c[c];
					v[copy_ix] = v[orig_ix]; //copy
					v[copy_ix].len = p->len + 1;
					p->c[c] = copy_ix;

					v[curr].link = copy_ix;
					v[last].link = copy_ix;

					int j = p->link;
					while (j >= 0) {
						if (v[j].c.count(c) == 0)
							break;
						v[j].c[c] = copy_ix;
						j = v[j].link;
					}
					break;
				}

				i = v[i].link;
			}
			last = curr;
		}
	};
}