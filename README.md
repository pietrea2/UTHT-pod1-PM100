# Serial CAN Bus

> Documentation for the **Serial CAN Bus** can be found [here](https://drive.google.com/drive/folders/1rzmLET68QOWb4At4mAyN4rDsj-VGBLyh?usp=sharing).


## Todo

- [ ] Setup, testing, and expected output documentation (screenshot, pictures, logs/stack traces, etc.);
- [ ] A list of dependencies (and links to those);
- [ ] Everything else that is listed under [the master `README`](../README.md).
<br>
<br>

# PM100 Inverter/Controller CAN Bus Message Reference

> Prepared by Adam Pietrewicz, adapted to Markdown by Jayden Lefebvre (@JLefebvre55)
> 
> Last Updated - July 14th 2021

***

## Broadcast Messages

> CAN ID: `0x0A0-0x0AF`. See doc for example implementation (pgs. 4-5) and per-byte breakdown (pgs. 5-11).

| Address   | Frequency     | Content                                                 | CAN Active Messages (Low Word)   |
|-----------|---------------|---------------------------------------------------------|----------------------------------|
| `0x0A0`   | Slow/10Hz     | Temperatures #1                                         | `0x0001`                         |
| `0x0A1`   | Slow/10Hz     | Temperatures #2                                         | `0x0002`                         |
| `0x0A2`   | Slow/10Hz     | Temperatures #3                                         | `0x0004`                         |
| `0x0A3`   | Fast/100Hz    | Analog Inputs Voltages                                  | `0x0008`                         |
| `0x0A4`   | Fast/100Hz    | Digital Input Status                                    | `0x0010`                         |
| `0x0A5`   | Fast/100Hz    | Motor Position Information                              | `0x0020`                         |
| `0x0A6`   | Fast/100Hz    | Current Information                                     | `0x0040`                         |
| `0x0A7`   | Fast/100Hz    | Voltage Information                                     | `0x0080`                         |
| `0x0A8`   | Fast/100Hz    | Flux Information                                        | `0x0100`                         |
| `0x0A9`   | Slow/10Hz     | Internal Voltages                                       | `0x0200`                         |
| `0x0AA`   | Fast/100Hz    | Internal States                                         | `0x0400`                         |
| `0x0AB`   | Fast/100Hz    | Fault Codes                                             | `0x0800`                         |
| `0x0AC`   | Fast/100Hz    | Torque & Timer Information                              | `0x1000`                         |
| `0x0AD`   | Fast/100Hz    | Modulation Index & Flux Weakening<br>Output Information | `0x2000`                         |
| `0x0AE`   | Slow/10Hz     | Firmware Information                                    | `0x4000`                         |
| `0x0AF`   | 100Hz (fixed) | Diagnostic Data                                         | `0x8000`                         |

***
## Command Messages

> CAN ID: `0x0C0`. See doc for example implementation (pgs. 2-3).

| Byte(s)  | Name                   | Format           | Description                                                                                                            |
|----------|------------------------|------------------|------------------------------------------------------------------------------------------------------------------------|
| 0, 1     | Torque Command         | Torque           | Torque command used when in torque mode.                                                                               |
| 2, 3     | Speed Command          | Angular Velocity | Speed command used when in speed mode.                                                                                 |
| 4        | Direction Command      | Boolean          | `0` - "Reverse", `1` - "Forward" (See Section 2.3.2.2)                                                                 |
| 5: Bit 0 | Inverter Enable        | Boolean          | `0` - Inverter Off, `1` - Inverter On                                                                                  |
| 5: Bit 1 | Inverter Discharge     | Boolean          | `0` - Disable Discharge, `1` - Enable Discharge                                                                        |
| 5, 2     | Speed Mode Enable      | Boolean          | `0` - Do not override mode, `1` - Overrides from torque <br>mode to speed mode ONLY (See "Using Speed Mode" in manual) |
| 6, 7     | Commanded Torque Limit | Torque           | Motor and Regen Torque limits. If set to `0`, default <br>torque limit from EEPROM is used.                            |

***
## Parameter Messages

> Sets EEPROM parameters.

**CAN ID `0x0C1`** - Used to send message *to* controller.

**CAN ID `0x0C2`** - Response *from* controller.
***