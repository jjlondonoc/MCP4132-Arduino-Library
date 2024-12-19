# MCP4132 Arduino Library API Documentation

## Classes

### `MCP4132`
The main class for interacting with the MCP4132 digital potentiometer.

#### Constructor
- `MCP4132()`: Default constructor for the MCP4132 class.
- `~MCP4132()`: Destructor.

#### Public Methods

1. **`void configure(uint8_t pinMOSI, uint8_t pinMISO, uint8_t pinSCK, uint8_t pinCS, Resistance maxResistance)`**
   - Configures the MCP4132 device and SPI communication.
   - Parameters:
     - `pinMOSI`: SPI MOSI pin.
     - `pinMISO`: SPI MISO pin.
     - `pinSCK`: SPI clock pin.
     - `pinCS`: Chip select pin.
     - `maxResistance`: Maximum resistance value (5kΩ, 10kΩ, 50kΩ, or 100kΩ). See enum section.

2. **`bool increase()`**
   - Increases the resistance by one step (approximately 78 ohms).
   - Returns: `true` if successful, `false` otherwise.

3. **`bool decrease()`**
   - Decreases the resistance by one step.
   - Returns: `true` if successful, `false` otherwise.

4. **`bool reset()`**
   - Resets the wiper position to its default value (midpoint).
   - Returns: `true` if successful, `false` otherwise.

5. **`bool setResistance(uint16_t value)`**
   - Sets the resistance value.
   - Parameters:
     - `value`: Desired resistance in ohms (must be within the device's range).
   - Returns: `true` if successful, `false` otherwise.

6. **`bool disableWiper()`**
   - Disconnects the wiper from the circuit.
   - Returns: `true` if successful, `false` otherwise.

7. **`bool enableWiper()`**
   - Connects the wiper to the circuit.
   - Returns: `true` if successful, `false` otherwise.

8. **`bool disableTerminal()`**
   - Disconnects the terminal from the circuit.
   - Returns: `true` if successful, `false` otherwise.

9. **`bool enableTerminal()`**
   - Connects the terminal to the circuit.
   - Returns: `true` if successful, `false` otherwise.

10. **`uint16_t getResistance()`**
    - Retrieves the current resistance value in ohms.
    - Returns: Resistance value.

11. **`uint16_t getWiperPosition()`**
    - Retrieves the current wiper position (7 bits, 0-127).
    - Returns: Wiper position.

12. **`bool isShutDownMode()`**
    - Checks if the device is in shutdown mode.
    - Returns: `true` if in shutdown mode, `false` otherwise.

---

### Enums

#### `Resistance`
Defines the available resistance models:
- `MODEL_5K = 5000`
- `MODEL_10K = 10000`
- `MODEL_50K = 50000`
- `MODEL_100K = 100000`

---

## Notes
- The MCP4132 has a wiper resistance of approximately 75 ohms.
- Ensure SPI is properly configured before communicating with the device.
- Shutdown mode disconnects the wiper and terminal connections to save power.
