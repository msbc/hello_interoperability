# Makefile for building cpp_print_capi with the Python C API


PYTHON_CMD ?= $(shell readlink -f $(shell which python))
CXX ?= c++
CXXFLAGS ?= -O3 -Wall -shared -std=c++11 -fPIC
PYTHON_INCLUDES := $(shell $(PYTHON_CMD)-config --includes)
# for linking to pybind11
PYTHON_INCLUDES += $(shell $(PYTHON_CMD) -m pybind11 --includes)
PYTHON_SUFFIX := $(shell $(PYTHON_CMD)-config --extension-suffix)
PYTHON_LD := $(shell $(PYTHON_CMD)-config --ldflags)
LD_FLAGS := $(PYTHON_LD) -Wl,-undefined,dynamic_lookup
OBJ_DIR := obj/
TARGET := $(OBJ_DIR)/cpp_print_capi$(PYTHON_SUFFIX)
SRC := cpp_print_capi.cpp
INSTALL := ../../build/lib

# For debugging variables in Makefile, e.g. by "make print-PYTHON_INCLUDES"
print-%  : ; @echo $* = $($*)

all: $(TARGET)

$(OBJ_DIR):
	@echo "Creating object directory..."
	@mkdir -p $(OBJ_DIR)

$(TARGET): $(SRC) $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(PYTHON_INCLUDES) $(SRC) -o $(TARGET) $(LD_FLAGS)

clean:
	rm -rf $(OBJ_DIR)

test: $(TARGET)
	@echo "Running tests..."
	@echo "Test 1: Basic print"
	cd $(OBJ_DIR) && $(PYTHON_CMD) -c "import cpp_print_capi; cpp_print_capi.cpp_print('Hello World! (Python => C++)')"

install: test
	cp $(OBJ_DIR)/*$(PYTHON_SUFFIX) $(INSTALL)

.PHONY: all clean test install
