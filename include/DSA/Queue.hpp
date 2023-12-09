#ifndef DSA_QUEUE_HEADER
#define DSA_QUEUE_HEADER

#include <deque>

namespace dsa {

	/**
	 * @brief Implements a simple FIFO queue.
	 */
	template <typename T>
	class Queue {
	public:

		Queue& operator=(const Queue&) = default;
		Queue& operator=(Queue&&) = default;
		

		/** @name Queue creation */
		/** @{ */
		Queue() = default;

		Queue(const Queue&) = default;
		Queue(Queue&&) = default;
		/** @} */


		/** @name Element insertion/retrieval */
		/** @{ */
		const T& front() const noexcept {
			return m_data.front();
		}

		const T& back() const noexcept {
			return m_data.back();
		}


		T& front() noexcept {
			return m_data.front();
		}

		T& back() noexcept {
			return m_data.back();
		}


		void push(const T& value) {
			m_data.push_back(value);
		}

		void push(T&& value) {
			m_data.push_back(std::move(value));
		}

		T pop() {
			auto value = std::move(m_data.front());
			m_data.pop_front();
			return value;
		}
		/** @} */


		/** @name Queue size */
		/** @{ */
		std::size_t size() const noexcept {
			return m_data.size();
		}

		bool isEmpty() const noexcept {
			return size() == 0;
		}
		/** @} */


	private:
		std::deque<T> m_data;
	};

}

#endif
