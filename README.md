# TSCH Network Interference Analysis: Co-Located Network Performance in Contiki-NG/Cooja

This repository hosts the implementation and simulation framework for our IEEE GLOBECOM-published research paper, *"Towards Co-Located TSCH Networks: An Inter-Network Interference Perspective"*. The project investigates the challenges of **Time-Slotted Channel Hopping (TSCH)** in dense, co-located IoT deployments, focusing on **inter-network interference** and its impact on reliability, latency, and packet delivery.

---

## Key Features

1. **Problem Addressed**:  
   TSCH, while robust in single-network scenarios, faces significant performance degradation when multiple networks operate in proximity due to overlapping schedules and channel-hopping patterns. This work quantifies these interference effects and proposes mitigation strategies.

2. **Methodology**:  
   - Developed a **Contiki-NG/Cooja-based simulation framework** to model co-located TSCH networks.  
   - Analyzed interference patterns under varying network densities, traffic loads, and scheduling policies.  
   - Evaluated metrics like **Packet Delivery Ratio (PDR)**, end-to-end latency, and energy consumption.  

3. **Implementation Highlights**:  
   - **C-based TSCH stack modifications** to simulate inter-network collisions and channel contention.  
   - Custom scripts for **automated topology generation** and **large-scale scenario testing**.  
   - Integration with Cooja for real-time visualization of node interactions and interference events.  

4. **Key Findings**:  
   - Co-located TSCH networks experience **periodic interference** when schedules are uncoordinated, degrading PDR by up to 40% in high-density setups.  
   - **Adaptive scheduling** and **channel-hopping optimizations** (e.g., Latin rectangle-based schemes) can reduce collision rates by 30–50%.  

---

## Repository Structure

├── simulations/ # Cooja simulation files (.csc) and node configurations

├── tsch-modifications/ # Custom TSCH scheduler and collision detection modules

├── scripts/ # Python/MATLAB scripts for data analysis and plotting

├── results/ # Pre-computed results (PDR, latency, energy metrics)

└── docs/ # Paper, presentation slides, and supplementary material

## Getting Started

1. **Dependencies**:  
   - Contiki-NG OS (v4.8+)  
   - Cooja Simulator  
   - Python 3.8+ (for data analysis)  

2. **Run Simulations**:  
   ```bash
   cd simulations/  
   # Example: 3 co-located networks with default parameters  
   make TARGET=cooja connect-router-cooja

## Reproduce Results:

- Use scripts/analyze_interference.py to generate PDR vs. network density plots.

- Refer to docs/paper.pdf for experiment parameters and validation.

## Citation
**if this work aids your research, please cite:**
 ```bash
@inproceedings{van2018towards,
  title={Towards co-located TSCH networks: An inter-network interference perspective},
  author={van Der Lee, Tim and Raza, Saleem and Exarchakos, George and Gunes, Mesut},
  booktitle={2018 IEEE Global Communications Conference (GLOBECOM)},
  pages={1--6},
  year={2018},
  organization={IEEE}
}


**Contributions Welcome**
**Open to collaborations on:**

Extending the framework to support multi-PHY layer interactions (e.g., BLE/TSCH coexistence).

Implementing machine learning-driven scheduling for dynamic interference mitigation.

For questions, contact: saleem.raza@daad-alumni.de
   
