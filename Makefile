CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -Werror -O2
CPPFLAGS ?= -Iinclude

TARGET := pipeline_simulator
SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

src/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

test: $(TARGET)
	./tests/smoke_test.sh

clean:
	rm -f $(OBJECTS) $(TARGET)
