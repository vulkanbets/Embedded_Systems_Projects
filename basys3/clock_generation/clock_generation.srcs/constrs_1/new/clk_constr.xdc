

## Set Pmod Header JC[0] to have outplut frequency from Clock Wizard
set_property -dict { PACKAGE_PIN K17   IOSTANDARD LVCMOS33 } [get_ports {clk_wiz_out}];


## Configuration options, can be used for all designs
set_property CONFIG_VOLTAGE 3.3 [current_design]
set_property CFGBVS VCCO [current_design]

## SPI configuration mode options for QSPI boot, can be used for all designs
set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]
set_property BITSTREAM.CONFIG.CONFIGRATE 33 [current_design]
set_property CONFIG_MODE SPIx4 [current_design]
