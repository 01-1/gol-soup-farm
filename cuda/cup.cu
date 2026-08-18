// {{{ <<-<<<<=< the optimal template >>=>>>>->>
#include <bits/stdc++.h>  // clang-format off
//#include <cuda/std/detail/libcxx/include/bitset>
//#include <curand_kernel.h>
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

// may segfault if runs out of memory
const int CUDA_GRID_DIM = 1; // 68 * 15
// 1087 max (68 * 16 - 1)
const int CUDA_BLOCK_DIM = 1;
const int CUDA_NUMCORES = CUDA_GRID_DIM * CUDA_BLOCK_DIM;

const int GPU_RUNTIME = 120;

const int CPU_CONCURRENCY_COUNT = 20;

const int RAD = 127; // for 256x256
const int LEN = RAD * 2 + 2;
//const int HLEN = LEN / 2;
const int LEN_SHIFT = (RAD-5) * LEN + RAD - 5; // 12x12
const int TABLE_SIZE = LEN * LEN;
const int TABLE_SIZE_WITHOUT_LAST_ROW = TABLE_SIZE - LEN;

const int LLEN = 17295;
const int HLLEN = LLEN / 2;
const int LLEN_SHIFT = LLEN * HLLEN + LLEN / 2;
const int LTABLE_SIZE = LLEN * LLEN;

// 128, 1230
// 80, 1536
// 1, ?
const int STARTING_COORDS_SIZE = 50;
const int COORDS_MAX_SIZE = 256; // max 3640 if short consider_count
const int TOO_FAST_MAGIC_NUMBER = INT_MAX; //727272727;

//__shared__ int WORLD[144];

using u8 = unsigned char;
using u16 = unsigned short;
using uint = unsigned int;
using ull = uint64_t;

struct packet {
  bool is_real;
  int score;
  int iterct;
  int thread_id;
  bool soup[144];
};

#define f0(type, i, r) for (type i = 0; i < r; i++) 

