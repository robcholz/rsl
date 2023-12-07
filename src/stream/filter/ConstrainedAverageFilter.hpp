//
// Created by robcholz on 11/2/23.
//
#pragma once

#ifndef RSL_CONSTRAINEDAVERAGEFILTER_HPP
#define RSL_CONSTRAINEDAVERAGEFILTER_HPP


namespace rsl{
	class ConstrainedAverageFilter{
		template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
		template<const T MAX_DIFFERENCE>
		CALC_T Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::Filter::constrainedAverage(const Pipeline* pipeline) {
			static T sum;
			static rsl::size_t length;
			static rsl::size_t index;
			static T val, prevVal;
			sum = T{0};
			index = 0;
			val = T{0};
			prevVal = T{0};
			length = pipeline->container.length();
			for (const T& i: pipeline->container) {
				prevVal = val;
				val = i;
				if (rsl::abs(val - prevVal) > MAX_DIFFERENCE)
					sum += prevVal;
				else
					sum += val;
				++index;
			}
			return sum / (DEFAULT_CAPACITY);
		}
	};
}

#endif //RSL_CONSTRAINEDAVERAGEFILTER_HPP
