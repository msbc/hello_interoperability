# Makefile for building cpp_print_lib with the Python C API


PYTHON_CMD ?= $(shell readlink -f $(shell which python))
CXX ?= c++
CXXFLAGS ?= -O3 -Wall -shared -std=c++11 -fPIC
PYTHON_INCLUDES := $(shell $(PYTHON_CMD)-config --includes)
PYTHON_SUFFIX := $(shell $(PYTHON_CMD)-config --extension-suffix)
PYTHON_LD := $(shell $(PYTHON_CMD)-config --ldflags)
LD_FLAGS := $(PYTHON_LD) -Wl,-undefined,dynamic_lookup
OBJ := obj
TARGET := $(OBJ)/cpp_print_lib$(PYTHON_SUFFIX)
SRC := cpp_print_capi.cpp
INSTALL := ../../buil/obj

# For debugging variables in Makefile, e.g. by "make print-PYTHON_INCLUDES"
print-%  : ; @echo $* = $($*)

all: $(TARGET)

obj:
	@echo "Creating object directory..."
	@mkdir -p obj

$(TARGET): $(SRC) obj
	$(CXX) $(CXXFLAGS) $(PYTHON_INCLUDES) $(SRC) -o $(TARGET) $(LD_FLAGS)

clean:
	rm -rf obj

test: $(TARGET)
	@echo "Running tests..."
	@echo "Test 1: Basic print"
	cd $(OBJ) && $(PYTHON_CMD) -c "import cpp_print_lib; cpp_print_lib.cpp_print('Hello World! (Python => C++)')"

install: test
	cp $(OBJ)/*$(PYTHON_SUFFIX) $(INSTALL)

.PHONY: all clean test install
