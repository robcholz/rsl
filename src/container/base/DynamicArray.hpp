//
// Created by robcholz on 9/25/23.
//
#pragma once

#ifndef RSL_DYNAMICARRAY_HPP
#define RSL_DYNAMICARRAY_HPP

#include <Internal.hpp>
#include <memory/ByteAllocator.hpp>


namespace rsl {
	/**
	 * @usage A heap-allocated, dynamic-size array
	 * @tparam T element type
	 * @tparam DEFAULT_CAPACITY default array capacity
 	 */
	template<typename T, rsl::size_t DEFAULT_CAPACITY = 10, typename ALLOCATOR=ByteAllocator<T>>
	class RSL_UNUSED DynamicArray {
	public:
		/**
		 * @usage construct a static array object
		 */
		DynamicArray();

		/**
		 * @usage construct with arguments
		 * @tparam Args type that matches T
		 * @param args parameter list
		 * @attention the length of the args should not be larger than the capacity
		 */
		template<typename... Args>
		explicit DynamicArray(const Args& ... args);

		/**
		 * @usage construct from another instance
		 * @param other another instance
		 * @attention if the length of the copied array is larger than the capacity of the array copied to, the array will be filled
		 */
		template<rsl::size_t CAPACITY_>
		explicit DynamicArray(const DynamicArray<T, CAPACITY_>& other);

		/**
		 * @usage copy constructor
		 * @param other instance
		 * @return new instance
		 * @attention if the length of the copied array is larger than the capacity of the array copied to, the array will be filled
		 */
		template<rsl::size_t CAPACITY_>
		DynamicArray& operator=(const DynamicArray<T, CAPACITY_>& other);

		/**
		 * @usage move constructor
		 * @param other instance
		 * @return new instance
		 * @attention if the length of the copied array is larger than the capacity of the array copied to, the array will be filled
		 */
		template<rsl::size_t CAPACITY_>
		DynamicArray& operator=(DynamicArray<T, CAPACITY_>&& other) noexcept;

		/**
		 * @usage compare the contents of two arrays
		 * @param other instance
		 * @return ture if two arrays are same in contents
		 */
		template<rsl::size_t CAPACITY_>
		bool operator==(const DynamicArray<T, CAPACITY_>& other) const;

		/**
		 * @usage compare the contents of two arrays
		 * @param other instance
		 * @return true if that array instance has longer length
		 */
		template<rsl::size_t CAPACITY_>
		bool operator>(const DynamicArray<T, CAPACITY_>& other) const;

		/**
		 * @usage compare the contents of two arrays
		 * @param other instance
		 * @return true if that array instance has shorter length
		 */
		template<rsl::size_t CAPACITY_>
		bool operator<(const DynamicArray<T, CAPACITY_>& other) const;

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
		T operator[](rsl::size_t index) const;

		/**
		 * @usage default destructor
		 */
		~DynamicArray();

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
		RSL_UNUSED void appendFront(const DynamicArray<T, CAPACITY_>& array);

		/**
		 * @usage append another array to the end of the array
		 * @param array
		 * @attention operation will be ignored if array is full
		 */
		template<rsl::size_t CAPACITY_>
		RSL_UNUSED void appendBack(const DynamicArray<T, CAPACITY_>& array);

		/**
		 * @usage append another array at the given index of the array
		 * @param index
		 * @param array
		 * @attention operation will be ignored if array is full
		 */
		template<rsl::size_t CAPACITY_>
		RSL_UNUSED void append(rsl::size_t index, const DynamicArray<T, CAPACITY_>& array);

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
		RSL_UNUSED bool removeAll(const DynamicArray<T, CAPACITY_>& array);

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

		RSL_UNUSED void trimToSize();

		RSL_UNUSED void capacity(rsl::size_t capacity);

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
		RSL_NODISCARD rsl::size_t capacity() const;

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
		T* container{nullptr}; // row array
		rsl::size_t containerLength{0}; // the current length of the array
		rsl::size_t containerCapacity{0};
		inline static T defaultValue{0};
		ALLOCATOR allocator;

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
		void addVariadic(const Arg& arg, const Args& ... args);

		void addVariadic();