__global__ void run(ull random_seed, packet* packet_store) {
  u8 table[TABLE_SIZE/2]; // can get less memory if use nybble
  memset(table, 0, TABLE_SIZE/2);
  ushort coords[COORDS_MAX_SIZE * 2]; //2x buffer space
  ushort consider[COORDS_MAX_SIZE * 9];

  // auto calc = [&consider, &table, &coords]() ;
  
  // calc approx 500M ops

  /* auto threadcout = [&]() {
    cout << "T" << blockIdx.x << ' ';
    cout << threadIdx.x << " ";
    cout << "- ";
  }; */ // cant cout

  //cuda::std::mt19937_64 gen(random_seed + threadIdx.x + blockIdx.x * blockDim.x);


  int iterct=0;
  bool soupedup[144];

  size_t real_thread_id = threadIdx.x + blockIdx.x * blockDim.x;

  ull xorshift_state = (random_seed + real_thread_id) * 0x2545F4914F6CDD1DULL; // idk if this mult is necesssary but whatevr

  //for(u16 iterct = 0; iterct < 10000; iterct++) {
  //f0(short, iterct, 99999) {
  while (1) {
    //cuda::std::sample(ben(WORLD), back_inserter(soup), 48, gen);

    short coords_size = 0;

    char iters_left = 1;

    memset(soupedup, 0, 144);

    uint bits;
    

    while (coords_size < STARTING_COORDS_SIZE) {
      if (--iters_left == 0) {
        xorshift_state ^= xorshift_state >> 12;
        xorshift_state ^= xorshift_state << 25;
        xorshift_state ^= xorshift_state >> 27;
        xorshift_state *= 0x2545F4914F6CDD1DULL;
        // take high 32(ish) bits
        bits = xorshift_state >> 32;
        iters_left = 4;
      }
      // maybe this can be optimized by taking more bits but IT DOESNT MATTER
      u8 nybbleI = bits & 0xF;
      bits >>= 4;
      u8 nybbleJ = bits & 0xF;
      bits >>= 4;

      if (nybbleI >= 12 || nybbleJ >= 12 || soupedup[nybbleI * 12 + nybbleJ]) {
        continue;
      }
      soupedup[nybbleI * 12 + nybbleJ] = true;
      coords[coords_size++] = LEN_SHIFT + nybbleI * LEN + nybbleJ; // can be optimized but DOESNT MATTER 144 divisions is not faster than 59000 comparisons
    }



    int tct = 0; //v = calc();

    int last = 0;
    int same = 0;
    bool skip = true;

    //vi consider;
    //int last3=0,last2=0,last=0;
    //for(u16 frame = 0; frame < 8640; frame++) {

    f0(short, frame, GPU_RUNTIME) {
      short consider_count = 0;

      //if (coords_size == 50) return;

      //f0(short, i, csizesave) {//coords_size) {

      for(short i = 0; i < coords_size; i++) {
        ushort c = coords[i];

        int x,u,v;
#define XV - LLEN - 1
        x = c XV;
        u = 0xFF & (table[x/2] >> (4 * (x&1)));
        v = table[x/2] & (0xFF << (4 * ((x&1)^1)));
        table[x/2] = (u + 1) << (4 * (x & 1)) | v;
        if (u == 0) {
          consider[consider_count++] = (c XV);
        }
#define XV - LLEN    
        x = c XV;
        u = 0xFF & (table[x/2] >> (4 * (x&1)));
        v = table[x/2] & (0xFF << (4 * ((x&1)^1)));
        table[x/2] = (u + 1) << (4 * (x & 1)) | v;
        if (u == 0) {
          consider[consider_count++] = (c XV);
        }
#define XV - LLEN + 1
        x = c XV;
        u = 0xFF & (table[x/2] >> (4 * (x&1)));
        v = table[x/2] & (0xFF << (4 * ((x&1)^1)));
        table[x/2] = (u + 1) << (4 * (x & 1)) | v;
        if (u == 0) {
          consider[consider_count++] = (c XV);
        }
#define XV         - 1
        x = c XV;
        u = 0xFF & (table[x/2] >> (4 * (x&1)));
        v = table[x/2] & (0xFF << (4 * ((x&1)^1)));
        table[x/2] = (u + 1) << (4 * (x & 1)) | v;
        if (u == 0) {
          consider[consider_count++] = (c XV);
        }

        u = 0xFF & (table[c/2] >> (4 * (c&1)));
        v = table[c/2] & (0xFF << (4 * ((c&1)^1)));
        table[c/2] = (u + 7) << (4 * (c & 1)) | v;
        if (u == 0) {
          consider[consider_count++] = (c);
        }
#define XV         + 1
        x = c XV;
        u = 0xFF & (table[x/2] >> (4 * (x&1)));
        v = table[x/2] & (0xFF << (4 * ((x&1)^1)));
        table[x/2] = (u + 1) << (4 * (x & 1)) | v;
        if (u == 0) {
          consider[consider_count++] = (c XV);
        }
#define XV + LLEN - 1
        x = c XV;
        u = 0xFF & (table[x/2] >> (4 * (x&1)));
        v = table[x/2] & (0xFF << (4 * ((x&1)^1)));
        table[x/2] = (u + 1) << (4 * (x & 1)) | v;
        if (u == 0) {
          consider[consider_count++] = (c XV);
        }
#define XV + LLEN    
        x = c XV;
        u = 0xFF & (table[x/2] >> (4 * (x&1)));
        v = table[x/2] & (0xFF << (4 * ((x&1)^1)));
        table[x/2] = (u + 1) << (4 * (x & 1)) | v;
        if (u == 0) {
          consider[consider_count++] = (c XV);
        }
#define XV + LLEN + 1
        x = c XV;
        u = 0xFF & (table[x/2] >> (4 * (x&1)));
        v = table[x/2] & (0xFF << (4 * ((x&1)^1)));
        table[x/2] = (u + 1) << (4 * (x & 1)) | v;
        if (u == 0) {
          consider[consider_count++] = (c XV);
        }
      }

      coords_size = 0;

      f0(short, i, consider_count) {
        int pt = consider[i];
        // can remove bounds check if put in whatever but this may be slower because it is more times, unless you remove the other if
        if (((pt >= TABLE_SIZE_WITHOUT_LAST_ROW) || (pt / LEN) == 0 || (pt % LEN) == 0)) {
          //tct = TOO_FAST_MAGIC_NUMBER; // todo make new magic number

          //goto BREAKER;
        }
        else if (1544 & (1 << table[pt])) {
          coords[coords_size++] = (pt);
        }
        table[pt] = 0;
      }

      if (coords_size >= COORDS_MAX_SIZE) { // 3000 is like, 5 sigma with 3640; this is like 16 sigma
        tct = TOO_FAST_MAGIC_NUMBER; // Growing too fast
        goto BREAKER;
      }

      tct += coords_size;
      if (last == coords_size) same++; 
      else same = 0;

      if (skip && (coords_size < frame/6 || same == 10)) {
        int v = tct + coords_size * (8640 - frame);
        if (v >= 4000000) { // approx 1.8% of compute time
          skip = false;
        } else {
          tct = v;
          goto BREAKER;
        }
      }

      last=coords_size;

    }
        //return;
BREAKER:
    if (coords_size >= COORDS_MAX_SIZE) {
      if (packet_store[real_thread_id].is_real) {
        //spinlock
      }
      packet_store[real_thread_id].score = tct;
      packet_store[real_thread_id].iterct = iterct;
      memcpy(packet_store[real_thread_id].soup, soupedup, 144);
      packet_store[real_thread_id].is_real = true;
    }
  }
}

