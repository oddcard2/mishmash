#include <gtest/gtest.h>

#include <map>
#include <vector>
#include <string>

using namespace std;

namespace {

	struct suffix_automation {
		struct node {
			int len; //max len of suffix at this state
			int link; //suffix link
			map<int, int> next; //TODO: template for character type?
		};

		vector<node> st;
		int last = 0;
		int sz = 1;

		suffix_automation(int n) {
			st.resize(2 * n); //2*n-1?
			st[0].link = -1;
			st[0].len = 0;
		}

		suffix_automation(const string& s) : suffix_automation(s.c_str(), s.size()) {
		}

		suffix_automation(const char* s, size_t len) : suffix_automation(int(len)) {
			add(s, len);
		}

		void reset() {
			for (auto &n : st) {
				n.next.clear();
			}
			sz = 1;
			last = 0;
		}

		void add(const string& s) {
			add(s.c_str(), s.size());
		}

		void add(const char* s, size_t len) {
			for (auto i = 0; i < len; ++i)
				add(s[i]);
		}

		void add(int c) {
			auto curr = sz++;
			st[last].next[c] = curr;
			st[curr].link = 0;

			auto i = st[last].link;
			while (i != -1) {
				auto p = &st[i];
				if (!p->next.count(c)) {
					p->next[c] = curr;
				}
				else {
					// p has edge c: p -> q
					auto q_ix = p->next[c];
					if (p->len + 1 == st[q_ix].len) {
						st[curr].link = q_ix;
					}
					else {
						//cloning of q
						auto copy_q_ix = sz++;
						st[copy_q_ix] = st[q_ix]; // copies state q
						st[copy_q_ix].len = p->len + 1; // but fixes len

						p->next[c] = copy_q_ix;

						// sets suffix links for curr and q
						st[curr].link = copy_q_ix;
						st[q_ix].link = copy_q_ix;

						for (auto j = p->link; (j != -1) && st[j].next[c] == q_ix; j = st[j].link)
							st[j].next[c] = copy_q_ix;
					}
					break;
				}
				i = st[i].link;
			}

			st[curr].len = st[last].len + 1;
			last = curr;
		}
	};

	struct emaxx_suffix_automation {
		struct state {
			int len, link;
			map<char, int> next;
		};

		vector<state> st;
		int sz, last;

		emaxx_suffix_automation(int n) {
			sz = last = 0;
			st.resize(2 * n);
			st[0].len = 0;
			st[0].link = -1;
			++sz;
		}

		emaxx_suffix_automation(const string& s) : emaxx_suffix_automation(s.c_str(), s.size()) {
		}

		emaxx_suffix_automation(const char* s, size_t len) : emaxx_suffix_automation(int(len)) {
			add(s, len);
		}

		void add(const string& s) {
			add(s.c_str(), s.size());
		}

		void add(const char* s, size_t len) {
			for (auto i = 0; i < len; ++i)
				add(s[i]);
		}

		void add(char c) {
			int cur = sz++;
			st[cur].len = st[last].len + 1;
			int p;
			for (p = last; p != -1 && !st[p].next.count(c); p = st[p].link)
				st[p].next[c] = cur;
			if (p == -1)
				st[cur].link = 0;
			else {
				int q = st[p].next[c];
				if (st[p].len + 1 == st[q].len)
					st[cur].link = q;
				else {
					int clone = sz++;
					st[clone].len = st[p].len + 1;
					st[clone].next = st[q].next;
					st[clone].link = st[q].link;
					for (; p != -1 && st[p].next[c] == q; p = st[p].link)
						st[p].next[c] = clone;
					st[q].link = st[cur].link = clone;
				}
			}
			last = cur;
		}
	};

	template<class SA>
	void do_simple_test(SA& sa) {
		EXPECT_EQ(1, sa.sz);

		sa.add('a');

		EXPECT_EQ(2, sa.sz);
		EXPECT_EQ(-1, sa.st[0].link);
		EXPECT_EQ(0, sa.st[1].link);
		EXPECT_EQ(1, sa.st[0].next.size());
		EXPECT_EQ(1, sa.st[0].next['a']);
		sa.add('b');

		EXPECT_EQ(3, sa.sz);
		EXPECT_EQ(0, sa.st[2].link);

		EXPECT_EQ(2, sa.st[0].next.size());
		EXPECT_EQ(1, sa.st[1].next.size());


		EXPECT_EQ(1, sa.st[0].next['a']);
		EXPECT_EQ(2, sa.st[0].next['b']);
		EXPECT_EQ(2, sa.st[1].next['b']);
	}

	TEST(suffix_automation_tests, simple_test) {
		suffix_automation sa(2);
		do_simple_test(sa);

		emaxx_suffix_automation esa(2);
		do_simple_test(esa);
	}

	template<class SA>
	void do_abbbbc_test(SA& sa) {
		EXPECT_EQ(10, sa.sz);
		EXPECT_EQ(3, sa.st[0].next.size());

		EXPECT_EQ(1, sa.st[1].next.size());
		EXPECT_EQ(2, sa.st[1].next['b']);
		EXPECT_EQ(1, sa.st[2].next.size());
		EXPECT_EQ(3, sa.st[2].next['b']);
		EXPECT_EQ(1, sa.st[3].next.size());
		EXPECT_EQ(5, sa.st[3].next['b']);
		EXPECT_EQ(1, sa.st[5].next.size());
		EXPECT_EQ(7, sa.st[5].next['b']);
		EXPECT_EQ(1, sa.st[7].next.size());
		EXPECT_EQ(9, sa.st[7].next['c']);
		EXPECT_EQ(0, sa.st[9].next.size());

		EXPECT_EQ(2, sa.st[4].next.size());
		EXPECT_EQ(6, sa.st[4].next['b']);
		EXPECT_EQ(9, sa.st[4].next['c']);
		EXPECT_EQ(2, sa.st[6].next.size());
		EXPECT_EQ(8, sa.st[6].next['b']);
		EXPECT_EQ(9, sa.st[6].next['c']);
		EXPECT_EQ(2, sa.st[8].next.size());
		EXPECT_EQ(7, sa.st[8].next['b']);
		EXPECT_EQ(9, sa.st[8].next['c']);

		EXPECT_EQ(4, sa.st[2].link);
		EXPECT_EQ(6, sa.st[3].link);
		EXPECT_EQ(8, sa.st[5].link);
		EXPECT_EQ(0, sa.st[9].link);

		EXPECT_EQ(0, sa.st[4].link);
		EXPECT_EQ(4, sa.st[6].link);
		EXPECT_EQ(6, sa.st[8].link);
		EXPECT_EQ(8, sa.st[5].link);

		EXPECT_EQ(9, sa.st[0].next['c']);
		EXPECT_EQ(9, sa.st[4].next['c']);
		EXPECT_EQ(9, sa.st[6].next['c']);
		EXPECT_EQ(9, sa.st[7].next['c']);
		EXPECT_EQ(9, sa.st[8].next['c']);
	}

	TEST(suffix_automation_tests, abbbbc_test) {
		suffix_automation sa("abbbbc");
		do_abbbbc_test(sa);

		emaxx_suffix_automation esa("abbbbc");
		do_abbbbc_test(esa);
	}
}