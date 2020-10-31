
#include <stdio.h> // for reading files(?)
#include <string.h>
#include <stdlib.h> // required for atof() method (?)

struct A
{
  int val1;
  double val2;
  int val3;
};

struct B
{
  struct A aInsideB;
};

void printA(struct A a)
{
  printf("This is 'val1': %d, this is 'val2': %.2f, and this is 'val3': %d\n", a.val1, a.val2, a.val3);
}

int main(void)
{
  struct A a = {10, 22.2, 333};
  printA(a);
  struct A a2 = {10};
  printA(a2);

  struct B b = {a};
  printA(b.aInsideB);

  printf("This is 'val1' (%d) from the A which is inside the B\n", b.aInsideB.val1);

  // The above line is equal to the two below
  struct A a3 = b.aInsideB;
  printf("This is 'val1' (%d) from the A which is inside the B\n", a3.val1);

  return 0;
}