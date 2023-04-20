#include <benchmark/benchmark.h>
#include "UBigInt.h"

static void BM_BigInt0Creation(benchmark::State& state) {
    for (auto _ : state)
        UBigInt bigInt;
}
// Register the function as a benchmark
BENCHMARK(BM_BigInt0Creation);

static void BM_BigIntCreation(benchmark::State& state) {
    for (auto _ : state)
        UBigInt bigInt("123456789012345678901234567890");
}
BENCHMARK(BM_BigIntCreation);

BENCHMARK_MAIN();