//
// Created by robcholz on 9/22/23.
//
#pragma once

#ifndef RSL_STATICARRAY_HPP
#define RSL_STATICARRAY_HPP

#include <Internal.hpp>


namespace rsl {
	/**
	 * @usage A stack-allocated, fixed-size array
	 * @tparam T element type
	 * @tparam DEFAULT_CAPACITY array capacity
	  */
	template<typename T, rsl::size_t DEFAULT_CAPACITY = 10>
	class RSL_UNUSED StaticArray {
	public:
		/**
		 * @usage construct a static array object
		 */
		constexpr StaticArray();

		/**
		 * @usage construct with arguments
		 * @tparam Args type that matches T
		 * @param args parameter list
		 * @attention the length of the args should not be larger than the capacity
		 */
		template<typename... Args>
		constexpr explicit StaticArray(const Args& ... args);

		/**
		 * @usage construct from another instance
		 * @param other another instance
		 * @attention if the length of the copied array is larger than the capacity of the array copied to, the array will be filled
		 */
		template<rsl::size_t CAPACITY_>
		explicit StaticArray(const StaticArray<T, CAPACITY_>& other);

		/**
		 * @usage copy constructor
		 * @param other instance
		 * @return new instance
		 * @attention if the length of the copied array is larger than the capacity of the array copied to, the array will be filled
		 */
		template<rsl::size_t CAPACITY_>
		StaticArray& operator=(const StaticArray<T, CAPACITY_>& other);

		/**
		 * @usage move constructor
		 * @param other instance
		 * @return new instance
		 * @attention if the length of the copied array is larger than the capacity of the array copied to, the array will be filled
		 */
		template<rsl::size_t CAPACITY_>
		StaticArray& operator=(StaticArray<T, CAPACITY_>&& other) noexcept;

		/**
		 * @usage compare the contents of two arrays
		 * @param other instance
		 * @return ture if two arrays are same in contents
		 */
		template<rsl::size_t CAPACITY_>
		bool operator==(const StaticArray<T, CAPACITY_>& other) const;

		/**
		 * @usage compare the contents of two arrays
		 * @param other instance
		 * @return true if that array instance has longer length
		 */
		template<rsl::size_t CAPACITY_>
		bool operator>(const StaticArray<T, CAPACITY_>& other) const;

		/**
		 * @usage compare the contents of two arrays
		 * @param other instance
		 * @return true if that array instance has shorter length
		 */
		template<rsl::size_t CAPACITY_>
		bool operator<(const StaticArray<T, CAPACITY_>& other) const;

		/**
		 * @usage get the reference of the element at the given index. this is equivalent to get(size_t index)
		 * @param other instance
		 * @return the reference of the element at the given index, default value if out of bound
		 */
		T& operator[](rsl::size_t index);

		/**
		 * @usage get the element at the given index. this is equivalent to get(size_t index)
		 * @param other instance
		 * @return the element at the given index, default value if out of bound
		 */
		constexpr const T& operator[](rsl::size_t index) const;

		/**
		 * @usage default destructor
		 */
		~StaticArray() = default;

		RSL_UNUSED void addFront(const T& element);

		/**
		 * @usage addBack an element to the end of the array
		 * @param element
		 * @attention operation will be ignored if array is full
		 */
		RSL_UNUSED void addBack(const T& element);

		/**
		 * @usage addBack the element at the given index of the array
		 * @param index
		 * @param element
		 * @attention operation will be ignored if array is full
		 */
		RSL_UNUSED void add(rsl::size_t index, const T& element);

		/**
		  * @usage append another array to the end of the array
		  * @param array
		  * @attention operation will be ignored if array is full
		  */
		template<rsl::size_t CAPACITY_>
		RSL_UNUSED void appendFront(const StaticArray<T, CAPACITY_>& array);

		/**
		 * @usage append another array to the end of the array
		 * @param array
		 * @attention operation will be ignored if array is full
		 */
		template<rsl::size_t CAPACITY_>
		RSL_UNUSED void appendBack(const StaticArray<T, CAPACITY_>& array);

