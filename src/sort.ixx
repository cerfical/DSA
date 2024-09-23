module;

#include <algorithm>
#include <ranges>
#include <vector>

export module dsa:sort;

import :heap_util;


namespace dsa {

    /** @name Sorting */
    /** @{ */
    /**
     * @brief Sorts a range of values in @f$O(n^2)@f$ time.
     */
    export template <std::ranges::random_access_range R>
    void bubbleSort(R& rng) {
        for(auto it1 = std::ranges::end(rng); it1 != std::ranges::begin(rng); it1--) {
            bool sorted = true;

            for(auto it2 = std::ranges::begin(rng); it2 != it1 - 1; it2++) {
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
    export template <std::ranges::random_access_range R>
    void selectionSort(R& rng) {
        for(auto it = std::ranges::begin(rng); it != std::ranges::end(rng); it++) {
            std::iter_swap(it, std::min_element(it, std::ranges::end(rng)));
        }
    }


    /**
     * @brief Sorts a range of values in @f$O(n^2)@f$ time.
     */
    export template <std::ranges::random_access_range R>
    void insertionSort(R& rng) {
        for(auto it = std::ranges::begin(rng); it != std::ranges::end(rng); it++) {
            auto key = std::move(*it);
            auto insertPos = it;

            // find the right place to insert the value
            while(insertPos != std::ranges::begin(rng) && *(insertPos - 1) > key) {
                *insertPos = std::move(*(insertPos - 1));
                insertPos--;
            }

            *insertPos = std::move(key);
        }
    }


    /**
     * @brief Performs a recursive sort in @f$O(n * \lg n)@f$ time, using extra memory.
     */
    export template <std::ranges::random_access_range R>
    void mergeSort(R& rng) {
        const auto size = std::ranges::size(rng);
        if(size <= 1) {
            return;
        }

        // split the range into two halves and sort them independently
        const auto mid = std::ranges::begin(rng) + (size / 2);
        auto left = std::ranges::subrange(std::ranges::begin(rng), mid);
        auto right = std::ranges::subrange(mid, std::ranges::end(rng));

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

        std::ranges::move(result, std::ranges::begin(rng));
    }


    /**
     * @brief Performs a recursive in-place sort in @f$O(n * \lg n)@f$ time on average.
     */
    export template <std::ranges::random_access_range R>
    void quickSort(R& rng) {
        const auto size = std::ranges::size(rng);
        if(size < 2) {
            return;
        }

        const auto pivotPos = std::ranges::end(rng) - 1;
        auto pivot = std::move(*pivotPos);

        auto lessPos = std::ranges::begin(rng);
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

        const auto less = std::ranges::subrange(std::ranges::begin(rng), lessPos);
        const auto greater = std::ranges::subrange(lessPos, pivotPos);

        quickSort(less);
        quickSort(greater);

        std::ranges::move_backward(greater, std::ranges::end(rng));
        *greaterPos = std::move(pivot);
    }


    /**
     * @brief Performs an in-place sort in @f$O(n * \lg n)@f$.
     */
    export template <std::ranges::random_access_range R>
    void heapSort(R& rng) {
        heap_util::createHeap(rng);

        const auto heapStart = std::ranges::begin(rng);
        auto heapEnd = std::ranges::end(rng);

        while(heapEnd != heapStart) {
            auto heap = std::ranges::subrange(heapStart, heapEnd);
            auto value = heap_util::extractTop(heap);
            heapEnd--;

            *heapEnd = std::move(value);
        }
    }
    /** @} */

}
