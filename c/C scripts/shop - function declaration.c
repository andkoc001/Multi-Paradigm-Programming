#include <stdio.h>
#include <stdlib.h>

struct Product {
	char* name;
	double price;
};

void passDirect(struct Product p)
{
	p.price = 1000.0;
}

void passPointer(struct Product* p);

int main()
{
	// These are two products
	struct Product a = { "Coke Can", 1.10 };
	struct Product* b = &a;
	
	passDirect(a);
	printf("Price is now %.2f\n", a.price);
	passPointer(b);
	printf("Price is now %.2f\n", a.price);

}

void passPointer(struct Product* p)
{
	p->price = 1000.0;
}