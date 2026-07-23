# Arduino Environmental Monitor

## Overview

This is a project I worked on to learn how to use the Arduino R4 board while also building a practical device that monitors the temperature, power drawn, time and displays it on a small screen. Throughout the time I worked on this project I gained experience with the Arduino IDE, common electronic used libraries, electronic components, circuit design, and integrated multiple modules into a single working system.
What began as a simple breadboard prototype eventually evolved into a complete hardware project. After making sure that the circuit I designed worked, I wanted to make it more professional looking. I created a custom PCB that mounts directly on top of the Arduino Uno R4, creating a much cleaner and more reliable design with fewer jumper wires.

The finished project displays environmental data, power consumption, and the current time on a 1.3-inch OLED display.

---

## Features

- Measures ambient temperature, humidity, and air pressure using a BME280 sensor
- Obtains voltage and current drawn using an INA219 sensor
- Displays information on a 1.3 inch OLED display
- Synchronizes a clock over WiFi for an accurate local time
- Push buttons were placed to navigate between different display screens
- Custom PCB shield HAT designed in KiCad for a clean final build

## Development of the Project

### Phase 1 - Breadboard Prototype

The project started with just a breadboard and temperature sensor displaying information on the Arduino IDE. For someone who had never built a project on their own, this was the hardest part. Understanding how libraries work and finding which library is needed for the electronic components was not easy at first. Coding was another part of the project that I was not confident about, however as I kept learning more and expanding the project, I gained more knowledge and confidence.
Once everything implemented was working as intended, I decided that it was time to take the next step.

Features included:
- BME280 environmental sensor
- INA219 current sensor
- OLED display
- Arduino Uno R4

### Phase 2 - Custom PCB

While the breadboard prototype was working as intended, I wanted to make it look less messy and more like a finished product. So I designed a custom PCB in KiCad that mounts directly on top of the Arduino Uno R4. This part helped me understand the KiCAD work flow. From deciding where to place the components, to finding the right footprints. This part was a lot of trial and error, but I am satisfied with the end product.

The PCB includes:
- Through hole components
- Push buttons for the user input
- Headers for the modules
- Integrated power distribution
- Cleaner wiring with a compact layout

## Hardware Used

- Arduino Uno R4 WiFi
- BME280 Environmental Sensor
- INA219 Current Sensor
- 1.3 inch 128×64  OLED Display
- Custom KiCad PCB
- Push Buttons
- DC Barrel Jack
- Breadboard with jumper wires (prototype phase)

## What I Learned

Throughout this project I learned how to:

- Program using the Arduino IDE
- Read sensor data over I²C
- Use commonly used Arduino libraries
- Debug hardware and software issues
- Design PCBs using KiCad
- Route traces and prepare a board for manufacturing
- Solder through hole components
- Integrate multiple modules into a single embedded system
- Synchronize time over Wi-Fi using the Arduino Uno R4

## Future Improvements

- Design a second revision of the PCB
- Design a 3D printed enclosure
- Add data logging to an SD card
- Create a web dashboard for remote monitoring
