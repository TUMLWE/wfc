---
title: >-
  A framework for the coordination of Wake Steering strategies

authors:
  - name: Carlo R Sucameli
    affiliation: 1
  - name: Filippo Campagnolo
    affiliation: 1
  - name: Vlaho Petrović
    affiliation: 2
  - name: Paul Hulsman
    affiliation: 2
  - name: Carlo L Bottasso
    affiliation: 1    
affiliations:
 - name: Lehrstuhl für Windenergie, Technische Universität München
   index: 1
 - name: ForWind – Center for Wind Energy Research, Institute of Physics, University of Oldenburg
   index: 2
---

# A framework for the coordination of Wake Steering strategies

## Table of Contents

- [A framework for the coordination of Wake Steering strategies](#a-framework-for-the-coordination-of-Wake-Steering-strategies)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [How to use this repository](#How-to-use-this-repository)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
  - [Usage](#usage)
    - [General Framework Architecture](#General-Framework-Architecture)
    - [Wake Steering Application](#Wake-Steering-Application)
  - [Support](#Support)
  - [License](#license)
  - [Acknowledgments](#acknowledgments)


## Introduction

The present repository contains a Simulink-based framework for the execution, monitoring and coordination of wake steering strategies on a single wind turbine. This framework, generalized to exclude any confidential information, was used to coordinate two different sets of experiments. The first aimed at wind power maximization through wake steering, and the second aimed at applying fixed offsets to a wind turbine to characterize its wake through LiDARs. The experiments were conducted jointly by the Lehrstuhl für Windenergie of the Technische Universität München and by the ForWind – Center for Wind Energy Research of the University of Oldenburg. The experimental test site is located in the north of Germany, and is composed of two-wind turbines. An aerial view of the test site is provided [below](./docs/overview_testsite.png)

![testsite](./docs/overview_testsite.png "Overview of the test site")

Wind turbine orientation was controlled through a programmable logic computer (PLC) installed at the base of WT1. During the experiment, wind direction and speed was measured through a met-mast installed approximately 300m north of the turbine. This inflow was used to determine the wind direction sector, which was used to assess which offset to provide as an additional input to the wind vane sensor installed on the turbine nacelle, which was therefore fed to the wind turbine controller.


## Getting Started:

### Prerequisites:
### Installation:

This repository is an extension of the framework for development, deployment and testing of interconnected PLC applications PAL (insert link). This repository contains a set of files and simulink models, which constitute PAL inputs that can be used to deploy a toggler for coordinating different wake steering strategies. For details on PAL setup, model development and how to develop a new project, please refer to the respective documentation. This repository should be placed as a submodule of PAL, which should be added in the \Examples folder of PAL.


## Usage

### General Framework Architecture
------------------------------------

Following the three layered approach of PAL, three layers have been included in the present framework for wind farm control, ITFC, HOST and SUBMODEL apps. In the experiment, the framework run on a Bachmann plc

An ITFC app, which during the experiments was developed by the wind turbine manufacturer, provided of all necessary data and the connection to the turbine controller was performed by the operator (who developed the "ITFC" app). This includes SCADA data, which were used to monitor the status of the turbines, but also data from a met-mast, which was located in the proximity of the turbines and was used to assess the inflow. The sampling frequency of the PLC system was 10 Hz. 

A HOST model is tasked with activities such as reading and writing data to and from ITFC applications, as well as hosting data for SUBMODEL access (both read and write), as well as generating the output .txt files.

As described in details in the PAL - User Manual (insert link), SUBMODEL applications perform all the higher level tasks, and are provided in the form of Simulink models. 

Mention the different inputfiles

### Wake Steering Application

An overview of the SUBMODELS that compose the present framework are shown in the following [figure](./docs/wfc_framework_apps.png). A description of each application type is provided below:

![WFC Framework](./docs/wfc_framework_apps.png)

**INFLW**

INFLW blocks perform the task of determining inflow conditions from available inflow measurements, in order to feed them as input for LUT interpolation present in a **OFFSET** block. Two identical Simulink models and **init_** files are provided in the present case for both **INFLW** blocks, but in principle they could be different, to accommodate different design choice of different wake steering strategies. 

In the present example, wind speed inflow is read at two different heights (116.3 and 54.2m), and is used to calculate averaged wind speeds, turbulence intensity and the shear exponent. Wind direction is also provided and averaged. Different moving averagings can be selected for each inflow quantity through the **init_** file. The Simulink model also performs additional checks and the inputs and flags errors if signals are frozen of NaN. The status of the INFLW block i.e. the availability of outputs signals is encoded as a 4 bit signal, which is then converted to integer and provided as an additional output of the model through the variable "output_InflowOK".

**OFFSET**

OFFSET blocks calculate the offsets, which are then fed to the TOGGLER app. 

In the present example, three OFFSET blocks are included. Just as **INFLW**, OFFSET_1 and OFFSET_2 are identical and read inputs from INFLW_1 and INFLW_2, respectively. These very simple Simulink models interpolate sample 4-dimensional LUT. These two offsets are toggled together with a Greedy offset within "Sector 1". OFFSET_3 provides a Simulink model which can be used for fixed offset calculation. This model does not require inputs. Generally speaking, it is not necessary to separate **INFLW** from **OFFSET**, which was done here to increase modularity.

**TOGGLER**

The main supervision task is performed by the "TOGGLER" application, which performs important tasks such as determining which strategy offset should be fed to the HOST (and therefore, to the turbine controller), according to a user-defined sequence. The "TOGGLER" also ensures that WFC is active only within prescribed inflow conditions. A thorough description of the wake steering applications will be provided in the full paper version. A schematics of the TOGGLER application is shown [below](./docs/wfc_framework_apps.png)

![Toggler](./docs/wfc_framework_apps.png)

Generally speaking, the TOGGLER block read its inputs from HOST (like any other application). Information about the inflow characteristics are used to assess which wind direction sector is active and, if so, whether wind conditions are suitable for offset provision. Furthermore, the wind turbine operational status is used to ensure the turbine is in power production. A WFC_status monitors the status of the operations, similarly to the variable "output_InflowOK" of the **INFLW** blocks. 

Simultaneously, a check is performed to verify the availability of the other applications within the PLC, through the status variables of the other SUBMODELS (see PAL documentation for details). This ensures that offset is selected only from active strategies. Manual toggling of strategies is also provided. A further histeresis block is added to prevent rapid switching on and off of the framework (for examples when operating close to the wind directions or wind speed boundaries).

Toggling is performed on all available strategies of the active sector, on a user-defined time interval (in the present example set to 35 minutes). It is worth reminding that in the Simulink model included, an additional non-controlled "Greedy" was included as a reference, whose offset was set to zero.

Additional time-management functionalities are included to prioritize strategies that have been run less time than others, and can be activated and defined through the relative **init** file.

Offsets from all the **OFFSET** applications are provided as inputs to the **TOGGLER** application. The appropriate strategy is selected from all the available offsets based on the above mentioned checks. 

The demanded offset can be further passed through a "Saturation block" (a "dummy" version is included in the present example), which can be used to perform additional processing on the signal. During the experiments of CompactWind2, for example, this block was built based on the wind turbine yaw controller to prevent involuntary shutdown during sudden switch of wake steering strategy. Clipping of the yaw offset according to manufacturer requirements can also be applied, if necessary.

## Support

For any questions, bug reports, or code-related queries, please use [GitHub Issues](https://github.com/TUMLWE/WFC/issues). 

For general questions, feel free to contact Carlo Sucameli (carlo.sucameli@tum.de) 


## License

This software is licensed under Apache License Version 2.0.

## Acknowledgements



# A Framework for the Coordination of Wake Steering Strategies

## Table of Contents

- [Introduction](#introduction)
- [How to Use This Repository](#how-to-use-this-repository)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
  - [General Framework Architecture](#general-framework-architecture)
  - [Wake Steering Application](#wake-steering-application)
- [Support](#support)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Introduction

This repository contains a Simulink-based framework designed for the execution, monitoring, and coordination of wake steering strategies on a single wind turbine. Generalized to exclude any confidential information, the framework was utilized to coordinate two sets of experiments: one aimed at wind power maximization through wake steering, and the other at applying fixed offsets to a wind turbine for wake characterization using LiDARs. These experiments were conducted collaboratively by the Lehrstuhl für Windenergie at the Technische Universität München and the ForWind – Center for Wind Energy Research at the University of Oldenburg. The experimental site, located in northern Germany, comprises two wind turbines. An aerial view of the test site is provided [here](./docs/overview_testsite.png).

![testsite](./docs/overview_testsite.png "Overview of the test site")

Wind direction and speed were measured by a met-mast located approximately 300m north of the turbine. This inflow data determined the wind direction sector and, subsequently, the offset calculation. This offset, combined with the misalignment provided by a wind vane sensor on the turbine nacelle, formed a signal that was then fed into the wind turbine controller. The offset calculation, was performed through a programmable logic computer (PLC) installed at the base of WT1.

## How to Use This Repository

### Prerequisites:

This repository is an extension of PAL, a Matlab-based framework for the development, deployment, and testing of interconnected PLC applications PAL([GitHub:](https://github.com/TUMLWE/PAL). Before using this repository, an user is recommended to have familiarized with PAL following the provided examples. An in-depth documentation is hosted on Read the Docs: [PAL Documentation](https://tumlwepal-rtd.readthedocs.io/en/latest/index.html). 


### Installation:

This repository is intended to serve as a submodule within PAL, and it should be incorporated into the \Examples folder of the PAL framework.


## Usage

### General Framework Architecture

Adopting the three-layered approach of *PAL*, the current framework for wind farm control comprises *ITFC*, *HOST*, and *SUBMODEL* applications. In the conducted experiments, the framework was operated on a Bachmann *PLC* at 10 Hz.

During experiments, the *ITFC* app was developed by the wind turbine manufacturer and connected to the turbine controller. This app provided all necessary data for the framework execution. This includes *SCADA* data, which were used to monitor the status of the turbines, but also data from a met-mast, which was located in the proximity of the turbines and was used to assess the inflow.

The *HOST* model undertakes critical responsibilities, including exchanging data with *ITFC* applications, hosting data for *SUBMODEL* access (both read and write), and generating output ".txt" files.

As described in details in the [PAL Documentation](https://tumlwepal-rtd.readthedocs.io/en/latest/index.html), *SUBMODEL* applications perform all the higher-level tasks and are provided in the form of *Simulink* models. A detailed description of the specific *SUBMODEL* apps and their operation is provided in the following section.

Each *PAL* project requires two Excel files as input: "*inputfile.xlsx*" and "*SVI_Definition.xlsx*." In consideration of potential storage issues on the *PLC* during testing, the repository includes an additional set of inputs labeled "test" alongside the default files. These test inputs are designed to facilitate focused testing of specific framework subsections, enabling the utilization of extended time histories for the test *ITFC*, thus limiting storage requirements.


### Wake Steering Application

An overview of the SUBMODELS composing the framework is shown in [this figure](./docs/wfc_framework_apps.png). Each application type is described below:

![WFC Framework](./docs/wfc_framework_apps.png)

**INFLW:**

INFLW blocks determine inflow conditions from available measurements. Two identical Simulink models and **init_** files are provided for both INFLW blocks, but they could be different to accommodate different wake steering strategies. The model reads wind speed inflow at two different heights (116.3m and 54.2m) to calculate averaged wind speeds, turbulence intensity, shear exponent, and wind direction. The Simulink model also performs additional checks, flagging errors if signals are frozen or NaN. The status of the INFLW block (output signals' availability) is encoded as a 4-bit signal, converted to an integer, and provided as an additional output through the variable "output_InflowOK".

**OFFSET:**

OFFSET blocks calculate offsets for the TOGGLER app. Three OFFSET blocks are included. OFFSET_1 and OFFSET_2 are identical, reading inputs from INFLW_1 and INFLW_2, respectively. These simple Simulink models interpolate a 4-dimensional LUT. OFFSET_3 provides a model for fixed offset calculation, not requiring inputs. Generally, it's not necessary to separate INFLW from OFFSET, done here for modularity.

**TOGGLER:**

The TOGGLER app supervises tasks such as determining which strategy offset to feed to the HOST and ensuring WFC is active only within prescribed inflow conditions. It reads inputs from HOST and uses information about inflow characteristics to assess the active wind direction sector. Simultaneously, it checks the availability of other applications within the PLC through status variables of other SUBMODELS (see PAL documentation for details). This ensures offset selection only from active strategies. Manual toggling of strategies is provided, with hysteresis to prevent rapid framework switching. Toggling is performed on all available strategies of the active sector at a user-defined time interval (35 minutes in this example).

Additional time-management functionalities prioritize strategies that have run less time and can be activated and defined through the relative **init** file. Offsets from all **OFFSET** applications are provided as inputs to the TOGGLER application. The appropriate strategy is selected based on the mentioned checks. The demanded offset can pass through a "Saturation block" (a "dummy" version included in the example), which can perform additional processing on the signal.

## Support

For questions, bug reports, or code-related queries, please use [GitHub Issues](https://github.com/TUMLWE/WFC/issues). For general questions, contact Carlo Sucameli (carlo.sucameli@tum.de).

## License

This software is licensed under Apache License Version 2.0.

## Acknowledgments