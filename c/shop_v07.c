// Shop simulator in C
// Author: Andrzej Kocielski
// Multi-Paradigm Programming, GMIT 2020
// Lecturer: dr Dominic Carr

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
struct ProductStock
{
  struct Product product; // cross reference to 'Product' struct; struct type.
  int quantity;           // quantity of the product available in the shop/customer stok.
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
  double cash;                   // The amount of maney in the shop.
  struct ProductStock stock[20]; // Nested 'ProductStock' struct (which in turn consists of nested 'Product' struct). This variable has a preset limit of items.
  int index;                     // This variable is used for cycling through the content ('for loop'); default (starting) value of index is 0.
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
  // if the price is  defined (we are showing the shop stock), then both name and price are shown; otherwise (we are showing the customer shopping list) only product name is showm
  if (prod.price == 0)
  {
    printf("Product: %s; ", prod.name); // Values of prod.name and prod.price of the passed instance of the struct when the method was called. These are referring to product's properties defining the strut instance.
  }
  else
  {
    printf("Product: %s; \tPrice: €%.2f \t", prod.name, prod.price); // Values of prod.name and prod.price of the passed instance of the struct when the method was called. These are referring to product's properties defining the strut instance.
  }
}
// Getting product price from another struct
double get_product_price(struct Product prod) //  The method does not return anything.
{
  return prod.price; // Values of prod.price from another struct
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
  fp = fopen("../shop_stock.csv", "r"); // The file is in the same directory, "r" means it is to be read only.

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
    struct ProductStock stockItem = {product, quantity};

    shop.stock[shop.index++] = stockItem; // The above data extracted from file will be added to shop stock of struct "Shop".
    // printf("Product: %s, €%.2f; available: %d pcs.\n", name, price, quantity); // Testing; the content of the struck will be read with a dedicated method "printShop" below.
  }

  return shop; // this returns the struct 'shop' of Shop type
}

// ----- ----- -----
// Process customer shopping
// Reading data from a file line by line and converts into a variable (product stock) and add to struct that represents the customer.
struct Customer create_customer(path_to_customer)
{

  // Reading file script is based on https://stackoverflow.com/a/3501681
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  size_t read;

  // reading the file.
  fp = fopen(path_to_customer, "r"); // The file is in the same directory, "r" means it is to be read only.
  //fp = fopen("../customer_insufficient_funds.csv", "r"); // The file is in the same directory, "r" means it is to be read only.
  //fp = fopen("../customer_exceeding_order.csv", "r"); // The file is in the same directory, "r" means it is to be read only.

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

    ///////////////////////////
    // Question: will this not overwrite the original struct 'Product product'?
    struct Product product = {name}; // variable product.price is omitted here, so the default value (zero) is assumed (?)

    struct ProductQuantity shopping_list_item = {product, quantity}; // 'shopping_list_item' is just a temporary variable
    // printf("Test3: %s, qty: %d\n", shopping_list_item.product, shopping_list_item.quantity); //test Ok
    customer_A.shoppingList[customer_A.index++] = shopping_list_item; // The above values from 'shopping_list_items' are now assigned to 'shoppingList[index]'.

    // printf("Test2: %s\n", product.name); //test OK
    // printf("Test3: %s\n", price); // test NOT OK
    // printf("qty, %d\n", customer_A.shoppingList[customer_A.index]); // for testing - OK
  }

  // test
  // printf("Number of itmes: %d\n", customer_A.index); // test OK
  // printf("1st product: %s\n", customer_A.shoppingList[0].product.name);       // test OK
  // printf("Amount of 1st product: %d\n", customer_A.shoppingList[0].quantity); // test OK
  // printf("****\n\n");

  return customer_A;
}

// ----- ----- -----
// Print out of the shop stock.
void printShop(struct Shop sh)
// The method takes "struct Shop" as a parameter; it does not return anything.
{
  // Show shop detials
  printf("Shop has €%.2f in cash\n", sh.cash);
  printf("==== ==== ====\n");

  // loop through the items and show the associated details (name, price, quantity)
  for (int i = 0; i < sh.index; i++)
  {
    printProduct(sh.stock[i].product);
    printf("Available amount: %d\n", sh.stock[i].quantity);
  }
  printf("\n");
}

