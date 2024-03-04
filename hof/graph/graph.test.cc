/**
 * @file
 * Copyright (C) 2024-present Tomasz G. Markiewicz (software.tgm@gmail.com)
 *
 * Created on Mar 2, 2024
 *
 */

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif /* __clang__ */

#include <memory>

#include <fmt/format.h>
#include <fmt/ranges.h>


#include "gtest-wrapper.hh"

#include "graph.hh"


// #include "common/debug.hh"

class graph_Test : public testing::Test {
public:
    virtual void SetUp() override { }
    virtual void TearDown() override { }
};

TEST_F(graph_Test, fixture_self_test) { }
TEST_F(graph_Test, DISABLED_test) { }

TEST_F(graph_Test, 2nd_dtor) {
    { std::make_shared<hof::graph>(); }
    {
        hof::graph const* ptr = new hof::graph();
        delete ptr;
    }
}


TEST_F(graph_Test, yt__example__copy_from_old_main) {

    auto const print_elem = [](auto const& elem) {
        fmt::print("Visited: {}\n", elem);
        return hof::visit_result_t::do_end_normally;
    };

    {
        using elem_t = std::string;
        hof::adj_list_t<elem_t> adj_list{
            {"a", {"b", "c", "f"}},
            {"b", {"d"}},
            {"c", {"e"}},
            {"d", {"f"}},
            {"e", {"a"}},
            {"f", {"a", "b"}},
        };



        fmt::print("\ndepth...\n");
        fmt::print("----------------\n");
        hof::depth_first_traversal<elem_t>(adj_list, elem_t{'a'}, print_elem);

        fmt::print("\ndepth generic...\n");
        fmt::print("----------------\n");
        hof::generic_graph_traversal<
            hof::graph_traversal_type_t::depth_first,
            elem_t>(adj_list, elem_t{'a'}, print_elem);

        fmt::print("\nbreadth...\n");
        fmt::print("----------------\n");
        hof::breadth_first_tranversal<elem_t>(
            adj_list, elem_t{'a'}, print_elem
        );

        fmt::print("\nbreadth generic...\n");
        fmt::print("----------------\n");
        hof::generic_graph_traversal<
            hof::graph_traversal_type_t::breadth_first,
            elem_t>(adj_list, elem_t{'a'}, print_elem);
    }
    {
        using hp_elem_t = char;
        hof::adj_list_t<hp_elem_t> const adj_list{
            {'f', {'g', 'i'}},
            {'g', {'h'}},
            {'h', {}},
            {'i', {'g', 'k'}},
            {'j', {'i'}},
            {'k', {}},
        };
        auto const call_has_path = [&](auto src, auto dst) {
            auto const result = hof::has_path<hp_elem_t>(adj_list, src, dst);
            fmt::print(
                "has_path<...>(..., '{}', '{}'): {}\n", src, dst, result
            );
            return result;
        };
        ASSERT_TRUE(call_has_path('f', 'i'));
        ASSERT_FALSE(call_has_path('i', 'f'));
        ASSERT_TRUE(call_has_path('i', 'h'));
    }

    {
        fmt::print("\n\n");
        using hp_elem_t = char;
        fmt::print("Uni-directional edge list...\n");
        fmt::print("----------------\n");
        hof::print(hof::edge_list_to_adj_list<
                   hof::edge_connect_t::unidirectional,
                   hp_elem_t>({
            {'i', 'j'},
            {'k', 'i'},
            {'m', 'k'},
            {'k', 'l'},
            {'o', 'n'},
        }));


        fmt::print("Bi-directional edge list...\n");
        fmt::print("----------------\n");
        hof::print(hof::edge_list_to_adj_list<
                   hof::edge_connect_t::bidirectional,
                   hp_elem_t>({
            {'i', 'j'},
            {'k', 'i'},
            {'m', 'k'},
            {'k', 'l'},
            {'o', 'n'},
        }));
    }
}


