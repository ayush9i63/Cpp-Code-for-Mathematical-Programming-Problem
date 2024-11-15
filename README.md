# Linear Programming Solver in C++

This repository contains implementations of various linear programming algorithms in C++. The methods implemented include:

- **Simplex Method**
- **Big-M Method**
- **Revised Simplex Method**
- **Dual Simplex Method**
- **Two-Phase Simplex Method**

## Overview

Linear programming is a mathematical technique for optimizing a linear objective function, subject to linear equality and inequality constraints. These methods are widely used in operations research, optimization, and computational mathematics.

## Features

- Handles both **maximization** and **minimization** problems.
- Supports constraints in the form of `<=`, `>=`, or `=`.
- Uses arrays for input and output management (no vectors used).
- Designed for efficiency and clarity.
- Easy-to-read input-output format for seamless integration into other projects.

## Folder Structure

```plaintext
.
├── Simplex/             # Code for the Simplex Method
├── BigM/                # Code for the Big-M Method
├── RevisedSimplex/      # Code for the Revised Simplex Method
├── DualSimplex/         # Code for the Dual Simplex Method
├── TwoPhaseSimplex/     # Code for the Two-Phase Simplex Method
└── README.md            # Repository overview
