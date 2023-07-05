#include <gtest/gtest.h>
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

TEST(weak_ptrTest, FunctionUseCountEqualsNullptr) {
    my::weak_ptr<int> weak_ptr;
    auto value = weak_ptr.use_count();
    auto expected = 0;

    EXPECT_EQ(expected, value);
}

TEST(weak_ptrTest, ConstructorWeakPtrEqualsSharedPtr) {
    my::shared_ptr<int> shared_ptr(new int{10});
    my::weak_ptr<int> weak_ptr(shared_ptr);
    auto value = weak_ptr.use_count();
    auto expected = 1;

    EXPECT_EQ(expected, value);
}

TEST(weak_ptrTest, CopyConstructorWeakPtrEqualsWeakNotNullPtr) {
    my::shared_ptr<int> shared_ptr(new int{10});
    my::weak_ptr<int> weak_ptr1(shared_ptr);
    my::weak_ptr<int> weak_ptr2(weak_ptr1);
    auto value = weak_ptr2.expired();
    auto expected = true;

    EXPECT_EQ(expected, value);
}

TEST(weak_ptrTest, CopyConstructorWeakPtrEqualsWeakNullPtr) {
    my::shared_ptr<int> shared_ptr;
    my::weak_ptr<int> weak_ptr1(shared_ptr);
    my::weak_ptr<int> weak_ptr2(weak_ptr1);
    auto value = weak_ptr2.expired();
    auto expected = false;

    EXPECT_EQ(expected, value);
}

TEST(weak_ptrTest, CopyAssignmentCounterEqualsTwoTest) {
    my::shared_ptr<int> shared_ptr1(new int{20});
    my::shared_ptr<int> shared_ptr2(new int{20});
    my::weak_ptr<int> weak_ptr1(shared_ptr1);
    my::weak_ptr<int> weak_ptr2(shared_ptr2);
    weak_ptr1 = weak_ptr2;
    auto ptrCounter = weak_ptr1.use_count();
    auto expected = 1;

    EXPECT_EQ(expected, ptrCounter);
}

TEST(weak_ptrTest, CopyAssignmentCounterEqualsTwoNullptr) {
    my::shared_ptr<int> shared_ptr1;
    my::shared_ptr<int> shared_ptr2;
    my::weak_ptr<int> weak_ptr1(shared_ptr1);
    my::weak_ptr<int> weak_ptr2(shared_ptr2);
    weak_ptr1 = weak_ptr2;
    auto ptrCounter = weak_ptr1.use_count();
    auto expected = 0;

    EXPECT_EQ(expected, ptrCounter);
}