#pragma once

#include <gtest/gtest.h>


template <template <typename> typename C, typename T>
class AdapterTest : public testing::Test {
protected:

    template <typename... Args>
    void pushValues(const T& value, const Args&... args) {
        data_.push(value);
        if constexpr(sizeof...(args)) {
            pushValues(args...);
        }
    }


    void pushValueAndCheckTop(const T& value, const T& expect) {
        data_.push(value);
        ASSERT_EQ(data_.top(), expect);
    }

    void pushValueAndCheckTop(const T& value) {
        pushValueAndCheckTop(value, value);
    }


    void pushValueAndCheckBack(const T&& value) {
        data_.push(value);
        ASSERT_EQ(data_.back(), value);
    }

    void popAndCheckValue(const T& expect) {
        ASSERT_EQ(data_.pop(), expect);
    }


private:
    C<T> data_;
};
