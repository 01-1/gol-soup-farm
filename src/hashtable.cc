// {{{ <<-<<<<=< the optimal template >>=>>>>->>
#include <bits/stdc++.h>  // clang-format off
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
//#define int long long
#define P pair
#define v vector
#define p push
#define e emplace
#define pb push_back
#define eb emplace_back
#define f first
#define s second
#define sz(x) ((int)ssize(x))
#define ben(q) begin(q),end(q)
#define SQ(x) ((x)*(x))
#define frange(i, l, r, k) for(int(i)=(l);(i)<(r);(i)+=(k))
#define fo(i, l, r) frange(i, l, r, 1)
#define f0(i, r) fo(i, 0, r)
#define f1(i, r) fo(i, 1, r)
#define rangerev(i, r, l, k) for(int(i)=(r);(i)>(l);(i)-=(k))
#define ranger(i, r, l) rangerev(i, r, l, 1)
#define fro(i, l, r) ranger(i, (r)-1, (l)-1)
#define fr0(i, r) fro(i, 0, r)
#define TT int TN; cin >> TN; f0(TI, TN)
#define nl << '\n'
#define t template<class T>
#define u using
#define I int
u ll = int64_t; u ull = uint64_t;
u pi = P<I, I>; u vp = v<pi>;
u vi = v<I>;    u v2 = v<vi>;
u v8 = v<uint8_t>; u vl = v<ll>;   
t using uset = unordered_set<T>; template<class K,class U> u umap = unordered_map<K, U>;
u seti  = set<I>;  u mapi  = map<I, I>;
u useti = uset<I>; u umapi = umap<I, I>;
t istream &operator>>(istream &i, v<T> &a) { for (auto &x : a) i >> x; return i; };
t ostream &operator<<(ostream &o, v<T> &a) { for (auto &x : a) o << x << ' '; return o; };
t void Unique(T &a) { a.erase(unique(a.begin(), a.end()), a.end()); }
t bool ckx(T &x, T v) { return v > x && (x = v, 1); }
t bool ckn(T &x, T v) { return v < x && (x = v, 1); }
#define rep(i,a,b) fo(i,a,b)
#define all(x) ben(x)
#undef t
#undef u
#undef I
// clang-format on
// }}} 998244353 1000000007

struct chash { // large odd number for C
	const uint32_t C = 1337272727;
	int operator()(int x) const { return __builtin_bswap32(x*C); }
};
//__gnu_pbds::gp_hash_table<ll,int,chash> h({},{},{},{},{1<<16});

const int CONST = 42069;

int run(vi coords) {
  int tct = 0;
  int last = coords.size();
  int last2 = last;

  f0(_, 8640) {
    //gp_hash_table<int, char, chash> nindc({},{},{},{},{1<<16});
    gp_hash_table<int, char> nindc;
    for (int c : coords) {
      nindc[c - CONST - 1]++;
      nindc[c - CONST    ]++;
      nindc[c - CONST + 1]++;
      nindc[c         - 1]++;
      nindc[c            ]+=7;
      nindc[c         + 1]++;
      nindc[c + CONST - 1]++;
      nindc[c + CONST    ]++;
      nindc[c + CONST + 1]++;
      //nindc[c] += 16;
    }
    vi ninder;
    //ninder.reserve(last + sqrt(last) * 4);
    
    //ninder.reserve(last + sqrt(last));
    //ninder.reserve(last * 2 - last2);
    /// 2pass

    for (auto [pt, ct] : nindc) {
      if (1544 & (1 << ct)) {
        ninder.push_back(pt);
        //cout << (int)ct << ':' << pt << ' ';
      }
    }
    coords = std::move(ninder);
    last2 = last;
    last = coords.size();
    tct += last;
    //cout << last << ' ' << sqrt(last) << ' ' << abs(last-last2)  nl;
  }
  //cout << tct nl;
  return tct;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int a,b,c;
  cin>>a>>b>>c;

  string st;
  cin >> st;
  vi coords;
  f0(i, 12) {
    f0(j, 12) {
      if (st[i*12 + j] == '1') {
        coords.pb(i * CONST + j);
      }
    }
  }
  cout << run(coords) << endl;
}
