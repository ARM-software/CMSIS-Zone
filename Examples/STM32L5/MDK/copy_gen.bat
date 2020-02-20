@ECHO OFF
XCopy /Y ..\Zone\ftl_gen\SystemIsolation_config.c blinky_s
XCopy /Y ..\Zone\ftl_gen\partition_gen.h blinky_s\RTE\Device\STM32L552ZETxQ
XCopy /Y ..\Zone\ftl_gen\mem_layout.h .\


