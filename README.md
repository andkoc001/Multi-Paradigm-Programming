# Multi-Paradigm Programming

Multi-Paradigm Programing module - assignment project, GMIT 2020

Lecturer: dr Dominic Carr

>Author: **Andrzej Kocielski**  
>Github: [andkoc001](https://github.com/andkoc001/)  
>Email: G00376291@gmit.ie, and.koc001@gmail.com

___

## Introduction

This is my assignment project to Multi-Paradigm Programming module, Galway-Mayo Institute of Technology, 2020.

This GitHub repository documents my research, project progress (git version control) and findings of the assignment project - application of various programming paradigms. The intention of the project is to get familiar with selected paradigms approches in solving programming problems.

> The term _programming paradigm_ is the style or the way of thinking about and approaching problems. - Lecture's notes

The task of this project assignment is to apply two different programming paradigmns to solve a practical problem, so that each of the paradigms would show their advantages and disadvantages. The selected paradigms are:

a. procedural paradigm - C language,
b. procedural paradigm - Python language,
c. object oriented programming - Python language.

## Simulation of a shop

The practical problem is to  built a simulation of a shop. The program is to simulate the cash and stock flow, monitor customers expenditure, etc. The following functionality is included into the simulation:

1. Entities: Shop, Customer(s), Product(s), Stock
2. Model the entities
3. Read in stock from a file
4. Print shop info (stock, cash)
5. Read in customers data from files
6. Print customer info
7. Validate customer's request (budget, available stock)
8. Update the shop data
9. Interactive mode - requests are typed in.

The user experience (UX) should remain the same regardless the paradigm used.

## Application in C - procedural paradigm

C programming language is an example of a procedural programming paradigm. Beacuse of its long legacy, the language may be considered old fashioned and also a relatively low-level in terms of memory management. As a result, a more complicated programs may seem to be excesively cumbersome. There is a necessity of frequent use of the pointers, for example.

One of the reasons of using C language in this project is to appreciate the advancements of more modern paradigm and languages.

## Application in Python - procedural paradigm

Python is a multi-paradigm programming language. One of the supported paradigm is procedural one. The program here was writen in in such a way as to mimic the program writen in C. In order to to achieve that, a data type `dataclass` has been used which resembles C's `struct` data type.

Python, being a more modern and a higher level language than C, is significantly easier to use. This is particularly well seen in relation to the memory management.

## Application in Python - object oreinted programming (OOP) paradigm

Python supports also the object oriented (OOP) programming paradigm. This paradigm avails of several new concepts, which can be very benefitial in dealing with some programming problems. First of all, there are objects, which combine data and the methods. Other important concepts of the OOP paradigm are abstraction, inheritance, encapsulation and polymorphism.

___
Andrzej Kocielski, 2020 - 2021
