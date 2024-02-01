// Define piezo sensors
int sS1 = A15;
int sS2 = A14;
int sS3 = A13;
int sS4 = A12;
int sS5 = A11;
int sS6 = A10;
int sS7 = A9;
int sS8 = A8;

// Define LEDs for each xylophone key
int lCLed = 23; //1
int DLed = 25; //2
int ELed = 27; //3
int FLed = 29; //4
int GLed = 31; //5
int ALed = 33; //6
int BLed = 35; //7
int hCLed = 37; //8
int stateled = 49; // indicates whether the mode is idle or activated

int button1 = 47; // Arduino pin that belongs to the button that activates the mode
int button1old = 1; // stores the state of the button 
int threshold = 30; // sensitivity of piezo sensor (arduino reads 0-1024 bits representing voltage measurements, this determines at what voltage to consider a hit)

// Song - Blinding Lights (These are all the keys in the main melody of the song)
int leds[] = {GLed,GLed,FLed,GLed,ALed,DLed,FLed, GLed,GLed,FLed,GLed,ALed,DLed,FLed, hCLed,ALed,GLed,FLed,hCLed,ALed,GLed,FLed,GLed};
int sensors[] = {sS5,sS5,sS4,sS5,sS6,sS2,sS4, sS5,sS5,sS4,sS5,sS6,sS2,sS4, sS8,sS6,sS5,sS4,sS8,sS6,sS5,sS4,sS5};


void setup() {
pinMode(redled,OUTPUT);
pinMode(button1,INPUT_PULLUP); // 0 means it's pressed
Serial.begin(9600);
}


void loop() {
  // Check if the button has been pressed
  int button1new = digitalRead(button1);

  // Check if button has been pressed
  if (button1old == 1 && button1new == 0){
    digitalWrite(stateled,LOW); // indicate state change

      // Iterate through all notes in the melody
      for(int i = 0; i<23; i++){
        int led = leds[i];
        delay(200);
        digitalWrite(led,HIGH);

        // Loop until arduino detects a voltage from the piezo higher than the threshold (indicates a key hit)
        while(analogRead(sensors[i]) < threshold)
        {
        }

        digitalWrite(led,LOW); // turn key LED off once piezo detects a hit
      } 
  }

  // Ensures that LED indicating state shows that the mode hasn't been activated
  else {
    digitalWrite(stateled, HIGH);
  }
}