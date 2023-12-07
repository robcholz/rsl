//
// Created by robcholz on 11/2/23.
//
#pragma once

#ifndef RSL_CONSTRAINFILTER_HPP
#define RSL_CONSTRAINFILTER_HPP


namespace rsl{
	class ConstrainFilter{
		template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
		template<const T MAX_DIFFERENCE>
		CALC_T Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::Filter::constrainDiff(const Pipeline* pipeline) {
			if (rsl::abs(pipeline->value - pipeline->commPreValue) > MAX_DIFFERENCE)
				return pipeline->commPreValue;
			return pipeline->value;
		}
	};
}

#endif //RSL_CONSTRAINFILTER_HPP
