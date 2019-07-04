CMSIS-Zone Example for Nuvoton's M2351
======================================

This examples demonstrates the usage of CMSIS-Zone for configuring the
TrustZone configuration for Nuvoton's M2351 TrustZone example.

The CMSIS-Zone project and configuration is stored in Zone folder. See below for
a quick step guide how to open and inspect the configuration.

The adopted MDK project is stored in MDK folder. See further below for a quick step
guide how to open and debug the demo on a NuMaker-PFM-M2351 board.


CMSIS-Zone Configuration
------------------------

The Zone configuration can be loaded in CMSIS-Zone by perfoming the following steps:

1. Start CMSIS-Zone utility (i.e. eclipse.exe)
2. Import project
   - File > Import > Existing Projects into Workspace
   - Select root directory: Examples/M2351/Zone
   - Projects: M2351
3. Open M2351.azone from Project Explorer
4. Click the Generate button in the Zone Editor tool bar
   All FreeMarker templates from ftl folder (*.ftl) are generated into ftl_gen folder:
   - dump_fzone.txt contains a textual dump of all zone project information.
   - mem_layout.h contains defines for memory region start addresses and sizes.
   - scatter_*.sct contains scatter file templates.
   - partition.h.ftl contains the TrustTone configurations obtained from the project settings.
   
The example zone configuration shows a minimal resource partitioning needed for
TrustZone devices, i.e. Secure and NonSecure zones.

The memory is devided into
individual section for secure and non-secure CODE and DATA, respectively. Additionally
a small flash region is reserved for the non-secure callable veneer table (i.e. secure
gateways). This information is used by the mem_layout.h, the scatter_*.sct, the SAU/NSBA/MPC
setups in partition.h templates.

Some peripherals are assigned to either the secure or the non-secure zone to demonstrate
generation of PPC setup and interrupt config in partition.h template.


MDK Example Project
-------------------

The demo project can be loaded in uVision, built and debugged by perfoming the
following steps:

1. Navigate to Examples\M2351\MDK
2. Opeb TrustZone.uvmpw to open the uVision multi-project workspace.
3. Optional: Update the generated files by executing the copy_gen.bat script.
4. Run the batch build in MDK.
   Both projects, Secure and NonSecure needs to be compiled in order.
5. Assure Secure is the active project.
6. Connect the NuMaker-PFM-M2351 using a Micro-USB cable at ICEJ.
7. Assure that ST-Link Debugger is selected and the NULink Debugger is used.
8. Launch a debug session and watch the serial console output.
