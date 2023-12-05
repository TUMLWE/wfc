# WFC

## Introduction

The present repository contains a SImulink-based framework for the execution, monitoring and coordination of wind farm control strategies on a single wind turbine. The present models have been readapted and redacted. from those used during the wake steering campaign of the project compact wind 2 and developed by the Technical University of munich and the university of oldenburg. The main goal of the project campaign was to conduct  wake steering on a specific wind direction sector (plus the additional toggling with a greedy case). Two separate wake steering strategies were tested simultaneously, thus necessitating a shared platform for execution. a fixed offset toggling is also performed on a different wind direction sector. Simulink models for inflow determination, offset calculation and toggling were developed, which were then converted to C code and implemented on a programmable logic computer. The PLC was then connected to the turbine controller, reading inputs from the scada system and providing back the offseted signal, which was added to the wind turbine misalignment and fed to the wind turbine controller.

##  How to use this repository:


This repository is an extension of the framework for development, deployment and testing of interconnected PLC applications PAL (insert link). This repository contains a set of files and simulink models, which constitute PAL inputs that can be used to deploy a toggler for coordinating different wake steering strategies. For details on PAL setup, model development and how to develop a new project, please refer to the respective documentation. This repository should be placed as a submodule of PAL, which should be added in the \Examples folder of PAL.


## Framework Architecture:
-------------------------------
Following the three layered approach of PAL, three layers have been included in the present framework for wind farm control, ITFC, HOST and SUBMODEL apps. 

An ITFC app, which during the experiments was developed by the wind turbine manufacturer, provided of all necessary data and the connection to the turbine controller was performed by the operator (who developed the "ITFC" app). This includes SCADA data, which were used to monitor the status of the turbines, but also data from a met-mast, which was located in the proximity of the turbines and was used to assess the inflow. The sampling frequency of the PLC system was 10 Hz. 

