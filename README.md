# PopW - Organic Particle Life Simulator

## Overview
This project is a life simulator for organic particles, heavily inspired by and partially based on David R. Miller's **BioSim4** ([GitHub Repository](https://github.com/davidrmiller/biosim4)). I greatly appreciate his work and have used it as a foundation to explore and expand upon similar ideas in artificial life simulations.

In this simulator, simple agents evolve in a isometric 2D grid environment, responding to stimuli and adapting their behavior through simulated evolutionary processes. The goal is to observe how simple rules can give rise to complex behaviors over successive generations.

## Features
- Simulated organic particles that interact, move, and evolve.
- A very simple neural network that models the particle brain 
- Genetic algorithm-based evolution to optimize agent behavior.
- 2D isometric grid world with customizable parameters.
- TODO -- multi-threaded execution for performance.
- TODO -- Visualization tools to observe agent behavior.

## Dependencies
To compile and run this project, you will need:
- A C++17-compliant compiler (e.g., GCC, Clang, MSVC)
- CMake (version 3.10 or higher)
- OpenCV (for visualization)
- Eigen3 (for matrix operations )
- python matplotlib module
- python networkx module
- pythopn scipy

## Directory Structure

```
<popw>/
├── src/                 # Source code files  
├── include/             # Header files
│   └── magic_enum/
├── data_out/            # Resources like textures or configuration files
│   ├── images/          # frames and video 
│   ├── nnets/           # csv for network visualization tool
│   └── logs/            # Logs and stats
├── config/              # Configuration settings
│   └── param.ini/         
├── build/               # Compiled binaries and temporary build files
├── CMakeLists.txt       # CMake build script
└── README.md            # Project documentation

```


## Installation & Usage
Clone the repository and build the project using CMake:

```sh
git clone https://github.com/framorgi/popw
cd popw
mkdir bin && cd bin
cmake ..
cmake --build . -j$(nproc) 
```

Run the simulation with:
```sh
./popw
```

Simulation parameters can be modified in the `param.ini` file.

## Acknowledgments
This project is inspired by **BioSim4** by David R. Miller. Have a look at his original work here: [https://github.com/davidrmiller/biosim4/](https://github.com/davidrmiller/biosim4/).

