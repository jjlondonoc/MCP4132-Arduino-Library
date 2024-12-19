/*
 * Example for MCP4132 Arduino Library
 * Author: Juan José Londoño
 * License: MIT
 *
 * This example demonstrates the basic usage of the MCP4132 library to 
 * control a digital potentiometer using SPI. The example includes 
 * commands to increase, decrease, reset, and set the resistance, 
 * as well as to enable or disable the wiper and terminal connections.
 *
 * To use this example:
 * - Connect the MCP4132 to your microcontroller according to the SPI pins defined below.
 * - Open the Serial Monitor in the Arduino IDE or any serial terminal.
 * - Send the following commands to control the device:
 *   'i' - Increase the resistance
 *   'd' - Decrease the resistance
 *   'r' - Reset the wiper to its default position
 *   's' - Set the resistance to 3400 ohms (You can change this value as you want)
 *   'w' - Disable the wiper connection
 *   'e' - Enable the wiper connection
 *   't' - Disable the terminal connection
 *   'f' - Enable the terminal connection
 */

// Include library
#include <MCP4132.h>

// Select pins for SPI protocol
#define MOSI 23
#define MISO 19
#define SCK 18
#define CS 5

MCP4132 pot; // Create MCP4132 object

void setup() {
  Serial.begin(9600);

  /*
   * Configure the MCP4132 digital potentiometer.
   *
   * Available models:
   * - MODEL_5K (5k ohms)
   * - MODEL_10K (10k ohms)
   * - MODEL_50K (50k ohms)
   * - MODEL_100K (100k ohms)
   */
  pot.configure(MOSI, MISO, SCK, CS, MODEL_10K);
  Serial.println("Potentiometer configured");

  // Read and display the initial wiper position
  uint16_t wiperData = pot.getWiperPosition();
  Serial.print("Initial Wiper position: ");
  Serial.println(wiperData);

  // Read and display the initial resistance value
  uint16_t resistance = pot.getResistance();
  Serial.print("Initial Resistance [ohms]: ");
  Serial.println(resistance);

  // Verify the shutdown mode status
  bool status = pot.isShutDownMode();
  Serial.print("Shutdown mode: ");
  Serial.println(status ? "Enabled" : "Disabled");
}

void loop() {
  if (Serial.available() > 0) {
    char data = Serial.read();
    switch (data) {
      case 'i':
        Serial.println("Increase command received");
        if (pot.increase()) {
          Serial.print("New Wiper position: ");
          Serial.println(pot.getWiperPosition());
          Serial.print("New Resistance [ohms]: ");
          Serial.println(pot.getResistance());
        } else {
          Serial.println("Error: SPI communication failed");
        }
        break;

      case 'd':
        Serial.println("Decrease command received");
        if (pot.decrease()) {
          Serial.print("New Wiper position: ");
          Serial.println(pot.getWiperPosition());
          Serial.print("New Resistance [ohms]: ");
          Serial.println(pot.getResistance());
        } else {
          Serial.println("Error: SPI communication failed");
        }
        break;

      case 'r':
        Serial.println("Reset command received");
        if (pot.reset()) {
          Serial.print("Wiper position reset to: ");
          Serial.println(pot.getWiperPosition());
          Serial.print("Resistance reset to: ");
          Serial.println(pot.getResistance());
        } else {
          Serial.println("Error: SPI communication failed");
        }
        break;

      case 's':
        Serial.println("Set resistance to 3400 ohms");
        if (pot.setResistance(3400)) {
          Serial.print("Wiper position after setting: ");
          Serial.println(pot.getWiperPosition());
          Serial.print("Resistance set to: ");
          Serial.println(pot.getResistance());
        } else {
          Serial.println("Error: SPI communication failed");
        }
        break;

      case 'w':
        Serial.println("Disable wiper command received");
        if (pot.disableWiper()) {
          Serial.println("Wiper disabled");
        } else {
          Serial.println("Error: SPI communication failed");
        }
        break;

      case 'e':
        Serial.println("Enable wiper command received");
        if (pot.enableWiper()) {
          Serial.println("Wiper enabled");
        } else {
          Serial.println("Error: SPI communication failed");
        }
        break;

      case 't':
        Serial.println("Disable terminal command received");
        if (pot.disableTerminal()) {
          Serial.println("Terminal disabled");
        } else {
          Serial.println("Error: SPI communication failed");
        }
        break;

      case 'f':
        Serial.println("Enable terminal command received");
        if (pot.enableTerminal()) {
          Serial.println("Terminal enabled");
        } else {
          Serial.println("Error: SPI communication failed");
        }
        break;

      default:
        Serial.println("Invalid command. Try: i, d, r, s, w, e, t, or f.");
        break;
    }
  }
}
