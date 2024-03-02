/**
 * @file
 * Copyright (C) 2019-present Tomasz G. Markiewicz (software.tgm@gmail.com)
 *
 * Created on Feb 11, 2020
 *
 */





#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif /* __clang__ */


#include "gtest-wrapper.hh"


#include "lambda_wrapper.hh"


class lambda_wrapper_test : public testing::Test {
public:
    virtual void SetUp() override {}
    virtual void TearDown() override {}
};

TEST_F(lambda_wrapper_test, fixture_self_test) {}
TEST_F(lambda_wrapper_test, DISABLED_test) {}

TEST_F(lambda_wrapper_test, create_lambda_and_call_it_with_wrapper) {
    auto const expected = [] { return "wowaoef"; };
    hof::lambda_wrapper<std::decay_t<decltype(expected)>> actual(expected);

    ASSERT_EQ(expected(), actual());
}


TEST_F(lambda_wrapper_test, create_lambda_with_param_and_call_it_with_wrapper) {
    auto const expected = [](int i) { return 2 * i; };
    hof::lambda_wrapper<std::decay_t<decltype(expected)>> actual(expected);

    ASSERT_EQ(expected(3), actual(3));
}


#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */
