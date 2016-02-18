#include "list.h"

list::list()
{
	head = nullptr;
	tail = nullptr;
}


list::~list()
{
	Bucket *n;
	while (head != nullptr) {
		n = head;
		head = n->next;
		delete n;
	}
}

void list::add(float ymax, float xmin, float minv, float dx, float dy)
{
	Bucket *n = new Bucket();
	n->ymax = ymax;
	n->xmin = xmin;
	n->minv = minv;
	n->dx = dx;
	n->dy = dy;
	n->prev = nullptr;

	n->next = head;
	if (head) {
		head->prev = n;
	}
	head = n;
}

void list::sort()
{
	bool done = false;

	Bucket* prev;
	Bucket* cur;
	Bucket* temp;

	if (head == nullptr || head->next == nullptr)
		return;
	while (!done) {
		done = true;
		cur = head->next;
		while (cur) {
			if (cur->xmin < cur->prev->xmin) {
				swapBack(cur);
				done = false;
			}
			cur = cur->next;
		}
	}
}

void list::print()
{
	Bucket* cur = head;
	Bucket* last = head;
	printf("F: ");
	while (cur) {
		printf("%f ", cur->ymax);
		last = cur;
		cur = cur->next;
	}
	printf("\nB: ");
	while (last) {
		printf("%f ", last->ymax);
		last = last->prev;
	}
	printf("\n");
}

void list::swapBack(Bucket* n) {
	Bucket* nodeBefore = n->prev;
	Bucket* nodeAfter = n->next;
	//Only if we can move it back at all.
	if (nodeBefore) {
		nodeBefore->next = nodeAfter;
		n->prev = nodeBefore->prev;
		n->next = nodeBefore;
		if (nodeBefore->prev)
			nodeBefore->prev->next = n;
		else
			head = n;
		if (nodeAfter)
			nodeAfter->prev = nodeBefore;
		nodeBefore->prev = n;
	}
}

void list::remove(Bucket * n)
{
	Bucket* prev = n->prev;
	Bucket* next = n->next;

	if (prev)
		prev->next = n->next;
	if (next)
		next->prev = prev;

	if (n == head)
		head = next;

	delete n;
}

void list::removeObsolete(int j)
{
	Bucket* cur = head;
	Bucket* prev;

	while (cur) {
		prev = cur;
		cur = cur->next;
		if (prev->ymax <= j) {
			remove(prev);
		}
	}
}

void list::prepend(list * b)
{
	Bucket* cur = b->head;
	while (cur) {
		this->add(cur->ymax, cur->xmin, cur->minv, cur->dx, cur->dy);
		cur = cur->next;
	}
}
