CMSIS-Zone Example for NXP LPC55S69
===================================

This examples demonstrates the usage of CMSIS-Zone for configuring the
TrustZone configuration for NXP's LPC55S69 Hello World example.

The CMSIS-Zone project and configuration is stored in Zone folder. See below for
a quick step guide how to open and inspect the configuration.

The adopted MDK project is stored in MDK folder. See further below for a quick step
guide how to open and debug the demo on an LPC55S69-EVK board.


CMSIS-Zone Configuration
------------------------

The Zone configuration can be loaded in CMSIS-Zone by perfoming the following steps:

1. Start CMSIS-Zone utility (i.e. eclipse.exe)
2. Import project
   - File > Import > Existing Projects into Workspace
   - Select root directory: Examples/LPC55S69/Zone
   - Projects: LPC55S69
3. Open LPC55S69.azone from Project Explorer
4. Click the Generate button in the Zone Editor tool bar
   All FreeMarker templates from ftl folder (*.ftl) are generated into ftl_gen folder:
   - dump_fzone.txt contains a textual dump of all zone project information.
   - mem_layout.h contains defines for memory region start addresses and sizes.
   - scatter_*.sct are examples how scatter files can be generated (not actually used).
   - tzm_config_*.c contains the TrustTone configurations obtained from the project settings.
   
   
MDK Example Project
-------------------

The demo project can be loaded in uVision, built and debugged by perfoming the
following steps:

1. Navigate to Examples\LPC55S69\MDK
2. Run hello_world.uvmpw.bat to open the uVision project.
   Alternatively manually open the multi-project workspace at
   Examples\LPC55S69\MDK\hello_world_s\mdk\hello_world.uvmpw
3. Optional: Update the generated files by executing the copy_gen.bat scripts in
   hello_world_s\mdk and hello_world_ns\mdk folders.
4. Run the batch build in MDK.
   Both projects, hello_world_s and hello_world_ns needs to be compiled in
   order.
5. Assure hello_world_s is the active project.
6. Connect the LPC55S69-EVK using a Micro-USB cable at P9.
7. Assure that CMSIS-DAP ARMv8-M Debugger is selected and the NXP-Link2 is used.
8. Optional: Open a serial terminal program (i.e. TeraTerm) on the virtual serial
   port provided in parallel to the debugger (e.g. USB Serial Device). Configure
   the port to 115200/8N1.
9. Launch a debug session and watch the serial console output.
