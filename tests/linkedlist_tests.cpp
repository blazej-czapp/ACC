#include <iostream>
#include "LinkedList.hpp"

using namespace std;
using namespace acc;



void test_adding_elements() {
	printf("test_adding_elements\n");
	LinkedList<int> list;
	for(int i=0;i<100;i++) {
		list.add(i*i);
	}

	for(int i=99;i>=0;i--) {
		int value = list.get(i);
		if(value != i*i) {
			printf("test_adding_elements - failed expected: %d got: %d\n", i*i, value);
		}
	}
}

void test_remove_by_value() {
	printf("test_remove_by_value\n");
	LinkedList<int> list;
	for(int i=0;i<100;i++) {
		list.add(i*i);
	}

	list.remove(99*99);
	list.remove(1);
	list.remove(49*49);

	if(list.size() != 97) {
		printf("test_remove_by_value - incorrect size after remove %d\n", list.size());
	}

	for(int i=0;i<100-3;i++) {
		int value = list.get(i);
		if(value == 1 || value == 49*49 || value == 99*99) {
			printf("test_remove_by_value - found removed value %d\n", value);
		}
	}
}


void test_copy_constructor() {
	printf("test_copy_constructor\n");
	LinkedList<int> list;
	for(int i=0;i<100;i++) {
		list.add(i*i);
	}

	LinkedList<int> copy(list);
	for(int i=99;i>=0;i--) {
		int value = copy.get(i);
		if(value != i*i) {
			printf("test_adding_elements - failed expected: %d got: %d\n", i*i, value);
		}
	}
}

void test_iterator__iteration() {
	printf("test_iterator__iteration\n");
	LinkedList<int> list;
	for(int i=0;i<100;i++) {
		list.add(i*i);
	}

	Iterator<int> iterator = list.iterator();
	for(int i=0;i<100;i++) {
		int value = iterator.get();
		if(value != list.get(i)) {
			printf("test_iterator__iteration failed, expected %d found %d\n", list.get(i), value);
		}
		iterator.next();
	}

	if(iterator.hasCurrent()) {
		printf("test_iterator__iteration failed, hasNext returned where it should be empty\n");
	}
}

void test_remove_by_index__first_element() {
	printf("test_remove_by_index__first_element\n");
	LinkedList<int> list;
	for(int i=0;i<100;i++) {
		list.add(i*i);
	}

	list.removeAt(0);

	if(list.size() != 99) {
		printf("test_remove_by_index__first_element expected size 99 got %d\n", list.size());
	}

	for(int i=0;i<99;i++) {
		int value = list.get(i);
		if(value != (i+1)*(i+1)) {
			printf("test_remove_by_index__first_element expected value %d got %d\n", (i+1)*(i+1), value);
		}
	}
}

void test_remove_by_index__midle_element() {
	printf("test_remove_by_index__midle_element\n");
	LinkedList<int> list;
	for(int i=0;i<51;i++) {
		list.add(i*i);
	}
	list.removeAt(20);

	if(list.size() != 50) {
		printf("test_remove_by_index__first_element expected size 50 got %d\n", list.size());
	}

	for(int i=0;i<50;i++) {
		int value = list.get(i);
		if(value == 20*20) {
			printf("test_remove_by_index__midle_element found removed element 20*20\n");
		}
	}

}

void test_remove_by_index__last_element() {
	printf("test_remove_by_index__last_element\n");
	LinkedList<int> list;
	for(int i=0;i<13;i++) {
		list.add(i*i);
	}
	list.removeAt(12);

	if(list.size() != 12) {
		printf("test_remove_by_index__last_element expected size 12 got %d\n", list.size());
	}	

	for(int i=0;i<12;i++) {
		if(list.get(i) == 12*12) {
			printf("test_remove_by_index__last_element found removed element 12\n");
		}
	}
}

void test_addAt__first_element() {
	printf("test_addAt__first_element\n");
	LinkedList<int> list;
	for(int i=0;i<10;i++) {
		list.add(i*i);
	}

	list.addAt(0, 999);

	if(list.get(0) != 999) {
		printf("test_addAt__first_element first element is not 999 but %d\n", list.get(0));
	}

	if(list.size() != 11) {
		printf("test_addAt__first_element wrong list size should be 11 was %d\n", list.size());
	}


	for(int i=0;i<10;i++) {
		if(list.get(i+1) != i*i) {
			printf("test_addAt__first_element orignal list was changed\n");
		}
	}
}

