//
// Created by robcholz on 9/25/23.
//
#pragma once

#ifndef RSL_QUEUE_HPP
#define RSL_QUEUE_HPP

#include <Internal.hpp>
#include "base/DynamicList.hpp"


namespace rsl {
    template<typename T, rsl::size_t DEFAULT_CAPACITY = 10, typename BASE_CONTAINER=DynamicList<T, DEFAULT_CAPACITY>>
    class Queue {
    public:
        Queue() = default;

        RSL_UNUSED void add(const T &element);

        RSL_UNUSED void pop();

        template<rsl::size_t CAPACITY_, typename BASE_CONTAINER_>
        RSL_UNUSED void swap(const Queue<T, CAPACITY_, BASE_CONTAINER_> &other);

        RSL_UNUSED T &element() const;

        RSL_UNUSED T &front() const;

        RSL_NODISCARD bool isEmpty() const;

        RSL_NODISCARD rsl::size_t length() const;

        RSL_NODISCARD rsl::size_t capacity() const;

    private:
        BASE_CONTAINER container;
    };

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    RSL_UNUSED
    void Queue<T, DEFAULT_CAPACITY, BASE_CONTAINER>::add(const T &element) {
        container.addFront(element);
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    RSL_UNUSED
    void Queue<T, DEFAULT_CAPACITY, BASE_CONTAINER>::pop() {
        container.popBack();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    template<rsl::size_t CAPACITY_, typename BASE_CONTAINER_>
    RSL_UNUSED
    void Queue<T, DEFAULT_CAPACITY, BASE_CONTAINER>::swap(const Queue<T, CAPACITY_, BASE_CONTAINER_> &other) {
        static rsl::size_t thisLength;
        static rsl::size_t index;
        thisLength = container.length();
        container.addBack(other);
        other.empty();
        for (index = 0; index < thisLength; ++index) {
            other.addFront(container.front());
            container.popFront();
        }
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    RSL_UNUSED
    T &Queue<T, DEFAULT_CAPACITY, BASE_CONTAINER>::element() const {
        container.front();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    RSL_UNUSED
    T &Queue<T, DEFAULT_CAPACITY, BASE_CONTAINER>::front() const {
        return container.front();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    RSL_UNUSED
    bool Queue<T, DEFAULT_CAPACITY, BASE_CONTAINER>::isEmpty() const {
        return container.isEmpty();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    RSL_UNUSED
    rsl::size_t Queue<T, DEFAULT_CAPACITY, BASE_CONTAINER>::length() const {
        return container.length();
    }

    template<typename T, rsl::size_t DEFAULT_CAPACITY, typename BASE_CONTAINER>
    RSL_UNUSED
    rsl::size_t Queue<T, DEFAULT_CAPACITY, BASE_CONTAINER>::capacity() const {
        return container.capacity();
    }
}

#endif //RSL_QUEUE_HPP
