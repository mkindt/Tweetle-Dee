
CPP = g++
CFLAGS = -Wall -Wextra -Werror


twits: twitFeed.cpp
	$(CPP) $(CFLAGS) -o twits twitFeed.cpp

clean:
	rm -f *.o;
	rm -f twits;
	rm -f *~;
