/**
 * @file
 * Copyright (C) 2024-present Tomasz G. Markiewicz (software.tgm@gmail.com)
 *
 * Created on Mar 2, 2024
 *
 */

#ifndef HOF_GRAPH_GRAPH_HH_
#define HOF_GRAPH_GRAPH_HH_


#include <cstdint>



#include <queue>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>



#include <fmt/format.h>
#include <fmt/ranges.h>


#include "concepts/visitable/visitable.hh"


namespace hof {

class graph final {
public:
    graph();
    virtual ~graph() noexcept;

private:
    /* no implementation */
    graph(graph const&) = delete;
    graph(graph&&) = delete;
    graph& operator=(graph const&) = delete;
    graph& operator=(graph&&) = delete;
};






template<typename T>
using adj_list_t = std::unordered_map<T, std::vector<T>>;

template<typename T>
using edge_list_t = std::vector<std::pair<T, T>>;

enum class graph_traversal_type_t { depth_first, breadth_first };

enum class edge_connect_t { unidirectional, bidirectional };




// template<typename F, typename T>
// concept VisitableWithResult = requires(F f, T t) {
//     { f(t) } -> std::convertible_to<visit_result_t>;
// };

template<graph_traversal_type_t graph_traversal_v, typename T, Visitable<T> Visit_f>
static void generic_graph_traversal(
    adj_list_t<T> const& adj_list,
    T const& first,
    Visit_f const& visit
) {
    using it_t = typename adj_list_t<T>::const_iterator;

    std::deque<it_t> trav_queue{}; // i.e.: traversal queue

    trav_queue.push_back(adj_list.find(first));
    if(std::end(adj_list) == trav_queue.back()) {
        return;
    }

    // {
    //     auto const it = adj_list.find(first);
    //     if(std::end(adj_list) == it) {
    //         return;
    //     }
    //     trav_queue.push_back(it);
    // }



    auto const [x_begin, x_end, x_take_from_queue] = [] {
        if constexpr(graph_traversal_type_t::depth_first ==
                     graph_traversal_v) {
            return std::make_tuple(
                [](auto const& container) { return std::rbegin(container); },
                [](auto const& container) { return std::rend(container); },
                [](auto* container) {
                    auto result = container->back();
                    container->pop_back();
                    return result;
                }
            );
        }
        else {
            return std::make_tuple(
                [](auto const& container) { return std::begin(container); },
                [](auto const& container) { return std::end(container); },
                [](auto* container) {
                    auto result = container->front();
                    container->pop_front();
                    return result;
                }
            );
        }
    }();


    std::unordered_set<T const*> visited{};

    while(false == trav_queue.empty()) {
        // auto const it = [&] {
        //     if constexpr(graph_traversal_type_t::depth_first ==
        //     graph_traversal_v) {
        //         auto result = trav_queue.back();
        //         trav_queue.pop_back();
        //         return result;
        //     }
        //     else {
        //         // graph_traversal_type_t::breadth_first
        //         auto result = trav_queue.front();
        //         trav_queue.pop_front();
        //         return result;
        //     }
        // }();
        auto const it = x_take_from_queue(&trav_queue);


        if constexpr(false) {
#pragma GCC diagnostic push
            // ISO C++ forbids braced-groups within expressions (-Wpedantic)
#pragma GCC diagnostic ignored "-Wpedantic"

            // NOTE(tgm): effectively the same thing that is in the else branch
            //            but written in a more concise style...
            std::end(visited) != visited.find(&(it->first))
                ? ({ continue; })
                : (visited.insert(&(it->first)), static_cast<void>(nullptr));

#pragma GCC diagnostic pop
        }
        else {
            if(false == visited.insert(&(it->first)).second) {
                continue;
            }
            // if(std::end(visited) != visited.find(&(it->first))) {
            //     continue;
            // }
            // visited.insert(&(it->first));
        }


        // visit(it->first);
        if(visit_result_t::do_end_by_visit == visit(it->first)) {
            return;
        }

        auto const trq_end = x_end(it->second);
        for(auto trq_it = x_begin(it->second); trq_end != trq_it; ++trq_it) {

            if(auto next_node = adj_list.find(*trq_it);
               std::end(adj_list) != next_node) {
                trav_queue.emplace_back(next_node);
            }
        }
    }
}

template<typename T, typename Visit_f>
static void depth_first_traversal(
    adj_list_t<T> const& adj_list,
    T const& first,
    Visit_f const& visit
) {
    if constexpr(true) {
        generic_graph_traversal<graph_traversal_type_t::depth_first, T, Visit_f>(
            adj_list, first, visit
        );
    }
    else {
        using it_t = typename adj_list_t<T>::const_iterator;
        std::vector<it_t> stack{};
        stack.reserve(adj_list.size());

        {
            auto const it = adj_list.find(first);
            if(std::end(adj_list) == it) {
                // NOTE(tgm): an alternative to checking here, whether we
                //            even were able to find the starting / first
                //            element alleviates us from running the following
                //            check in the while loop, i.e.:
                //
                //              if(std::end(adj_list) == it) { continue; }
                //
                return;
            }
            stack.push_back(it);
        }

        // std::unordered_map<T const*, bool> visited{};
        std::unordered_set<T const*> visited;


        while(false == stack.empty()) {
            it_t const it = stack.back();
            stack.pop_back();



            if(std::end(visited) != visited.find(&(it->first))) {
                // fmt::print("  Skipping: {}\n", it->first);
                continue;
            }

            // visited[&(it->first)] = true;
            visited.insert(&(it->first));

            visit(it->first);


            for(auto stack_it = std::rbegin(it->second);
                std::rend(it->second) != stack_it;
                ++stack_it) {
                auto const& e = *stack_it;

                auto const sub_it = adj_list.find(e);
                if(std::end(adj_list) != sub_it) {
                    stack.push_back(sub_it);
                    // fmt::print("  pushing: {}\n", sub_it->first);
                }
            }
        }
    }
}

template<typename T, typename Visit_f>
static void breadth_first_tranversal(
    adj_list_t<T> const& adj_list,
    T const& first,
    Visit_f const& visit
) {
    if constexpr(true) {
        generic_graph_traversal<
            graph_traversal_type_t::breadth_first,
            T,
            Visit_f>(adj_list, first, visit);
    }
    else {
        using it_t = typename adj_list_t<T>::const_iterator;
        std::deque<it_t> fifo{};

        if constexpr(true) {
            // more concise implementation of the else branch
            fifo.push_back(adj_list.find(first));
            if(std::end(adj_list) == fifo.back()) {
                return;
            }
        }
        else {
            // more explicit implementation
            {
                auto const it = adj_list.find(first);
                if(std::end(adj_list) == it) {
                    return;
                }
                fifo.push_back(it);
            }
        }

        std::unordered_set<T const*> visited{};


        while(false == fifo.empty()) {
            auto const it = fifo.front();
            fifo.pop_front();

            if(std::end(visited) != visited.find(&(it->first))) {
                continue;
            }

            visited.insert(&(it->first));

            visit(it->first);

            for(auto fifo_it = std::begin(it->second);
                std::end(it->second) != fifo_it;
                ++fifo_it) {

                auto const elem_it = adj_list.find(*fifo_it);
                if(std::end(adj_list) != elem_it) {
                    fifo.push_back(elem_it);
                }
            }
        }
    }
}


template<typename T>
static bool
has_path(adj_list_t<T> const& adj_list, T const& src, T const& dst) {
    using it_t = typename adj_list_t<T>::const_iterator;

    std::vector<it_t> stack{};

    if constexpr(true) {
        // more concise implementation of the else branch
        stack.push_back(adj_list.find(src));

        if(std::end(adj_list) == stack.back() ||
           std::end(adj_list) == adj_list.find(dst)) {
            return false;
        }
    }
    else {
        // more explicit implementation
        {
            auto const it = adj_list.find(src);
            auto const end = std::end(adj_list);
            if(end == adj_list.find(dst) || end == it) {
                return false;
            }
            stack.push_back(it);
        }
    }


    std::unordered_set<T const*> visited{};


    while(false == stack.empty()) {
        auto const it = stack.back();
        stack.pop_back();

        if(std::end(visited) != visited.find(&(it->first))) {
            continue;
        }
        visited.insert(&(it->first));


        if(dst == it->first) {
            return true;
        }

        for(auto stack_it = std::rbegin(it->second);
            std::rend(it->second) != stack_it;
            ++stack_it) {

            auto elem_it = adj_list.find(*stack_it);

            if(std::end(adj_list) != elem_it) {
                stack.emplace_back(elem_it);
            }
        }
    }
    return false;
}


template<edge_connect_t edge_connect, typename T>
adj_list_t<T> edge_list_to_adj_list(edge_list_t<T> const& edge_list) {
    adj_list_t<T> result{};
    std::unordered_map<T, std::unordered_set<T>> org{};

    for(auto const& edge : edge_list) {
        org[edge.first].insert(edge.second);
        if constexpr(edge_connect_t::bidirectional == edge_connect) {
            org[edge.second].insert(edge.first);
        }
    }


    for(auto const& elem : org) {
        result[elem.first] = typename adj_list_t<T>::mapped_type(
            std::begin(elem.second), std::end(elem.second)
        );
    }


    return result;
}

template<typename T>
static void print(adj_list_t<T> const& adj_list) {
    for(auto const& elem : adj_list) {
        fmt::print("{}: {}\n", elem.first, elem.second);
    }
}






template<typename T>
std::uint32_t count_disconnected_sub_graphs(adj_list_t<T> const& adj_list) {
    std::unordered_set<T const*> nodes{};
    nodes.reserve(adj_list.size());
    for(auto const& elem : adj_list) {
        nodes.insert(&(elem.first));
    }

    auto const nodes_remover = [&](T const& elem) {
        nodes.erase(&elem);
        // fmt::print("erasing: {}\n", elem);
        return visit_result_t::do_end_normally;
    };

    std::uint32_t result = 0;
    while(false == nodes.empty()) {
        depth_first_traversal<T>(adj_list, **std::begin(nodes), nodes_remover);
        ++result;
    }

    return result;
}

template<graph_traversal_type_t graph_traversal_v, typename T>
bool are_nodes_connected(
    adj_list_t<T> const& adj_list,
    T const& src,
    T const& dst
) {
    bool result = false;


    auto are_connected = [&dst, &result](T const& current) {
        if(dst == current) {
            result = true;
            return visit_result_t::do_end_by_visit;
        }
        return visit_result_t::do_end_normally;
    };

    generic_graph_traversal<graph_traversal_v>(adj_list, src, are_connected);



    return result;
}

template<typename T>
std::int32_t shortest_path_length(
    adj_list_t<T> const& adj_list,
    T const& src,
    T const& dst
) {
    using it_t = typename adj_list_t<T>::const_iterator;

    auto const end_al = std::end(adj_list);

    auto const it_dst = adj_list.find(dst);


    std::deque<std::pair<it_t, std::int32_t>> fifo{};
    fifo.push_back(std::make_pair(adj_list.find(src), 0));




    if(end_al == fifo.back().first || end_al == it_dst) {
        return -1;
    }


    // result.push_back(&*fifo.back());

    std::unordered_set<T const*> visited{};

    while(false == fifo.empty()) {
        auto const [it, result] = fifo.front();
        fifo.pop_front();

        if(false == visited.insert(&(it->first)).second) {
            continue;
        }

        // fmt::print(
        //     "{}visiting: [{}]\n",
        //     fmt::join(
        //         std::vector<std::string>(
        //             static_cast<std::uint32_t>(result), " "
        //         ),
        //         ""
        //     ),
        //     it->first
        // );

        if(it_dst == it) {
            return result;
        }

        for(auto const& neigh : it->second) {
            auto const it_neigh = adj_list.find(neigh);
            if(end_al == it_neigh) {
                continue;
            }
            fifo.push_back(std::make_pair(it_neigh, 1 + result));
        }
    }






    return -1;
}



static_assert(std::is_same_v<char, std::unordered_map<char, int>::key_type>);


} /* namespace hof */

#endif /* HOF_GRAPH_GRAPH_HH_ */
