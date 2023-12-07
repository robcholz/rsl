//
// Created by robcholz on 11/1/23.
//
#pragma once

#ifndef RSL_HEAPALLOCATOR_HPP
#define RSL_HEAPALLOCATOR_HPP

#include <Internal.hpp>
#include "container/base/List.hpp"


namespace rsl {
	template<typename T, rsl::signed_size_t MAX_OBJECTS>
	class RSL_UNUSED HeapAllocator {
	public:
		RSL_UNUSED HeapAllocator();

		RSL_UNUSED T* malloc(rsl::size_t size = -1);

		RSL_UNUSED void free(rsl::ptr_t ptr);

		RSL_NODISCARD rsl::size_t size() const;

		RSL_NODISCARD rsl::size_t allocatedBytes() const;

		RSL_NODISCARD rsl::size_t freeBytes() const;

		RSL_NODISCARD constexpr rsl::signed_size_t maxBytes() const;

	private:
		ListNode<T> container[MAX_OBJECTS + 1]; // one extra object for reservedHead
		const ListNode<T>* reservedHead;
		rsl::size_t allocNum;
	};

	template<typename T, rsl::signed_size_t MAX_OBJECTS>
	HeapAllocator<T, MAX_OBJECTS>::HeapAllocator(): reservedHead(nullptr), allocNum(0) {
		RSL_COMPILETIME_BOUND_CHECK(MAX_OBJECTS >= 0, "");
		static ListNode<T>* node;
		static rsl::size_t index;
		reservedHead = &container[0];
		node = reservedHead;
		for (index = 1; index < allocNum; ++index) {
			node->next = &container[index];
			container[index].next = nullptr;
			node = node->next;
		}
	}

	template<typename T, rsl::signed_size_t MAX_OBJECTS>
	T* HeapAllocator<T, MAX_OBJECTS>::malloc(rsl::size_t size) {
		RSL_RUNTIME_BOUND_CHECK_ARG(allocNum >= MAX_OBJECTS, "Allocated objects reached limit", return nullptr;);
		static ListNode<T>* node;
		node = reservedHead->next;
		reservedHead->next = node->next;
		++allocNum;
		return node;
	}

	template<typename T, rsl::signed_size_t MAX_OBJECTS>
	void HeapAllocator<T, MAX_OBJECTS>::free(rsl::ptr_t ptr) {
		RSL_RUNTIME_BOUND_CHECK_ARG((ptr >= container[0] && ptr <= container[MAX_OBJECTS - 1]), "", return;);
		((ListNode<T>*) ptr)->next = reservedHead->next;
		reservedHead->next = ptr;
		--allocNum;
	}

	template<typename T, rsl::signed_size_t MAX_OBJECTS>
	rsl::size_t HeapAllocator<T, MAX_OBJECTS>::size() const {
		return allocNum;
	}

	template<typename T, rsl::signed_size_t MAX_OBJECTS>
	rsl::size_t HeapAllocator<T, MAX_OBJECTS>::allocatedBytes() const {
		return allocNum * sizeof(T);
	}

	template<typename T, rsl::signed_size_t MAX_OBJECTS>
	rsl::size_t HeapAllocator<T, MAX_OBJECTS>::freeBytes() const {
		return (MAX_OBJECTS - allocNum) * sizeof(T);
	}

	template<typename T, rsl::signed_size_t MAX_OBJECTS>
	constexpr rsl::signed_size_t HeapAllocator<T, MAX_OBJECTS>::maxBytes() const {
		return MAX_OBJECTS * sizeof(T);
	}
}

#endif //RSL_HEAPALLOCATOR_HPP
