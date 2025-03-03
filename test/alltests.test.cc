/**
 * @file
 * Copyright (C) 2017 Tomasz G. Markiewicz (software dot tgm at gmail dot com)
 *
 * Created on Mar 9, 2017
 *
 */





#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif /* __clang__ */


#include "gtest-wrapper.hh"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class TemplateTest : public testing::Test {
public:
    virtual void SetUp() override { }
    virtual void TearDown() override { }
};

TEST_F(TemplateTest, fixture_self_test) { }
TEST_F(TemplateTest, DISABLED_test) { }


#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */
