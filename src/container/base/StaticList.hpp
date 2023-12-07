//
// Created by robcholz on 9/25/23.
//
#pragma once

#ifndef RSL_STATICLIST_HPP
#define RSL_STATICLIST_HPP

#include <Internal.hpp>
#include "List.hpp"


namespace rsl {
	/**
	 * @usage A stack-allocated, fixed-sized list
	 * @tparam T element type
	 * @tparam DEFAULT_CAPACITY list capacity
 	 */
	template<typename T, rsl::size_t DEFAULT_CAPACITY = 10>
	class RSL_UNUSED StaticList {
	private:
		using ReservedListNode = StaticListNode<T>;
		using ListNode = StaticDoublyListNode<T>;
	public:
		/**
		 * @usage construct a static list object
		 */
		StaticList();

		/**
		 * @usage construct with arguments
		 * @tparam Args type that matches T
		 * @param args parameter list
		 * @attention the length of the args should not be larger than the capacity
		 */
		template<typename... Args>
		explicit StaticList(const Args& ... args);

		/**
		 * @usage construct from another instance
		 * @param other another instance
		 * @attention if the length of the copied list is larger than the capacity of the list copied to, the list will be filled
		 */
		template<rsl::size_t CAPACITY_>
		explicit StaticList(const StaticList<T, CAPACITY_>& other);

		/**
		 * @usage copy constructor
		 * @param other instance
		 * @return new instance
		 * @attention if the length of the copied list is larger than the capacity of the list copied to, the list will be filled
		 */
		template<rsl::size_t CAPACITY_>
		StaticList& operator=(const StaticList<T, CAPACITY_>& other);

		/**
		 * @usage move constructor
		 * @param other instance
		 * @return new instance
		 * @attention if the length of the copied list is larger than the capacity of the list copied to, the list will be filled
		 */
		template<rsl::size_t CAPACITY_>
		StaticList& operator=(StaticList<T, CAPACITY_>&& other) noexcept;

		template<rsl::size_t CAPACITY_>
		StaticList& operator+=(const StaticList<T, CAPACITY_>& other);

		/**
		 * @usage compare the contents of two lists
		 * @param other instance
		 * @return ture if two lists are same in contents
		 */
		template<rsl::size_t CAPACITY_>
		bool operator==(const StaticList<T, CAPACITY_>& other) const;

		/**
		 * @usage compare the contents of two lists
		 * @param other instance
		 * @return true if that list instance has longer length
		 */
		template<rsl::size_t CAPACITY_>
		bool operator>(const StaticList<T, CAPACITY_>& other) const;

		/**
		 * @usage compare the contents of two lists
		 * @param other instance
		 * @return true if that list instance has shorter length
		 */
		template<rsl::size_t CAPACITY_>
		bool operator<(const StaticList<T, CAPACITY_>& other) const;

		/**
		 * @usage default destructor
		 */
		~StaticList() = default;

		RSL_UNUSED void addFront(const T& element);

		/**
		 * @usage addBack an element to the end of the list
		 * @param element
		 * @attention operation will be ignored if list is full
		 */
		RSL_UNUSED void addBack(const T& element);

		/**
		 * @usage append another list to the end of the list
		 * @param list
		 * @attention operation will be ignored if list is full
		 */
		template<rsl::size_t CAPACITY_>
		RSL_UNUSED void appendFront(const StaticList<T, CAPACITY_>& list);

		template<rsl::size_t CAPACITY_>
		RSL_UNUSED void appendBack(const StaticList<T, CAPACITY_>& list);

		/**
		 * @usage remove the element at the given index
		 * @param index
		 * @return the removed element
		 * @attention operation will be ignored if list is full
		 */
		RSL_UNUSED T& front() const;

		/**
		 * @usage remove the element at the given index
		 * @param index
		 * @return the removed element
		 * @attention operation will be ignored if list is full
		 */
		RSL_UNUSED T& back() const;

		RSL_UNUSED void popFront();

		RSL_UNUSED void popBack();

