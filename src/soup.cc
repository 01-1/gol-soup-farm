// {{{ <<-<<<<=< the optimal template >>=>>>>->>
#include <bits/stdc++.h>  // clang-format off
using namespace std;
//#define int long long
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2,tune=native")
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
//

ofstream e(std::format("outputs/{:%F %T %Z}",
        std::chrono::zoned_time{std::chrono::current_zone(),
                                std::chrono::system_clock::now()}));

struct ENDLTYPE {};
ENDLTYPE ENDLINST;

struct LogStream { template<typename T> LogStream& operator<<(const T& mValue); };
LogStream lstream;
mutex threadlock;

template<typename T> LogStream& LogStream::operator<<(const T& mValue)
{
    std::cout << mValue;
    e << mValue;
    return lstream;
}
template<> LogStream& LogStream::operator<<(const ENDLTYPE& ENDLINST)
{
    std::cout << endl;
    e << endl;
    return lstream;
}

#define endl ENDLINST
auto& realcout =cout;
#define cout lstream

// }}} 998244353 1000000007

using rng=mt19937_64;

mutex locker;
const int CONST = 17295;
const int CONST_SHIFT = CONST * CONST / 2;

void threadcout(int thread_id) {
  cout << "T";
  cout << thread_id << " ";
  if (thread_id < 10) cout << ' ';
  cout << "- ";
}

void run(int thread_id) {
  vector<uint8_t> table (CONST_SHIFT * 2);
  bool flag = false;
  auto calc = [&](vi coords) {
    int tct = 0;

    vi indlist;

    int last = 0;
    int same = 0;
    //int last3=0,last2=0,last=0;
    f0(frame, 8640) {

      f0(i, coords.size()) {
        int c = coords[i];

#define XV - CONST - 1
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
#define XV - CONST    
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
#define XV - CONST + 1
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
#define XV         - 1
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
        if ((table[c]+=7) == 7) {
          indlist.push_back(c);
        }
#define XV         + 1
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
#define XV + CONST - 1
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
#define XV + CONST    
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
#define XV + CONST + 1
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
      }
      
      coords.clear();
      for (int pt : indlist) {
        int ct = table[pt];
        table[pt] = 0;
        if (1544 & (1 << ct)) {
          coords.push_back(pt);
          //cout << (int)ct << ':' << pt << ' ';
        }
      }
      indlist.clear();
      int csize = coords.size();
      tct += csize;
      //cout << last nl;
      if (last == csize) same++; 
      else same = 0;

      if (csize < frame/6 || same == 10) {
        //return tct + csize * (8640 - frame);

        int v = tct + csize * (8640 - frame);
        if (v >= 8000000) {
          //skip = false;
        } else {
          flag = true;
          return v;
        }
      }
      //last3=last2;
      //last2=last;
      last=csize;
    }
    //cout << tct nl;
    flag = false;
    return tct;
  };

  auto uecalc = [&](vi coords) {
    int tct = 0;

    vi indlist;

    f0(frame, 8640) {

      f0(i, coords.size()) {
        int c = coords[i];

#define XV - CONST - 1
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
#define XV - CONST    
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
#define XV - CONST + 1
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
#define XV         - 1
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
        if ((table[c]+=7) == 7) {
          indlist.push_back(c);
        }
#define XV         + 1
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
#define XV + CONST - 1
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
#define XV + CONST    
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
#define XV + CONST + 1
        if ((table[c XV]++) == 0) {
          indlist.push_back(c XV);
        }
      }
      
      coords.clear();
      for (int pt : indlist) {
        int ct = table[pt];
        table[pt] = 0;
        if (1544 & (1 << ct)) {
          coords.push_back(pt);
          //cout << (int)ct << ':' << pt << ' ';
        }
      }
      indlist.clear();
      int size = coords.size();
      tct += size;
      //cout << last nl;
    }
    //cout << tct nl;
    flag = false;
    return tct;
  };

  rng gen(chrono::system_clock::now().time_since_epoch().count());

  vi WORLD;
  f0(i, 12){
    f0(j, 12){
      WORLD.pb(CONST_SHIFT + i * CONST + j);
    }
  }

  int iterct=0;

  while (1) {
    uint64_t u;
    vi soup;

    std::sample(ben(WORLD), back_inserter(soup), 48, gen);

    if ((++iterct) % 1000000 == 0) {
      unique_lock lock(locker);
      threadcout(thread_id);
      cout << iterct << " iterations elapsed." << endl;
    }

    int v = calc(soup);
    cout << v << endl;
    /*
    int ov = v;

    if (v >= 8000000) {
      v = uecalc(soup);
    }

    if (v >= 10000000) {
      unique_lock lock(locker);
      threadcout(thread_id);
      cout<<"Score " << v;
      cout << "! Iteration " << iterct << ", ov = ";
      cout << ov;
      fo(mil, 11, 1+v/1000000) {
        cout << " ("<<mil<<"M+)";
      }
      cout << "\n";
      for (auto x:soup) {
        cout << x << ' ';
      }
      cout <<endl;
    }*/
  }
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  future<void> threads[20];

  f0(i, 1) {
    threads[i] = std::async(run, i);
  }
}
