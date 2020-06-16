int leftpos=10;
int rightpos=7;
int leftneg=12;
int rightneg=5;
int ledPin=15;
void setup()
{
  pinMode(leftpos,OUTPUT);
  pinMode(rightpos,OUTPUT);
  pinMode(leftneg,OUTPUT);
  pinMode(rightneg,OUTPUT);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(10);
}
void drive(int lspeed, int rspeed)
{
  if(lspeed>=0)
  {
    analogWrite(leftpos,lspeed);
    digitalWrite(leftneg,LOW);
  }
  else
  {
    analogWrite(leftneg,abs(lspeed));
    digitalWrite(leftpos,LOW);
  }
  if(rspeed>=0)
  {
    analogWrite(rightpos,rspeed);
    digitalWrite(rightneg,LOW);
  }
  else
  {
    analogWrite(rightneg,abs(rspeed));
    digitalWrite(rightpos,LOW);
  }
}

void glowLed()
{
  digitalWrite(ledPin,HIGH);
  delay(2000);
  digitalWrite(ledPin,LOW);
}
void loop()
{
  char x;
  while(Serial.available())
  {
    while(Serial.available())
    {
      x=Serial.read();
      Serial.read();
    }
    if(x=='0')
      drive(200,255);
    else if(x=='2')
      drive(200,0);
    else if(x=='1')
      drive(0,255);
    else if(x=='3')
      drive(0,0);
    else if(x='4')
       glowLed(); 
    delay(100);
      drive(0,0);
     //delay(200);
     //delay(400);
  }
  
}
