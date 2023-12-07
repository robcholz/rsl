//
// Created by robcholz on 9/24/23.
//

#include <string>
#include <array>
#include "catch2/catch_test_macros.hpp"
#include "container/base/StaticArray.hpp"


TEST_CASE("Static Array Test", "[static_array]") {
	using String = std::string;

	rsl::StaticArray<int, 100> array_i100;
	rsl::StaticArray<double, 10> array_d10;
	rsl::StaticArray<String, 9> array_str9;

	SECTION("Capacity assertion") {
		CHECK(array_i100.capacity() == 100);
		CHECK(array_d10.capacity() == 10);
		CHECK(array_str9.capacity() == 9);
	}

	SECTION("Initial length assertion") {
		CHECK(array_i100.length() == 0);
		CHECK(array_d10.length() == 0);
		CHECK(array_str9.length() == 0);
	}

	SECTION("overloaded operators assertion") {
		array_i100.addBack(2);
		array_i100.addFront(1);
		array_d10.addBack(0.5);
		array_str9.addBack("123");

		rsl::StaticArray<int, 3> array_i100copy(array_i100);
		rsl::StaticArray<int, 2> array_i100copy1 = static_cast<rsl::StaticArray<int, 2>>(array_i100copy);

		CHECK(array_i100copy1[0] == 1);
		CHECK(array_i100copy1[1] == 2);

		CHECK(array_i100[0] == 1);
		CHECK(array_d10[0] == 0.5);
		CHECK(array_str9[0] == "123");

		rsl::StaticArray<int, 3> array_i{1, 2};
		rsl::StaticArray<double, 5> array_d;
		rsl::StaticArray<String, 3> array_str;

		int test[2] = {1, 2};
		int index = 0;
		for (const auto& element: array_i) {
			CHECK(element == test[index]);
			++index;
		}

		auto it=array_i100.end();
		std::cout << "Static Array Reverse traversal: ";
		while (it != array_i100.begin()) {
			std::cout << *it << " ";
			--it;
		}
		std::cout << *it << std::endl;

		bool i = (array_i100 == array_i);
		bool d = (array_d10 > array_d);
		bool str = (array_str9 < array_str);

		CHECK(i);
		CHECK(d);
		CHECK(!str);
	}

	SECTION("addBack() assertion") {
		array_i100.addBack(1);
		array_d10.addBack(0.5);
		array_str9.addBack("123");

		CHECK(array_i100.length() == 1);
		CHECK(array_d10.length() == 1);
		CHECK(array_str9.length() == 1);

		CHECK(array_i100[0] == 1);
		CHECK(array_d10[0] == 0.5);
		CHECK(array_str9[0] == "123");
	}

	SECTION("Append(const Array&) assertion") {
		rsl::StaticArray<int, 9> array;
		array.addBack(1);
		array.addBack(3);
		array_i100.empty();
		array_i100.addBack(1);
		array_i100.addBack(10000);
		array_i100.appendBack(array);

		CHECK(array_i100.length() == 4);
		CHECK(array_i100[0] == 1);
		CHECK(array_i100[1] == 10000);
		CHECK(array_i100[2] == 1);
		CHECK(array_i100[3] == 3);
	}

	SECTION("Append(rsl::size_t,const Array&) assertion") {
		rsl::StaticArray<int, 9> array;
		array.addBack(1);
		array.addBack(3);
		array_i100.empty();
		array_i100.addBack(2);
		array_i100.addBack(10000);
		array_i100.addBack(1415);
		array_i100.append(1, array);

		CHECK(array_i100.length() == 5);
		CHECK(array_i100[0] == 2);
		CHECK(array_i100[1] == 1);
		CHECK(array_i100[2] == 3);
		CHECK(array_i100[3] == 10000);
		CHECK(array_i100[4] == 1415);
	}

	SECTION("remove() assertion") {
		array_i100.empty();
		array_i100.addBack(2);
		array_i100.addBack(10000);
		array_i100.addBack(1415);
		array_i100.remove(1);

		CHECK(array_i100.length() == 2);
		CHECK(array_i100[0] == 2);
		CHECK(array_i100[1] == 1415);
	}

	SECTION("searchRemove() assertion") {
		array_i100.empty();
		array_i100.addBack(2);
		array_i100.addBack(10000);
		array_i100.addBack(1415);

		CHECK(array_i100.searchRemove(2));
		CHECK(array_i100.searchRemove(1415));
		CHECK(!array_i100.searchRemove(111122));

		CHECK(array_i100.length() == 1);
		CHECK(array_i100[0] == 10000);
	}

	SECTION("removeAll() assertion") {
		array_i100.empty();
		array_i100.addBack(4);
		array_i100.addBack(10000);
		array_i100.addBack(1415);
		array_i100.addBack(1234);
		array_i100.addBack(1314);

		rsl::StaticArray<int, 3> d;
		d.addBack(10000);
		d.addBack(1234);
		d.addBack(1415);
		array_i100.removeAll(d);

		CHECK(array_i100.length() == 2);
		CHECK(array_i100[0] == 4);
		CHECK(array_i100[1] == 1314);
	}

	SECTION("removeRange() assertion") {
		array_str9.empty();
		array_str9.addBack("4");
		array_str9.addBack("10000");
		array_str9.addBack("1415");
		array_str9.addBack("1234");
		array_str9.addBack("1314");

		array_str9.removeRange(1, 3);

		CHECK(array_str9.length() == 2);
		CHECK(array_str9[0] == "4");
		CHECK(array_str9[1] == "1314");
	}

	SECTION("empty() isEmpty() assertion") {
		array_str9.empty();

		CHECK(array_str9.isEmpty());
	}

	SECTION("contains() assertion") {
		array_str9.empty();
		array_str9.addBack("4");
		array_str9.addBack("10000");
		array_str9.addBack("1415");
		array_str9.addBack("1234");
		array_str9.addBack("1314");

		CHECK(array_str9.contains("1415"));
	}

	SECTION("length() capacity() assertion") {
		array_str9.empty();
		array_str9.addBack("4");
		array_str9.addBack("10000");
		array_str9.addBack("1415");
		array_str9.addBack("1234");
		array_str9.addBack("1314");

		CHECK(array_str9.length() == 5);
		CHECK(array_str9.capacity() == 9);
	}

	SECTION("get() assertion") {
		array_str9.empty();
		array_str9.addBack("4");
		array_str9.addBack("10000");
		array_str9.addBack("1415");
		array_str9.addBack("1234");
		array_str9.addBack("1314");

		CHECK(array_str9.get(2) == "1415");
	}

	SECTION("indexOf() lastIndexOf() assertion") {
		array_str9.empty();
		array_str9.addBack("4");
		array_str9.addBack("1234");
		array_str9.addBack("1415");
		array_str9.addBack("1234");
		array_str9.addBack("1314");

		CHECK(array_str9.indexOf("1234") == 1);
		CHECK(array_str9.lastIndexOf("1234") == 3);
	}

	SECTION("print() assertion") {
		array_str9.empty();
		array_str9.addBack("4");
		array_str9.addBack("1234");
		array_str9.addBack("1415");
		array_str9.addBack("1234");
		array_str9.addBack("1314");

		array_str9.print();
	}
}
