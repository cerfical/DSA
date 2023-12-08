#include <gtest/gtest.h>
#include <DSA/List.hpp>

namespace dsa {
	template <typename T>
	void PrintTo(const List<T>& list, std::ostream* out) {
		// for consistency, use GTest's own printer to print out the list
		*out << testing::PrintToString(
			std::vector<T>(list.cbegin(), list.cend())
		);
	}
}



class DtorCallTracer {
public:
	explicit DtorCallTracer(int* dtorCalls = {}) noexcept
		: m_dtorCalls(dtorCalls)
	{ }

	~DtorCallTracer() {
		if(m_dtorCalls) {
			(*m_dtorCalls)++;
		}
	}


	DtorCallTracer(DtorCallTracer&& other) noexcept {
		m_dtorCalls = std::exchange(other.m_dtorCalls, {});
	}
	
	DtorCallTracer& operator=(DtorCallTracer&& other) noexcept {
		m_dtorCalls = std::exchange(other.m_dtorCalls, {});
		return *this;
	}


	DtorCallTracer(const DtorCallTracer&) = delete;
	DtorCallTracer& operator=(const DtorCallTracer&) = delete;


private:
	int* m_dtorCalls;
};



class ListTests : public testing::Test {
protected:
	dsa::List<int> list = { 1, 2, 3 };
	const dsa::List<int> emptyList;
};



TEST_F(ListTests, clearMakesListEmpty) {
	list.clear();
	ASSERT_TRUE(list.isEmpty());
}

TEST_F(ListTests, clearDestroysAllElements) {
	dsa::List<DtorCallTracer> tracers;
	int dtorCalls = 0;

	tracers.pushBack(DtorCallTracer(&dtorCalls));
	tracers.pushBack(DtorCallTracer(&dtorCalls));
	tracers.pushBack(DtorCallTracer(&dtorCalls));
	tracers.clear();

	ASSERT_EQ(dtorCalls, 3);
}



TEST_F(ListTests, pushBackIncreasesListSize) {
	list.pushBack(0);
	ASSERT_EQ(list.size(), 4);
}

TEST_F(ListTests, pushBackInsertsElementAtListBack) {
	list.pushBack(12);
	ASSERT_EQ(list.back(), 12);
}



TEST_F(ListTests, popBackDecreasesListSize) {
	list.popBack();
	ASSERT_EQ(list.size(), 2);
}

TEST_F(ListTests, popBackReturnsElementAtListBack) {
	ASSERT_EQ(list.popBack(), 3);
}



TEST_F(ListTests, pushFrontIncreasesListSize) {
	list.pushFront(0);
	ASSERT_EQ(list.size(), 4);
}

TEST_F(ListTests, pushFrontInsertsElementAtListFront) {
	list.pushFront(12);
	ASSERT_EQ(list.front(), 12);
}



TEST_F(ListTests, popFrontDecreasesListSize) {
	list.popFront();
	ASSERT_EQ(list.size(), 2);
}

TEST_F(ListTests, popFrontReturnsElementAtListFront) {
	ASSERT_EQ(list.popFront(), 1);
}



TEST_F(ListTests, equivalentIteratorsAreEqual) {
	ASSERT_EQ(emptyList.begin(), emptyList.end());

	ASSERT_EQ(++list.begin(), ++list.begin());
	ASSERT_EQ(--list.end(), --list.end());
	ASSERT_EQ(list.begin(), list.cbegin());
	ASSERT_EQ(list.end(), list.cend());
}

TEST_F(ListTests, notEquivalentIteratorsAreNotEqual) {
	ASSERT_NE(list.begin(), emptyList.begin());
	ASSERT_NE(list.end(), emptyList.end());
	
	ASSERT_NE(list.begin(), list.end());
	ASSERT_NE(++list.begin(), list.begin());
	ASSERT_NE(--list.end(), list.end());
}

TEST_F(ListTests, iteratorCopiesAreEqual) {
	const auto it1 = list.begin();
	const auto it2 = it1;
	
	auto it3 = list.end();
	it3 = it1;

	ASSERT_EQ(it1, it2);
	ASSERT_EQ(it1, it3);
}



TEST_F(ListTests, iteratorIncrementMovesToNextElement) {
	auto it = list.begin();
	
	++it;
	ASSERT_EQ(*it, 2);
	
	it++;
	ASSERT_EQ(*it, 3);
}

TEST_F(ListTests, iteratorDecrementMovesToPreviousElement) {
	auto it = list.end();

	--it;
	ASSERT_EQ(*it, 3);

	it--;
	ASSERT_EQ(*it, 2);
}

TEST_F(ListTests, iteratorPostIncrementDecrementReturnsCurrentElement) {
	auto it = list.begin();
	
	ASSERT_EQ(*(it++), 1);
	ASSERT_EQ(*(it--), 2);
}



TEST_F(ListTests, moveLeavesListEmpty) {
	auto tmp = std::move(list);
	ASSERT_TRUE(list.isEmpty() && !tmp.isEmpty());

	list = std::move(tmp);
	ASSERT_TRUE(tmp.isEmpty() && !list.isEmpty());
}

TEST_F(ListTests, equivalentListsAreEqual) {
	const dsa::List<int> l1 = { 1, 2, 3 };
	
	ASSERT_EQ(list, list);
	ASSERT_EQ(list, l1);
}

TEST_F(ListTests, notEquivalentListsAreNotEqual) {
	const dsa::List<int> l1 = { 1, 4, 3 };
	const dsa::List<int> l2 = { 2, 2, 3 };
	const dsa::List<int> l3 = { 1, 2, 4 };
	const dsa::List<int> l4 = { 1, 2, 3, 4 };
	const dsa::List<int> l5 = { 1, 2 };

	ASSERT_NE(list, emptyList);
	ASSERT_NE(list, l1);
	ASSERT_NE(list, l2);
	ASSERT_NE(list, l3);
	ASSERT_NE(list, l4);
	ASSERT_NE(list, l5);
}

TEST_F(ListTests, listCopiesAreEqual) {
	auto copy1 = list;
	ASSERT_EQ(copy1, list);

	copy1 = emptyList;
	ASSERT_EQ(copy1, emptyList);

	auto copy2 = emptyList;
	ASSERT_EQ(copy2, emptyList);

	copy2 = list;
	ASSERT_EQ(copy2, list);
}
