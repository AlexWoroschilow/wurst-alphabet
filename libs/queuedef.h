/*
	  This file is part of gdub.
	  (C) 2006 Steve Hoffmann 
 
	  gdub is free software; you can redistribute it and/or modify
	  it under the terms of the GNU General Public License as published
	  by the Free Software Foundation; either version 2, or (at your
	  option) any later version.
 
	  gdub is distributed in the hope that it will be useful, but
	  WITHOUT ANY WARRANTY; without even the implied warranty of
	  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	  General Public License for more details.
 
	  You should have received a copy of the GNU General Public License
	  along with gdub; see the file COPYING.  If not, write to the
	  Free Software Foundation, Inc., 59 Temple Place - Suite 330,
	  Boston, MA 02111-1307, USA.	
 
 */

/**
 * @file queuedef.h
 * @author Steve Hoffmann
 * @brief header file for a queue
 */

/*
 * $Log$
 *
 */


#ifndef QUEUEDEF_H
#define QUEUEDEF_H

/*#include "memman.h"*/
#include "memory.h"
#include "basic-types.h"

typedef int Queueelem;

typedef struct
{
	Queueelem *queuespace;
	int 	enqueueindex,
			dequeueindex,
			queuesize,
			noofelements;
} Queue;

void emptyqueue(void *spacetab, Queue *q, int queuesize);
BOOL queueisempty(Queue *q);
void resizequeue(void *spacetab, Queue *q);
void enqueue(void *spacetab, Queue *q, Queueelem elem);
Queueelem dequeue(Queue *q);
void showqueue(Queue *q);
void wrapqueue(void *spacetab, Queue *q);

#endif 
