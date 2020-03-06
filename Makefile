CXXFLAGS = -Wall -g -Wwrite-strings -pedantic -std=gnu++17 -D usedmake
CXX = g++
RM = rm -rf

all: AoC_2019_day12/main
run:
	AoC_2019_day12/main

.PHONY: clean

clean:
	$(RM) AoC_2019_day12/main

