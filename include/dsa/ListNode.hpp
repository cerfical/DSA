#pragma once

namespace dsa {

    /**
     * @brief Represents a single List element with a value.
     */
    template <typename T>
    struct ListNode {
        ListNode* prev = {};
        ListNode* next = {};

        T value;
    };

}
