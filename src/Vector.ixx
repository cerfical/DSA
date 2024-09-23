module;

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <type_traits>

export module dsa:Vector;


namespace dsa {

    export template <typename T>
    class Vector {
        using DataStorage = std::aligned_storage_t<sizeof(T), alignof(T)>[];

    public:

        class ConstIterator {
            friend Vector;

        public:

            [[nodiscard]]
            friend auto operator==(const ConstIterator& lhs, const ConstIterator& rhs) noexcept -> bool {
                return lhs.pos_ == rhs.pos_;
            }


            ConstIterator(const ConstIterator&) noexcept = default;
            auto operator=(const ConstIterator&) noexcept -> ConstIterator& = default;

            ConstIterator(ConstIterator&&) noexcept = default;
            auto operator=(ConstIterator&&) noexcept -> ConstIterator& = default;


            ConstIterator() noexcept = default;
            ~ConstIterator() = default;


            auto operator++() noexcept -> ConstIterator& {
                pos_ = std::next(pos_);
                return *this;
            }

            auto operator++(int) noexcept -> ConstIterator {
                const auto it = *this;
                operator++();
                return it;
            }


            auto operator--() noexcept -> ConstIterator& {
                pos_ = std::prev(pos_);
                return *this;
            }

            auto operator--(int) noexcept -> ConstIterator {
                const auto it = *this;
                operator--();
                return it;
            }


            [[nodiscard]]
            auto operator*() const noexcept -> const T& {
                return *pos_;
            }

            [[nodiscard]]
            auto operator->() const noexcept -> const T* {
                return &operator*();
            }


        private:
            ConstIterator(T* pos) noexcept
                : pos_(pos) {}

            T* pos_ = {};
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


        Vector(const Vector& other)
            : data_(std::make_unique<DataStorage>(other.size_)), size_(other.size()), capacity_(other.size()) {

            std::copy(other.data(), other.data() + other.size(), data());
        }

        auto operator=(const Vector& other) -> Vector& {
            auto copy = other;
            std::swap(*this, copy);
            return *this;
        }


        Vector(Vector&& other) noexcept
            : data_(std::move(other.data_))
            , size_(std::exchange(other.size_, 0))
            , capacity_(std::exchange(other.capacity_, 0)) {}

        auto operator=(Vector&& other) noexcept -> Vector& {
            std::destroy_at(this);
            std::construct_at(this, std::move(other));

            return *this;
        }


        Vector(std::initializer_list<T> values) {
            for(const auto& value : values) {
                pushBack(value);
            }
        }


        Vector() noexcept = default;

        ~Vector() {
            clear();
        }


        void reserve(std::size_t capacity) {
            if(capacity > capacity_) {
                auto newData = std::make_unique<DataStorage>(capacity);

                std::uninitialized_move(data(), data() + size(), reinterpret_cast<T*>(newData.get()));

                data_ = std::move(newData);
                capacity_ = capacity;
            }
        }

        [[nodiscard]]
        auto capacity() const noexcept -> std::size_t {
            return capacity_;
        }


        void pushBack(T value) {
            insert(std::move(value), end());
        }

        [[nodiscard]]
        auto popBack() noexcept -> T {
            auto val = std::move(back());
            erase(--end());
            return val;
        }


        [[nodiscard]]
        auto front() const noexcept -> const T& {
            return const_cast<Vector*>(this)->front();
        }

        [[nodiscard]]
        auto front() noexcept -> T& {
            return *begin();
        }


        [[nodiscard]]
        auto back() const noexcept -> const T& {
            return const_cast<Vector*>(this)->back();
        }

        [[nodiscard]]
        auto back() noexcept -> T& {
            return *(--end());
        }


        [[nodiscard]]
        auto begin() const noexcept -> ConstIterator {
            return const_cast<Vector*>(this)->begin();
        }

        [[nodiscard]]
        auto begin() noexcept -> Iterator {
            return { data() };
        }


        [[nodiscard]]
        auto end() const noexcept -> ConstIterator {
            return const_cast<Vector*>(this)->end();
        }

        [[nodiscard]]
        auto end() noexcept -> Iterator {
            return { data() + size_ };
        }


        void clear() noexcept {
            while(!isEmpty()) {
                erase(--end());
            }
        }

        [[nodiscard]]
        auto isEmpty() const noexcept -> bool {
            return size() == 0;
        }

        [[nodiscard]]
        auto size() const noexcept -> std::size_t {
            return size_;
        }


    private:
        void insert(T&& value, ConstIterator where) {
            const auto insertIndex = where.pos_ - data();
            if(size() == capacity()) {
                reserve(std::max(capacity() * 2, static_cast<std::size_t>(1)));
            }

            const auto insertPos = data() + insertIndex;
            std::move_backward(insertPos, data() + size(), data() + size() + 1);

            *insertPos = std::move(value);
            size_++;
        }

        void erase(ConstIterator where) noexcept {
            // shift all elements except the erased element to the left by one position
            const auto last = std::move(where.pos_ + 1, data() + size(), where.pos_);

            // the last moved element needs to be destroyed
            std::destroy_at(last - 1);

            size_--;
        }


        [[nodiscard]]
        auto data() const noexcept -> const T* {
            return const_cast<Vector*>(this)->data();
        }

        [[nodiscard]]
        auto data() noexcept -> T* {
            return reinterpret_cast<T*>(data_.get());
        }


        std::unique_ptr<DataStorage> data_;

        std::size_t size_ = 0;
        std::size_t capacity_ = 0;
    };

}
