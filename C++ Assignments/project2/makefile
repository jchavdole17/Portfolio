a.out: PasswordDriver.o PasswordManager.o
	g++ PasswordDriver.o PasswordManager.o 
PasswordDriver.o: PasswordDriver.cpp PasswordManager.h
	g++ -c -std=gnu++0x PasswordDriver.cpp
PasswordManager.o: PasswordManager.cpp PasswordManager.h
	g++ -c -std=gnu++0x PasswordManager.cpp