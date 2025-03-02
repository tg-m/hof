/**
 * @file
 * Copyright (C) 2017 Tomasz G. Markiewicz (software.tgm@gmail.com)
 *
 * Created on Jul 29, 2017
 *
 */




#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif /* __clang__ */


#include <exception>
// #include <iostream>
#include <string>



#include "gtest-wrapper.hh"

class CppTest : public testing::Test {
public:
    virtual void SetUp() override { }
    virtual void TearDown() override { }
};

TEST_F(CppTest, fixture_self_test) { }
TEST_F(CppTest, DISABLED_test) { }


TEST_F(CppTest, std_string_with_null_pointer) {
    char const* ptr = nullptr;

    // We especially want to catch this exception.
    //
    // NOLINTBEGIN(clang-analyzer-cplusplus.StringChecker)
    ASSERT_THROW(std::string{ptr}, std::exception);
    // NOLINTEND(clang-analyzer-cplusplus.StringChecker)
}


#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */
