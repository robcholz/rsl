//
// Created by robcholz on 11/2/23.
//
#pragma once

#ifndef RSL_CONSTRAINEDJITTERFILTER_HPP
#define RSL_CONSTRAINEDJITTERFILTER_HPP


namespace rsl{
	class ConstrainedJitterFilter{
		template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
		CALC_T Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::Filter::constrainedJitter(const Pipeline* pipeline) {
			return CALC_T{0};
		}

	};
}

#endif //RSL_CONSTRAINEDJITTERFILTER_HPP
