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
#include <utility>

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






// count paths
// ---------------
//
// Write a function, countPaths, that takes in a grid as an argument. In
// the grid, 'X' represents walls and 'O' represents open spaces. You may
// only move down or to the right and cannot pass through walls. The
// function should return the number of ways possible to travel from the
// top-left corner of the grid to the bottom-right corner.
//
//
namespace {
static std::pair<char, char> get_wall_open_space_descriptors() {
    return std::make_pair('X', 'O');
}
namespace details {
static std::int32_t count_paths_two_dim_array_as_helper(
    std::uint32_t const r,
    std::uint32_t const c,
    std::vector<std::vector<char>> const& grid,
    std::vector<std::vector<std::int32_t>>* memo,
    char const W
) {


    if(-1 != (*memo)[r][c]) {
        return (*memo)[r][c];
    }

    if(W == grid[r][c]) {
        (*memo)[r][c] = 0;
        return 0;
    }


    (*memo)[r][c] =
        count_paths_two_dim_array_as_helper(1 + r, c, grid, memo, W) +
        count_paths_two_dim_array_as_helper(r, 1 + c, grid, memo, W);

    return (*memo)[r][c];
}

static std::uint32_t count_paths_hashmap_as_helper(
    std::uint64_t const row,
    std::uint64_t const col,
    std::vector<std::vector<char>> const& grid,
    std::unordered_map<std::uint64_t, std::uint32_t>* memo,
    char const W
) {

    std::uint64_t const key = (row << 32) + col;

    auto const it = memo->find(key);
    if(std::end(*memo) != it) {
        return it->second;
    }

    auto const all_rows = grid.size();
    auto const all_cols = grid.at(0).size();


    if(W == grid[row][col]) {
        (*memo)[key] = 0;
        return 0;
    }

    std::uint32_t result = 0;
    if(all_cols > 1 + col) {
        result += count_paths_hashmap_as_helper(row, 1 + col, grid, memo, W);
    }
    if(all_rows > 1 + row) {
        result += count_paths_hashmap_as_helper(1 + row, col, grid, memo, W);
    }

    (*memo)[key] = result;

    return result;
}
} /* namespace details */

static std::uint32_t count_paths_two_dim_array_as_helper(
    std::vector<std::vector<char>> const& grid
) {
    auto const all_rows = static_cast<std::uint32_t>(grid.size());
    auto const all_cols = static_cast<std::uint32_t>(grid.at(0).size());

    std::vector<std::vector<std::int32_t>> memo(
        1 + all_rows, std::vector<std::int32_t>(1 + all_cols, -1)
    );

    auto const [W, O] = get_wall_open_space_descriptors();

    // Set-up boundary conditions "outside" of the grid
    for(std::uint32_t c = 0; 1 + all_cols > c; ++c) {
        memo[all_rows][c] = 0;
    }
    for(std::uint32_t r = 0; 1 + all_rows > r; ++r) {
        memo[r][all_cols] = 0;
    }

    // base case (righ down corner)
    memo[all_rows - 1][all_cols - 1] =
        O == grid[all_rows - 1][all_cols - 1] ? 1 : 0;


    auto const result = static_cast<std::uint32_t>(
        details::count_paths_two_dim_array_as_helper(0, 0, grid, &memo, W)
    );

    // for(auto const& v : memo) {
    //     for(auto const e : v) {
    //         fmt::print("{:9}", e);
    //     }
    //     fmt::print("\n");
    // }

    return result;
}

static std::uint32_t
count_paths_hashmap_as_helper(std::vector<std::vector<char>> const& grid) {
    auto const [W, O] = get_wall_open_space_descriptors();

    auto const all_rows = grid.size();
    auto const all_cols = grid.at(0).size();

    std::unordered_map<std::uint64_t, std::uint32_t> memo{};


    std::uint64_t const key_base = ((all_rows - 1) << 32) + all_cols - 1;
    memo[key_base] = W == grid[all_rows - 1][all_cols - 1] ? 0 : 1;

    auto const result =
        details::count_paths_hashmap_as_helper(0, 0, grid, &memo, W);


    // {
    //     std::vector<std::vector<std::int32_t>> v_memo(
    //         all_rows, std::vector<std::int32_t>(all_cols, -1)
    //     );
    //     for(auto const& e : memo) {
    //         auto const key = e.first;
    //         auto const row = (0xFFFFFFFF00000000 & key) >> 32;
    //         auto const col = (0x00000000FFFFFFFF & key);
    //         v_memo[row][col] = static_cast<std::int32_t>(e.second);
    //     }
    //     for(auto const& v : v_memo) {
    //         for(auto const e : v) {
    //             fmt::print("{:9}", e);
    //         }
    //         fmt::print("\n");
    //     }
    // }


    return result;
}
} /* namespace */


