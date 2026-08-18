// {{{ <<-<<<<=< the optimal template >>=>>>>->>
#include <bits/stdc++.h>  // clang-format off
using namespace std;
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

//char uwu[] ="\nx=12,y=12\n";

string start = "x=12,y=12\n";
using rng=mt19937_64;


int main() {
  cin.tie(0)->sync_with_stdio(0);
  rng gen(chrono::system_clock::now().time_since_epoch().count());

  // TODO:
  // make array of rle of strings for every possible row
  // cout each row

//while(1) {
  f0(i, 1<<20) {
    cout << start;
    // slow version
    int v = gen();
    f0(i, 5) {
      f0(j, 12) {
        // note the inversion
        cout << (char)('b'+(v&1)*0b1101);
        v>>=1;
      }
      cout << '$';
    }
    v = gen();
    f0(i, 5) {
      f0(j, 12) {
        // note the inversion
        cout << (char)('b'+(v&1)*0b1101);
        v>>=1;
      }
      cout << '$';
    }
    v = gen();
    f0(j, 12) {
      // note the inversion
      cout << (char)('b'+(v&1)*0b1101);
      v>>=1;
    }
    cout << '$';
    f0(j, 12) {
      // note the inversion
      cout << (char)('b'+(v&1)*0b1101);
      v>>=1;
    }
    cout << "!";
    if ((v & 0xFFFF) == 0xFFFF) {
      cout << endl;
    } else {
      cout nl;
    }
  }
}
