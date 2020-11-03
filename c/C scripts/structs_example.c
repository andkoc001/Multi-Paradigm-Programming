// accompanies MPP - Week 6 - Structs Explained
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct A {
	int val;
	double val2;
	int val3;
};

struct B {
	struct A aInsideB;
};

void printA(struct A a){
	printf("this is 'val' %d, this is 'val2' %.2f, and this is 'val3' %d\n", a.val, a.val2, a.val3);
}

int main(void) 
{
	struct A a = { 10, 20.2, 4 };
	printA(a);
	struct A a2 = { 100 };
	printA(a2);
	
	struct B b = { a };
	printA(b.aInsideB);
	
	struct A a3 = b.aInsideB;
	printf("this is a 'val' (%d) from the A which is inside the B", a3.val);

    return 0;
}