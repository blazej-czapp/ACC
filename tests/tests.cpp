#include <iostream>
#include "LinkedList.hpp"
#include "ArrayList.hpp"

using namespace std;
using namespace acc;


void test_adding_elements(List<int> &list) {
	printf("test_adding_elements\n");
	for(int i=0;i<100;i++) {
		list.add(i*i);
	}

	for(int i=99;i>=0;i--) {
		int value = list[i];
		if(value != i*i) {
			printf("test_adding_elements - failed expected: %d got: %d\n", i*i, value);
		}
	}
}

void test_remove_by_value(List<int> &list) {
	printf("test_remove_by_value\n");
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
		int value = list[i];
		if(value == 1 || value == 49*49 || value == 99*99) {
			printf("test_remove_by_value - found removed value %d\n", value);
		}
	}
}


void linkedlist__test_copy_constructor() {
	printf("test_copy_constructor\n");
	LinkedList<int> list;
	for(int i=0;i<100;i++) {
		list.add(i*i);
	}

	LinkedList<int> copy(list);
	for(int i=99;i>=0;i--) {
		int value = copy[i];
		if(value != i*i) {
			printf("test_adding_elements - failed expected: %d got: %d\n", i*i, value);
		}
	}
}

void test_iterator__iteration(List<int> &list) {
	printf("test_iterator__iteration\n");
	for(int i=0;i<100;i++) {
		list.add(i*i);
	}

	Iterator<int> iterator = list.iterator();
	for(int i=0;i<100;i++) {
		int value = iterator.get();
		if(value != list[i]) {
			printf("test_iterator__iteration failed, expected %d found %d\n", list[i], value);
		}
		iterator.next();
	}

	if(iterator.hasCurrent()) {
		printf("test_iterator__iteration failed, hasNext returned where it should be empty\n");
	}
}

void test_remove_by_index__first_element(List<int> &list) {
	printf("test_remove_by_index__first_element\n");
	for(int i=0;i<100;i++) {
		list.add(i*i);
	}

	list.removeAt(0);

	if(list.size() != 99) {
		printf("test_remove_by_index__first_element expected size 99 got %d\n", list.size());
	}

	for(int i=0;i<99;i++) {
		int value = list[i];
		if(value != (i+1)*(i+1)) {
			printf("test_remove_by_index__first_element expected value %d got %d\n", (i+1)*(i+1), value);
		}
	}
}

void test_remove_by_index__midle_element(List<int> &list) {
	printf("test_remove_by_index__midle_element\n");
	for(int i=0;i<51;i++) {
		list.add(i*i);
	}
	list.removeAt(20);

	if(list.size() != 50) {
		printf("test_remove_by_index__first_element expected size 50 got %d\n", list.size());
	}

	for(int i=0;i<50;i++) {
		int value = list[i];
		if(value == 20*20) {
			printf("test_remove_by_index__midle_element found removed element 20*20\n");
		}
	}

}

void test_remove_by_index__last_element(List<int> &list) {
	printf("test_remove_by_index__last_element\n");
	for(int i=0;i<13;i++) {
		list.add(i*i);
	}
	list.removeAt(12);

	if(list.size() != 12) {
		printf("test_remove_by_index__last_element expected size 12 got %d\n", list.size());
	}	

	for(int i=0;i<12;i++) {
		if(list[i] == 12*12) {
			printf("test_remove_by_index__last_element found removed element 12\n");
		}
	}
}

void test_addAt__first_element(List<int> &list) {
	printf("test_addAt__first_element\n");
	for(int i=0;i<10;i++) {
		list.add(i*i);
	}

	list.addAt(0, 999);

	if(list[0] != 999) {
		printf("test_addAt__first_element first element is not 999 but %d\n", list[0]);
	}

	if(list.size() != 11) {
		printf("test_addAt__first_element wrong list size should be 11 was %d\n", list.size());
	}


	for(int i=0;i<10;i++) {
		if(list[i+1] != i*i) {
			printf("test_addAt__first_element orignal list was changed\n");
		}
	}
}

