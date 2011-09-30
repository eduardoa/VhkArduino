#ifndef SoftwareTimers_h
#define SoftwareTimers_h
#endif

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

/**
 * Class for timers with 32 bit unsigned integer space.
 * 
 * This class can use any kind of reference timer as long as you insert the right function on the now parameter.
 * It also has functionality to handle overflows in the base timer used.
 */
class Timer32 {
protected:
	uint32_t setTime; // The moment the timer was set.
	uint32_t delay; // The time the timer should wait.
public:
	Timer32() {};
	Timer32(uint32_t duration, uint32_t now) { set(duration, now); };
	
	bool expired(uint32_t now);
	uint32_t remaining(uint32_t now);
	void set(uint32_t duration, uint32_t now);
};

/**
 * This timer uses the Arduino micros() function as reference for Timer32.
 */
class MicroSecondTimer : public Timer32 {
public:
	MicroSecondTimer() {};
	MicroSecondTimer(uint32_t us) { set(us); };
	
	bool expired();
	uint32_t remaining();
	void set(uint32_t us);
};

/**
 * This timer uses the Arduino millis() function as reference for Timer32.
 */
class MilliSecondTimer : public Timer32 {
public:
	MilliSecondTimer() {};
	MilliSecondTimer(uint32_t ms) { set(ms); };
	
	bool expired();
	uint32_t remaining();
	void set(uint32_t ms);
};

/**
 * This timer is a MilliSecondTimer with specific functionality for ACK handling.
 */
class AckTimer : public MilliSecondTimer {
protected:
	bool armed;
public:
	void disarm();
	bool isArmed();
	void set(uint32_t ms);
};
