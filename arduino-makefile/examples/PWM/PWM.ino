/*
  PWM
  Turns on RGB LED 
*/		
void setup() {
/* pinMode(3,OUTPUT); */
/* pinMode(5,OUTPUT); */
/* pinMode(6,OUTPUT); */

analogWrite(3,0);
analogWrite(5,0);
analogWrite(6,0);

}

void loop() {

int i=0;


for (i = 0 ; i < 41 ; i++ ) {
		analogWrite(6,(i*500));
		delay(50);
}

for (i = 40 ; i > -1 ; i-- ) {
		analogWrite(6,(i*500));
		delay(50);
}

}
