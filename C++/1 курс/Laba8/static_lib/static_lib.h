#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Items {
	string name;
	string amount;
	string cost;
	string date;
	Items* next;
};

struct List {
	Items* head = NULL, * tail = NULL;
};

class ITEM {
public:
	void Print(const List&);
	void Push(struct List& item, string name, string amount, string cost, string date);
	void Pop(Items*&, List&);
	void Sort(List&);

	List& Create() {
		List element;
		return element;
	}
};

void ITEM::Print(const List& item) {

	cout << "\nСписок:\n\n";

	Items* current = item.head;
	for (current; current != NULL; current = current->next)
		cout << current->name << ' ' << current->cost << '\n';

	putchar('\n');
}

void ITEM::Push(List& item, string name, string amount, string cost, string date) {

	Items* new_element = new Items();

	new_element->name = name;
	new_element->amount = amount;
	new_element->cost = cost;
	new_element->date = date;

	if (item.head == NULL) {
		item.head = new_element;
		item.tail = new_element;
	}
	else {
		item.tail->next = new_element;
		item.tail = new_element;
	}
}

void ITEM::Pop(Items*& cur, List& m) {

	if (cur == m.head)
		m.head = cur->next;

	else if (cur == m.tail) {
		Items* new_tail = m.head;
		Items* Tail = m.head->next;

		while (Tail->next != NULL) {
			Tail = Tail->next;
			new_tail = new_tail->next;
		}
		new_tail->next = NULL;
		cur = new_tail->next;
		free(Tail);
	}
	else {
		Items* temp = cur->next;
		cur = temp->next;
		free(temp);
	}

}

void ITEM::Sort(List& item) {

	int condition = 100000;
	Items* cur = item.head;

	for (cur; cur != NULL; cur = cur->next) {
		if (atoi(cur->cost.c_str()) < condition)
			Pop(cur, item);
		item.tail = cur;
		if (cur == NULL) break;

		if (cur->next != NULL)
			item.tail = cur->next;
	}

	Print(item);
}
