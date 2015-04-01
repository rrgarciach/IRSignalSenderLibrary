#include "Arduino.h"
#include "IRSignalSender.h"

IRSignalSender::IRSignalSender(uint8_t pin)
{
	pinMode(pin,OUTPUT);
	digitalWrite(pin, LOW);
	_IRledPin = pin;
}

void IRSignalSender::sendCommand(uint8_t command)
{
	Serial.println(F("SENDING SIGNAL!"));
	parsePulse(command);
	delay(5);
	parsePulse(command);
}

void IRSignalSender::parsePulse(uint8_t command) {
	switch (command) {
		// TURN ON command:
		case 0:
			_NumIRsignals = cmd_on[0]*2;
			for (int i = 1; i < _NumIRsignals; i += 2) {
				pulseIR(cmd_on[i]*10*2);
				delayMicroseconds(cmd_on[i+1]*10*2);
			}
		break;
		// TURN OFF command:
		case 1:
			_NumIRsignals = cmd_off[0]*2;
			for (int i = 1; i < _NumIRsignals; i += 2) {
				pulseIR(cmd_off[i]*10*2);
				delayMicroseconds(cmd_off[i+1]*10*2);
			}
		break;
	}
}

void IRSignalSender::pulseIR(long microsecs) {
	cli();
	while (microsecs > 0) {
		digitalWrite(_IRledPin, HIGH);
		delayMicroseconds(10);
		digitalWrite(_IRledPin, LOW);
		delayMicroseconds(10);

		microsecs -= 26;
	}
	sei();
}