TEST_F(graph_Test, yt__example__idead_for_graphs) {
    auto const print_f = [](auto const& elem) {
        fmt::print("elem: {}\n", elem);
        return hof::visit_result_t::do_end_normally;
    };

    using elem_t = char;

    hof::adj_list_t<elem_t> const adj_list{
        {'a', {'b', 'c'}},
        {'b', {'a', 'c'}},
        {'c', {'a', 'b', 'd'}},
        {'d', {'a', 'c'}},
        {'e', {'f', 'g'}},
        {'f', {'g'}},
        {'g', {'h'}},
        {'h', {'e'}},
    };
    hof::depth_first_traversal<elem_t>(adj_list, 'a', print_f);

    {
        bool is_a_connected_to_d_result = false;
        auto const is_a_to_d_f = [&](auto const elem) {
            if('e' == elem) {
                is_a_connected_to_d_result = true;
                return hof::visit_result_t::do_end_by_visit;
            }
            return hof::visit_result_t::do_end_normally;
        };
        hof::depth_first_traversal<elem_t>(adj_list, 'a', is_a_to_d_f);
        fmt::print(
            "is_a_connected_to_d_result: {}\n", is_a_connected_to_d_result
        );
        ASSERT_FALSE(is_a_connected_to_d_result);
    }
}



TEST_F(graph_Test, yt__example__are_nodes_connected_to_each_other) {
    using elem_t = char;

    hof::adj_list_t<elem_t> const adj_list{
        {'a', {'b', 'c'}},
        {'b', {'a', 'c'}},
        {'c', {'a', 'b', 'd'}},
        {'d', {'a', 'c'}},
        {'e', {'f', 'g'}},
        {'f', {'g'}},
        {'g', {'h'}},
        {'h', {'e'}},
    };


    auto const make_is_connected_to = [](elem_t const& conn_to, bool* result) {
        return [=](elem_t const& elem) {
            // fmt::print("visiting: {}\n", elem);
            if(conn_to == elem) {
                *result = true;
                return hof::visit_result_t::do_end_by_visit;
            }
            return hof::visit_result_t::do_end_normally;
        };
    };


    for(auto const& [from, to, expected] : {
            std::make_tuple('a', 'b', true),
            std::make_tuple('a', 'e', false),
            std::make_tuple('f', 'f', true),
            std::make_tuple('z', 'z', false), // test node not in the graph
        }) {
        bool result = false;
        fmt::print(
            "is [{}] connected to: [{}]: {}\n",
            from,
            to,
            (hof::depth_first_traversal<elem_t>(
                 adj_list, from, make_is_connected_to(to, &result)
             ),
             result)
        );
        ASSERT_EQ(expected, result);
    }
}

TEST_F(
    graph_Test,
    yt__example__count_disconnected_sub_graphs___std_int32_t___0
) {
    using elem_t = std::int32_t;

    hof::adj_list_t<elem_t> const adj_list{
        {3, {}},
        {4, {6}},
        {6, {4, 5, 7, 8}},
        {8, {6}},
        {7, {6}},
        {5, {6}},
        {1, {2}},
        {2, {1}},
    };

    std::uint32_t const expected = 3;
    std::uint32_t const actual = hof::count_disconnected_sub_graphs(adj_list);


    ASSERT_EQ(expected, actual);
}

TEST_F(
    graph_Test,
    yt__example__count_disconnected_sub_graphs___std_int32_t___1
) {
    using elem_t = std::int32_t;

    hof::adj_list_t<elem_t> const adj_list{
        {0, {8, 1, 5}},
        {1, {0}},
        {5, {0, 8}},
        {8, {0, 5}},
        {2, {3, 4}},
        {3, {2, 4}},
        {4, {3, 2}},
    };

    std::uint32_t const expected = 2;
    std::uint32_t const actual = hof::count_disconnected_sub_graphs(adj_list);


    ASSERT_EQ(expected, actual);
}

