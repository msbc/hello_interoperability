//==================//
//   Introduction   //
//==================//
// This file is a demonstration of how to implement a simple C++ function that can be
// called from Python. See https://docs.python.org/3/extending/extending.html for more
// information on extending Python with C/C++ code.

//==================//
//   Python C API   //
//==================//
// This macro is defined to ensure that the Python C API sets correct types for sizes.
// As of Python 3.13 it is no longer necessary to define this macro, but it is still a
// good practice, especially for backwards compatibility with older versions of Python.
#define PY_SSIZE_T_CLEAN

// This header file includes the Python C API, which provides functions and macros for
// interacting with Python objects and the Python interpreter from C/C++ code. It can
// redefine some macros and types, so it should be included before any other headers.
#include <Python.h>

// One of the many things that the Python C API does is to define the PyObject type.
// PyObject is a type defined in the Python C API that represents a Python object, and is
// repesented as a struct in C/C++. The PyObject* type is a pointer to a PyObject struct,
// which contains the reference count and type information for the object. The PyObject*
// type is used to represent all Python objects in the C API. Let's just think of it as a
// generic object type that can represent any Python object.

//===================================//
//   C++ Standard Library Includes   //
//===================================//
// This header file includes the C++ standard library's string class, which provides
// functionality for manipulating strings. It is included here to allow the use of

#include <iostream>  // for std::cout, std::endl
#include <string>    // for std::string

//====================//
//   Implementation   //
//====================//

// Create a function that can be called from Python
static PyObject* cpp_print(PyObject* self, PyObject* args) {
  // Declare a char* variable to hold the raw string
  const char* raw_message;

  std::cout << "    cpp_print called" << std::endl;

  // Parse the input tuple to extract the string argument
  // The "s" format character indicates that we expect a string argument
  // The &message argument is where the parsed string will be stored
  //
  // See https://www.mit.edu/people/amliu/vrut/python/ext/parseTuple.html
  // for more information on the format characters used in PyArg_ParseTuple.
  if (!PyArg_ParseTuple(args, "s", &raw_message)) {
    // If parsing fails, print an error message to the console
    std::cerr << "Error: Failed to parse input arguments." << std::endl;
    return nullptr;  // Return NULL (null pointer) if parsing fails
  }

  // Convert the raw C-style string to a std::string
  std::string message(raw_message);

  // Print the message to the console
  std::cout << message << std::endl;
  // Print a message indicating that the function was called
  std::cout << "    cpp_print: Message printed successfully." << std::endl;

  // Return None to indicate successful completion
  Py_RETURN_NONE;
}

// Define the methods in this C++/Python module
static PyMethodDef CppPrintMethods[] = {
    {"cpp_print", cpp_print, METH_VARARGS, "Print a message from Python using C++."},
    {NULL, NULL, 0, NULL}};

// Define the module that Python will use to access the C++ function
static struct PyModuleDef cppprintmodule = {
    PyModuleDef_HEAD_INIT,
    "cpp_print_lib",  // Name of module
    NULL,             // Module docstring
    -1,               // Size of per-interpreter state of the module
    CppPrintMethods};

// Module initialization function
PyMODINIT_FUNC PyInit_cpp_print_lib(void) { return PyModule_Create(&cppprintmodule); }