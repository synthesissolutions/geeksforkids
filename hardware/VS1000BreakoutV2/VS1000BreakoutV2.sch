EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L VS1000:VS1000 U1
U 1 1 5F8673A3
P 2900 5070
F 0 "U1" H 2800 7035 50  0000 C CNN
F 1 "VS1000" H 2800 6944 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 2900 5070 50  0001 C CNN
F 3 "" H 2900 5070 50  0001 C CNN
	1    2900 5070
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J3
U 1 1 5F86CA2C
P 5220 1550
F 0 "J3" H 5277 2017 50  0000 C CNN
F 1 "USB_B_Micro" H 5277 1926 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_GCT_USB3076-30-A" H 5370 1500 50  0001 C CNN
F 3 "~" H 5370 1500 50  0001 C CNN
	1    5220 1550
	1    0    0    -1  
$EndComp
Text GLabel 3700 5320 2    50   Input ~ 0
USB_D+
Text GLabel 3700 5170 2    50   Input ~ 0
USB_D-
Text GLabel 5520 1550 2    50   Input ~ 0
USB_CONN_D+
Text GLabel 5520 1650 2    50   Input ~ 0
USB_CONN_D-
NoConn ~ 5520 1750
NoConn ~ 5120 1950
$Comp
L power:GND #PWR031
U 1 1 5F8713D3
P 5220 1950
F 0 "#PWR031" H 5220 1700 50  0001 C CNN
F 1 "GND" H 5225 1777 50  0000 C CNN
F 2 "" H 5220 1950 50  0001 C CNN
F 3 "" H 5220 1950 50  0001 C CNN
	1    5220 1950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR033
U 1 1 5F8719AA
P 5600 1280
F 0 "#PWR033" H 5600 1130 50  0001 C CNN
F 1 "+5V" H 5615 1453 50  0000 C CNN
F 2 "" H 5600 1280 50  0001 C CNN
F 3 "" H 5600 1280 50  0001 C CNN
	1    5600 1280
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 1280 5600 1350
Wire Wire Line
	5600 1350 5520 1350
$Comp
L power:+5V #PWR023
U 1 1 5F8725DC
P 3700 5620
F 0 "#PWR023" H 3700 5470 50  0001 C CNN
F 1 "+5V" V 3715 5748 50  0000 L CNN
F 2 "" H 3700 5620 50  0001 C CNN
F 3 "" H 3700 5620 50  0001 C CNN
	1    3700 5620
	0    1    1    0   
$EndComp
$Comp
L power:VDDA #PWR022
U 1 1 5F874D76
P 3700 5470
F 0 "#PWR022" H 3700 5320 50  0001 C CNN
F 1 "VDDA" V 3715 5598 50  0000 L CNN
F 2 "" H 3700 5470 50  0001 C CNN
F 3 "" H 3700 5470 50  0001 C CNN
	1    3700 5470
	0    1    1    0   
$EndComp
$Comp
L power:VDDA #PWR020
U 1 1 5F875442
P 3700 4720
F 0 "#PWR020" H 3700 4570 50  0001 C CNN
F 1 "VDDA" V 3715 4848 50  0000 L CNN
F 2 "" H 3700 4720 50  0001 C CNN
F 3 "" H 3700 4720 50  0001 C CNN
	1    3700 4720
	0    1    1    0   
$EndComp
$Comp
L power:VDDA #PWR017
U 1 1 5F875D18
P 3700 3970
F 0 "#PWR017" H 3700 3820 50  0001 C CNN
F 1 "VDDA" V 3715 4098 50  0000 L CNN
F 2 "" H 3700 3970 50  0001 C CNN
F 3 "" H 3700 3970 50  0001 C CNN
	1    3700 3970
	0    1    1    0   
$EndComp
$Comp
L power:VDDA #PWR016
U 1 1 5F876A8F
P 3700 3670
F 0 "#PWR016" H 3700 3520 50  0001 C CNN
F 1 "VDDA" V 3715 3798 50  0000 L CNN
F 2 "" H 3700 3670 50  0001 C CNN
F 3 "" H 3700 3670 50  0001 C CNN
	1    3700 3670
	0    1    1    0   
$EndComp
$Comp
L power:VDD #PWR025
U 1 1 5F877733
P 3700 6070
F 0 "#PWR025" H 3700 5920 50  0001 C CNN
F 1 "VDD" V 3715 6198 50  0000 L CNN
F 2 "" H 3700 6070 50  0001 C CNN
F 3 "" H 3700 6070 50  0001 C CNN
	1    3700 6070
	0    1    1    0   
