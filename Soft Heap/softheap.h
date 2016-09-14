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

}