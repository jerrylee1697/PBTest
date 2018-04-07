#include "IRremote.h"

int RECV_PIN = 14;
int e_Pin = 25;
IRrecv irrecv(RECV_PIN);
IRsend irsend(e_Pin);

int codeLen;
decode_results results;
unsigned int rawCodes[RAWBUF];


void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  //pinMode(e_Pin, OUTPUT);

}

void storeCode(decode_results *results){
    codeLen = results->rawlen - 1;
    // To store raw codes:
    // Drop first value (gap)
    // Convert from ticks to microseconds
    // Tweak marks shorter, and spaces longer to cancel out IR receiver distortion
    for (int i = 1; i <= codeLen; i++) {
      if (i % 2) {
        // Mark
        rawCodes[i - 1] = results->rawbuf[i] * USECPERTICK - MARK_EXCESS;
        Serial.print(" m");
      }
      else {
        // Space
        rawCodes[i - 1] = results->rawbuf[i] * USECPERTICK + MARK_EXCESS;
        Serial.print(" s");
      }
      Serial.print(rawCodes[i - 1], DEC);
    }
    Serial.println("");
}
void loop() {
  //Serial.println(irrecv.decode(&results)); Juju debug print
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  storeCode();
  irsend.sendRaw(rawCodes, codeLen, 38);

    //digitalWrite(e_Pin, HIGH);

  delay(100);
}