$EndComp
$Comp
L power:VDD #PWR08
U 1 1 5F877D47
P 1900 6070
F 0 "#PWR08" H 1900 5920 50  0001 C CNN
F 1 "VDD" V 1915 6197 50  0000 L CNN
F 2 "" H 1900 6070 50  0001 C CNN
F 3 "" H 1900 6070 50  0001 C CNN
	1    1900 6070
	0    -1   -1   0   
$EndComp
$Comp
L power:VDD #PWR05
U 1 1 5F8785F0
P 1900 4270
F 0 "#PWR05" H 1900 4120 50  0001 C CNN
F 1 "VDD" V 1915 4397 50  0000 L CNN
F 2 "" H 1900 4270 50  0001 C CNN
F 3 "" H 1900 4270 50  0001 C CNN
	1    1900 4270
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR021
U 1 1 5F879A2A
P 3700 4870
F 0 "#PWR021" H 3700 4620 50  0001 C CNN
F 1 "GND" V 3705 4742 50  0000 R CNN
F 2 "" H 3700 4870 50  0001 C CNN
F 3 "" H 3700 4870 50  0001 C CNN
	1    3700 4870
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR019
U 1 1 5F87A68F
P 3700 4420
F 0 "#PWR019" H 3700 4170 50  0001 C CNN
F 1 "GND" V 3705 4292 50  0000 R CNN
F 2 "" H 3700 4420 50  0001 C CNN
F 3 "" H 3700 4420 50  0001 C CNN
	1    3700 4420
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR018
U 1 1 5F87ADF4
P 3700 4270
F 0 "#PWR018" H 3700 4020 50  0001 C CNN
F 1 "GND" V 3705 4142 50  0000 R CNN
F 2 "" H 3700 4270 50  0001 C CNN
F 3 "" H 3700 4270 50  0001 C CNN
	1    3700 4270
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5F87B145
P 3700 3370
F 0 "#PWR015" H 3700 3120 50  0001 C CNN
F 1 "GND" V 3705 3242 50  0000 R CNN
F 2 "" H 3700 3370 50  0001 C CNN
F 3 "" H 3700 3370 50  0001 C CNN
	1    3700 3370
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR024
U 1 1 5F87BF3C
P 3700 5920
F 0 "#PWR024" H 3700 5670 50  0001 C CNN
F 1 "GND" V 3705 5792 50  0000 R CNN
F 2 "" H 3700 5920 50  0001 C CNN
F 3 "" H 3700 5920 50  0001 C CNN
	1    3700 5920
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5F87D193
P 1900 5920
F 0 "#PWR07" H 1900 5670 50  0001 C CNN
F 1 "GND" V 1905 5792 50  0000 R CNN
F 2 "" H 1900 5920 50  0001 C CNN
F 3 "" H 1900 5920 50  0001 C CNN
	1    1900 5920
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5F87E8AB
P 1900 4120
F 0 "#PWR04" H 1900 3870 50  0001 C CNN
F 1 "GND" V 1905 3992 50  0000 R CNN
F 2 "" H 1900 4120 50  0001 C CNN
F 3 "" H 1900 4120 50  0001 C CNN
	1    1900 4120
	0    1    1    0   
$EndComp
$Comp
L Power_Protection:USBLC6-2SC6 U2
U 1 1 5F87FE8F
P 7400 1610
F 0 "U2" H 7660 1960 50  0000 C CNN
F 1 "USBLC6-2SC6" H 7710 1260 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 7400 1110 50  0001 C CNN
F 3 "https://www.st.com/resource/en/datasheet/usblc6-2.pdf" H 7600 1960 50  0001 C CNN
	1    7400 1610
	1    0    0    -1  
