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
    virtual void SetUp() override {
    }
    virtual void TearDown() override {
    }
};

TEST_F(graph_Test, fixture_self_test) {
}
TEST_F(graph_Test, DISABLED_test) {
}

TEST_F(graph_Test, 2nd_dtor) {
    {
        std::make_shared<hof::graph>();
    }
    {
        hof::graph const* ptr = new hof::graph();
        delete ptr;
    }
}


TEST_F(graph_Test, copy_from_old_main) {

    auto const print_elem = [](auto const& elem) {
        fmt::print("Visited: {}\n", elem);
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
        hof::generic_graph_traversal<hof::graph_traversal_type_t::depth_first, elem_t>(adj_list, elem_t{'a'}, print_elem);

        fmt::print("\nbreadth...\n");
        fmt::print("----------------\n");
        hof::breadth_first_tranversal<elem_t>(adj_list, elem_t{'a'}, print_elem);

        fmt::print("\nbreadth generic...\n");
        fmt::print("----------------\n");
        hof::generic_graph_traversal<hof::graph_traversal_type_t::breadth_first, elem_t>(adj_list, elem_t{'a'}, print_elem);
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
        };
        call_has_path('f', 'i');
        call_has_path('i', 'f');
        call_has_path('i', 'h');
    }

    {
        fmt::print("\n\n");
        using hp_elem_t = char;
        fmt::print("Uni-directional edge list...\n");
        fmt::print("----------------\n");
        hof::print(hof::edge_list_to_adj_list<hof::edge_connect_t::unidirectional, hp_elem_t>({
            {'i', 'j'},
            {'k', 'i'},
            {'m', 'k'},
            {'k', 'l'},
            {'o', 'n'},
        }));


        fmt::print("Bi-directional edge list...\n");
        fmt::print("----------------\n");
        hof::print(hof::edge_list_to_adj_list<hof::edge_connect_t::bidirectional, hp_elem_t>({
            {'i', 'j'},
            {'k', 'i'},
            {'m', 'k'},
            {'k', 'l'},
            {'o', 'n'},
        }));


    }



}
#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */
