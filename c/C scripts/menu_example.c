// MPP - Week 6 - A Menu in C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void askName()
{
	fflush(stdin);
	printf("What is your name?\n");
	char name[10];
	fgets(name,10,stdin);
	printf("Glad to meet you, %s\n",name);
}

int main(void) 
{
	int choice = -1;

	while (choice != 0){
		
		fflush(stdin);
		printf("\nPlease choose an option ");
		scanf("%d", &choice);

		if (choice == 1)
		{
			printf("The user pressed 1\n");
		} else if (choice == 2){
			printf("here we can do something else");
		} else if (choice == 3){
			askName();
		}
	}
	printf("Buh bye");
}