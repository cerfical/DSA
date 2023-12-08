#ifndef DSA_HEAP_HEADER
#define DSA_HEAP_HEADER

#include "HeapUtils.hpp"
#include <vector>

namespace dsa {
	/**
	 * @brief Implements a fast queue that gives priority to 'smaller' elements first.
	 */
	template <typename T>
	class Heap {
	public:
		Heap() = default;


		Heap(const Heap&) = default;
		Heap& operator=(const Heap&) = default;

		Heap(Heap&&) = default;
		Heap& operator=(Heap&&) = default;


		const T& top() const noexcept {
			return m_data.front();
		}

		void push(const T& value) {
			insertValue(value);
		}

		void push(T&& value) {
			insertValue(std::move(value));
		}

		T pop() {
			auto value = popAndReplaceTop();
			HeapUtils::heapify(m_data, 0);
			return value;
		}


		std::size_t size() const noexcept {
			return m_data.size();
		}

		bool isEmpty() const noexcept {
			return size() == 0;
		}


	private:

		template <typename S>
		void insertValue(S&& value) {
			m_data.push_back(std::forward<S>(value));

			auto n = m_data.size() - 1;
			while(n != 0 && m_data[n] < m_data[HeapUtils::parentOf(n)]) {
				std::swap(m_data[n], m_data[HeapUtils::parentOf(n)]);
				n = HeapUtils::parentOf(n);
			}
		}

		T popAndReplaceTop() {
			auto value = std::exchange(m_data.front(), std::move(m_data.back()));
			m_data.pop_back();
			
			return value;
		}


		std::vector<T> m_data;

	};
}

#endif
