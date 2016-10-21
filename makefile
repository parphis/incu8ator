CC = g++
C11 = -std=c++11
THREAD = -pthread
DEBUG = 
LFLAGS = -Wall
CFLAGS = -Wall -c $(THREAD) $(C11)
OBJS = nc8tr.o displayBase.o displayStdOut.o incu8ator.o sensorBase.o sensorDHT22.o sensoremu.o pugixml.o programWheel.o utils.o elapsedTimeThread.o incu8atorLog.o
EXENAME = nc8tr
EXEC = -o $(EXENAME)
VER = $(EXENAME)_$$(date +'%Y%m%d_%H%M%S')

nc8tr: $(OBJS)
	$(CC) $(DEBUG) $(THREAD) $(C11) $(LFLAGS) $(OBJS) $(EXEC)

nc8tr.o: nc8tr.cpp utils.h incu8ator.h
	$(CC) $(DEBUG) $(CFLAGS) nc8tr.cpp 
displayBase.o: displayBase.cpp displayBase.h displayStdOut.h
	$(CC) $(DEBUG) $(CFLAGS) displayBase.cpp
displayStdOut.o: displayStdOut.cpp displayStdOut.h
	$(CC) $(DEBUG) $(CFLAGS) displayStdOut.cpp
incu8ator.o: incu8ator.cpp incu8ator.h
	$(CC) $(DEBUG) $(CFLAGS) incu8ator.cpp
sensorBase.o: sensorBase.cpp sensorBase.h sensoremu.h sensorDHT22.h
	$(CC) $(DEBUG) $(CFLAGS) sensorBase.cpp
sensorDHT22.o: sensorDHT22.cpp sensorDHT22.h
	$(CC) $(DEBUG) $(CFLAGS) sensorDHT22.cpp
sensoremu.o: sensoremu.cpp sensoremu.h
	$(CC) $(DEBUG) $(CFLAGS) sensoremu.cpp
pugixml.o: ./pugi/pugixml-1.7/src/pugiconfig.hpp ./pugi/pugixml-1.7/src/pugixml.cpp ./pugi/pugixml-1.7/src/pugixml.hpp
	$(CC) $(DEBUG) $(CFLAGS) ./pugi/pugixml-1.7/src/pugixml.cpp
programWheel.o: programWheel.cpp programWheel.h utils.h elapsedTimeThread.h
	$(CC) $(DEBUG) $(CFLAGS) programWheel.cpp
utils.o: utils.cpp utils.h
	$(CC) $(DEBUG) $(CFLAGS) utils.cpp
elapsedTimeThread.o: elapsedTimeThread.cpp elapsedTimeThread.h utils.h
	$(CC) $(DEBUG) $(CFLAGS) elapsedTimeThread.cpp
incu8atorLog.o: incu8atorLog.cpp incu8atorLog.h 
	$(CC) $(DEBUG) $(CFLAGS) incu8atorLog.cpp

clean:
	\rm *.o *~ $(EXENAME)
tar:
	tar cfv $(VER).tar *.cpp *.h makefile