void test_addAt__middle_element() {
	printf("test_addAt__middle_element\n");
	LinkedList<int> list;
	for(int i=0;i<10;i++) {
		list.add(i*i);
	}

	list.addAt(5, 999);

	if(list.get(5) != 999) {
		printf("test_addAt__middle_element first element is not 999 but %d\n", list.get(5));
	}

	if(list.size() != 11) {
		printf("test_addAt__middle_element wrong list size should be 11 was %d\n", list.size());
	}


	for(int i=0;i<5;i++) {
		if(list.get(i) != i*i) {
			printf("test_addAt__middle_element orignal list was changed\n");
		}
	}

	for(int i=6;i<11;i++) {
		if(list.get(i) != (i-1)*(i-1)) {
			printf("test_addAt__middle_element orignal list was changed\n");
		}
	}
}

void test_addAt__last_element() {
	printf("test_addAt__last_element\n");
	LinkedList<int> list;
	for(int i=0;i<10;i++) {
		list.add(i*i);
	}

	list.addAt(9, 999);

	if(list.get(9) != 999) {
		printf("test_addAt__last_element 9th element is not 999 but %d\n", list.get(9));
	}

	if(list.size() != 11) {
		printf("test_addAt__last_element wrong list size should be 11 was %d\n", list.size());
	}


	for(int i=0;i<9;i++) {
		if(list.get(i) != i*i) {
			printf("test_addAt__last_elements orignal list was changed\n");
		}
	}
}

void test_forward_iterator__remove_first() {
	printf("test_forward_iterator__remove_first\n");
	LinkedList<int> list;
	for(int i=0;i<10;i++) {
		list.add(i*i);
	}

	Iterator<int> iterator = list.iterator();
	iterator.remove();

	if(list.size() != 9) {
		printf("test_forward_iterator__remove_first wrong list size found %d should be 9\n", list.size());		
	}

	for(int i=1;i<10;i++) {
		if(list.get(i-1) != i*i) {
			printf("test_forward_iterator__remove_first wrong value on list %d\n", list.get(i-1));
		}
	}
}

void test_forward_iterator__remove_midle() {
	printf("test_forward_iterator__remove_midle\n");
	LinkedList<int> list;
	for(int i=0;i<10;i++) {
		list.add(i*i);
	}

	Iterator<int> iterator = list.iterator();
	for (int i = 0; i < 5; i++)
	{
		iterator.next();
	}
	iterator.remove();
	
	for(int i=0;i<9;i++) {
		if(i < 5 && list.get(i) != i*i) {
			printf("test_forward_iterator__remove_midle pre found %d should be %d\n",list.get(i), i*i);
		}

		if(i >= 5 && list.get(i) != (i+1)*(i+1)) {
			printf("test_forward_iterator__remove_midle post found %d should be %d\n",list.get(i), i*i);
		}
	}	
}

void test_forward_iterator__remove_last() {
	printf("test_forward_iterator__remove_last\n");
	LinkedList<int> list;
	for(int i=0;i<10;i++) {
		list.add(i*i);
	}

	Iterator<int> iterator = list.iterator();
	for (int i = 0; i < 9; i++)
	{
		iterator.next();
	}
	iterator.remove();

	if(list.size() != 9) {
		printf("%test_forward_iterator__remove_last expected list size 9 was %d\n", list.size());
	}

	for(int i=0;i<9;i++) {
		if(list.get(i) != i*i) {
			printf("test_forward_iterator__remove_last expected %d found %d\n", i*i, list.get(i));
		}
	}


}

void test_forward_iterator__remove_all() {

}

void test_reverse_iterator__iteration() {
	
}

int main() {
	test_iterator__iteration();

	test_copy_constructor();
	test_adding_elements();
	test_remove_by_value();

	test_remove_by_index__first_element();
	test_remove_by_index__midle_element();
	test_remove_by_index__last_element();

	test_addAt__first_element();
	test_addAt__middle_element();
	test_addAt__last_element();

	test_forward_iterator__remove_first();
	test_forward_iterator__remove_midle();
	test_forward_iterator__remove_last();
	return 0;
}