TEST_F(dynamic_programming_Test, count_paths_in_a_grid_with_walls_000x_000) {
    auto const [X, _] = get_wall_open_space_descriptors();
    std::vector<std::vector<char>> const grid{
        {_, _, _},
        {_, _, _},
    };

    std::uint32_t const expected = 3;
    std::uint32_t const actual = count_paths_two_dim_array_as_helper(grid);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(expected, count_paths_hashmap_as_helper(grid));
}
TEST_F(dynamic_programming_Test, count_paths_in_a_grid_with_walls_000x_001) {
    auto const [X, _] = get_wall_open_space_descriptors();
    std::vector<std::vector<char>> const grid{
        {_, _, X},
        {_, _, _},
    };

    std::uint32_t const expected = 2;
    std::uint32_t const actual = count_paths_two_dim_array_as_helper(grid);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(expected, count_paths_hashmap_as_helper(grid));
}
TEST_F(dynamic_programming_Test, count_paths_in_a_grid_with_walls_000x_002) {
    auto const [X, _] = get_wall_open_space_descriptors();
    std::vector<std::vector<char>> const grid{
        {_, X, _},
        {_, _, _},
    };

    std::uint32_t const expected = 1;
    std::uint32_t const actual = count_paths_two_dim_array_as_helper(grid);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(expected, count_paths_hashmap_as_helper(grid));
}
TEST_F(dynamic_programming_Test, count_paths_in_a_grid_with_walls_000x_003) {
    auto const [X, _] = get_wall_open_space_descriptors();
    std::vector<std::vector<char>> const grid{
        {_, _, X},
        {_, _, _},
        {_, _, _},
    };

    std::uint32_t const expected = 5;
    std::uint32_t const actual = count_paths_two_dim_array_as_helper(grid);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(expected, count_paths_hashmap_as_helper(grid));
}
TEST_F(dynamic_programming_Test, count_paths_in_a_grid_with_walls_0000) {
    auto const [X, _] = get_wall_open_space_descriptors();
    std::vector<std::vector<char>> const grid{
        {_, _},
        {_, _},
    };

    std::uint32_t const expected = 2;
    std::uint32_t const actual = count_paths_two_dim_array_as_helper(grid);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(expected, count_paths_hashmap_as_helper(grid));
}
TEST_F(dynamic_programming_Test, count_paths_in_a_grid_with_walls_0001) {
    auto const [X, _] = get_wall_open_space_descriptors();
    std::vector<std::vector<char>> const grid{
        {_, _, X},
        {_, _, _},
        {_, _, _},
    };

    std::uint32_t const expected = 5;
    std::uint32_t const actual = count_paths_two_dim_array_as_helper(grid);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(expected, count_paths_hashmap_as_helper(grid));
}
TEST_F(dynamic_programming_Test, count_paths_in_a_grid_with_walls_0002) {
    auto const [X, _] = get_wall_open_space_descriptors();
    std::vector<std::vector<char>> const grid{
        {_, _, _},
        {_, _, X},
        {_, _, _},
    };

    std::uint32_t const expected = 3;
    std::uint32_t const actual = count_paths_two_dim_array_as_helper(grid);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(expected, count_paths_hashmap_as_helper(grid));
}
TEST_F(dynamic_programming_Test, count_paths_in_a_grid_with_walls_0003) {
    auto const [X, _] = get_wall_open_space_descriptors();
    std::vector<std::vector<char>> const grid{
        {_, _, _},
        {_, X, X},
        {_, _, _},
    };

    std::uint32_t const expected = 1;
    std::uint32_t const actual = count_paths_two_dim_array_as_helper(grid);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(expected, count_paths_hashmap_as_helper(grid));
}
TEST_F(dynamic_programming_Test, count_paths_in_a_grid_with_walls_0004) {
    auto const [X, _] = get_wall_open_space_descriptors();
    std::vector<std::vector<char>> const grid{
        {_, _, X, _, _, _},
        {_, _, X, _, _, _},
        {_, _, X, _, _, _},
        {X, X, X, _, _, _},
        {_, _, _, _, _, _},
    };

    std::uint32_t const expected = 0;
    std::uint32_t const actual = count_paths_two_dim_array_as_helper(grid);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(expected, count_paths_hashmap_as_helper(grid));
}
TEST_F(dynamic_programming_Test, count_paths_in_a_grid_with_walls_0005) {
    auto const [X, _] = get_wall_open_space_descriptors();
    std::vector<std::vector<char>> const grid{
        {_, _, X, _, _, _},
        {_, _, _, _, _, X},
        {X, _, _, _, _, _},
        {X, X, X, _, _, _},
        {_, _, _, _, _, _},
    };

    std::uint32_t const expected = 42;
    std::uint32_t const actual = count_paths_two_dim_array_as_helper(grid);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(expected, count_paths_hashmap_as_helper(grid));
}
TEST_F(dynamic_programming_Test, count_paths_in_a_grid_with_walls_0006) {
    auto const [X, _] = get_wall_open_space_descriptors();
    std::vector<std::vector<char>> const grid{
        {_, _, X, _, _, _},
        {_, _, _, _, _, X},
        {X, _, _, _, _, _},
        {X, X, X, _, _, _},
        {_, _, _, _, _, X},
    };

    std::uint32_t const expected = 0;
    std::uint32_t const actual = count_paths_two_dim_array_as_helper(grid);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(expected, count_paths_hashmap_as_helper(grid));
}
TEST_F(dynamic_programming_Test, count_paths_in_a_grid_with_walls_0007) {
    auto const [X, _] = get_wall_open_space_descriptors();
    std::vector<std::vector<char>> const grid{
        // 15 x 15
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
    };

    std::uint32_t const expected = 40116600;
    std::uint32_t const actual = count_paths_two_dim_array_as_helper(grid);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(expected, count_paths_hashmap_as_helper(grid));
}
TEST_F(dynamic_programming_Test, count_paths_in_a_grid_with_walls_0008) {
    auto const [X, _] = get_wall_open_space_descriptors();
    std::vector<std::vector<char>> const grid{
        // 15 x 15
        {_, _, X, X, _, _, _, X, _, _, _, _, _, _, _},
        {_, _, X, X, _, _, _, X, _, _, _, _, _, _, _},
        {_, _, _, X, _, _, _, X, _, _, _, _, _, _, _},
        {X, _, _, _, _, _, _, X, _, _, _, _, _, _, _},
        {X, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, X, X, _},
        {_, _, _, _, _, _, _, X, _, _, _, _, _, X, _},
        {_, _, _, _, _, _, _, _, X, _, _, _, _, _, _},
        {X, X, X, _, _, _, _, _, _, X, _, _, _, _, _},
        {_, _, _, _, X, X, _, _, _, _, X, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, X, X, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, X, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, X, _, _, _, _, _, _},
    };

    std::uint32_t const expected = 3190434;
    std::uint32_t const actual = count_paths_two_dim_array_as_helper(grid);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(expected, count_paths_hashmap_as_helper(grid));
}



