/**
 * @file
 * Copyright (C) 2024-present Tomasz G. Markiewicz (software.tgm@gmail.com)
 *
 * Created on Mar 6, 2024
 *
 */

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif /* __clang__ */

#include <memory>
#include <unordered_map>

#include <fmt/format.h>
#include <fmt/ranges.h>


#include "gtest-wrapper.hh"



// #include "common/debug.hh"

class dynamic_programming_Test : public testing::Test {
public:
    virtual void SetUp() override { }
    virtual void TearDown() override { }
};

TEST_F(dynamic_programming_Test, fixture_self_test) { }
TEST_F(dynamic_programming_Test, DISABLED_test) { }

namespace {
static std::uint64_t fibonacci_recursive(std::uint64_t const n) {
    // if(0 == n) {
    //     return 0;
    // }
    // if(3 > n) {
    //     return 1;
    // }
    // return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);

    return 3 > n ? (1 + n) / 2
                 : fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}
static std::uint64_t fibonacci_iterative_with_cache(std::uint64_t const n) {
    static std::vector<std::uint64_t> results{0, 1, 1, 2};
    while(results.size() <= n) {
        auto const size = results.size();
        results.emplace_back(results[size - 1] + results[size - 2]);
    }
    return results[n];
}

static std::uint64_t tribonacci_recursive(std::uint64_t const n) {
    // 0, 1, 1, 2
    // if(0 == n) {
    //     return 0;
    // }
    // if(3 > n) {
    //     return 1;
    // }
    // if(4 > n) {
    //     return 2;
    // }
    // return tribonacci_recursive(n - 1) + tribonacci_recursive(n - 2) +
    //        tribonacci_recursive(n - 3);
    return 4 > n ? (1 + n) / 2
                 : tribonacci_recursive(n - 1) + tribonacci_recursive(n - 2) +
                       tribonacci_recursive(n - 3);
}

static std::uint64_t tribonacci_iterative_with_cache(std::uint64_t const n) {
    static std::vector<std::uint64_t> results{0, 1, 1, 2, 4, 7};
    while(results.size() <= n) {
        auto const s = results.size();
        results.emplace_back(results[s - 1] + results[s - 2] + results[s - 3]);
    }
    return results[n];
}
} /* namespace */



TEST_F(dynamic_programming_Test, fibonacci_recursive_0006) {
    std::uint64_t const expected = 8;
    std::uint64_t const actual = fibonacci_recursive(6);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, fibonacci_recursive_0040) {
    std::uint64_t const expected = 102334155UL;
    std::uint64_t const actual = fibonacci_recursive(40);

    ASSERT_EQ(expected, actual);
}

TEST_F(dynamic_programming_Test, fibonacci_iterative_with_cache_0006) {
    std::uint64_t const expected = 8;
    std::uint64_t const actual = fibonacci_iterative_with_cache(6);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, fibonacci_iterative_with_cache_0040) {
    std::uint64_t const expected = 102334155UL;
    std::uint64_t const actual = fibonacci_iterative_with_cache(40);

    ASSERT_EQ(expected, actual);
}



TEST_F(dynamic_programming_Test, tribonacci_recursive_0020) {
    std::uint64_t const expected = 66012;
    std::uint64_t const actual = tribonacci_recursive(20);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, tribonacci_iterative_with_cache_0020) {
    std::uint64_t const expected = 66012;
    std::uint64_t const actual = tribonacci_iterative_with_cache(20);

    ASSERT_EQ(expected, actual);
}



