#ifndef DSA_HEAP_UTILS_HEADER
#define DSA_HEAP_UTILS_HEADER

#include <ranges>

namespace dsa {
	/**
	 * @brief A set of utilities for working with a heap defined within some range.
	 */
	class HeapUtils {
	public:

		/**
		 * @brief Enforces the min-heap property on a node, given that all other descendant nodes already satisfy the property.
		 */
		template <std::ranges::random_access_range R>
		static void heapify(R&& range, std::size_t n) {
			auto min = n;
			while((min = smallerChildOrNode(std::forward<R>(range), n)) != n) {
				std::swap(range[n], range[min]);
				n = min;
			}
		}


		/**
		 * @brief Builds a min-heap in a range that allows random access to its elements.
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
				heapify(std::forward<R>(range), n);
			}
		}


		static std::size_t leftChildOf(std::size_t n) noexcept {
			return n * 2 + 1;
		}

		static std::size_t rightChildOf(std::size_t n) noexcept {
			return n * 2 + 2;
		}

		static std::size_t parentOf(std::size_t n) noexcept {
			return (n - 1) / 2;
		}


	private:

		template <typename R>
		static std::size_t smallerChildOrNode(R&& range, std::size_t n) {
			return minimum(std::forward<R>(range),
				minimum(std::forward<R>(range), n, leftChildOf(n)),
				rightChildOf(n)
			);
		}

		template <typename R>
		static std::size_t minimum(R&& range, std::size_t n, std::size_t child) {
			if(child < std::ranges::size(range) && range[child] < range[n]) {
				return child;
			}
			return n;
		}


		HeapUtils() = delete;
		~HeapUtils() = delete;

	};
}

#endif
