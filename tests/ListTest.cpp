#include <dsa/List.hpp>
#include <gtest/gtest.h>

#include <ostream>
#include <utility>
#include <vector>


namespace dsa {
    template <typename T>
    void PrintTo(const List<T>& list, std::ostream* out) {
        // for consistency, use GTest's own printer to print out the list
        *out << testing::PrintToString(std::vector<T>(list.cbegin(), list.cend()));
    }
}

using namespace dsa;


class DtorCallTracer {
public:

    DtorCallTracer(const DtorCallTracer&) = delete;
    DtorCallTracer& operator=(const DtorCallTracer&) = delete;


    DtorCallTracer(DtorCallTracer&& other) noexcept {
        dtorCalls_ = std::exchange(other.dtorCalls_, {});
    }

    DtorCallTracer& operator=(DtorCallTracer&& other) noexcept {
        dtorCalls_ = std::exchange(other.dtorCalls_, {});
        return *this;
    }


    explicit DtorCallTracer(int* dtorCalls = {}) noexcept
        : dtorCalls_(dtorCalls) {}

    ~DtorCallTracer() {
        if(dtorCalls_) {
            (*dtorCalls_)++;
        }
    }


private:
    int* dtorCalls_ = {};
};


class ListTest : public testing::Test {
protected:
    List<int> list = { 1, 2, 3 };
    const List<int> emptyList;
};


TEST_F(ListTest, clearMakesListEmpty) {
    list.clear();
    ASSERT_TRUE(list.isEmpty());
}


TEST_F(ListTest, clearDestroysAllListElements) {
    List<DtorCallTracer> tracers;
    int dtorCalls = 0;

    tracers.pushBack(DtorCallTracer(&dtorCalls));
    tracers.pushBack(DtorCallTracer(&dtorCalls));
    tracers.pushBack(DtorCallTracer(&dtorCalls));
    tracers.clear();

    ASSERT_EQ(dtorCalls, 3);
}


TEST_F(ListTest, pushBackIncreasesListSize) {
    list.pushBack(0);
    ASSERT_EQ(list.size(), 4);
}


TEST_F(ListTest, pushBackPutsElementInListBack) {
    list.pushBack(12);
    ASSERT_EQ(list.back(), 12);
}


TEST_F(ListTest, popBackDecreasesListSize) {
    list.popBack();
    ASSERT_EQ(list.size(), 2);
}


TEST_F(ListTest, popBackReturnsElementInListBack) {
    ASSERT_EQ(list.popBack(), 3);
}


TEST_F(ListTest, pushFrontIncreasesListSize) {
    list.pushFront(0);
    ASSERT_EQ(list.size(), 4);
}


TEST_F(ListTest, pushFrontPutsElementInListFront) {
    list.pushFront(12);
    ASSERT_EQ(list.front(), 12);
}


TEST_F(ListTest, popFrontDecreasesListSize) {
    list.popFront();
    ASSERT_EQ(list.size(), 2);
}


TEST_F(ListTest, popFrontReturnsElementInListFront) {
    ASSERT_EQ(list.popFront(), 1);
}


TEST_F(ListTest, equivalentIteratorsAreEqual) {
    ASSERT_EQ(emptyList.begin(), emptyList.end());

    ASSERT_EQ(++list.begin(), ++list.begin());
    ASSERT_EQ(--list.end(), --list.end());
    ASSERT_EQ(list.begin(), list.cbegin());
    ASSERT_EQ(list.end(), list.cend());
}


TEST_F(ListTest, notEquivalentIteratorsAreNotEqual) {
    ASSERT_NE(list.begin(), emptyList.begin());
    ASSERT_NE(list.end(), emptyList.end());

    ASSERT_NE(list.begin(), list.end());
    ASSERT_NE(++list.begin(), list.begin());
    ASSERT_NE(--list.end(), list.end());
}


TEST_F(ListTest, iteratorCopiesAreEqual) {
    const auto it1 = list.begin();
    const auto it2 = it1;

    auto it3 = list.end();
    it3 = it1;

    ASSERT_EQ(it1, it2);
    ASSERT_EQ(it1, it3);
}


TEST_F(ListTest, iteratorIncrementMovesToNextElement) {
    auto it = list.begin();

    ++it;
    ASSERT_EQ(*it, 2);

    it++;
    ASSERT_EQ(*it, 3);
}


TEST_F(ListTest, iteratorDecrementMovesToPreviousElement) {
    auto it = list.end();

    --it;
    ASSERT_EQ(*it, 3);

    it--;
    ASSERT_EQ(*it, 2);
}


TEST_F(ListTest, iteratorPostIncrementDecrementReturnsCurrentElement) {
    auto it = list.begin();

    ASSERT_EQ(*(it++), 1);
    ASSERT_EQ(*(it--), 2);
}


TEST_F(ListTest, moveLeavesListEmpty) {
    auto tmp = std::move(list);
    ASSERT_TRUE(list.isEmpty() && !tmp.isEmpty());

    list = std::move(tmp);
    ASSERT_TRUE(tmp.isEmpty() && !list.isEmpty());
}


TEST_F(ListTest, equivalentListsAreEqual) {
    const List<int> l1 = { 1, 2, 3 };

    ASSERT_EQ(list, list);
    ASSERT_EQ(list, l1);
}


TEST_F(ListTest, notEquivalentListsAreNotEqual) {
    const List<int> l1 = { 1, 4, 3 };
    const List<int> l2 = { 2, 2, 3 };
    const List<int> l3 = { 1, 2, 4 };
    const List<int> l4 = { 1, 2, 3, 4 };
    const List<int> l5 = { 1, 2 };

    ASSERT_NE(list, emptyList);
    ASSERT_NE(list, l1);
    ASSERT_NE(list, l2);
    ASSERT_NE(list, l3);
    ASSERT_NE(list, l4);
    ASSERT_NE(list, l5);
}


TEST_F(ListTest, listCopiesAreEqual) {
    auto copy1 = list;
    ASSERT_EQ(copy1, list);

    copy1 = emptyList;
    ASSERT_EQ(copy1, emptyList);

    auto copy2 = emptyList;
    ASSERT_EQ(copy2, emptyList);

    copy2 = list;
    ASSERT_EQ(copy2, list);
}