		/**
		 * @usage append another array at the given index of the array
		 * @param index
		 * @param array
		 * @attention operation will be ignored if array is full
		 */
		template<rsl::size_t CAPACITY_>
		RSL_UNUSED void append(rsl::size_t index, const StaticArray<T, CAPACITY_>& array);

		RSL_UNUSED T& front() const;

		RSL_UNUSED T& back() const;

		RSL_UNUSED void popFront();

		RSL_UNUSED void popBack();

		/**
		 * @usage remove the element at the given index
		 * @param index
		 * @return the removed element
		 * @attention operation will be ignored if array is full
		 */
		RSL_UNUSED T remove(rsl::size_t index);

		/**
		 * @usage search and remove the element if it exists
		 * @param element element to be searched
		 * @return if it is removed successfully
		 */
		RSL_UNUSED bool searchRemove(const T& element);

		/**
		 * @usage remove all elements occurred in the given array
		 * @param array
		 * @return if at least one element is removed
		 */
		template<rsl::size_t CAPACITY_>
		RSL_UNUSED bool removeAll(const StaticArray<T, CAPACITY_>& array);

		/**
		 * @usage remove a range of elements by given indexes, \b inclusive
		 * @param fromIndex the start of the index
		 * @param toIndex the end of the index
		 * @attention operation will be ignored if indexes out of bounds
		 */
		RSL_UNUSED void removeRange(rsl::size_t fromIndex, rsl::size_t toIndex);

		/**
		 * @usage empty the entire array
		 */
		RSL_UNUSED void empty();

		/**
		 * @usage check if the array is empty
		 * @return true if empty
		 */
		RSL_NODISCARD bool isEmpty() const;

		/**
		 * @usage check if an element is contained in the array
		 * @param element
		 * @return true if the given element is contained
		 */
		RSL_UNUSED bool contains(const T& element) const;

		/**
		 * @usage get the length of the array
		 * @return the length of the array
		 */
		RSL_NODISCARD rsl::size_t length() const;

		/**
		 * @usage get the capacity, max elements the array can hold
		 * @return capacity
		 */
		RSL_NODISCARD constexpr rsl::size_t capacity() const;

		/**
		 * @usage get the reference of the element at the given index. this is equivalent to operator[]
		 * @param index
		 * @return the reference of the element, the default value of T if index out of bound
		 */
		RSL_UNUSED T& get(rsl::size_t index);

		/**
		 * @usage get the element at the given index. this is equivalent to operator[]
		 * @param index
		 * @return the element, the default value of T if index out of bound
		 */
		RSL_UNUSED T get(rsl::size_t index) const;

		/**
		 * @usage search the first occurrence of the given element and return the index of it
		 * @param element
		 * @return -1 if not found, otherwise the index of the element
		 */
		RSL_UNUSED rsl::signed_size_t indexOf(const T& element) const;

		/**
		 * @usage search the last occurrence of the given element and return the index of it
		 * @param element
		 * @return -1 if not found, otherwise the index of the element
		 */
		RSL_UNUSED rsl::signed_size_t lastIndexOf(const T& element) const;

		/**
		 * @usage get the row pointer pointed to the internal stack-allocated array, you cannot edit the contents of the returned pointer
		 * @return the const pointer
		 */
		RSL_UNUSED const T* getRowArray() const;

		/**
		 * @usage print the array
		 */
		RSL_UNUSED void print() const;

	private:
		T container[DEFAULT_CAPACITY]; // row array
		rsl::size_t containerLength{}; // the current length of the array
		inline static T defaultValue{0};

		class RSL_UNUSED Iterator {
		private:
			T* containerPtr;

		public:
			using iterator_category RSL_UNUSED = std::random_access_iterator_tag;
			using value_type = T;
			using difference_type RSL_UNUSED = std::ptrdiff_t;
			using pointer = T*;
			using reference = T&;

			RSL_UNUSED
			explicit Iterator(pointer ptr) : containerPtr(ptr) {}

