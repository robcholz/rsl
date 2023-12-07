//
// Created by robcholz on 11/2/23.
//
#pragma once

#ifndef RSL_AVERAGEFILTER_HPP
#define RSL_AVERAGEFILTER_HPP


namespace rsl {
	template<typename T, typename CALC_T=float>
	class AverageFilter {
	public:
		AverageFilter() = default;


		CALC_T filter(const T& data) {
			sum = T{0};
			for (const T& i: pipeline->container)
				sum += i;
			return sum / (DEFAULT_CAPACITY);
		}

	private:
		T sum;
	};
}

#endif //RSL_AVERAGEFILTER_HPP