TEST_F(graph_Test, count_disconnected_sub_graphs__char) {
    using elem_t = char;

    hof::adj_list_t<elem_t> const adj_list{
        {'a', {'b', 'c'}},
        {'b', {'a', 'c'}},
        {'c', {'a', 'b', 'd'}},
        {'d', {'a', 'c'}},
        {'e', {'f', 'g'}},
        {'f', {'g'}},
        {'g', {'h'}},
        {'h', {'e'}},
    };

    std::uint32_t const expected = 2;
    auto const result = hof::count_disconnected_sub_graphs<elem_t>(adj_list);
    fmt::print("num_of_disconn_sub_graphs: {}\n", result);

    ASSERT_EQ(expected, result);
}

TEST_F(graph_Test, count_disconnected_sub_graphs__std_int32_t___0) {
    using elem_t = std::int32_t;

    hof::adj_list_t<elem_t> const adj_list{
        {3, {}},
        {4, {6}},
        {6, {4, 5, 7, 8}},
        {8, {6}},
        {7, {6}},
        {5, {6}},
        {1, {2}},
        {2, {1}},
    };

    ASSERT_EQ(
        true,
        hof::are_nodes_connected<hof::graph_traversal_type_t::depth_first>(
            adj_list, 1, 2
        )
    );
    ASSERT_EQ(
        true,
        hof::are_nodes_connected<hof::graph_traversal_type_t::depth_first>(
            adj_list, 4, 7
        )
    );

    ASSERT_EQ(
        false,
        hof::are_nodes_connected<hof::graph_traversal_type_t::depth_first>(
            adj_list, 5, 3
        )
    );
    ASSERT_EQ(
        false,
        hof::are_nodes_connected<hof::graph_traversal_type_t::depth_first>(
            adj_list, 5, 2
        )
    );
    ASSERT_EQ(
        false,
        hof::are_nodes_connected<hof::graph_traversal_type_t::depth_first>(
            adj_list, 5, 1
        )
    );
}



TEST_F(
    graph_Test,
    yt__example__find_size_of_the_largest_disconnected_subgraph___std_int32_t___1
) {
    using elem_t = std::int32_t;

    hof::adj_list_t<elem_t> const adj_list{
        {0, {8, 1, 5}},
        {1, {0}},
        {5, {0, 8}},
        {8, {0, 5}},
        {2, {3, 4}},
        {3, {2, 4}},
        {4, {3, 2}},
    };

    std::unordered_set<elem_t> nodes = [&]{
        std::unordered_set<elem_t> result{};
        result.reserve(adj_list.size());
        for(auto const& e : adj_list) {
            result.insert(e.first);
        }
        return result;
    }();


    std::uint32_t const largest_size = [&] {
        std::uint32_t result = 0;

        while(false == nodes.empty()) {
            std::uint32_t current_largest_size = 0;
            hof::generic_graph_traversal<
                hof::graph_traversal_type_t::breadth_first>(
                adj_list,
                *std::begin(nodes),
                [&](elem_t const& current) {
                    nodes.erase(current);
                    ++current_largest_size;
                    return hof::visit_result_t::do_end_normally;
                }
            );

            result = std::max<>(result, current_largest_size);
        }


        return result;
    }();

    std::uint32_t const expected = 4;
    std::uint32_t const actual = largest_size;

    fmt::print("largest_size: {}\n", largest_size);

    ASSERT_EQ(expected, actual);
}




