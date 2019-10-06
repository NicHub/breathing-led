/*
 * S T M 3 2 - E 4 0 7  —  B R E A T H I N G    L E D
 *
 * Copyright (C) 2019  Nicolas Jeanmonod, ouilogique.com
 *
 * https://github.com/NicHub/
 *
 */

#include <Arduino.h>
#include "System_Clock_Configuration.h" // Needed for SerialUSB on USB-OTG#1 to work.

#define LED_STME407 PC13 // Built-in LED. Inverted logic.
#define LED_ARDUINO PA5  // Labeled D13 on the board.

const int nb_elem = 638;
const uint32_t brightness_array[nb_elem] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 7,
    11, 17, 30, 42, 55, 67, 79, 92, 104, 117, 129, 142, 154, 166, 179, 191, 204,
    216, 224, 230, 237, 241, 244, 247, 248, 250, 250, 251, 251, 252, 252, 252,
    253, 253, 253, 253, 254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 253,
    253, 253, 253, 252, 252, 252, 251, 251, 250, 250, 249, 249, 248, 247, 247,
    246, 246, 245, 244, 243, 243, 241, 239, 238, 237, 234, 231, 229, 225, 222,
    218, 213, 209, 202, 195, 187, 178, 168, 158, 147, 137, 125, 113, 100, 88, 75,
    64, 55, 47, 40, 33, 28, 23, 19, 16, 13, 12, 11, 11, 10, 10, 10, 11, 14, 17,
    21, 26, 32, 39, 47, 57, 67, 79, 91, 103, 115, 126, 136, 146, 156, 165, 173,
    180, 186, 191, 195, 199, 203, 206, 210, 213, 215, 218, 220, 223, 225, 227,
    228, 230, 232, 234, 236, 237, 239, 240, 240, 241, 242, 243, 245, 245, 245,
    245, 244, 243, 242, 241, 239, 238, 237, 236, 234, 232, 230, 228, 227, 225,
    224, 223, 222, 220, 217, 215, 213, 211, 210, 208, 206, 204, 201, 198, 195,
    192, 189, 187, 184, 182, 179, 176, 174, 169, 166, 164, 160, 157, 154, 150,
    145, 139, 133, 127, 120, 112, 106, 98, 89, 81, 73, 63, 55, 48, 41, 35, 29, 24,
    20, 17, 14, 12, 10, 10, 9, 9, 9, 9, 9, 11, 13, 17, 23, 31, 39, 49, 61, 76, 90,
    106, 122, 138, 154, 170, 184, 197, 208, 217, 225, 231, 235, 239, 241, 244,
    246, 247, 247, 247, 247, 248, 249, 249, 250, 251, 251, 251, 252, 252, 253,
    253, 253, 253, 253, 253, 253, 254, 253, 253, 253, 253, 252, 252, 252, 251,
    251, 250, 249, 248, 246, 245, 244, 242, 241, 240, 239, 238, 237, 236, 235,
    234, 234, 233, 233, 232, 230, 228, 226, 225, 221, 218, 215, 213, 210, 207,
    203, 200, 197, 195, 192, 189, 185, 182, 179, 175, 169, 163, 157, 149, 142,
    134, 125, 115, 106, 96, 86, 76, 65, 56, 48, 40, 34, 28, 23, 18, 15, 11, 9, 8,
    7, 7, 6, 6, 5, 5, 6, 7, 9, 12, 15, 18, 23, 28, 34, 41, 48, 55, 62, 68, 74, 80,
    84, 88, 93, 95, 96, 99, 98, 98, 99, 100, 101, 103, 104, 105, 105, 105, 106,
    109, 111, 114, 118, 121, 124, 128, 131, 134, 139, 143, 147, 150, 152, 153,
    154, 152, 151, 149, 146, 142, 138, 133, 130, 125, 120, 116, 110, 105, 100, 94,
    90, 86, 81, 77, 72, 66, 61, 57, 52, 49, 45, 41, 38, 35, 32, 28, 26, 24, 21,
    19, 17, 15, 13, 12, 11, 9, 8, 7, 6, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
    1, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 9, 10, 12, 14, 15, 17, 19, 22, 24, 27, 30,
    33, 35, 38, 41, 45, 49, 54, 59, 64, 68, 72, 76, 79, 82, 85, 87, 88, 87, 85,
    83, 81, 77, 74, 70, 66, 62, 58, 54, 51, 47, 44, 42, 39, 36, 33, 30, 28, 26,
    25, 23, 20, 18, 15, 14, 12, 11, 10, 9, 8, 7, 6, 5, 4, 4, 4, 4, 3, 3, 2, 2, 2,
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const uint32_t scaling_fact = 4;
const uint32_t scaling_offset = 255.0 - ceil(255.0 / scaling_fact);

/**
 *
 */
void setup()
{
    pinMode(LED_STME407, OUTPUT);
    pinMode(LED_ARDUINO, OUTPUT);
    digitalWrite(LED_STME407, HIGH);
    digitalWrite(LED_ARDUINO, LOW);

    // Serial USB (USB CDC) is read through USB-OTG#1 virtual interface.
    SerialUSB.begin(BAUD_RATE); // Change BAUD_RATE in platformio.ini.
    SerialUSB.print("\nSerialUSB START");

    // Serial 3 is read with an UART Serial Bridge connected on
    // TX and GND pins of the BOOT header located beside the UEXT connector.
    Serial3.begin(BAUD_RATE); // Change BAUD_RATE in platformio.ini.
    Serial3.print("\nSerial3 START");

    // Serial 6 is read with an UART Serial Bridge connected on
    // pin 3 (TX) and pin 2 (GND) of the UEXT connector.
    Serial6.begin(BAUD_RATE); // Change BAUD_RATE in platformio.ini.
    Serial6.print("\nSerial6 START");
}

/**
 *
 */
void loop()
{
    static int cnt = 0;
    uint32_t brightness = brightness_array[cnt] / scaling_fact + scaling_offset;
    cnt++;
    if (cnt > nb_elem - 1)
    {
        digitalWrite(LED_STME407, LOW);
        cnt = 0;
    }
    else
    {
        digitalWrite(LED_STME407, HIGH);
    }
    SerialUSB.print(cnt);
    SerialUSB.print(" ");
    SerialUSB.println(brightness);
    analogWrite(LED_ARDUINO, brightness);
    delay(36);
}
