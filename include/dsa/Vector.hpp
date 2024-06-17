#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <type_traits>

namespace dsa {

    template <typename T>
    class Vector {
        using DataStorage = std::aligned_storage_t<sizeof(T), alignof(T)>[];

    public:

        class ConstIterator {
            friend Vector;

        public:

            friend bool operator==(const ConstIterator& lhs, const ConstIterator& rhs) noexcept {
                return lhs.pos_ == rhs.pos_;
            }


            ConstIterator(const ConstIterator&) noexcept = default;
            ConstIterator& operator=(const ConstIterator&) noexcept = default;

            ConstIterator(ConstIterator&&) noexcept = default;
            ConstIterator& operator=(ConstIterator&&) noexcept = default;


            ConstIterator() noexcept = default;
            ~ConstIterator() = default;


            ConstIterator& operator++() noexcept {
                pos_++;
                return *this;
            }

            ConstIterator operator++(int) noexcept {
                const auto it = *this;
                operator++();
                return it;
            }


            ConstIterator& operator--() noexcept {
                pos_--;
                return *this;
            }

            ConstIterator operator--(int) noexcept {
                const auto it = *this;
                operator--();
                return it;
            }


            const T& operator*() const noexcept {
                return *pos_;
            }

            const T* operator->() const noexcept {
                return &operator*();
            }


        private:
            ConstIterator(T* pos) noexcept
                : pos_(pos) {}

            T* pos_ = {};
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


        Vector(const Vector& other)
            : data_(std::make_unique<DataStorage>(other.size_)), size_(other.size()), capacity_(other.size()) {

            std::copy(other.data(), other.data() + other.size(), data());
        }

        Vector& operator=(const Vector& other) {
            auto copy = other;
            std::swap(*this, copy);
            return *this;
        }


        Vector(Vector&& other) noexcept
            : data_(std::move(other.data_))
            , size_(std::exchange(other.size_, 0))
            , capacity_(std::exchange(other.capacity_, 0)) {}

        Vector& operator=(Vector&& other) noexcept {
            std::destroy_at(this);
            std::construct_at(this, std::move(other));

            return *this;
        }


        Vector(std::initializer_list<T> values) {
            for(const auto& v : values) {
                pushBack(v);
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

        std::size_t capacity() const noexcept {
            return capacity_;
        }


        void pushBack(T value) {
            insert(std::move(value), end());
        }

        T popBack() noexcept {
            auto val = std::move(back());
            erase(--end());
            return val;
        }


        const T& front() const noexcept {
            return const_cast<Vector*>(this)->front();
        }

        T& front() noexcept {
            return *begin();
        }


        const T& back() const noexcept {
            return const_cast<Vector*>(this)->back();
        }

        T& back() noexcept {
            return *(--end());
        }


        ConstIterator begin() const noexcept {
            return const_cast<Vector*>(this)->begin();
        }

        Iterator begin() noexcept {
            return { data() };
        }


        ConstIterator end() const noexcept {
            return const_cast<Vector*>(this)->end();
        }

        Iterator end() noexcept {
            return { data() + size_ };
        }


        void clear() noexcept {
            while(!isEmpty()) {
                erase(--end());
            }
        }

        bool isEmpty() const noexcept {
            return size() == 0;
        }

        std::size_t size() const noexcept {
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


        const T* data() const noexcept {
            return const_cast<Vector*>(this)->data();
        }

        T* data() noexcept {
            return reinterpret_cast<T*>(data_.get());
        }


        std::unique_ptr<DataStorage> data_;

        std::size_t size_ = 0;
        std::size_t capacity_ = 0;
    };

}