TEST_F(graph_Test, yt__example__shortest_path_length___char___0) {
    using elem_t = char;

    // Graph looks like this:
    //
    // w -- x -- y -- z -- v
    // |                   |
    //  -------------------
    //
    hof::adj_list_t<elem_t> const adj_list{
        {'v', {'w', 'z'}},
        {'w', {'x', 'v'}},
        {'x', {'w', 'y'}},
        {'y', {'x', 'z'}},
        {'z', {'y', 'v'}},
    };


    std::int32_t const expected = 2;
    std::int32_t const actual = hof::shortest_path_length(adj_list, 'w', 'z');
    ASSERT_EQ(expected, actual);


    ASSERT_EQ(2, hof::shortest_path_length(adj_list, 'w', 'y'));
    ASSERT_EQ(2, hof::shortest_path_length(adj_list, 'x', 'z'));
    ASSERT_EQ(2, hof::shortest_path_length(adj_list, 'y', 'v'));
    ASSERT_EQ(2, hof::shortest_path_length(adj_list, 'z', 'w'));
    ASSERT_EQ(2, hof::shortest_path_length(adj_list, 'v', 'x'));


    ASSERT_EQ(1, hof::shortest_path_length(adj_list, 'w', 'x'));
    ASSERT_EQ(1, hof::shortest_path_length(adj_list, 'x', 'y'));
    ASSERT_EQ(1, hof::shortest_path_length(adj_list, 'y', 'z'));
    ASSERT_EQ(1, hof::shortest_path_length(adj_list, 'z', 'v'));
    ASSERT_EQ(1, hof::shortest_path_length(adj_list, 'v', 'w'));

    ASSERT_EQ(0, hof::shortest_path_length(adj_list, 'w', 'w'));
    ASSERT_EQ(0, hof::shortest_path_length(adj_list, 'x', 'x'));
    ASSERT_EQ(0, hof::shortest_path_length(adj_list, 'y', 'y'));
    ASSERT_EQ(0, hof::shortest_path_length(adj_list, 'z', 'z'));
    ASSERT_EQ(0, hof::shortest_path_length(adj_list, 'v', 'v'));

    ASSERT_EQ(-1, hof::shortest_path_length(adj_list, 'w', 'a'));
    ASSERT_EQ(-1, hof::shortest_path_length(adj_list, 'x', 'a'));
    ASSERT_EQ(-1, hof::shortest_path_length(adj_list, 'y', 'a'));
    ASSERT_EQ(-1, hof::shortest_path_length(adj_list, 'z', 'a'));
    ASSERT_EQ(-1, hof::shortest_path_length(adj_list, 'v', 'a'));
}


TEST_F(graph_Test, yt__example__shortest_path_length___char___4) {
    using elem_t = char;


    auto const adj_list = hof::edge_list_to_adj_list<hof::edge_connect_t::bidirectional, elem_t>({
            {'a', 'c'},
            {'a', 'b'},
            {'c', 'b'},
            {'c', 'd'},
            {'b', 'd'},
            {'e', 'd'},
            {'g', 'g'},
    });


    std::int32_t const expected = -1;
    std::int32_t const actual = hof::shortest_path_length(adj_list, 'b', 'g');
    ASSERT_EQ(expected, actual);


}

