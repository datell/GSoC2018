# Google Summer of Code 2018 - Faster Matrix Algebra for ATLAS #

This repository contains a very first draft for an efficient implementation of symmetric matrices using the C++ library Eigen. More information about the project and the design of the contained class SymmetricMatrix can be found in the project documentation that can be build using ``make doc-proj``.

## Structure ##

The repository is structured as follows

    GSoC2018
    ├── README.markdown             
    ├── makefile                 
    ├── doc     
    |   ├── doxygen
    │   │   ├── Doxyfile
    │   │   └── mainpage.dox   
    │   ├── latex
    │   │   └── Project.tex
    │   └── img
    ├── include
    │   ├── SymmetricMatrix.h
    │   └── eigen3
    ├── benchmark
    │   ├── add_fixed.cc
    │   ├── add_dynamic.cc
    │   ├── mult_fixed.cc
    │   └── mult_dynamic.cc
    ├── examples
    │   ├── example1.cc
    │   ├── example2.cc
    │   ├── example3.cc
    │   ├── example4.cc
    │   └── example5.cc
    └── bin

## How to build ##

The SymmetricMatrix class is header only, therefore you can just include the file ``./include/SymmatricMatrix.h`` and give it a try.
Since this is an experimental project, Eigen is included in the ``./include`` directory. There is no need to have it in one of your include directories. Actually you can build everything except the Google benchmarks with nothing installed but a compiler that supports C++11.
If you want to build any of the code example contained in the repository by hand, make sure you add ``./include`` to your include path using, e.g., ``g++ -std=c++11 -I include source.cc``.

Using GNU Make you can build the contained examples, benchmarks, tests and the documentation. The following make directives are available:

    all                 Builds everything except documentation
    example             Builds the examples
    benchmark           Builds the benchmarks using Google's benchmark library
    test                Builds tests
    doc-code            Builds the Doxygen documentation of SymmetricMatrix as HTML
    doc-proj            Builds documentation about the project and its design as PDF
    clean               Removes built executables and documentation

E.g., running ``make example`` builds all files contained in [./examples](./examples) in ./bin. 

The make directives ``make doc-code`` and ``make doc-proj`` create symbolic links in the directory root called ``SymmetricMatrix.html`` and ``Project.pdf``.

### Dependencies ###

To build examples, benchmarks and tests a C++ compiler that supports C++11 is required. As default compiler ``gcc`` is chosen but you can change the [makefile](makefile) to other compilers like ``clang`` or ``icc``.

To build the Google benchmarks you need to ensure that the corresponding library and headers are available. See [here](https://github.com/google/benchmark) for further information about the Google benchmark library.

To build the Doxygen documentation of the SymmetricMatrix class Doxygen must be installed. See [here](https://www.stack.nl/~dimitri/doxygen/) for further information about Doxygen.

To build the project documentation pdflatex is required. See [here](https://www.tug.org/applications/pdftex/) for further information about pdflatex.

## Examples ##

Several examples that demonstrate all available features of the SymmetricMatrix class can be found in [./example](./example). In detail the following topics are covered:

**[Example 1](./examples/example1.cc)**
- Construct an instance of ``SymmetricMatrix`` from an instance of ``Eigen::Matrix`` (fixed size)
- Print an instance of ``SymmetricMatrix`` into console
- Test if an instance of ``Eigen::Matrix`` is symmetric
- Access elements of the symmetric matrix directly and change their value

**[Example 2](./examples/example2.cc)**
- Difference between matrices with fixed and with dynamic size
- Typedefs for several classes of class template SymmetricMatrix
- Constructing symmetric matrices filled with random values

**[Example 3](./examples/example3.cc)**
- Addition and subtraction for two instances of symmetric matrix
- Addition and subtraction for symmetric matrices and arbitrary matrices

**[Example 4](./examples/example4.cc)**
- Multiplication for two instances of symmetric matrix
- Multiplication of symmetric and arbitrary matrices

**[Example 5](./examples/example5.cc)**
- Runtime exceptions and compile-time errors

## Benchmarks ##

If the Google benchmark library is installed the following benchmarks can be run. Since benchmarking is a complex task this repository does not contain standalone benchmarks. They would most likely provide unreliable results.

Note that using the makefile requires the Google benchmark header to be contained in one of your include paths. If not so, change the makefile or try to compile the benchmarks *by hand*.

All benchmark results including their graphical representations can be found in the project documentation.

**[add_fixed.cc](benchmarks/add_fixed.cc):** Measures the time consumption of addition of instances of SymmetricMatrix and Eigen::Matrix for several fixed dimensions using the Google benchmark library.

**[add_dynamic.cc](benchmarks/add_dynamic.cc):** Measures the time consumption of addition of instances of SymmetricMatrix and Eigen::Matrix for several dynamic dimensions using the Google benchmark library.

**[mult_fixed.cc](benchmarks/mult_fixed.cc):** Measures the time consumption of multiplication of instances of SymmetricMatrix and Eigen::Matrix for several fixed dimensions using the Google benchmark library.

**[mult_dynamic.cc](benchmarks/mult_dynamic.cc):** Measures the time consumption of multiplication of instances of SymmetricMatrix and Eigen::Matrix for several dynamic dimensions using the Google benchmark library.

## Tests ##

All tests work by first constructing an instance of Eigen::Matrix, make sure that this instance is symmetric and constructing instances of SymmetricMatrix by passing the constructed Eigen::Matrix. Then any operation is performed for both the SymmetricMatrix and the Eigen::Matrix. If both operations yield the same result, the test is passed. In fact the all tests check if instances of SymmetricMatrix behave like semantically identical instances of Eigen::Matrix.

These four tests are included:

**[fixed_fixed.cc](tests/fixed_fixed.cc):** Tests operations on symmetric matrices of fixed dimension with symmetric matrices of fixed dimension. Several data types and matrix dimensions are tested.

**[fixed_dynamic.cc](tests/fixed_fixed.cc):** Tests operations on symmetric matrices of fixed dimension with symmetric matrices of dynamic dimension. Several data types and matrix dimensions are tested.

**[dynamic_dynamic.cc](tests/fixed_fixed.cc):** Tests operations on symmetric matrices of dynamic dimension with symmetric matrices of dynamic dimension. Several data types and matrix dimensions are tested.

**[exception.cc](tests/exception.cc):** Tests edge cases that should throw exception.