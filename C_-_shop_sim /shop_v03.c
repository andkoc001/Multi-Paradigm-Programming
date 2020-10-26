// Shop simulator in C
// Author: Andrzej Kocielski
// Multi-Paradigm Programming, GMIT 2020
// Lecturer: Dominic Carr

// ===== ===== =====
// Importing external libraries
// ===== ===== =====

#include <stdio.h> // for reading files(?)
#include <string.h>
#include <stdlib.h> // required for atof() method (?)

// ===== ===== =====
// Definiton of structs.
// ===== ===== =====

// ----- ----- -----
// This struct defines the blueprint for products offered in the shop. It consists of two variables, defined inside the struct.
struct Product
{
  char *name;   // * (asterix) indicates a pointer and will allow for dynamic memory allocation, because the length of the product name is not yet know.
  double price; // double float data type for the product price.
};

// ----- ----- -----
// This struct defines the stock of a product and its available quantity. Note it consists of another struct object, nested inside. This struct is used to show the stock both shop and customers.
struct ProductStock
{
  struct Product product; // cross reference to 'Product' struct; struct type.
  int quantity;           // quantity of the product available in the shop.
};

// ----- ----- -----
// This struct defines the shop entity. The struct variable stock is predefined (and cross referred to another struct).
struct Shop
{
  double cash;                   // The amount of maney in the shop.
  struct ProductStock stock[20]; // Nested 'ProductStock' struct (which in turn consists of nested 'Product' struct). This variable has a preset limit of items.
  int index;                     // This variable is used for cycling through the content (for loop); default (starting) value of index is 0.
};

// ----- ----- -----
// This struct defines the customer blueprint.
struct Customer
{
  char *name;                           // Pointer is used here, so that the size of memory is dynamically allocated, depending on the name's length.
  double budget;                        // This variable will limit the customer buying capacity.
  struct ProductStock shoppingList[10]; // Nested 'ProductStock' struck, predefined size of the array (amount of items a customer may hold).
  int index;                            // This variable allows for looping through the items the customer has.
};

// ===== ===== =====
// Definition of methods
// ===== ===== =====

// Reminder: In C functions exchange information by means of parameters and arguments. The term parameter refers to any declaration within the parentheses following the function name in a function declaration or definition; the term argument refers to any expression within the parentheses of a function call. (Source: https://www.cs.auckland.ac.nz/references/unix/digital/AQTLTBTE/DOCU_056.HTM)

// ----- ----- -----
// Printing product info
void printProduct(struct Product prod) // This method requires a struct 'Product' (takes as a parameter), named localy within the method as to 'prod'. The method does not return anything.
{
  printf("Product Name: %s \nProduct Price: €%.2f \n", prod.name, prod.price); // Values of prod.name and prod.price of the passed instance of the struct when the method was called. These are referring to product's properties defined the strut instance (within 'Main' method).
}

// ----- ----- -----
// Printing customer info
void printCustomer(struct Customer cust) // This method takes an instance of struct 'Customer' as a parameter, refered within the method as to 'cust'. The method does not return anything.
{
  printf("---- ----\n");
  printf("Customer Name: %s \nCustomer Budget: €%.2f \n\n", cust.name, cust.budget); // Values of cust.name and cust.budget are referring to customer's details defined the strut instance (within 'Main' method).
  printf("==== ====\n");
  // Below we are going to print all the items (for loop) the customer has, using the 'index' variable defined in the struct.
  for (int i = 0; i < cust.index; i++) // Iteration of from i=0, increasing by 1, through all the items the customer has. Variable 'index' (defined in the struct) by defult starts with value 0 (zero)
  {
    printProduct(cust.shoppingList[i].product);                                          // Calls for previously defined method. In each cycle, as arguments, item of i-th index is taken.
    printf("%s orders %d of above product\n", cust.name, cust.shoppingList[i].quantity); // example of chain-accessing the data in the nested stucts
    // Calculating sub-total cost of all items of the i-th product (of the same kind).
    double cost = cust.shoppingList[i].quantity * cust.shoppingList[i].product.price;                                 // qty*price
    printf("The sub-total cost of %s to %s will be €%.2f. \n\n", cust.shoppingList[i].product.name, cust.name, cost); // Prints out cost of all items of the product
  }
}

// ----- ----- -----
// Reading data from a file line by line and converts into a variable (product stock) and add to struct that represents the shop.
struct Shop createAndStockShop() // The type has been later changed from "Void" to "struct Shop".
{

  // Reading file script is based on https://stackoverflow.com/a/3501681
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  size_t read;

