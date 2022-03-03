#pragma once

class node {
public:
	int value;
	node* next = nullptr;

	node(int value) {
		this->value = value;
	}
};

class linked_list {
private:
	int size = 0;
	node* head = nullptr;

	node* get_node(int index)
	{
		node* current = head;

		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		return current;
	}

	node* create_node(int value)
	{
		size++;
		return new node(value);
	}

public:
	int get_size()
	{
		return size;
	}

	void append(int value)
	{
		node* new_node = create_node(value);

		if (head == nullptr) {
			head = new_node;
		}
		else {
			node* tail = head;
			while (tail->next != nullptr) {
				tail = tail->next;
			}
			tail->next = new_node;
		}
	}

	void prepend(int value)
	{
		insert(0, value);
	}

	void insert(int index, int value)
	{
		node* new_node = create_node(value);

		if (index == 0) {
			new_node->next = head;
			head = new_node;
		}
		else {
			node* current = get_node(index - 1);
			new_node->next = current->next;
			current->next = new_node;
		}
	}

	int get(int index)
	{
		return get_node(index)->value;
	}

	void remove(int index)
	{
		node* removed_node;

		if (index == 0) {
			removed_node = head;
			head = head->next;
		}
		else {
			node* previous_node = get_node(index - 1);
			removed_node = previous_node->next;
			previous_node->next = removed_node->next;
		}
		delete removed_node;
		size--;
	}

	bool contains(int value) {
		node* current = head;

		for (int i = 0; i < size; i++) {
			if (current->value == value) return true;
			current = current->next;
		}
		return false;
	}

	~linked_list() {
		while (get_size() > 0) {
			remove(0);
		}
	}
};