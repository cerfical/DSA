module;

#include <cstddef>
#include <initializer_list>
#include <memory>

export module dsa:List;


namespace dsa {

    /**
     * @brief Implements a doubly linked list.
     */
    export template <typename T>
    class List {
        struct ListNode;

    public:

        class ConstIterator {
            friend List;

        public:

            [[nodiscard]]
            friend auto operator==(const ConstIterator& lhs, const ConstIterator& rhs) noexcept -> bool {
                return lhs.currentNode_ == rhs.currentNode_;
            }


            ConstIterator(const ConstIterator&) noexcept = default;
            auto operator=(const ConstIterator&) noexcept -> ConstIterator& = default;

            ConstIterator(ConstIterator&&) noexcept = default;
            auto operator=(ConstIterator&&) noexcept -> ConstIterator& = default;


            ConstIterator() noexcept = default;
            ~ConstIterator() = default;


            auto operator++() noexcept -> ConstIterator& {
                currentNode_ = currentNode_->next;
                return *this;
            }

            auto operator++(int) noexcept -> ConstIterator {
                const auto it = *this;
                operator++();
                return it;
            }


            auto operator--() noexcept -> ConstIterator& {
                currentNode_ = currentNode_->prev;
                return *this;
            }

            auto operator--(int) noexcept -> ConstIterator {
                const auto it = *this;
                operator--();
                return it;
            }


            [[nodiscard]]
            auto operator*() const noexcept -> const T& {
                return currentNode_->value;
            }

            [[nodiscard]]
            auto operator->() const noexcept -> const T* {
                return &operator*();
            }


        private:
            ConstIterator(ListNode* node) noexcept
                : currentNode_(node) {}

            ListNode* currentNode_ = {};
        };


        class Iterator : public ConstIterator {
        public:

            auto operator++() noexcept -> Iterator& {
                ConstIterator::operator++();
                return *this;
            }

            auto operator++(int) noexcept -> Iterator {
                const auto it = *this;
                operator++();
                return it;
            }


            auto operator--() noexcept -> Iterator& {
                ConstIterator::operator--();
                return *this;
            }

            auto operator--(int) noexcept -> Iterator {
                const auto it = *this;
                operator--();
                return it;
            }


            [[nodiscard]]
            auto operator*() const noexcept -> T& {
                return const_cast<T&>(ConstIterator::operator*());
            }

            [[nodiscard]]
            auto operator->() const noexcept -> T* {
                return &operator*();
            }


        private:
            using ConstIterator::ConstIterator;
        };


        List(const List& other) {
            for(const auto& value : other) {
                pushBack(value);
            }
        }

        auto operator=(const List& other) -> List& {
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

        auto operator=(List&& other) noexcept -> List& {
            std::destroy_at(this);
            std::construct_at(this, std::move(other));

            return *this;
        }


        List(std::initializer_list<T> values) {
            for(const auto& value : values) {
                pushBack(value);
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


        [[nodiscard]]
        auto popFront() noexcept -> T {
            auto value = std::move(front());
            erase(begin());
            return value;
        }

        [[nodiscard]]
        auto front() const noexcept -> const T& {
            return const_cast<List*>(this)->front();
        }

        [[nodiscard]]
        auto front() noexcept -> T& {
            return *begin();
        }


        [[nodiscard]]
        auto popBack() noexcept -> T {
            auto value = std::move(back());
            erase(--end());
            return value;
        }

        [[nodiscard]]
        auto back() const noexcept -> const T& {
            return const_cast<List*>(this)->back();
        }

        [[nodiscard]]
        auto back() noexcept -> T& {
            return *(--end());
        }


        [[nodiscard]]
        auto size() const noexcept -> std::size_t {
            return size_;
        }

        [[nodiscard]]
        auto isEmpty() const noexcept -> bool {
            return size() == 0;
        }

        void clear() noexcept {
            while(!isEmpty()) {
                erase(--end());
            }
        }


        [[nodiscard]]
        auto begin() const noexcept -> ConstIterator {
            return const_cast<List*>(this)->begin();
        }

        [[nodiscard]]
        auto begin() noexcept -> Iterator {
            return { head_.next };
        }


        [[nodiscard]]
        auto end() const noexcept -> ConstIterator {
            return const_cast<List*>(this)->end();
        }

        [[nodiscard]]
        auto end() noexcept -> Iterator {
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
            auto node = std::make_unique<ListNode>(std::move(value), next);

            next->prev->next = node.get();
            next->prev = node.get();

            node.release();
            size_++;
        }

        void erase(ConstIterator where) noexcept {
            const auto node = std::unique_ptr<ListNode>(where.currentNode_);

            node->prev->next = node->next;
            node->next->prev = node->prev;
            size_--;
        }


        auto makeListHead() noexcept -> ListHeadNode {
            const auto head = static_cast<ListNode*>(&head_);
            return { head, head };
        }

        ListHeadNode head_ = makeListHead();
        std::size_t size_ = 0;
    };

}
