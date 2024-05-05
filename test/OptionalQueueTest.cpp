#include <gtest/gtest.h>

#include <optional_queue/OptionalQueue.hpp>

struct TestOptionalQueue : public OptionalQueue<int> {
    using OptionalQueue::_elem;
    using OptionalQueue::_queue;
};

TEST(OptionalQueueTest, ConstructionTest) {
    TestOptionalQueue queue;
    ASSERT_FALSE(queue._elem);
    ASSERT_TRUE(queue._queue.empty());
    ASSERT_EQ(queue.size(), 0ul);
}

TEST(OptionalQueueTest, CancelEnqueueTest) {
    TestOptionalQueue queue;
    int elem = 1;

    {
        auto handle = queue.push(elem);
        handle.cancelEnqueue();
        ASSERT_EQ(&elem, queue._elem);
        ASSERT_TRUE(queue._queue.empty());
        ASSERT_EQ(elem, queue.top());
        ASSERT_EQ(queue.size(), 1ul);
    }

    ASSERT_FALSE(queue._elem);
    ASSERT_TRUE(queue._queue.empty());
    ASSERT_EQ(queue.size(), 0ul);
}

TEST(OptionalQueueTest, EnqueueTest) {
    TestOptionalQueue queue;
    int elem = 1;

    {
        auto handle = queue.push(elem);
        ASSERT_EQ(&elem, queue._elem);
        ASSERT_TRUE(queue._queue.empty());
    }

    ASSERT_FALSE(queue._elem);
    ASSERT_FALSE(queue._queue.empty());
    ASSERT_EQ(elem, queue.top());
}

TEST(OptionalQueueTest, PopTest) {
    TestOptionalQueue queue;
    int elem1 = 1;
    int elem2 = 2;

    { auto handle1 = queue.push(elem1); }

    auto handle2 = queue.push(elem2);
    ASSERT_EQ(queue.size(), 2ul);
    ASSERT_FALSE(queue.empty());

    ASSERT_EQ(&elem2, queue._elem);
    ASSERT_EQ(queue._queue.size(), 1ul);
    ASSERT_EQ(elem1, queue.top());

    queue.pop();
    ASSERT_FALSE(queue.empty());
    ASSERT_TRUE(queue._queue.empty());
    ASSERT_EQ(elem2, queue.top());
    ASSERT_EQ(queue.size(), 1ul);

    queue.pop();
    ASSERT_FALSE(queue._elem);
    ASSERT_TRUE(queue._queue.empty());
    ASSERT_EQ(queue.size(), 0ul);
}