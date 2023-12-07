//
// Created by robcholz on 9/25/23.
//
#pragma once

#ifndef RSL_LIST_HPP
#define RSL_LIST_HPP


#include <Internal.hpp>

namespace rsl{
	template<typename T>
	struct ListNode{
		T data;
		ListNode* next;
	};

	template<typename T>
	struct DoublyListNode{
		T data;
		DoublyListNode* prev;
		DoublyListNode* next;
	};

	template<typename T>
	struct StaticListNode{
		T data;
		rsl::size_t next;
	};

	template<typename T>
	struct StaticDoublyListNode{
		T data;
		rsl::size_t prev;
		rsl::size_t next;
	};
}

#endif //RSL_LIST_HPP
