#pragma once
#ifndef nullptr
#define nullptr NULL
#endif
#include <stdio.h>


struct Bucket
{
	float ymax, xmin, minv;
	float dx, dy;
	Bucket* next;
	Bucket* prev;
};

class list
{
private:

public:

	Bucket *head;
	Bucket *tail;

	Bucket *current;

	list();
	~list();
	
	void add(float ymax, float xmin, float minv, float dx, float dy);
	void swapBack(Bucket* n);
	void remove(Bucket* n);
	void removeObsolete(int j);
	void prepend(list* b);
	void sort();
	void print();

	Bucket* begin() { 
		current = head;
		return head; 
	};

	Bucket* next() {
		current = current->next;
		return current;
	}

	Bucket* end() {
		return nullptr;
	}
};

