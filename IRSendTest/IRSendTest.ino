#include "IRremote.h"

int RECV_PIN = 4;
int SEND_PIN = 25;
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
  pinMode(SEND_PIN, OUTPUT);
  Serial.println("Enabled IRout");
}

//const unsigned int testbuf[1] = {};
//
//void loop() {
//  //Serial.println(irrecv.decode(&results)); Juju debug print
////    irsend.sendRaw((unsigned int *)irparams.rawbuf, irparams.rawlen, khz);
////    digitalWrite(SEND_PIN, HIGH);
//
//  if (irrecv.decode(&results)) {
//    Serial.println(results.value, HEX);
//    irrecv.resume(); // Receive the next value
//  }
//  delay(5000);
//  irsend.sendRaw((unsigned int *)irparams.rawbuf, irparams.rawlen, khz);
//}

//IRsend irsend(SEND_PIN);


void loop() {
  int khz = 38; // 38kHz carrier frequency for the NEC protocol
//  unsigned int irSignal[] = {9000, 4500, 560, 560, 560, 560, 560, 1690, 560, 560, 560, 560, 560, 560, 560, 560, 560, 560, 560, 1690, 560, 1690, 560, 560, 560, 1690, 560, 1690, 560, 1690, 560, 1690, 560, 1690, 560, 560, 560, 560, 560, 560, 560, 1690, 560, 560, 560, 560, 560, 560, 560, 560, 560, 1690, 560, 1690, 560, 1690, 560, 560, 560, 1690, 560, 1690, 560, 1690, 560, 1690, 560, 39416, 9000, 2210, 560}; //AnalysIR Batch Export (IRremote) - RAW
    unsigned int irSignal[] = {8900, 4600, 500, 650, 450, 1800, 450, 650, 450, 650, 500, 1750, 450, 1800, 450, 650, 450, 650, 500, 1750, 450, 650, 500, 1750, 450, 1750, 450, 700, 450, 650, 450, 1800, 450, 1750, 450, 1800, 450, 650, 450, 700, 450, 650, 450, 650, 450, 700, 450, 650, 450, 1800, 450, 650, 450, 1750, 450, 1800, 450, 1750, 500, 1750, 450, 1800, 450, 1750, 500, 650, 450};

  irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); //Note the approach used to automatically calculate the size of the array.

  delay(1000); //In this example, the signal will be repeated every 5 seconds, approximately.

}
