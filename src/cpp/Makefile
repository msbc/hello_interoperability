# Makefile for building cpp_print_capi with the Python C API

# Get full/abs path of the Python executable and expand (sym)links
PYTHON_CMD ?= $(shell readlink -f $(shell which python))
# Set C++ compiler command if not already set
CXX ?= c++
# Set C++ compiler flags if not already set (we need `-shared` here)
CXXFLAGS ?= -O3 -Wall -shared -std=c++11 -fPIC
# Set up includes for Python C API
PYTHON_INCLUDES := $(shell $(PYTHON_CMD)-config --includes)
# Set up includes for pybind11 package
# Note: pybind11 is a header-only library, so we don't need to link against it
PYTHON_INCLUDES += $(shell $(PYTHON_CMD) -m pybind11 --includes)
# Get the Python extension suffix (e.g. cpython-310-darwin.so)
PYTHON_SUFFIX := $(shell $(PYTHON_CMD)-config --extension-suffix)
# Get the Python linker flags
PYTHON_LD := $(shell $(PYTHON_CMD)-config --ldflags)
# Set up the object directory
OBJ_DIR := obj/
# Make list of all source files
# Note: we assume all source files are in the current directory
SRC_FILES := $(wildcard *.cpp)
# Make list of all object files
OBJ_FILES := $(addprefix $(OBJ_DIR),$(notdir $(SRC_FILES:.cpp=$(PYTHON_SUFFIX))))
INSTALL := ../../build/lib
# Set up leading compiler flags
COMMPILER_FLAGS := $(CPPFLAGS) $(CXXFLAGS) $(PYTHON_INCLUDES)
# Set up all linker flags
LD_FLAGS := $(PYTHON_LD) -Wl,-undefined,dynamic_lookup

# For debugging variables in Makefile, e.g. by "make print-PYTHON_INCLUDES"
print-%  : ; @echo $* = $($*)

all: $(OBJ_FILES)

$(OBJ_DIR):
	@echo "Creating object directory..."
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%$(PYTHON_SUFFIX) : %.cpp $(OBJ_DIR)
	$(CXX) $(COMMPILER_FLAGS) $< -o $@ $(LD_FLAGS)

clean:
	rm -rf $(OBJ_DIR)

test: $(OBJ_FILES)
	@echo "Running tests..."
	@echo "Test 1: Basic print"
	cd $(OBJ_DIR) && $(PYTHON_CMD) -c "import cpp_print_capi; cpp_print_capi.cpp_print('Hello World! (Python => C++)')"

install: test
	cp $(OBJ_DIR)/*$(PYTHON_SUFFIX) $(INSTALL)

.PHONY: all clean test install
