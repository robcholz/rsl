//
// Created by robcholz on 11/2/23.
//
#pragma once

#ifndef RSL_WEIGHTEDAVERAGEFILTER_HPP
#define RSL_WEIGHTEDAVERAGEFILTER_HPP


namespace rsl{
	template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
	CALC_T Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::Filter::weightedAverage(const Pipeline* pipeline) {
		static const StaticArray<float, DEFAULT_CAPACITY> weights{0.05, 0.06, 0.07, 0.08, 0.08, 0.9, 0.11, 0.12, 0.15, 0.19};
		return weightedAverage(pipeline, weights);
	}

	template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
	CALC_T Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::Filter::weightedAverage(const Pipeline* pipeline,
	                                                                                        const StaticArray<float, DEFAULT_CAPACITY>& weights) {
		static T sum;
		static rsl::size_t index;
		sum = T{0};
		index = 0;
		for (const T& i: pipeline->container) {
			sum += i * weights[index];
			++index;
		}
		return sum;
	}


}

#endif //RSL_WEIGHTEDAVERAGEFILTER_HPP
