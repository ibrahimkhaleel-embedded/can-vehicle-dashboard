# CAN message table

All messages use **standard 11-bit identifiers**. Payloads are ASCII characters
(digits or short text) so they can be printed directly on the CLCD.

| CAN ID | Name | Sender | Receiver | Payload | Notes |
|--------|------|--------|----------|---------|-------|
| `0x10` | `SPEED_MSG_ID` | ECU1 | ECU3 | 2 ASCII digits + `\0` (DLC 3) | Speed from ADC channel 4, scaled by `/ 10.33` |
| `0x20` | `GEAR_MSG_ID` | ECU1 [confirm] | ECU3 | 2 ASCII characters, e.g. `G1`, `GN`, `GR` | ECU3 displays it at CLCD column 4. Gear codes in ECU1: `ON`, `GN`, `G1`-`G5`, `GR`, `C_`. In the uploaded ECU1 code the selected gear is printed on ECU1's own CLCD, so [confirm whether it is also sent on the bus] |
| `0x30` | `RPM_MSG_ID` | ECU2 | ECU3 | 4 ASCII digits + `\0` (DLC 5) | RPM from ADC channel 4, scaled by `* 5.866` |
| `0x40` | `ENG_TEMP_MSG_ID` | - | - | - | Defined in `msg_id.h`, not used yet |
| `0x50` | `INDICATOR_MSG_ID` | ECU2 | ECU3 | 3 ASCII characters + `\0` (DLC 4): `LEF`, `RIG`, `HAZ`, `OFF` | Controls the CLCD arrow and the indicator LEDs on ECU3 |

**Baud rate:** [add your bus bit rate here]
