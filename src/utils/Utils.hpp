//
// Created by robcholz on 10/31/23.
//
#pragma once

#ifndef RSL_UTILS_HPP
#define RSL_UTILS_HPP


namespace rsl {
	template<typename T>
	inline constexpr const T& max(const T& a, const T& b) {
		return (a < b) ? b : a;
	}

	template<typename T>
	inline constexpr const T& min(const T& a, const T& b) {
		return (a > b) ? b : a;
	}

	template<typename T>
	inline constexpr T abs(const T& value) {
		return (value < 0) ? -value : value;
	}

	template<typename T>
	inline constexpr T fabs(const T& value) {
		return (value < 0) ? -value : value;
	}

	template<typename T, typename U>
	struct isSame {
		static constexpr bool value = false;

		isSame& operator=(const isSame&) = delete;

		~isSame() = delete;
	};

	template<typename T>
	struct isSame<T, T> {
		static constexpr bool value = true;

		isSame& operator=(const isSame&) = delete;

		~isSame() = delete;
	};
}

#endif //RSL_UTILS_HPP
