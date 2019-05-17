# CMSIS-Zone

The branch *master* of this GitHub repository contains the first alpha version of CMSIS-Zone Utility that supports
the multi-step approach for splitting complex multi-core systems into sub-systems.
The relevant part of the [documentation](https://arm-software.github.io/CMSIS-Zone/index.html) is available under 
https://arm-software.github.io/CMSIS-Zone/index.html.

This alpha version of CMSIS-Zone focuses on the TrustZone configuration of single or multi-core Cortex-M33 systems.
It implements currently the infra-structure that is required for:
  - Split of a multi-processor system for single processor views and secure/non-secure views
  - TrustZone setup (SAU, Interrupt assignment to Secure/Non-Secure)
  - Setup of device specific Memory Protection Controller (MPC)
  - Setup of device specific Peripheral Protection Controller (PPC)
  - Generation of linker scatter files.
  
We will show how to apply this concept using example projects.

The following CMSIS-Zone features are still under development and not yet available in the alpha version:
  - Configuration of the Memory Protection Unit (MPU)
  - Support for multi-core targets that contain a mixture of cores (Cortex-M/Cortex-A)
  - Project wizard for creating new CMSIS-Zone projects

The source code of the CMSIS-Zone Utility will be released under open source license once we have completed all the features
described above. However we will update this page frequently to show the current progress of this project and to solve issues
that are detected during testing.

Use [Issues](https://github.com/ARM-software/CMSIS-Zone#issues-and-labels) to provide feedback and report problems for the
CMSIS-Zone Utility and the CMSIS-Zone project examples.

**Note:** The branch *develop* of this GitHub repository reflects our current state of 
example projects and is constantly updated. It allows you to review the work and provide feedback or create pull requests for contributions.

For further details see also the [Slides of the Embedded World CMSIS Partner Meeting](https://github.com/ARM-software/CMSIS_5/blob/develop/CMSIS_EW2019.pdf).

## Directory Structure

| Directory            | Content                                                   |                
| -------------------- | --------------------------------------------------------- |
| Example              | Example projects that show the usage of CMSIS-Zone        |
| Schema               | XML schema files for content validation                   |
| Templates            | FreeMarker templates that generate output files           |
| docs                 | The documentation for CMSIS-Zone                          |

## License

Arm CMSIS and the CMSIS-Zone examples in this repository are licensed under Apache-2.0.

## Contributions and Pull Requests

Contributions are accepted under Apache-2.0. Only submit contributions where you have authored all of the code.

### Issues and Labels

Please feel free to raise an [issue on GitHub](https://github.com/ARM-software/CMSIS-Zone/issues)
to report misbehavior (i.e. bugs) or start discussions about enhancements. This
is your best way to interact directly with the maintenance team and the community.
We encourage you to append implementation suggestions as this helps to decrease the
workload of the very limited maintenance team. 

We will be monitoring and responding to issues as best we can.
Please attempt to avoid filing duplicates of open or closed items when possible.
In the spirit of openness we will be tagging issues with the following:

- **bug** – We consider this issue to be a bug that will be investigated.

- **wontfix** - We appreciate this issue but decided not to change the current behavior.
	
- **enhancement** – Denotes something that will be implemented soon. 

- **future** - Denotes something not yet schedule for implementation.

- **out-of-scope** - We consider this issue loosely related to CMSIS. It might by implemented outside of CMSIS. Let us know about your work.
	
- **question** – We have further questions to this issue. Please review and provide feedback.

- **documentation** - This issue is a documentation flaw that will be improved in future.

- **review** - This issue is under review. Please be patient.
	
- **DONE** - We consider this issue as resolved - please review and close it. In case of no further activity this issues will be closed after a week.

- **duplicate** - This issue is already addressed elsewhere, see comment with provided references.

- **Important Information** - We provide essential informations regarding planned or resolved major enhancements.

---

_Copyright (c) 2014-2016, ARM Limited and Contributors. All rights reserved._
