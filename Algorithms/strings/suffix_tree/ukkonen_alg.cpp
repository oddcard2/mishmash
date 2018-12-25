#include <gtest/gtest.h>

#include <map>
#include <functional>
#include <algorithm>


using namespace std;

namespace {

	//http://e-maxx.ru/algo/ukkonen
	//with modifications
	/***********************/
	template<typename S>
	struct emaxx_ukkonen {
		vector<S> s;
		int n;

		emaxx_ukkonen(int maxn) : ptr(0, 0) {

		}

		struct node {
			//[l,r)
			int l, r, par, link;
			map<S, int> next;

			node(int l = 0, int r = 0, int par = -1)
				: l(l), r(r), par(par), link(-1) {}
			//edge len to parent
			int len() { return r - l; }
			//child node for c or -1 if no child 
			int &get(char c) {
				if (!next.count(c))  next[c] = -1;
				return next[c];
			}
			bool is_leaf() { return next.empty(); }
		};
		vector<node> t;
		int sz;

		struct state {
			int v, pos; //node and offset on edge from parent)
			state(int v, int pos) : v(v), pos(pos) {}
		};
		state ptr;

		/**
		 * gets state for [l,r) substring start
		 * \returns state with v == -1 if no such position found 
		 */
		state go(state st, int l, int r) {
			while (l < r) {
				if (st.pos == t[st.v].len()) { //need to go futher, edge is processed
					st = state(t[st.v].get(s[l]), 0);
					if (st.v == -1) //no such path for the letter s[l], stop here  
						return st;
				}
				else { //on edge
					if (s[t[st.v].l + st.pos] != s[l])
						return state(-1, -1); //no symbol s[l] in the edge
					if (r - l < t[st.v].len() - st.pos)
						return state(st.v, st.pos + r - l); //[l,r) ends on the edge
					l += t[st.v].len() - st.pos; //reads until edge end 
					st.pos = t[st.v].len(); //need to descend below
				}
			}
			return st;
		}

		/**
		 * Creates new vertex on the middle of edge if required
		 * \param st - vertex parent position
		 */
		int split(state st) {
			if (st.pos == t[st.v].len())
				return st.v; //point to current vertex, offset from parent = parent edge length
			if (st.pos == 0)
				return t[st.v].par; //points to parent, offset = 0
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
			if (t[v].link != -1)  return t[v].link; //old vertex, so no need to update suffix link (we increased edge only)
			if (t[v].par == -1)  return 0; //root

			int to = get_link(t[v].par); //parent must have link because it's old internal node 

			//create the new vertex on the next suffix edge if required (delayed suffix link update)
			//we go to below reading the text to get position for splitting
			return t[v].link = split(go(state(to, t[to].len()), t[v].l + (t[v].par == 0), t[v].r));
		}

