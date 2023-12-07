//
// Created by robcholz on 10/31/23.
//
#pragma once

#ifndef RSL_TYPES_HPP
#define RSL_TYPES_HPP

#include "container/base/StaticArray.hpp"
#include "container/base/StaticList.hpp"
#include "container/Deque.hpp"
#include "container/Queue.hpp"
#include "container/Stack.hpp"


namespace rsl {
	template<typename T, rsl::size_t DEFAULT_CAPACITY = 10>
	using StaticDeque = Deque<T, DEFAULT_CAPACITY, StaticArray<T, DEFAULT_CAPACITY>>;
	template<typename T, rsl::size_t DEFAULT_CAPACITY = 10>
	using DynamicDeque = Deque<T, DEFAULT_CAPACITY, DynamicArray<T, DEFAULT_CAPACITY>>;
	template<typename T, rsl::size_t DEFAULT_CAPACITY = 10>
	using StaticQueue = Queue<T, DEFAULT_CAPACITY, StaticList<T, DEFAULT_CAPACITY>>;
	template<typename T, rsl::size_t DEFAULT_CAPACITY = 10>
	using DynamicQueue = Queue<T, DEFAULT_CAPACITY, DynamicList<T, DEFAULT_CAPACITY>>;
	template<typename T, rsl::size_t DEFAULT_CAPACITY = 10>
	using StaticStack = Stack<T, DEFAULT_CAPACITY, StaticList<T, DEFAULT_CAPACITY>>;
	template<typename T, rsl::size_t DEFAULT_CAPACITY = 10>
	using DynamicStack = Stack<T, DEFAULT_CAPACITY, DynamicList<T, DEFAULT_CAPACITY>>;
}

#endif //RSL_TYPES_HPP
