#include <gtest/gtest.h>
#include "sql_parser.h"

class SQLParserTests : public ::testing::Test {
protected:
    SQLParser parser;

    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

TEST_F(SQLParserTests, TestSelectStatement) {
    std::string sql = "SELECT * FROM users;";
    auto result = parser.parse(sql);
    ASSERT_TRUE(result.success);
    ASSERT_EQ(result.command, "SELECT");
}

TEST_F(SQLParserTests, TestInsertStatement) {
    std::string sql = "INSERT INTO users (name, age) VALUES ('Alice', 30);";
    auto result = parser.parse(sql);
    ASSERT_TRUE(result.success);
    ASSERT_EQ(result.command, "INSERT");
}

TEST_F(SQLParserTests, TestInvalidStatement) {
    std::string sql = "INVALID SQL STATEMENT";
    auto result = parser.parse(sql);
    ASSERT_FALSE(result.success);
}