/*
Capers Lever
Indexed Multi List
Creation Date: 9/16/2014
Last Modified: 4/9/2016
CSCI 315 Data Structures
Grade Received: 85
Comments: Developed using Visual Studio. Copy and paste into new Visual Studio project and run.
*/
#include <iostream>
#include "IndexedMultiList.h"
using namespace std;

IndexedMultiList::IndexedMultiList() {
	head = NULL;
	usedSize = 0;
}

bool IndexedMultiList::insert(int index, char val, int count) {
	if (index < 0) { return false; }
	if (head == NULL) { //first time inserting into list
		head = new Node(val, count);
		usedSize++;
		return true;
	}
	if (index == 0) {
		Node *cur = new Node(val, count, head); //making new head with next pointer to head
		head = cur; //setting new head
		usedSize++;
		return true;
	}
	if (index == usedSize) { //inserts into the end when usedSize is 2,
		Node *cur = head;    //then the index 2 would be the last spot
		while (cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = new Node(val, count);
		usedSize++;
		return true;
	}
	if (index > 0){ //normal case. middle of list insert
		Node *cur = head;
		int counter = 1;
		while (counter != index) {
			cur = cur->next;
			counter++;
		} //cur next will be index to insert into 
		Node *pt2me = cur->next;
		cur->next = new Node(val, count, pt2me);
		usedSize++;
		return true;
	}
	return false;
}

void IndexedMultiList::print() const {
	Node *cur = head;
	while (cur != NULL) {
		cout << cur->data << " " << cur->number << endl;
		cur = cur->next;
	}
}

int IndexedMultiList::removeIndex(int index) {
	if (index < 0 || index > usedSize - 1) { return -1; } //checking valid indicies
	int removed = 0;
	if (index == 0) { //special case to remove the head
		removed = head->data;
		Node *cur = head;
		head = head->next; //new head
		delete cur;
		usedSize--;
		return removed;
	}
	Node *cur = head;
	int counter = 0;
	while (counter != index - 1) { //one before the index to remove
		cur = cur->next;
		counter++;
	}
	removed = cur->next->number; //return value; cur next is being deleted
	Node *kill = cur->next;      //kill now cur->next
	cur->next = kill->next;      //setting pointers up 
	delete kill;
	usedSize--;
	return removed;
}

bool IndexedMultiList::remove(char val) {
	Node *cur = head;
	int index = 0;
	while (cur->data != val) {
		cur = cur->next;
		index++; //keeping track of the index cur is at for removal
	}
	if (cur == NULL) { return false; }
	cur->number--;
	if (cur->number < 1) {
		removeIndex(index); //using that index to remove
	}
	return true;
}

int IndexedMultiList::removeAll(char val) {
	int removed = 0;
	if (head->data == val) {
		removed = head->number;
		removeIndex(0);
		return removed;
	}
	int index = 0;
	Node *cur = head;
	while (cur != NULL && cur->data != val) {
		cur = cur->next;
		index++;
	}
	removed = cur->number;
	removeIndex(index);
	return removed;
}

int IndexedMultiList::uniqueSize() const {
	return usedSize;
}

bool IndexedMultiList::change(int index, int amount) {
	if (index < 0 || index > usedSize - 1) { return false; } //checking valid indicies
	Node *cur = head;
	int count = 0; //for passing removeIndex the index of cur w/o looping again
	while (count != index) {
		cur = cur->next;
		count++;         
	}
	cur->number += amount; 
	if (cur->number <= 0) { //if no more vals left remove with index
		removeIndex(index);
	}
	return true;
}

bool IndexedMultiList::update(char val, int amount) {
	int index = find(val);               //saving to only call find once
	if (index == -1) { return false; }   //checking if val was found in list
	Node *cur = head;
	for (int i = 0; i < index; i++) {    //saving value of index for later so ussing i so not to corrupt index
		cur = cur->next;
	}
	cur->number += amount;               //adding amount to val
	if (cur->number <= 0) {              //removing if no more of val left
		removeIndex(index);
		return true;
	}
	return true;
}

int IndexedMultiList::find(char val) const {
	Node *cur = head;
	int index = 0;
	while (cur != NULL && cur->data != val) {
		cur = cur->next;
		index++;
	}
	if (cur == NULL) { return -1; } //checking what argument broke the loop
	return index;
}

int IndexedMultiList::countPosition(int index) const {
	if (index < 0 || index > usedSize - 1) { return -1; } //valid indicies check
	Node *cur = head;
	while (index != 0) { //going to count down from index while moving cur up list
		cur = cur->next;
		index--;
	}
	int count = cur->number;
	return count;
}

int IndexedMultiList::totalItemCount(char val) const {
	Node *cur = head;
	int count = 0;
	while (cur != NULL) {
		if (cur->data == val) {
			count += cur->number;
		}
		cur = cur->next;
	}
	return count;
}

int IndexedMultiList::countItem(char val) const {
	Node *cur = head;
	int count = 0;
	while (cur != NULL) {
		if (cur->data == val) {
			count++;
		}
		cur = cur->next;
	}
	return count;
}

int IndexedMultiList::size() const {
	Node *cur = head;
	int size = 0;
	while (cur != NULL) {
		size += cur->number;
		cur = cur->next;
	}
	return size;
}

bool IndexedMultiList::getAt(int index, char &out) const {
	if (index < 0 || index > usedSize - 1) { return false; }
	Node *cur = head;
	while (cur != NULL && index != 0) {
		cur = cur->next;
		index--;
	}
	if (cur == NULL) { return false; }
	out = cur->data;
	return true;
}
