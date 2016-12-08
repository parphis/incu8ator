CC = g++
C = gcc
C11 = -std=c++11
THREAD = -pthread
DEBUG = -g 
LFLAGS = -Wall -lssd1306 -lbcm2835 -lrt
CFLAGS = -Wall -c $(THREAD) $(C11)
OBJS = nc8tr.o displayBase.o displayStdOut.o displayOLED.o incu8ator.o sensorBase.o bcm2835.o sensorDHT22.o sensoremu.o pugixml.o programWheel.o utils.o elapsedTimeThread.o log.o common_dht_read.o pi_2_dht_read.o pi_2_mmio.c
EXENAME = nc8tr
EXEC = -o $(EXENAME)
VER = $(EXENAME)_$$(date +'%Y%m%d_%H%M%S')

nc8tr: $(OBJS)
	$(CC) $(DEBUG) $(THREAD) $(C11) $(LFLAGS) $(OBJS) $(EXEC)

nc8tr.o: nc8tr.cpp utils.h incu8ator.h log.h
	$(CC) $(DEBUG) $(CFLAGS) nc8tr.cpp 
displayBase.o: displayBase.cpp displayBase.h displayStdOut.h displayOLED.h
	$(CC) $(DEBUG) $(CFLAGS) displayBase.cpp
displayStdOut.o: displayStdOut.cpp displayStdOut.h
	$(CC) $(DEBUG) $(CFLAGS) displayStdOut.cpp
displayOLED.o: displayOLED.cpp displayOLED.h
	$(CC) $(DEBUG) $(CFLAGS) displayOLED.cpp
incu8ator.o: incu8ator.cpp incu8ator.h sensorBase.h displayBase.h programWheel.h log.h
	$(CC) $(DEBUG) $(CFLAGS) incu8ator.cpp
sensorBase.o: sensorBase.cpp sensorBase.h sensoremu.h sensorDHT22.h
	$(CC) $(DEBUG) $(CFLAGS) sensorBase.cpp
bcm2835.o: ./ArduiPi_SSD1306/bcm2835.c ./ArduiPi_SSD1306/bcm2835.h
	$(C) $(DEBUG) $(CFLAGS) ./ArduiPi_SSD1306/bcm2835.c
sensorDHT22.o: sensorDHT22.cpp sensorDHT22.h utils.h log.h pi_2_dht_read.h ./ArduiPi_SSD1306/bcm2835.h
	$(CC) $(DEBUG) $(CFLAGS) sensorDHT22.cpp
sensoremu.o: sensoremu.cpp sensoremu.h
	$(CC) $(DEBUG) $(CFLAGS) sensoremu.cpp
pugixml.o: ./pugi/pugixml-1.7/src/pugiconfig.hpp ./pugi/pugixml-1.7/src/pugixml.cpp ./pugi/pugixml-1.7/src/pugixml.hpp
	$(CC) $(DEBUG) $(CFLAGS) ./pugi/pugixml-1.7/src/pugixml.cpp
programWheel.o: programWheel.cpp programWheel.h utils.h elapsedTimeThread.h log.h
	$(CC) $(DEBUG) $(CFLAGS) programWheel.cpp
utils.o: utils.cpp utils.h
	$(CC) $(DEBUG) $(CFLAGS) utils.cpp
elapsedTimeThread.o: elapsedTimeThread.cpp elapsedTimeThread.h utils.h
	$(CC) $(DEBUG) $(CFLAGS) elapsedTimeThread.cpp
log.o: log.cpp log.h
	$(CC) $(DEBUG) $(CFLAGS) log.cpp
common_dht_read.o: common_dht_read.h
	$(CC) $(DEBUG) $(CFLAGS) common_dht_read.c
pi_2_dht_read.o: pi_2_dht_read.h pi_2_mmio.h
	$(CC) $(DEBUG) $(CFLAGS) pi_2_dht_read.c
pi_2_mmio.o: pi_2_mmio.h
	$(CC) $(DEBUG) $(CFLAGS) pi_2_mmio.c

clean:
	\rm *.o *~ $(EXENAME)
tar:
	tar cfv $(VER).tar *.cpp *.h makefile ./ArduiPi_SSD1306/*.* ./pugi/*.*
