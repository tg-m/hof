/**
 * @file
 * Copyright (C) 2024-present Tomasz G. Markiewicz (software dot tgm at gmail dot com)
 *
 * Created on Mar 4, 2024
 *
 */

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wreserved-identifier"
#endif /* __clang__ */

#include <cstdint>


#include <memory>
// #include <numeric>
#include <ostream>     // std::ostream
#include <type_traits> // std::is_nothrow_move_constructible_v
#include <utility>     // std::move
#include <vector>


#include <fmt/core.h>

#include "gtest-wrapper.hh"

#include "linked_list.hh"

#include "concepts/visitable/visitable.hh"

// #include "common/debug.hh"

class linked_list_Test : public testing::Test {
public:
    virtual void SetUp() override { }
    virtual void TearDown() override { }
};

TEST_F(linked_list_Test, fixture_self_test) { }
TEST_F(linked_list_Test, DISABLED_test) { }

TEST_F(linked_list_Test, 2nd_dtor) {
    { std::make_shared<hof::linked_list<int>>(); }
    {
        hof::linked_list<int> const* ptr = new hof::linked_list<int>();
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        delete ptr;
    }
}


TEST_F(linked_list_Test, basic_traversal___) {
    using elem_t = char;
    // NOLINTBEGIN(modernize-use-designated-initializers)
    hof::linked_list<elem_t>::node a{'a', nullptr};
    hof::linked_list<elem_t>::node b{'b', nullptr};
    hof::linked_list<elem_t>::node c{'c', nullptr};
    // NOLINTEND(modernize-use-designated-initializers)

    a.next = &b;
    b.next = &c;

    auto const print = [](elem_t const elem) {
        fmt::print("elem: {}\n", elem);
        if('z' == elem) {
            return hof::visit_result_t::do_end_by_visit;
        }
        return hof::visit_result_t::do_end_normally;
    };

    hof::linked_list<elem_t>::traverse(a, print);
}

namespace {

template<typename T>
struct container_t {
private:
    static constexpr bool do_log() { return true; }
    static constexpr bool do_log_extra() { return false; }

public:
    explicit container_t() noexcept(noexcept(T()))
    : data() { }
    container_t(T const& a_data) noexcept(noexcept(T()))
    : data(a_data) {
        if constexpr(do_log() && do_log_extra()) {
            fmt::print(
                " > container_t::container_t(T const&).data = [{}]\n", data
            );
        }
    }
    explicit container_t(T&& a_data
    ) noexcept(std::is_nothrow_move_constructible_v<T>)
    : data(std::move(a_data)) {
        if constexpr(do_log() && do_log_extra()) {
            fmt::print(" > container_t::container_t(T&&).data = [{}]\n", data);
        }
    }
    ~container_t() {
        if constexpr(do_log()) {
            fmt::print(" > container_t::~container_t().data = [{}]\n", data);
        }
    }

    container_t(container_t const& other) noexcept(noexcept(T(T())))
    : data(other.data) {
        if constexpr(do_log() && do_log_extra()) {
            fmt::print(
                " > container_t::container_t(container_t const&).data <- data "
                "= [{}] <- [{}]\n",
                T(),
                other.data
            );
        }
    }
    container_t& operator=(container_t const& other
    ) noexcept(std::is_nothrow_copy_constructible_v<T>) {
        if(&other != this) {
            if constexpr(do_log() && do_log_extra()) {
                fmt::print(
                    " > container_t::operator=(container_t const&).data <- "
                    "data = [{}] <- [{}]\n",
                    data,
                    other.data
                );
            }
            data = other.data;
        }
        return *this;
    }
    container_t(container_t&& other) noexcept(noexcept(T(T())))
    : data(std::move(other.data)) {
        if constexpr(do_log() && do_log_extra()) {
            fmt::print(
                " > container_t::container_t(container_t&&).data <- data = "
                "[{}] <- [{}]\n",
                T(),
                other.data
            );
        }
        other.data = T();
    }
    container_t& operator=(container_t&& other
    ) noexcept(std::is_nothrow_move_constructible_v<T>) {
        if constexpr(do_log() && do_log_extra()) {
            fmt::print(
                " > container_t::operator=(container_t&&).data <- data = [{}] "
                "<- [{}]\n",
                data,
                other.data
            );
        }
        data = other.data;
        other.data = T();

        return *this;
    }

    friend bool operator==(container_t const& l, container_t const& r) {
        return l.data == r.data;
    }
    friend bool operator!=(container_t const& l, container_t const& r) {
        return !(l == r);
    }

    friend std::ostream& operator<<(std::ostream& os, container_t const& c) {
        os << c.data;
        return os;
    }


    // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
    T data;
};
} /* namespace */
TEST_F(linked_list_Test, create_and_add_elements) {

    using elem_t = container_t<char>;

    auto const print = [](elem_t const& elem) {
        fmt::print("elem: elem.data: {}\n", elem.data);
        if('z' == elem.data) {
            return hof::visit_result_t::do_end_by_visit;
        }
        return hof::visit_result_t::do_end_normally;
    };

    {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpessimizing-move"
#endif /* __clang__ */
        //
        // We want to use here sub-optimal (possimising) implementation,
        // due to the code coverage!
        //
        hof::linked_list<elem_t> ll{std::move(elem_t{'a'})};
#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */

        ll.append('b');
        ll.append(elem_t('c'));
        {
            auto const d = elem_t{'d'};
            ll.append(d);
            ASSERT_EQ('d', d.data);
        }
        hof::linked_list<elem_t>::append(ll, 'e', 'f');
        {
            auto const g = elem_t{'g'};
            auto const h = elem_t{'h'};
            ll.append(g, h);
            ASSERT_EQ('g', g.data);
            ASSERT_EQ('h', h.data);
        }
        {
            auto i = elem_t{'i'};
            auto j = elem_t{'j'};
            ll.append(i, std::move(j), 'k', elem_t{'l'});
            ASSERT_EQ('i', i.data);
            // NOLINTBEGIN(bugprone-use-after-move)
            // NOLINTBEGIN(hicpp-invalid-access-moved)
            ASSERT_EQ('\0', j.data); // We std::move-d j!
            // NOLINTEND(hicpp-invalid-access-moved)
            // NOLINTEND(bugprone-use-after-move)
        }

        ll.traverse(print);
    }
}

TEST_F(linked_list_Test, to_container___) {
    using elem_t = container_t<std::int32_t>;


    // std::vector<elem_t> const expected{1, 2, 3, 4, 5, 6, 7, 13};
    // // std::vector<elem_t> const expected = []{
    // //     std::vector<elem_t> result(7, elem_t());
    // //     std::iota(std::begin(result), std::end(result), 1);
    // //     return result;
    // // }();

    std::vector<elem_t> const expected = [] {
        std::vector<elem_t> result{};
        result.reserve(64);
        for(std::int32_t i = 1; 8 > i; ++i) {
            result.emplace_back(i);
            // result.push_back(i);
        }

        return result;
    }();


    hof::linked_list<elem_t> llist{};
    for(auto const& e : expected) {
        llist.append(e);
    }

    llist.print();

    auto const actual = llist.to_container<std::vector<elem_t>>();

    ASSERT_EQ(expected, actual);
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */
