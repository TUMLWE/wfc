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

This repository contains a Simulink-based framework designed for the execution, monitoring, and coordination of wake steering strategies on a single wind turbine. Generalized to exclude any confidential information, the framework was utilized to coordinate two sets of experiments: one aimed at wind power maximization through wake steering, and the other at applying fixed offsets to a wind turbine for wake characterization using LiDARs. These experiments were conducted collaboratively by the Lehrstuhl für Windenergie at the Technische Universität München and the ForWind – Center for Wind Energy Research at the University of Oldenburg, within the federally-funded project CompactWindII. The experimental site, located in northern Germany, comprises two wind turbines. An aerial view of the test site is provided [here](./docs/overview_testsite.png).

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

Below, you'll find a comprehensive overview of the various *SUBMODELS*
that constitute the [framework](./docs/wfc_framework_apps.png). Each application type is detailed,
providing a thorough understanding of their roles and interactions within the overall system.

![WFC Framework](./docs/wfc_framework_apps.png)

#### INFLW

**INFLW** blocks determine inflow conditions based on available measurements. Their primary function is to provide inputs for offset determination within the **OFFSET** block. In the current setup, two identical
Simulink models and **init_** files are supplied for both **INFLW** blocks, although in principle they can be customized to accommodate diverse design choices.

In this specific instance, wind speed inflow is measured at two different heights (116.3 and 54.2m), and used for the calculation of averaged wind speeds, turbulence intensity, and the shear exponent. Additionally, wind direction data is collected and averaged. Various moving averaging configurations for each inflow quantity can be selected through the **init_** file. The *Simulink* model incorporates checks to validate inputs, flag errors in case of frozen signals or NaN, and encodes the status of the **INFLW** block as a 4-bit signal. This signal is then converted to an integer and provided as an additional output through the variable "output_InflowOK."

**OFFSET**

OFFSET blocks are responsible for calculating offsets, subsequently fed to the **TOGGLER** app.

In the current example, three OFFSET blocks are included. Similar to **INFLW**, **OFFSET_1** and **OFFSET_2** are identical, reading inputs from **INFLW_1** and **INFLW_2**, respectively. These simple *Simulink* models interpolate a sample 4-dimensional LUT, but in principle they could incorporate more complex control techniques. Both offsets are toggled in sequence with a Greedy offset within "Sector 1". 

OFFSET_3 provides a *Simulink* model for fixed offset calculation. It operates within "Sector 2" and does not
require inputs. 

Generally speaking, there is no strict need to separate **INFLW** from **OFFSET**, which could be incorporated in a single application. In the present case, this separation was implemented to enhance modularity and parallel development.

#### TOGGLER

The primary supervisory role is handled by the **TOGGLER** application, which executes tasks such as
determining the strategy offset to be fed to the *HOST* (and consequently, to the turbine controller) based on a
user-defined sequence. The "TOGGLER" also ensures that the Wind Farm Control (WFC) is active only
under prescribed inflow conditions, according to the active wind direction sector. A thorough description of the wake steering applications will be provided in the full paper version. A schematics of the TOGGLER application is shown [below](./docs/wfc_framework_apps.png)

![Toggler](./docs/wfc_framework_toggler.png)

In general, the *TOGGLER* block reads its inputs from the *HOST*, similarly to any other application. Information about inflow characteristics from the met mast, averaged with a user-defined time windowing, is utilized to determine the activewind direction sector and assess whether wind conditions
are suitable for offset provision. Simultaneously, the operational status of the wind turbine is monitored to
ensure its power production. A variable "WFC_status" tracks the status of the toggling operations, akin to the
"output_InflowOK" variable in the **INFLW** blocks.

A check is performed to confirm the availability of other applications within the PLC through status variables of the other SUBMODELS (see PAL documentation for details). This ensures that offsets are selected only from active strategies. Manual toggling of strategies can be performed through both the **init_** file and at runtime using the dedicated flags. A further hysteresis block is added to prevent rapid switching on and off of the framework (which can happen, for example, when operating close to the wind directions or wind speed sector boundaries).

Toggling is performed on all available strategies of an active sector on a user-defined time interval (in the
present example it is set to 35 minutes). It is worth reminding that in the *Simulink* model included, an additional non-controlled "Greedy" was included as a reference, whose offset was set to zero.

Additional time-management functionalities are included, which can be used to prioritize strategies that have run less time than others. This functionality can be activated and defined through the **init** file.

Offsets from all **OFFSET** applications converge as inputs to the **TOGGLER** application, which selects the fitting strategy based on the aforementioned checks.

The demanded offset can be further passed through a "Saturation block" (a "dummy" version is included in the
present example), which can be used to perform additional processing on the signal. During the experiments of
CompactWind2, for example, this block was built based on the wind turbine yaw controller to prevent involuntary
shutdown during sudden switch of wake steering strategy. Clipping of the yaw offset according to manufacturer requirements can also be applied, if necessary.

## Support

For questions, bug reports, or code-related queries, please use [GitHub Issues](https://github.com/TUMLWE/WFC/issues). For general questions, contact Carlo Sucameli (carlo.sucameli@tum.de).

## License

This software is licensed under Apache License Version 2.0.

## Acknowledgments

This work was funded by the CompactWindII project, federally funded by the Federal Ministry for Economic Affairs and Climate Action of Germany.

Special thanks are extended to ENO Energy GmbH for their extensive support during the whole experimentation, having provided the wind farm and data on which the original version of the present framework was developed.