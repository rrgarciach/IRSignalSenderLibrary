#ifndef IRSignalSender_h
#define IRSignalSender_h

#include "Arduino.h"

class IRSignalSender
{
	public:
		IRSignalSender(int pin);
		void sendCommand(int command);
	private:
		int _IRledPin;
		int _NumIRsignals;
		// int _IRsignals[];
		// int _signalSizes[];
		void parsePulse(int command);
		void pulseIR(long microsecs);
};

#endif