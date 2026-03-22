/* This file is in the public domain. */

#include "heapsort.h"

/*
	Sorts the ptrs vector.  (*cmp)(ptrs[i],ptrs[j]) should return:

		< 0	if *ptrs[i] < *ptrs[j]
		= 0	if *ptrs[i] = *ptrs[j]
		> 0	if *ptrs[i] > *ptrs[j]

	For example, if the ptrs are actually pointers to int, it would
	be perfectly good to write a cmp function as follows (unless the
	integers are so large that overflow can occur in the subtraction):

		int cmp(p1,p2)
		void *p1;
		void *p2;
		{
		 return(*(int *)p1 - *(int *)p2);
		}

	The vector will be in non-decreasing order by this criterion on
	return from heapsort.
*/

static void _heapsort_bubble_down(int i, int size, void **ptrs, int (*cmp)(void *, void *))
{
 int j;
 int l;
 int r;
 int cl;
 int cr;
 void *temp;

 while (1)
  { if (i >= size) return;
    l = i + i + 1;
    r = l + 1;
    cl = (l >= size) ? 1 : ((*cmp)(ptrs[i],ptrs[l]) >= 0);
    cr = (r >= size) ? 1 : ((*cmp)(ptrs[i],ptrs[r]) >= 0);
    switch ((cl<<1)|cr)
     { case 0:
	  j = ((*cmp)(ptrs[l],ptrs[r]) > 0) ? l : r;
	  break;
       case 1:
	  j = l;
	  break;
       case 2:
	  j = r;
	  break;
       case 3:
	  return;
     }
    temp = ptrs[j];
    ptrs[j] = ptrs[i];
    ptrs[i] = temp;
    i = j;
  }
}

void heap_sort(void **ptrs, int nels, int (*cmp)(void *, void *))
{
 int i;
 void *temp;

 if (nels <= 1) return;
 for (i=nels>>1;i>=0;i--) _heapsort_bubble_down(i,nels,ptrs,cmp);
 i = nels;
 while (i > 1)
  { i --;
    temp = ptrs[i];
    ptrs[i] = ptrs[0];
    ptrs[0] = temp;
    _heapsort_bubble_down(0,i,ptrs,cmp);
  }
}
