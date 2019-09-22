/*
	chrono_test.cpp - Test application for the ChronoTrigger timer library.
	
	Revision 0
	
	Notes:
			-
			
	2019/09/22, Maya Posch
*/


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
