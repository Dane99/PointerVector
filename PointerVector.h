#pragma once
#include <iostream>
#include <vector>


template <class T>
struct PointerAndID
{
	PointerAndID(T* pointer, int itemID) { this->pointer = pointer; this->itemID = itemID; };

	T* pointer;
	int itemID;
};


// Class template for C++ standard library (std::vector). This class adds functionality for deleting and assigning identification to heap memory pointers.
// Note offset is the number for addressing it in an array. E.g. array[5]. ID is the PointerAndID defined id.
template <class T>
class PointerVector
{
public:
	PointerVector() { }

	~PointerVector() {
		for (int i = 0; i < getSize(); i++) {
			eraseWithOffset(i);
		}
	}

	// Returns the pointer corresponding with the offset.
	T* getPointerWithOffset(int offset) const {
		return pointerWrapper.at(offset).pointer;
	}

	// Returns the pointer corresponding with the item id.
	T* getPointerWithID(int itemID) const {
		int offset = findOffset(itemID);
		return pointerWrapper.at(offset).pointer;
	}

	// Returns the last pointer that was added.
	T* getLastPointer() const {
		int offset = this->getSize() - 1;
		return pointerWrapper.at(offset).pointer;
	}

	// Adds an pointer to the end of the pointer vector. Returns the id for the item.
	int push_back(T* item) {
		pointerWrapper.emplace_back(item, currentId);
		return currentId++;
	}

	void pop() {
		int offset = this->getSize() - 1;
		eraseWithOffset(offset);
	}

	// Removes a pointer if it has a matching item id. Also deletes the resources that it is holding.
	void eraseWithID(int itemID) {
		int offset = findOffset(itemID);
		deleteMemoryAndPointer(offset);
	}

	void eraseWithOffset(int offset) {
		deleteMemoryAndPointer(offset);
	}

	// Returns the size/length of the pointerVector.
	int getSize() const {
		return pointerWrapper.size();
	}

private:
	// Finds the offset at which the item id exists.
	int findOffset(int itemID) const {
		for (int i = 0; i < pointerWrapper.size(); i++) {
			if (pointerWrapper.at(i).itemID == itemID) {
				return i;
			}
		}
		std::cout << "ERROR. findOffset not found." << std::endl;
		return -1;
	}

	// Deletes both the pointer and the memory that the pointer holds.
	void deleteMemoryAndPointer(int offset) {
		delete pointerWrapper.at(offset).pointer;
		pointerWrapper.erase(pointerWrapper.begin() + offset);
	}

	int currentId = 0;
	std::vector<PointerAndID<T>> pointerWrapper;
};