//using cin = std::cin;
using std::cin;

std::mutex coutmutex;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

#define f0(i, r) for (int i = 0; i < r; i++) 
  /*
  f0(i, 12){
    f0(j, 12){
      WORLD[i*12+j] = (LEN_SHIFT + i * LEN + j);
    }
  }*/
  // memory access prob slower
 


  ull random_seed = std::chrono::system_clock::now().time_since_epoch().count();

  //packet* pDevice_packet_store;
  packet* device_packet_store;

  
  const size_t PACKET_STORE_SIZE = sizeof(packet) * CUDA_NUMCORES;
  //packet** pDevice_packet_store = *pDevice_packet_store;

  cudaStream_t runstream;
  cudaStreamCreate(&runstream);
  cudaMallocAsync((void**)&device_packet_store, PACKET_STORE_SIZE, runstream);
  cudaMemsetAsync(device_packet_store, 0, PACKET_STORE_SIZE, runstream);

  cudaStream_t memcpystream;
  cudaStreamCreate(&memcpystream);

  packet host_packet_store[CUDA_NUMCORES];


  int numBlocks;
  int blockSize = CUDA_BLOCK_DIM;


  cudaOccupancyMaxActiveBlocksPerMultiprocessor(
        &numBlocks,
        run,
        blockSize,
        0);

      cout << "max num blocks "  << numBlocks<< endl;

  run<<<CUDA_GRID_DIM,CUDA_BLOCK_DIM,0,runstream>>>(random_seed, device_packet_store);
  {
      std::unique_lock lock(coutmutex);
      cout << "Starting!" << endl;
  }


  std::array<std::vector<packet>, CPU_CONCURRENCY_COUNT> task_queues;
  std::array<std::mutex, CPU_CONCURRENCY_COUNT> queue_mutexes;
  std::array<std::condition_variable, CPU_CONCURRENCY_COUNT> mutex_conditions;
  
  auto run = [&] (int thread_id) {
    std::vector<u8> table(LTABLE_SIZE);
    
    auto calc = [&table](std::vector<int> coords) {
      int tct = 0;

      std::vector<int> indlist;

      int last = 0;
      int same = 0;

      int skip = true;
      //int last3=0,last2=0,last=0;
      f0(frame, 8640) {

        f0(i, coords.size()) {

          int c = coords[i];

#define XV - LEN - 1
          if ((table[c XV]++) == 0) {
            indlist.push_back(c XV);
          }
#define XV - LEN    
          if ((table[c XV]++) == 0) {
            indlist.push_back(c XV);
          }
#define XV - LEN + 1
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
#define XV + LEN - 1
          if ((table[c XV]++) == 0) {
            indlist.push_back(c XV);
          }
#define XV + LEN    
          if ((table[c XV]++) == 0) {
            indlist.push_back(c XV);
          }
#define XV + LEN + 1
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
          }
        }
        indlist.clear();
        int csize = coords.size();
        tct += csize;
        if (last == csize) same++; 
        else same = 0;
        last=csize;


        if (skip && (csize < frame/6 || same == 10)) {
          int v = tct + csize * (8640 - frame);
          if (v >= 8000000) { // approx 1.8% of compute time
            skip = false;
          } else {
            return v;
          }
        }

      }
      return tct;
    };

    while (1) {
      packet p;
      /*{
        std::unique_lock lock(coutmutex);
        cout << thread_id << " wait" << endl;
      }*/
      {
        std::unique_lock lock(queue_mutexes[thread_id]);
        mutex_conditions[thread_id].wait(lock, [&] {
            return !task_queues[thread_id].empty();
        });
        p = task_queues[thread_id].back();
        task_queues[thread_id].pop_back();
      }
      /*{
        std::unique_lock lock(coutmutex);
        cout << thread_id << " found" << endl;
      }*/
      std::vector<int> coords;
      f0(i, 12) {
        f0(j, 12) {
          if (p.soup[i*12+j]) {
            coords.push_back(LLEN_SHIFT + LLEN * i + j);
          }
        }
      }
      int realscore = calc(coords);
      /*
      {
        std::unique_lock lock(coutmutex);
        cout << thread_id << " calced" << endl;
      }*/
      if (realscore >= 10000000*0) {
        std::unique_lock lock(coutmutex);
        //cout << "Score " << realscore << " achieved! Iteration count: " << p.iterct << ", thread " << "\n";
        cout<<"Score " << realscore; //p.score;
        cout << "! Iteration " << p.iterct << ", thread G" << p.thread_id << "/C" << thread_id;
        for(int mil = 11; mil*1000000 <= realscore; mil++) {
          cout << " ("<<mil<<"M+)";
        }
        cout << "\n";
        f0(i, 144) {
          cout << p.soup[i];
        }
        if (!p.is_real) {
          cout << "\nThere is something wrong: packet sent to CPU thread is not real!";
        }
        cout << endl;
      }
    }
    // for(int core_i = thread_id; core_i < CUDA_NUMCORES; core_i += CPU_CONCURRENCY_COUNT) {
      //packet p = host_packet_store[core_i];
  };


  std::thread threads[CPU_CONCURRENCY_COUNT];

  f0(i, CPU_CONCURRENCY_COUNT) {
    threads[i] = std::thread(run, i);
  } // or use std::thread


  while (1) {
    //cout<< cudaGetErrorString(cudaGetLastError()) << endl;

    auto error = cudaGetLastError();
    if (error) {
      std::unique_lock lock(coutmutex);
      cout << "CUDA error!!!\n";
      auto s = cudaGetErrorString(error);
      cout << s << endl;
    }

    cudaMemcpyAsync(host_packet_store, device_packet_store, PACKET_STORE_SIZE, cudaMemcpyDeviceToHost, memcpystream);
    cudaMemsetAsync(device_packet_store, 0, PACKET_STORE_SIZE, memcpystream);
    cudaStreamSynchronize(memcpystream);

    // if more than 1% consider multithreading
    int packets_received = 0;

    int cpu_thread_id = 0;

    std::array<int, CPU_CONCURRENCY_COUNT> tqsizes{};

    int tqsize = 0;

    f0(core_i, CUDA_NUMCORES) {
      packet p = host_packet_store[core_i];
      if (!p.is_real) continue;
      packets_received++;
      p.thread_id = core_i;
      int ptqs = tqsizes[cpu_thread_id];
      {
        std::unique_lock lock(queue_mutexes[cpu_thread_id]);
        task_queues[cpu_thread_id].push_back(p);
        tqsizes[cpu_thread_id] = task_queues[cpu_thread_id].size();
        mutex_conditions[cpu_thread_id].notify_one();
      }

      tqsize += (tqsizes[cpu_thread_id] - ptqs);

      cpu_thread_id++;
      if (cpu_thread_id == CPU_CONCURRENCY_COUNT) {
        cpu_thread_id = 0;
      }
    }
    //std::future<void> futures[CPU_CONCURRENCY_COUNT];

    /*
    std::future<void> futures[CPU_CONCURRENCY_COUNT];

    f0(i, CPU_CONCURRENCY_COUNT) {
      futures[i] = std::async(run, i);
    }

    f0(i, CPU_CONCURRENCY_COUNT) {
      futures[i].wait();
    }*/

    if (tqsize >= 100) {
      {
        std::unique_lock lock(coutmutex);
        cout << "Large task queue: " << tqsize << endl;
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    if (packets_received > CUDA_NUMCORES / 1000) {
      std::unique_lock lock(coutmutex);
      cout << "More than 0.1% of packets received: " << packets_received << endl;
    } else {
      //cout << "Sleeping..." << endl;
      //std::this_thread::sleep_for(std::chrono::milliseconds(100));
      //cout << "Waking up..." << endl;
    }
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
