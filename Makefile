CC = g++
BUILD_DIR = build
CFLAGS = -std=c++17 -pthread -Wall -Werror

TARGET = average_calculator

OBJECTS = \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/utils.o 

mainDependencies = main.cpp \
	utils.hpp

utilsDependencies = utils.cpp \
	utils.hpp


all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: $(mainDependencies)
	$(CC) $(CFLAGS) -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/utils.o: $(utilsDependencies)
	$(CC) $(CFLAGS) -c utils.cpp -o $(BUILD_DIR)/utils.o	

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out