		/**
		 * @usage search and remove the element if it exists
		 * @param element element to be searched
		 * @return if it is removed successfully
		 */
		RSL_UNUSED bool searchRemove(const T& element);

		/**
		 * @usage searchRemove all elements occurred in the given list
		 * @param list
		 * @return if at least one element is removed
		 */
		template<rsl::size_t CAPACITY_>
		RSL_UNUSED bool removeAll(const StaticList<T, CAPACITY_>& list);

		/**
		 * @usage empty the entire list
		 */
		RSL_UNUSED void empty();

		/**
		 * @usage check if the list is empty
		 * @return true if empty
		 */
		RSL_NODISCARD bool isEmpty() const;

		/**
		 * @usage check if an element is contained in the list
		 * @param element
		 * @return true if the given element is contained
		 */
		RSL_UNUSED bool contains(const T& element) const;

		/**
		 * @usage get the length of the list
		 * @return the length of the list
		 */
		RSL_NODISCARD rsl::size_t length() const;

		/**
		 * @usage get the capacity, max elements the list can hold
		 * @return capacity
		 */
		RSL_NODISCARD rsl::size_t capacity() const;

		/**
		 * @usage print the list
		 */
		RSL_UNUSED void print() const;

	private:
		ListNode container[DEFAULT_CAPACITY + 3]; // reserve two nodes for head and reservedHead
		rsl::size_t head{};
		rsl::size_t tail{};
		rsl::size_t reservedHead{};
		rsl::size_t containerLength{}; // the current length of the list
		static inline T defaultValue{0};

		RSL_UNUSED void createReservedList();

		RSL_UNUSED void init();

		RSL_UNUSED rsl::size_t malloc();

		/**
 		 * @usage remove the element at the given pointer
		 * @param pointer
 		 * @return the removed data
 		 * @attention operation will be ignored if index is out of bound
 		 */
		RSL_UNUSED void remove(rsl::size_t before, rsl::size_t after);

		template<typename Arg, typename... Args>
		void addVariadic(const Arg& arg, const Args& ... args);

		void addVariadic();

	public:
		class RSL_UNUSED Iterator {
		private:
			ListNode* containerPtr;
			rsl::size_t current;

		public:
			using iterator_category RSL_UNUSED = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type RSL_UNUSED = std::ptrdiff_t;
			using pointer = T*;
			using reference = T&;

			RSL_UNUSED
			Iterator(ListNode* ptr, rsl::size_t current) : current(current), containerPtr(ptr) {}

			bool operator==(const Iterator& other) const {
				return current == other.current && containerPtr == other.containerPtr;
			}

			bool operator!=(const Iterator& other) const {
				return !(current == other.current && containerPtr == other.containerPtr);
			}

			reference operator*() const {
				return containerPtr[current].data;
			}

			pointer operator->() const {
				return &(containerPtr[current].data);
			}

			Iterator& operator++() {
				current = containerPtr[current].next;
				return *this;
			}

			Iterator operator++(int) {
				Iterator temp = *this;
				++(*this);
				return temp;
			}

			Iterator& operator--() {
				current = containerPtr[current].prev;
				return *this;
			}

			Iterator operator--(int) {
				Iterator temp = *this;
				--(*this);
				return temp;
			}
		};

		/**
		 * @usage iterator func
		 * @return begin
		 */
		Iterator begin() const;

		/**
		 * @usage iterator func
		 * @return end
		 */
		Iterator end() const;
	};

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	StaticList<T, CAPACITY>::StaticList() :
			containerLength(0) {
		init();
	}

	template<typename T, rsl::size_t CAPACITY>
	template<typename... Args>
	RSL_UNUSED
	StaticList<T, CAPACITY>::StaticList(const Args& ... args) :
			containerLength(0) {
		RSL_COMPILETIME_BOUND_CHECK(sizeof...(args) <= CAPACITY, "Too many arguments to addBack into the list.");
		init();
		(addVariadic((args)...));
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	StaticList<T, CAPACITY>::StaticList(const StaticList<T, CAPACITY_>& other) {
		RSL_RUNTIME_BOUND_CHECK(other.length() > CAPACITY, "Assignment incomplete! Capacity is too small.");
		init();
		for (const auto& element: other) {
			addBack(element);
		}
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	StaticList<T, CAPACITY>& StaticList<T, CAPACITY>::operator=(const StaticList<T, CAPACITY_>& other) {
		RSL_RUNTIME_BOUND_CHECK(other.length() > CAPACITY, "Assignment incomplete! Capacity is too small.");
		// guard self assignment
		if (this == &other)
			return *this;
		init();
		for (const auto& element: other) {
			addBack(element);
		}
		return *this;
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	StaticList<T, CAPACITY>& StaticList<T, CAPACITY>::operator=(StaticList<T, CAPACITY_>&& other) noexcept {
		RSL_RUNTIME_BOUND_CHECK_ARG((other.length() > CAPACITY), "Assignment incomplete! Capacity is too small.",);
		// guard self assignment
		if (this == &other)
			return *this;
		init();
		for (const auto& element: other) {
			addBack(element);
		}
		return *this;
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	StaticList<T, CAPACITY>& StaticList<T, CAPACITY>::operator+=(const StaticList<T, CAPACITY_>& other) {
		appendFront(other);
		return *this;
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	bool StaticList<T, CAPACITY>::operator==(const StaticList<T, CAPACITY_>& other) const {
		if (this->containerLength != other.length())
			return false;
		for (const auto& element_this: *this)
			for (const auto& element_other: other)
				if (element_this != element_other)
					return false;
		return true;
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	bool StaticList<T, CAPACITY>::operator>(const StaticList<T, CAPACITY_>& other) const {
		return (this->containerLength > other.length());
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	bool StaticList<T, CAPACITY>::operator<(const StaticList<T, CAPACITY_>& other) const {
		return (this->containerLength < other.length());
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticList<T, CAPACITY>::addFront(const T& element) {
		RSL_RUNTIME_BOUND_CHECK_ARG(containerLength >= CAPACITY, "Out of Capacity, addBack failed", return;);
		static rsl::size_t node_new;
		node_new = StaticList::malloc();
		container[node_new].data = element;

		container[node_new].next = container[head].next; // r next
		container[container[head].next].prev = node_new; // r prev

		container[head].next = node_new; // l next
		container[node_new].prev = head; // l prev
		++containerLength;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticList<T, CAPACITY>::addBack(const T& element) {
		RSL_RUNTIME_BOUND_CHECK_ARG(containerLength >= CAPACITY, "Out of Capacity, addBack failed", return;);
		static rsl::size_t node_new;
		node_new = StaticList::malloc();
		container[node_new].data = element;

		container[container[tail].prev].next = node_new;
		container[node_new].prev = container[tail].prev;

		container[tail].prev = node_new; // r
		container[node_new].next = tail; // l

		++containerLength;
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	void StaticList<T, CAPACITY>::appendFront(const StaticList<T, CAPACITY_>& list) {
		RSL_RUNTIME_BOUND_CHECK_ARG(containerLength + list.length() >= CAPACITY, "Out of Capacity, addBack failed", return;);
		for (const auto& element: list) {
			addFront(element);
		}
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	void StaticList<T, CAPACITY>::appendBack(const StaticList<T, CAPACITY_>& list) {
		RSL_RUNTIME_BOUND_CHECK_ARG(containerLength + list.length() >= CAPACITY, "Out of Capacity, addBack failed", return;);
		for (const auto& element: list) {
			addBack(element);
		}
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	T& StaticList<T, CAPACITY>::front() const {
		RSL_RUNTIME_BOUND_CHECK_ARG(container[head].next == 0, "head->next is nullptr", return defaultValue);
		return container[container[head].next].data;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	T& StaticList<T, CAPACITY>::back() const {
		return container[container[tail].prev].data;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticList<T, CAPACITY>::popFront() {
		StaticList::remove(head, container[container[head].next].next);
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticList<T, CAPACITY>::popBack() {
		StaticList::remove(container[container[tail].prev].prev, tail);
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	bool StaticList<T, CAPACITY>::searchRemove(const T& element) {
		static rsl::size_t before;
		before = container[head].next;
		while (before != 0 && container[before].next != 0) {
			if (container[container[before].next].data == element) {
				StaticList::remove(before, container[container[before].next].next);
				return true;
			}
			before = container[before].next;
		}
		return false;
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	bool StaticList<T, CAPACITY>::removeAll(const StaticList<T, CAPACITY_>& list) {
		static bool flag = false;
		for (const auto& element: list) {
			searchRemove(element);
			flag = true;
		}
		return flag;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticList<T, CAPACITY>::empty() {
		containerLength = 0;

		container[container[tail].prev].next = container[reservedHead].next;
		container[reservedHead].next = container[tail].prev;

		container[tail].prev = 0;
		container[head].next = 0;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_NODISCARD
	bool StaticList<T, CAPACITY>::isEmpty() const {
		return (containerLength == 0);
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_NODISCARD
	bool StaticList<T, CAPACITY>::contains(const T& element) const {
		for (const auto& element_: *this) {
			if (element_ == element)
				return true;
		}
		return false;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_NODISCARD
	rsl::size_t StaticList<T, CAPACITY>::length() const {
		return this->containerLength;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_NODISCARD
	rsl::size_t StaticList<T, CAPACITY>::capacity() const {
		return CAPACITY;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticList<T, CAPACITY>::print() const {
		static rsl::size_t i;
		i = 0;
		RSL_PRINT("StaticList[");
		for (const auto& element: *this) {
			RSL_PRINT(element);
			++i;
			if (i < containerLength) {
				RSL_PRINT(",");
			}
		}
		RSL_PRINT("]");
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	typename StaticList<T, CAPACITY>::Iterator StaticList<T, CAPACITY>::begin() const {
		return Iterator{(ListNode*) container, container[head].next};
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	typename StaticList<T, CAPACITY>::Iterator StaticList<T, CAPACITY>::end() const {
		return Iterator((ListNode*) container, tail);
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticList<T, CAPACITY>::createReservedList() {
		static rsl::size_t i;
		head = 0;
		tail = 1;
		reservedHead = 2;
		container[reservedHead].next = 3;
		for (i = 3; i < CAPACITY + 3; ++i) {
			container[i].next = i + 1;
		}
		container[CAPACITY + 2].next = 0;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticList<T, CAPACITY>::init() {
		createReservedList();
		container[head].next = tail;
		container[head].prev = 0;
		container[head].data = defaultValue;
		container[tail].next = 0;
		container[tail].prev = head;
		container[tail].data = defaultValue;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	rsl::size_t StaticList<T, CAPACITY>::malloc() {
		static rsl::size_t returned_node;
		returned_node = container[reservedHead].next;
		if (returned_node == 0)
			return 0;
		container[reservedHead].next = container[returned_node].next;
		container[returned_node].next = 0;
		container[returned_node].prev = 0;
		return returned_node;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticList<T, CAPACITY>::remove(rsl::size_t before, rsl::size_t after) {
		static rsl::size_t reservedNode;
		reservedNode = container[before].next;

		container[before].next = after;
		container[after].prev = before;

		container[reservedNode].prev = 0;

		container[reservedNode].next = container[reservedHead].next;
		container[reservedHead].next = reservedNode;
		--containerLength;
	}

	template<typename T, rsl::size_t CAPACITY>
	template<typename Arg, typename... Args>
	RSL_UNUSED
	void StaticList<T, CAPACITY>::addVariadic(const Arg& arg, const Args& ... args) {
		StaticList::addBack(arg);
		StaticList::addVariadic(args...);
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticList<T, CAPACITY>::addVariadic() {}
}


#endif //RSL_STATICLIST_HPP
