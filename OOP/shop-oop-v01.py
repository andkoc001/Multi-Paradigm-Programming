# Shop simulator in Python OOP v01
# Author: Andrzej Kocielski
# Multi-Paradigm Programming, GMIT 2020
# Lecturer: dr Dominic Carr


'''
# ===== ===== ===== ===== ===== =====
# Importing external libraries
# ===== ===== ===== ===== ===== =====
'''

import os
import csv

'''
# ===== ===== ===== ===== ===== =====
# Definiton of classes
# ===== ===== ===== ===== ===== =====
'''

# ----- ----- ----- ----- -----
# Product class
# ----- ----- ----- ----- -----


class Product:

    def __init__(self, name, price=0):
        self.name = name
        self.price = price

    def __repr__(self):
        return f'NAME: {self.name} PRICE: {self.price:.2f}'

# ----- ----- ----- ----- -----
# ProductStock class
# ----- ----- ----- ----- -----


class ProductStock:

    def __init__(self, product, quantity):
        self.product = product
        self.quantity = quantity

    def name(self):
        return self.product.name

    def unit_price(self):
        return self.product.price

    def cost(self):
        return self.unit_price() * self.quantity

    def __repr__(self):
        return f"{self.product} QUANTITY: {self.quantity:.0f}"

# ----- ----- ----- ----- -----
# Customer class
# ----- ----- ----- ----- -----


class Customer:

    def __init__(self, path):
        self.shopping_list = []
        with open(path) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            first_row = next(csv_reader)
            self.name = first_row[0]
            self.budget = float(first_row[1])
            for row in csv_reader:
                name = row[0]
                quantity = float(row[1])
                p = Product(name)
                ps = ProductStock(p, quantity)
                self.shopping_list.append(ps)

    def calculate_costs(self, price_list):
        for shop_item in price_list:
            for list_item in self.shopping_list:
                if (list_item.name() == shop_item.name()):
                    list_item.product.price = shop_item.unit_price()

    def order_cost(self):
        cost = 0

        for list_item in self.shopping_list:
            cost += list_item.cost()

        return cost

    def __repr__(self):

        str = f"{self.name} wants to buy"
        for item in self.shopping_list:
            cost = item.cost()
            str += f"\n{item}"
            if (cost == 0):
                str += f" {self.name} doesn't know how much that costs :("
            else:
                str += f" COST: {cost:.2f}"

        str += f"\nThe cost would be: {self.order_cost():.2f}, he would have {self.budget - self.order_cost():.2f} left"
        return str

# ----- ----- ----- ----- -----
# Shop class
# ----- ----- ----- ----- -----


class Shop:

    def __init__(self, path):
        self.stock = []
        with open(path) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            first_row = next(csv_reader)
            self.cash = float(first_row[0])
            for row in csv_reader:
                p = Product(row[0], float(row[1]))
                ps = ProductStock(p, float(row[2]))
                self.stock.append(ps)

    def __repr__(self):
        str = ""
        str += f'Shop has {self.cash:.2f} in cash\n'
        for item in self.stock:
            str += f"{item}\n"
        return str


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

    s = Shop("../Data/shop_stock.csv")
    # print(s)

    # deafault customer, provided with the box
    c = Customer("../Data/customer.csv")
    c.calculate_costs(s.stock)
    print(c)

    '''
    # Create shop only once, upon the program start
    shop_one = create_and_stock_shop()  # assign data from a file to variable shop_one.
    # print(shop_one) # for testing - ok

    shop_menu(shop_one)  # calls function that displays the shop menu
    '''


'''
# ===== ===== ===== ===== ===== =====
# Check dependencies
# ===== ===== ===== ===== ===== =====
'''

if __name__ == "__main__":
    # execute only if run as a script
    main()
