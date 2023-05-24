CFLAGS = -Wall -Wextra -Wno-unused-variable -Wno-sign-compare

dijkstra: dijkstra.cpp Graph_Representation.cpp data_loader.cpp
	g++ $(CFLAGS) dijkstra.cpp Graph_Representation.cpp data_loader.cpp -o dijkstra

dial: dial.cpp Graph_Representation.cpp data_loader.cpp
	g++ $(CFLAGS) dial.cpp Graph_Representation.cpp data_loader.cpp -o dial

clean:
	@rm dijkstra dial