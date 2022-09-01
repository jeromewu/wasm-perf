# WebAssembly Performance

Explore how to achieve maximum performance in WebAssembly.

Full post: [https://jeromewu.github.io/improving-performance-using-webassembly-simd-intrinsics/](https://jeromewu.github.io/improving-performance-using-webassembly-simd-intrinsics/)

## Setup

We benchmark the performance by measuring time to complete 10,000 times of two
64 x 64 matrix multiplication with various implementation and flags:

**Implementation**:

- [mul_mats.js](./mul_mats.js): JavaScript version
- [mul_mats.c](./mul_mats.c): C version
- [mul_mats_intrin.c](./mul_mats_intrin.c): C version with SIMD intrinsics

**Flags**:

- `-O3`: optimize code and enable vectorization
- `-msimd128`: enable SIMD 128 optimization

## Performance

**Environment**:

- Hardware
  - CPU: 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz
  - RAM: 16 GB
- Software
  - Linux Kernel: 5.19.1-3-MANJARO
  - NodeJS: v16.16.0
  - Emscripten: 3.1.18
  - GCC: 12.2.0

Here we use mul_mats.js as baseline to compare the speed / time.

| Implementation | Flags | Time |
| -------------- | ----- | ---- |
| mul_mats.js | | 5.768s (+-0%) |
| mul_mats-wasm.js | | 6.865s (+19%) |
| mul_mats-wasm-simd.js | -msimd128 | 6.964s (+21%) |
| mul_mats_intrin-wasm-simd.js | -msimd128 | 4.718s (-18%) |
| mul_mats-wasm-O3.js | -O3 | 2.012s (-65%) |
| mul_mats-wasm-O3-simd.js | -O3 -msimd128 | 0.278s (-95.2%) |
| **mul_mats_intrin-wasm-simd-O3.js** | **-O3 -msimd128** | **0.245s (-95.8%)** |
| mul_mats (gcc) | | 7.697s (+33%) |
| mul_mats-O3 (gcc) | -O3 | 0.401s (-93%) |
| mul_mats-O3-avx (gcc) | -O3 -mavx2 | 0.119s (-98%) |

Use SIMD intrinsics with `-O3` and `-msimd128` flags can be **95.8%** faster than pure
JavaScript implementation. :tada:

## Try it

To build binaries, you need to install Docker 19.03+ and run:

```bash
make
```

You should find all binaries in `dist/` folder.

To run all of them, simply hit:

```bash
make run-all
```

> Some of the execution might failed you are NOT using Linux, check
> [Makefile](./Makefile) to see how to run a specific case.
