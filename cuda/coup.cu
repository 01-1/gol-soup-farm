// {{{ <<-<<<<=< the optimal template >>=>>>>->>
#include <bits/stdc++.h>  // clang-format off
//#include <cuda/std/algorithm>
#include <curand_kernel.h>
//#define int long long
#define P pair
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
// clang-format on
//

std::ofstream e(std::format("outputs/{:%F %T %Z}",
        std::chrono::zoned_time{std::chrono::current_zone(),
                                std::chrono::system_clock::now()}));

struct ENDLTYPE {};
ENDLTYPE ENDLINST;

struct LogStream { template<typename T> LogStream& operator<<(const T& mValue); };
LogStream lstream;

template<typename T> LogStream& LogStream::operator<<(const T& mValue)
{
    std::cout << mValue;
    e << mValue;
    return lstream;
}
template<> LogStream& LogStream::operator<<(const ENDLTYPE& ENDLINST)
{
    std::cout << std::endl;
    e << std::endl;
    return lstream;
}

#define endl ENDLINST
auto& realcout = std::cout;
#define cout lstream

// }}} 998244353 1000000007

//using rng = std::mt19937_64;

std::mutex locker;
const int LEN = 1024;
const int HLEN = LEN / 2;
const int LEN_SHIFT = LEN * HLEN;

const int COORDS_SIZE = 8192; // max 8192 if short consider_count

#define array std::array

array<int, 144> WORLD;

__global__ void run(uint64_t random_seed) {
  array<uint8_t, LEN_SHIFT * 2> table;
  array<int, COORDS_SIZE> coords;
  array<int, COORDS_SIZE * 9> consider;

  auto calc = [&consider, &table, &coords](int coords_count) {
    bool skip = true;
    int tct = 0;

    //vi consider;

    int last = 0;
    int same = 0;
    uint16_t coords_size = 0;

    //int last3=0,last2=0,last=0;
    f0(frame, 8640) {

      uint16_t consider_count = 0;

      f0(i, coords_size) {
        int c = coords[i];

#define XV - LEN - 1
        if ((table[c XV]++) == 0) {
          consider[consider_count++] = (c XV);
        }
#define XV - LEN    
        if ((table[c XV]++) == 0) {
          consider[consider_count++] = (c XV);
        }
#define XV - LEN + 1
        if ((table[c XV]++) == 0) {
          consider[consider_count++] = (c XV);
        }
#define XV         - 1
        if ((table[c XV]++) == 0) {
          consider[consider_count++] = (c XV);
        }
        if ((table[c]+=7) == 7) {
          consider[consider_count++] = (c);
        }
#define XV         + 1
        if ((table[c XV]++) == 0) {
          consider[consider_count++] = (c XV);
        }
#define XV + LEN - 1
        if ((table[c XV]++) == 0) {
          consider[consider_count++] = (c XV);
        }
#define XV + LEN    
        if ((table[c XV]++) == 0) {
          consider[consider_count++] = (c XV);
        }
#define XV + LEN + 1
        if ((table[c XV]++) == 0) {
          consider[consider_count++] = (c XV);
        }
      }

      f0(i, consider_count) {
        int pt = consider[i];
        if (1544 & (1 << table[pt])) {
          coords[coords_size++] = (pt);
        }
        table[pt] = 0;
      }

      if (coords_size > 4096) {
        return 727272727; // Growing too fast
      }
      tct += coords_size;
      if (last == coords_size) same++; 
      else same = 0;

      if (skip && (coords_size < frame/6 || same == 10)) {
        int v = tct + coords_size * (8640 - frame);
        if (v >= 8000000) {
          skip = false;
        } else {
          return v;
        }
      }
      last=coords_size;
    }
    return tct;
  };

  auto threadcout = [&]() {
    cout << "T" << blockIdx.x << ' ';
    cout << threadIdx.x << " ";
    cout << "- ";
  };

  cuda::std::mt19937_64 gen(random_seed + threadIdx.x + blockIdx.x * blockDim.x);


  int iterct=0;
  array<int, 144> soup;

  f0(iterct, 10000) {
    uint64_t u;

    cuda::std::sample(ben(WORLD), back_inserter(soup), 48, gen);

    int v = calc(soup);
    int ov = v;

    if (v >= 10000000) {
      /*
      std::unique_lock lock(locker);
      //threadcout(thread_id);
      threadcout();
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
      */
    }
  }
}

//using cin = std::cin;
using std::cin;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  f0(i, 12){
    f0(j, 12){
      WORLD[i*12+j] = (LEN_SHIFT + i * LEN + j);
    }
  }
  
  uint64_t random_seed = std::chrono::system_clock::now().time_since_epoch().count();
  run<<<68, 128>>>(random_seed);

}