static std::pair<char, char> get_water_land_descriptors() {
    return std::make_pair('W', 'L');
}
static std::uint32_t island_count(std::vector<std::vector<char>> const& grid) {
    auto const [W, L] = get_water_land_descriptors();



    auto const islands_traverse_depth_first =
        [](std::vector<std::vector<char>> const& grid_,
           std::pair<std::uint32_t, std::uint32_t> const start_row_col,
           std::vector<std::vector<bool>>* visited) {
            auto const rows_num = static_cast<std::uint32_t>(grid_.size());
            auto const cols_num = static_cast<std::uint32_t>(grid_[0].size());

            auto const [xW, xL] = get_water_land_descriptors();

            std::vector<std::pair<std::uint32_t, std::uint32_t>> lifo{};

            lifo.push_back(start_row_col);

            while(false == lifo.empty()) {
                auto const [row, col] = lifo.back();
                lifo.pop_back();

                // fmt::print("inspecting: row, col: [{}][{}]\n", row, col);

                if(true == (*visited)[row][col]) { continue; }

                (*visited)[row][col] = true;


                auto const neighbours = std::vector<std::pair<std::uint32_t, std::uint32_t>>{
                    // INFO(tgm): We depend here on the fact that:
                    //
                    //              static_cast<std::uint32_t>(-1) = 2^32 - 1
                    //
                    //            and this is WAY TOO LARGE size of the grid
                    //            to be able to look for islands on it.
                    //
                    //            This assumption, however, can be lifted by
                    //            taking more caution when adding (row, col)
                    //            that are placed on the edge of the grid!
                    //
                    // clang-format off
                    {row - 1, col    }, // up
                    {row + 1, col    }, // down
                    {row    , col - 1}, // left
                    {row    , col + 1}, // right
                    // clang-format on
                };

                for(auto const& n : neighbours) {
                    auto const [r, c] = n;


                    if((rows_num > r && cols_num > c) &&
                       (false == (*visited)[r][c]) && xL == grid_[r][c]) {
                        // fmt::print("  inserting: (r, c) = [{}]\n", n);
                        lifo.push_back(n);
                    }
                }
            }

        };


    std::vector<std::vector<bool>> visited = [&] {
        std::vector<std::vector<bool>> result{};

        for(auto const& row : grid) {
            result.emplace_back(std::vector<bool>(row.size(), false));
        }

        return result;
    }();

    std::uint32_t result = 0;

    // Why 'c' and 'r' instead of more descriptive names?
    //
    // 'c' and 'r' are used for brevity
    //
    // 'r' - row number
    // 'c' - column number
    for(std::uint32_t r = 0; grid.size() > r; ++r) {
        auto const& row = grid[r];
        for(std::uint32_t c = 0; row.size() > c; ++c) {
            if(W == row[c]) { continue; }
            if(true == visited[r][c]) { continue; }

            fmt::print("traversing: (r, c:) [{}]\n", std::make_pair(r, c));

            islands_traverse_depth_first(grid, std::make_pair(r, c), &visited);

            ++result;
        }
    }


    return result;
}

TEST_F(graph_Test, yt__example__island_count_problem___x) {
    // '_' and 'X' are more readable
    // '_' - water
    // 'X' - land
    auto const [_, X] = get_water_land_descriptors();

    std::vector<std::vector<char>> const grid{
        {_, X, _, _, X, _},
        {X, X, _, _, X, _},
        {_, X, _, _, _, _},
        {_, _, _, X, X, _},
        {_, X, _, X, X, _},
        {_, _, _, _, _, _},
    };

    std::uint32_t const expected = 4;
    std::uint32_t const actual = island_count(grid);

    ASSERT_EQ(expected, actual);
}


