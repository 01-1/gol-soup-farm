# Game of Life soup search farm

Note: the code was written without LLMs, but this description was written with LLMs.

Searching for the largest soup in Conway's Game of Life under a set of constraints, run as a
distributed CPU job across rented spot instances.

Built for a hackathon in September–October 2024. Development continued afterward as a personal
project; the later work is not part of the hackathon submission.

## What's here

| Path | |
|---|---|
| `src/` | The CPU search — `sa.cc` (simulated annealing), `soup.cc`, `concur.cc` (the concurrent search shipped in the container), `hashtable.cc`, and several generation/evaluation variants. This is what actually ran. |
| `deploy/` | Dockerfile, entrypoint, and Kubernetes manifests. |
| `cuda/` | An attempted GPU search path (`cup.cu`, 581 lines; `coup.cu`, an earlier version). It did not work out and was not used for the production runs. Kept because it's most of the code I wrote. |
| `analysis/` | Python utilities for decoding, unflattening, rendering and summarising results. |
| `Makefile` | Build targets — separate debug (sanitizers, `_GLIBCXX_DEBUG`) and `-Ofast` paths. |

## How it ran

The search compiles inside the container at startup, runs, and streams results back to a
collector host over ssh:

```sh
g++ concur8.cc -O2 -o /soup -std=c++20 -march=native
/soup | ssh -i /do do@COLLECTOR_HOST "cat > '$(date --iso-8601=ns)'"
```

Scheduled on Rackspace Spot via Terraform, deployed as a Kubernetes `Deployment`. At peak this
ran across **roughly 1000 machines, on the order of 10,000 cores.**

The manifests here are smaller example configurations rather than the peak one — `cup8.yaml`
requests 64 replicas at 7 CPU each:

```yaml
spec:
  replicas: 64
  ...
          resources:
            requests:
              cpu: 7
```

Scaling out across cheap preemptible CPU was what made the search practical. The GPU attempt in
`cuda/` was the other thing I tried; horizontal CPU is what shipped.

### A note on result collection

Results were shipped home over ssh using a write-only key baked into the image, rather than
provisioning object storage and credentialing each pod against it. For a disposable farm of
preemptible workers this was materially less setup for the same outcome, at the cost of a
credential living in the image. That key and the cluster's `kubeconfig` are omitted from this
repository, and the collector's address is redacted to `COLLECTOR_HOST`.

## Caveats

- **Style.** The C++ is written in competitive-programming idiom — `bits/stdc++.h`, short macro
  definitions, terse names. That is deliberate for the context it was written in, and it is not
  how I would write a library.
- `cuda/cup.cu` depends on libcu++'s `bitset`, which is Apache-2.0 with LLVM exceptions and is
  not vendored here.
- `deploy/Dockerfile` references `concur8.cc`, a variant that was never committed; `src/concur.cc`
  is the nearest surviving version.
- The upstream projects this work sat alongside — `apgmera`, `apgcpu`, `lifelib` — are not mine
  and are not included.
