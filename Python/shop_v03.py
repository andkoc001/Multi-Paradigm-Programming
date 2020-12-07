# Shop simulator in Python procedural v03
# Author: Andrzej Kocielski
# Multi-Paradigm Programming, GMIT 2020
# Lecturer: dr Dominic Carr

'''
# ===== ===== ===== ===== ===== =====
# Importing external libraries
# ===== ===== ===== ===== ===== =====
'''

import os
from dataclasses import dataclass, field
from typing import List
import csv

'''
# ===== ===== ===== ===== ===== =====
# Definiton of dataclasses
# ===== ===== ===== ===== ===== =====
'''


@dataclass
# This dataclass defines the data structure (blueprint) for products offered in the shop. It consists of two variables, defined inside.
class Product:
    name: str
    price: float = 0.0


@dataclass
# This dataclass defines the blueprint for products offered in the shop.
class ProductStock:
    # dataclass Product, defined above (i.e. nested dataclasses)
    product: Product
    quantity: int


@dataclass
# This dataclass is used to show the stock both shop and customer.
class ProductQuantity:
    product: Product  # nested dataclasses
    quantity: int


@dataclass
# This dataclass defines the shop entity. Consist of the nested dataclass.
class Shop:
    cash: float = 0.0
    stock: List[ProductStock] = field(default_factory=list)


@dataclass
# Defines the customer blueprint.
class Customer:
    name: str = ""
    budget: float = 0.0
    shopping_list: List[ProductStock] = field(default_factory=list)


'''
# ===== ===== ===== ===== ===== =====
# Definition of the functions
# ===== ===== ===== ===== ===== =====
'''


# ----- ----- ----- ----- -----
# Create shop - read data from file
# ----- ----- ----- ----- -----
def create_and_stock_shop():
    shop = Shop()  # initialise an instance of the Shop dataclass
    with open('../Data/shop_stock.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        first_row = next(csv_reader)
        # reads and assigns amount of cash in shop from file
        shop.cash = float(first_row[0])
        for row in csv_reader:
            # initialise instance of Product; assigns product name [0] and price [1]
            p = Product(row[0], float(row[1]))
            # initialise instance of ProductStock; assigns product stock
            ps = ProductStock(p, float(row[2]))
            shop.stock.append(ps)  # add subsequent items to the list
            # print(ps)
    return shop


# ----- ----- ----- ----- -----
# Create customer - read data from file
# ----- ----- ----- ----- -----
def create_customer(file_path):
    # print("inside 'create customer' function")  # for testing - ok
    # initialise an instance of the Customer dataclass - is this line necessary?
    customer = Customer()
    with open(file_path) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        first_row = next(csv_reader)
        # reads and assigns name [0] and budget [1] from file
        customer = Customer(first_row[0], float(first_row[1]))
        # print(f"1: Printing customer's name: {str(customer.name)} and budget: {customer.budget:.2f}") # for testing - ok
        for row in csv_reader:
            name = row[0]
            quantity = float(row[1])
            p = Product(name)
            ps = ProductStock(p, quantity)
            customer.shopping_list.append(ps)

        # print(f"Printing customer's shopping list: {customer.shopping_list}") for testing - ok
        # for item in customer.shopping_list: # for testing - ok
            # print_product(item.product)

        return customer


# ----- ----- ----- ----- -----
# Printing product info
# ----- ----- ----- ----- -----
def print_product(prod):
    # if the price is defined (we are showing the shop stock), then both name and price are shown otherwise(we are showing the customer shopping list) only product name is showm
    if prod.price == 0:
        print(f"Product: {prod.name};")
    else:
        print(f"Product: {prod.name}; \tPrice: €{prod.price:.2f}\t", end="")


# ----- ----- ----- ----- -----
# ----- ----- ----- ----- -----
def print_customer(c):
    print(f'CUSTOMER NAME: {c.name} \nCUSTOMER BUDGET: {c.budget}')

    for item in c.shopping_list:
        print_product(item.product)

        print(f'{c.name} ORDERS {item.quantity} OF ABOVE PRODUCT')
        cost = item.quantity * item.product.price
        print(f'The cost to {c.name} will be €{cost}')


# ----- ----- ----- ----- -----
# Print out of the shop details
# ----- ----- ----- ----- -----
def print_shop(sh):  # takes 'shop' dataclass as a parameter
    # Show shop detials
    print(sh)  # for testing - ok
    print(f"\nShop has {sh.cash:.2f} in cash")
    print("==== ==== ====\n")
    for item in sh.stock:
        print_product(item.product)
        print(f"Available amount: {item.quantity}")
    print()


'''
c = read_customer("../Data/customer_good.csv")
print_customer(c)
'''

# ----- ----- ----- ----- -----
# The shop main menu
# ----- ----- ----- ----- -----


def display_menu():

    print("")
    print("=" * 15)
    print("Shop Main Menu (Python procedural):")
    print("=" * 15)
    print("1 - Shop status")
    print("2 - Customer A - good case")
    print("3 - Customer B - insufficient funds case")
    print("4 - View Customer C - exceeding order case")
    print("5 - Interactive mode")
    print("9 - Exit application\n")
    print("NB: The sequence of the customers being processed might affect the initial case of the customers.")
    print("=" * 15)


# ----- ----- ----- ----- -----
# The main function - start of the program
# ----- ----- ----- ----- -----


def shop_menu(shop):
    '''
    Shop menu
    '''

    # Main menu screen
    display_menu()

    while True:  # this is a 'forever' loop, unless interupted (break)

        # Request input from the user, assign to variable choice
        choice = input("Enter your choice: ")

        if (choice == "1"):
            print("inside option 1\n")
            print_shop(shop)
            display_menu()

        elif (choice == "2"):
            # print("inside option 2\n") # for testing - ok

            # create customer A struct (good case)
            customer_A = create_customer(
                "../Data/customer_good.csv")  # read data from a file
            # print(customer_A)  # for testing ...

            # print customer details and shopping list

            '''
            struct Customer customer_A = create_customer("../Data/customer_good.csv"); // This struct calls the method that will read data from a file.
            // print customer details and shopping list
            double total_cost = print_customers_details(&customer_A, &sh);

            // show customer's shopping list by calling relevant method
            process_order(&customer_A, &sh, &total_cost);
            '''

            display_menu()

        elif (choice == "3"):
            print("inside option 3\n")
            display_menu()

        elif (choice == "4"):
            print("inside option 4\n")
            display_menu()

        elif (choice == "5"):
            print("inside option 5\n")
            display_menu()

        elif (choice == "9"):  # Exit condition
            print("")
            break

        else:
            display_menu()


'''
# ===== ===== ===== ===== ===== =====
# The main function - start of the program
# ===== ===== ===== ===== ===== =====
'''


def main():
    '''
    This is the main function the program. It defines a starting point and controls all other functionality of the program. It is called automatically at the program start.
    '''

    # Clear screen
    # os.system("cls")   # for Windows systems
    # os.system("clear")  # for Linux systems

    print("\n\n>>> Multi-Paradigm Programming Project by Andrzej Kocielski, 2020 <<<")

    '''
    Create shop only once, upon the program start
    '''
    shop_one = create_and_stock_shop()  # assign data from a file to variable shop_one.
    # print(shop_one) # for testing - ok

    shop_menu(shop_one)  # calls function that displays the shop menu


'''
# ===== ===== ===== ===== ===== =====
# Check dependencies
# ===== ===== ===== ===== ===== =====
'''

if __name__ == "__main__":
    # execute only if run as a script
    main()