//
// max path sum
// ---------------
//
// Write a function, maxPathSum, that takes in a grid as an argument. The
// function should return the maximum sum possible by traveling a path from
// the top-left corner to the bottom-right corner. You may only travel
// through the grid by moving down or right.
//
// You can assume that all numbers are non-negative.
//

namespace {
namespace details {
static std::int32_t count_max_path_sum_2d_array_as_memo(
    std::uint32_t const row,
    std::uint32_t const col,
    std::vector<std::vector<std::uint32_t>> const& grid,
    std::vector<std::vector<std::int32_t>>* const memo
) {
    auto const rows = static_cast<std::uint32_t>(grid.size());
    auto const cols = static_cast<std::uint32_t>(grid[0].size());

    auto const value = (*memo)[row][col];

    if(-1 != value) {
        return value;
    }

    std::int32_t result = 0;



    if(rows > 1 + row) {
        result = std::max<>(
            result,
            count_max_path_sum_2d_array_as_memo(1 + row, col, grid, memo)
        );
    }
    if(cols > 1 + col) {
        result = std::max<>(
            result,
            count_max_path_sum_2d_array_as_memo(row, 1 + col, grid, memo)
        );
    }

    result += static_cast<std::int32_t>(grid[row][col]);


    (*memo)[row][col] = result;

    return result;
}
} /* namespace details */
static std::uint32_t count_max_path_sum_2d_array_as_memo(
    std::vector<std::vector<std::uint32_t>> const& grid
) {
    // auto const rows = static_cast<std::uint32_t>(grid.size());
    // auto const cols = static_cast<std::uint32_t>(grid.at(0).size());
    auto const rows = grid.size();
    auto const cols = grid.at(0).size();
    std::vector<std::vector<std::int32_t>> memo(
        rows, std::vector<std::int32_t>(cols, -1)
    );

    memo[rows - 1][cols - 1] =
        static_cast<std::int32_t>(grid[rows - 1][cols - 1]);


    std::uint32_t const result = static_cast<std::uint32_t>(
        details::count_max_path_sum_2d_array_as_memo(0, 0, grid, &memo)
    );


    return result;
}
} /* namespace */