		void tree_extend(int pos) {
			for (;;) {
				state nptr = go(ptr, pos, pos + 1);
				if (nptr.v != -1) {
					ptr = nptr; //next time starts from first suffix poistion empty rule is used for which
					return; //empty rule applied
				}

				//creates new vertex if required
				int mid = split(ptr);

				//adds new leaf
				int leaf = sz++;
				t[leaf] = node(pos, n, mid);
				t[mid].get(s[pos]) = leaf;

				//go to next suffix using suffix link and updates suffix link inside if required
				ptr.v = get_link(mid);
				ptr.pos = t[ptr.v].len();
				if (!mid)  
					break; //if parent of leaf is root
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
	

	TEST(ukkonen_alg_test, emaxx_test) {
		string s = "xabxa$";
		/***********************/
		emaxx_ukkonen<char> t((int)s.size());
		t.s.assign(begin(s), end(s));
		t.build_tree();
		/***********************/
		
		//TODO: check maps
		EXPECT_EQ(9, t.sz);
		EXPECT_EQ(4, t.t[0].next.size());
		EXPECT_EQ(1, t.t[0].next.count('x'));
		EXPECT_EQ(1, t.t[0].next.count('a'));
		EXPECT_EQ(1, t.t[0].next.count('b'));
		EXPECT_EQ(1, t.t[0].next.count('$'));
	}

	TEST(ukkonen_alg_test, get_all_suffixes_test) {
		string s = "xabxa$";

		vector<string> suffixes;
		/***********************/
		emaxx_ukkonen<char> t((int)s.size());
		t.s.assign(begin(s), end(s));
		t.build_tree();
		/***********************/
		vector<bool> used(t.t.size()); ///t.size()!
		function<void(int,string)> dfs = [&](int v, string suf) {
			used[v] = 1;

			//we can check $ at the end of suf
			//there may be no transition for $ in node, $ may be part of leaf
			bool is_leaf = t.t[v].is_leaf();
			int l = t.t[v].l;
			int len = t.t[v].len();
			suf.append(s.substr(l, len));
			if (is_leaf)
				suffixes.push_back(suf);

			for (const auto& u : t.t[v].next) {
				if (used[u.second])
					continue;
				
				dfs(u.second, suf);
			}
		};

		dfs(0, "");

		sort(begin(suffixes), end(suffixes), [](const string& s1, const string s2) { return s1.size() < s2.size(); });
		ASSERT_EQ(6, suffixes.size());
		ASSERT_EQ("$", suffixes[0]); //!!
		EXPECT_EQ("a$", suffixes[1]);
		EXPECT_EQ("xa$", suffixes[2]);
		EXPECT_EQ("bxa$", suffixes[3]);
		EXPECT_EQ("abxa$", suffixes[4]);
		EXPECT_EQ("xabxa$", suffixes[5]);

	}

	TEST(ukkonen_alg_test, substring_search_test) {
		string s = "xabxahaaxxhxa$";
		string sub = "haaxx";

		/***********************/
		emaxx_ukkonen<char> t((int)s.size());
		t.s.assign(begin(s), end(s));
		t.build_tree();
		/***********************/

		vector<bool> used(t.t.size()); ///t.size()!
		int pos = -1;
		int depth = 0;
		int offset = 0;
		int len = (int)sub.size();
		function<void(int)> dfs = [&](int v) {
			used[v] = 1;

			depth += t.t[v].len();
			int checkn = min(t.t[v].len(), len - offset);
			if (!equal(begin(s) + t.t[v].l, begin(s) + t.t[v].l + checkn, begin(sub) + offset, begin(sub) + offset + checkn))
				return;

			if (offset < len)
				offset += checkn;
			bool is_leaf = t.t[v].is_leaf();
			if (is_leaf && offset == len) {
				pos = t.n - depth;
			}

			for (const auto& u : t.t[v].next) {
				if (used[u.second] || pos != -1)
					continue;

				if (offset == len || u.first == sub[offset])
					dfs(u.second);
			}

			depth -= t.t[v].len();
		};

		dfs(0);

		EXPECT_EQ(5, pos);

		sub = "haaxxa";
		pos = -1;
		depth = 0;
		offset = 0;
		len = (int)sub.size();

		dfs(0);
		EXPECT_EQ(-1, pos);
	}

	TEST(ukkonen_alg_test, longest_common_substring_test_ok) {
		string s1 = "xabxahaaxxhxa";
		string s2 = "hgfxahaaxthxa";
		string ans = "xahaax";

		string s = s1 + '$' + s2 + '#';

		/***********************/
		emaxx_ukkonen<char> t((int)s.size());
		t.s.assign(begin(s), end(s));
		t.build_tree();
		/***********************/

		vector<bool> used(t.t.size()); ///t.size()!
		vector<pair<int, int>> posv(t.t.size());
		int depth = 0;
		int first_len = s1.length();

		function<pair<int,int>(int)> dfs_init = [&](int v) {
			used[v] = 1;

			pair<int, int> pos{ -1,-1 };

			depth += t.t[v].len();
			bool is_leaf = t.t[v].is_leaf();
			int start = t.n - depth;
			if (is_leaf) {
				if (start < first_len) {
					pos.first = start;
				}
				else {
					pos.second = start;
				}
			}

			for (const auto& u : t.t[v].next) {
				if (used[u.second])
					continue;
				auto cpos = dfs_init(u.second);
				if (cpos.first != -1)
					pos.first = cpos.first;
				if (cpos.second != -1)
					pos.second = cpos.second;
			}

			posv[v] = pos;

			depth -= t.t[v].len();
			return pos;
		};

		dfs_init(0);

		fill(begin(used), end(used), 0);
		depth = 0;
		int mx_depth = 0;
		pair<int, int> mx_pos;
		function<void(int)> dfs_search = [&](int v) {
			used[v] = 1;

			depth += t.t[v].len();

			if (depth > mx_depth && posv[v].first >= 0 && posv[v].second >= 0) {
				mx_depth = depth;
				mx_pos = posv[v];
			}

			for (const auto& u : t.t[v].next) {
				if (used[u.second])
					continue;

				dfs_search(u.second);
			}

			depth -= t.t[v].len();
		};

		dfs_search(0);

		ASSERT_EQ(ans.size(), mx_depth);
		EXPECT_EQ(3, mx_pos.first);
		EXPECT_EQ(3, mx_pos.second - s1.size() - 1 /*$*/);
	}

	TEST(ukkonen_alg_test, longest_common_substring_test_fail) {

	}

	TEST(ukkonen_alg_test, longest_common_substring_first_index) {
		//optimization to get first index
	}

	TEST(ukkonen_alg_test, ed5f_test) {
		//https://codeforces.com/contest/616/problem/F
	}

	/***********************/

	//https://codeforces.com/blog/entry/16780
	//with modifications
	/***********************/
	struct ukkonen_tree
	{
		const int inf = int(1e9);
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

	TEST(ukkonen_alg_test, cf_impl_test) {
		//for some reason second implementation from CF doesn't work

		/*int str_len = 6;

		string s = "xabxa$";
		ukkonen_tree t(6);
		for (int i = 0; i < s.size(); i++)
			t.add_letter(s[i]);*/
	}
}