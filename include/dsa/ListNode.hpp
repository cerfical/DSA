#ifndef DSA_LIST_NODE_HEADER
#define DSA_LIST_NODE_HEADER

namespace dsa {

	/**
	 * @brief Represents a single List element with a value.
	 */
	template <typename T>
	struct ListNode {

		T value;

		ListNode* prev = {};
		ListNode* next = {};

	};

}

#endif