void test_addAt__middle_element(List<int> &list) {
	printf("test_addAt__middle_element\n");
	for(int i=0;i<10;i++) {
		list.add(i*i);
	}

	list.addAt(5, 999);

	if(list[5] != 999) {
		printf("test_addAt__middle_element first element is not 999 but %d\n", list[5]);
	}

	if(list.size() != 11) {
		printf("test_addAt__middle_element wrong list size should be 11 was %d\n", list.size());
	}


	for(int i=0;i<5;i++) {
		if(list[i] != i*i) {
			printf("test_addAt__middle_element orignal list was changed\n");
		}
	}

	for(int i=6;i<11;i++) {
		if(list[i] != (i-1)*(i-1)) {
			printf("test_addAt__middle_element orignal list was changed\n");
		}
	}
}

void test_addAt__last_element(List<int> &list) {
	printf("test_addAt__last_element\n");
	for(int i=0;i<10;i++) {
		list.add(i*i);
	}

	list.addAt(9, 999);

	if(list[9] != 999) {
		printf("test_addAt__last_element 9th element is not 999 but %d\n", list[9]);
	}

	if(list.size() != 11) {
		printf("test_addAt__last_element wrong list size should be 11 was %d\n", list.size());
	}


	for(int i=0;i<9;i++) {
		if(list[i] != i*i) {
			printf("test_addAt__last_elements orignal list was changed\n");
		}
	}
}

void test_forward_iterator__remove_first(List<int> &list) {
	printf("test_forward_iterator__remove_first\n");
	for(int i=0;i<10;i++) {
		list.add(i*i);
	}

	Iterator<int> iterator = list.iterator();
	iterator.remove();

	if(list.size() != 9) {
		printf("test_forward_iterator__remove_first wrong list size found %d should be 9\n", list.size());		
	}

	for(int i=1;i<10;i++) {
		if(list[i-1] != i*i) {
			printf("test_forward_iterator__remove_first wrong value on list %d\n", list[i-1]);
		}
	}
}

void test_forward_iterator__remove_midle(List<int> &list) {
	printf("test_forward_iterator__remove_midle\n");
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
		if(i < 5 && list[i] != i*i) {
			printf("test_forward_iterator__remove_midle pre found %d should be %d\n",list[i], i*i);
		}

		if(i >= 5 && list[i] != (i+1)*(i+1)) {
			printf("test_forward_iterator__remove_midle post found %d should be %d\n",list[i], i*i);
		}
	}	
}

void test_forward_iterator__remove_last(List<int> &list) {
	printf("test_forward_iterator__remove_last\n");
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
		if(list[i] != i*i) {
			printf("test_forward_iterator__remove_last expected %d found %d\n", i*i, list[i]);
		}
	}


}

void test_forward_iterator__remove_all(List<int> &list) {
	printf("test_forward_iterator__remove_all\n");
	for(int i=0;i<10;i++) {
		list.add(i*i);
	}

	
	for (Iterator<int> it = list.iterator(); it.hasCurrent(); it.next()) {
		it.remove();
	}

	if(list.size() != 0) {
		printf("test_forward_iterator__remove_all is not 0 - %d\n", list.size());
	}
}

void test_reverse_iterator__iteration(List<int> &list) {
	printf("test_reverse_iterator__iteration\n");
	for(int i=0; i < 10; i++) {
		list.add(i*i);
	}

	int i = 9;
	for(Iterator<int> it=list.reverse();it.hasCurrent();it.next(), i--) {
		if(it.get() != i*i) {
			printf("test_reverse_iterator__iteration found %d should %d\n", it.get(), i*i);
		}
	}
}

void test_reverse_remove__first(List<int> &list) {
	printf("test_reverse_remove__first\n");
	for(int i=0; i < 10; i++) {
		list.add(i*i);
	}

	Iterator<int> iterator = list.reverse();
	iterator.remove();
	iterator.next();

	if(list.size() != 9) {
		printf("test_reverse_remove__first list size should be 9 is %d\n", list.size());
	}
	
	for(int i=8; i >= 0; iterator.next(), i--) {
		if(list[i] != i*i || iterator.get() != i*i) {
			printf("test_reverse_remove__first expected %d list.get - %d, iterator %d\n", i*i, list[i], iterator.get());
		}
	}
}