  // reading the file.
  fp = fopen("shop_stock.csv", "r"); // The file is in the same directory, "r" means it is to be read only.
  // Error handling (in case the file cannot be found)
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // read the first line only - the initial value of cash available in shop
  read = getline(&line, &len, fp);
  double cashInShop = atof(line);
  struct Shop shop = {cashInShop}; // This struct represents shop's initial cash

  // Below we read each line and extract and assign certain data to correct variables.
  while ((read = getline(&line, &len, fp)) != -1) // Reads line by line to the end of file. "&line" referres to value of the line (I guess).
  {
    // printf(": %s \n", line); // This is for testing if the program reads the file; comented out for clarity
    // Method "strtok" is used to break down a string by provided delimiter (eg ",").
    char *nam = strtok(line, ","); // Exctract certain data (product name) from the line (slicing) till encounter delimiter "," and assigns to variable "name" - here with pointer, as we do not know how long is the name.
    char *pri = strtok(NULL, ","); // Exctract product price from the previous delimiter in the line (NULL) till encounter the next delimiter ",".
    char *qua = strtok(NULL, ","); // Exctract product available quantity from the previous delimiter in the line (NULL) till encounter the next delimiter ",".
    // Printing the outcome. Note 1: quantity is read from file as string type. Note 2: the method introduces a line break after the line from file was read (because by default it reads data as string).
    // To convert string into intiger, we will use "atoi" method, and to float - "atof" method.
    int quantity = atoi(qua);
    double price = atof(pri);
    char *name = malloc(sizeof(char) * 50); // max length of the product name to be read from file is limited to 50 characters
    strcpy(name, nam);                      // copies variable nam to variable name (initialised in the line above)
    struct Product product = {name, price};
    struct ProductStock stockItem = {product, quantity};
    shop.stock[shop.index++] = stockItem; // The above data extracted from file will be added to shop stock of struct "Shop".
    // printf("Product: %s, €%.2f; available: %d pcs.\n", name, price, quantity); // Commented out as replaced by a dedicated method "printShop" below.
  }

  fclose(fp);
  // error handling
  //if (line)
  //  free(line);
  //exit(EXIT_SUCCESS);

  return shop;
}

// ----- ----- -----
// Method to create a print out of the shop stock. It takes "struct Shop" as a parameter.
void printShop(struct Shop sh)
{
  printf("---- ----\n");
  printf("Shop has %.2f in cash\n", sh.cash);
  printf("==== ====\n");
  for (int i = 0; i < sh.index; i++)
  {
    printProduct(sh.stock[i].product);
    printf("Available amount: %d\n", sh.stock[i].quantity);
    printf("----\n");
  }
  printf("\n");
}

// ===== ===== =====
// Main program methods (chosen from the main menu).
// ===== ===== =====

// ----- ----- -----
// Option 1 - display the shop available cash and stock
int shop_status(void) // The 'main' function is of 'int' type, and does not return anything.
{

  struct Shop shop = createAndStockShop(); // This method will read data from a file.
  printShop(shop);
  return 0;
}

// ===== ===== =====
// The shop main menu
// ===== ===== =====

// Menu script adapted from https://ladvien.com/command-line-menu-c/
void shop_menu()
{
  char char_choice[2];
  int choice = 0; // the initial value is set

  system("cls");   // for Windows system
  system("clear"); // for Linux system

  do
  {
    printf("\n");
    printf("Shop Main Menu:\n");
    printf("***************\n");
    printf("1. Shop status\n");
    printf("2. Customer A status - initially good case\n");
    printf("3. Customer A shopping\n"); // customer status will be updated
    printf("4. Customer B status - initially insufficient funds case\n");
    printf("5. Customer B shopping\n");
    printf("6. Customer C status - Initially exceeding order case\n");
    printf("7. Customer C shopping\n");
    printf("8. Interactive mode\n");
    printf("9. Exit\n");

    printf("Note the sequence of the customers' shopping being processed will affect the shop status and might also affect the initial case of the customers. \n");

    scanf("%s", char_choice);
    choice = atoi(char_choice);

    switch (choice)
    {
    case 1:
      shop_status();
      break;
    case 2:
      // customer_a_status(); // initially good case
      break;
    case 4:
      // customer_b_status(); // initially insufficient funds case
      break;
    case 6:
      // customer_c_status(); // initiallt exceeding order case
      break;
    case 8:
      // interactive_mode();
      break;
    case 9:
      // exit
      break;
    default:
      printf("Wrong key. Enter the option number for desired operation.\n");
      break;
    }
  } while (choice != 9);
}

// ===== ===== =====
// The main method of the program
// ===== ===== =====

int main()
{
  shop_menu(); // calls the method that displays the shop menu

  return 0;
}