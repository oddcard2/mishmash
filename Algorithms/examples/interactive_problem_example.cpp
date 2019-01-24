/*
//https://codeforces.com/contest/1104/problem/D

bool game() {
	//cout << "? x y" << '\n' << std::flush;
	//cin >> ans
	//ans x (x>=y) or y (x<y) or e (>60 requests)
	//! a

	//1. find segment with the only 0 inside
	int l = 0, r = 1;
	int is_more = false; //f(r) > f(l)
	string ans;
	do {
		cout << "? " << l << " " << r << '\n' << std::flush;
		cin >> ans;
		if (ans == "e")
			return false;

		is_more = ans == "y";
		if (is_more) {
			l = r;
			r *= 2;
		}
	} while (is_more);

	//2. find 2 subseq elems x1>=x2
	while (l + 1 < r) {
		int mid = (l + r) / 2;

		cout << "? " << l << " " << mid << '\n' << std::flush;
		cin >> ans;
		if (ans == "e")
			return false;

		if (ans == "x") {//l>=mid
			r = mid;
		}
		else {
			l = mid;
		}
	}

	cout << "! " << r << '\n' << std::flush;

	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	while (1) {
		string cmd;
		cin >> cmd;

		if (cmd == "start") {
			if (!game())
				break;
		}
		else if (cmd == "mistake" || cmd == "end") {
			break;
		}
	}
	
	return 0;
}

*/