
// clavier FMBN16BD
// keypad pins to arduino pin mapping
const int kpPin1 = 26;
const int kpPin2 = 27;
const int kpPin3 = 28;
const int kpPin4 = 29;
const int kpPin5 = 33;
const int kpPin6 = 32;
const int kpPin7 = 31;
const int kpPin8 = 30;

int kpGetNibble1(){
    int res = 0x00;

    pinMode(kpPin1, INPUT);
    pinMode(kpPin2, INPUT);
    pinMode(kpPin3, INPUT);
    pinMode(kpPin4, INPUT);
    pinMode(kpPin5, OUTPUT);
    pinMode(kpPin6, OUTPUT);
    pinMode(kpPin7, OUTPUT);
    pinMode(kpPin8, OUTPUT);

    digitalWrite(kpPin5, HIGH);
    digitalWrite(kpPin6, HIGH);
    digitalWrite(kpPin7, HIGH);
    digitalWrite(kpPin8, HIGH);
    
    if(digitalRead(kpPin1) == HIGH)
        res += 0x01;
    if(digitalRead(kpPin2) == HIGH)
        res += 0x02;
    if(digitalRead(kpPin3) == HIGH)
        res += 0x04;
    if(digitalRead(kpPin4) == HIGH)
        res += 0x08;

    digitalWrite(kpPin5, LOW);
    digitalWrite(kpPin6, LOW);
    digitalWrite(kpPin7, LOW);
    digitalWrite(kpPin8, LOW);

    return res;
}

int kpGetNibble2(){
    int res = 0x00;

    pinMode(kpPin1, OUTPUT);
    pinMode(kpPin2, OUTPUT);
    pinMode(kpPin3, OUTPUT);
    pinMode(kpPin4, OUTPUT);
    pinMode(kpPin5, INPUT);
    pinMode(kpPin6, INPUT);
    pinMode(kpPin7, INPUT);
    pinMode(kpPin8, INPUT);
    
    digitalWrite(kpPin5, HIGH);
    digitalWrite(kpPin6, HIGH);
    digitalWrite(kpPin7, HIGH);
    digitalWrite(kpPin8, HIGH);
    
    if(digitalRead(kpPin5) == HIGH)
        res += 0x10;
    if(digitalRead(kpPin6) == HIGH)
        res += 0x20;
    if(digitalRead(kpPin7) == HIGH)
        res += 0x40;
    if(digitalRead(kpPin8) == HIGH)
        res += 0x80;

    digitalWrite(kpPin1, LOW);
    digitalWrite(kpPin2, LOW);
    digitalWrite(kpPin3, LOW);
    digitalWrite(kpPin4, LOW);

    return res;
}

int kpGetValue(){
    int res = 0x00;
    res += getNibble1();
    res += getNibble2();

    switch(res){
        case 0x88:
            return 1;
        case 0x48:
            return 2;
        case 0x28:
            return 3;
        case 0x18:
            return 4;
        case 0x84:
            return 5;
        case 0x44:
            return 6;
        case 0x24:
            return 7;
        case 0x14:
            return 8;
        case 0x82:
            return 9;
        case 0x42:
            return 10;
        case 0x22:
            return 11;
        case 0x12:
            return 12;
        case 0x81:
            return 13;
        case 0x41:
            return 14;
        case 0x21:
            return 15;
        case 0x11:
            return 16;
        default:
            return -1;
    }
}

