//
// Created by robcholz on 9/25/23.
//
#pragma once

#ifndef RSL_DEQUE_HPP
#define RSL_DEQUE_HPP

#include <Internal.hpp>
#include "base/DynamicArray.hpp"


namespace rsl {
    template<typename T, rsl::size_t DEFAULT_CAPACITY = 10, typename BASE_CONTAINER=DynamicArray<T, DEFAULT_CAPACITY>>
    class RSL_UNUSED Deque {
    public:
        Deque() = default;

        template<typename... Args>
        explicit Deque(const Args &... args);

        template<rsl::size_t CAPACITY_>
        explicit Deque(const Deque<T, CAPACITY_> &other);

        template<rsl::size_t CAPACITY_>
        Deque &operator=(const Deque<T, CAPACITY_> &other);

        template<rsl::size_t CAPACITY_>
        Deque &operator=(Deque<T, CAPACITY_> &&other) noexcept;

        template<rsl::size_t CAPACITY_>
        bool operator==(const Deque<T, CAPACITY_> &other) const;

        template<rsl::size_t CAPACITY_>
        bool operator>(const Deque<T, CAPACITY_> &other) const;

        template<rsl::size_t CAPACITY_>
        bool operator<(const Deque<T, CAPACITY_> &other) const;

       // T &operator[](rsl::size_t index);

       // T operator[](rsl::size_t index) const;

        ~Deque() = default;

        RSL_UNUSED void add(const T &element);

        RSL_UNUSED void addFront(const T &element);

        RSL_UNUSED void addBack(const T &element);

        RSL_UNUSED T &element() const;

        RSL_UNUSED T &front() const;

        RSL_UNUSED T &back() const;

        RSL_UNUSED void pop();

        RSL_UNUSED void popFront();

        RSL_UNUSED void popBack();

        RSL_UNUSED void empty();

        RSL_UNUSED void trimToSize();

        RSL_UNUSED void capacity(rsl::size_t capacity);

        RSL_NODISCARD bool isEmpty() const;

        RSL_UNUSED T &get(rsl::size_t index);

        RSL_UNUSED T get(rsl::size_t index) const;

        RSL_UNUSED bool contains(const T &element) const;

        RSL_NODISCARD rsl::size_t length() const;

        RSL_NODISCARD rsl::size_t capacity() const;

        RSL_UNUSED void print() const;

    private:
        BASE_CONTAINER container;

    public:
	    typename BASE_CONTAINER::Iterator begin() const {
			return container.begin();
		}

	    typename BASE_CONTAINER::Iterator end() const {
		    return container.end();
		}
    };

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    template<typename... Args>
    Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::Deque(const Args &... args) {
        container = BASE_CONTAINER(args...);
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    template<rsl::size_t CAPACITY_>
    Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::Deque(const Deque<T, CAPACITY_> &other) {
        container(other.container);
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    template<rsl::size_t CAPACITY_>
    Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER> &Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::operator=(const Deque<T, CAPACITY_> &other) {
        container = other.container;
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    template<rsl::size_t CAPACITY_>
    Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER> &
    Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::operator=(Deque<T, CAPACITY_> &&other) noexcept {
        container = other.container;
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    template<rsl::size_t CAPACITY_>
    bool Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::operator==(const Deque<T, CAPACITY_> &other) const {
        return container == other.container;
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    template<rsl::size_t CAPACITY_>
    bool Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::operator>(const Deque<T, CAPACITY_> &other) const {
        return container > other.container;
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    template<rsl::size_t CAPACITY_>
    bool Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::operator<(const Deque<T, CAPACITY_> &other) const {
        return container < other.container;
    }

	/*
    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    T &Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::operator[](rsl::size_t index) {
        return container[index];
    }


    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    T Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::operator[](rsl::size_t index) const {
        return container[index];
    }
    */

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    void Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::add(const T &element) {
        container.addBack(element);
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    void Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::addFront(const T &element) {
        container.addFront(element);
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    void Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::addBack(const T &element) {
        container.addBack(element);
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    T &Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::element() const {
        return container.front();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    T &Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::front() const {
        return container.front();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    T &Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::back() const {
        return container.back();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    void Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::pop() {
        container.popFront();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    void Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::popFront() {
        container.popFront();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    void Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::popBack() {
        container.popBack();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    void Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::empty() {
        container.empty();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    void Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::trimToSize() {
        container.trimToSize();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    void Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::capacity(rsl::size_t capacity) {
        container.capacity(capacity);
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    bool Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::isEmpty() const {
        return container.isEmpty();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    T &Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::get(rsl::size_t index) {
        return container.get(index);
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    T Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::get(rsl::size_t index) const {
        return container.get(index);
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    bool Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::contains(const T &element) const {
        return container.contains(element);
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    rsl::size_t Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::length() const {
        return container.length();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    rsl::size_t Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::capacity() const {
        return container.capacity();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    void Deque<T, DEFAULT_CAPACITY, BASE_CONTAINER>::print() const {
        container.print();
    }
}

#endif //RSL_DEQUE_HPP
