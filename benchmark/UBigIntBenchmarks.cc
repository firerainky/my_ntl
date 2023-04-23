#include <benchmark/benchmark.h>

#include "UBigInt.h"

static void BM_BigInt0Creation(benchmark::State &state)
{
    for (auto _ : state)
        UBigInt bigInt;
}
// Register the function as a benchmark
BENCHMARK(BM_BigInt0Creation);

static void BM_BigIntCreation(benchmark::State &state)
{
    for (auto _ : state)
        UBigInt bigInt("123456789012345678901234567890");
}
BENCHMARK(BM_BigIntCreation);

static void BM_StringCompare(benchmark::State &state)
{
    std::string s1(state.range(0), '-');
    std::string s2(state.range(0), '-');
    for (auto _ : state)
    {
        auto comparison_result = s1.compare(s2);
        benchmark::DoNotOptimize(comparison_result);
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_StringCompare)->RangeMultiplier(2)->Range(1 << 10, 1 << 18)->Complexity(benchmark::oN);

BENCHMARK_MAIN();
