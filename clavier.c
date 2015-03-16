
// keypad pins to arduino pin mapping
const int kpPin1 = 1;
const int kpPin2 = 2;
const int kpPin3 = 3;
const int kpPin4 = 4;
const int kpPin5 = 5;
const int kpPin6 = 6;
const int kpPin7 = 7;
const int kpPin8 = 8;

void clavierSetup(){
    pinMode(kpPin1, INPUT);
    pinMode(kpPin2, INPUT);
    pinMode(kpPin3, INPUT);
    pinMode(kpPin4, INPUT);
    pinMode(kpPin5, INPUT);
    pinMode(kpPin6, INPUT);
    pinMode(kpPin7, INPUT);
    pinMode(kpPin8, INPUT);
}

int getKpKey(){
    kpPinState1 = digitalRead(kpPin1);
    kpPinState2 = digitalRead(kpPin2);
    kpPinState3 = digitalRead(kpPin3);
    kpPinState4 = digitalRead(kpPin4);
    kpPinState5 = digitalRead(kpPin5);
    kpPinState6 = digitalRead(kpPin6);
    kpPinState7 = digitalRead(kpPin7);
    kpPinState8 = digitalRead(kpPin8);


}

