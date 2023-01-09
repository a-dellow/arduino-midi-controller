#include "MIDIUSB.h"

int THRESHOLD = 10;

int val_1 = 0;
int valB_1 = 0;
int val_2 = 0;
int valB_2 = 0;

void setup() {

    Serial.begin(115200);
}



void loop() {

    val_1 = analogRead(A1);  // function to read analog voltage from sensor 1
    //if(valB_1 > (val_1) && val_1 > THRESHOLD){  
      //sensOne();
    //}
    Serial.print("A1: ");
    Serial.println((val_1 * (-1)) + 1023);

    valB_1 = val_1;


    //val_2 = analogRead(A2);  // function to read analog voltage from sensor 1
    //if(valB_2 > (val_2) && val_2 > THRESHOLD){  
      //sensTwo();
    //}
    //Serial.print("A2: ");
    //Serial.println(val_2);

    //valB_2 = val_2;
}



void sensOne() {

    Serial.println("Sending note on");
    noteOn(0, 48, (val_1 / 8));   // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    delay(50);

    Serial.print("A1_Pin: ");
    Serial.println(val_1 / 8);

    Serial.println("Sending note off");
    noteOff(0, 48, (val_1 / 8));  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    delay(50);

    while (val_1 > THRESHOLD) {
        val_1 = analogRead(A1);

    }
}

void sensTwo() {

    Serial.println("Sending note on");
    noteOn(0, 48, (val_2 / 8));   // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    delay(50);

    Serial.print("A2_Pin: ");
    Serial.println(val_2 / 8);

    Serial.println("Sending note off");
    noteOff(0, 48, (val_2 / 8));  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    delay(50);

    while (val_2 > THRESHOLD) {
        val_2 = analogRead(A2);

    }
}

void noteOn(byte channel, byte pitch, byte velocity) {
    midiEventPacket_t noteOn = { 0x09, 0x90 | channel, pitch, velocity };
    MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
    midiEventPacket_t noteOff = { 0x08, 0x80 | channel, pitch, velocity };
    MidiUSB.sendMIDI(noteOff);
}