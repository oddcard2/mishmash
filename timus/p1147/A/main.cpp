#include "bits/stdc++.h"

using namespace std;

////////////

struct plane {
	struct node {
		node() : col(0), q1(nullptr), q2(nullptr), q3(nullptr), q4(nullptr) {}
		int col;
		node *q1, *q2, *q3, *q4;
	};

	plane(int w, int h) : w(w), h(h) {}
	int w, h;
	node root;

	// pay attention on order x1,x2, then y1,y2, not x1,y1,x2,y2! It's easily to see bounds
	void paint(node* n, int tx1, int tx2, int ty1, int ty2, int x1, int x2, int y1, int y2, int col) {
		if (x1 <= tx1 && tx2 <= x2 && y1 <= ty1 && ty2 <= y2) {
			n->col = col;
			return;
		}

		int tw = (tx2 - tx1 + 1);
		int th = (ty2 - ty1 + 1);
		int mx = (tw + 1) / 2;
		int my = (th + 1) / 2;

		// push current color first
		if (n->col != -1) {
			if (tw - mx > 0) {
				if (!n->q1) n->q1 = new node();
				n->q1->col = n->col;
			}
			if (tw - mx > 0 && th - my > 0) {
				if (!n->q2) n->q2 = new node();
				n->q2->col = n->col;
			}
			if (th - my > 0) {
				if (!n->q3) n->q3 = new node();
				n->q3->col = n->col;
			}
			if (!n->q4) n->q4 = new node();
			n->q4->col = n->col;

			n->col = -1;
		}

		if (tw - mx>0 && x2 >= tx1 + mx && y1 <= ty1 + my - 1) { //q1, x2, y1
			if (!n->q1) n->q1 = new node();

			paint(n->q1, tx1 + mx, tx2, ty1, ty1 + my - 1, x1, x2, y1, y2, col);
		}
		if (tw - mx>0 && th - my>0 && x2 >= tx1 + mx && y2 >= ty1 + my) { //q2, x2, y2
			if (!n->q2) n->q2 = new node();

			paint(n->q2, tx1 + mx, tx2, ty1 + my, ty2, x1, x2, y1, y2, col);
		}
		if (th - my>0 && x1 <= tx1 + mx - 1 && y2 >= ty1 + my) { //q3, x1, y2
			if (!n->q3) n->q3 = new node();

			paint(n->q3, tx1, tx1 + mx - 1, ty1 + my, ty2, x1, x2, y1, y2, col);
		}
		if (x1 <= tx1 + mx - 1 && y1 <= ty1 + my - 1) { //q4, x1, y1
			if (!n->q4) n->q4 = new node();

			paint(n->q4, tx1, tx1 + mx - 1, ty1, ty1 + my - 1, x1, x2, y1, y2, col);
		}
	}

	void paint(int x1, int y1, int x2, int y2, int col) {
		paint(&root, 0, w - 1, 0, h - 1, x1, x2, y1, y2, col);
	}

	void stat(node* n, int tx1, int tx2, int ty1, int ty2, vector<int> &s) {
		int tw = (tx2 - tx1 + 1);
		int th = (ty2 - ty1 + 1);
		int mx = (tw + 1) / 2;
		int my = (th + 1) / 2;

		if (n->col != -1) {
			s[n->col] += tw * th;
			return;
		}
		if (n->q1) { //q1
			stat(n->q1, tx1 + mx, tx2, ty1, ty1 + my - 1, s);
		}
		if (n->q2) { //q2
			stat(n->q2, tx1 + mx, tx2, ty1 + my, ty2, s);
		}
		if (n->q3) { //q3
			stat(n->q3, tx1, tx1 + mx - 1, ty1 + my, ty2, s);
		}
		if (n->q4) { //q4
			stat(n->q4, tx1, tx1 + mx - 1, ty1, ty1 + my - 1, s);
		}
	}

	void stat(vector<int> &s) {
		stat(&root, 0, w - 1, 0, h - 1, s);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int a, b, n;
	cin >> a >> b >> n;

	plane p(a, b);

	int i = 0;
	while (++i <= n) {
		int x1, y1, x2, y2, col;
		cin >> x1 >> y1 >> x2 >> y2 >> col;

		p.paint(x1, y1, x2 - 1, y2 - 1, col);
	}

	vector<int> stat(2501);

	p.stat(stat);
	stat[1] += stat[0];

	for (int i = 1; i < 2501; i++) {
		if (stat[i]) {
			cout << i << " " << stat[i] << endl;
		}
	}
	
	return 0;
}