		void ensureCapacity(rsl::size_t minCapacity);

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

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::DynamicArray() : containerLength(0) {
		capacity(DEFAULT_CAPACITY);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<typename... Args>
	RSL_UNUSED
	DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::DynamicArray(const Args& ... args) : containerLength(0) {
		capacity(sizeof...(args));
		(addVariadic((args)...));
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::DynamicArray(const DynamicArray<T, CAPACITY_>& other) {
		static rsl::size_t otherLength;
		static const T* otherContainer;
		static rsl::size_t i;

		otherLength = other.length();
		otherContainer = other.getRowArray();
		capacity(other.capacity());
		this->containerLength = otherLength;
		for (i = 0; i < containerLength; ++i) {
			this->container[i] = otherContainer[i];
		}
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>& DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::operator=(const DynamicArray<T, CAPACITY_>& other) {
		// guard self assignment
		if (this == &other)
			return *this;

		static rsl::size_t otherLength;
		static const T* otherContainer;
		static rsl::size_t i;

		otherLength = other.length();
		otherContainer = other.getRowArray();
		capacity(other.capacity());
		this->containerLength = otherLength;
		for (i = 0; i < containerLength; ++i) {
			this->container[i] = otherContainer[i];
		}
		return *this;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>& DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::operator=(DynamicArray<T, CAPACITY_>&& other) noexcept {
		// guard self assignment
		if (this == &other)
			return *this;

		static rsl::size_t otherLength;
		static const T* otherContainer;
		static rsl::size_t i;

		otherLength = other.length();
		otherContainer = other.getRowArray();
		capacity(other.capacity());
		this->containerLength = otherLength;
		for (i = 0; i < containerLength; ++i) {
			this->container[i] = otherContainer[i];
		}
		return *this;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	bool DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::operator==(const DynamicArray<T, CAPACITY_>& other) const {
		static const T* otherContainer;
		static rsl::size_t i;

		otherContainer = other.getRowArray();
		if (this->containerLength != other.length())
			return false;
		for (i = 0; i < this->containerLength; ++i) {
			if (this->container[i] != otherContainer[i])
				return false;
		}
		return true;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	bool DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::operator>(const DynamicArray<T, CAPACITY_>& other) const {
		return (this->containerLength > other.length());
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	bool DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::operator<(const DynamicArray<T, CAPACITY_>& other) const {
		return (this->containerLength < other.length());
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	T& DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::operator[](rsl::size_t index) {
		return get(index);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	T DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::operator[](rsl::size_t index) const {
		return get(index);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::~DynamicArray() {
		allocator.free(container);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::addFront(const T& element) {
		add(0, element);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::addBack(const T& element) {
		ensureCapacity(containerCapacity + 1);
		container[containerLength] = element;
		++containerLength;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::add(rsl::size_t index, const T& element) {
		ensureCapacity(containerCapacity + 1);
		static rsl::size_t i;
		for (i = containerLength; i > index; --i) {
			container[i] = container[i - 1];
		}
		container[index] = element;
		++containerLength;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::appendFront(const DynamicArray<T, CAPACITY_>& array) {
		append(0, array);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::appendBack(const DynamicArray<T, CAPACITY_>& array) {
		static rsl::size_t arrayLength = array.length();
		static const T* arrayContainer = array.getRowArray();
		static rsl::size_t i;
		ensureCapacity(containerCapacity + arrayLength);
		for (i = 0; i < arrayLength; ++i) {
			container[containerLength + i] = arrayContainer[i];
		}
		containerLength += arrayLength;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::append(rsl::size_t index, const DynamicArray<T, CAPACITY_>& array) {
		static rsl::size_t arrayLength = array.length();
		static const T* arrayContainer = array.getRowArray();
		static rsl::size_t i;
		ensureCapacity(containerCapacity + arrayLength);
		for (i = index; i < containerLength; ++i) {
			container[i + containerLength - 1] = container[i];
		} // move the elements
		for (i = 0; i < arrayLength; ++i) {
			container[index + i] = arrayContainer[i];
		} // add the elements
		containerLength += arrayLength;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	T& DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::front() const {
		return container[0];
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	T& DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::back() const {
		RSL_RUNTIME_BOUND_CHECK_ARG(containerLength == 0, "Array length is 0", return container[0];);
		return container[containerLength - 1];
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::popFront() {
		DynamicArray::remove(0);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::popBack() {
		DynamicArray::remove(containerLength - 1);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	T DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::remove(rsl::size_t index) {
		RSL_RUNTIME_BOUND_CHECK_ARG(index >= containerLength, "Out of capacity, remove failed", return defaultValue;);
		static T temp = container[index];
		static rsl::size_t i;
		for (i = index; i < containerLength - 1; ++i) {
			container[i] = container[i + 1];
		}
		--containerLength;
		return temp;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	bool DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::searchRemove(const T& element) {
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

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<rsl::size_t CAPACITY_>
	RSL_UNUSED
	bool DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::removeAll(const DynamicArray<T, CAPACITY_>& array) {
		static bool flag = false;
		static rsl::size_t arrayLength = array.length();
		static const T* arrayContainer = array.getRowArray();
		static rsl::size_t i, k;
		for (i = 0; i < arrayLength; ++i) {
			for (k = 0; k < this->containerLength; ++k) {
				if (arrayContainer[i] == this->container[k]) {
					this->remove(k);
					flag = true;
				}
			}
		}
		return flag;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::removeRange(rsl::size_t fromIndex, rsl::size_t toIndex) {
		RSL_RUNTIME_BOUND_CHECK_ARG(fromIndex >= containerLength || toIndex >= containerLength || fromIndex > toIndex, "Arguments out of bounds", return;);
		static rsl::size_t i;
		for (i = toIndex + 1; i < containerLength; ++i) {
			container[fromIndex + i - toIndex - 1] = container[i];
		}
		containerLength -= (toIndex - fromIndex + 1);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::empty() {
		containerLength = 0;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::trimToSize() {
		if (containerCapacity > containerLength) {
			static T* newContainer;
			newContainer = allocator.malloc(sizeof(T[containerLength]));
			static rsl::size_t i;
			for (i = 0; i < containerLength; ++i) {
				newContainer[i] = container[i];
			}
			containerCapacity = containerLength;
			allocator.free(container);
			container = newContainer;
		}
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::capacity(rsl::size_t capacity) {
		if (capacity > containerCapacity) {
			static T* newContainer;
			newContainer = allocator.malloc(sizeof(T[capacity]));
			static rsl::size_t i;
			if (containerLength != 0)
				for (i = 0; i < containerLength; ++i) {
					newContainer[i] = container[i];
				}
			containerCapacity = capacity;
			allocator.free(container);
			container = newContainer;
		}
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_NODISCARD
	bool DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::isEmpty() const {
		return (containerLength == 0);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	bool DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::contains(const T& element) const {
		static rsl::size_t i;
		for (i = 0; i < containerLength; ++i) {
			if (container[i] == element)
				return true;
		}
		return false;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_NODISCARD
	rsl::size_t DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::length() const {
		return this->containerLength;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_NODISCARD
	rsl::size_t DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::capacity() const {
		return containerCapacity;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	T& DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::get(rsl::size_t index) {
		RSL_RUNTIME_BOUND_CHECK_ARG(index >= containerLength, "Index out of bound", return defaultValue;);
		return container[index];
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	T DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::get(rsl::size_t index) const {
		RSL_RUNTIME_BOUND_CHECK_ARG(index >= containerLength, "Index out of bound", return defaultValue;);
		return container[index];
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	rsl::signed_size_t DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::indexOf(const T& element) const {
		static rsl::signed_size_t i;
		for (i = 0; i < containerLength; ++i) {
			if (container[i] == element)
				return i;
		}
		return -1;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	rsl::signed_size_t DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::lastIndexOf(const T& element) const {
		static rsl::signed_size_t i;
		for (i = containerLength - 1; i >= 0; --i) {
			if (container[i] == element)
				return i;
		}
		return -1;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	const T* DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::getRowArray() const {
		return container;
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::print() const {
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

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	typename DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::Iterator DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::begin() {
		return Iterator{container};
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	RSL_UNUSED
	typename DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::Iterator DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::end() {
		return Iterator{container};
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	template<typename Arg, typename... Args>
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::addVariadic(const Arg& arg, const Args& ... args) {
		container[containerLength] = arg;
		++containerLength;
		addBack(args...);
	}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::addVariadic() {}

	template<typename T, rsl::size_t DEFAULT_CAPACITY, typename ALLOCATOR>
	void DynamicArray<T, DEFAULT_CAPACITY, ALLOCATOR>::ensureCapacity(rsl::size_t minCapacity) {
		if (minCapacity > containerCapacity) {
			capacity((containerCapacity * 3) / 2 + 1);
		}
	}
}


#endif // RSL_DYNAMICARRAY_HPP
