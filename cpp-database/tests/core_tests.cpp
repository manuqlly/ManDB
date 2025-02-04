#include <gtest/gtest.h>
#include "core/database.h"
#include "core/table.h"
#include "core/query.h"

class DatabaseTest : public ::testing::Test {
protected:
    Database db;

    void SetUp() override {
        db.connect("test.db");
    }

    void TearDown() override {
        db.disconnect();
    }
};

TEST_F(DatabaseTest, ConnectDisconnect) {
    EXPECT_TRUE(db.isConnected());
}

TEST_F(DatabaseTest, ExecuteQuery) {
    EXPECT_NO_THROW(db.executeQuery("CREATE TABLE test (id INTEGER PRIMARY KEY, name TEXT)"));
}

class TableTest : public ::testing::Test {
protected:
    Table table;

    void SetUp() override {
        table.create("test");
    }
};

TEST_F(TableTest, InsertAndSelect) {
    table.insert(1, "Alice");
    EXPECT_EQ(table.select(1), "Alice");
}

class QueryTest : public ::testing::Test {
protected:
    Query query;

    void SetUp() override {
        // Setup code if needed
    }
};

TEST_F(QueryTest, ParseValidQuery) {
    EXPECT_NO_THROW(query.parse("SELECT * FROM test"));
}