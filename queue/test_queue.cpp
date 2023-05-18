#include <gtest/gtest.h>
#include <iostream>
#include "queue.h"

// Fixture class
class QueueTest : public ::testing::Test {
   protected:
    QueueTest() {}
    ~QueueTest() override {}

    void SetUp() override {}

    void TearDown() override {}

    Queue<int> q0_;
};

// All test are with int object

// Test 1: enqueue is working
TEST_F(QueueTest, EnqueueWorking) {
    int val = 5;

    // enqueue with l value
    q0_.enqueue(val);
    ASSERT_EQ(q0_.size(), 1);
    EXPECT_EQ(q0_.getFront(), val);
    EXPECT_EQ(q0_.getBack(), val);

    // enqueue with r value
    q0_.enqueue(33);
    ASSERT_EQ(q0_.size(), 2);
    EXPECT_EQ(q0_.getFront(), val);
    EXPECT_EQ(q0_.getBack(), 33);
}

// Test 2: dequeue is working
TEST_F(QueueTest, DequeueWorking) {
    int queueLen = 10;
    for (int i = 0; i < queueLen; ++i) q0_.enqueue(23 + i);

    // dequeueing non-empy queue
    for (int i = 0; i < queueLen; ++i) {
        EXPECT_EQ(q0_.dequeue(), 23 + i);
        EXPECT_EQ(q0_.size(), queueLen - i - 1);
    }

    // dequeueing empty queue
    EXPECT_ANY_THROW(q0_.dequeue());
}

// Test 3: resize is working
TEST_F(QueueTest, ResizeWhenEnqueueWorking) {
    int queueLen = 24;
    for (int i = 0; i < queueLen; ++i) q0_.enqueue(23 + i);
    ASSERT_EQ(q0_.size(), queueLen);

    // dequeue to check
    for (int i = 0; i < queueLen; ++i) {
        EXPECT_EQ(q0_.dequeue(), 23 + i);
        EXPECT_EQ(q0_.size(), queueLen - i - 1);
    }
    //q0_.print_queue_pretty();
}

// Test 4: wrap around is working
TEST_F(QueueTest, WrapArounWorking) {
    int queueLen = 24;
    int dequeueLen = 17;
    for (int i = 0; i < queueLen; ++i) q0_.enqueue(23 + i);
    for (int i = 0; i < dequeueLen; ++i) q0_.dequeue();
    for (int i = 0; i < queueLen; ++i) q0_.enqueue(23+i);
    q0_.print_queue_pretty();

    // dequeue to check
    for (int i = dequeueLen; i < queueLen; ++i) {
        EXPECT_EQ(q0_.dequeue(), 23 + i);
    }
    for (int i = 0; i < queueLen; ++i) {
        EXPECT_EQ(q0_.dequeue(), 23 + i);
    }
}

// Test 5: copy constructor is working
TEST_F(QueueTest, CopyConstructorWorking) {
    // reference queue q0_
    for (int i = 0; i < 10; ++i) q0_.enqueue(i);
    for (int i = 0; i < 5; ++i) q0_.dequeue();
    for (int i = 0; i < 8; ++i) {
        q0_.enqueue(i+10);
    }
    //q0_.print_queue_pretty();

    // copy construct
    Queue<int> qCpConstruct{q0_};
    ASSERT_TRUE(q0_ == qCpConstruct);

    q0_.enqueue(99);
    ASSERT_FALSE(q0_ == qCpConstruct);

}

// Test 6: move constructor is working
TEST_F(QueueTest, MoveConstructorWorking) {
    // reference queue q0_
    for (int i = 0; i < 10; ++i) q0_.enqueue(i);
    for (int i = 0; i < 5; ++i) q0_.dequeue();
    for (int i = 0; i < 8; ++i) {
        q0_.enqueue(i+10);
    }

    // copy for future checking
    Queue<int> q0_copy{q0_};

    Queue<int> qMvConstruct{std::move(q0_)};
    //qMvConstruct.print_queue_pretty();
    //q0_.print_queue_pretty();
    
    ASSERT_TRUE(q0_copy == qMvConstruct);
    ASSERT_TRUE(q0_.isEmpty());
}

// Test 7: copy assignment is working
TEST_F(QueueTest, CopyAsnWorking) {
    // reference queue q0_
    for (int i = 0; i < 10; ++i) q0_.enqueue(i);
    for (int i = 0; i < 5; ++i) q0_.dequeue();
    for (int i = 0; i < 8; ++i) {
        q0_.enqueue(i+10);
    }
    Queue<int> qCpAsn;
    qCpAsn = q0_;

    ASSERT_TRUE(q0_ == qCpAsn);
    qCpAsn.enqueue(-200);
    ASSERT_FALSE(q0_ == qCpAsn);
}

// Test 8: move assignment is working
TEST_F(QueueTest, MoveAsnWorking) {
    // reference queue q0_
    for (int i = 0; i < 10; ++i) q0_.enqueue(i);
    for (int i = 0; i < 5; ++i) q0_.dequeue();
    for (int i = 0; i < 8; ++i) {
        q0_.enqueue(i+10);
    }
    Queue<int> q0_copy{q0_};

    // reference queue q1_
    Queue<int> q1_;
    for (int i = 0; i < 10; ++i) q1_.enqueue(i);
    for (int i = 0; i < 5; ++i) q1_.dequeue();

    Queue<int> qMvAsn{q1_};
    qMvAsn = std::move(q0_);

    ASSERT_TRUE(qMvAsn == q0_copy);
    ASSERT_TRUE(q0_ == q1_);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}