$EndComp
Text GLabel 7800 1510 2    50   Input ~ 0
USB_CONN_D-
Text GLabel 7000 1510 0    50   Input ~ 0
USB_CONN_D+
Text GLabel 7800 1710 2    50   Input ~ 0
USB_D-
Text GLabel 7000 1710 0    50   Input ~ 0
USB_D+
$Comp
L power:GND #PWR038
U 1 1 5F883FF7
P 7400 2010
F 0 "#PWR038" H 7400 1760 50  0001 C CNN
F 1 "GND" H 7405 1837 50  0000 C CNN
F 2 "" H 7400 2010 50  0001 C CNN
F 3 "" H 7400 2010 50  0001 C CNN
	1    7400 2010
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR037
U 1 1 5F88470C
P 7400 1210
F 0 "#PWR037" H 7400 1060 50  0001 C CNN
F 1 "+5V" H 7415 1383 50  0000 C CNN
F 2 "" H 7400 1210 50  0001 C CNN
F 3 "" H 7400 1210 50  0001 C CNN
	1    7400 1210
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5F8857C8
P 4210 6310
F 0 "R2" H 4269 6356 50  0000 L CNN
F 1 "1M" V 4210 6260 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 4210 6310 50  0001 C CNN
F 3 "~" H 4210 6310 50  0001 C CNN
	1    4210 6310
	1    0    0    -1  
$EndComp
$Comp
L Device:Resonator_Small Y1
U 1 1 5F88689D
P 4630 6310
F 0 "Y1" V 4810 6290 50  0000 C CNN
F 1 "12MHz" V 4440 6280 50  0000 C CNN
F 2 "Project:Resonator" H 4605 6310 50  0001 C CNN
F 3 "~" H 4605 6310 50  0001 C CNN
	1    4630 6310
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4210 6210 4530 6210
Wire Wire Line
	4210 6410 4530 6410
$Comp
L power:GND #PWR030
U 1 1 5F88A603
P 4920 6350
F 0 "#PWR030" H 4920 6100 50  0001 C CNN
F 1 "GND" H 4925 6177 50  0000 C CNN
F 2 "" H 4920 6350 50  0001 C CNN
F 3 "" H 4920 6350 50  0001 C CNN
	1    4920 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4920 6350 4920 6310
Wire Wire Line
	4920 6310 4830 6310
Wire Wire Line
	4110 6220 4110 6210
Wire Wire Line
	4110 6210 4210 6210
Wire Wire Line
	3700 6220 4110 6220
Connection ~ 4210 6210
Wire Wire Line
	3700 6370 4130 6370
Wire Wire Line
	4130 6370 4130 6410
Wire Wire Line
	4130 6410 4210 6410
Connection ~ 4210 6410
$Comp
L power:GND #PWR06
U 1 1 5F892A70
P 1900 4420
F 0 "#PWR06" H 1900 4170 50  0001 C CNN
F 1 "GND" V 1905 4292 50  0000 R CNN
F 2 "" H 1900 4420 50  0001 C CNN
F 3 "" H 1900 4420 50  0001 C CNN
	1    1900 4420
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C5
U 1 1 5F893056
P 4230 3820
F 0 "C5" V 4120 3820 50  0000 C CNN
F 1 "1uF" V 4340 3820 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4230 3820 50  0001 C CNN
F 3 "~" H 4230 3820 50  0001 C CNN
	1    4230 3820
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR027
U 1 1 5F895177
P 4330 3820
F 0 "#PWR027" H 4330 3570 50  0001 C CNN
F 1 "GND" V 4335 3692 50  0000 R CNN
F 2 "" H 4330 3820 50  0001 C CNN
F 3 "" H 4330 3820 50  0001 C CNN
	1    4330 3820
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4130 3820 3700 3820
Text GLabel 3700 3520 2    50   Input ~ 0
LEFT
Text GLabel 3700 4570 2    50   Input ~ 0
RIGHT
Text GLabel 3700 6820 2    50   Input ~ 0
MISO
Text GLabel 3700 6670 2    50   Input ~ 0
TX
Text GLabel 3700 6520 2    50   Input ~ 0
RX
Text GLabel 1900 6820 0    50   Input ~ 0
MOSI
Text GLabel 1900 6670 0    50   Input ~ 0
SCK
Text GLabel 1900 6520 0    50   Input ~ 0
CS
Text GLabel 1780 3370 1    50   Input ~ 0
RESET
$Comp
L power:VDD #PWR01
U 1 1 5F897D03
P 1350 3320
F 0 "#PWR01" H 1350 3170 50  0001 C CNN
F 1 "VDD" H 1365 3493 50  0000 C CNN
F 2 "" H 1350 3320 50  0001 C CNN
F 3 "" H 1350 3320 50  0001 C CNN
	1    1350 3320
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 5F898B57
P 1530 3370
F 0 "R1" V 1450 3360 50  0000 C CNN
F 1 "100K" V 1530 3370 31  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 1530 3370 50  0001 C CNN
F 3 "~" H 1530 3370 50  0001 C CNN
	1    1530 3370
	0    1    1    0   
