

##Pmod Header JC
set_property -dict { PACKAGE_PIN K17   IOSTANDARD LVCMOS33 } [get_ports {SCK}];#Sch name = JC1
set_property -dict { PACKAGE_PIN M18   IOSTANDARD LVCMOS33 } [get_ports {CS}];#Sch name = JC2


## Configuration options, can be used for all designs
set_property CONFIG_VOLTAGE 3.3 [current_design]
set_property CFGBVS VCCO [current_design]

## SPI configuration mode options for QSPI boot, can be used for all designs
set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]
set_property BITSTREAM.CONFIG.CONFIGRATE 33 [current_design]
set_property CONFIG_MODE SPIx4 [current_design]
