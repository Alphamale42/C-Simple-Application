/ENSF337- Fall 2022
#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

#include "list.h"


FlowList::FlowList(): headH(0){}; // one - line constructor setting headH to null.


FlowList::~FlowList() {  // destructor class function
	Node *h1 = headH;
	Node *next = NULL;
	while(h1 != NULL) {
		next = h1 -> next;
		free(h1);
		h1 = next;
	}
	headH= NULL;
}

int FlowList::create(const ListItem& new_item){
	Node *start = headH;
	
	while(start != 0) {
		if( start -> item.year == new_item.year)
			return 0;
		start = start -> next;
	}
	
	Node *nptr = new Node;
	if(nptr == NULL) {
		cerr << "Memory not available" << endl;
		exit(1);
	}
	nptr -> item = new_item;
	
	
	if(headH == 0 || new_item.year < headH -> item.year) {
		nptr -> next = headH;
		headH = nptr;
	}
	else {
		Node *before = headH;
		Node *after = headH -> next;
		while(after != 0 && new_item.year > after -> item.year) {
			before = after;
			after = after -> next;
		}
		nptr -> next = after;
		before -> next = nptr;
	}
	return 1;
}

ListItem FlowList::get_average(const int& position) const {
	Node * pos_pointer = headH;
	int counter = 1;
	while(counter < position) {
		pos_pointer = pos_pointer -> next;
		counter++;
	}
	return pos_pointer -> item;
}

int FlowList::remove(const int& yr) {
	if(headH == 0 || yr < headH -> item.year) 
		return 0;
	Node *doomed_node = 0;
	if(yr == headH -> item.year) {
		doomed_node = headH;
		headH = headH -> next;
	}
	else {
		Node *before = headH;
		Node *maybe_doomed = headH -> next;
		while(maybe_doomed != 0 && yr > maybe_doomed -> item.year) {
			before = maybe_doomed;
			maybe_doomed = maybe_doomed -> next;
		}
		if(maybe_doomed == 0)
			return 0;
		if(maybe_doomed -> item.year == yr){
			doomed_node = maybe_doomed;
			before -> next = maybe_doomed -> next;
		}
		else 
			return 0;
	}
	delete doomed_node;
	return 1;
}

void FlowList::print() const{
	cout << fixed;
	if(headH != 0) {
		Node *print_pt = headH;
		while(print_pt != 0) {
			cout << setw(8) << left << print_pt -> item.year << setprecision(1) << print_pt -> item.flow << endl;
			print_pt = print_pt -> next;
		}
	}
}

