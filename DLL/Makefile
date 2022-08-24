DLL : DLL_main.o libDLL.a
	g++ -o DLL DLL_main.o -L. -lDLL

libDLL.a : DLL.o
	ar rc libDLL.a DLL.o

DLL.o : DLL.cpp
	g++ -c DLL.cpp

DLL_main.o : DLL_main.cpp
	g++ -c DLL_main.cpp

clean :
	rm -f *.o *.a main DLL_main
