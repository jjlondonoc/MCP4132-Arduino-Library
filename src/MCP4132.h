#ifndef __MCP4132_H__
#define __MCP4132_H__

#include <Arduino.h>

enum Resistance {
    MODEL_5K = 5000,
    MODEL_10K = 10000,
    MODEL_50K = 50000,
    MODEL_100K = 100000,
};

class MCP4132 {
    private:
        uint8_t _pinMOSI;
        uint8_t _pinMISO;
        uint8_t _pinSCK;
        uint8_t _pinCS;

        Resistance _maxResistance;

        const uint8_t _wiperResistance = 75; // Typical value according to datasheet

        enum Register : uint8_t {
            WIPER = 0x00,  // Address of WIPER register
            TCON = 0x04,   // Address of TCON register
            STATUS = 0x05, // Address of Status register
            INCREASE = 0x04, // Command for wiper++
            DECREASE = 0x08  // Command for wiper--
        };

        bool writeCommand(Register registerAddress, uint8_t dataByte);
        bool adjustWiper(Register registerAddress);
        uint16_t readCommand(Register registerAddress);

    public:
        MCP4132();
        ~MCP4132();
        void configure
        (
            const uint8_t pinMOSI,
            const uint8_t pinMISO,
            const uint8_t pinSCK,
            const uint8_t pinCS,
            const Resistance maxResistance
        );
        bool increase(); // Increase resistance in 78 ohms
        bool decrease(); // Decrease resistance in 78 ohms
        bool reset(); // Reset wiper value to default configuration
        bool setResistance(uint16_t value); // Set value between 75 ohms and 10000 ohms
        bool disableWiper(); // Disconnect wiper from the circuit
        bool enableWiper();  // Connect wiper from the circuit
        bool disableTerminal(); // Disconnect terminal from the circuit
        bool enableTerminal();  // Connect terminal from the circuit
        uint16_t getResistance(); // Get current resistance value in ohms
        uint16_t getWiperPosition(); // Get current position of wiper (7 bits)
        bool isShutDownMode(); // Get status of the device

};

#endif // __MCP4132_H__