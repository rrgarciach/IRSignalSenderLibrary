#include "Arduino.h"
#include "IRSignalSender.h"

IRSignalSender::IRSignalSender(int pin)
{
	pinMode(pin,OUTPUT);
	digitalWrite(pin, LOW);
	_NumIRsignals = 100;
	_IRledPin = pin;
}

void IRSignalSender::sendCommand(int command)
{
	Serial.println("SENDING SIGNAL!");
	parsePulse(command);
	delay(5);
	parsePulse(command);
}

void IRSignalSender::parsePulse(int command) {
	switch (command) {
		case 0:
			_NumIRsignals = cmd_Midea_OnOff[0];
			for (int i = 1; i < _NumIRsignals; i += 2) {
				pulseIR(cmd_Midea_OnOff[i]*10);
				delayMicroseconds(cmd_Midea_OnOff[i+1]*10);
			}
		break;
		case 1:
			_NumIRsignals = cmd_SamsungTV_OnOff[0];
			for (int i = 1; i < _NumIRsignals; i += 2) {
				pulseIR(cmd_SamsungTV_OnOff[i]*10);
				delayMicroseconds(cmd_SamsungTV_OnOff[i+1]*10);
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