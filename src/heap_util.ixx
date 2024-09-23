module;

#include <cstddef>
#include <ranges>

export module dsa:heap_util;


namespace dsa::heap_util {

    inline std::size_t leftChildNode(std::size_t node) noexcept {
        return node * 2 + 1;
    }

    inline std::size_t rightChildNode(std::size_t node) noexcept {
        return node * 2 + 2;
    }

    inline std::size_t parentNode(std::size_t node) noexcept {
        return (node - 1) / 2;
    }


    template <std::ranges::random_access_range R>
    void heapify(R&& range, std::size_t startNode) noexcept {
        const auto largerChildNodeOr = [](const R& range, auto n) {
            const auto maximumNode = [](const R& range, auto n, auto child) {
                if(child < std::ranges::size(range) && range[n] < range[child]) {
                    return child;
                }
                return n;
            };

            return maximumNode(range, maximumNode(range, n, leftChildNode(n)), rightChildNode(n));
        };

        auto max = startNode;
        while((max = largerChildNodeOr(range, startNode)) != startNode) {
            std::swap(range[startNode], range[max]);
            startNode = max;
        }
    }


    template <std::ranges::random_access_range R>
    void createHeap(R&& range) noexcept {
        const auto size = std::ranges::size(range);
        if(size < 2) {
            return;
        }

        auto n = parentNode(size - 1) + 1;
        while(n != 0) {
            n--;
            heapify(range, n);
        }
    }


    template <std::ranges::random_access_range R>
    void insertLast(R&& range) noexcept {
        auto n = std::ranges::size(range) - 1;
        while(n != 0 && range[parentNode(n)] < range[n]) {
            std::swap(range[n], range[parentNode(n)]);
            n = parentNode(n);
        }
    }


    template <std::ranges::random_access_range R>
    auto extractTop(R&& range) noexcept -> std::ranges::range_value_t<R> {
        const auto first = std::ranges::begin(range);
        const auto last = std::ranges::end(range) - 1;

        auto value = std::exchange(*first, *last);
        heapify(std::ranges::subrange(first, last), 0);

        return value;
    }


    template <std::ranges::random_access_range R>
    bool isHeap(R&& range, std::size_t startNode = 0) noexcept {
        const auto hasMaxHeapProp = [](const R& range, auto n, auto child) {
            if(child < std::ranges::size(range)) {
                if(range[n] < range[child] || !isHeap(std::forward<R>(range), child)) {
                    return false;
                }
            }
            return true;
        };

        return hasMaxHeapProp(range, startNode, leftChildNode(startNode))
            && hasMaxHeapProp(range, startNode, rightChildNode(startNode));
    }

}