			bool operator==(const Iterator& other) const {
				return containerPtr == other.containerPtr;
			}

			bool operator!=(const Iterator& other) const {
				return containerPtr != other.containerPtr;
			}

			reference operator*() const {
				return *containerPtr;
			}

			pointer operator->() const {
				return containerPtr;
			}

			Iterator& operator++() {
				++containerPtr;
				return *this;
			}

			Iterator& operator++(int) {
				static Iterator temp;
				temp = *this;
				++(*this);
				return temp;
			}

			Iterator& operator--() {
				--containerPtr;
				return *this;
			}

			Iterator& operator--(int) {
				static Iterator temp;
				temp = *this;
				--(*this);
				return temp;
			}
		};

		template<typename Arg, typename... Args>
		constexpr void addVariadic(const Arg& arg, const Args& ... args);

		constexpr void addVariadic();

	public:
		/**
		 * @usage iterator func
		 * @return begin
		 */
		Iterator begin();

		/**
		 * @usage iterator func
		 * @return end
		 */
		Iterator end();
	};

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	constexpr StaticArray<T, CAPACITY>::StaticArray() : containerLength(0) {
	}

	template<typename T, rsl::size_t CAPACITY>
	template<typename... Args>
	RSL_UNUSED
	constexpr StaticArray<T, CAPACITY>::StaticArray(const Args& ... args) : containerLength(0) {
		RSL_COMPILETIME_BOUND_CHECK(sizeof...(args) <= CAPACITY, "Too many arguments to addBack into the array.");
		(addVariadic((args)...));
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	StaticArray<T, CAPACITY>::StaticArray(const StaticArray<T, CAPACITY_>& other) {
		static rsl::size_t otherLength = other.length();
		static const T* otherContainer = other.getRowArray();
		containerLength = otherLength;
		RSL_RUNTIME_BOUND_CHECK_ARG(otherLength > CAPACITY, "Assignment failed! Capacity is too small.",
		                            containerLength = CAPACITY;);
		static rsl::size_t i;
		for (i = 0; i < containerLength; ++i) {
			this->container[i] = otherContainer[i];
		}
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	StaticArray<T, CAPACITY>& StaticArray<T, CAPACITY>::operator=(const StaticArray<T, CAPACITY_>& other) {
		// guard self assignment
		if (this == &other)
			return *this;
		static rsl::size_t otherLength = other.length();
		static const T* otherContainer = other.getRowArray();
		containerLength = otherLength;
		RSL_RUNTIME_BOUND_CHECK_ARG(otherLength > CAPACITY, "Assignment failed! Capacity is too small.",
		                            containerLength = CAPACITY;);
		static rsl::size_t i;
		for (i = 0; i < containerLength; ++i) {
			this->container[i] = otherContainer[i];
		}
		return *this;
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	StaticArray<T, CAPACITY>& StaticArray<T, CAPACITY>::operator=(StaticArray<T, CAPACITY_>&& other) noexcept {
		// guard self assignment
		if (this == &other)
			return *this;
		static rsl::size_t otherLength = other.length();
		static const T* otherContainer = other.getRowArray();
		containerLength = otherLength;
		RSL_RUNTIME_BOUND_CHECK_ARG(otherLength > CAPACITY, "Assignment failed! Capacity is too small.",
		                            containerLength = CAPACITY;);
		static rsl::size_t i;
		for (i = 0; i < containerLength; ++i) {
			this->container[i] = otherContainer[i];
		}
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	bool StaticArray<T, CAPACITY>::operator==(const StaticArray<T, CAPACITY_>& other) const {
		static const T* otherContainer = other.getRowArray();
		if (containerLength != other.length())
			return false;
		static rsl::size_t i;
		for (i = 0; i < containerLength; ++i) {
			if (this->container[i] != otherContainer[i])
				return false;
		}
		return true;
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	bool StaticArray<T, CAPACITY>::operator>(const StaticArray<T, CAPACITY_>& other) const {
		return (containerLength > other.length());
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	bool StaticArray<T, CAPACITY>::operator<(const StaticArray<T, CAPACITY_>& other) const {
		return (containerLength < other.length());
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	T& StaticArray<T, CAPACITY>::operator[](rsl::size_t index) {
		RSL_RUNTIME_BOUND_CHECK_ARG(index >= containerLength, "Index out of bound", return defaultValue);
		return container[index];
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	constexpr const T& StaticArray<T, CAPACITY>::operator[](rsl::size_t index) const {
		RSL_RUNTIME_BOUND_CHECK_ARG(index >= containerLength, "Index out of bound", return defaultValue);
		return container[index];
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticArray<T, CAPACITY>::addFront(const T& element) {
		add(0, element);
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticArray<T, CAPACITY>::addBack(const T& element) {
		RSL_RUNTIME_BOUND_CHECK_ARG(containerLength >= CAPACITY, "Out of Capacity, addBack failed", return;);
		container[containerLength] = element;
		++containerLength;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticArray<T, CAPACITY>::add(rsl::size_t index, const T& element) {
		RSL_RUNTIME_BOUND_CHECK_ARG(containerLength >= CAPACITY || CAPACITY <= index, "Out of Capacity, addBack failed",
		                            return;);
		static rsl::size_t i;
		for (i = containerLength; i > index; --i) {
			container[i] = container[i - 1];
		}
		container[index] = element;
		++containerLength;
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	void StaticArray<T, CAPACITY>::appendFront(const StaticArray<T, CAPACITY_>& array) {
		append(0, array);
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	void StaticArray<T, CAPACITY>::appendBack(const StaticArray<T, CAPACITY_>& array) {
		static rsl::size_t arraySize = array.length();
		static const T* arrayContainer = array.getRowArray();
		RSL_RUNTIME_BOUND_CHECK_ARG(containerLength + arraySize >= CAPACITY, "Out of Capacity, addBack failed",
		                            return;);
		static rsl::size_t i;
		for (i = 0; i < arraySize; ++i) {
			container[containerLength + i] = arrayContainer[i];
		}
		containerLength += arraySize;
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	void StaticArray<T, CAPACITY>::append(rsl::size_t index, const StaticArray<T, CAPACITY_>& array) {
		static rsl::size_t arraySize = array.length();
		static const T* arrayContainer = array.getRowArray();
		RSL_RUNTIME_BOUND_CHECK_ARG(containerLength + arraySize >= CAPACITY || CAPACITY <= index,
		                            "Out of Capacity, addBack failed", return;);
		static rsl::size_t i;
		for (i = index; i < containerLength; ++i) {
			container[i + containerLength - 1] = container[i];
		} // move the elements
		for (i = 0; i < arraySize; ++i) {
			container[index + i] = arrayContainer[i];
		} // add the elements
		containerLength += arraySize;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	T& StaticArray<T, CAPACITY>::front() const {
		return container[0];
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	T& StaticArray<T, CAPACITY>::back() const {
		return container[containerLength - 1];
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticArray<T, CAPACITY>::popFront() {
		StaticArray::remove(0);
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticArray<T, CAPACITY>::popBack() {
		StaticArray::remove(containerLength - 1);
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	T StaticArray<T, CAPACITY>::remove(rsl::size_t index) {
		RSL_RUNTIME_BOUND_CHECK_ARG(index >= containerLength, "Out of Capacity, addBack failed", return defaultValue;);
		static T temp = container[index];
		static rsl::size_t i;
		for (i = index; i < containerLength - 1; ++i) {
			container[i] = container[i + 1];
		}
		--containerLength;
		return temp;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	bool StaticArray<T, CAPACITY>::searchRemove(const T& element) {
		static rsl::signed_size_t index;
		index = indexOf(element);
		if (index == -1)
			return false;
		for (; index < containerLength - 1; ++index) {
			container[index] = container[index + 1];
		}
		--containerLength;
		return true;
	}

	template<typename T, rsl::size_t CAPACITY>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	bool StaticArray<T, CAPACITY>::removeAll(const StaticArray<T, CAPACITY_>& array) {
		static bool flag = false;
		static rsl::size_t arraySize = array.length();
		static const T* arrayContainer = array.getRowArray();
		static rsl::size_t i, k;
		for (i = 0; i < arraySize; ++i) {
			for (k = 0; k < containerLength; ++k) {
				if (arrayContainer[i] == this->container[k]) {
					this->remove(k);
					flag = true;
				}
			}
		}
		return flag;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticArray<T, CAPACITY>::removeRange(rsl::size_t fromIndex, rsl::size_t toIndex) {
		RSL_RUNTIME_BOUND_CHECK_ARG(fromIndex >= containerLength || toIndex >= containerLength || fromIndex > toIndex,
		                            "Arguments out of bounds", return;);
		static rsl::size_t i;
		for (i = toIndex + 1; i < containerLength; ++i) {
			container[fromIndex + i - toIndex - 1] = container[i];
		}
		containerLength -= (toIndex - fromIndex + 1);
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticArray<T, CAPACITY>::empty() {
		containerLength = 0;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_NODISCARD
	bool StaticArray<T, CAPACITY>::isEmpty() const {
		return (containerLength == 0);
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	bool StaticArray<T, CAPACITY>::contains(const T& element) const {
		static rsl::size_t i;
		for (i = 0; i < containerLength; ++i) {
			if (container[i] == element)
				return true;
		}
		return false;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_NODISCARD
	rsl::size_t StaticArray<T, CAPACITY>::length() const {
		return containerLength;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_NODISCARD
	constexpr rsl::size_t StaticArray<T, CAPACITY>::capacity() const {
		return CAPACITY;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	T& StaticArray<T, CAPACITY>::get(rsl::size_t index) {
		RSL_RUNTIME_BOUND_CHECK_ARG(index >= containerLength, "Out of bound", return defaultValue;);
		return container[index];
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	T StaticArray<T, CAPACITY>::get(rsl::size_t index) const {
		RSL_RUNTIME_BOUND_CHECK_ARG(index >= containerLength, "Out of bound", return defaultValue;);
		return container[index];
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	rsl::signed_size_t StaticArray<T, CAPACITY>::indexOf(const T& element) const {
		static rsl::signed_size_t i;
		for (i = 0; i < containerLength; ++i) {
			if (container[i] == element)
				return i;
		}
		return -1;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	rsl::signed_size_t StaticArray<T, CAPACITY>::lastIndexOf(const T& element) const {
		static rsl::signed_size_t i;
		for (i = containerLength - 1; i >= 0; --i) {
			if (container[i] == element)
				return i;
		}
		return -1;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	const T* StaticArray<T, CAPACITY>::getRowArray() const {
		return container;
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	void StaticArray<T, CAPACITY>::print() const {
		static rsl::size_t i;
		RSL_PRINT("Array[");
		for (i = 0; i < containerLength; ++i) {
			RSL_PRINT(container[i]);
			if (i < containerLength - 1) {
				RSL_PRINT(",");
			}
		}
		RSL_PRINT("]");
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	typename StaticArray<T, CAPACITY>::Iterator StaticArray<T, CAPACITY>::begin() {
		return Iterator{container};
	}

	template<typename T, rsl::size_t CAPACITY>
	RSL_UNUSED
	typename StaticArray<T, CAPACITY>::Iterator StaticArray<T, CAPACITY>::end() {
		return Iterator{container};
	}

	template<typename T, rsl::size_t CAPACITY>
	template<typename Arg, typename... Args>
	constexpr void StaticArray<T, CAPACITY>::addVariadic(const Arg& arg, const Args& ... args) {
		container[containerLength] = arg;
		++containerLength;
		addVariadic(args...);
	}

	template<typename T, rsl::size_t CAPACITY>
	constexpr void StaticArray<T, CAPACITY>::addVariadic() {}
}


#endif //RSL_STATICARRAY_HPP
