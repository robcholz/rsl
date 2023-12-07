//
// Created by robcholz on 10/8/23.
//
#pragma once

#ifndef RSL_PORTABLE_HPP
#define RSL_PORTABLE_HPP


#include "Headers.hpp"

#ifdef ARDUINO

#ifdef RSL_DEBUG_ENABLE

#define RSL_PRINT(arg) Serial.print(arg)
#define RSL_PRINTF(arg) Serial.println(arg)
#define RSL_TO_STR_NUM(arg) to_string(arg)
#define RSL_TO_STR_STR(arg) String(arg)

namespace rsl {
	template<typename T>
	struct numeric_limits {
		static const T max;
		static const T min;
	};

#define DECLARE_TEMPLATE_SPEC(type,max,min) template<> \
	struct numeric_limits<type> { \
		static const int max = std::numeric_limits<type>::max(); \
		static const int min = std::numeric_limits<int>::min(); \
	}                                      \
	DECLARE_TEMPLATE_SPEC(uint8_t,UINT8_MAX,UINT8_MIN);
	DECLARE_TEMPLATE_SPEC(uint16_t,UINT16_MAX,UINT16_MIN);
	DECLARE_TEMPLATE_SPEC(uint32_t,UINT32_MAX,UINT32_MIN);
	DECLARE_TEMPLATE_SPEC(uint64_t,UINT64_MAX,UINT64_MIN);

	DECLARE_TEMPLATE_SPEC(int8_t,INT8_MAX,INT8_MIN);
	DECLARE_TEMPLATE_SPEC(int16_t,INT16_MAX,INT16_MIN);
	DECLARE_TEMPLATE_SPEC(int32_t,INT32_MAX,INT32_MIN);
	DECLARE_TEMPLATE_SPEC(int64_t,INT64_MAX,INT64_MIN);
#undef DECLARE_TEMPLATE_SPEC
}

#endif

#else

#ifdef RSL_DEBUG_ENABLE

#define RSL_PRINT(arg) std::cout<<(arg)
#define RSL_PRINTF(arg) std::cout<<(arg)<<::std::endl
#define RSL_TO_STR_NUM(arg) std::to_string(arg)
#define RSL_TO_STR_CHAR(arg) std::string(arg)

namespace rsl {
	template<typename T>
	struct numeric_limits {
		static const T max=std::numeric_limits<T>::max();
		static const T min=std::numeric_limits<T>::min();
	};
}

#endif

#define RSL_mm_ALLOC(size) ::malloc(size)
#define RSL_mm_FREE(ptr) ::free(ptr)

namespace rsl {
	typedef long signed_size_t;
	typedef ::size_t size_t;
	typedef void* ptr_t;
}// namespace rsl

#endif

#endif //RSL_PORTABLE_HPP
