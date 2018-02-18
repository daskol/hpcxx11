#include <benchmark/benchmark.h>
#include "hpc++11.h"

static void BM_SumVectors(benchmark::State &state) {
    //state.PauseTiming();
    std::vector<float> a(1024 * 1024);
    std::vector<float> b(1024 * 1024);
    std::vector<float> c(1024 * 1024);

    for (size_t i = 0; i != a.size(); ++i) {
        a[i] = i;
        b[i] = b.size() - i - 1;
    }
    //state.ResumeTiming();

    while (state.KeepRunning()) {
        sum_vectors(a, b, c);
    }
}

BENCHMARK(BM_SumVectors);
BENCHMARK_MAIN();
