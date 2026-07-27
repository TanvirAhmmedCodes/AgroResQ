<div align="center">

# 🌱 AgroResQ

### Intelligent Disaster Relief & Smart Agriculture Ecosystem

*A C++ Decision Support System for Disaster Management and Post-Disaster Agricultural Recovery*

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)
![Platform](https://img.shields.io/badge/Platform-Console-green)
![Database](https://img.shields.io/badge/Database-File%20Handling-orange)
![Architecture](https://img.shields.io/badge/Architecture-Layered-success)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)

</div>

---

# 📖 About AgroResQ

AgroResQ is an intelligent **Decision Support System (DSS)** developed in C++ for the **SDP 100 (Software Development Project)** course.

The project combines two important domains into a single software platform:

- 🚨 Disaster Relief Management
- 🌾 Smart Agriculture Recovery

The system helps emergency responders efficiently register disasters, manage victims, allocate shelters, coordinate rescue teams, distribute relief resources, and estimate operational costs. After the disaster, the agriculture module assists farmers by analyzing soil conditions, recommending suitable crops, planning irrigation schedules, and predicting crop diseases to accelerate agricultural recovery.

---

# 🎯 Project Objectives

- Digitally manage disaster information.
- Register and manage affected victims and families.
- Prioritize rescue operations.
- Allocate shelters intelligently.
- Manage relief resources.
- Coordinate rescue teams and volunteers.
- Monitor soil conditions.
- Recommend suitable crops.
- Predict agricultural risks.
- Generate reports for decision making.

---

# ✨ Major Features

## 🚨 Disaster Management Module

- Disaster Registration
- Victim Registration
- Family Management
- Rescue Team Management
- Volunteer Management
- Shelter Allocation
- Relief Resource Management
- Relief Distribution
- Emergency Alert System
- Rescue Priority Scheduling
- Route Optimization
- Budget Estimation

---

## 🌾 Smart Agriculture Module

- Farm Management
- Crop Management
- Weather Information
- Soil Monitoring
- Soil Health Score
- Crop Recommendation
- Irrigation Planning
- Crop Disease Prediction
- Agricultural Recovery Planning
- Decision Support System

---

## 📊 Reporting Module

- Report Generation
- Data Summary
- Disaster Statistics
- Agriculture Statistics

---

# 🏛️ Project Architecture

```
                    User Interface
                           │
                ┌──────────┴──────────┐
                │                     │
        Disaster Module      Agriculture Module
                │                     │
          Service Layer        Service Layer
                │                     │
         Repository Layer      Repository Layer
                │                     │
           File Handling Database
```

---

# 📂 Complete Project Structure

```text
AgroResQ
│
├── algorithms/
├── core/
├── data_structures/
├── entities/
├── hardware/
├── repositories/
│   ├── agriculture/
│   ├── disaster/
│   ├── report/
│   └── victim/
├── services/
├── ui/
├── database/
├── docs/
│
├── main.cpp
├── README.md
└── .gitignore
```

---

# 🧠 Algorithms Used

## Disaster Algorithms

- Rescue Priority Calculator
- Shelter Allocation Algorithm
- Relief Distribution Algorithm
- Emergency Alert System
- Budget Calculator

---

## Agriculture Algorithms

- Crop Recommendation
- Soil Health Score
- Disease Prediction
- Irrigation Planner
- Recovery Planner
- Decision Support Engine

---

# 📚 Data Structures Used

- Linked List
- Queue
- Priority Queue
- Graph

---

# 💾 Database

The project uses **File Handling** as the storage system.

```
database/

crops.txt
disaster.txt
families.txt
farms.txt
relief.txt
reports.txt
rescueTeams.txt
shelters.txt
soil.txt
victims.txt
volunteers.txt
weather.txt
```

---

# 📦 Core Components

## Core

- BaseEntity
- Validator
- FileManager
- IDGenerator
- Color Utility

---

## Hardware Simulation

The agriculture module supports sensor abstraction.

Components:

- ISensor
- RealSensor
- SimulatedSensor
- SensorFactory
- SensorService

---

# 👨‍💻 Team Members

| Name | Student ID | Responsibility |
|------|------------|----------------|
| **S. M. Masrur Rafin** | 20254103164 | Disaster Module Lead |
| **Abu Hourira MD Abdul Aziz** | 20254103163 | Victim & Shelter Management |
| **MD Tanvir Ahmmed** | 20254103191 | Agriculture Module Lead |
| **Ishraq Ahmmed** | 20254103173 | Agriculture Data & Algorithms |
| **Suborna Akter** | 20254103352 | Testing, Documentation & Report Generation |

---

# ⚙️ Technologies Used

- C++
- Object-Oriented Programming (OOP)
- File Handling
- Data Structures
- Graph Algorithms
- Priority Queue
- Decision Support System
- Code::Blocks
- Visual Studio Code
- Git
- GitHub

---

# 🚀 How to Build

## Clone Repository

```bash
git clone https://github.com/TanvirAhmmedCodes/AgroResQ.git
```

---

## Compile

Using g++

```bash
g++ main.cpp -o AgroResQ
```

Or simply open the project in:

- Code::Blocks
- Visual Studio Code

Build and Run.

---

# 📄 Documentation

The `docs/` directory contains:

- Project Proposal
- SDP Final Report
- User Manual

---

# 🌍 Sustainable Development Goals

- SDG 2 – Zero Hunger
- SDG 3 – Good Health and Well-being
- SDG 11 – Sustainable Cities and Communities
- SDG 13 – Climate Action

---

# 🔮 Future Improvements

- GIS Map Integration
- Real-Time Weather API
- SMS Alert Integration
- IoT Sensor Connectivity
- Cloud Database
- Mobile Application
- AI-based Disaster Prediction
- Machine Learning Crop Recommendation

---

# 📜 License

This project was developed solely for academic purposes as part of the **Software Development Project (SDP 100)** at **Bangladesh University of Business and Technology (BUBT)**.

---

<div align="center">

## Team AgroResQ

### Intelligent Disaster Relief & Smart Agriculture Ecosystem

**Developed using C++ with Object-Oriented Programming and Data Structures**

© 2026 Team AgroResQ | BUBT

</div>