# ChronoTrigger #

ChronoTrigger is a simple, restartable timer. It is written in C++11 and depends only on its STL headers. Total LoC is 80 lines:

    -------------------------------------------------------------------------------
	Language                     files          blank        comment           code
	-------------------------------------------------------------------------------
	C++                              1             25             27             51
	C/C++ Header                     1             13              9             29
	-------------------------------------------------------------------------------
	SUM:                             2             38             36             80
	-------------------------------------------------------------------------------

## API ##

	void setCallback(std::function<void(int)> cb, uint32_t data);
	bool start(uint32_t interval, bool single = false);
	void restart();
	void finish();
	void stop();

## Building ##

ChronoTrigger can be used as plain source in a project after including the `chronotrigger.h` header file and adding the `chronotrigger.cpp` source file to the project. Alternatively a library can be built using the provided Makefile in the `src` folder:

	make lib

This will build the `.a` library in the `src/lib` folder. 

Only dependency is C++11.

## Test application ##

A test application is found in the `src/cpp-test` folder, which can be built using the same Makefile in the `src` folder with the following command:

	make test

The source for this test application looks as follows:

	#include "../cpp/chronotrigger.h"

	#include <iostream>
	#include <atomic>


	// Globals:
	std::mutex mutex;
	std::condition_variable cv;
	std::atomic_uint8_t countdown;


	void lavos(int value) {
		std::cout << "Lavos called with value: " << value << ". Countdown: " << (int) countdown.load() << std::endl;
		--countdown;
		if (countdown == 0) {
			cv.notify_all();
		}
	}


	int main() {
		// Have the timer class call the callback 10 times in 1 second intervals before the callback
		// ends the application.
	
		ChronoTrigger ct;
		countdown = 10;
	
		int keepAlive = 1; // In seconds.
		ct.setCallback(lavos, 42);
		ct.start((keepAlive) * 1000);
	
		// Wait until signalled.
		std::unique_lock<std::mutex> lk(mutex);
		cv.wait(lk);
	
		ct.stop();
	
		std::cout << "All done here." << std::endl;
		
		return 0;
	}


## Status ##

ChronoTrigger has been tested and so far found to be stable. More testing is however required for different usage scenarios. 

This code is used in the [NymphMQTT](https://github.com/MayaPosch/NymphMQTT) MQTT library, which is a component of the [MQTTCute](https://github.com/MayaPosch/MQTTCute) MQTT desktop client.