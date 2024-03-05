/**
 * @file
 * Copyright (C) 2024-present Tomasz G. Markiewicz (software.tgm@gmail.com)
 *
 * Created on Mar 4, 2024
 *
 */

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif /* __clang__ */

#include <cstdint>


#include <memory>

#include <fmt/core.h>

#include "gtest-wrapper.hh"

#include "linked_list.hh"

// #include "common/debug.hh"

class linked_list_Test : public testing::Test {
public:
    virtual void SetUp() override {
    }
    virtual void TearDown() override {
    }
};

TEST_F(linked_list_Test, fixture_self_test) {
}
TEST_F(linked_list_Test, DISABLED_test) {
}

TEST_F(linked_list_Test, 2nd_dtor) {
    {
        std::make_shared<hof::linked_list<int>>();
    }
    {
        hof::linked_list<int> const* ptr = new hof::linked_list<int>();
        delete ptr;
    }
}


TEST_F(linked_list_Test, basic_traversal___) {
    using elem_t = char;
    hof::linked_list<elem_t>::node a{'a', nullptr};
    hof::linked_list<elem_t>::node b{'b', nullptr};
    hof::linked_list<elem_t>::node c{'c', nullptr};

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
    container_t(T const& a_data) : data(a_data) {}
    container_t(T&& a_data) : data(std::move(a_data)) {}
    ~container_t() {
        fmt::print(" > container_t::~container_t().data = [{}]\n", data);
    }

    container_t(container_t const& other) : data(other.data) { }
    container_t& operator=(container_t const& other) {
        if(&other != this) {
            data = other.data;
        }
        return *this;
    }
    container_t(container_t&& other) : data(other.data) { other.data = T(); }
    container_t& operator=(container_t&& other) {
        data = other.data;
        other.data = T();

        return *this;
    }


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
        hof::linked_list<elem_t> ll{std::move(elem_t{'a'})};
        ll.append('b');
        ll.append(std::move(elem_t('c')));
        {
            auto const d = elem_t{'d'};
            ll.append(d);
        }
        hof::linked_list<elem_t>::append(ll, 'e', 'f');
        {
            auto const g = elem_t{'g'};
            auto const h = elem_t{'h'};
            ll.append(g, h);
        }
        {
            auto i = elem_t{'i'};
            auto j = elem_t{'j'};
            ll.append(i, std::move(j), 'k', elem_t{'l'});
        }

        ll.traverse(print);
    }

}

#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */
