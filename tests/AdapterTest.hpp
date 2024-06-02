#pragma once

#include <gtest/gtest.h>


template <template <typename> typename C, typename T>
class AdapterTests : public testing::Test {
protected:

	template <typename... Args>
	void pushValues(const T& value, const Args&... args) {
		m_data.push(value);
		if constexpr(sizeof...(args)) {
			pushValues(args...);
		}
	}


	void pushValueAndCheckTop(const T& value, const T& expect) {
		m_data.push(value);
		ASSERT_EQ(m_data.top(), expect);
	}

	void pushValueAndCheckTop(const T& value) {
		pushValueAndCheckTop(value, value);
	}


	void pushValueAndCheckBack(const T&& value) {
		m_data.push(value);
		ASSERT_EQ(m_data.back(), value);
	}
	
	void popAndCheckValue(const T& expect) {
		ASSERT_EQ(m_data.pop(), expect);
	}


private:
	C<T> m_data;
};
