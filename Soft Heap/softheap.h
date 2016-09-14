#pragma once

#include <stdlib.h>
#include <limits.h>
#include <iostream>

typedef struct ILCELL
{
	int key;
	struct ILCELL *next;
} ilcell;

typedef struct NODE
{
	int ckey, rank;
	struct NODE *next, *child;
	struct ILCELL *il, *il_tail;
} node;

typedef struct HEAD
{
	struct NODE *queue;
	struct HEAD *next, *prev, *suffix_min;
	int rank;
} head;

//-----------------------------------------

node* new_node()
{
	return (node*)malloc(sizeof(node));
}

head* new_head()
{
	return (head*)malloc(sizeof(head));
}

//-----------------------------------------

static head *header, *tail;
static int r;

void initialize()
{
	header = new_head();
	tail = new_head();
	tail->rank = INT_MAX;
	header->next = tail;
	tail->prev = header;
	std::cout << "Enter r:\n" << std::endl;
	std::cin >> r;
}

void insert(int newKey)
{
	node *q;
	ilcell *l;

	l = (ilcell *)malloc(sizeof(ilcell));
	l->key = newKey;
	l->next = NULL;
	
	q = new_node();
	q->rank = 0;
	q->ckey = newKey;
	q->il = l;
	q->il_tail = l;

	meld(q);
}

void meld(node *q)
{
	head *h, *prevHead, *toHead = header->next;
	node *top, *bottom;
	
	while (q->rank > toHead->rank)
		toHead = toHead->next;

	prevHead = toHead->prev;

	while (q->rank == toHead->rank)
	{
		if (toHead->queue->ckey > q->ckey)
		{
			top = q;
			bottom = toHead->queue;
		}
		else
		{
			top = toHead->queue;
			bottom = q;
		}

		q = new_node();
		q->ckey = top->ckey;
		q->rank = top->rank + 1;
		q->child = bottom;
		q->next = top;
		q->il = top->il;
		q->il_tail = top->il_tail;
		toHead = toHead->next;
	}

	if (prevHead == toHead->prev)
		h = new_head();
	else
		h = prevHead->next;

	h->queue = q;
	h->rank = q->rank;
	h->prev = prevHead;
	h->next = toHead;
	prevHead->next = h;
	toHead->prev = h;
	fix_minlist(h);
}