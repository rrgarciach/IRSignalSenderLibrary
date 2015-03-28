#include "Arduino.h"
#include "IRSignalSender.h"

IRSignalSender::IRSignalSender(int pin)
{
	pinMode(pin,OUTPUT);
	digitalWrite(pin, LOW);
	_NumIRsignals = 100;
	_IRledPin = pin;
	// _signalSizes[0] = 200;
	// _IRsignals[0] = cmd_Midea_OnOff;
	// _signalSizes[1] = 68;
	// _IRsignals[1] = cmd_SamsungTV_OnOff;
	// _IRsignals[0] = cmd_Midea_OnOff;
	// _signalSizes[1] = 68;
	// _IRsignals[1] = cmd_SamsungTV_OnOff;
}

void IRSignalSender::sendCommand(int command)
{
	Serial.println("SENDING SIGNAL!");
	parsePulse(command);
	delay(5);
	parsePulse(command);
}

void IRSignalSender::parsePulse(int command) {
	int cmd_Midea_OnOff[] = {200, 422, 412,  	54, 154,  	52, 50,  	54, 154,  	52, 154,  	52, 50,  	54, 50,  	54, 154,  	52, 50,  	54, 50,  	54, 154,  	52, 52,  	52, 52,  	52, 154,  	52, 154,  	52, 52,  	52, 154,  	54, 154,  	52, 50,  	54, 154,  	52, 154,  	52, 154,  	54, 152,  	54, 152,  	54, 154,  	52, 52,  	52, 154,  	54, 50,  	52, 50,  	54, 50,  	54, 50,  	54, 50,  	52, 52,  	52, 52,  	52, 154,  	54, 50,  	54, 152,  	54, 50,  	54, 50,  	54, 50,  	52, 52,  	52, 154,  	54, 50,  	54, 154,  	52, 50,  	54, 154,  	52, 154,  	54, 152,  	54, 152,  	54, 494,  	422, 414,  	52, 154,  	52, 52,  	52, 154,  	54, 152,  	54, 50,  	54, 50,  	54, 152,  	54, 50,  	54, 50,  	52, 156,  	52, 50,  	54, 50,  	54, 152,  	54, 152,  	54, 50,  	54, 154,  	54, 152,  	54, 50,  	54, 154,  	52, 154,  	52, 154,  	54, 152,  	54, 152,  	54, 154,  	52, 50,  	54, 154,  	54, 50,  	52, 50,  	54, 50,  	54, 50,  	54, 50,  	54, 50,  	52, 52,  	52, 154,  	54, 50,  	54, 152,  	54, 50,  	54, 50,  	54, 50,  	52, 52,  	52, 156,  	52, 50,  	54, 154,  	52, 52,  	52, 154,  	54, 152,  	54, 152,  	54, 154,  	52, 0};
	int cmd_SamsungTV_OnOff[] = {68, 428, 422,  56, 156,    56, 156,  	58, 156,  	56, 50,  	56, 50,  	56, 52,  	56, 50,  	56, 52,  	56, 156,  	56, 156,  	56, 156,  	58, 50,  	56, 50,  	56, 52,  	56, 50,  	56, 50,  	58, 50,  	56, 156,  	56, 50,  	56, 52,  	56, 50,  	56, 52,  	56, 50,  	56, 50,  	56, 158,  	56, 50,  	56, 156,  	56, 158,  	56, 156,  	56, 156,  	58, 156,  	56, 156,  	56, 0};
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