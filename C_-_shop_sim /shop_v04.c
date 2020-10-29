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
// Definiton of structs
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
struct ProductQuantity
{
  struct Product product; // cross reference to 'Product' struct; struct type.
  int quantity;           // quantity of the product available in the shop/customer stok.
};

// ----- ----- -----
// This struct defines the shop entity. The struct variable stock is predefined (and cross referred to other nested structs).
struct Shop
{
  double cash;                      // The amount of maney in the shop.
  struct ProductQuantity stock[20]; // Nested 'ProductQuantity' struct (which in turn consists of nested 'Product' struct). This variable has a preset limit of items.
  int index;                        // This variable is used for cycling through the content ('for loop'); default (starting) value of index is 0.
};

// ----- ----- -----
// This struct defines the customer blueprint.
struct Customer
{
  char *name;                              // Pointer is used here, so that the size of memory is dynamically allocated, depending on the name's length.
  double budget;                           // This variable will limit the customer buying capacity.
  struct ProductQuantity shoppingList[10]; // Nested 'ProductQuantity' struck, predefined size of the array (amount of items a customer may hold).
  int index;                               // This variable allows for looping through the items the customer has.
};

// ===== ===== =====
// Definition of methods
// ===== ===== =====

// Terminology reminder: In C functions exchange information by means of parameters and arguments. The term parameter refers to any declaration within the parentheses following the function name in a function declaration or definition; the term argument refers to any expression within the parentheses of a function call. (Source: https://www.cs.auckland.ac.nz/references/unix/digital/AQTLTBTE/DOCU_056.HTM)

// ----- ----- -----
// Printing product info
void printProduct(struct Product prod) // This method requires a struct 'Product' (takes it as a parameter), named localy within the method as to 'prod'. The method does not return anything.
{
  printf("Product Name: %s \nProduct Price: €%.2f \n", prod.name, prod.price); // Values of prod.name and prod.price of the passed instance of the struct when the method was called. These are referring to product's properties defining the strut instance.
}

// ----- ----- -----
// Create shop
// Reading data from a file line by line and converts into a variables (shop cash and stock).
struct Shop createAndStockShop() // This creates a struct of 'Shop' type and its actual instance is a results (return) of the function createAndStockShop().
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
  {
    printf("File not found\n");
    exit(EXIT_FAILURE);
  }

  // read the first line only - the initial value of cash available in shop
  read = getline(&line, &len, fp);
  double cashInShop = atof(line);
  struct Shop shop = {cashInShop}; // This struct initialises the 'shop' instance of 'Shop' struct, and saves the shop's initial cash

  // Below we read each line and extract and assign certain data to correct variables.
  while ((read = getline(&line, &len, fp)) != -1) // Reads line by line to the end of file. "&line" referres to value of the line (I guess); -1 means to the end of file.
  {
    // printf(": %s \n", line); // This is for testing if the program reads the file; comented out for clarity

    // Function "strtok" is used to break down a string by provided delimiter (eg ",").
    char *nam = strtok(line, ","); // Exctract certain data (product name) from the line (slicing) till encounter delimiter "," and assigns to variable "name" - here with pointer, as we do not know how long is the name.
    char *pri = strtok(NULL, ","); // Exctract product price from the previous delimiter in the line (NULL) till encounter the next delimiter ",".
    char *qua = strtok(NULL, ","); // Exctract product available quantity from the previous delimiter in the line (NULL) till encounter the next delimiter "," (or end of line?).

    // Printing the outcome. Note 1: quantity is read from file as string type. Note 2: the method introduces a line break after the line from file that was read (because by default it reads data as string).

    // To convert string into intiger, we will use "atoi" method, and to float - "atof" method.
    double price = atof(pri);
    int quantity = atoi(qua);
    char *name = malloc(sizeof(char) * 50); // max length of the product name read from the file is dynamically allocated in the memory (with a pointer) and is limited to 50 characters
    strcpy(name, nam);                      // copies variable 'nam' (initialised in the line above) to string variable 'name'

    // assign the read values to the struct placeholders
    struct Product product = {name, price};
    struct ProductQuantity stockItem = {product, quantity};

    shop.stock[shop.index++] = stockItem; // The above data extracted from file will be added to shop stock of struct "Shop".
    // printf("Product: %s, €%.2f; available: %d pcs.\n", name, price, quantity); // Testing; the content of the struck will be read with a dedicated method "printShop" below.
  }

  return shop; // this returns the struct 'shop' of Shop type
}

