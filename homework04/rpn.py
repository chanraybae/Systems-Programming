#!/usr/bin/env python3

import os
import sys

# Globals

OPERATORS = {'+', '-', '*', '/'}
stack = []

# Functions

def usage(status=0):
    ''' Display usage message and exit with status. '''
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname}

By default, {progname} will process expressions from standard input.''')
    sys.exit(status)

def error(message):
    ''' Display error message and exit with error. '''
    print(message, file=sys.stderr)
    sys.exit(1)

def evaluate_operation(operation, operand1, operand2):
    ''' Return the result of evaluating the operation with operand1 and
    operand2.

    >>> evaluate_operation('+', 4, 2)
    6

    >>> evaluate_operation('-', 4, 2)
    2

    >>> evaluate_operation('*', 4, 2)
    8

    >>> evaluate_operation('/', 4, 2)
    2.0
    '''
    if operation == '+':
        return (operand1 + operand2)
    elif operation == '-':
        return (operand1 - operand2)
    elif operation == '*':
        return (operand1 * operand2)
    elif operation == '/':
        return (operand1 / operand2)

def evaluate_expression(expression):
    ''' Return the result of evaluating the RPN expression.

    >>> evaluate_expression('4 2 +')
    6.0

    >>> evaluate_expression('4 2 -')
    2.0

    >>> evaluate_expression('4 2 *')
    8.0

    >>> evaluate_expression('4 2 /')
    2.0

    >>> evaluate_expression('4 +')
    Traceback (most recent call last):
    ...
    SystemExit: 1

    >>> evaluate_expression('a b +')
    Traceback (most recent call last):
    ...
    SystemExit: 1
    '''
    expression = expression.split(' ')

    for element in expression:
        if element in OPERATORS:
            if len(stack) < 2:
                error("Stack doesn't have enough operands!")

            a = stack.pop()
            b = stack.pop()
            c = evaluate_operation(element, b, a)
            stack.append(c)

        else:
            try:
                element = float(element)
                stack.append(element)
            except ValueError:
                error("Float conversion was not successful!")

    return stack.pop()

def main():
    ''' Parse command line arguments and process expressions from standard
    input. '''
    if len(sys.argv) == 2:
        if sys.argv[1] == '-h':
            usage()
        else:
            usage(1)

    result = 0
    for line in sys.stdin:
        line = line.strip()
        result_line = evaluate_expression(line)
        print(result_line)


# Main Execution

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
