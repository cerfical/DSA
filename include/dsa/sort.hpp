#pragma once

#include "heap_util.hpp"

#include <algorithm>
#include <ranges>
#include <vector>

namespace dsa {

    /** @name Sorting */
    /** @{ */
    /**
     * @brief Sorts a range of values in @f$O(n^2)@f$ time.
     */
    template <std::ranges::random_access_range R>
    void bubbleSort(R&& range) {
        for(auto it1 = range.end(); it1 != range.begin(); it1--) {
            bool sorted = true;

            for(auto it2 = range.begin(); it2 != it1 - 1; it2++) {
                if(*(it2 + 1) < *it2) {
                    std::iter_swap(it2 + 1, it2);
                    sorted = false;
                }
            }

            // exit early, if no element was swapped
            if(sorted) {
                break;
            }
        }
    }


    /**
     * @brief Sorts a range of values in @f$O(n^2)@f$ time.
     */
    template <std::ranges::random_access_range R>
    void selectionSort(R&& range) {
        for(auto it = range.begin(); it != range.end(); it++) {
            std::iter_swap(it, std::min_element(it, range.end()));
        }
    }


    /**
     * @brief Sorts a range of values in @f$O(n^2)@f$ time.
     */
    template <std::ranges::random_access_range R>
    void insertionSort(R&& range) {
        for(auto it = range.begin(); it != range.end(); it++) {
            auto key = std::move(*it);
            auto insertPos = it;

            // find the right place to insert the value
            while(insertPos != range.begin() && *(insertPos - 1) > key) {
                *insertPos = std::move(*(insertPos - 1));
                insertPos--;
            }

            *insertPos = std::move(key);
        }
    }


    /**
     * @brief Performs a recursive sort in @f$O(n * \lg n)@f$ time, using extra memory.
     */
    template <std::ranges::random_access_range R>
    void mergeSort(R&& range) {
        const auto size = std::ranges::size(range);
        if(size <= 1) {
            return;
        }

        // split the range into two halves and sort them independently
        const auto mid = range.begin() + size / 2;
        auto left = std::ranges::subrange(range.begin(), mid);
        auto right = std::ranges::subrange(mid, range.end());

        mergeSort(left);
        mergeSort(right);

        // iteratively extract the smallest element from the two now sorted subsequences
        // and put it in a temporary storage to build a complete sorted sequence
        std::vector<std::ranges::range_value_t<R>> result;
        result.reserve(size);

        while(!std::ranges::empty(left) && !std::ranges::empty(right)) {
            if(left.front() < right.front()) {
                result.push_back(std::move(left.front()));
                left.advance(1);
            } else {
                result.push_back(std::move(right.front()));
                right.advance(1);
            }
        }

        // collect leftovers from either the left or right, depending on which half was emptied first
        std::ranges::move(left, std::back_inserter(result));
        std::ranges::move(right, std::back_inserter(result));

        std::ranges::move(result, range.begin());
    }


    /**
     * @brief Performs a recursive in-place sort in @f$O(n * \lg n)@f$ time on average.
     */
    template <std::ranges::random_access_range R>
    void quickSort(R&& range) {
        const auto size = std::ranges::size(range);
        if(size < 2) {
            return;
        }

        const auto pivotPos = range.end() - 1;
        auto pivot = std::move(*pivotPos);

        auto lessPos = range.begin();
        auto greaterPos = pivotPos;

        // move elements less than the pivot to the beginning of the range, other elements are moved to the end
        while(lessPos != greaterPos) {
            if(*lessPos < pivot) {
                lessPos++;
            } else {
                std::iter_swap(lessPos, greaterPos - 1);
                greaterPos--;
            }
        }

        const auto less = std::ranges::subrange(range.begin(), lessPos);
        const auto greater = std::ranges::subrange(lessPos, pivotPos);

        quickSort(less);
        quickSort(greater);

        std::ranges::move_backward(greater, range.end());
        *greaterPos = std::move(pivot);
    }


    /**
     * @brief Performs an in-place sort in @f$O(n * \lg n)@f$.
     */
    template <std::ranges::random_access_range R>
    void heapSort(R&& range) {
        heap::createHeap(range);

        const auto heapStart = std::ranges::begin(range);
        auto heapEnd = std::ranges::end(range);

        while(heapEnd != heapStart) {
            auto value = heap::extractTop(std::ranges::subrange(heapStart, heapEnd));
            heapEnd--;

            *heapEnd = std::move(value);
        }
    }
    /** @} */

}