//
// sum possible
// ---------------
// Write a function sumPossible that takes in an amount and an array of
// positive numbers. The function should return a boolean indicating
// whether or not it is possible to create the amount by summing numbers of
// the array. You may reuse numbers of the array as many times as
// necessary.
//
// You may assume that the target amount is non-negative.
//
// Details(tgm):
//
// Given:
//   - an integer: 'k', and
//   - an array: A = [a, b, c, ...]
//
// Find out whether it is possible to add elements from 'A' to get sum 'k'.
//
// NOTE: EACH ELEMENT FROM AN ARRAY 'A' __CAN__ BE USED MULTIPLE TIMES!
//
//
namespace {
namespace details {
static bool is_sum_possible(
    std::vector<std::uint32_t> const& numbers,
    std::uint32_t const sum,
    std::unordered_map<std::uint32_t, bool>* lookup
) {
    auto const it = lookup->find(sum);
    auto const end_lookup = std::end(*lookup);
    if(end_lookup != it) {
        return it->second;
    }
    for(auto const num : numbers) {
        if(num <= sum) {
            auto const diff = sum - num;
            if(is_sum_possible(numbers, diff, lookup)) {
                return true;
            }
            (*lookup)[diff] = false;
            // auto const is_diff = is_sum_possible(numbers, diff, lookup);
            // (*lookup)[diff] = is_diff;
            // if(is_diff) {
            //     return true;
            // }
        }
    }
    return false;
}
} /* namespace details */
static bool is_sum_possible(
    std::vector<std::uint32_t> const& numbers,
    std::uint32_t const sum
) {
    std::unordered_map<std::uint32_t, bool> lookup{};
    lookup.reserve(numbers.size() * 4);
    for(auto const num : numbers) {
        lookup.insert({num, true});
    }
    lookup.insert({0, true}); // We can _ALWAYS_ sum up to 0!
    return details::is_sum_possible(numbers, sum, &lookup);
}
} /* namespace */


TEST_F(dynamic_programming_Test, is_sum_possible__000x__000) {
    std::vector<std::uint32_t> const numbers{1, 2, 3};
    std::uint32_t const sum = 4;

    bool const expected = true;
    bool const actual = is_sum_possible(numbers, sum);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, is_sum_possible__000x__001) {
    std::vector<std::uint32_t> const numbers{4, 6, 10};
    std::uint32_t const sum = 15;

    bool const expected = false;
    bool const actual = is_sum_possible(numbers, sum);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, is_sum_possible__0000) {
    std::vector<std::uint32_t> const numbers{5, 12, 4};
    std::uint32_t const sum = 8;

    bool const expected = true;
    bool const actual = is_sum_possible(numbers, sum);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, is_sum_possible__0001) {
    std::vector<std::uint32_t> const numbers{6, 2, 10, 19};
    std::uint32_t const sum = 15;

    bool const expected = false;
    bool const actual = is_sum_possible(numbers, sum);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, is_sum_possible__0002) {
    std::vector<std::uint32_t> const numbers{6, 2, 1};
    std::uint32_t const sum = 13;

    bool const expected = true;
    bool const actual = is_sum_possible(numbers, sum);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, is_sum_possible__0003) {
    std::vector<std::uint32_t> const numbers{6, 20, 1};
    std::uint32_t const sum = 103;

    bool const expected = true;
    bool const actual = is_sum_possible(numbers, sum);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, is_sum_possible__0004) {
    std::vector<std::uint32_t> const numbers{};
    std::uint32_t const sum = 12;

    bool const expected = false;
    bool const actual = is_sum_possible(numbers, sum);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, is_sum_possible__0005) {
    std::vector<std::uint32_t> const numbers{12};
    std::uint32_t const sum = 12;

    bool const expected = true;
    bool const actual = is_sum_possible(numbers, sum);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, is_sum_possible__0006) {
    std::vector<std::uint32_t> const numbers{};
    std::uint32_t const sum = 0;

    bool const expected = true;
    bool const actual = is_sum_possible(numbers, sum);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, is_sum_possible__0007) {
    std::vector<std::uint32_t> const numbers{10, 8, 265, 24};
    std::uint32_t const sum = 271;

    bool const expected = false;
    bool const actual = is_sum_possible(numbers, sum);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, is_sum_possible__0008) {
    std::vector<std::uint32_t> const numbers{4, 2, 10};
    std::uint32_t const sum = 2017;

    bool const expected = false;
    bool const actual = is_sum_possible(numbers, sum);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, is_sum_possible__0009) {
    std::vector<std::uint32_t> const numbers{3, 5};
    std::uint32_t const sum = 13;

    bool const expected = true;
    bool const actual = is_sum_possible(numbers, sum);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, is_sum_possible__0010) {
    std::vector<std::uint32_t> const numbers{4, 5, 7};
    std::uint32_t const sum = 10;

    bool const expected = true;
    bool const actual = is_sum_possible(numbers, sum);

    ASSERT_EQ(expected, actual);
}