$EndComp
Wire Wire Line
	1900 3370 1630 3370
Wire Wire Line
	1430 3370 1350 3370
Wire Wire Line
	1350 3370 1350 3320
$Comp
L Device:C_Small C4
U 1 1 5F89F1DA
P 4210 5770
F 0 "C4" V 4100 5770 50  0000 C CNN
F 1 "10uF" V 4320 5770 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4210 5770 50  0001 C CNN
F 3 "~" H 4210 5770 50  0001 C CNN
	1    4210 5770
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR026
U 1 1 5F89FA7C
P 4310 5770
F 0 "#PWR026" H 4310 5520 50  0001 C CNN
F 1 "GND" V 4315 5642 50  0000 R CNN
F 2 "" H 4310 5770 50  0001 C CNN
F 3 "" H 4310 5770 50  0001 C CNN
	1    4310 5770
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3700 5770 4110 5770
NoConn ~ 3700 4120
$Comp
L Memory_Flash:MX25R3235FZNxx1 U3
U 1 1 5F8A1DB3
P 10100 1650
F 0 "U3" H 9710 2020 50  0000 L CNN
F 1 "MX25L6473FM2I-08G" H 9370 1280 50  0000 L CNN
F 2 "Package_SO:SOIC-8_5.275x5.275mm_P1.27mm" H 10100 1050 50  0001 C CNN
F 3 "http://www.macronix.com/Lists/Datasheet/Attachments/7534/MX25R3235F,%20Wide%20Range,%2032Mb,%20v1.6.pdf" H 10100 1650 50  0001 C CNN
	1    10100 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR044
U 1 1 5F8A297B
P 10300 2050
F 0 "#PWR044" H 10300 1800 50  0001 C CNN
F 1 "GND" H 10305 1877 50  0000 C CNN
F 2 "" H 10300 2050 50  0001 C CNN
F 3 "" H 10300 2050 50  0001 C CNN
	1    10300 2050
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR043
U 1 1 5F8A2EAD
P 10300 1250
F 0 "#PWR043" H 10300 1100 50  0001 C CNN
F 1 "VDD" H 10315 1423 50  0000 C CNN
F 2 "" H 10300 1250 50  0001 C CNN
F 3 "" H 10300 1250 50  0001 C CNN
	1    10300 1250
	1    0    0    -1  
$EndComp
Text GLabel 10600 1650 2    50   Input ~ 0
MISO
Text GLabel 9600 1450 0    50   Input ~ 0
MOSI
Text GLabel 9600 1550 0    50   Input ~ 0
SCK
Text GLabel 9210 1600 1    50   Input ~ 0
CS
Text GLabel 9600 1750 0    50   Input ~ 0
VDD
Text GLabel 9600 1850 0    50   Input ~ 0
VDD
$Comp
L power:VDD #PWR041
U 1 1 5F8AE117
P 8930 1870
F 0 "#PWR041" H 8930 1720 50  0001 C CNN
F 1 "VDD" H 8945 2043 50  0000 C CNN
F 2 "" H 8930 1870 50  0001 C CNN
F 3 "" H 8930 1870 50  0001 C CNN
	1    8930 1870
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R7
U 1 1 5F8AF2CF
P 9210 1750
F 0 "R7" V 9130 1740 50  0000 C CNN
F 1 "100K" V 9210 1750 31  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 9210 1750 50  0001 C CNN
F 3 "~" H 9210 1750 50  0001 C CNN
	1    9210 1750
	-1   0    0    1   
$EndComp
Wire Wire Line
	9600 1650 9210 1650
Wire Wire Line
	9210 1870 8930 1870
Text Notes 2010 7330 0    50   ~ 0
GPIO0_7 Controls VDD Voltage\nPull-Up for 3.3V\nPull-down for 1.8V
Text Notes 2010 7660 0    50   ~ 0
GPIO0_6 Controls USB Functions\nPull-Up for USB Audio Device\nPull-down for USB Storage
Text Notes 3400 7650 0    50   ~ 0
XCS\nPull-Up to enable SPI EEPROM boot\nPull-down to disable
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 5F8B3564
P 4720 5020
F 0 "J1" H 4692 4902 50  0000 R CNN
F 1 "Power Jumper" H 4692 4993 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4720 5020 50  0001 C CNN
F 3 "~" H 4720 5020 50  0001 C CNN
	1    4720 5020
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR029
U 1 1 5F8B5BA6
P 4430 4860
F 0 "#PWR029" H 4430 4710 50  0001 C CNN
F 1 "+5V" H 4445 5033 50  0000 C CNN
F 2 "" H 4430 4860 50  0001 C CNN
F 3 "" H 4430 4860 50  0001 C CNN
	1    4430 4860
	1    0    0    -1  
