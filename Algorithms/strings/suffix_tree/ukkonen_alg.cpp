#include <map>
#include <gtest/gtest.h>
#include <map>

using namespace std;

namespace {

	//http://e-maxx.ru/algo/ukkonen
	//with modifications
	/***********************/
	struct emaxx_ukkonen {
		string s;
		int n;

		emaxx_ukkonen(int maxn) : ptr(0, 0) {

		}

		struct node {
			int l, r, par, link;
			map<char, int> next;

			node(int l = 0, int r = 0, int par = -1)
				: l(l), r(r), par(par), link(-1) {}
			int len() { return r - l; }
			int &get(char c) {
				if (!next.count(c))  next[c] = -1;
				return next[c];
			}
		};
		vector<node> t;
		int sz;

		struct state {
			int v, pos;
			state(int v, int pos) : v(v), pos(pos) {}
		};
		state ptr;

		state go(state st, int l, int r) {
			while (l < r)
				if (st.pos == t[st.v].len()) {
					st = state(t[st.v].get(s[l]), 0);
					if (st.v == -1)  return st;
				}
				else {
					if (s[t[st.v].l + st.pos] != s[l])
						return state(-1, -1);
					if (r - l < t[st.v].len() - st.pos)
						return state(st.v, st.pos + r - l);
					l += t[st.v].len() - st.pos;
					st.pos = t[st.v].len();
				}
				return st;
		}

		int split(state st) {
			if (st.pos == t[st.v].len())
				return st.v;
			if (st.pos == 0)
				return t[st.v].par;
			node v = t[st.v];
			int id = sz++;
			t[id] = node(v.l, v.l + st.pos, v.par);
			t[v.par].get(s[v.l]) = id;
			t[id].get(s[v.l + st.pos]) = st.v;
			t[st.v].par = id;
			t[st.v].l += st.pos;
			return id;
		}

		int get_link(int v) {
			if (t[v].link != -1)  return t[v].link;
			if (t[v].par == -1)  return 0;
			int to = get_link(t[v].par);
			return t[v].link = split(go(state(to, t[to].len()), t[v].l + (t[v].par == 0), t[v].r));
		}

		void tree_extend(int pos) {
			for (;;) {
				state nptr = go(ptr, pos, pos + 1);
				if (nptr.v != -1) {
					ptr = nptr;
					return;
				}

				int mid = split(ptr);
				int leaf = sz++;
				t[leaf] = node(pos, n, mid);
				t[mid].get(s[pos]) = leaf;

				ptr.v = get_link(mid);
				ptr.pos = t[ptr.v].len();
				if (!mid)  break;
			}
		}

		void build_tree() {
			sz = 1;
			t.resize(2 * s.size() + 1);
			n = (int)s.size();

			for (int i = 0; i<n; ++i)
				tree_extend(i);
		}
	};
	/***********************/

	//https://codeforces.com/blog/entry/16780
	//with modifications
	/***********************/
	struct ukkonen_tree
	{
		const int inf = 1e9;
		//const int maxn = 1e4; ///
		//char s[maxn];
		string s;
		//outgoing edges list
		vector<map<int, int>> to;// [maxn];
		//int len[maxn], f_pos[maxn], link[maxn];
		vector<int> len, f_pos, link;

		int node, pos;
		int sz, n;

		ukkonen_tree(int max_str_len) {
			int maxn = 2 * max_str_len + 1;
			s.resize(maxn);
			to.resize(maxn);
			len.resize(maxn);
			f_pos.resize(maxn);
			link.resize(maxn);
			len[0] = inf;

			sz = 1;
			n = 0;
			pos = 0;
			node = 0;
		}

		int make_node(int _pos, int _len)
		{
			f_pos[sz] = _pos;
			len[sz] = _len;
			return sz++;
		}

		void go_edge()
		{

			while (pos > len[to[node][s[n - pos]]])
			{
				node = to[node][s[n - pos]]; //saves node
				pos -= len[node];
			}
		}

		void add_letter(int c)
		{
			s[n++] = c;
			pos++;
			int last = 0;
			while (pos > 0)
			{
				go_edge(); //go to tail of current prefix of string
				int edge = s[n - pos]; //next symbol
				int &v = to[node][edge]; //checks if there is edge starts with the current symbol
				//f_pos[v] - first pos of edge which going to v at string
				//len[v] - length of this edge
				int t = s[f_pos[v] + pos - 1]; //
				if (v == 0)
				{
					v = make_node(n - pos, inf);
					link[last] = node;
					last = 0;
				}
				else if (t == c)
				{
					link[last] = node;
					return;
				}
				else
				{
					int u = make_node(f_pos[v], pos - 1);
					to[u][c] = make_node(n - 1, inf);
					to[u][t] = v;
					f_pos[v] += pos - 1;
					len[v] -= pos - 1;
					v = u;
					link[last] = u;
					last = u;
				}
				if (node == 0)
					pos--;
				else
					node = link[node];
			}
		}
	};
	/***********************/

	TEST(ukkonen_alg_test, emaxx_test) {
		int str_len = 6;
		/***********************/
		emaxx_ukkonen t(str_len);
		/***********************/
		
		t.s = "xabxa$"; //from Yuri lecture

		t.build_tree();
	}

	TEST(ukkonen_alg_test, cf_impl_test) {
		//for some reason second implementation from CF doesn't work

		int str_len = 6;

		string s = "xabxa$";
		ukkonen_tree t(6);
		for (int i = 0; i < s.size(); i++)
			t.add_letter(s[i]);
	}

	TEST(ukkonen_alg_test, simple_dfs_test) {
	}

	TEST(ukkonen_alg_test, get_all_suffixes_test) {

	}

	TEST(ukkonen_alg_test, substring_search_test_ok) {
		//gets all indexes of substring in original string
	}

	TEST(ukkonen_alg_test, substring_search_test_fail) {
		//gets all indexes of substring in original string
	}

	TEST(ukkonen_alg_test, longest_common_substring_test_ok) {

	}

	TEST(ukkonen_alg_test, longest_common_substring_test_fail) {

	}

	TEST(ukkonen_alg_test, longest_common_substring_first_index) {
		//optimization to get first index
	}

	TEST(ukkonen_alg_test, ed5f_test) {
		//https://codeforces.com/contest/616/problem/F
	}
}