void test_revers_remove__middle(List<int> &list) {
	printf("test_revers_remove__middle\n");
	for(int i=0; i < 10; i++) {
		list.add(i*i);
	}

	Iterator<int> iterator = list.reverse();
	for(int i=8;i>=5;i--) {
		iterator.next();
	}
	iterator.remove();
	iterator.next();

	if(list.size() != 9) {
		printf("test_revers_remove__middle wrong size %d should be 9\n", list.size());
	}

	for(int i=4; i >= 0; iterator.next(), i--) {
		if(list[i] != i*i || iterator.get() != i*i) {
			printf("test_revers_remove__middle wrong value list.get - %d, iterator - %d, should be %d\n", list[i], iterator.get(), i*i);
		}
	}

	for(int i=5;i<9;i++) {
		if(list[i] != (i+1)*(i+1)) {
			printf("test_revers_remove__middle wrong value list.get - %d, should be %d\n", list[i], (i+1)*(i+1));
		}
	}
}

void test_reverse_remove__last(List<int> &list) {
	printf("test_reverse_remove__last\n");
	for(int i=0; i < 10; i++) {
		list.add(i*i);
	}

	Iterator<int> iterator = list.reverse();
	for(int i=9;i>0;i--) {
		iterator.next();
	}
	iterator.remove();

	if(list.size() != 9) {
		printf("test_reverse_remove__last wrong list size %d should be 9\n", list.size());
	}
	
	for(int i=1; i<10;i++) {
		if(list[i-1] != i*i) {
			printf("test_reverse_remove__last wrong value should be %d found %d\n", i*i, list[i-1]);
		}
	}
}

void test_reverse_remove__all(List<int> &list) {
	printf("test_reverse_remove__all\n");
	for(int i=0; i < 10; i++) {
		list.add(i*i);
	}

	for(Iterator<int> it=list.reverse(); it.hasCurrent();it.next()) {
		it.remove();
	}

	if(list.size() != 0) {
		printf("test_reverse_remove__all wrong list size %d should be 0\n", list.size());	
	}
}

void test_contains(List<int> &list) {
	printf("test_contains\n");
	for(int i=0; i < 10; i++) {
		list.add(i*i);
	}

	if(!list.contains(0)) {
		printf("test_contains failed for 0\n");
	}

	if(!list.contains(81)) {
		printf("test_contains failed for 81 last\n");
	}

	if(!list.contains(25)) {
		printf("test_contains failed for 25 middle\n");
	}

	if(list.contains(300)) {
		printf("test_contains failed, found 300\n");
	}
}

void test_indexOf(List<int> &list) {
	printf("test_indexOf\n");
	for(int i=0; i < 10; i++) {
		list.add(i*i);
	}
	list.add(81);
	list.add(81);
	list.add(81);
	list.add(100);

	if(list.indexOf(0) != 0) {
		printf("test_indexOf failed for 0\n");	
	}

	if(list.indexOf(81) != 9) {
		printf("test_indexOf failed for 9\n");	
	}

	if(list.indexOf(100) != 13) {
		printf("test_indexOf failed for 9\n");	
	}

	if(list.indexOf(16) != 4) {
		printf("test_indexOf failed for 16\n");	
	}

	if(list.indexOf(300) != -1) {
		printf("test_indexOf failed for 300\n");	
	}
}

void test_lastIndexOf(List<int> &list) {
	printf("test_lastIndexOf\n");
	for(int i=0; i < 10; i++) {
		list.add(i*i);
	}
	list.add(81);
	list.add(81);
	list.add(81);
	list.add(100);

	if(list.lastIndexOf(0) != 0) {
		printf("test_lastIndexOf failed for 0\n");	
	}

	if(list.lastIndexOf(81) != 12) {
		printf("test_lastIndexOf failed for 9\n");	
	}

	if(list.lastIndexOf(100) != 13) {
		printf("test_lastIndexOf failed for 9\n");	
	}

	if(list.lastIndexOf(16) != 4) {
		printf("test_lastIndexOf failed for 16\n");	
	}

	if(list.lastIndexOf(300) != -1) {
		printf("test_lastIndexOf failed for 300\n");	
	}
}

int main() {

	/* LinkedList */
	printf("--- LinkedList ---\n");
	{
		LinkedList<int> list;
		test_adding_elements(list);
	}
	{
		LinkedList<int> list;
		test_iterator__iteration(list);	
	}
	linkedlist__test_copy_constructor();
	
	{
		LinkedList<int> list;
		test_remove_by_value(list);
	}
	{
		LinkedList<int> list;
		test_remove_by_index__first_element(list);
	}
	{
		LinkedList<int> list;
		test_remove_by_index__midle_element(list);
	}
	{
		LinkedList<int> list;
		test_remove_by_index__last_element(list);
	}

	{
		LinkedList<int> list;
		test_addAt__first_element(list);
	}
	{
		LinkedList<int> list;
		test_addAt__middle_element(list);
	}
	{
		LinkedList<int> list;
		test_addAt__last_element(list);
	}

	{
		LinkedList<int> list;
		test_forward_iterator__remove_first(list);
	}
	{
		LinkedList<int> list;
		test_forward_iterator__remove_midle(list);
	}
	{
		LinkedList<int> list;
		test_forward_iterator__remove_last(list);
	}
	{
		LinkedList<int> list;
		test_forward_iterator__remove_all(list);
	}

	{
		LinkedList<int> list;
		test_reverse_iterator__iteration(list);
	}
	{
		LinkedList<int> list;
		test_reverse_remove__first(list);
	}
	{
		LinkedList<int> list;
		test_revers_remove__middle(list);
	}
	{
		LinkedList<int> list;
		test_reverse_remove__last(list);
	}
	{
		LinkedList<int> list;
		test_reverse_remove__all(list);
	}

	{
		LinkedList<int> list;
		test_contains(list);
	}
	{
		LinkedList<int> list;
		test_indexOf(list);
	}
	{
		LinkedList<int> list;
		test_lastIndexOf(list);
	}

	/* ArrayListList */
	printf("--- ArrayListList ---\n");
	{
		ArrayList<int> ArrayList;
		test_adding_elements(ArrayList);
	}
	{
		ArrayList<int> list;
		test_iterator__iteration(list);	
	}
	
	
	{
		ArrayList<int> list;
		test_remove_by_value(list);
	}
	{
		ArrayList<int> list;
		test_remove_by_index__first_element(list);
	}
	{
		ArrayList<int> list;
		test_remove_by_index__midle_element(list);
	}
	{
		ArrayList<int> list;
		test_remove_by_index__last_element(list);
	}

	{
		ArrayList<int> list;
		test_addAt__first_element(list);
	}
	{
		ArrayList<int> list;
		test_addAt__middle_element(list);
	}
	{
		ArrayList<int> list;
		test_addAt__last_element(list);
	}

	{
		ArrayList<int> list;
		test_forward_iterator__remove_first(list);
	}
	{
		ArrayList<int> list;
		test_forward_iterator__remove_midle(list);
	}
	{
		ArrayList<int> list;
		test_forward_iterator__remove_last(list);
	}
	{
		ArrayList<int> list;
		test_forward_iterator__remove_all(list);
	}

	{
		ArrayList<int> list;
		test_reverse_iterator__iteration(list);
	}
	{
		ArrayList<int> list;
		test_reverse_remove__first(list);
	}
	{
		ArrayList<int> list;
		test_revers_remove__middle(list);
	}
	{
		ArrayList<int> list;
		test_reverse_remove__last(list);
	}
	{
		ArrayList<int> list;
		test_reverse_remove__all(list);
	}

	{
		ArrayList<int> list;
		test_contains(list);
	}
	{
		ArrayList<int> list;
		test_indexOf(list);
	}
	{
		ArrayList<int> list;
		test_lastIndexOf(list);
	}

	return 0;
}