//
// min change
// ---------------
//
// Write a function minChange that takes in an amount and an array of
// coins. The function should return the minimum number of coins required
// to create the amount. You may use each coin as many times as necessary.
//
// If it is not possible to create the amount, then return -1.
//
//
namespace {
namespace details {
static std::int32_t find_min_size_of_coins_set__int32(
    std::int32_t amount,
    std::vector<std::int32_t> const& coins,
    std::unordered_map<std::int32_t, std::int32_t>* memo
) {
    if(0 > amount) {
        return -1;
    }
    if(0 == amount) {
        return 0;
    }

    auto const it = memo->find(amount);
    if(std::end(*memo) != it) {
        return it->second;
    }

    std::int32_t result = -1;

    for(auto const num : coins) {
        auto const new_result =
            find_min_size_of_coins_set__int32(amount - num, coins, memo);
        result = 0 > result     ? new_result
               : 0 > new_result ? result
                                : std::min<>(result, new_result);
        // if(0 > result) {
        //     result = new_result;
        // }
        // else if(0 <= new_result) {
        //     result = std::min<>(result, new_result);
        // }
    }


    0 > result ? result : ++result;

    memo->insert({amount, result});

    return result;
}
} /* namespace details */

static std::int32_t find_min_size_of_coins_set__int32(
    std::int32_t amount,
    std::vector<std::int32_t> const& coins
) {
    // memo cointains pairs of:
    //
    //   amount : num_of_elements
    //
    // where:
    //
    //   - amount - sum of coins
    //   - num_of_elements - MINIMUM number of coins from the std::vector
    //     'coins' that is required to add to obtain number amount
    //
    std::unordered_map<std::int32_t, std::int32_t> memo{};
    // memo.insert({0, 0}); // base case
    // for(auto const num : coins) {
    //     // other 'bases cases'
    //     memo.insert({num, 1});
    // }



    return details::find_min_size_of_coins_set__int32(amount, coins, &memo);
}
namespace details {
static std::int32_t find_min_size_of_coins_set__uint32(
    std::uint32_t amount,
    std::vector<std::uint32_t> const& coins,
    std::unordered_map<std::uint32_t, std::int32_t>* memo
) {
    if(auto const it = memo->find(amount); std::end(*memo) != it) {
        return it->second;
    }


    std::int32_t result{-1};

    for(auto const coin : coins) {
        if(coin > amount) {
            continue;
        }
        auto const new_result =
            find_min_size_of_coins_set__uint32(amount - coin, coins, memo);
        result = 0 > result     ? new_result
               : 0 > new_result ? result
                                : std::min<>(result, new_result);
    }

    0 > result ? result : ++result;


    memo->insert({amount, result});

    return result;
}
} /* namespace details */

static std::int32_t find_min_size_of_coins_set__uint32(
    std::uint32_t amount,
    std::vector<std::uint32_t> const& coins
) {

    std::unordered_map<std::uint32_t, std::int32_t> memo{};
    memo.insert({0, 0});
    for(auto const c : coins) {
        memo.insert({c, 1});
    }

    return details::find_min_size_of_coins_set__uint32(amount, coins, &memo);
}

template<typename To, typename From>
std::vector<To> cast_vec(std::vector<From> const& v) {
    std::vector<To> result{};
    result.reserve(v.size());

    for(auto const e : v) {
        result.emplace_back(static_cast<To>(e));
    }

    return result;
}
} // namespace


TEST_F(dynamic_programming_Test, find_min_size_of_coins_set____000x__001) {
    std::vector<std::int32_t> const coins{1, 2, 3};
    std::int32_t const amount = 5;

    std::int32_t const expected = 2;
    std::int32_t const actual =
        find_min_size_of_coins_set__int32(amount, coins);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(
        expected,
        find_min_size_of_coins_set__uint32(
            static_cast<std::uint32_t>(amount),
            cast_vec<std::uint32_t, std::int32_t>(coins)
        )
    );
}
TEST_F(dynamic_programming_Test, find_min_size_of_coins_set____000x__002) {
    std::vector<std::int32_t> const coins{1, 2, 3, 7};
    std::int32_t const amount = 5;

    std::int32_t const expected = 2;
    std::int32_t const actual =
        find_min_size_of_coins_set__int32(amount, coins);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(
        expected,
        find_min_size_of_coins_set__uint32(
            static_cast<std::uint32_t>(amount),
            cast_vec<std::uint32_t, std::int32_t>(coins)
        )
    );
}

