CMSIS-Zone Example for the Microchip SAML11
===========================================

This examples demonstrates the usage of CMSIS-Zone for configuring the
TrustZone configuration for the Microchip SAML11 TrustZone example.

The CMSIS-Zone project and configuration is stored in Zone folder. See below for
a quick step guide how to open and inspect the configuration.

The adopted MDK project is stored in MDK folder. See further below for a quick step
guide how to open and debug the demo on a SAML11 Xplained board.


CMSIS-Zone Configuration
------------------------

The Zone configuration can be loaded in CMSIS-Zone by perfoming the following steps:

1. Start CMSIS-Zone utility (i.e. eclipse.exe)
2. Import project
   - File > Import > Existing Projects into Workspace
   - Select root directory: Examples/SAML11/Zone
   - Projects: SAML11
3. Open SAML11.azone from Project Explorer
4. Click the Generate button in the Zone Editor tool bar
   All FreeMarker templates from ftl folder (\*.ftl) are generated into ftl_gen folder:
   - flash.dbgconf.lst contains a textual dump of all information gathered for the fuse bit configuration.
   - flash.dbgconf contains a debug configuration file for MDK, that programs the memory map related fuse bits.
   - scatter_ns.sct contains a scatter file for the non-secure application.
   - scatter_s.sct contains a scatter file for the secure application.
  
The example zone configuration shows a minimal resource partitioning needed for
TrustZone devices, i.e. Secure and NonSecure zones.

MDK Example Project
-------------------

tbd