//
// Created by robcholz on 11/2/23.
//
#pragma once

#ifndef RSL_MEDIANAVERAGEFILTER_HPP
#define RSL_MEDIANAVERAGEFILTER_HPP


namespace rsl{
	class MedianAverageFilter{
		template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
		CALC_T Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::Filter::medianAverage(const Pipeline* pipeline) {
			static T sum;
			static rsl::size_t length;
			static rsl::size_t index;
			length = pipeline->container.length();
			sum = T{0};
			index = 0;
			for (const T& i: pipeline->container) {
				if (index != 0 || index != length - 1)
					sum += i;
				++index;
			}
			return sum / (DEFAULT_CAPACITY - 2);
		}

	};
}

#endif //RSL_MEDIANAVERAGEFILTER_HPP
