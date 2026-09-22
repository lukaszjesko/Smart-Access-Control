# Smart Access Control — RFID + PIN Door Lock

Two-factor access control terminal on a custom PCB. Verification combines
something you **have** (a 13.56 MHz contactless card) with something you
**know** (a 4-digit PIN), driving an electric strike through a relay.


![Assembled board](docs/img/board.jpg)

---

## Status

| Stage | State |
|---|---|
| Firmware | Working — validated on breadboard |
| Schematic | Complete, ERC clean |
| PCB layout | v1.0 routed, 2-layer, 53.6 × 61.5 mm |
| Fabrication | v1.1 in preparation — v1.0 was **not** ordered; review caught blocking errors first |
| Bring-up measurements | Pending |

This is an active learning project. Section
[Known limitations](#known-limitations) lists what I found wrong in v1.0
and why. I consider that list the most useful part of this repository.

---

## Why this project

I wanted one device that forced me through the full hardware workflow rather
than a breadboard demo: requirements, schematic capture, footprint assignment,
layout, design rule check, manufacturing output, assembly, and bring-up.
Access control was chosen because its failure modes are interesting — a lock
that fails open is a security problem, and a lock that fails closed is a
safety problem.

---

## How it works

```
        ┌──────────────┐  SPI   ┌─────────────┐
        │  MFRC522     │◄──────►│             │
        │  RFID reader │        │             │
        └──────────────┘        │             │
                                │  ATmega328P │  GPIO   ┌────────────┐  12 V
        ┌──────────────┐  GPIO  │  (Nano)     │────────►│   Relay    │───────►
        │  4×4 keypad  │◄──────►│             │         │            │  strike
        └──────────────┘        │             │         └────────────┘
                                │             │
        ┌──────────────┐  I2C   │             │  GPIO   ┌────────────┐
        │  LCD 16×2    │◄──────►│             │────────►│ LEDs, buzz │
        └──────────────┘        └─────────────┘         └────────────┘
```

The firmware is a finite state machine with five states:

```
WAIT_FOR_CARD ──card matches──► WAIT_FOR_PIN ──► ENTERING_PIN
      ▲                                                │
      │                                    ┌───────────┴───────────┐
      │                                    ▼                       ▼
      └────────────────────────────── GRANTED                  DENIED
```

Access requires **both** factors. A valid card alone does not unlock the door.

---

## Hardware

### Pin map

| Function | Signal | Pin | Notes |
|---|---|---|---|
| RFID | SDA / SS | D10 | SPI chip select |
| RFID | MOSI | D11 | |
| RFID | MISO | D12 | |
| RFID | SCK | D13 | |
| LCD | SDA | A4 | I²C, address 0x27 |
| LCD | SCL | A5 | |
| Keypad | Rows R1–R4 | D6–D9 | |
| Keypad | Cols C1–C4 | D5–D2 | |
| Buzzer | — | A0 | |
| LED green | — | A1 | |
| LED red | — | A2 | |
| Relay | — | A3 | **Active LOW** |

### Design decisions

**Relay driven active LOW, initialised HIGH before `pinMode()`.**
During early testing the strike pulsed briefly at power-up. The relay module
is active LOW, so the pin's default state after reset released the lock for a
few milliseconds. Writing HIGH *before* configuring the pin as an output
removes the glitch. A lock that opens on every power cycle is not a lock.

**RFID reader on a connector, not on the board.**
The MFRC522 carries a tuned 13.56 MHz antenna. Putting an untuned antenna on
my own two-layer board would have meant an RF design problem I was not ready
to solve, so v1.0 uses the module on a header.

**Ground pour on the bottom layer** to shorten return paths for the SPI bus
and give the relay switching current somewhere low-impedance to go.

---

## Security analysis

Honest assessment of this design. None of these are hypothetical.

| Weakness | Impact | Mitigation in v1.1 |
|---|---|---|
| Authentication uses only the card **UID** | MIFARE Classic UIDs are readable by any phone with NFC and writable on cheap magic cards, so the card factor can be cloned in under a minute | Move to MIFARE DESFire EV3 with AES challenge–response, where the key never crosses the air interface |
| No lockout on failed PIN attempts | 4 digits is 10 000 combinations against a fixed 2 s penalty — roughly 5.5 hours of unattended guessing | Lock out after 5 attempts with exponential backoff, persisted to EEPROM so a power cycle does not reset it |
| No session timeout after a valid card | Present a card, walk away, and the terminal waits indefinitely for a PIN from anyone | 15 s timeout back to idle |
| PIN stored in plaintext in firmware | Anyone who dumps flash over ICSP reads the PIN | Store a salted hash in EEPROM; compare in constant time |
| Credentials are compile-time constants | Adding a user means reflashing | Master-card enrolment, users in EEPROM |
| MCU flash is readable | Full firmware and secrets extractable | Set the AVR lock bits |

**Not addressed by this design:** an attacker with physical access to the
*secure side* can simply bridge the relay contacts. Like most commercial
terminals, this device assumes the controller and wiring are on the protected
side of the door. Real installations put the decision logic inside and only
the reader outside — which is exactly what the OSDP protocol exists for, and
where v2 is headed.

---

## Known limitations

Found during review of v1.0. All fixed in v1.1 before fabrication.

**Hardware**
- **Both status LEDs are reversed in the schematic.** The Arduino pin drives the
  cathode through the resistor and the anode sits at ground, so the LEDs are
  reverse-biased and can never light, whatever the firmware does. Verified in the
  board file: `D1 pad 1 (K) -> Net-(D1-K) -> R1 -> A2`, `D1 pad 2 (A) -> GND`.
  Caught during review before fabrication, which is exactly why a board gets
  reviewed before money is spent on it.
- **Keypad connector order does not match a standard membrane ribbon.** J2 is
  wired C4 C3 C2 C1 R1 R2 R3 R4; the usual flat cable is R1 R2 R3 R4 C1 C2 C3 C4.
  To be confirmed against the actual keypad, then fixed in `keys[][]` rather
  than on the board.
- No decoupling capacitors. Every IC needs 100 nF at its supply pin, plus bulk
  capacitance at the board input. The supply dip I worked around in firmware
  was a hardware problem.
- All nets routed at 0.25 mm, including +5 V and GND. Power nets need their
  own net class at 0.5–0.8 mm.
- No mounting holes. The board cannot be fixed to an enclosure.
- Buzzer driven directly from a GPIO pin, above the recommended per-pin
  current for the ATmega328P. Needs a transistor and a flyback diode.
- MFRC522 SPI lines driven at 5 V logic, while the datasheet limits inputs to
  VDD + 0.5 V. Needs level shifting on MOSI, SCK and SS.
- Reader reset line left unconnected, so a hung reader cannot be recovered.

**Firmware**
- Uses `String` on a 2 kB RAM part — heap fragmentation risk. Replace with a
  fixed `char` buffer.
- `delay()` inside the state machine blocks the keypad and reader for up to
  3 seconds. Replace with `millis()`-based timing.
- No check that the reader is present at boot; an unplugged module fails
  silently.
- Successful UIDs are printed to the serial port.

---

## Repository layout

```
├── src/                     firmware (PlatformIO, Arduino framework)
├── include/
│   └── config.example.h     copy to config.h and fill in — config.h is gitignored
├── hardware/                KiCad 10 project
│   └── production/          Gerber + drill files
└── docs/img/                photos and renders
```

## Build

```bash
cp include/config.example.h include/config.h   
pio run --target upload
```

Requires [PlatformIO](https://platformio.org/). Target: `nanoatmega328new`.

## Licence

Firmware: MIT. Hardware: [CERN-OHL-S-2.0](https://ohwr.org/cern_ohl_s_v2.txt).