// ----- ----- -----
// Printing customer shoppling list
void process_order(struct Customer cust, struct Shop sh)
// This method takes an instance of struct 'Customer' and struct 'shop' as parameters, refered within the method as to 'cust' and 'sh'. The method does not return anything.
{
  // Show customers details
  printf("Customer Name: %s, budget: €%.2f \n", cust.name, cust.budget); // Values of cust.name and cust.budget are referring to customer's details defined the strut instance (within 'Main' method).
  printf("---- ---- ----\n");

  // initialise auxiliary variables
  double total_cost = 0;

  //int customer_wants = cust.shoppingList[0].quantity;

  //show customer's shopping list
  for (int i = 0; i < cust.index; i++) // Iteration of from i=0, increasing by 1, through all the items the customer has. Variable 'index' (defined in the struct) by defult starts with value 0 (zero)
  {
    // Show customers details
    double sub_total = 0;

    printf("Customer wants product: %s, quantity %d. ", cust.shoppingList[i].product, cust.shoppingList[i].quantity); // example of chain-accessing the data in the nested stucts

    // Calculating sub-total cost of all items of the i-th product in customer's shopping list.

    char *cust_item_name = cust.shoppingList[i].product.name; // assign the i-th product from the customer schopping list as a shorthand

    // check whether the product from customer's shopping list is matches with the shop stock list of products
    int match_exist = 0;

    // Iterate through shop stock list to match items from customer's shopping list
    for (int j = 0; j < sh.index; j++)
    {

      char *sh_item_name = sh.stock[j].product.name; // assign the j-th product from the shop stock list

      if (strcmp(cust_item_name, sh_item_name) == 0) // if there is match
      {
        match_exist++;

        //check products availability
        if (cust.shoppingList[i].quantity <= sh.stock[j].quantity) // sufficient amount of the product in the shop stock
        {
          // perform the cost of the i-th item from the customer's shopping list
          double sub_total_full = cust.shoppingList[i].quantity * sh.stock[j].product.price; // qty*price
          printf("\tSub-total cost will be €%.2f. \n", sub_total_full);                      // Prints out cost of all items of the product
          sub_total = sub_total_full;
        }

        else // customer wants more than in stock
        {
          int partial_order_qty = cust.shoppingList[i].quantity - (cust.shoppingList[i].quantity - sh.stock[j].quantity); // will buy all that is in stock

          // perform the cost of the i-th item from the customer's shopping list
          double sub_total_partial = partial_order_qty * sh.stock[j].product.price;                                            // partial qty * price
          printf("\tOnly %d is available and bought. Sub-total cost will be €%.2f. \n", partial_order_qty, sub_total_partial); // Prints out cost of all items of the product
          sub_total = sub_total_partial;
        }

        // addition of sub totals
        total_cost = total_cost + sub_total;
      }
    }

    // if customer wants a product that is not in the shop
    if (match_exist == 0) // there is no match
    {
      printf("\tThis product not available. Sub-total cost will be €%.2f. \n", sub_total); // Prints out cost of all items of the product
    }
  }

  printf("\nTotal cost will be €%.2f. \n", total_cost); // Prints out cost of all items of the product

  // Check whether the customer can afford the desired items
  if (cust.budget < total_cost)
  {
    printf("Unfortunately, you do not have enough money for all the desired items. You are short of €%.2f. ", (total_cost - cust.budget));
    printf("Come back with more frinds (money) or negotiate your shopping list.\n");
  }
  else
  {

    //////// // Update the stock
    //////// // Update the stock
    //////// // Update the stock
    //////// // Update the stock
    //////// // Update the stock
    //////// // Update the stock
    //////// // Update the stock
    //////// // Update the stock
    //////// // Update the stock
    //////// // Update the stock
    //////// // Update the stock
    //////// // Update the stock
    //////// // Update the stock

    printf("After shopping the remaining money will be €%.2f. \n", (cust.budget - total_cost));
  };
}

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
  struct Shop shop = createAndStockShop();                              // This struct calls the method that will read data from a file.
  struct Customer customer_A = create_customer("../customer_good.csv"); // This struct calls the method that will read data from a file.

  // show customer's shopping list by calling relevant method
  process_order(customer_A, shop);

  return 0;
}

// ----- ----- -----
// Option 3 - process customer B (insufficient funds case) shopping
void customer_B_shopping(void)
{
  // create customer A struct (good case)
  struct Shop shop = createAndStockShop();                                            // This struct calls the method that will read data from a file.
  struct Customer customer_B = create_customer("../customer_insufficient_funds.csv"); // This struct calls the method that will read data from a file.

  // show customer's shopping list by calling relevant method
  process_order(customer_B, shop);

  return 0;
}

// ----- ----- -----
// Option 4 - process customer A (exceeding order case) shopping
void customer_C_shopping(void)
{
  // create customer A struct (good case)
  struct Shop shop = createAndStockShop();                                         // This struct calls the method that will read data from a file.
  struct Customer customer_C = create_customer("../customer_exceeding_order.csv"); // This struct calls the method that will read data from a file.

  // show customer's shopping list by calling relevant method
  process_order(customer_C, shop);

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

  system("cls");   // for Windows systems
  system("clear"); // for Linux systems

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
      customer_B_shopping(); // initially insufficient funds case
      break;
    case 4:
      customer_C_shopping(); // initially exceeding order case
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
