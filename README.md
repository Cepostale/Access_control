# 🔑 AccessControl - C++ Campus Security Simulation
This project is a high-fidelity simulation of a centralized badge management and security system. 
Developed in C++17, it manages the interactions between personnel, physical badges, and building readers, all orchestrated by a simulation engine that mimics a real school day.

## 🛠 Technical Prerequisites: C++17
This project relies on modern C++ standards for robust data management
- **Compiler:** A C++17 compatible compiler is required (GCC 7+, Clang 5+, or MSVC 2017+)
- **Build System:** CMake 3.30 or higher
- **Logic Requirements:** The system uses specific STL containers (`std::map`, `std::vector`) and decimal-based time calculations that require C++17 for optimal performance

## 🏗 Project Architecture
The project is divided into three logical layers,ensuring a strict separation between data, hardware simulation, and the central decision engine
### 1. The Decision Core (Logic Layer)
- **Serveur.h:** The "brain" of the system. It centralizes all security rules.
  - **Complex Mapping:** Uses a nested map structure `map<string, map<string, bool>>` to organize data across three levels: **User Status ➔ Building ➔ Access Right**
  - **Access Validation:** Processes `askAcces()` requests and returns a `ResultatVerification` struct, containing both the boolean result and a string explaining the reason for refusal
  - **Persistence:** Handles loading configuration files and saving detailed logs (`saveLogs`)
    
### 2. The Simulation Engine (Control Layer)
- **Scheduler.h:** Manages the lifecycle of the simulation
  - **Time Engine:** Handles a custom clock (`heureSimulation`) where 0.5 represents 30 minutes. The school day is simulated from **07:30 to 19:00**
  - **Event Manager:** Includes `genererEvenementAleatoire()` to simulate peak and off-peak traffic at readers
  - **Automation:** Increments time and triggers reader checks automatically
 
### 3. Entity Models (Data Layer)
- **Personne.h / HeritagePersonne.h:** Defines the users. Uses inheritance to manage different statuses (Student, Staff, etc.)
- **Badge.h / HeritageBadge.h:** Represents the physical tokens
- **LecteurBadge.h:** Simulates the physical hardware located at doors. It interfaces with the `Serveur` to request authorization

## 📁 Project Structure
```
.
├── include/           # Header files (.h)
│   ├── Serveur.h      # Decision logic & Structs
│   ├── Scheduler.h    # Simulation engine
│   ├── Badge.h        # Base entities
│   └── Heritage...h   # Polymorphism & Extensions
├── src/               # Implementation files (.cpp)
│   ├── Serveur.cpp
│   ├── Scheduler.cpp
│   └── ...
├── main.cpp           # Entry point (Simulation Runner)
└── CMakeLists.txt     # Build configuration
```

## 🚀 Installation & Execution
Via CMake
```
# 1. Create build directory
mkdir build && cd build

# 2. Configure the project
cmake ..

# 3. Build the executable
cmake --build .

# 4. Run the simulation
./Projet2025
```

## ⚙️ Key Features
- **Real-time Logging:** Generates a `fichierLogs` containing every access attempt with dual timestamps (Real-world time vs. Simulation time).

- **Dynamic Simulation:** A full day is simulated with specific opening/closing hours (`estHeureOuverture`)

- **Granular Permissions:** Rights are not just "Global," but specifically linked to the building and the user's status

- **Detailed Feedback:** The system provides specific reasons for access denial (e.g., "Wrong Building," "Invalid Time Slot," "Unknown Badge"

## 📝 Entry Point
**Main.cpp:** Acts as the launcher. It initializes the `Scheduler`, loads the configuration into the `Serveur`, and starts the `simulation()` loop to demonstrate the system's ability to handle various security scenarios
