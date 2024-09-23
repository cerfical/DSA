module;

#include <cstddef>
#include <ranges>

export module dsa:heap_util;


namespace dsa::heap_util {

    [[nodiscard]]
    auto leftChild(std::size_t idx) noexcept -> std::size_t {
        return (idx * 2) + 1;
    }


    [[nodiscard]]
    auto rightChild(std::size_t idx) noexcept -> std::size_t {
        return (idx * 2) + 2;
    }


    [[nodiscard]]
    auto parent(std::size_t idx) noexcept -> std::size_t {
        return (idx - 1) / 2;
    }


    template <std::ranges::random_access_range R>
    void heapify(R& rng, std::size_t idx) noexcept {
        const auto rngSz = std::ranges::size(rng);
        while(true) {
            auto max = idx;
            if(const auto left = leftChild(idx); left < rngSz && rng[max] < rng[left]) {
                max = left;
            }
            if(const auto right = rightChild(idx); right < rngSz && rng[max] < rng[right]) {
                max = right;
            }

            if(max == idx) {
                break;
            }

            std::swap(rng[idx], rng[max]);
            idx = max;
        }
    }


    template <std::ranges::random_access_range R>
    void createHeap(R& rng) noexcept {
        const auto rngSz = std::ranges::size(rng);
        if(rngSz < 2) {
            return;
        }

        auto idx = parent(rngSz - 1) + 1;
        while(idx != 0) {
            idx--;
            heapify(rng, idx);
        }
    }


    template <std::ranges::random_access_range R>
    void insertLast(R& rng) noexcept {
        auto lastIdx = std::ranges::size(rng) - 1;
        while(lastIdx != 0 && rng[parent(lastIdx)] < rng[lastIdx]) {
            std::swap(rng[lastIdx], rng[parent(lastIdx)]);
            lastIdx = parent(lastIdx);
        }
    }


    template <std::ranges::random_access_range R>
    [[nodiscard]]
    auto extractTop(R& rng) noexcept -> std::ranges::range_value_t<R> {
        const auto first = std::ranges::begin(rng);
        const auto last = std::ranges::end(rng) - 1;

        auto value = std::exchange(*first, *last);
        auto newHeap = std::ranges::subrange(first, last);
        heapify(newHeap, 0);

        return value;
    }


    template <std::ranges::random_access_range R>
    [[nodiscard]]
    auto isHeap(const R& rng, std::size_t idx = 0) noexcept -> bool {
        const auto rngSz = std::ranges::size(rng);

        const auto right = rightChild(idx);
        const auto left = leftChild(idx);

        if(left >= rngSz || right >= rngSz) {
            return false;
        }

        if(rng[idx] < rng[left] || rng[idx] < rng[right]) {
            return false;
        }

        return isHeap(rng, left) && isHeap(right);
    }

}
