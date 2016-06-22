byte one[] = {1,0,0,1,1,0,0,0,1,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,0,1,0,0,1,0,0,0,1,1,1,1,0,1,0,1,1,1,1,1,0,0,0,1,0,1,1,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1,0,0,1,1,1,0,1,0,0,1,0,0,0,0,0,0,1,1,0,0,1,0,1,0};

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  send("Hello Dimme =)\n");
  delay(1000);
}

void send(String text) {
  byte i;
  for (i = 0; i < text.length(); ++i) {
    send_char(text.charAt(i));
  }
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

void send_char(char ch) {
  byte i;
  for (i = 0; i < 16; ++i) {
    transmit(1);
  }
  for (i = 0; i < 8; ++i) {
    byte b = (ch >> i) & 1;
    transmit(b);
  }
}

void transmit(byte b) {
  int i;
  for (i = 0; i < 100; ++i) {
    if (b == 1) {
      if (one[i] == 1) {
        digitalWrite(12, HIGH);
        digitalWrite(13, HIGH);
        delayMicroseconds(500);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);
      } else {
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);
        delayMicroseconds(500);
        digitalWrite(12, HIGH);
        digitalWrite(13, HIGH);
      }
    } else {
      if (one[i] == 0) {
        digitalWrite(12, HIGH);
        digitalWrite(13, HIGH);
        delayMicroseconds(500);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);
      } else {
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);
        delayMicroseconds(500);
        digitalWrite(12, HIGH);
        digitalWrite(13, HIGH);
      }
    }
    delayMicroseconds(500);
  }
}



