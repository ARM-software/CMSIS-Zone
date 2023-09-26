# Command Line Mode {#zTCLI}

As the \ref rzone ".rzone" and \ref azone ".azone" files are XML based, it is possible to create or modify the files in external tools without using the \ref zTInteractiveMode. To generate output files the CMSIS-Zone Utility can be started in headless mode. The command line format is:
```
eclipsec.exe -noSplash  -consoleLog --launcher.suppressErrors -application com.arm.cmsis.zone.ui.headlessgen -azone FILENME.azone  -ftl FTL_DIR -ftl_gen FTL_GEN_DIR
```

**Where**

| Parameter                                         | Description                                                    | Required |
|:--------------------------------------------------|:---------------------------------------------------------------|:---------|
| `-noSplash`                                       | Suppresses Eclipse's splash screen                             | [required] |
| `-launcher.suppressErrors`                        | Suppresses error dialog                                        | [optional] |
| `-consoleLog`                                     | Suppresses diagnostic messages                                 | [optional] |
| `-application com.arm.cmsis.zone.ui.headlessgen`  | Specifies the plug-in to be called                             | [required] |
| `-azone FILNAME.azone`                            | Specifies the .azone file to be processed                      | [required] |
| `-ftl FTL_DIR`                                    | Relative or absolute directory with templates to process       | [optional - by default, \c ftl directory under the azone's file path is used] |
| `-ftl_gen FTL_GEN_DIR`                            | Relative or absolute output directory to write generated files | [optional - by default, \c ftl_gen directory under the azone's file path is used] |
| `-help`                                           | Shows command line parameter information                       | [optional] |

<!--\b Examples
\code
eclipsec.exe -noSplash -application com.arm.cmsis.zone.ui.headlessgen -azone Musca-A1.azone
\endcode-->