//
// Created by robcholz on 10/08/23.
//
#pragma once

#ifndef RSL_ALLOCATOR_HPP
#define RSL_ALLOCATOR_HPP

#include <Internal.hpp>


namespace rsl {
	template<typename T, rsl::signed_size_t MAX_OBJECTS = -1>
	class RSL_UNUSED ObjectAllocator {
	public:
		RSL_UNUSED T* malloc();

		RSL_UNUSED void free(rsl::ptr_t ptr);

		RSL_NODISCARD rsl::size_t size() const;

		RSL_NODISCARD rsl::signed_size_t maxObjects() const;

	private:
		rsl::size_t allocatedObjects = 0;
	};

	template<typename T, rsl::signed_size_t MAX_OBJECTS>
	T* ObjectAllocator<T, MAX_OBJECTS>::malloc() {
		RSL_RUNTIME_BOUND_CHECK_ARG(MAX_OBJECTS != -1 && allocatedObjects >= MAX_OBJECTS, "Allocated objects reached limit", return nullptr);
		++allocatedObjects;
		return (T*) (RSL_mm_ALLOC(sizeof(T)));
	}

	template<typename T, rsl::signed_size_t MAX_OBJECTS>
	void ObjectAllocator<T, MAX_OBJECTS>::free(rsl::ptr_t ptr) {
		--allocatedObjects;
		RSL_mm_FREE(ptr);
	}

	template<typename T, rsl::signed_size_t MAX_OBJECT>
	rsl::size_t ObjectAllocator<T, MAX_OBJECT>::size() const {
		return allocatedObjects;
	}

	template<typename T, rsl::signed_size_t MAX_OBJECT>
	rsl::signed_size_t ObjectAllocator<T, MAX_OBJECT>::maxObjects() const {
		return MAX_OBJECT;
	}
}

#endif //RSL_ALLOCATOR_HPP