$EndComp
Wire Wire Line
	4520 4920 4430 4920
Wire Wire Line
	4430 4920 4430 4860
$Comp
L Device:R_Small R3
U 1 1 5F8B6E1B
P 4420 5170
F 0 "R3" H 4479 5216 50  0000 L CNN
F 1 "1M" V 4420 5120 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 4420 5170 50  0001 C CNN
F 3 "~" H 4420 5170 50  0001 C CNN
	1    4420 5170
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR028
U 1 1 5F8B7DDD
P 4420 5270
F 0 "#PWR028" H 4420 5020 50  0001 C CNN
F 1 "GND" H 4425 5097 50  0000 C CNN
F 2 "" H 4420 5270 50  0001 C CNN
F 3 "" H 4420 5270 50  0001 C CNN
	1    4420 5270
	1    0    0    -1  
$EndComp
Wire Wire Line
	4420 5070 4420 5020
Wire Wire Line
	3700 5020 4420 5020
Connection ~ 4420 5020
Wire Wire Line
	4420 5020 4520 5020
Text GLabel 1900 3670 0    50   Input ~ 0
GPIO_1
Text GLabel 1900 3520 0    50   Input ~ 0
GPIO_0
Text GLabel 1900 3820 0    50   Input ~ 0
GPIO_2
Text GLabel 1900 3970 0    50   Input ~ 0
GPIO_3
Text GLabel 1900 4570 0    50   Input ~ 0
GPIO_4
Text GLabel 1900 4720 0    50   Input ~ 0
GPIO_5
Text GLabel 1900 4870 0    50   Input ~ 0
GPIO_6
Text GLabel 1900 5020 0    50   Input ~ 0
GPIO_7
Text GLabel 1900 5170 0    50   Input ~ 0
GPIO_8
Text GLabel 1900 5320 0    50   Input ~ 0
GPIO_9
Text GLabel 1900 5470 0    50   Input ~ 0
GPIO_10
Text GLabel 1900 5620 0    50   Input ~ 0
GPIO_12
Text GLabel 1900 5770 0    50   Input ~ 0
GPIO_13
Text GLabel 1900 6220 0    50   Input ~ 0
GPIO_11
Text GLabel 1900 6370 0    50   Input ~ 0
GPIO_14
Text GLabel 5360 2650 2    50   Input ~ 0
RESET
Text GLabel 5360 2750 2    50   Input ~ 0
GPIO_0
Text GLabel 5360 2850 2    50   Input ~ 0
GPIO_1
Text GLabel 5360 2950 2    50   Input ~ 0
GPIO_2
Text GLabel 5360 3050 2    50   Input ~ 0
GPIO_3
Text GLabel 5360 3150 2    50   Input ~ 0
GPIO_4
Text GLabel 5360 3250 2    50   Input ~ 0
GPIO_5
Text GLabel 5360 3350 2    50   Input ~ 0
GPIO_6
Text GLabel 5360 3450 2    50   Input ~ 0
GPIO_7
Text GLabel 5360 3550 2    50   Input ~ 0
GPIO_8
Text GLabel 5360 3650 2    50   Input ~ 0
GPIO_9
$Comp
L Connector:Conn_01x14_Male J2
U 1 1 5F8CB356
P 5160 3250
F 0 "J2" H 5268 4031 50  0000 C CNN
F 1 "Conn_01x14_Male" H 5268 3940 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x14_P2.54mm_Vertical" H 5160 3250 50  0001 C CNN
F 3 "~" H 5160 3250 50  0001 C CNN
	1    5160 3250
	1    0    0    -1  
$EndComp
Text GLabel 5360 3750 2    50   Input ~ 0
GPIO_10
Text GLabel 5360 3850 2    50   Input ~ 0
GPIO_11
$Comp
L power:GND #PWR032
U 1 1 5F8CE93F
P 5450 4040
F 0 "#PWR032" H 5450 3790 50  0001 C CNN
F 1 "GND" H 5455 3867 50  0000 C CNN
F 2 "" H 5450 4040 50  0001 C CNN
F 3 "" H 5450 4040 50  0001 C CNN
	1    5450 4040
	1    0    0    -1  