// ----- ----- -----
// Process customer shopping
// Reading data from a file line by line and converts into a variable (product stock) and add to struct that represents the customer.
struct Customer create_customer()
{
  // Reading file script is based on https://stackoverflow.com/a/3501681
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  size_t read;

  // reading the file.
  fp = fopen("customer_good.csv", "r"); // The file is in the same directory, "r" means it is to be read only.

  // Error handling (in case the file cannot be found)
  if (fp == NULL)
  {
    printf("File not found\n");
    exit(EXIT_FAILURE);
  }

  // read the first line only - the name of the customer and available money
  read = getline(&line, &len, fp);

  // Function "strtok" is used to break down a string by provided delimiter (eg ",").
  char *nam = strtok(line, ","); // Exctract certain data (customer name) from the line (slicing) till encounter delimiter "," and assigns to variable "name" - here with pointer, as we do not know how long is the name.
  char *bud = strtok(NULL, ","); // Exctract product available quantity from the previous delimiter in the line (NULL) till encounter the next delimiter "," (or end of line?).

  // Printing the outcome. Note 1: quantity is read from file as string type. Note 2: the method introduces a line break after the line from file was read (because by default it reads data as string).

  // To convert string into intiger, we will use "atoi" method, and to float - "atof" method.
  char *name = malloc(sizeof(char) * 50); // max length of the customer name to be read from file is limited to 50 characters
  strcpy(name, nam);                      // copies variable 'nam' (initialised in the line above) to string variable 'name'
  int budget = atof(bud);

  //assign name and budget to the customer - use the above variables (name and budget)
  struct Customer customer_A = {name, budget};
  //printf("Ccustomer: %s, money: %.2f\n", customer_A.name, customer_A.budget); // for testing

  // read the remaining lines from the file, extract and assign certain data to the appropriate variables.
  while ((read = getline(&line, &len, fp)) != -1) // Reads line by line to the end of file. "&line" referres to value of the line (I guess); -1 means until the end of file.
  {
    // Method "strtok" is used to break down a string by provided delimiter (eg ",").
    char *p_nam = strtok(line, ","); // Exctract certain data (product name) from the line (slicing) till encounter delimiter "," and assigns to variable "name" - here with pointer, as we do not know how long is the name.
    char *p_qua = strtok(NULL, ","); // Exctract product available quantity from the previous delimiter in the line (NULL) till encounter the next delimiter ",".

    // Printing the outcome. Note 1: quantity is read from file as string type. Note 2: the method introduces a line break after the line from file was read (because by default it reads data as string).

    // To convert string into intiger, we will use "atoi" method, and to float - "atof" method.
    char *name = malloc(sizeof(char) * 50); // max length of the product name to be read from file is limited to 50 characters
    strcpy(name, p_nam);                    // copies variable nam to variable name (initialised in the line above)
    int quantity = atoi(p_qua);

    struct Product product = {name}; // variable product.price is omitted here - is that right?
    // printf("Test: %s\n", product.name); //test Ok

    struct ProductQuantity shopping_list_item = {product, quantity}; // 'shopping_list_item' is just a temporary variable
    // printf("Teeest: %s, qty: %d\n", shopping_list_item.product, shopping_list_item.quantity); //test Ok
    customer_A.shoppingList[customer_A.index++] = shopping_list_item; // The above values from 'shopping_list_items' are now assigned to 'shoppingList[index]'.

    printf("qty, %d\n", customer_A.shoppingList[customer_A.index]);
  }
  printf("Number of items: %d\n", customer_A.index);                       // test OK
  printf("1st product: %s\n", customer_A.shoppingList[0].product.name);    // test OK
  printf("Amount of 1st item: %d\n", customer_A.shoppingList[0].quantity); // test OK
  printf("****\n\n");

