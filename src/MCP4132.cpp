#include <MCP4132.h>
#include <SPI.h>


MCP4132::MCP4132() {}

MCP4132::~MCP4132() {}

// Setup the device and configure SPI protocol
void MCP4132::configure
(
    const uint8_t pinMOSI,
    const uint8_t pinMISO,
    const uint8_t pinSCK,
    const uint8_t pinCS,
    const Resistance maxResistance
) {
    _pinMOSI = pinMOSI;
    _pinMISO = pinMISO;
    _pinSCK = pinSCK;
    _pinCS = pinCS;

    _maxResistance = maxResistance;

    pinMode(_pinCS, OUTPUT); // Configure CS as digital output pin
    digitalWrite(_pinCS, HIGH); // Disable SPI transactions

    SPI.begin();

    delay(1000);
}

bool MCP4132::writeCommand(Register registerAddress, uint8_t dataByte) {

    uint8_t commandByte = (registerAddress << 4) | 0x00; // 0x00 is a command for write into a register

    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

    digitalWrite(_pinCS, LOW);

    uint8_t byte1 = SPI.transfer(commandByte); // Send command byte and receive MSB
    uint8_t byte2 = SPI.transfer(dataByte);    // Send data byte and receive LSB

    digitalWrite(_pinCS, HIGH);

    SPI.endTransaction();

    uint16_t dataReceived = ((uint16_t)byte1 << 8) | byte2;

    return dataReceived == 0xFFFF;
}

bool MCP4132::adjustWiper(Register registerAddress) {
    
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

    digitalWrite(_pinCS, LOW);

    uint8_t dataReceived = SPI.transfer(registerAddress);

    digitalWrite(_pinCS, HIGH);

    SPI.endTransaction();

    return dataReceived & (1 << 1);
    
}

uint16_t MCP4132::readCommand(Register registerAddress) {

    uint8_t address = (registerAddress << 4) | 0x0C; // 0x0C is a command for read a register
    
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

    digitalWrite(_pinCS, LOW);

    uint8_t byte1 = SPI.transfer(address);
    uint8_t byte2 = SPI.transfer(0x00); // Send dummy data

    digitalWrite(_pinCS, HIGH);

    SPI.endTransaction();

    uint16_t dataReceived = ((uint16_t)byte1 << 8) | byte2;
    
    // Validate if bit 9 (Error bit) is 1, else return 0x0000 (Error)
    return dataReceived & (1 << 9) ? dataReceived : 0x0000;
}

// Get current position of wiper (7 bits)
uint16_t MCP4132::getWiperPosition() {
    return readCommand(WIPER) & 0xFF;
}

// Increase resistance in aprox. 78 ohms
bool MCP4132::increase() {
    uint8_t wiperPosition = getWiperPosition();
    if(wiperPosition < 127) {
        if (adjustWiper(INCREASE)) {
            return true;
        }
    }
    return false;
}

// Decrease resistance in aprox. 78 ohms
bool MCP4132::decrease() {
    uint8_t wiperPosition = getWiperPosition();
    if(wiperPosition > 0) {
        if (adjustWiper(DECREASE)) {
            return true;
        }
    }
    return false; // Indica un fallo en la operación
}

// Reset wiper value to default configuration (Middle value)
bool MCP4132::reset() {
    uint8_t wiperPosition = 0x40; // 64 --> 128/2
    bool success = writeCommand(WIPER, wiperPosition);
    return success;
}

// Set value between 75 ohms and 10000 ohms
bool MCP4132::setResistance(uint16_t value) {
    if(value > _maxResistance) {
        value = _maxResistance;
    }
    else if(value < _wiperResistance) {
        value = _wiperResistance;
    }

    uint32_t numerator = (static_cast<uint32_t>(value) - _wiperResistance) * 128 + (_maxResistance / 2);
    uint8_t wiperPosition = static_cast<uint8_t>(numerator / _maxResistance);

    bool success = writeCommand(WIPER, wiperPosition);

    return success;
}

// Disconnect wiper from the circuit
bool MCP4132::disableWiper() {
    uint16_t regData = readCommand(TCON);
    if(regData == 0x0000) {
        return false; // Error reading data
    }
    /*
     * Check bit 1 (wiper status)
     * 1: Connected
     * 0: Disconnected
     */
    bool wiperConnected = regData & (1 << 1);
    if(!wiperConnected) {
        return true;
    }
    else {
        uint8_t dataByte = (regData & ~(1 << 1)) & 0xFF; // Clear bit 1 (disconnect wiper);
        return writeCommand(TCON, dataByte); 
    }
}

// Connect wiper from the circuit
bool MCP4132::enableWiper() {
    uint16_t regData = readCommand(TCON);
    if(regData == 0x0000) {
        return false; // Error reading data
    }
    /*
     * Check bit 1 (wiper status)
     * 1: Connected
     * 0: Disconnected
     */
    bool wiperConnected = regData & (1 << 1);
    if(wiperConnected) {
        return true;
    }
    else {
        uint8_t dataByte = (regData | (1 << 1)) & 0xFF; // Set bit 1 (connect wiper);
        return writeCommand(TCON, dataByte); 
    }
}

// Disconnect terminal from the circuit
bool MCP4132::disableTerminal() {
    uint16_t regData = readCommand(TCON);
    if(regData == 0x0000) {
        return false; // Error reading data
    }
    /*
     * Check bit 0 (terminal status)
     * 1: Connected
     * 0: Disconnected
     */
    bool terminalConnected = regData & (1 << 0);
    if(!terminalConnected) {
        return true;
    }
    else {
        uint8_t dataByte = (regData & ~(1 << 0)) & 0xFF; // Clear bit 0 (disconnect terminal);
        return writeCommand(TCON, dataByte); 
    }
}

// Connect terminal from the circuit
bool MCP4132::enableTerminal() {
    uint16_t regData = readCommand(TCON);
    if(regData == 0x0000) {
        return false; // Error reading data
    }
    /*
     * Check bit 0 (terminal status)
     * 1: Connected
     * 0: Disconnected
     */
    bool terminalConnected = regData & (1 << 0);
    if(terminalConnected) {
        return true;
    }
    else {
        uint8_t dataByte = (regData | (1 << 0)) & 0xFF; // Set bit 0 (connect terminal);
        return writeCommand(TCON, dataByte); 
    }
}

// Get status of the device
bool MCP4132::isShutDownMode() {
    uint16_t regData = readCommand(STATUS);
    /*
     * Check bit 1 (SHDN)
     * 1: ShutDown state activated
     * 0: ShutDown state deactivated
     */
    return regData & (1 << 1);
}

// Get current resistance aproximated value in ohms
uint16_t MCP4132::getResistance() {
    uint8_t wiperPosition = getWiperPosition();

    uint32_t numerator = static_cast<uint32_t>(wiperPosition) * _maxResistance + 64UL;
    uint16_t resistance = static_cast<uint16_t>((numerator / 128UL) + _wiperResistance);

    return resistance;
}
