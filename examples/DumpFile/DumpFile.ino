/**
 * SD card file dump
 *
 * This example shows how to read a file from the SD card using the
 * SD library and send it over the serial port.
 *
 * SD card attached to SPI bus as follows:
 * o UNO:  MOSI - pin 11
 *         MISO - pin 12
 *          CLK - pin 13
 *           CS - pin 4 (CS pin can be changed)
 *         and pin #10 (SS) must be an output
 * o Mega:  MOSI - pin 51
 *          MISO - pin 50
 *           CLK - pin 52
 *            CS - pin 4 (CS pin can be changed)
 *          and pin #52 (SS) must be an output
 * o Leonardo: Connect to hardware SPI via the ICSP header
 *
 * Created  22 Dec 2010 by Limor Fried
 * Modified  9 Apr 2012 by Tom Igoe
 *
 * This example code is in the public domain.
 */

#include <SPI.h>
#include <SD.h>

// change this to match your SD shield or module;
//     Arduino Ethernet shield: pin 4
//     Adafruit SD shields and modules: pin 10
//     Sparkfun SD shield: pin 8
const int chipSelect = 4;

void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for Leonardo only
    }

    Serial.print("Initializing SD card...");

    // make sure that the default chip select pin is set to
    // output, even if you don't use it:
    pinMode(SS, OUTPUT);

    // see if the card is present and can be initialized:
    if (!SD.begin(chipSelect))
    {
        Serial.println("Card failed, or not present");
        // don't do anything more:
        return;
    }
    Serial.println("Card initialized.");

    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("datalog.txt");

    if (dataFile)
    {
        // if the file is available, write to it
        while (dataFile.available())
        {
            Serial.write(dataFile.read());
        }
        dataFile.close();
    }
    else
    {
        // if the file isn't open, pop up an error
        Serial.println("Error opening datalog.txt");
    }
}

void loop()
{
}
