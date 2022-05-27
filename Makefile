socketclient: main.o
	g++ main.o -o socketclient -lws2_32

main.o: main.cpp
	g++ -c main.cpp

# socketclient: socketclient.o
# 	g++ socketclient.o -o socketclient -lws2_32

# socketclient.o: socketclient.cpp
#     g++ -c socketclient.cpp