TEST_F(dynamic_programming_Test, count_max_path_sum____v_0000) {
    std::vector<std::vector<std::uint32_t>> const grid = {
        {1, 3, 12},
        {5, 1, 1},
        {3, 6, 1},
    };
    std::uint32_t const expected = 18;
    std::uint32_t const actual = count_max_path_sum_2d_array_as_memo(grid);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, count_max_path_sum____v_0001) {
    std::vector<std::vector<std::uint32_t>> const grid = {
        {1, 2, 8, 1},
        {3, 1, 12, 10},
        {4, 0, 6, 3},
    };
    std::uint32_t const expected = 36;
    std::uint32_t const actual = count_max_path_sum_2d_array_as_memo(grid);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, count_max_path_sum____v_0002) {
    std::vector<std::vector<std::uint32_t>> const grid = {
        {1, 2, 8, 1},
        {3, 10, 12, 10},
        {4, 0, 6, 3},
    };
    std::uint32_t const expected = 39;
    std::uint32_t const actual = count_max_path_sum_2d_array_as_memo(grid);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, count_max_path_sum____v_0003) {
    std::vector<std::vector<std::uint32_t>> const grid = {
        {1, 1, 3, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 1, 1, 6, 1, 1, 5, 1, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 5, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {2, 1, 1, 1, 1, 8, 1, 1, 1, 1, 1, 1, 1},
        {2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 9, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 42, 1, 1, 1, 1, 1, 1, 1, 8, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
    std::uint32_t const expected = 82;
    std::uint32_t const actual = count_max_path_sum_2d_array_as_memo(grid);

    ASSERT_EQ(expected, actual);
}



//
// non adjacent sum
// ---------------
//
// Write a function, nonAdjacentSum, that takes in an array of numbers as
// an argument. The function should return the maximum sum of non-adjacent
// elements in the array. There is no limit on how many elements can be
// taken into the sum as long as they are not adjacent.
//
namespace {
namespace details { } /* namespace details */
static std::uint32_t find_max_non_adjacent_sum__with_no_helper(
    std::vector<std::uint32_t> const& nums
) {
    //
    // Example 1:
    //
    //   2, 4, 5, 12, 7
    //   2, 4, 7, 16, 14
    //
    //
    // Example 2:
    //
    // 7  5  5  12  17  29
    // 7  5 12  19  29  48
    //
    //
    // Example 3:
    //
    //   nums_idx:: -3  -2  -1   0   1   2   3   4   5   6
    //   num::                   7   5   5  12  17  29
    //   max_idx::   0   1   2   3   4   5   6   7   8   9
    //   max::       0   0   0   7   5  12  19  29  48
    //
    //
    // Recursive algorithm:
    //
    //   f_0 = n_0
    //   f_1 = n_1
    //   f_2 = n_2 + f_0
    //   f_3 = n_3 + max(f_0, f_1)
    //   f_4 = n_4 + max(f_1, f_2)
    //   f_5 = ...
    //
    //   f_k = n_k + max(f_(k - 2), f_(k - 3))
    //
    auto const nums_size = static_cast<std::uint32_t>(nums.size());
    std::vector<std::uint32_t> max_sum(3, 0);
    for(std::uint32_t i = 0; nums_size > i; ++i) {
        max_sum.push_back(nums[i] + std::max<>(max_sum[i], max_sum[1 + i]));
    }



    auto const ms_size = static_cast<std::uint32_t>(max_sum.size());
    return std::max<>(max_sum[ms_size - 1], max_sum[ms_size - 2]);
}
} /* namespace */


TEST_F(dynamic_programming_Test, find_max_non_adjacent_sum____v0000) {
    std::vector<std::uint32_t> const nums{2, 4, 5, 12, 7};

    std::uint32_t const expected = 16;
    std::uint32_t const actual =
        find_max_non_adjacent_sum__with_no_helper(nums);


    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, find_max_non_adjacent_sum____v0001) {
    std::vector<std::uint32_t> const nums{7, 5, 5, 12};

    std::uint32_t const expected = 19;
    std::uint32_t const actual =
        find_max_non_adjacent_sum__with_no_helper(nums);


    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, find_max_non_adjacent_sum____v0002) {
    std::vector<std::uint32_t> const nums{7, 5, 5, 12, 17, 29};

    std::uint32_t const expected = 48;
    std::uint32_t const actual =
        find_max_non_adjacent_sum__with_no_helper(nums);


    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, find_max_non_adjacent_sum____v0003) {
    std::vector<std::uint32_t> const nums{72, 62, 10, 6,  20, 19, 42,
                                          46, 24, 78, 30, 41, 75, 38,
                                          23, 28, 66, 55, 12, 17, 9,
                                          12, 3,  1,  19, 30, 50, 20};

    std::uint32_t const expected = 488;
    std::uint32_t const actual =
        find_max_non_adjacent_sum__with_no_helper(nums);


    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, find_max_non_adjacent_sum____v0004) {
    std::vector<std::uint32_t> const nums{
        72, 62, 10, 6,  20, 19, 42, 46, 24, 78, 30, 41, 75, 38, 23, 28,
        66, 55, 12, 17, 83, 80, 56, 68, 6,  22, 56, 96, 77, 98, 61, 20,
        0,  76, 53, 74, 8,  22, 92, 37, 30, 41, 75, 38, 23, 28, 66, 55,
        12, 17, 72, 62, 10, 6,  20, 19, 42, 46, 24, 78, 42
    };

    std::uint32_t const expected = 1465;
    std::uint32_t const actual =
        find_max_non_adjacent_sum__with_no_helper(nums);


    ASSERT_EQ(expected, actual);
}

//
// summing squares
// ---------------
// Write a function, summingSquares, that takes a target number as an
// argument. The function should return the minimum number of perfect
// squares that sum to the target. A perfect square is a number of the form
// (i*i) where i >= 1.
//
// For example: 1, 4, 9, 16 are perfect squares, but 8 is not perfect square
//
namespace {
namespace details {
static std::uint32_t
find_min_number_of_summing_perfect_squares__helper_hashmap(
    std::uint32_t const n,
    std::unordered_map<std::uint32_t, std::uint32_t>* memo
) {
    if(auto it = memo->find(n); std::end(*memo) != it) {
        return it->second;
    }


    // we can use at most 'n' ones:
    //
    //  n = 1^2 + 1^2 + ... + 1^2
    //
    std::uint32_t result = 1 + n;
    std::uint32_t cur = static_cast<std::uint32_t>(std::sqrt(n));
    std::uint32_t cur_square = cur * cur;

    if(n == cur_square) {
        (*memo)[n] = 1;
        return 1;
    }


    while(0 != cur_square) {
        // fmt::print(
        //     "looking for {} = {}^2 + count({})\n", n, cur, n - cur_square
        // );
        result = std::min<>(
            result,
            find_min_number_of_summing_perfect_squares__helper_hashmap(
                cur_square, memo
            ) +
                find_min_number_of_summing_perfect_squares__helper_hashmap(
                    n - cur_square, memo
                )
        );

        --cur;
        cur_square = cur * cur;
    }

    (*memo)[n] = result;
    return result;
}
} /* namespace details */
static std::uint32_t
find_min_number_of_summing_perfect_squares(std::uint32_t const n) {
    std::unordered_map<std::uint32_t, std::uint32_t> memo{};
    memo[1] = 1;
    memo[0] = 0;

    auto const result =
        details::find_min_number_of_summing_perfect_squares__helper_hashmap(
            n, &memo
        );

    // for(auto const kv : memo) {
    //     fmt::print("memo[{}] = {}\n", kv.first, kv.second);
    // }

    return result;
}
} /* namespace */


TEST_F(
    dynamic_programming_Test,
    find_min_number_of_summing_perfect_squares___v_0000
) {
    std::uint32_t const number = 8;

    std::uint32_t const expected = 2;
    std::uint32_t const actual =
        find_min_number_of_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(
    dynamic_programming_Test,
    find_min_number_of_summing_perfect_squares___v_0001
) {
    std::uint32_t const number = 9;

    std::uint32_t const expected = 1;
    std::uint32_t const actual =
        find_min_number_of_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(
    dynamic_programming_Test,
    find_min_number_of_summing_perfect_squares___v_0002
) {
    std::uint32_t const number = 12;

    std::uint32_t const expected = 3;
    std::uint32_t const actual =
        find_min_number_of_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(
    dynamic_programming_Test,
    find_min_number_of_summing_perfect_squares___v_0003
) {
    std::uint32_t const number = 1;

    std::uint32_t const expected = 1;
    std::uint32_t const actual =
        find_min_number_of_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(
    dynamic_programming_Test,
    find_min_number_of_summing_perfect_squares___v_0004
) {
    std::uint32_t const number = 31;

    std::uint32_t const expected = 4;
    std::uint32_t const actual =
        find_min_number_of_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(
    dynamic_programming_Test,
    find_min_number_of_summing_perfect_squares___v_0005
) {
    std::uint32_t const number = 50;

    std::uint32_t const expected = 2;
    std::uint32_t const actual =
        find_min_number_of_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(
    dynamic_programming_Test,
    find_min_number_of_summing_perfect_squares___v_0006
) {
    std::uint32_t const number = 68;

    std::uint32_t const expected = 2;
    std::uint32_t const actual =
        find_min_number_of_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(
    dynamic_programming_Test,
    find_min_number_of_summing_perfect_squares___v_0007
) {
    std::uint32_t const number = 87;

    std::uint32_t const expected = 4;
    std::uint32_t const actual =
        find_min_number_of_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}



namespace {
namespace details {
static std::vector<std::uint32_t> find_summing_perfect_squares(
    std::uint32_t const n,
    std::unordered_map<std::uint32_t, std::vector<std::uint32_t>>* const memo
) {
    if(auto const it = memo->find(n); std::end(*memo) != it) {
        return it->second;
    }

    std::uint32_t cur = static_cast<std::uint32_t>(std::sqrt(n));
    std::uint32_t cur_square = cur * cur;
    std::vector<std::uint32_t> result(n, 1);

    if(n == cur_square) {
        (*memo)[n].emplace_back(cur);
        return std::vector<std::uint32_t>{cur};
    }

    while(0 != cur) {
        auto const left = find_summing_perfect_squares(cur_square, memo);
        auto const right = find_summing_perfect_squares(n - cur_square, memo);

        if(result.size() > left.size() + right.size()) {
            result = left;

            result.insert(
                std::end(result), std::begin(right), std::end(right)
            );
        }
        --cur;
        cur_square = cur * cur;
    }


    (*memo)[n] = result;
    return result;
}
} /* namespace details */
static std::vector<std::uint32_t>
find_summing_perfect_squares(std::uint32_t const n) {
    std::unordered_map<std::uint32_t, std::vector<std::uint32_t>> memo{};
    memo[1].emplace_back(1);
    memo[0].emplace_back(0);

    auto const result = details::find_summing_perfect_squares(n, &memo);
    // for(auto const e : result) {
    //     fmt::print("e: {}\n", e);
    // }
    return result;
}
} /* namespace */
TEST_F(dynamic_programming_Test, find_summing_perfect_squares___mine_v_0000) {
    std::uint32_t const number = 1789;

    std::vector<std::uint32_t> const expected{42, 5};
    std::vector<std::uint32_t> const actual =
        find_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, find_summing_perfect_squares___mine_v_0001) {
    std::uint32_t const number = 1611;

    std::vector<std::uint32_t> const expected{39, 9, 3};
    std::vector<std::uint32_t> const actual =
        find_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, find_summing_perfect_squares___mine_v_0002) {
    std::uint32_t const number = 285;

    std::vector<std::uint32_t> const expected{16, 5, 2};
    std::vector<std::uint32_t> const actual =
        find_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, find_summing_perfect_squares___v_0000) {
    std::uint32_t const number = 8;

    std::vector<std::uint32_t> const expected{2, 2};
    std::vector<std::uint32_t> const actual =
        find_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, find_summing_perfect_squares___v_0001) {
    std::uint32_t const number = 9;

    std::vector<std::uint32_t> const expected{3};
    std::vector<std::uint32_t> const actual =
        find_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, find_summing_perfect_squares___v_0002) {
    std::uint32_t const number = 12;

    std::vector<std::uint32_t> const expected{2, 2, 2};
    std::vector<std::uint32_t> const actual =
        find_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, find_summing_perfect_squares___v_0003) {
    std::uint32_t const number = 1;

    std::vector<std::uint32_t> const expected{1};
    std::vector<std::uint32_t> const actual =
        find_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, find_summing_perfect_squares___v_0004) {
    std::uint32_t const number = 31;

    std::vector<std::uint32_t> const expected{5, 2, 1, 1};
    std::vector<std::uint32_t> const actual =
        find_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, find_summing_perfect_squares___v_0005) {
    std::uint32_t const number = 50;

    // std::vector<std::uint32_t> const expected{5, 5};
    std::vector<std::uint32_t> const expected{7, 1};
    std::vector<std::uint32_t> const actual =
        find_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, find_summing_perfect_squares___v_0006) {
    std::uint32_t const number = 68;

    std::vector<std::uint32_t> const expected{8, 2};
    std::vector<std::uint32_t> const actual =
        find_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}
TEST_F(dynamic_programming_Test, find_summing_perfect_squares___v_0007) {
    std::uint32_t const number = 87;

    std::vector<std::uint32_t> const expected{9, 2, 1, 1};
    std::vector<std::uint32_t> const actual =
        find_summing_perfect_squares(number);

    ASSERT_EQ(expected, actual);
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */
