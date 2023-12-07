//
// Created by robcholz on 9/25/23.
//
#pragma once

#ifndef RSL_DYNAMICLIST_HPP
#define RSL_DYNAMICLIST_HPP

#include <memory/ObjectAllocator.hpp>
#include <Internal.hpp>
#include "List.hpp"


namespace rsl {
	/**
	 * @usage A heap-allocated list
	 * @tparam T element type
	 * @tparam DEFAULT_CAPACITY this param has no effect
 	 */
	template<typename T, rsl::size_t DEFAULT_CAPACITY = 10, typename ALLOCATOR=ObjectAllocator<DoublyListNode<T>>>
	class RSL_UNUSED DynamicList {
	private:
		using ListNode = DoublyListNode<T>;
	public:
		/**
		 * @usage construct a static list object
		 */
		DynamicList();

		/**
		 * @usage construct with arguments
		 * @tparam Args type that matches T
		 * @param args parameter list
		 * @attention the length of the args should not be larger than the capacity
		 */
		template<typename... Args>
		explicit DynamicList(const Args& ... args);

		/**
		 * @usage construct from another instance
		 * @param other another instance
		 * @attention if the length of the copied list is larger than the capacity of the list copied to, the list will be filled
		 */
		template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
		explicit DynamicList(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& other);

		/**
 		 * @usage default destructor
         */
		~DynamicList();

		/**
		 * @usage copy constructor
		 * @param other instance
		 * @return new instance
		 * @attention if the length of the copied list is larger than the capacity of the list copied to, the list will be filled
		 */
		template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
		DynamicList& operator=(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& other);

		/**
		 * @usage move constructor
		 * @param other instance
		 * @return new instance
		 * @attention if the length of the copied list is larger than the capacity of the list copied to, the list will be filled
		 */
		template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
		DynamicList& operator=(DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>&& other) noexcept;

		template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
		DynamicList& operator+=(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& other);

		/**
		 * @usage compare the contents of two lists
		 * @param other instance
		 * @return ture if two lists are same in contents
		 */
		template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
		bool operator==(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& other) const;

		/**
		 * @usage compare the contents of two lists
		 * @param other instance
		 * @return true if that list instance has longer length
		 */
		template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
		bool operator>(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& other) const;

		/**
		 * @usage compare the contents of two lists
		 * @param other instance
		 * @return true if that list instance has shorter length
		 */
		template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
		bool operator<(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& other) const;

		RSL_UNUSED void addFront(const T& element);

		/**
		 * @usage addBack an element to the end of the list
		 * @param element
		 * @attention operation will be ignored if list is full
		 */
		RSL_UNUSED void addBack(const T& element);

		template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
		RSL_UNUSED void appendFront(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& list);

		/**
		 * @usage append another list to the end of the list
		 * @param list
		 * @attention operation will be ignored if list is full
		 */
		template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
		RSL_UNUSED void appendBack(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& list);

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
		template<rsl::size_t DEFAULT_CAPACITY_>
		RSL_UNUSED bool removeAll(const DynamicList<T, DEFAULT_CAPACITY_>& list);

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
		ListNode* head;
		ListNode* tail;
		rsl::size_t size{}; // the current length of the list
		ALLOCATOR allocator;
		inline static T defaultValue{0};

		class RSL_UNUSED Iterator {
		private:
			ListNode* current;

		public:
			using iterator_category RSL_UNUSED = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type RSL_UNUSED = std::ptrdiff_t;
			using pointer = T*;
			using reference = T&;

			RSL_UNUSED
			explicit Iterator(ListNode* current) : current(current) {}

			bool operator==(const Iterator& other) {
				return current == other.current;
			}

			bool operator!=(const Iterator& other) const {
				return current != other.current;
			}

			reference operator*() const {
				return current->data;
			}

			pointer operator->() const {
				return &(current->data);
			}

			Iterator& operator++() {
				current = current->next;
				return *this;
			}

			Iterator& operator++(int) {
				static Iterator temp;
				temp = *this;
				++(*this);
				return temp;
			}

			Iterator& operator--() {
				current = current->prev;
				return *this;
			}

			Iterator& operator--(int) {
				static Iterator temp;
				temp = *this;
				--(*this);
				return temp;
			}
		};

		RSL_UNUSED void init();

		/**
 		 * @usage remove the element at the given pointer
		 * @param pointer
 		 * @return the removed data
 		 * @attention operation will be ignored if index is out of bound
 		 */
		RSL_UNUSED void remove(ListNode* before, ListNode* after);

		template<typename Arg, typename... Args>
		RSL_UNUSED void addVariadic(const Arg& arg, const Args& ... args);

		void addVariadic();

	public:
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

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::DynamicList() :
			size(0),
			head(nullptr),
			tail(nullptr) {
		init();
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<typename... Args>
	DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::DynamicList(const Args& ... args) :
			size(0),
			head(nullptr),
			tail(nullptr) {
		init();
		(addVariadic((args)...));
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
	DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::DynamicList(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& other) {
		init();
		for (const auto& element: other) {
			addBack(element);
		}
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::~DynamicList() {
		static ListNode* node, * node_reserved;
		node = tail;
		while (node->prev != nullptr) {
			node_reserved = node->prev;
			allocator.free(node);
			node = node_reserved;
		}
		allocator.free(head);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
	DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>&
	DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::operator=(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& other) {
		// guard self assignment
		if (this == &other)
			return *this;
		init();
		for (const auto& element: other) {
			addBack(element);
		}
		return *this;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
	DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>&
	DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::operator=(DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>&& other) noexcept {
		// guard self assignment
		if (this == &other)
			return *this;
		init();
		for (const auto& element: other) {
			addBack(element);
		}
		return *this;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
	RSL_UNUSED
	DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>&
	DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::operator+=(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& other) {
		appendBack(other);
		return *this;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
	RSL_UNUSED
	bool DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::operator==(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& other) const {
		if (this->size != other.length())
			return false;
		for (const auto& element_this: *this)
			for (const auto& element_other: other)
				if (element_this != element_other)
					return false;
		return true;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
	RSL_UNUSED
	bool DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::operator>(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& other) const {
		return (this->size > other.length());
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
	RSL_UNUSED
	bool DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::operator<(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& other) const {
		return (this->size < other.length());
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::addFront(const T& element) {
		static ListNode* node_new;
		node_new = allocator.malloc();
		RSL_RUNTIME_BOUND_CHECK_ARG(node_new == nullptr, "Allocation failed, current objects: " + RSL_TO_STR_NUM(allocator.length())
		                                                 + " max objects: " + RSL_TO_STR_NUM(allocator.maxObjects()), return;);
		node_new->data = element;

		node_new->next = head->next; // r next
		head->next->prev = node_new; // r prev
		head->next = node_new; // l next
		node_new->prev = head; // l prev

		++size;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::addBack(const T& element) {
		static ListNode* node_new;
		node_new = allocator.malloc();
		RSL_RUNTIME_BOUND_CHECK_ARG(node_new == nullptr, "Allocation failed, current objects: " + RSL_TO_STR_NUM(allocator.size())
		                                                 + " max objects: " + RSL_TO_STR_NUM(allocator.maxObjects()), return;);
		node_new->data = element;

		tail->prev->next = node_new;
		node_new->prev = tail->prev;
		tail->prev = node_new; // r
		node_new->next = tail; // l

		++size;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
	RSL_UNUSED
	void DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::appendFront(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& list) {
		for (const auto& element: list) {
			addFront(element);
		}
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t DEFAULT_CAPACITY_, typename ALLOCATOR_>
	RSL_UNUSED
	void DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::appendBack(const DynamicList<T, DEFAULT_CAPACITY_, ALLOCATOR_>& list) {
		for (const auto& element: list) {
			addBack(element);
		}
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	T& DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::front() const {
		RSL_RUNTIME_BOUND_CHECK_ARG(head->next == nullptr, "head->next is nullptr", return defaultValue;);
		return head->next->data;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	T& DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::back() const {
		RSL_RUNTIME_BOUND_CHECK_ARG(tail->prev == nullptr, "head->next is nullptr", return defaultValue);
		return tail->prev->data;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::popFront() {
		DynamicList::remove(head, head->next->next);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::popBack() {
		DynamicList::remove(tail->prev->prev, tail);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	bool DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::searchRemove(const T& element) {
		static ListNode* before;
		before = head->next;
		while (before != nullptr && before->next != nullptr) {
			if (before->next->data == element) {
				DynamicList::remove(before, before->next->next);
				return true;
			}
			before = before->next;
		}
		return false;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t DEFAULT_CAPACITY_>
	RSL_UNUSED
	bool DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::removeAll(const DynamicList<T, DEFAULT_CAPACITY_>& list) {
		static bool flag = false;
		for (const auto& element: list) {
			searchRemove(element);
			flag = true;
		}
		return flag;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::empty() {
		static ListNode* reservedNode, * node;
		reservedNode = tail->prev;
		while (reservedNode == nullptr) {
			node = reservedNode->prev;
			allocator.free(reservedNode);
			reservedNode = node;
		}
		head->next = tail;
		tail->prev = head;
		size = 0;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_NODISCARD
	bool DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::isEmpty() const {
		return (size == 0);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_NODISCARD
	bool DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::contains(const T& element) const {
		for (const auto& element_: *this) {
			if (element_ == element)
				return true;
		}
		return false;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_NODISCARD
	rsl::size_t DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::length() const {
		return this->size;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_NODISCARD
	rsl::size_t DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::capacity() const {
		return DEFAULT_CAPACITY;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::print() const {
		static rsl::size_t i;
		i = 0;
		RSL_PRINT("DynamicList[");
		for (const auto& element: *this) {
			RSL_PRINT(element);
			++i;
			if (i < size) {
				RSL_PRINT(",");
			}
		}
		RSL_PRINT("]");
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	typename DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::Iterator DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::begin() const {
		return Iterator(head->next);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	typename DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::Iterator DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::end() const {
		return Iterator(tail);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::init() {
		head = allocator.malloc();
		tail = allocator.malloc();
		head->data = defaultValue;
		tail->data = defaultValue;
		head->next = tail;
		tail->next = nullptr;
		head->prev = nullptr;
		tail->prev = head;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::remove(ListNode* before, ListNode* after) {
		allocator.free(before->next);
		before->next = after;
		after->prev = before;
		--size;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<typename Arg, typename... Args>
	RSL_UNUSED
	void DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::addVariadic(const Arg& arg, const Args& ... args) {
		DynamicList::addBack(arg);
		DynamicList::addVariadic(args...);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicList<T, DEFAULT_CAPACITY, ALLOCATOR>::addVariadic() {}
}


#endif //RSL_DYNAMICLIST_HPP
