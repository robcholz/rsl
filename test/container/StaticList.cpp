//
// Created by robcholz on 9/25/23.
//

#include <string>
#include <list>
#include "catch2/catch_test_macros.hpp"
#include "container/base/StaticList.hpp"


TEST_CASE("Static List Test", "[static_list]") {
	using String = std::string;

	rsl::StaticList<int, 5> list_i5;
	rsl::StaticList<double, 10> list_d10;
	rsl::StaticList<String, 9> list_str9;

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

		list_i5 = rsl::StaticList<int, 5>{1, 2, 3, 4, 5};

		for(const auto& i:list_i5){

		}

		auto it=list_i5.end();
		--it;
		std::cout << "Static Reverse traversal: ";
		while (it != list_i5.begin()) {
			std::cout << *it << " ";
			--it;
		}
		std::cout << *it << std::endl;
	}

	/*
	SECTION("Append(const Array&) assertion") {
		rsl::StaticArray<int, 9> array;
		array.add(1);
		array.add(3);
		list_i100.empty();
		list_i100.add(1);
		list_i100.add(10000);
		list_i100.append(array);

		CHECK(list_i100.length() == 4);
		CHECK(list_i100[0] == 1);
		CHECK(list_i100[1] == 10000);
		CHECK(list_i100[2] == 1);
		CHECK(list_i100[3] == 3);
	}

	SECTION("Append(rsl::size_t,const Array&) assertion") {
		rsl::StaticArray<int, 9> array;
		array.add(1);
		array.add(3);
		list_i100.empty();
		list_i100.add(2);
		list_i100.add(10000);
		list_i100.add(1415);
		list_i100.append(1, array);

		CHECK(list_i100.length() == 5);
		CHECK(list_i100[0] == 2);
		CHECK(list_i100[1] == 1);
		CHECK(list_i100[2] == 3);
		CHECK(list_i100[3] == 10000);
		CHECK(list_i100[4] == 1415);
	}

	SECTION("remove() assertion") {
		list_i100.empty();
		list_i100.add(2);
		list_i100.add(10000);
		list_i100.add(1415);
		list_i100.remove(1);

		CHECK(list_i100.length() == 2);
		CHECK(list_i100[0] == 2);
		CHECK(list_i100[1] == 1415);
	}

	SECTION("searchRemove() assertion") {
		list_i100.empty();
		list_i100.add(2);
		list_i100.add(10000);
		list_i100.add(1415);

		CHECK(list_i100.searchRemove(2));
		CHECK(list_i100.searchRemove(1415));
		CHECK(!list_i100.searchRemove(111122));

		CHECK(list_i100.length() == 1);
		CHECK(list_i100[0] == 10000);
	}

	SECTION("removeAll() assertion") {
		list_i100.empty();
		list_i100.add(4);
		list_i100.add(10000);
		list_i100.add(1415);
		list_i100.add(1234);
		list_i100.add(1314);

		rsl::StaticArray<int, 3> d;
		d.add(10000);
		d.add(1234);
		d.add(1415);
		list_i100.removeAll(d);

		CHECK(list_i100.length() == 2);
		CHECK(list_i100[0] == 4);
		CHECK(list_i100[1] == 1314);
	}

	SECTION("removeRange() assertion") {
		list_str9.empty();
		list_str9.add("4");
		list_str9.add("10000");
		list_str9.add("1415");
		list_str9.add("1234");
		list_str9.add("1314");

		list_str9.removeRange(1, 3);

		CHECK(list_str9.length() == 2);
		CHECK(list_str9[0] == "4");
		CHECK(list_str9[1] == "1314");
	}

	SECTION("empty() isEmpty() assertion") {
		list_str9.empty();

		CHECK(list_str9.isEmpty());
	}

	SECTION("contains() assertion") {
		list_str9.empty();
		list_str9.add("4");
		list_str9.add("10000");
		list_str9.add("1415");
		list_str9.add("1234");
		list_str9.add("1314");

		CHECK(list_str9.contains("1415"));
	}

	SECTION("length() capacity() assertion") {
		list_str9.empty();
		list_str9.add("4");
		list_str9.add("10000");
		list_str9.add("1415");
		list_str9.add("1234");
		list_str9.add("1314");

		CHECK(list_str9.length() == 5);
		CHECK(list_str9.capacity() == 9);
	}

	SECTION("get() assertion") {
		list_str9.empty();
		list_str9.add("4");
		list_str9.add("10000");
		list_str9.add("1415");
		list_str9.add("1234");
		list_str9.add("1314");

		CHECK(list_str9.get(2) == "1415");
	}

	SECTION("indexOf() lastIndexOf() assertion") {
		list_str9.empty();
		list_str9.add("4");
		list_str9.add("1234");
		list_str9.add("1415");
		list_str9.add("1234");
		list_str9.add("1314");

		CHECK(list_str9.indexOf("1234") == 1);
		CHECK(list_str9.lastIndexOf("1234") == 3);
	}

	SECTION("print() assertion") {
		list_str9.empty();
		list_str9.add("4");
		list_str9.add("1234");
		list_str9.add("1415");
		list_str9.add("1234");
		list_str9.add("1314");

		list_str9.print();
	}
	 */
}