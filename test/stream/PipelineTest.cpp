//
// Created by robcholz on 11/2/23.
//

#include <string>
#include "catch2/catch_test_macros.hpp"
#include "stream/Pipeline.hpp"


TEST_CASE("Pipeline Test", "[pipeline]") {
	using String = std::string;
	using MyPipeline = rsl::Pipeline<int, float>;
	MyPipeline constrained_diff;
	MyPipeline median;
	MyPipeline average;
	MyPipeline medianAvg;
	MyPipeline constrainedAvg;
	MyPipeline IIR;
	MyPipeline weightedAvg;
	MyPipeline jitter;
	MyPipeline constrained_jitter;
	MyPipeline kalman;

	SECTION("Init") {
		constexpr rsl::StaticArray<int, 3> arr1{1, 2, 3};
		constrained_diff.filter(MyPipeline::Filter::constrainDiff<2>);
		median.filter(MyPipeline::Filter::median);
		average.filter(MyPipeline::Filter::average);
		medianAvg.filter(MyPipeline::Filter::medianAverage);
		constrainedAvg.filter(MyPipeline::Filter::constrainedAverage<2>);
		IIR.filter(MyPipeline::Filter::IIR<50>);
		weightedAvg.filter(MyPipeline::Filter::weightedAverage);
		jitter.filter(MyPipeline::Filter::jitterFilter);
		constrained_jitter.filter(MyPipeline::Filter::constrainedJitter);
		kalman.filter(MyPipeline::Filter::kalmanFilter);
	}

	SECTION("Initial length assertion") {

	}
}