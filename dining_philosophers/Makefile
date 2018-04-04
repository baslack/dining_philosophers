CXX_LINK = -pthread
SRCDIR = ./src/
INCDIR = ./include/
CXX_FLAGS = -std=c++11 -Wall -I $(INCDIR)

all:  dining deadlocked starving semaphore

OBJA = $(SRCDIR)dining_philosophers.cpp $(SRCDIR)Barrier.cpp $(INCDIR)Barrier.hpp
dining: 
	g++ $(CXX_FLAGS) -o ./dining_philosophers $(OBJA) $(CXX_LINK)

OBJB = $(SRCDIR)deadlocked_philosophers.cpp $(SRCDIR)Barrier.cpp $(INCDIR)Barrier.hpp
deadlocked: 
	g++ $(CXX_FLAGS) -o ./deadlocked_philosophers $(OBJB) $(CXX_LINK)

OBJC = $(SRCDIR)starving_philosophers.cpp $(SRCDIR)Barrier.cpp $(INCDIR)Barrier.hpp
starving: 
	g++ $(CXX_FLAGS) -o ./starving_philosophers $(OBJC) $(CXX_LINK)

OBJD = $(SRCDIR)semaphore_philosophers.cpp $(SRCDIR)Barrier.cpp $(INCDIR)Barrier.hpp
semaphore: 
	g++ $(CXX_FLAGS) -o ./semaphore_philosophers $(OBJD) $(CXX_LINK)

clean:
	rm ./dining_philosophers ./deadlocked_philosophers ./starving_philosophers ./semaphore_philosophers