$EndComp
Wire Wire Line
	5360 3950 5450 3950
Wire Wire Line
	5450 3950 5450 4040
$Comp
L power:+5V #PWR036
U 1 1 5F8CFDA8
P 6560 2570
F 0 "#PWR036" H 6560 2420 50  0001 C CNN
F 1 "+5V" H 6575 2743 50  0000 C CNN
F 2 "" H 6560 2570 50  0001 C CNN
F 3 "" H 6560 2570 50  0001 C CNN
	1    6560 2570
	1    0    0    -1  
$EndComp
Wire Wire Line
	6660 2630 6560 2630
Wire Wire Line
	6560 2630 6560 2570
$Comp
L power:VDD #PWR034
U 1 1 5F8D186F
P 6440 2650
F 0 "#PWR034" H 6440 2500 50  0001 C CNN
F 1 "VDD" H 6455 2823 50  0000 C CNN
F 2 "" H 6440 2650 50  0001 C CNN
F 3 "" H 6440 2650 50  0001 C CNN
	1    6440 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6660 2730 6440 2730
Wire Wire Line
	6440 2730 6440 2650
Text GLabel 6210 2940 3    50   Input ~ 0
RX
Text GLabel 6660 2930 0    50   Input ~ 0
TX
Text GLabel 6660 3030 0    50   Input ~ 0
SCK
Text GLabel 6660 3130 0    50   Input ~ 0
MOSI
Text GLabel 6660 3230 0    50   Input ~ 0
MISO
Text GLabel 6660 3330 0    50   Input ~ 0
CS
$Comp
L Connector:Conn_01x14_Male J4
U 1 1 5F8D3F0E
P 6860 3230
F 0 "J4" H 6832 3204 50  0000 R CNN
F 1 "Conn_01x14_Male" H 6832 3113 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x14_P2.54mm_Vertical" H 6860 3230 50  0001 C CNN
F 3 "~" H 6860 3230 50  0001 C CNN
	1    6860 3230
	-1   0    0    -1  
$EndComp
Text GLabel 6660 3430 0    50   Input ~ 0
GPIO_12
Text GLabel 6660 3530 0    50   Input ~ 0
GPIO_13
Text GLabel 6660 3630 0    50   Input ~ 0
GPIO_14
Text GLabel 6660 3830 0    50   Input ~ 0
L_AC
Text GLabel 6660 3730 0    50   Input ~ 0
R_AC
$Comp
L power:GND #PWR035
U 1 1 5F8D6B25
P 6520 3990
F 0 "#PWR035" H 6520 3740 50  0001 C CNN
F 1 "GND" H 6525 3817 50  0000 C CNN
F 2 "" H 6520 3990 50  0001 C CNN
F 3 "" H 6520 3990 50  0001 C CNN
	1    6520 3990
	1    0    0    -1  
$EndComp
Wire Wire Line
	6660 3930 6520 3930
Wire Wire Line
	6520 3930 6520 3990
$Comp
L Device:C_Small C1
U 1 1 5F8DEDD6
P 1730 2300
F 0 "C1" H 1822 2346 50  0000 L CNN
F 1 "10uF" H 1822 2255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1730 2300 50  0001 C CNN
F 3 "~" H 1730 2300 50  0001 C CNN
	1    1730 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5F8DF69F
P 2180 2300
F 0 "C2" H 2272 2346 50  0000 L CNN
F 1 "10uF" H 2272 2255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2180 2300 50  0001 C CNN
F 3 "~" H 2180 2300 50  0001 C CNN
	1    2180 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C3
U 1 1 5F8E0B71
P 2600 2290
F 0 "C3" H 2692 2336 50  0000 L CNN
F 1 "10uF" H 2692 2245 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2600 2290 50  0001 C CNN
F 3 "~" H 2600 2290 50  0001 C CNN
	1    2600 2290
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5F8E113D
P 1730 2400
F 0 "#PWR03" H 1730 2150 50  0001 C CNN
F 1 "GND" H 1735 2227 50  0000 C CNN
F 2 "" H 1730 2400 50  0001 C CNN
F 3 "" H 1730 2400 50  0001 C CNN
	1    1730 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5F8E180D
P 2180 2400
F 0 "#PWR010" H 2180 2150 50  0001 C CNN
F 1 "GND" H 2185 2227 50  0000 C CNN
F 2 "" H 2180 2400 50  0001 C CNN
F 3 "" H 2180 2400 50  0001 C CNN
	1    2180 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5F8E1CB8
