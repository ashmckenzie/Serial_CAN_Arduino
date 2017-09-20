// MASK&FILE EXAMPLE OF SERIAL CAN MODULE
#include <Serial_CAN_Module.h>
#include <SoftwareSerial.h>

Serial_CAN can;

#define can_tx  3           // tx of serial can module connect to D3
#define can_rx  2           // rx of serial can module connect to D2

unsigned long mask[4] = 
{
    0, 0x0f,            // ext, maks 0
    0, 0x0f,            // ext, mask 1
};

unsigned long filt[12] = 
{
    0, 0x01,            // ext, filt 0
    0, 0x02,            // ext, filt 1
    0, 0x03,            // ext, filt 2
    0, 0x04,            // ext, filt 3
    0, 0x05,            // ext, filt 4
    0, 0x06,            // ext, filt 5
};

void setup()
{
    Serial.begin(9600);
    can.begin(can_tx, can_rx, 9600);      // tx, rx

    
    if(can.setFilt(filt))
    {
        Serial.println("set filt ok");
    }
    else 
    {
        Serial.println("set filt fail");
    }
    
    if(can.setMask(mask))
    {
        Serial.println("set mask ok");
    }
    else
    {
        Serial.println("set mask fail");
    }
    
    
}

unsigned long id = 0;
unsigned char dta[8];

// send(unsigned long id, byte ext, byte rtrBit, byte len, const byte *buf);
void loop()
{
    if(can.recv(&id, dta))
    {
        Serial.print("GET DATA FROM ID: ");
        Serial.println(id);
        for(int i=0; i<8; i++)
        {
            Serial.print("0x");
            Serial.print(dta[i], HEX);
            Serial.print('\t');
        }
        Serial.println();
    }
}

// END FILE