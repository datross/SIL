# Types

Base types:

- int
- float
- string
- *Is this a good idea?* [] : a collection of ressources

# Expressions

## Operators (by decreasing priority order)

- '||'
- '&&'
- '!='
- '=='
- '>='
- '<='
- '>'
- '<'
- '+'
- '-'
- '*' 
- '/'

## Access a variable

	<variable_name>

## Call a function

	<function_name>(<expression>, <expression>, ...)

# Block

	{
		<program>
		<program>
		...
	}

# Programs


## Declare a variable

	<type> <variable_name>

## Assign value to variable

	<variable_name> = <expression>

## if / else

	if(<expression>)
		<block>

or

	if(<expression>)
		<block>
	else
		<block>

## while

	while(<expression>)
		<block>

## Block

A program can be a block

	<block>

## return statement

A function must return an expression (for the moment?)

	return <expression>

## Declare a function (is it a program?)

	<type> <function_name>(<type> <arg1_name>, <type> <arg2_name>, ...)
	{
		<program>
		<program>
		...
	}

# Code example :

	// This is a comment. 
	// Less or more game written in SIL.

	int inputNumber()
	{
		print("Your guess?")
		return int(input())
	} 

	int main(int argc, string[] argv)
	{
		print("Less or more game !")

		int number
		int choice

		number = random(0,100)
		choice = intputNumber()

		while(choice != number)
		{
			if(choice < number)
			{
				print("It's more!")
			}
			else
			{
				print("It's less!")
			}
			choice = intputNumber()
		}
		
		print("Bravo!")
		
		return 0
	}

# Abstract Syntax Tree

A root of a tree has to be a function.
Here are the different node types of a tree :

## Function 

_children:_

- expression 1
- ...
- expression 2

##


    
