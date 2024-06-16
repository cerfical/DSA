#pragma once

#include <cstddef>
#include <initializer_list>
#include <memory>

namespace dsa {

    /**
     * @brief Implements a doubly linked list.
     */
    template <typename T>
    class List {
        struct ListNode;

    public:

        class ConstIterator {
            friend List;

        public:

            friend bool operator==(const ConstIterator& lhs, const ConstIterator& rhs) noexcept {
                return lhs.currentNode_ == rhs.currentNode_;
            }


            ConstIterator(const ConstIterator&) noexcept = default;
            ConstIterator& operator=(const ConstIterator&) noexcept = default;

            ConstIterator(ConstIterator&&) noexcept = default;
            ConstIterator& operator=(ConstIterator&&) noexcept = default;


            ConstIterator() noexcept = default;
            ~ConstIterator() = default;


            ConstIterator& operator++() noexcept {
                currentNode_ = currentNode_->next;
                return *this;
            }

            ConstIterator operator++(int) noexcept {
                const auto it = *this;
                operator++();
                return it;
            }


            ConstIterator& operator--() noexcept {
                currentNode_ = currentNode_->prev;
                return *this;
            }

            ConstIterator operator--(int) noexcept {
                const auto it = *this;
                operator--();
                return it;
            }


            const T& operator*() const noexcept {
                return currentNode_->value;
            }

            const T* operator->() const noexcept {
                return &operator*();
            }


        private:
            ConstIterator(ListNode* node) noexcept
                : currentNode_(node) {}

            ListNode* currentNode_ = {};
        };


        class Iterator : public ConstIterator {
        public:

            Iterator& operator++() noexcept {
                ConstIterator::operator++();
                return *this;
            }

            Iterator operator++(int) noexcept {
                const auto it = *this;
                operator++();
                return it;
            }


            Iterator& operator--() noexcept {
                ConstIterator::operator--();
                return *this;
            }

            Iterator operator--(int) noexcept {
                const auto it = *this;
                operator--();
                return it;
            }


            T& operator*() const noexcept {
                return const_cast<T&>(ConstIterator::operator*());
            }

            T* operator->() const noexcept {
                return &operator*();
            }


        private:
            using ConstIterator::ConstIterator;
        };


        List(const List& other) {
            for(const auto& val : other) {
                pushBack(val);
            }
        }

        List& operator=(const List& other) {
            auto copy = other;
            std::swap(*this, copy);
            return *this;
        }


        List(List&& other) noexcept
            : size_(std::exchange(other.size_, 0)) {

            auto* const last = other.head_.prev;
            auto* const first = other.head_.next;

            last->next = static_cast<ListNode*>(&head_);
            first->prev = static_cast<ListNode*>(&head_);

            head_ = std::exchange(other.head_, other.makeListHead());
        }

        List& operator=(List&& other) noexcept {
            std::destroy_at(this);
            std::construct_at(this, std::move(other));

            return *this;
        }


        List(std::initializer_list<T> values) {
            for(const auto& v : values) {
                pushBack(v);
            }
        }


        List() noexcept = default;

        ~List() {
            clear();
        }


        void pushFront(T value) {
            insert(std::move(value), begin());
        }

        void pushBack(T value) {
            insert(std::move(value), end());
        }


        T popFront() noexcept {
            auto val = std::move(front());
            erase(begin());
            return val;
        }

        const T& front() const noexcept {
            return const_cast<List*>(this)->front();
        }

        T& front() noexcept {
            return *begin();
        }


        T popBack() noexcept {
            auto val = std::move(back());
            erase(--end());
            return val;
        }

        const T& back() const noexcept {
            return const_cast<List*>(this)->back();
        }

        T& back() noexcept {
            return *(--end());
        }


        std::size_t size() const noexcept {
            return size_;
        }

        bool isEmpty() const noexcept {
            return size() == 0;
        }

        void clear() noexcept {
            while(!isEmpty()) {
                erase(--end());
            }
        }


        ConstIterator begin() const noexcept {
            return const_cast<List*>(this)->begin();
        }

        Iterator begin() noexcept {
            return { head_.next };
        }


        ConstIterator end() const noexcept {
            return const_cast<List*>(this)->end();
        }

        Iterator end() noexcept {
            return { static_cast<ListNode*>(&head_) };
        }


    private:

        struct ListHeadNode {
            ListNode* prev = {};
            ListNode* next = {};
        };

        struct ListNode : public ListHeadNode {
            ListNode(T&& value, ListNode* next) noexcept
                : ListHeadNode(next->prev, next), value(std::move(value)) {}

            T value;
        };


        void insert(T&& value, ConstIterator where) {
            auto* const next = where.currentNode_;
            auto n = std::make_unique<ListNode>(std::move(value), next);

            next->prev->next = n.get();
            next->prev = n.get();

            n.release();
            size_++;
        }

        void erase(ConstIterator where) noexcept {
            const auto n = std::unique_ptr<ListNode>(where.currentNode_);

            n->prev->next = n->next;
            n->next->prev = n->prev;
            size_--;
        }


        ListHeadNode makeListHead() noexcept {
            const auto head = static_cast<ListNode*>(&head_);
            return { head, head };
        }

        ListHeadNode head_ = makeListHead();
        std::size_t size_ = 0;
    };

}
