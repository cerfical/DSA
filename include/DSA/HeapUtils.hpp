#ifndef DSA_HEAP_UTILS_HEADER
#define DSA_HEAP_UTILS_HEADER

#include <ranges>

namespace dsa {
	/**
	 * @brief A set of utilities for working with a heap defined within some owning container.
	 */
	class HeapUtils {
	public:

		/** @name Heap management functions */
		/** @{ */
		/**
		 * @brief Builds a max-heap in a range that allows random access to its elements.
		 */
		template <std::ranges::random_access_range R>
		static void createHeap(R&& range) {
			const auto size = std::ranges::size(range);
			if(size < 2) {
				return;
			}

			auto n = parentOf(size - 1) + 1;
			while(n != 0) {
				n--;
				heapify(range, n);
			}
		}


		/**
		 * @brief Inserts the value placed last in the range into the heap.
		 */
		template <std::ranges::random_access_range R>
		static void insertLast(R&& range) {
			auto n = std::ranges::size(range) - 1;
			while(n != 0 && range[parentOf(n)] < range[n]) {
				std::swap(range[n], range[parentOf(n)]);
				n = parentOf(n);
			}
		}


		/**
		 * @brief Extracts the top element from the heap and shifts the heap by one position to replace the removed element.
		 */
		template <std::ranges::random_access_range R>
		static auto extractTop(R&& range) {
			const auto first = std::ranges::begin(range);
			const auto last = std::ranges::end(range) - 1;
			
			auto value = std::exchange(*first, *last);
			heapify(std::ranges::subrange(first, last), 0);
			return value;
		}


		/** @brief Checks a range of values against the max-heap property constraints. */
		template <std::ranges::random_access_range R>
		static bool isHeap(R&& range, std::size_t startNode = 0) {
			return hasMaxHeapProperty(range, startNode, leftChildOf(startNode))
				&& hasMaxHeapProperty(range, startNode, rightChildOf(startNode));
		}
		/** @} */



		/** @name Binary heap traversal functions */
		/** @{ */
		static std::size_t leftChildOf(std::size_t node) noexcept {
			return node * 2 + 1;
		}

		static std::size_t rightChildOf(std::size_t node) noexcept {
			return node * 2 + 2;
		}

		static std::size_t parentOf(std::size_t node) noexcept {
			return (node - 1) / 2;
		}
		/** @} */



	private:

		template <typename R>
		static void heapify(R&& range, std::size_t n) {
			auto max = n;
			while((max = largerChildOrNode(range, n)) != n) {
				std::swap(range[n], range[max]);
				n = max;
			}
		}


		template <typename R>
		static std::size_t largerChildOrNode(const R& range, std::size_t n) {
			return maximum(range,
				maximum(range, n, leftChildOf(n)),
				rightChildOf(n)
			);
		}


		template <typename R>
		static std::size_t maximum(const R& range, std::size_t n, std::size_t child) {
			if(child < std::ranges::size(range) && range[n] < range[child]) {
				return child;
			}
			return n;
		}


		template <typename R>
		static bool hasMaxHeapProperty(const R& range, std::size_t n, std::size_t child) {
			if(child < std::ranges::size(range)) {
				if(range[n] < range[child] || !isHeap(range, child)) {
					return false;
				}
			}
			return true;
		}


		HeapUtils() = delete;
		~HeapUtils() = delete;

	};
}

#endif
