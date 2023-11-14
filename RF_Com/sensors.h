#pragma once
//-----Internals------
#include "utility.h"
//-----Internals------

// Include your sensor libraries here
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

namespace sensors {

  RF24 radio(21, 20);  // CE, CSN
  const byte address[6] = "17026";

  void init() {
    radio.begin();
    radio.setPALevel(RF24_PA_MAX);
    radio.openWritingPipe(address);
    radio.stopListening();
  }

  void send_data(String msg){
    int str_len = msg.length() + 1;
    char text[str_len];
    msg.toCharArray(text, str_len);
    radio.write(&text, sizeof(text));
  }
}  // namespace sensors