TEST_F(dynamic_programming_Test, find_min_size_of_coins_set____0000) {
    std::vector<std::int32_t> const coins{1, 5, 4, 12};
    std::int32_t const amount = 8;

    std::int32_t const expected = 2;
    std::int32_t const actual =
        find_min_size_of_coins_set__int32(amount, coins);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(
        expected,
        find_min_size_of_coins_set__uint32(
            static_cast<std::uint32_t>(amount),
            cast_vec<std::uint32_t, std::int32_t>(coins)
        )
    );
}
TEST_F(dynamic_programming_Test, find_min_size_of_coins_set____0001) {
    std::vector<std::int32_t> const coins{1, 9, 5, 14, 30};
    std::int32_t const amount = 13;

    std::int32_t const expected = 5;
    std::int32_t const actual =
        find_min_size_of_coins_set__int32(amount, coins);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(
        expected,
        find_min_size_of_coins_set__uint32(
            static_cast<std::uint32_t>(amount),
            cast_vec<std::uint32_t, std::int32_t>(coins)
        )
    );
}
TEST_F(dynamic_programming_Test, find_min_size_of_coins_set____0002) {
    std::vector<std::int32_t> const coins{2, 5, 7};
    std::int32_t const amount = 23;

    std::int32_t const expected = 4;
    std::int32_t const actual =
        find_min_size_of_coins_set__int32(amount, coins);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(
        expected,
        find_min_size_of_coins_set__uint32(
            static_cast<std::uint32_t>(amount),
            cast_vec<std::uint32_t, std::int32_t>(coins)
        )
    );
}
TEST_F(dynamic_programming_Test, find_min_size_of_coins_set____0003) {
    std::vector<std::int32_t> const coins{1, 5, 10, 25};
    std::int32_t const amount = 102;

    std::int32_t const expected = 6;
    std::int32_t const actual =
        find_min_size_of_coins_set__int32(amount, coins);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(
        expected,
        find_min_size_of_coins_set__uint32(
            static_cast<std::uint32_t>(amount),
            cast_vec<std::uint32_t, std::int32_t>(coins)
        )
    );
}
TEST_F(dynamic_programming_Test, find_min_size_of_coins_set____0004) {
    std::vector<std::int32_t> const coins{1, 5, 10, 25};
    std::int32_t const amount = 200;

    std::int32_t const expected = 8;
    std::int32_t const actual =
        find_min_size_of_coins_set__int32(amount, coins);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(
        expected,
        find_min_size_of_coins_set__uint32(
            static_cast<std::uint32_t>(amount),
            cast_vec<std::uint32_t, std::int32_t>(coins)
        )
    );
}
TEST_F(dynamic_programming_Test, find_min_size_of_coins_set____0005) {
    std::vector<std::int32_t> const coins{4, 2, 10};
    std::int32_t const amount = 2017;

    std::int32_t const expected = -1;
    std::int32_t const actual =
        find_min_size_of_coins_set__int32(amount, coins);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(
        expected,
        find_min_size_of_coins_set__uint32(
            static_cast<std::uint32_t>(amount),
            cast_vec<std::uint32_t, std::int32_t>(coins)
        )
    );
}
TEST_F(dynamic_programming_Test, find_min_size_of_coins_set____0006) {
    std::vector<std::int32_t> const coins{10, 8, 265, 24};
    std::int32_t const amount = 271;

    std::int32_t const expected = -1;
    std::int32_t const actual =
        find_min_size_of_coins_set__int32(amount, coins);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(
        expected,
        find_min_size_of_coins_set__uint32(
            static_cast<std::uint32_t>(amount),
            cast_vec<std::uint32_t, std::int32_t>(coins)
        )
    );
}
TEST_F(dynamic_programming_Test, find_min_size_of_coins_set____0007) {
    std::vector<std::int32_t> const coins{4, 2, 10};
    std::int32_t const amount = 0;

    std::int32_t const expected = 0;
    std::int32_t const actual =
        find_min_size_of_coins_set__int32(amount, coins);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(
        expected,
        find_min_size_of_coins_set__uint32(
            static_cast<std::uint32_t>(amount),
            cast_vec<std::uint32_t, std::int32_t>(coins)
        )
    );
}
TEST_F(dynamic_programming_Test, find_min_size_of_coins_set____0008) {
    std::vector<std::int32_t> const coins{};
    std::int32_t const amount = 0;

    std::int32_t const expected = 0;
    std::int32_t const actual =
        find_min_size_of_coins_set__int32(amount, coins);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(
        expected,
        find_min_size_of_coins_set__uint32(
            static_cast<std::uint32_t>(amount),
            cast_vec<std::uint32_t, std::int32_t>(coins)
        )
    );
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */
