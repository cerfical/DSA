#ifndef DSA_HEAP_HEADER
#define DSA_HEAP_HEADER

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
			heapify(0);
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
			while(n != 0 && m_data[n] < m_data[parentOf(n)]) {
				std::swap(m_data[n], m_data[parentOf(n)]);
				n = parentOf(n);
			}
		}

		T popAndReplaceTop() {
			auto value = std::exchange(m_data.front(), std::move(m_data.back()));
			m_data.pop_back();
			
			return value;
		}

		void heapify(std::size_t n) {
			auto min = n;
			while((min = smallerChildOrNode(n)) != n) {
				std::swap(m_data[n], m_data[min]);
				n = min;
			}
		}



		std::size_t parentOf(std::size_t n) const noexcept {
			return (n - 1) / 2;
		}

		std::size_t leftChildOf(std::size_t n) const noexcept {
			return n * 2 + 1;
		}

		std::size_t rightChildOf(std::size_t n) const noexcept {
			return n * 2 + 2;
		}



		std::size_t smallerChildOrNode(std::size_t n) const noexcept {
			return minimum(minimum(n, leftChildOf(n)), rightChildOf(n));
		}

		std::size_t minimum(std::size_t n, std::size_t child) const noexcept {
			if(child < m_data.size() && m_data[child] < m_data[n]) {
				return child;
			}
			return n;
		}



		std::vector<T> m_data;

	};
}

#endif
