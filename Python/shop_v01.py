# Shop simulator in Python procedural v01
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
# Definition of functions
# ===== ===== ===== ===== ===== =====
'''


def create_and_stock_shop():
    s = Shop()
    with open('../Data/shop_stock.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        first_row = next(csv_reader)
        s.cash = float(first_row[0])
        for row in csv_reader:
            p = Product(row[0], float(row[1]))
            ps = ProductStock(p, float(row[2]))
            s.stock.append(ps)
            # print(ps)
    return s


def read_customer(file_path):
    with open(file_path) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        first_row = next(csv_reader)
        c = Customer(first_row[0], float(first_row[1]))
        for row in csv_reader:
            name = row[0]
            quantity = float(row[1])
            p = Product(name)
            ps = ProductStock(p, quantity)
            c.shopping_list.append(ps)
        return c


def print_product(p):
    print(f'\nPRODUCT NAME: {p.name} \nPRODUCT PRICE: {p.price}')


def print_customer(c):
    print(f'CUSTOMER NAME: {c.name} \nCUSTOMER BUDGET: {c.budget}')

    for item in c.shopping_list:
        print_product(item.product)

        print(f'{c.name} ORDERS {item.quantity} OF ABOVE PRODUCT')
        cost = item.quantity * item.product.price
        print(f'The cost to {c.name} will be €{cost}')


def print_shop(s):
    print(f'Shop has {s.cash} in cash')
    for item in s.stock:
        print_product(item.product)
        print(f'The Shop has {item.quantity} of the above')

#s = create_and_stock_shop()
# print_shop(s)


c = read_customer("../Data/customer_good.csv")
print_customer(c)


'''
# ===== ===== ===== ===== ===== =====
# The shop main menu
# ===== ===== ===== ===== ===== =====
'''


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


'''
# ===== ===== ===== ===== ===== =====
# The main function - start of the program 
# ===== ===== ===== ===== ===== =====
'''


def shop_menu(sh):
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
            # printShop()
            display_menu()

        elif (choice == "2"):
            print("inside option 2\n")
            # get_countries_by_ind_year()
            display_menu()

        elif (choice == "3"):
            print("inside option 3\n")
            # add_new_person()
            display_menu()

        elif (choice == "4"):
            print("inside option 4\n")
            # view_countries_by_name()
            display_menu()

        elif (choice == "5"):
            print("inside option 5\n")
            # view_countries_by_population()
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
    os.system("cls")   # for Windows systems
    os.system("clear")  # for Linux systems

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
