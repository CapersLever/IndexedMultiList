#include "IndexedMultiList.h"
#include <iostream>
using namespace std;

IndexedMultiList::IndexedMultiList() {
	usedSize = 0;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) { //array full of NULL values
		arr[i].letter = NULL;
		arr[i].number = NULL;
	}
}

bool IndexedMultiList::insert(int index, char val, int count) {
	if (index >= DEFAULT_MAX_ITEMS) { return false; }
	if (usedSize == DEFAULT_MAX_ITEMS) { return false; } //the list is full
	if (index > usedSize + 1) { return false; } //when index is more than the filled spots in the array
	if (index < 0) { return false; } //invalid index
	
	if (usedSize == 0 && index == 0) { //list is empty insert into first spot
		arr[0].letter = val;
		arr[0].number = count;
		usedSize++; //increases the amont of used spaces 
		return true; //this insert is done and should only run when lst is empty
	}	

	if (index == 0) { //inserting into the front of the list
		for (int i = DEFAULT_MAX_ITEMS - 1; i > 0; i--) { //shifts all forward one
			arr[i] = arr[i - 1];
		}
		arr[0].letter = val; //inserts into the first spot
		arr[0].number = count;
		usedSize++;
		return true;
	}

	if (index == usedSize) { //for inserting into the next spot but not the end of the array
		arr[usedSize].letter = val;
		arr[usedSize].number = count;
		usedSize++;
		return true;
	}
	//default or middle of list input
	int loop = DEFAULT_MAX_ITEMS - 1;
	for (loop; loop > index; loop--) { //stops one before the changed index
		arr[loop] = arr[loop - 1];
	}
	arr[loop].letter = val;
	arr[loop].number = count;
	usedSize++;
	return true;
}

void IndexedMultiList::print() const{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
		if (arr[i].letter != NULL) {
			cout << arr[i].number << " " << arr[i].letter << endl;
		}
	}
}

bool IndexedMultiList::empty() const {
	for (int i = 0; i < DEFAULT_MAX_ITEMS - 1; i++) {
		if (arr[i].letter != NULL) { //when arr[i] is empty
			return false;            // will return true
		}
	}
	return true; //assuming list will be empty more than full
}

int IndexedMultiList::uniqueSize() const {
	return usedSize; //keeping track of this var in remove and insert methods
}

int IndexedMultiList::size() const {
	int total = 0;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
		total = total + arr[i].number; //count of total number in all spots of arr
	}
	return total;
}

int IndexedMultiList::find(char val) const {
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
		if (arr[i].letter == val)
			return i; //return index found
	}
	return -1; //return -1 if nt found
}

int IndexedMultiList::countItem(char val) const {
	int count = 0;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
		if (arr[i].letter == val) //count times found in list
			count++;
	}
	return count;
}

int IndexedMultiList::totalItemCount(char val) const {
	int total = 0;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
		if (arr[i].letter == val) {
			total = total + arr[i].number; //simple loop count
		}
	}
	return total;
}

int IndexedMultiList::countPosition(int index) const {
	if (index > usedSize || index > DEFAULT_MAX_ITEMS - 1) { return arr[0].number; } //invalid index values return value out of first pos
	return arr[index].number; //eturn the number at index
}

bool IndexedMultiList::getAt(int index, char &out) const {
	if (arr[index].letter == NULL) { return false; } //checking valid
	else {
		out = arr[index].letter; //setting out
		return true;
	}
}

bool IndexedMultiList::update(char val, int amount) {
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
		if (arr[i].letter == val) {
			arr[i].number = arr[i].number + amount; //updating number
			return true;
		}
	}
	return false;
}

bool IndexedMultiList::change(int index, int amount) {
	if (index < 0 || index > usedSize || index >= DEFAULT_MAX_ITEMS) { return false; } //checking valididty
	arr[index].number = arr[index].number + amount; //changing index
	if (arr[index].number <= 0) { //checking if no more values exist after change
		removeIndex(index); //calling to shift arr
	}
	return true;
}

bool IndexedMultiList::remove(char val) {
	int index = find(val); //so only run once
	if (index != -1) { 
		arr[index].number = arr[index].number - 1; //
	}
	else
		return false; //find did not find val in list
	if (arr[index].number <= 0) {
		removeIndex(index); //calling if number is below 0
	}
	return true;
}

int IndexedMultiList::removeIndex(int index) {
	if (index >= DEFAULT_MAX_ITEMS) { return false; }
	if (arr[index].letter == NULL) { return -1; } //checking valid
	int removed = arr[index].number; //to keep how many items were removed
	if (index == DEFAULT_MAX_ITEMS - 1) {
		arr[DEFAULT_MAX_ITEMS - 1].letter = NULL;
		arr[DEFAULT_MAX_ITEMS -1].number = NULL;
		usedSize--;
		return removed;
	}
	for (int i = index; i < DEFAULT_MAX_ITEMS - 1; i++) {
		arr[i] = arr[i + 1];
	}
	arr[DEFAULT_MAX_ITEMS - 1].letter = NULL;
	arr[DEFAULT_MAX_ITEMS - 1].number = NULL;
	usedSize--;
	return removed;
}

int IndexedMultiList::removeAll(char val) {
	int index = find(val); //finding index to remove all from
	if (index != -1) //checking if found
		return removeIndex(index); //giving the index to removeIndex
	//will shift the arr and return amount of items removed
	else
		return 0; //no items removed, no items found
}
