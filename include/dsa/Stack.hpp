#pragma once

#include <deque>

namespace dsa {

	/**
	 * @brief Implements a simple LIFO stack.
	 */
	template <typename T>
	class Stack {
	public:

		Stack& operator=(const Stack&) = default;
		Stack& operator=(Stack&&) = default;


		/** @name Stack creation */
		/** @{ */
		Stack() = default;

		Stack(const Stack&) = default;
		Stack(Stack&&) = default;
		/** @} */


		/** @name Element insertion/retrieval */
		/** @{ */
		const T& top() const noexcept {
			return m_data.back();
		}

		T& top() noexcept {
			return m_data.back();
		}


		void push(const T& value) {
			m_data.push_back(value);
		}

		void push(T&& value) {
			m_data.push_back(std::move(value));
		}

		T pop() {
			auto value = std::move(m_data.back());
			m_data.pop_back();
			return value;
		}
		/** @} */


		/** @name Stack size */
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
