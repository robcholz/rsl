//
// Created by robcholz on 11/2/23.
//
#pragma once

#ifndef RSL_KALMANFILTER_HPP
#define RSL_KALMANFILTER_HPP


namespace rsl{
	class KalmanFilter{
		template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
		CALC_T Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::Filter::kalmanFilter(const Pipeline* pipeline) {
			static float est_e = 2;
			return kalmanFilter(pipeline, 2, est_e, 0.01);
		}

		template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
		CALC_T Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::Filter::kalmanFilter(const Pipeline* pipeline, float mea_e, float& est_e, float q) {
			float kalman_gain = est_e / (est_e + mea_e);
			float current_estimate = pipeline->prevValueEst + kalman_gain * (pipeline->value - pipeline->prevValueEst);
			est_e = (1.0 - kalman_gain) * est_e + rsl::fabs(pipeline->prevValueEst - current_estimate) * q;
			return current_estimate;
		}
	};
}

#endif //RSL_KALMANFILTER_HPP
