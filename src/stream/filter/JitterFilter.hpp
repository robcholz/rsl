//
// Created by robcholz on 11/2/23.
//
#pragma once

#ifndef RSL_JITTERFILTER_HPP
#define RSL_JITTERFILTER_HPP


namespace rsl{
	class JitterFilter{
		template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
		CALC_T Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::Filter::jitterFilter(const Pipeline* pipeline) {
			// oReminder
		}

	};
}

#endif //RSL_JITTERFILTER_HPP
