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
			m_data.push_back(value);
			HeapUtils::insertLast(m_data);
		}

		void push(T&& value) {
			m_data.push_back(std::move(value));
			HeapUtils::insertLast(m_data);
		}

		T pop() {
			auto value = HeapUtils::extractTop(m_data);
			m_data.pop_back();
			return value;
		}


		std::size_t size() const noexcept {
			return m_data.size();
		}

		bool isEmpty() const noexcept {
			return size() == 0;
		}


	private:
		std::vector<T> m_data;
	};
}

#endif