P 2600 2390
F 0 "#PWR012" H 2600 2140 50  0001 C CNN
F 1 "GND" H 2605 2217 50  0000 C CNN
F 2 "" H 2600 2390 50  0001 C CNN
F 3 "" H 2600 2390 50  0001 C CNN
	1    2600 2390
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR02
U 1 1 5F8E21BE
P 1730 2200
F 0 "#PWR02" H 1730 2050 50  0001 C CNN
F 1 "VDD" H 1745 2373 50  0000 C CNN
F 2 "" H 1730 2200 50  0001 C CNN
F 3 "" H 1730 2200 50  0001 C CNN
	1    1730 2200
	1    0    0    -1  
$EndComp
$Comp
L power:VDDA #PWR09
U 1 1 5F8E2A09
P 2180 2200
F 0 "#PWR09" H 2180 2050 50  0001 C CNN
F 1 "VDDA" H 2195 2373 50  0000 C CNN
F 2 "" H 2180 2200 50  0001 C CNN
F 3 "" H 2180 2200 50  0001 C CNN
	1    2180 2200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR011
U 1 1 5F8E36F3
P 2600 2190
F 0 "#PWR011" H 2600 2040 50  0001 C CNN
F 1 "+5V" H 2615 2363 50  0000 C CNN
F 2 "" H 2600 2190 50  0001 C CNN
F 3 "" H 2600 2190 50  0001 C CNN
	1    2600 2190
	1    0    0    -1  
$EndComp
$Comp
L Device:LED_Small D1
U 1 1 5F8E47EB
P 3390 2280
F 0 "D1" V 3436 2210 50  0000 R CNN
F 1 "Power" V 3345 2210 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3390 2280 50  0001 C CNN
F 3 "~" V 3390 2280 50  0001 C CNN
	1    3390 2280
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR013
U 1 1 5F8E55A8
P 3390 2180
F 0 "#PWR013" H 3390 2030 50  0001 C CNN
F 1 "+5V" H 3405 2353 50  0000 C CNN
F 2 "" H 3390 2180 50  0001 C CNN
F 3 "" H 3390 2180 50  0001 C CNN
	1    3390 2180
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 5F8E5A32
P 3390 2660
F 0 "#PWR014" H 3390 2410 50  0001 C CNN
F 1 "GND" H 3395 2487 50  0000 C CNN
F 2 "" H 3390 2660 50  0001 C CNN
F 3 "" H 3390 2660 50  0001 C CNN
	1    3390 2660
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R5
U 1 1 5F8E6EDF
P 7480 4690
F 0 "R5" V 7400 4690 50  0000 C CNN
F 1 "470" V 7480 4690 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 7480 4690 50  0001 C CNN
F 3 "~" H 7480 4690 50  0001 C CNN
	1    7480 4690
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R6
U 1 1 5F8E7B3E
P 7480 5360
F 0 "R6" V 7400 5360 50  0000 C CNN
F 1 "470" V 7480 5360 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 7480 5360 50  0001 C CNN
F 3 "~" H 7480 5360 50  0001 C CNN
	1    7480 5360
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C6
U 1 1 5F8E80B2
P 8030 4870
F 0 "C6" H 8122 4916 50  0000 L CNN
F 1 "4.7nF" H 8122 4825 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8030 4870 50  0001 C CNN
F 3 "~" H 8030 4870 50  0001 C CNN
	1    8030 4870
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C7
U 1 1 5F8E8C3B
P 8060 5610
F 0 "C7" H 8152 5656 50  0000 L CNN
F 1 "4.7nF" H 8152 5565 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8060 5610 50  0001 C CNN
F 3 "~" H 8060 5610 50  0001 C CNN
	1    8060 5610
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C8
U 1 1 5F8E9021
P 8580 4690
F 0 "C8" V 8351 4690 50  0000 C CNN
F 1 "10uF" V 8442 4690 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8580 4690 50  0001 C CNN
F 3 "~" H 8580 4690 50  0001 C CNN
	1    8580 4690
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C9
U 1 1 5F8E946B
P 8580 5360
F 0 "C9" V 8351 5360 50  0000 C CNN
F 1 "10uF" V 8442 5360 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8580 5360 50  0001 C CNN
F 3 "~" H 8580 5360 50  0001 C CNN
	1    8580 5360
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR039
U 1 1 5F8F8D03
P 8030 4970
F 0 "#PWR039" H 8030 4720 50  0001 C CNN
F 1 "GND" H 8035 4797 50  0000 C CNN
F 2 "" H 8030 4970 50  0001 C CNN
F 3 "" H 8030 4970 50  0001 C CNN
	1    8030 4970
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR040
U 1 1 5F8F92E6
P 8060 5710
F 0 "#PWR040" H 8060 5460 50  0001 C CNN
F 1 "GND" H 8065 5537 50  0000 C CNN
F 2 "" H 8060 5710 50  0001 C CNN
F 3 "" H 8060 5710 50  0001 C CNN
	1    8060 5710
	1    0    0    -1  
