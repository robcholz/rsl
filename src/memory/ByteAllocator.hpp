//
// Created by robcholz on 9/25/23.
//
#pragma once

#ifndef RSL_ALLOCATOR_HPP
#define RSL_ALLOCATOR_HPP

#include <Internal.hpp>


namespace rsl {
	template<typename T, rsl::signed_size_t MAX_BYTES = -1>
	class RSL_UNUSED ByteAllocator {
	public:
		RSL_UNUSED T* malloc(rsl::size_t size);

		RSL_UNUSED void free(rsl::ptr_t ptr);

		RSL_NODISCARD rsl::size_t size() const;

		RSL_NODISCARD rsl::signed_size_t maxBytes() const;

	private:
		rsl::size_t allocatedBytes = 0;
	};

	template<typename T, rsl::signed_size_t MAX_BYTES>
	T* ByteAllocator<T, MAX_BYTES>::malloc(rsl::size_t size) {
		RSL_RUNTIME_BOUND_CHECK_ARG(MAX_BYTES != -1 && allocatedBytes >= MAX_BYTES, "Allocated objects reached limit", return nullptr;);
		allocatedBytes += size;
		return (T*) (::malloc(size));
	}

	template<typename T, rsl::signed_size_t MAX_BYTES>
	void ByteAllocator<T, MAX_BYTES>::free(rsl::ptr_t ptr) {
		--allocatedBytes;
		::free(ptr);
	}

	template<typename T, rsl::signed_size_t MAX_BYTES>
	rsl::size_t ByteAllocator<T, MAX_BYTES>::size() const {
		return allocatedBytes;
	}

	template<typename T, rsl::signed_size_t MAX_BYTES>
	rsl::signed_size_t ByteAllocator<T, MAX_BYTES>::maxBytes() const {
		return MAX_BYTES;
	}
}

#endif //RSL_ALLOCATOR_HPP