  /* // test OK
  for (int i = 0; i < customer_A.index; i++)
  {
    printf("Available amount: %d\n", customer_A.shoppingList[i].quantity);
    printf("---- ---- ----\n");
  }
  printf("\n");
  */

  //printf("Test4: %s\n", customer_A.name); // test OK
  //printf("Test5: %.2f\n", customer_A.budget); // test OK

  //printf("%s's budget: €%.2f; Shopping item 1: %s, qty: __ pcs.\n", name, budget, customer_A.shoppingList[0]); // Testing; the content of the struck will be read with a dedicated method "printShop" below.
  //printf("Test5: Customer: %s; product: __, qty: __ pcs.\n", name);

  return customer_A;
}

// ----- ----- -----
// Method to create a print out of the shop stock. It takes "struct Shop" as a parameter.
void printShop(struct Shop sh)
{
  printf("----\n");
  printf("Shop has %.2f in cash\n", sh.cash);
  printf("==== ==== ====\n");
  for (int i = 0; i < sh.index; i++)
  {
    printProduct(sh.stock[i].product);
    printf("Available amount: %d\n", sh.stock[i].quantity);
    printf("---- ---- ----\n");
  }
  printf("\n");
}

/*
// ----- ----- -----
// Printing customer info
void printCustomer(struct Customer cust) // This method takes an instance of struct 'Customer' as a parameter, refered within the method as to 'cust'. The method does not return anything.
{

  // create customer from file

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
*/

// ===== ===== =====
// Main program methods (options from the main menu).
// ===== ===== =====

// ----- ----- -----
// Option 1 - display the shop available cash and stock
int shop_status(void) // This method is of 'int' type, and does not return anything.
{
  struct Shop shop = createAndStockShop(); // This struct calls the method that will read data from a file.
  printShop(shop);
  return 0;
}

// ----- ----- -----
// Option 2 - process customer A (good case) shopping
void customer_A_shopping(void)
{
  // create customer A struct (good case)
  struct Customer customer_A = create_customer(); // This struct calls the method that will read data from a file.
  //printCustomer(customer_A);
  return 0;
}

// ===== ===== =====
// The shop main menu
// ===== ===== =====

// Menu script adapted from https://ladvien.com/command-line-menu-c/
void shop_menu()
{
  char char_choice[2];
  int choice = -1; // the initial value is set just to initialise the variable

  system("cls");   // for Windows system
  system("clear"); // for Linux system

  do
  {
    printf("\n");
    printf("Shop Main Menu:\n");
    printf("***************\n");
    printf("1. Shop status\n");
    printf("2. Customer A - good case\n");
    printf("3. Customer B - insufficient funds case\n");
    printf("4. Customer C - exceeding order case\n");
    printf("5. Interactive mode\n");
    // printf("7. Reset shop")
    printf("9. Exit\n");
    printf("NB: The sequence of the customers being processed might affect the initial case of the customers. \n");

    fflush(stdin); // flushes the input string from any left overs from previous inputs
    scanf("%s", char_choice);
    choice = atoi(char_choice);

    switch (choice)
    {
    case 1:
      shop_status();
      break;
    case 2:
      customer_A_shopping(); // initially good case
      break;
    case 3:
      // printCustomer(customer_B); // initially insufficient funds  case
      break;
    case 4:
      // printCustomer(customer_C); // initially exceeding order case
      break;
    case 5:
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