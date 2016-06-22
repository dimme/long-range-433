#define PULSETIME 1 //In ms

//byte BARKER_CODE[13] = {1,1,1,1,1,0,0,1,1,0,1,0,1};
//byte BARKER_CODE[169] = {1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,1,-1,1,-1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,1,-1,1,-1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,1,-1,1,-1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1};
byte BARKER_CODE[169] = {1,1,1,1,1,0,0,1,1,0,1,0,1,1,1,1,1,1,0,0,1,1,0,1,0,1,1,1,1,1,1,0,0,1,1,0,1,0,1,1,1,1,1,1,0,0,1,1,0,1,0,1,1,1,1,1,1,0,0,1,1,0,1,0,1,0,0,0,0,0,1,1,0,0,1,0,1,0,0,0,0,0,0,1,1,0,0,1,0,1,0,1,1,1,1,1,0,0,1,1,0,1,0,1,1,1,1,1,1,0,0,1,1,0,1,0,1,0,0,0,0,0,1,1,0,0,1,0,1,0,1,1,1,1,1,0,0,1,1,0,1,0,1,0,0,0,0,0,1,1,0,0,1,0,1,0,1,1,1,1,1,0,0,1,1,0,1,0,1};
byte BARKER_LENGTH = 169;

void setup() {
  //pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  sendString("Hello Dimme =)\n");
}

void sendString(String text) {
  byte i;
  for (i = 0; i < text.length(); ++i) {
    sendChar(text.charAt(i));
  }
}

void sendChar(char ch) {
  byte i;
  for (i = 0; i < 8; ++i) {
    transmitBarkerCode(1);
  }
  for (i = 0; i < 8; ++i) {
    byte b = (ch >> i) & 1;
    transmitBarkerCode(b);
  }
}

void transmitBarkerCode(byte b) {
  byte i;
  for (i = 0; i < BARKER_LENGTH; ++i) {
    if (b == 1) {
      transmitBit(BARKER_CODE[i]);
    } else {
      transmitBit(BARKER_CODE[i] == 1 ? 0 : 1);
    }
  }
}

void transmitBit(byte b) {
  if (b == 1) {
    digitalWrite(12, HIGH);
    delay(PULSETIME);
  } else {
    digitalWrite(12, LOW);
    delay(PULSETIME);
  }
}



