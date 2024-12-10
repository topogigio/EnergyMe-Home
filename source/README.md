# EnergyMe - Home | Source Code

## Technical Overview

The system consists of an ESP32 microcontroller interfacing with an ADE7953 energy measurement IC via SPI, capable of monitoring:

- 1 direct channel (channel 0)
- 16 multiplexed channels
- Supports both single-phase and three-phase measurements
- Real-time monitoring of voltage, current, power (active/reactive/apparent), power factor, and energy

## Core Components

### ADE7953

Handles energy measurements with features like:

- No-load threshold detection
- Phase calibration
- Multiple measurement modes (voltage, current, power, energy)
- Line cycle accumulation mode for improved accuracy

### Additional Components

- **Multiplexer**: Manages channel switching for the 16 secondary channels
- **SPIFFS**: Stores configuration and calibration data
- **Web Interface**: Provides configuration and monitoring capabilities
- **MQTT**: Enables remote data logging and device management
- **Modbus TCP**: Industrial protocol support

## Secrets Management

The codebase includes critical security elements:

secrets/
  ├── ca.pem           # AWS IoT Root CA
  ├── certclaim.pem    # Device certificate for AWS IoT
  ├── privateclaim.pem # Device private key
  ├── endpoint.txt     # AWS IoT endpoint
  ├── rulemeter.txt    # AWS IoT rule configuration
  └── encryptionkey.txt # Local data encryption key

These are used for:

- Secure MQTT communication with AWS IoT Core
- Device provisioning and authentication
- Local data encryption

## Data Storage

Configuration data is stored in JSON files:

- **calibration.json**: Measurement calibration values
- **channel.json**: Channel configuration
- **energy.json**: Energy accumulation data
- **daily-energy.json**: Daily energy statistics

## Measurement Process

- Direct channel (0) reads voltage as reference
- Multiplexed channels (1-16) use voltage from channel 0
- Current measurement per channel
- Power calculations:
  - Active power from energy accumulation
  - Reactive power calculated from apparent and active power
  - Power factor compensation for three-phase loads

## Calibration

Calibration parameters include:

- LSB values for voltage, current, power measurements
- Phase calibration for accurate power factor readings
- No-load thresholds to eliminate noise
