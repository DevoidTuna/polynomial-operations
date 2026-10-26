# Polynomial Calculator

> University assignment for the **Logic and Algorithms II** course, made to practice structs and dynamic memory allocation in C++.

Console program that stores polynomials as dynamically allocated arrays of monomials and runs basic operations on them.

## Features

- Show a polynomial formatted (e.g. `3x^2 - 5x + 8`)
- Evaluate a polynomial for a given value
- Add and subtract two polynomials
- Multiply a polynomial by a constant
- Multiply a polynomial by a monomial
- Multiply two polynomials

Every operation returns a new polynomial, with like terms combined and sorted by exponent.

## How it works

- `Monomio`: coefficient (`double`), variable (`char`) and exponent (`int`).
- `Polinomio`: pointer to an array of `Monomio` allocated with `new[]`, plus the number of terms.
- `simplificar`: merges like terms, removes zero terms and sorts by descending exponent.

## Build and run

```bash
g++ main.cpp -o poli
./poli
```

The program asks for the variable letter and the terms (coefficient and exponent) of two polynomials, P and Q, then shows a menu with the operations. The interface is in Portuguese.

## Example

With `P = 3x^2 - 5x + 8` and `Q = -2x + 1`:

```
P + Q = 3x^2 - 7x + 9
P - Q = 3x^2 - 3x + 7
P * (-2) = -6x^2 + 10x - 16
P * Q = -6x^3 + 13x^2 - 21x + 8
```
