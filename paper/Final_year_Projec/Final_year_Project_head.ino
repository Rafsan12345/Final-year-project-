//int pot = A5;
String comdata;
void setup(){
Serial.begin(9600);
Serial.println("CLEARDATA");
Serial.println("LABEL, Time, Started Time, Date, ID");
Serial.println("RESETTIMER");
}

void loop(){

if (Serial.available() > 0) {
       comdata =Serial.readString();

Serial.print("DATA, TIME, TIMER, DATE,");
Serial.print(comdata);
Serial.println(",");
//Serial.print(comdata);
//Serial.println(",");
//delay(1500);
}
}
