#include <stdio.h>
#include <stdlib.h>

struct Product {
	char* name;
	double price;
};

void passDirect(struct Product p)
{
	p.price = 1000.0;
	p.name = "Coke 330ml";
}

void passPointer(struct Product* p)
{
	p->price = 1000.0;
	p->name = "Coke 330ml";
}

int main()
{
	// These are two products
	struct Product a = { "Coke Can", 1.10 };
	struct Product* b = &a;
	
	passDirect(a);
	printf("Price is now %.2f for %s \n", a.price, a.name);
	passPointer(b);
	printf("Price is now %.2f for %s \n", a.price, a.name);

}
