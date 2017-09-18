# Variables
 SOURCES := $(shell find PEPAS/src -name '*.cpp')
 TEMP := $(subst PEPAS/src/,obj/src/,$(SOURCES))
 OBJECTS := $(subst .cpp,.o,$(TEMP))
 COMPILER := g++
 LINKING_FLAGS := -std=c++11 -Wall -I PEPAS/headers/ -o
 COMPILING_FLAGS := -g -std=c++11 -Wall -I PEPAS/headers/ -c -o
 LIBRARIES := -pthread

# Target
 all: directories main

 main: $(OBJECTS)
	$(COMPILER) $(LINKING_FLAGS) $@ $^ $(LIBRARIES)

 directories:
	mkdir ./obj
	find PEPAS/src -type d | sed -e 's/PEPAS/obj/g' | xargs mkdir -p

# Pattern
 obj/src/%.o: PEPAS/src/%.cpp
	$(COMPILER) $(COMPILING_FLAGS) $@ $<

# Clean object files and binary
 clean:
	rm -r ./obj
	rm main

 cleanlog:
	rm log.txt

.PHONY: all clean main

