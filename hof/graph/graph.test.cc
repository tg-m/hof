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

#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */
