a.out: Longhorn.o Checking.o Savings.o Account.o
	g++ Longhorn.o Checking.o Savings.o Account.o
Longhorn.o: Longhorn.cpp Account.h Checking.h Savings.h
	g++ -c -std=gnu++0x Longhorn.cpp
Checking.o: Checking.cpp Checking.h
	g++ -c -std=gnu++0x Checking.cpp
Savings.o: Savings.cpp Savings.h
	g++ -c -std=gnu++0x Savings.cpp
Account.o: Account.cpp Account.h
	g++ -c -std=gnu++0x Account.cpp