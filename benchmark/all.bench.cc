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




#include <vector>

#include <random>



#include <benchmark/benchmark.h>



// static void BM_SomeFunction(benchmark::State& state) {
//  // Perform setup here
//  for (auto _ : state) {
//    // This code gets timed
//    some_function();
//  }
//}





static void random_distribution_mersenne_twister_benchmark(benchmark::State& state) {
    // std::random_device rd{};  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(std::random_device{}()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<uint8_t> dis(0, 255);


    for(auto _ : state) {
        for(int64_t i = 0; state.range(0) > i; ++i) {
            dis(gen);
        }
    }

    state.SetBytesProcessed(
        /*static_cast<std::int64_t>*/(state.iterations()) *
        /*static_cast<std::int64_t>*/ (state.range(0))
    );
    state.SetComplexityN(state.range(0));
}
BENCHMARK(random_distribution_mersenne_twister_benchmark)->RangeMultiplier(2)->Range(64, 2048)->Complexity(benchmark::oN)->ComputeStatistics("max", [](const std::vector<double>& v) -> double {
    return *(std::max_element(std::begin(v), std::end(v)));
});





// Run the benchmark
BENCHMARK_MAIN();


#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */
