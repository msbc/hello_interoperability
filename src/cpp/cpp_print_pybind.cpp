// "pybind11 is a lightweight header-only library that exposes C++ types in Python and
// vice versa, mainly to create Python bindings of existing C++ code"
// https://pybind11.readthedocs.io/en/stable/
//
// Requires pybind11 to be installed in your Python environment (pip/conda).
#include <pybind11/pybind11.h>

// C++ Standard Library includes
#include <iostream>

// Namespace alias (think `import numpy as np` in Python)
namespace py = pybind11;

void cpp_print(const std::string& message) {
  std::cout << "    cpp_print called (pybind)" << std::endl;
  std::cout << message << std::endl;
  std::cout << "    cpp_print: Message printed successfully (pybind)." << std::endl;
}

// PYBIND11_MODULE(<module_name>, <module>) is a macro that defines a Python module.
// `m` here acts a lot like `self` in Python, representing the module itself.
PYBIND11_MODULE(cpp_print_pybind, m) {
  m.doc() = "C++ print module implimented with pybind11";  // optional module docstring
  m.def("cpp_print", &cpp_print, "Print a message from Python using C++");
}
