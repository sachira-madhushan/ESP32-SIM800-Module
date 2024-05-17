#define SMS_TARGET  "+94783398454"
#define TINY_GSM_MODEM_SIM800 
#define TINY_GSM_RX_BUFFER   1024
#include <TinyGsmClient.h>
const char simPIN[]   = "";

#define MODEM_TX 27
#define MODEM_RX 26

#define SerialMon Serial
#define SerialAT  Serial1
#ifdef DUMP_AT_COMMANDS
  #include <StreamDebugger.h>
  StreamDebugger debugger(SerialAT, SerialMon);
  TinyGsm modem(debugger);
#else
  TinyGsm modem(SerialAT);
#endif


void setup() {
  SerialMon.begin(9600);
  SerialAT.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);

  SerialMon.println("Initializing modem...");
  modem.init();

  String smsMessage = "Hello from ESP32!";

  if(modem.sendSMS(SMS_TARGET, smsMessage)){
    SerialMon.println(smsMessage);
  }else{
    SerialMon.println("SMS failed to send");
  }

}

