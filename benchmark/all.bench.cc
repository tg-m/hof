/**
 * @file
 * Copyright (C) 2019 Tomasz G. Markiewicz (software.tgm@gmail.com)
 *
 * Created on Sep 3, 2019
 *
 */

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif /* __clang__ */



#include <cstdint>


#include <algorithm>
#include <random>
#include <vector>



#include <benchmark/benchmark.h>



// static void BM_SomeFunction(benchmark::State& state) {
//  // Perform setup here
//  for (auto _ : state) {
//    // This code gets timed
//    some_function();
//  }
//}





namespace {

static void
random_distribution_mersenne_twister_benchmark(benchmark::State& state) {
    // Will be used to obtain a seed for the random number engine
    // std::random_device rd{};


    // Standard mersenne_twister_engine seeded with rd()
    std::mt19937 gen(std::random_device{}());

    std::uniform_int_distribution<std::uint8_t> dis(0, 255);


    for(auto _ : state) {
        for(std::int64_t i = 0; state.range(0) > i; ++i) {
            dis(gen);
        }
    }

    state.SetBytesProcessed(
        /*static_cast<std::int64_t>*/(state.iterations()) *
        /*static_cast<std::int64_t>*/ (state.range(0))
    );
    state.SetComplexityN(state.range(0));
}

} /* namespace */


BENCHMARK(random_distribution_mersenne_twister_benchmark)
    ->RangeMultiplier(2)
    ->Range(64, 2048)
    ->Complexity(benchmark::oN)
    ->ComputeStatistics("max", [](std::vector<double> const& v) -> double {
        return *(std::ranges::max_element(v));
    });





// Run the benchmark
BENCHMARK_MAIN();


#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */
