#include <iostream>
#include "List.h"
#include "Student.h"

using namespace std;


List::List() {
	head = NULL;
	count = 0;
}


bool List::empty() {
	if (count == 0) return true;
	return false;
}


int List::size() {
	return count;
}


Node* List::find(int position) {
	Node* cur;

	if (position > count) return NULL; //exceeed number of node
	cur = head;
	for (int count = 1; count < position; count++)
		cur = cur->next;
	return cur;
}


bool List::get(int position, type& result) {
	if (position > count) return false; //exceeed number of node
	result = find(position)->item;
	return true;
}


bool List::set(int position, type newItem) {
	if (position > count) return false;
	find(position)->item = newItem;
	return true;
}


bool List::insert(int at, type newItem) {// Any simplification can be done on code below?
	Node* pre, * cur, * tmp = new Node(newItem);

	if (at < 1 || at > count + 1) return false; //1 until last number of node
	if (!tmp) return false;

	if (empty()) {
		head = tmp;
		count++;
		return true;
	}
	if (at == 1) {
		tmp->next = head;
		head = tmp;
		count++;
		return true;
	}
	pre = find(at - 1); //node before insert position 
	cur = pre->next;//node after insert position
	tmp->next = cur;//insert node. next = cur
	pre->next = tmp;//node before.nexxt = tmp
	count++;
	return true;
}


bool List::remove(int from) {
	Node* pre, * cur;

	if (from < 1 || from > count) return false;
	if (from == 1) {
		cur = head;//cur point to head
		head = head->next;//head = second node
		count--;
		free(cur);//free head
		return true;
	}
	pre = find(from - 1);//pre = node before  node that delete
	cur = pre->next;//cur =  node that delete
	pre->next = cur->next; //pre.next = node that delete.next
	free(cur);
	count--;
	return true;
}

//insert Student according to name
bool List::insert(type newItem) {
	Node* pre, * cur, * tmp;

	tmp = new Node(newItem);//create a element and store all struct value in temp node

	if (!tmp) return false; //if fail to create tmp then break
	if (empty()) {//if list is empty 
		head = tmp;
		count++;
		return true;
	}
	count++;
	if (head->item.compareName1(newItem)) {//if head(b) bigger than now(a)  //only use for temp compare with head
		tmp->next = head; 				   //now point to previous
		head = tmp;						   //now become head
		return true;					   //become now -> previous
	}
	pre = head;									    //call out the list with head     //only use for temp compare with below head
	cur = pre->next;								//cur is a node that after head (call it as node 2)
	for (; cur != NULL;) {							//if cur is not null then continue below line 
		if (cur->item.compareName1(newItem)) break;	//if cur.name(b) is larger than temp.name(a) then break (quit the for loop) ~ cuz temp(a) should put front of cur(b)
		pre = cur;	cur = cur->next;				//if cur.name(a) is smaller than temp.name(b) then change next node (node 3) to compare 
	}												// loop until node is NULL so the biggest temp will put before NUll
	tmp->next = cur;								//insert temp node before cur node or NULL
	pre->next = tmp;								//
	return true;
}


