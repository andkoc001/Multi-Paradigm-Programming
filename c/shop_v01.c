// Shop simulator in C
// Author: Andrzej Kocielski
// Multi-Paradigm Programming, GMIT 2020
// Lecturer: Dominic Carr

// ===== ===== =====
// Importing external libraries

#include <stdio.h> // for reading files(?)
#include <string.h>
#include <stdlib.h> // required for atof() method (?)

// ===== ===== =====
// Definiton of structs. This is a data type (refered below as to an object) in C language; the concept similar to classes or objects' constructors, a blueprint.

// This struct defines the blueprint for products offered in the shop. It consists of two variables, defined inside the struct.
struct Product
{
  char *name;   // * (asterix) indicates a pointer and will allow for dynamic memory allocation, because the length of the product name is not yet know.
  double price; // double float data type for the product price.
};

// This constructor defines the stock of a product and its available quantity. Note it consists of another struct object, nested inside. This struct is used to show the stock both shop and customers.
struct ProductStock
{
  struct Product product; // cross reference to 'Product' constructor; struct type.
  int quantity;           // quantity of the product available in the shop.
};

// This constructor defines the shop entity. The constructor variable stock is predefined (and cross referred to another constructor).
struct Shop
{
  double cash;                   // The amount of maney in the shop.
  struct ProductStock stock[20]; // Nested 'ProductStock' struct (which in turn consists of nested 'Product' struct). This variable has a preset limit of items.
  int index;                     // This variable is used for cycling through the content (for loop); default (starting) value of index is 0.
};

// This constructor defines the customer blueprint.
struct Customer
{
  char *name;                           // Pointer is used here, so that the size of memory is dynamically allocated, depending on the name's length.
  double budget;                        // This variable will limit the customer buying capacity.
  struct ProductStock shoppingList[10]; // Nested 'ProductStock' struck, predefined size of the array (amount of items a customer may hold).
  int index;                            // This variable allows for looping through the items the customer has.
};

// ===== ===== =====
// Definition of methods

// Printing product info
void printProduct(struct Product prod) // This method requires a struct 'Product' (takes as a parameter), named localy within the method as to 'prod'. The method does not return anything.
{
  printf("Product Name: %s \nProduct Price: €%.2f \n", prod.name, prod.price); // Values of prod.name and prod.price of the passed instance of the struct when the method was called. These are referring to product's properties defined the strut instance (within 'Main' method).
}

// Printing customer info
void printCustomer(struct Customer cust) // This method takes an instance of struct 'Customer' as a parameter, refered within the method as to 'cust'. The method does not return anything.
{
  printf("-----\nCustomer Name: %s \nCustomer Budget: €%.2f \n\n-----\n", cust.name, cust.budget); // Values of cust.name and cust.budget are referring to customer's details defined the strut instance (within 'Main' method).
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

// ===== ===== =====
// Reading data from a file line by line and converts into a variable (product stock) and add to struct that represents the shop.
struct Shop createAndStockShop() // The type has been later changed from "Void" to "struct Shop".
{
  struct Shop shop = {222}; // This struct represents shop - what products are in stock. Insde the curly brackets is the shop cash

  // Reading file script is based on https://stackoverflow.com/a/3501681
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  size_t read;

  // reading the file.
  fp = fopen("../stock.csv", "r"); // The file is in the same directory, "r" means it is to be read only.
  // Error handling (in case the file cannot be found)
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // Below we read each line and extract and assign certain data to correct variables.
  while ((read = getline(&line, &len, fp)) != -1) // Reads line by line to the end of file. "&line" referres to value of the line (I guess).
  {
    // printf(": %s \n", line); // This is for cheking if the program reads the file; comented out for clarity
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

// Method to create a print out. It takes "struct Shop" as a parameter.
void printShop(struct Shop sh)
{
  printf("\n");
  printf("Shop has %.2f in cash\n", sh.cash);
  printf("========\n");
  for (int i = 0; i < sh.index; i++)
  {
    printProduct(sh.stock[i].product);
    printf("Available amount: %d\n", sh.stock[i].quantity);
    printf("----\n");
  }
  printf("\n");
}

// ===== ===== =====
// Main program body

int main(void) // The 'main' function is of 'int' type, and does not return anything.
{
  // Below is a block of code made obscolete (and hence commented out) by creation of the method "createAndStockShop()".

  /*
  // Initialisation of a customer. Note, only two of three variables are being defined here. 'shoppingList has already a value predefined in the moment of cration.
  struct Customer customer1 = {"Andrzej", 123.45}; // Andrzej with budget 123.45 has been assigned to instance 'customer1' of 'Customer' class.
  printf("\n");
  // obsolete // printf("Customer name is %s. His/her current budget is €%.2f.\n", customer1.name, customer1.budget); // This line is used as a check.

  // Initialisation of products.
  struct Product prod1 = {"SoftDrink Can", 0.85}; // Product's name and price assigned to instance 'prod1' of 'Product' class.
  printf("\n");
  // obsolete // printf("This is %s. One item costs €%.2f.\n", prod1.name, prod1.price); // This line is used as a check.
  printProduct(prod1);

  struct Product prod2 = {"Bread", 1.30}; // Product's name and price assigned to instance 'prod1' of 'Product' class.
  printf("\n");
  printProduct(prod2);

  // Initialisation of prodcts quantity the customer desires.
  struct ProductStock prod1Stock = {prod1, 4}; // Product's refernce to 'prod1' (of 'Product' struct) and quantity the customer desires.
  struct ProductStock prod2Stock = {prod2, 2};
  printf("\n");
  // obsolete // printf("Available quantity of product %s is %d.\n", prod1Stock.product.name, prod1Stock.quantity); // This line is used as a check.
  customer1.shoppingList[customer1.index++] = prod1Stock; // Iterates through products the customer has. The index by default is zero, but increases each time it is accessed.
  customer1.shoppingList[customer1.index++] = prod2Stock;
  printCustomer(customer1);
  */

  struct Shop shop = createAndStockShop(); // This method will read data from a file.
  printShop(shop);
  return 0;
}

//C functions exchange information by means of parameters and arguments. The term parameter refers to any declaration within the parentheses following the function name in a function declaration or definition; the term argument refers to any expression within the parentheses of a function call.
