libMemoryManager.a: MemoryManager.o AllocationAlgorithms.o bitmap.o ProcessList.o
	ar cr libMemoryManager.a MemoryManager.o AllocationAlgorithms.o bitmap.o ProcessList.o

MemoryManager.o: MemoryManager.cpp
	c++ -Wall -g -c MemoryManager.cpp -o MemoryManager.o

AllocationAlgorithms.o: AllocationAlgorithms.cpp
	c++ -Wall -g -c AllocationAlgorithms.cpp -o AllocationAlgorithms.o

bitmap.o: bitmap.cpp
	c++ -Wall -g -c bitmap.cpp -o bitmap.o

ProcessList.o: ProcessList.cpp
	c++ -Wall -g -c ProcessList.cpp -o ProcessList.o
