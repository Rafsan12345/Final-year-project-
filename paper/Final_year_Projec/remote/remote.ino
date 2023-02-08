
#include <IRremote.h>
int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
int c = 0 ;

int state1 = 1;
int state2 = 1;
int state3 = 1;
int state4 = 1;
int state5 = 1;


int led1 = 8;
int led3 = 10;
int led4 = 11;
int led5 = 12;

void setup()
{


  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(led1, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);




}

void loop() {






  //Serial.println(c);
  //38863BD2 power
  //38863BE0 1
  //38863BD0 2
  //38863BF0 3
  //38863BC8 4
  //38863BF2 up
  //38863BFA dwn

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value

    // all on off
    if (results.value == 0x38863BD2)
    {
      digitalWrite(led1, state2);
      digitalWrite(led5, state2);
      digitalWrite(led3, state2);
      digitalWrite(led4, state2);
      state2 = !state2;
    }






    // led 1
    else if (results.value == 0x38863BE0) // light on off perpose
    {
      digitalWrite(led1, state1);
      state1 = !state1;
    }
    // led 3

    else if (results.value == 0x38863BD0)
    {
      digitalWrite(led3, state2);
      state2 = !state2;
    }
    // led4
    else if (results.value == 0x38863BF0) // light on off perpose
    {
      digitalWrite(led4, state4);
      state4 = !state4;
    }
    // led 5
    else if (results.value == 0x38863BC8) // light on off perpose
    {
      digitalWrite(led5, state5);
      state5 = !state5;
    }


    /// regulator
    else if (results.value == 0x38863BF2) // up
    {


      c++;


    }


    else if (results.value == 0x38863BFA) // down
    {


      c--;


    }
    else
    {
      //none
    }



  }


  else
  {
    //none
  }





}
