void setup() {
pinMode(2,INPUT); // r1
pinMode(3,INPUT); //r2
pinMode(4,INPUT); // r3
pinMode(5,INPUT); // r4
pinMode(6,INPUT); //i1
pinMode(7,INPUT);  //i2
pinMode(8,INPUT); //i3
pinMode(13,INPUT);//i4
pinMode(9,OUTPUT); // pwm
pinMode(4,INPUT); //analog1
pinMode(5,INPUT); // analog2
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(12,OUTPUT);



Serial.begin(9600);
\
}

void loop() {
int R1 = digitalRead(2);
int R2 = digitalRead(3);
int R3 = digitalRead(4);
int R4 = digitalRead(5);

int I1 = digitalRead(6);
int I2 = digitalRead(7);
int I3 = digitalRead(8); 
int I4 = digitalRead(13);

int A1 = analogRead(4);
int A2 = analogRead(5);

//regulator
if (A1>0   || A2>0 ) 
{ 
int Value = max(A1,A2);
analogWrite(9,Value);


}










if (R1 == HIGH ||  I1 == HIGH ) 
{ 

digitalWrite(10,HIGH);


}

if (R1 == LOW ||  I1 == LOW ) 
{ 

digitalWrite(10,LOW);


}

// 2
if (R2 == HIGH ||  I2 == HIGH ) 
{ 

digitalWrite(11,HIGH);


}

if (R2 == LOW ||  I2 == LOW ) 
{ 

digitalWrite(11,LOW);


}

//3
if (R3 == HIGH ||  I3 == HIGH ) 
{ 

digitalWrite(12,HIGH);


}

if (R3 == LOW ||  I3 == LOW ) 
{ 

digitalWrite(12,LOW);


}
//4
/* if (R4 == HIGH ||  I4 == HIGH ) 
{ 

digitalWrite(13,HIGH);


}

if (R4 == LOW ||  I4 == LOW ) 
{ 

digitalWrite(13,LOW);


}

*/


















}
