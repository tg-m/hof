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


#include <concepts>
#include <memory>

#include "gtest-wrapper.hh"

#include "visitable.hh"


template<typename T, hof::Visitable<T> Visit_f>
hof::visit_result_t consume(T const& data, Visit_f const& visit) {
    return visit(data);
}

class visitable_Test : public testing::Test {
public:
    virtual void SetUp() override {
    }
    virtual void TearDown() override {
    }
};

TEST_F(visitable_Test, fixture_self_test) { }
TEST_F(visitable_Test, DISABLED_test) { }



TEST_F(visitable_Test, basic_concept_test) {
    auto const l = [](int x) {
        return 0 == x % 2 ? hof::visit_result_t::do_end_by_visit : hof::visit_result_t::do_end_normally;
    };

    ASSERT_EQ(hof::visit_result_t::do_end_by_visit, consume(0, l));
    ASSERT_EQ(hof::visit_result_t::do_end_by_visit, consume(2, l));
    ASSERT_EQ(hof::visit_result_t::do_end_by_visit, consume(4, l));

    ASSERT_EQ(hof::visit_result_t::do_end_normally, consume(1, l));
    ASSERT_EQ(hof::visit_result_t::do_end_normally, consume(3, l));
    ASSERT_EQ(hof::visit_result_t::do_end_normally, consume(5, l));
    ASSERT_EQ(hof::visit_result_t::do_end_normally, consume(7, l));
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */
