//
// Created by robcholz on 9/25/23.
//

#include <string>
#include <array>
#include "catch2/catch_test_macros.hpp"
#include "container/base/DynamicList.hpp"


TEST_CASE("Dynamic List Test", "[dynamic_list]") {
	using String = std::string;

	rsl::DynamicList<int, 5> list_i5;
	rsl::DynamicList<double, 10> list_d10;
	rsl::DynamicList<String, 9> list_str9;

	SECTION("Capacity assertion") {
		CHECK(list_i5.capacity() == 5);
		CHECK(list_d10.capacity() == 10);
		CHECK(list_str9.capacity() == 9);
	}

	SECTION("Initial length assertion") {
		CHECK(list_i5.length() == 0);
		CHECK(list_d10.length() == 0);
		CHECK(list_str9.length() == 0);
	}

	SECTION("overloaded operators assertion") {
		/*
		list_i100.add(1);
		list_i100.add(2);
		list_d10.add(0.5);
		list_str9.add("123");

		rsl::StaticArray<int, 3> array_i100copy(list_i100);
		rsl::StaticArray<int, 2> array_i100copy1 = static_cast<rsl::StaticArray<int, 2>>(array_i100copy);

		rsl::StaticArray<int, 3> array_i{1, 2};
		rsl::StaticArray<double, 5> array_d;
		rsl::StaticArray<String, 3> array_str;

		int test[2] = {1, 2};
		int index = 0;
		for (const auto& element: array_i) {
			CHECK(element == test[index]);
			++index;
		}

		bool i = (list_i100 == array_i);
		bool d = (list_d10 > array_d);
		bool str = (list_str9 < array_str);

		CHECK(i);
		CHECK(d);
		CHECK(!str);
		 */
	}

	SECTION("addBack() assertion") {
		//list_i5 = rsl::StaticList<int, 5>{1, 2, 3, 4, 5};
		list_i5.addBack(1);
		list_i5.addBack(2);
		list_i5.addBack(3);
		list_i5.addBack(4);
		list_i5.addBack(5);

		list_d10.addBack(0.5);
		list_str9.addBack("123");

		CHECK(list_i5.length() == 5);
		CHECK(list_d10.length() == 1);
		CHECK(list_str9.length() == 1);


		list_i5.addBack(1);

		list_i5.print();
		list_i5.searchRemove(3);
		list_i5.popFront();
		list_i5.print();
		list_i5.popBack();
		list_i5.popBack();
		list_i5.popFront();
		list_i5.print();

		list_i5 = rsl::DynamicList<int, 5>{1, 2, 3, 4, 5};

		auto it = list_i5.end();
		--it;
		std::cout << "Dynamic Reverse traversal: ";
		while (it != list_i5.begin()) {
			std::cout << *it << " ";
			--it;
		}
		std::cout << *it << std::endl;
	}
}