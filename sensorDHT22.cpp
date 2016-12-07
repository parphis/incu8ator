#include "sensorDHT22.h"

// uses the common_dht_read.h
void sensorDHT22::adafruitRead(void) {
	int err;
	if((err = pi_2_dht_read(DHT22, mGPIOPin, &humidity, &temperature))!=DHT_SUCCESS) {
		switch(err) {
		case DHT_ERROR_TIMEOUT:  errorString = "Query timeout."; crcError = 1; crcErrorCounter++; break;
		case DHT_ERROR_CHECKSUM: errorString = "Checksum error."; crcError = 1; crcErrorCounter++; break;
		case DHT_ERROR_ARGUMENT: errorString = "Argument error."; crcError = 1; crcErrorCounter++; break;
		case DHT_ERROR_GPIO: errorString = "GPIO error."; crcError = 1; crcErrorCounter++; break;
		default: errorString = "Unknown error."; crcError = 1; crcErrorCounter++;
		}
	}
	else {
		crcError = crcErrorCounter = 0;
	}
}
// custom algorythm built from the net everywhere
void sensorDHT22::customRead(void) {
	int counter = 0;
	int laststate = HIGH;
	int j = 0, i = 0;
	uint8_t data[5], checkSum;
	std::string d1,d2,d3,d4,d5;

	data[0] = data[1] = data[2] = data[3] = data[4] = 0;
	
	// set GPIO pin to output
	bcm2835_gpio_fsel(mGPIOPin, BCM2835_GPIO_FSEL_OUTP);

	//start signal
	bcm2835_gpio_write(mGPIOPin, HIGH); // pull up for ...
	bcm2835_delay(200); //200ms
	bcm2835_gpio_write(mGPIOPin, LOW); // keep low at least 1ms (18ms)
	bcm2835_delay(20); //20ms
	bcm2835_gpio_write(mGPIOPin, HIGH); // pull up 20-40us and wait for sensor response
	bcm2835_delayMicroseconds(20); // 40us

	//get acknowledge or timeout
	bcm2835_gpio_fsel(mGPIOPin, BCM2835_GPIO_FSEL_INPT);

	// sensor response: low signal and keep it 80us	
	while(bcm2835_gpio_lev(mGPIOPin)==1) {
		usleep(1);
	}
	
	//reading data
	for(i=0; i<100; i++) {
		counter = 0;
		// level from low to high >=80us 
		while(bcm2835_gpio_lev(mGPIOPin)==laststate) {
			counter++;
			//bcm2835_delayMicroseconds(1);
			if(counter==1000) break;
		}
		// laststate should be LOW for 50us
		laststate = bcm2835_gpio_lev(mGPIOPin);
		if(counter==1000) break;
		if((i>3) && (i%2==0)) {
			//shove each bit into the storage bytes
			data[j/8] <<= 1;
			if(counter > 200) {
				data[j/8] |= 1;
			}
			j++;
		}
	}
	checkSum = data[0] + data[1] + data[2] + data[3];
	if(checkSum!=data[4]) {
		crcError = 1;
		crcErrorCounter++;
	}
	else {
		crcError = crcErrorCounter = 0;
		doCalc(data);
	}
}
void sensorDHT22::doCalc(uint8_t data[5]) {
	humidity = data[0] * 256 + data[1];
	humidity /= 10;
	temperature = (data[2] & 0x7f) * 256 + data[3];
	temperature /= 10.0;
	if(data[2] & 0x80) temperature *= -1;
}
sensorDHT22::sensorDHT22(void) {
	// I do not know what to do here?
	// uninitialized BCM2835 causes only zero C and RH on the 
	// display so do not need to stop the whole process.
	if(bcm2835_init()==false) {
		log::err("BCM2835 library initialization failed!");
	}
	mReadAlgorythm = 1;
}
sensorDHT22::~sensorDHT22(void) {
}
void sensorDHT22::readOut(void) {
	switch(mReadAlgorythm) {
		case 1: adafruitRead(); break;
		case 2: customRead(); break;
		default: ;
	}
}
bool sensorDHT22::helloSensor(void) {
	return true;
}
template<class T>
void sensorDHT22::dbg(T *pulses, T *lvls, int m) {
	for(int x=0; x<=m; ++x)
		std::cout << "[" << x << "]=" << (int)pulses[x];
	std::cout<<std::endl;
	if(lvls==NULL) return;
	for(int x=0; x<=m; ++x) {
		char a;
		a = lvls[x]==1?'-':'_';
		std::cout << (int)pulses[x] << ":";
		for(int y=0; y<pulses[x]; y+=8)
			std::cout << a;
	}
	std::cout << std::endl;
}
