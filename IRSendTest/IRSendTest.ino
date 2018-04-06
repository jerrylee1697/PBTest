#include "IRremote.h"

int RECV_PIN = 4;
int SEND_PIN = 5;
int khz = 38;

IRrecv irrecv(RECV_PIN);
IRsend irsend(SEND_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  irsend.enableIROut(khz);
  Serial.println("Enabled IRout");
}

const unsigned int testbuf[1] = {};

void loop() {
  //Serial.println(irrecv.decode(&results)); Juju debug print
//    irsend.sendRaw((unsigned int *)irparams.rawbuf, irparams.rawlen, khz);
    digitalWrite(SEND_PIN, HIGH);

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  delay(1000);
//  irsend.sendRaw((unsigned int *)irparams.rawbuf, irparams.rawlen, khz);
}
