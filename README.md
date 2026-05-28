# Traffic Light System 🚦

This repository contains an embedded systems project developed using Arduino during my embedded lab course. The project started as a simple traffic light controller and gradually evolved into a smart pedestrian crossing system using sensors, timing systems, and communication between multiple Arduino boards.

The main goal of the project was to understand how embedded systems work by combining hardware and software to simulate a real-world traffic light intersection.

---

# Project Overview

The system controls:
- Vehicle traffic lights (Red, Yellow, Green)
- Pedestrian crossing lights
- Pedestrian crossing requests
- Vehicle detection using sensors

Different tasks were completed throughout the project, with each task adding more functionality and complexity to the system.

---

# Features

- Traffic light control using Finite State Machines (FSM)
- Pedestrian crossing system with safe timing logic
- Real hardware implementation using Arduino Uno
- Master/Slave communication using I2C (`Wire.h`)
- IR sensor integration for pedestrian detection
- Ultrasonic sensor integration for vehicle detection
- Smart safety logic to prevent unsafe pedestrian crossing
- Real-time timing using `millis()`

---

# Tasks

## Task 1 — Basic Traffic Light FSM
Implemented a basic traffic light system using red, yellow, and green LEDs.  
The system cycles continuously using a finite state machine.

## Task 2 — Pedestrian Crossing System
Added pedestrian LEDs and a push button that allows pedestrians to request crossing safely.

## Task 3 — Hardware Implementation
Implemented the Task 1 simulation using real Arduino hardware and tested the traffic light behavior physically.

## Task 4 — Hardware Pedestrian System
Implemented the pedestrian crossing system on real hardware using LEDs and push buttons.

## Task 5 — I2C Master/Slave System
Split the project into two Arduino boards:
- Master Arduino controls the traffic lights and state machine
- Slave Arduino handles pedestrian LEDs and button input

Both boards communicate using I2C communication.

## Task 6 — Smart Traffic System
Final version of the project using:
- IR Sensor
- Ultrasonic Sensor

The system detects nearby vehicles and prevents pedestrians from crossing when the road is unsafe.

---

# Hardware Used

- Arduino Uno
- LEDs
- Push Button
- Breadboard
- IR Sensor
- HC-SR04 Ultrasonic Sensor
- Resistors
- Jumper Wires

---

# Technologies Used

- Arduino IDE
- C/C++
- Embedded Systems Design
- Finite State Machines
- I2C Communication (`Wire.h`)

---

# What I Learned

Through this project I learned:
- How finite state machines are used in embedded systems
- How to interface sensors with Arduino
- How communication between microcontrollers works using I2C
- How hardware and software interact together
- How to debug and test embedded systems projects
- How to design safer and smarter control systems

---

# Repository Structure

Traffic-Light-System/
│
├── Diagrams/
├── presentation/
├── task-1-basic-fsm/
├── task-2-pedestrian-crossing/
├── task-3-hardware-fsm/
├── task-4-hardware-pedestrian/
├── task-5-i2c-master-slave/
├── task-6-smart-traffic-system/
└── README.md
