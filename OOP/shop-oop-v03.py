# Shop simulator in Python OOP v03
# Author: Andrzej Kocielski
# GitHub:
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
        return f"Product: {self.name}; \tPrice: {self.price:.2f}"

# ----- ----- ----- ----- -----
# Product_stock class
# ----- ----- ----- ----- -----


class Product_stock:

    def __init__(self, product, quantity):
        self.product = product
        self.quantity = quantity

    # below is just a convenience method that allows using 'name' rather than 'self.product.name' (self is instance of the class)
    def name(self):
        return self.product.name

    def unit_price(self):
        return self.product.price

    def cost(self):
        return self.unit_price() * self.quantity

    def __repr__(self):
        # self.product below is an instance of a class
        return f"{self.product} \tAvailable amount: {self.quantity:.0f}"

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
                ps = Product_stock(p, quantity)
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

    # ----- ----- ----- ----- -----
    # Create shop - read data from file
    # ----- ----- ----- ----- -----
    def __init__(self, path):
        self.stock = []
        with open(path) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            first_row = next(csv_reader)
            self.cash = float(first_row[0])
            for row in csv_reader:
                p = Product(row[0], float(row[1]))
                ps = Product_stock(p, float(row[2]))
                self.stock.append(ps)

    # ----- ----- ----- ----- -----
    # The shop self representation
    # ----- ----- ----- ----- -----

    def __repr__(self):
        str = ""
        str += f"\nShop has {self.cash:.2f} in cash\n"
        print("+" * 15)
        for item in self.stock:
            str += f"{item}\n"

        return str

    # ----- ----- ----- ----- -----
    # The shop menu and main program functions
    # ----- ----- ----- ----- -----

    def display_menu(self):

        while True:  # this is a 'forever' loop, unless interupted (break)

            # Main menu screen
            print("")
            print("+" * 15)
            print("Shop Main Menu (Python OOP):")
            print("+" * 15)
            print("1 - Shop status")
            print("2 - Customer A - good case")
            print("3 - Customer B - insufficient funds case")
            print("4 - Customer C - exceeding order case")
            print("5 - Interactive mode")
            print("9 - Exit application\n")
            print("NB: The sequence of the customers being processed might affect the initial case of the customers.")
            print("+" * 15)

            # Request input from the user, assign to variable choice
            choice = input("Enter your choice: ")

            if (choice == "1"):
                print("in display_menu option 1 ")  # for testing - ok
                print(self)  # for testing - ok
                # print_shop(shop)
                # display_menu()

            elif (choice == "2"):
                print("    in display_menu option 2 ")  # for testing - ok

                # # create customer A struct (good case)
                # customer_A = create_customer("../Data/customer_good.csv")  # read data from a file

                # # print customer details and shopping list
                # total_cost = print_customers_details(customer_A, shop)

                # # show customer's shopping list by calling relevant method
                # process_order(customer_A, shop, total_cost)

                # display_menu()

            elif (choice == "3"):
                print("    in display_menu option 3 ")  # for testing - ok
                # # create customer B struct (good case)
                # customer_B = create_customer("../Data/customer_insufficient_funds.csv")  # read data from a file

                # # print customer details and shopping list
                # total_cost = print_customers_details(customer_B, shop)

                # # show customer's shopping list by calling relevant method
                # process_order(customer_B, shop, total_cost)

                # display_menu()

            elif (choice == "4"):
                print("    in display_menu option 4 ")  # for testing - ok
                # # create customer C struct (good case)
                # customer_C = create_customer("../Data/customer_exceeding_order.csv")  # read data from a file

                # # print customer details and shopping list
                # total_cost = print_customers_details(customer_C, shop)

                # # show customer's shopping list by calling relevant method
                # process_order(customer_C, shop, total_cost)

                # display_menu()

            elif (choice == "5"):

                print("   in display_menu option 5 ")  # for testing - ok
                # Welcoming message
                print("Interactive shopping mode")
                print("-------------------------")

                # # get user's name
                # customer_name = input("What's your name, good customer?: ")
                # print(f"Welcome, {customer_name}. ")

                # # get user's budget
                # budget = float(
                #     input("Enter your budget in whole Euros (without cents): "))

                # # go to the interactive mode
                # interactive_mode(shop, budget)

                # display_menu()

            elif (choice == "9"):  # Exit condition
                print("")
                break

            else:
                print("Wrong key, try again.")
                # display_menu(self)


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

    # Create shop only once, upon the program start; assign data from a file to variable shop_one.
    shop_one = Shop("../Data/shop_stock.csv")
    # print(shop_one)  # for testing - ok

    # calls function that displays the shop menu
    shop_one.display_menu()

    '''
    # deafault customer, provided in the box
    c = Customer("../Data/customer.csv")
    c.calculate_costs(shop_one.stock)
    print(c)
    '''


'''
# ===== ===== ===== ===== ===== =====
# Check dependencies
# ===== ===== ===== ===== ===== =====
'''

if __name__ == "__main__":
    # execute only if run as a script
    main()
