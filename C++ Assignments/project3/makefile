a.out: DarkZone.o Queue.o Stack.o
	g++ DarkZone.o Queue.o Stack.o
DarkZone.o: DarkZone.cpp Node.h Queue.h Stack.h
	g++ -c -std=gnu++0x DarkZone.cpp
Queue.o: Queue.cpp Queue.h
	g++ -c -std=gnu++0x Queue.cpp
Stack.o: Stack.cpp Stack.h
	g++ -c -std=gnu++0x Stack.cpp