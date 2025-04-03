#! /usr/bin/env python
# -*- coding: utf-8 -*-

# Add the directory containing the C++ shared library to the system path
# This is necessary to load the shared library from Python
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), 'obj')))

# Import our `cpp_print_capi` module
import cpp_print_capi  # noqa (my linter doesn't like where this is)

cpp_print_capi.cpp_print("Hello World! (Python => C++ with C API)")


# Import our `cpp_print_pybind` module
import cpp_print_pybind  # noqa (my linter doesn't like where this is)

cpp_print_pybind.cpp_print("Hello World! (Python => C++ with PyBind11)")
