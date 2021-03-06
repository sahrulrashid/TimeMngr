// myTimer.h

#ifndef _MYTIMER_h
#define _MYTIMER_h

#include "Signals.h"

class TimeMngr
{
 protected:
	 typedef void(*CALLBACK_FUNC)(void);
	 CALLBACK_FUNC callback;
	 unsigned long pMills = 0;
	 unsigned long	interval;
	 bool enable = false;

 public:
	Signals<> SignalTimeout;

	TimeMngr() {
		enable = false;
	}

	TimeMngr(unsigned long intervalMs, bool tmrStart)
	{
		interval = intervalMs;
		pMills = millis();
		enable = tmrStart;
	}
	
	TimeMngr(unsigned long intervalMs, bool tmrStart, CALLBACK_FUNC cb)
	{
		interval = intervalMs;
		pMills = millis();
		enable = tmrStart;
		callback = cb;
	}

	void setInterval(unsigned long milisec) {
		interval = milisec;
	}
	
	void attachCallback(CALLBACK_FUNC cb){
		callback = cb;
	}
	
	void detachCallback(){
		callback = NULL;
	}

	void start(void) {
		enable = true;
		pMills = millis();
	}

	void stop(void) {
		enable = false;
	}

	void tick(void) {
		if (enable) {
			unsigned long cMills = millis();
			if (cMills - pMills >= interval) {
				pMills = cMills;
				SignalTimeout.emit();
			}
		}
	}
	
	void tickWithCallback(void) {
		if (enable) {
			unsigned long cMills = millis();
			if (cMills - pMills >= interval) {
				pMills = cMills;
				callback();
			}
		}
	}
};

#endif