TEST_F(graph_Test, yt__example__island_count_problem___00) {
    // '_' and 'X' are more readable
    // '_' - water
    // 'X' - land
    auto const [_, X] = get_water_land_descriptors();

    std::vector<std::vector<char>> const grid{
        {_, X, _, _, _},
        {_, X, _, _, _},
        {_, _, _, X, _},
        {_, _, X, X, _},
        {X, _, _, X, X},
        {X, X, _, _, _},
    };

    std::uint32_t const expected = 3;
    std::uint32_t const actual = island_count(grid);

    ASSERT_EQ(expected, actual);
}
TEST_F(graph_Test, yt__example__island_count_problem___01) {
    // '_' and 'X' are more readable
    // '_' - water
    // 'X' - land
    auto const [_, X] = get_water_land_descriptors();

    std::vector<std::vector<char>> const grid{
        {X, _, _, X, _},
        {X, _, _, X, X},
        {_, X, _, X, _},
        {_, _, _, _, _},
        {_, _, X, X, X},
    };

    std::uint32_t const expected = 4;
    std::uint32_t const actual = island_count(grid);

    ASSERT_EQ(expected, actual);
}
TEST_F(graph_Test, yt__example__island_count_problem___02) {
    // '_' and 'X' are more readable
    // '_' - water
    // 'X' - land
    auto const [_, X] = get_water_land_descriptors();

    std::vector<std::vector<char>> const grid{
        {X, X, X},
        {X, X, X},
        {X, X, X},
    };

    std::uint32_t const expected = 1;
    std::uint32_t const actual = island_count(grid);

    ASSERT_EQ(expected, actual);
}
TEST_F(graph_Test, yt__example__island_count_problem___03) {
    // '_' and 'X' are more readable
    // '_' - water
    // 'X' - land
    auto const [_, X] = get_water_land_descriptors();

    std::vector<std::vector<char>> const grid{
        {_, _, _},
        {_, _, _},
        {_, _, _},
    };

    std::uint32_t const expected = 0;
    std::uint32_t const actual = island_count(grid);

    ASSERT_EQ(expected, actual);
}
TEST_F(graph_Test, yt__example__island_count_problem___mine_BIG) {
    // '_' and 'X' are more readable
    // '_' - water
    // 'X' - land
    auto const [_, X] = get_water_land_descriptors();

    std::vector<std::vector<char>> const grid{
        // clang-format off
        {_, X, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, _, _, X, X, X, X, X, X, X, X, X, X, X, X, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, _, _, X, _, _, _, _, _, _, _, _, _, _, X, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, X, X, X, X, X, _, X, _, _, X, X, X, X, X, X, X, _, X, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, X, _, _, _, X, _, X, _, _, X, _, _, _, _, _, X, _, X, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, X, _, X, _, X, _, X, X, _, X, _, X, X, X, _, X, _, X, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, X, _, _, _, X, _, X, _, _, _, _, _, _, X, _, X, _, X, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, X, _, X, _, _, _, _, X, _, X, _, X, _, X, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, X, X, _, _, X, _, X, X, _, _, _, _, _, X, _, X, _, X, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, X, _, _, X, _, _, X, _, _, _, X, _, X, _, X, _, X, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, X, X, X, X, _, _, X, _, _, _, X, X, X, _, X, _, X, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, _, _, _, X, _, _, _, _, X, X, _, X, _, X, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, X, X, X, X, X, X, _, _, _, _, X, _, _, X, _, X, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, X, X, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, X, X, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, X, X, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, X, X, X, _, _, _, X, X, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, X, _, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        // clang-format on
    };

    std::uint32_t const expected = 7;
    std::uint32_t const actual = island_count(grid);

    ASSERT_EQ(expected, actual);
}
TEST_F(graph_Test, yt__example__island_count_problem___mine_CONCENTRIC) {
    // '_' and 'X' are more readable
    // '_' - water
    // 'X' - land
    auto const [_, X] = get_water_land_descriptors();

    std::vector<std::vector<char>> const grid{
        // clang-format off
        {X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},
        {X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, X},
        {X, _, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, _, X},
        {X, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, X, _, X},
        {X, _, X, _, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, _, X, _, X},
        {X, _, X, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, X, X, X, X, X, X, X, X, X, X, X, X, X, X, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, X, _, _, _, _, _, _, _, _, _, _, _, _, X, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, X, _, X, X, X, X, X, X, X, X, X, X, _, X, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, X, _, X, _, _, _, _, _, _, _, _, X, _, X, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, X, _, X, _, X, X, X, X, X, X, _, X, _, X, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, X, _, X, _, X, _, _, _, _, X, _, X, _, X, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, X, _, X, _, X, _, X, X, _, X, _, X, _, X, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, X, _, X, _, X, _, X, X, _, X, _, X, _, X, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, X, _, X, _, X, _, X, X, _, X, _, X, _, X, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, X, _, X, _, X, _, _, _, _, X, _, X, _, X, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, X, _, X, _, X, X, X, X, X, X, _, X, _, X, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, X, _, X, _, _, _, _, _, _, _, _, X, _, X, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, X, _, X, X, X, X, X, X, X, X, X, X, _, X, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, X, _, _, _, _, _, _, _, _, _, _, _, _, X, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, X, X, X, X, X, X, X, X, X, X, X, X, X, X, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, X, _, X, _, X},
        {X, _, X, _, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, _, X, _, X},
        {X, _, X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, X, _, X},
        {X, _, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, _, X},
        {X, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, X},
        {X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},
        // clang-format on
    };

    std::uint32_t const expected = 9;
    std::uint32_t const actual = island_count(grid);

    ASSERT_EQ(expected, actual);
}

static std::pair<std::uint32_t, std::uint32_t>
minmax_island_size(std::vector<std::vector<char>> const& grid) {
    auto const [W, L] = get_water_land_descriptors();

    using position_t = std::pair<std::uint32_t, std::uint32_t>;



    using visited_t = std::vector<std::vector<bool>>;

    auto const find_island_size =
        [](std::vector<std::vector<char>> const& grid_,
           position_t const position,
           visited_t* visited_ptr) {
            auto const max_rows = static_cast<std::uint32_t>(grid_.size());
            auto const max_cols = static_cast<std::uint32_t>(grid_[0].size());


            auto const [xW, xL] = get_water_land_descriptors();

            // auto const [row, col] = position;

            std::vector<position_t> lifo{};


            lifo.push_back(position);


            std::uint32_t size = 0;

            while(false == lifo.empty()) {
                auto const cur_pos = lifo.back();
                lifo.pop_back();
                auto const [row, col] = cur_pos;

                // fmt::print("  cur_pos: {}\n", cur_pos);
                // fmt::print(
                //     "  visited[{}]: {}\n",
                //     cur_pos,
                //     static_cast<bool>((*visited_ptr)[row][col])
                // );
                // fmt::print("  lifo.size(): {}\n", lifo.size());


                if(true == (*visited_ptr)[row][col]) {
                    continue;
                }
                (*visited_ptr)[row][col] = true;

                ++size;


                std::vector<position_t> const neighbours{
                    // clang-format off
                    {row - 1, col    }, // up
                    {row + 1, col    }, // down
                    {row    , col - 1}, // left
                    {row    , col + 1}, // right
                    // clang-format on
                };

                for(auto const& n : neighbours) {
                    auto const [r, c] = n;
                    if(max_rows > r && max_cols > c &&
                       (false == (*visited_ptr)[r][c]) &&
                       (xL == grid_[r][c])) {
                        lifo.push_back(n);
                    }
                }
            }
            return size;
        };

    visited_t visited = [&] {
        visited_t result{};
        for(auto const& row : grid) {
            result.push_back(std::vector<bool>(row.size(), false));
        }
        return result;
    }();


    auto max = static_cast<std::uint32_t>(0);
    auto min = static_cast<std::uint32_t>(-1);
    for(std::uint32_t r = 0; grid.size() > r; ++r) {
        auto const& row = grid[r];
        for(std::uint32_t c = 0; row.size() > c; ++c) {
            if(W == row[c]) {
                continue;
            }
            if(true == visited[r][c]) {
                continue;
            }

            position_t const position = std::make_pair(r, c);
            // fmt::print("traversing: (r, c) [{}] = '{}'\n", position, row[c]);


            std::uint32_t const cur_size =
                find_island_size(grid, position, &visited);

            min = std::min<>(min, cur_size);
            max = std::max<>(max, cur_size);
        }
    }

    if(0 == max) { min = 0; }

    return std::make_pair(min, max);
}
TEST_F(graph_Test, yt__example__island_min_max_count____0000) {
    // '_' and 'X' are more readable
    // '_' - water
    // 'X' - land
    auto const [_, X] = get_water_land_descriptors();

    std::vector<std::vector<char>> const grid{
        {_, X, _, _, _},
        {_, X, _, _, _},
        {_, _, _, X, _},
        {_, _, X, X, _},
        {X, _, _, X, X},
        {X, X, _, _, _},
    };


    auto const expected = std::pair<std::uint32_t, std::uint32_t>{2, 5};
    auto const actual = minmax_island_size(grid);
    fmt::print("(min, max) = {}\n", actual);

    ASSERT_EQ(expected, actual);
}
TEST_F(graph_Test, yt__example__island_min_max_count____0001) {
    // '_' and 'X' are more readable
    // '_' - water
    // 'X' - land
    auto const [_, X] = get_water_land_descriptors();

    std::vector<std::vector<char>> const grid{
        {X, _, _, X, _},
        {X, _, _, X, X},
        {_, X, _, X, _},
        {_, _, _, _, _},
        {_, _, X, X, X},
    };


    auto const expected = std::pair<std::uint32_t, std::uint32_t>{1, 4};
    auto const actual = minmax_island_size(grid);
    fmt::print("(min, max) = {}\n", actual);

    ASSERT_EQ(expected, actual);
}
TEST_F(graph_Test, yt__example__island_min_max_count____0002) {
    // '_' and 'X' are more readable
    // '_' - water
    // 'X' - land
    auto const [_, X] = get_water_land_descriptors();

    std::vector<std::vector<char>> const grid{
        {X, X, X},
        {X, X, X},
        {X, X, X},
    };


    auto const expected = std::pair<std::uint32_t, std::uint32_t>{9, 9};
    auto const actual = minmax_island_size(grid);
    fmt::print("(min, max) = {}\n", actual);

    ASSERT_EQ(expected, actual);
}
TEST_F(graph_Test, yt__example__island_min_max_count____0003) {
    // '_' and 'X' are more readable
    // '_' - water
    // 'X' - land
    auto const [_, X] = get_water_land_descriptors();

    std::vector<std::vector<char>> const grid{
        {X, X},
        {_, _},
        {X, X},
        {_, X},
    };


    auto const expected = std::pair<std::uint32_t, std::uint32_t>{2, 3};
    auto const actual = minmax_island_size(grid);
    fmt::print("(min, max) = {}\n", actual);

    ASSERT_EQ(expected, actual);
}


TEST_F(graph_Test, yt__example__island_min_max_count____000x) {
    // '_' and 'X' are more readable
    // '_' - water
    // 'X' - land
    auto const [_, X] = get_water_land_descriptors();

    std::vector<std::vector<char>> const grid{
        {_, X, _, _, X, _},
        {X, X, _, _, X, _},
        {_, X, _, _, _, _},
        {_, _, _, X, X, _},
        {_, _, _, X, X, _},
        {_, _, _, X, _, _},
    };


    auto const expected = std::pair<std::uint32_t, std::uint32_t>{2, 5};
    auto const actual = minmax_island_size(grid);
    fmt::print("(min, max) = {}\n", actual);

    ASSERT_EQ(expected, actual);
}


TEST_F(graph_Test, yt__example__island_min_max_count____mine_CHESS_BOARD) {
    // '_' and 'X' are more readable
    // '_' - water
    // 'X' - land
    auto const [_, X] = get_water_land_descriptors();

    std::vector<std::vector<char>> const grid{
        {_, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _},
        {_, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _},
        {_, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _},
        {_, X, _, X, _, X, _, X},
        {X, _, X, _, X, _, X, _},
    };


    auto const expected = std::pair<std::uint32_t, std::uint32_t>{1, 1};
    auto const actual = minmax_island_size(grid);
    fmt::print("(min, max) = {}\n", actual);

    ASSERT_EQ(expected, actual);
}
TEST_F(graph_Test, yt__example__island_min_max_count____mine_EMPTY) {
    // '_' and 'X' are more readable
    // '_' - water
    // 'X' - land
    auto const [_, X] = get_water_land_descriptors();

    std::vector<std::vector<char>> const grid{
        {_, _, _},
        {_, _, _},
        {_, _, _},
    };


    auto const expected = std::pair<std::uint32_t, std::uint32_t>{0, 0};
    auto const actual = minmax_island_size(grid);
    fmt::print("(min, max) = {}\n", actual);

    ASSERT_EQ(expected, actual);
}



#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */
