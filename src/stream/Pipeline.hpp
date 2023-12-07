//
// Created by robcholz on 10/31/23.
//
#pragma once

#ifndef RSL_PIPELINE_HPP
#define RSL_PIPELINE_HPP

#include <Internal.hpp>
#include <utils/Utils.hpp>
#include "container/base/StaticList.hpp"
#include "container/base/StaticArray.hpp"
#include "container/Deque.hpp"


namespace rsl {
	template<typename T, typename CALC_T=float, typename OUT_T=float, rsl::size_t DEFAULT_CAPACITY = 10,typename CONTAINER=Deque<T, DEFAULT_CAPACITY, StaticList<T, DEFAULT_CAPACITY>>>
	class Pipeline {
	public:
		class Filter;

		using FilterFunc = CALC_T (*)(const Pipeline* pipeline);
	public:
		RSL_UNUSED void add(const T& element);

		RSL_UNUSED void filter(FilterFunc filterFunc);

		RSL_UNUSED const OUT_T& output();

		RSL_UNUSED void empty();

		RSL_UNUSED void update();

		RSL_UNUSED void feedback(bool feedback);

		RSL_NODISCARD bool isEmpty() const;

		RSL_NODISCARD rsl::size_t length() const;

		RSL_NODISCARD rsl::size_t capacity() const;

	private:
		CONTAINER container;

		T value{0}, prevValue{0};
		T valueEst{0}, prevValueEst{0};
		T commPreValue{0};
		bool dataFeedback;

		FilterFunc filterFunction;
		friend Filter;

		void addAscending(const T& element);
	};

	template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
	void Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::add(const T& element) {
		prevValueEst = valueEst;
		prevValue = value;
		commPreValue = container.back();
		value = element;
	}

	template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
	void Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::filter(Pipeline::FilterFunc filterFunc) {
		filterFunction = filterFunc;
	}

	template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
	const OUT_T& Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::output() {
		return static_cast<OUT_T>(valueEst);
	}

	template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
	void Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::empty() {
		container.empty();
		value(0);
		prevValue = 0;
		valueEst(0);
		prevValueEst = 0;
	}

	template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
	void Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::update() {
		RSL_COMPILETIME_BOUND_CHECK(filterFunction != nullptr, "");
		if (container.length() == DEFAULT_CAPACITY)
			container.pop();
		valueEst = filterFunction(this);
		if (dataFeedback)
			addAscending(valueEst);
		else
			addAscending(value);
	}

	template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
	void Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::feedback(bool feedback) {
		dataFeedback = feedback;
	}

	template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
	bool Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::isEmpty() const {
		return container.isEmpty();
	}

	template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
	rsl::size_t Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::length() const {
		return container.length();
	}

	template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
	rsl::size_t Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::capacity() const {
		return container.capacity();
	}

	template<typename T, typename CALC_T, typename OUT_T, rsl::size_t DEFAULT_CAPACITY, typename CONTAINER>
	void Pipeline<T, CALC_T, OUT_T, DEFAULT_CAPACITY, CONTAINER>::addAscending(const T& element) {
		if (container.length() == 0) {
			container.add(element);
			return;
		}
		static rsl::size_t index;
		index = 0;
		auto it = container.begin();
		while (it != container.end() && element > *it)
			++it;
		container.insert(it, element);
	}
}

#endif //RSL_PIPELINE_HPP

