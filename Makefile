CXX := g++

SRC_DIR := src
INC_DIR := include

SRCS := $(wildcard $(SRC_DIR)/*.cpp)

TARGET := analyzer

CXXFLAGS := -I$(INC_DIR)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -o $(TARGET) $(CXXFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
