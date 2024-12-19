# MCP4132 Library Examples

This folder contains examples that demonstrate how to use the MCP4132 library. Each example focuses on a specific feature or functionality of the MCP4132 digital potentiometer, allowing users to understand and implement the library effectively.

## Examples Included

### 1. `Basic-usage`
This example demonstrates the basic functionality of the MCP4132 library, including:
- Configuring the MCP4132 for SPI communication.
- Reading the initial resistance and wiper position.
- Increasing, decreasing, and setting resistance values.
- Enabling and disabling the wiper and terminal connections.
- Checking and handling the shutdown mode.

### How to Use
1. Open the example folder (`basic_usage`) in the Arduino IDE.
2. Upload the `basic_usage.ino` file to your microcontroller.
3. Open the Serial Monitor (Ctrl + Shift + M) at 9600 baud to interact with the example.
4. Send the following commands to test functionality:
   - **`i`**: Increase resistance by one step.
   - **`d`**: Decrease resistance by one step.
   - **`r`**: Reset the wiper to its default midpoint position.
   - **`s`**: Set resistance to 3400 ohms.
   - **`w`**: Disable the wiper connection.
   - **`e`**: Enable the wiper connection.
   - **`t`**: Disable the terminal connection.
   - **`f`**: Enable the terminal connection.

### Notes
- Ensure your hardware is connected correctly:
  - MOSI, MISO, SCK, and CS pins configured in the code.
  - Proper power supply to the MCP4132.
- This example uses the **MODEL_10K** resistance model. Adjust if necessary.

---

## License
All examples are provided under the MIT License. See the main `README.md` for more details.

## Author
Juan José Londoño
