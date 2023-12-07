//
// Created by robcholz on 11/2/23.
//
#pragma once

#ifndef RSL_IIRFILTER_HPP
#define RSL_IIRFILTER_HPP


namespace rsl{
	class IIRFilter{
		template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
		template<short ALPHA>
		CALC_T Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::Filter::IIR(const Pipeline* pipeline) {
			return (ALPHA / 100.f) * pipeline->value + (1.0 - (ALPHA / 100.f)) * pipeline->commPreValue;
		}
	};
}

#endif //RSL_IIRFILTER_HPP
