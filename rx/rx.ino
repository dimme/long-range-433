int one[100] = {1,-1,-1,1,1,-1,-1,-1,1,1,-1,1,-1,-1,-1,-1,1,-1,-1,1,-1,1,-1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,-1,1,1,1,1,-1,1,-1,1,1,1,1,1,-1,-1,-1,1,-1,1,1,-1,1,1,-1,-1,-1,-1,-1,-1,1,1,1,1,1,1,-1,1,1,-1,-1,1,1,1,-1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,1,-1,1,-1};
int buff[100];

void setup() {
  Serial.begin(9600);
  pinMode(12, INPUT);
}

void loop() {
  Serial.print(getCharacter());
}

char getCharacter() {
  byte count = 0;
  while (true) {
    // check for the start flag
    if (getBit() == 1)
      count++;
    else
      count = 0;

    // We have a char coming!
    if (count == 16)
      break;
  }

  char ch = 'a';
  int i;
  for (i = 0; i < 8; ++i) {
    if (getBit() == 1) {
      ch |= 1 << i;
    } else {
      ch &= ~(1 << i);
    }
  }

  return ch;
}

byte getBit() {
  while (true) {
    delayMicroseconds(100);
    shift_right(buff);
    if (digitalRead(12) == 1) {
      buff[0] = 1;
    } else {
      buff[0] = -1;
    }

    
    int corr = xcorr(one,buff);
    
    if (corr > 20) {
      return (byte) 1;
    }

    if (corr < -20) {
      return (byte) 0;
    }
    
    
  }

  return 0;
}

void shift_right(int arr[]) {
  int i;
  for (i = 99; i > 0; --i) {
    arr[i] = arr[i-1];
  }
}

void shift_left(int arr[]) {
  int i;
  for (i = 0; i < 99; ++i) {
    arr[i] = arr[i+1];
  }
}

int xcorr(int arr1[], int arr2[]) {
  int val = 0;
  int i;
  for (i = 0; i < 100; ++i) {
    val += arr1[i] * arr2[i];
  }
  return val;
}

