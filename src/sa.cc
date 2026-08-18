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

using rng = std::mt19937_64;

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

#define endl ENDLINST;


int RUNTIME;
extern const int CONST;
extern const int CONST_SHIFT;


auto startcalc = [](vi coords) {
  //vi coords = flatten(gcoords);
  vector<uint8_t> table (CONST_SHIFT * 2);
  int tct = 0;

  vi indlist;

  f0(_, RUNTIME) {

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
    tct += coords.size();
    //cout << last nl;
  }
  //cout << tct nl;
  return tct;
};
 



// }}} 998244353 1000000007

#define cout lstream
const int CONST = 17295;// //42069;
const int CONST_SHIFT = CONST * CONST / 2;

string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

vi flatten(const v<v<bool>>& coords) {
  vi result;
  f0(i, coords.size()) {
    f0(j, coords[i].size()) {
      if (coords[i][j]) {
        result.pb(CONST_SHIFT + i * CONST + j);
      }
    }
  }
  return result;
}

string b64ify(const v<v<bool>>& coords) {
  string result;
  f0(i, coords.size()) {
    frange(j, 0, coords[i].size(), 6) {
      uint8_t c = 0;
      f0(k, min((size_t) 6, coords[i].size() - j)) {
        c |= coords[i][j+k] << k;
      }
      result += base64[c];
    }
    result += ':';
  }
  return result;
}

uint broadcast_id = 0;
int best_val = 0;

double STARTING_TEMP = 0.85;

double broadcast_temp = STARTING_TEMP;

v<v<bool>> best_coords;

void sa(v<v<bool>> coords, int orig_val, int thread_id) {

  vector<uint8_t> table (CONST_SHIFT * 2);


  auto calc = [&](vi coords) {
    int tct = 0;

    vi indlist;

    f0(_, RUNTIME) {

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
      tct += coords.size();
      //cout << last nl;
    }
    //cout << tct nl;
    return tct;
  };
  
  rng gen(chrono::system_clock::now().time_since_epoch().count());

  std::uniform_int_distribution<> r12(0, 11);

  double temp = STARTING_TEMP;
  int max_val  = orig_val;
  int last_val = orig_val;

  uint last_broadcast_id = 0;

  uint time_since_update = 0;

  while (1) {
    // permute
    int i = r12(gen);
    int j = r12(gen);
    coords[i][j] = !coords[i][j];
    int cur_val = calc(flatten(coords));

    if (cur_val > last_val * (1 - temp)) {
      time_since_update = 0;
      last_val = cur_val;
      temp *= 0.9999;
      unique_lock lock(threadlock);
      if (temp < STARTING_TEMP * 1 && ckx(best_val, cur_val)) {
        // change 1 to 0.99 to eliminate whatever
        best_coords = coords;
        broadcast_id++;
        last_broadcast_id = broadcast_id;
        broadcast_temp = temp;
        cout << "Broadcast!\n";
      }
      bool flag = broadcast_id != last_broadcast_id;
      if (!flag) {
        u_char off_bits = 0;
        f0(i, 12)  {
          f0(j, 12) {
            off_bits += coords[i][j] ^ best_coords[i][j];
          }
        }
        // 89
        if (off_bits >= 72) flag = true; // CHANGE FOR NOT 12x12
      }
      cout << "Thread ";
      cout << thread_id<< "!";
      if (thread_id < 10) cout << ' ';
      cout << " - ";
      if (flag) {
        last_val = best_val;
        coords = best_coords;
        last_broadcast_id = broadcast_id;
        temp = broadcast_temp;
        cout << "reverting to last broadcast!" << endl
      } else {
        cout << b64ify(coords);
        cout << " temp " << temp;
        cout << ", value " << cur_val << endl;
      }
    } else {
      coords[i][j] = !coords[i][j];
      temp *= 0.99995;
      unique_lock lock(threadlock);
      if (broadcast_id != last_broadcast_id || time_since_update > 100) {
        last_val = best_val;
        coords = best_coords;
        last_broadcast_id = broadcast_id;
        temp = broadcast_temp;
      } else {
        cout << "Thread ";
        cout << thread_id << " ";
        if (thread_id < 10) cout << ' ';
        cout << " - ";
        cout << "no change. temp " << temp << endl;
        time_since_update++;
      }
    }
  }
}


signed main() {

  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int HEIGHT, WIDTH;
  cin>>HEIGHT>> WIDTH >> RUNTIME;

  //useti coords;
  v<v<bool>> coords(12, v<bool>(12));
  string tstr;
  cin >> tstr;
  map<string, int> wawa;

  f0(i, HEIGHT) {
    //string s;
    //cin >> s;
    //tstr += s;
    f0(j, WIDTH) {
      coords[i][j]=tstr[i * WIDTH + j]&1;
    }
  }
  best_coords = coords;

  int orig_val = startcalc(flatten(coords));

  future<void> threads[20];

  f0(i, 20) {
    threads[i] = std::async(sa, coords, orig_val, i);
  }
}