$EndComp
Wire Wire Line
	7580 4690 8030 4690
Wire Wire Line
	8030 4770 8030 4690
Connection ~ 8030 4690
Wire Wire Line
	8030 4690 8480 4690
Wire Wire Line
	8060 5510 8060 5360
Wire Wire Line
	7580 5360 8060 5360
Connection ~ 8060 5360
Wire Wire Line
	8060 5360 8480 5360
Text GLabel 7120 4690 0    50   Input ~ 0
LEFT
Wire Wire Line
	7120 4690 7380 4690
Text GLabel 7150 5360 0    50   Input ~ 0
RIGHT
Wire Wire Line
	7150 5360 7380 5360
$Comp
L Connector:AudioJack4 J5
U 1 1 5F90802D
P 9370 5060
F 0 "J5" H 9040 4943 50  0000 R CNN
F 1 "AudioJack4" H 9040 5034 50  0000 R CNN
F 2 "Project:Jack_3.5mm_PJ320A_Horizontal" H 9370 5060 50  0001 C CNN
F 3 "~" H 9370 5060 50  0001 C CNN
	1    9370 5060
	-1   0    0    1   
$EndComp
Wire Wire Line
	9170 4960 8960 4960
Wire Wire Line
	8960 4960 8960 5360
Wire Wire Line
	8960 5360 8680 5360
Wire Wire Line
	9170 4860 8960 4860
Wire Wire Line
	8960 4860 8960 4690
Wire Wire Line
	8960 4690 8680 4690
$Comp
L power:GND #PWR042
U 1 1 5F90E41A
P 9080 5220
F 0 "#PWR042" H 9080 4970 50  0001 C CNN
F 1 "GND" H 9085 5047 50  0000 C CNN
F 2 "" H 9080 5220 50  0001 C CNN
F 3 "" H 9080 5220 50  0001 C CNN
	1    9080 5220
	1    0    0    -1  
$EndComp
Wire Wire Line
	9080 5220 9080 5160
Wire Wire Line
	9080 5160 9170 5160
NoConn ~ 9170 5060
Text GLabel 8960 4690 1    50   Input ~ 0
L_AC
Text GLabel 8960 5360 3    50   Input ~ 0
R_AC
Wire Wire Line
	9210 1850 9210 1870
Wire Wire Line
	9210 1600 9210 1650
Connection ~ 9210 1650
$Comp
L power:VDD #PWR0101
U 1 1 5F9536E8
P 6210 2550
F 0 "#PWR0101" H 6210 2400 50  0001 C CNN
F 1 "VDD" H 6225 2723 50  0000 C CNN
F 2 "" H 6210 2550 50  0001 C CNN
F 3 "" H 6210 2550 50  0001 C CNN
	1    6210 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R4
U 1 1 5F911D55
P 6210 2650
F 0 "R4" V 6280 2600 50  0000 C CNN
F 1 "100K" V 6210 2650 31  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 6210 2650 50  0001 C CNN
F 3 "~" H 6210 2650 50  0001 C CNN
	1    6210 2650
	-1   0    0    1   
$EndComp
Wire Wire Line
	6660 2830 6210 2830
Wire Wire Line
	6210 2830 6210 2940
Wire Wire Line
	6210 2830 6210 2750
Connection ~ 6210 2830
$Comp
L Device:R_Small R8
U 1 1 5F95DB93
P 3390 2520
F 0 "R8" H 3449 2566 50  0000 L CNN
F 1 "470" V 3390 2460 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 3390 2520 50  0001 C CNN
F 3 "~" H 3390 2520 50  0001 C CNN
	1    3390 2520
	1    0    0    -1  
$EndComp
Wire Wire Line
	3390 2420 3390 2380
Wire Wire Line
	3390 2660 3390 2620
$EndSCHEMATC
