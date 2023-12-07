//
// Created by robcholz on 11/2/23.
//
#pragma once

#ifndef RSL_MEDIANFILTER_HPP
#define RSL_MEDIANFILTER_HPP


namespace rsl{
	class MedianFilter{
		ttemplate<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
				CALC_T Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::Filter::median(const Pipeline* pipeline) {
			static rsl::size_t index;
			static rsl::size_t length;
			index = 0;
			length = pipeline->container.length() / 2;
			for (const T& i: pipeline->container) {
				if (index == length)
					return i;
				++index;
			}
			return CALC_T{0}; // for static code analysis only
		}
	};
}

#endif //RSL_MEDIANFILTER_HPP
