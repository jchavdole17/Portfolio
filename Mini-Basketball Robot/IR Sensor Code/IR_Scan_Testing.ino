// constants
#define IRbeacon1 11
#define IRbeacon2 24
#define IRbeacon3 25
#define SETPOINT 100 // loop count setpoint

int LC = 0;

int IR1CNTL = 0;
int IR2CNTC = 0;
int IR3CNTR = 0;

long previousMillis = 0;
int avgInterval = 200;
long interval = 0;

void IR_Scan();


  

void setup() {
  // put your setup code here, to run once:
    //IR 
  pinMode(IRbeacon1, INPUT); // NOTE: 1 indicates no beacon detected, 0 is yes beacon detected
  pinMode(IRbeacon2, INPUT);
  pinMode(IRbeacon3, INPUT);

  Serial.begin(115200);
  Serial.println("Starting scanning...");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly: 
  IR_Scan();
}

void IR_Scan(){
// read the input pin:
  unsigned long currentMillis = millis();
    Serial.println("Scanning ...");
  if (currentMillis - previousMillis >= interval) {
    LC++;
    previousMillis = currentMillis;
    int IRStateL = digitalRead(IRbeacon1);
    int IRStateC = digitalRead(IRbeacon2);
    int IRStateR = digitalRead(IRbeacon3);
    

 //   Serial.println("1 means detected signal");
    Serial.print("Left state: ");
    Serial.println(IRStateL);
    Serial.print("Centre state: ");
    Serial.println(IRStateC);
    Serial.print("Right state: ");
    Serial.println(IRStateR);
    
    // print out the state of the button:
    //Serial.println(IRState1); // Note - it's 0 if beacon is ON, 1 if beacon is OFF. Do some if or case statements to print out more meaningful information.
    if (IRStateL == 0) {
      IR1CNTL++;
     // Serial.println("Beam Detected Left");
    }
    if(IRStateC == 0) {
      IR2CNTC++;
   //   Serial.print("\t");
   //   Serial.println("Beam Detected Center");
    } 
     if(IRStateR == 0) {
      IR3CNTR++;
    //  Serial.print("\t");Serial.print("\t");
    //  Serial.println("Beam Detected Right");
    }   
  }
  if(LC == SETPOINT)
  {
    int IRS[3] = {IR1CNTL,IR2CNTC,IR3CNTR};
    int i = 0;
    int maximum = IRS[i];
    i++;
    for(i; i<3; i++)
    {
      if(IRS[i] > IRS[i-1])
      {
        maximum  = IRS[i];
      }
    }
    Serial.print("Maximum: ");
    Serial.println(maximum);
    Serial.print("Left counts: ");
    Serial.println(IR1CNTL);
    Serial.print("Centre counts: ");
    Serial.println(IR2CNTC);
    Serial.print("Right: ");
    Serial.println(IR3CNTR);
    
    if(maximum == 0)
    {
      Serial.println("ALL OFF");
      delay(2000);
    }
    else
    {
    if(maximum == IR1CNTL) {
      Serial.println("LEFT BEAM");
    }
    
    if(maximum == IR2CNTC) {
      Serial.println("CENTRE BEAM");

    }
    if(maximum == IR3CNTR){ 
      Serial.println("RIGHT BEAM");
    }
    delay(2000);
    }
    IR1CNTL = 0;
    IR2CNTC = 0;
    IR3CNTR = 0;
    LC = 0;
  }
  
}
