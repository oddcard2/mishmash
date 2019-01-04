#ifndef ALGORITHMS_COMMON_H_
#define ALGORITHMS_COMMON_H_

#include <vector>
using namespace std;

////////////
typedef long long ll;

typedef vector<int> vi;

typedef pair<int, int> pii;
typedef tuple<int, int, int> tri;

#define rn\
int n; cin>>n;

#define rvi(name, count)\
vi name(count);\
for (int i = 0; i < count; i++) cin >> name[i];

#define rvn \
int n; cin >> n;\
vi v(n); \
for (int i = 0; i < n; i++) cin >> v[i];

#define rvn1 \
int n; cin >> n;\
vi v(n+1); \
for (int i = 0; i < n; i++) cin >> v[i+1];


////////////

#endif

