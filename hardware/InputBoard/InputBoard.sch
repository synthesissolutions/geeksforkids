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
L Connector:8P8C J1
U 1 1 5D58DD64
P 4190 1570
F 0 "J1" V 4201 2100 50  0000 L CNN
F 1 "8P8C" V 4292 2100 50  0000 L CNN
F 2 "Useful Modifications:RJ45_x08_Horizontal_tabs" V 4190 1595 50  0001 C CNN
F 3 "~" V 4190 1595 50  0001 C CNN
	1    4190 1570
	0    1    1    0   
$EndComp
Text Notes 3840 1870 0    59   ~ 0
G 5 1 2 X Y 3
$Comp
L power:GND #PWR05
U 1 1 5D6AE98C
P 3890 1970
F 0 "#PWR05" H 3890 1720 50  0001 C CNN
F 1 "GND" V 3890 1750 50  0000 C CNN
F 2 "" H 3890 1970 50  0001 C CNN
F 3 "" H 3890 1970 50  0001 C CNN
	1    3890 1970
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR010
U 1 1 5D6B449C
P 4490 1970
F 0 "#PWR010" H 4490 1820 50  0001 C CNN
F 1 "+3.3V" V 4490 2230 50  0000 C CNN
F 2 "" H 4490 1970 50  0001 C CNN
F 3 "" H 4490 1970 50  0001 C CNN
	1    4490 1970
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR06
U 1 1 5D6B4DCC
P 3990 1970
F 0 "#PWR06" H 3990 1820 50  0001 C CNN
F 1 "+5V" V 3980 2190 50  0000 C CNN
F 2 "" H 3990 1970 50  0001 C CNN
F 3 "" H 3990 1970 50  0001 C CNN
	1    3990 1970
	-1   0    0    1   
$EndComp
Text GLabel 4090 1970 3    50   Input ~ 0
Sound1
Text GLabel 4190 1970 3    50   Input ~ 0
Sound2
Text GLabel 4290 1970 3    50   Input ~ 0
JoyX
Text GLabel 4390 1970 3    50   Input ~ 0
JoyY
Text GLabel 7030 2060 2    50   Input ~ 0
JoyY
$Comp
L MCU_Microchip_ATtiny:ATtiny814-SS U1
U 1 1 6015A26B
P 6430 1960
F 0 "U1" H 6020 2630 50  0000 C CNN
F 1 "ATtiny814-SS" H 6790 2610 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 6430 1960 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/40001912A.pdf" H 6430 1960 50  0001 C CNN
	1    6430 1960
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 60170FA0
P 6430 2660
F 0 "#PWR016" H 6430 2410 50  0001 C CNN
F 1 "GND" V 6430 2440 50  0000 C CNN
F 2 "" H 6430 2660 50  0001 C CNN
F 3 "" H 6430 2660 50  0001 C CNN
	1    6430 2660
	1    0    0    -1  
$EndComp
Text GLabel 7030 1860 2    50   Input ~ 0
RightButton
Text GLabel 7030 1760 2    50   Input ~ 0
LeftButton
Text GLabel 4590 1970 3    50   Input ~ 0
Other
Text GLabel 7030 2160 2    50   Input ~ 0
ReverseButton
Text GLabel 7030 1960 2    50   Input ~ 0
JoyX
Text GLabel 7030 1660 2    50   Input ~ 0
DriveButton
Text GLabel 7030 2260 2    50   Input ~ 0
Other
$Comp
L power:GND #PWR023
U 1 1 601EFEBA
P 4330 3990
F 0 "#PWR023" H 4330 3740 50  0001 C CNN
F 1 "GND" V 4330 3790 50  0000 C CNN
F 2 "" H 4330 3990 50  0001 C CNN
F 3 "" H 4330 3990 50  0001 C CNN
	1    4330 3990
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Male J4
U 1 1 601EFEC4
P 4330 4190
F 0 "J4" V 4484 4002 50  0000 R CNN
F 1 "Programmer" V 4393 4002 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4330 4190 50  0001 C CNN
F 3 "~" H 4330 4190 50  0001 C CNN
	1    4330 4190
	0    -1   -1   0   
$EndComp
Text GLabel 4430 3990 1    50   Input ~ 0
Program
Text GLabel 7030 1560 2    50   Input ~ 0
Program
$Comp
L power:+3.3V #PWR028
U 1 1 6019E5D0
P 4230 3990
F 0 "#PWR028" H 4230 3840 50  0001 C CNN
F 1 "+3.3V" V 4230 4250 50  0000 C CNN
F 2 "" H 4230 3990 50  0001 C CNN
F 3 "" H 4230 3990 50  0001 C CNN
	1    4230 3990
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR029
U 1 1 601A23F4
P 6430 1260
F 0 "#PWR029" H 6430 1110 50  0001 C CNN
F 1 "+3.3V" V 6430 1520 50  0000 C CNN
F 2 "" H 6430 1260 50  0001 C CNN
F 3 "" H 6430 1260 50  0001 C CNN
	1    6430 1260
	1    0    0    -1  
$EndComp
Text GLabel 5830 1860 0    50   Input ~ 0
RX
Text GLabel 5830 1760 0    50   Input ~ 0
TX
Text GLabel 5830 1560 0    50   Input ~ 0
SCL
Text GLabel 5830 1660 0    50   Input ~ 0
SDA
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 604EF3F5
P 8890 3790
F 0 "J2" H 8998 4071 50  0000 C CNN
F 1 "Conn_01x04_Male" H 8998 3980 50  0000 C CNN
F 2 "Connector_JST:JST_SH_SM04B-SRSS-TB_1x04-1MP_P1.00mm_Horizontal" H 8890 3790 50  0001 C CNN
F 3 "~" H 8890 3790 50  0001 C CNN
	1    8890 3790
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 604F0DDC
P 9090 3690
F 0 "#PWR03" H 9090 3440 50  0001 C CNN
F 1 "GND" V 9090 3490 50  0000 C CNN
F 2 "" H 9090 3690 50  0001 C CNN
F 3 "" H 9090 3690 50  0001 C CNN
	1    9090 3690
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR04
U 1 1 604F1EBB
P 9090 3790
F 0 "#PWR04" H 9090 3640 50  0001 C CNN
F 1 "+3.3V" V 9090 4050 50  0000 C CNN
F 2 "" H 9090 3790 50  0001 C CNN
F 3 "" H 9090 3790 50  0001 C CNN
	1    9090 3790
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R2
U 1 1 604F3129
P 9800 4200
F 0 "R2" H 9859 4246 50  0000 L CNN
F 1 "10K" H 9859 4155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9800 4200 50  0001 C CNN
F 3 "~" H 9800 4200 50  0001 C CNN
	1    9800 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 604F5584
P 9310 4200
F 0 "R1" H 9369 4246 50  0000 L CNN
F 1 "10K" H 9369 4155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9310 4200 50  0001 C CNN
F 3 "~" H 9310 4200 50  0001 C CNN
	1    9310 4200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR07
U 1 1 604F6219
P 9310 4300
F 0 "#PWR07" H 9310 4150 50  0001 C CNN
F 1 "+3.3V" V 9310 4560 50  0000 C CNN
F 2 "" H 9310 4300 50  0001 C CNN
F 3 "" H 9310 4300 50  0001 C CNN
	1    9310 4300
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR022
U 1 1 604F6B33
P 9800 4300
F 0 "#PWR022" H 9800 4150 50  0001 C CNN
F 1 "+3.3V" V 9800 4560 50  0000 C CNN
F 2 "" H 9800 4300 50  0001 C CNN
F 3 "" H 9800 4300 50  0001 C CNN
	1    9800 4300
	-1   0    0    1   
$EndComp
Text GLabel 9420 3990 2    50   Input ~ 0
SCL
Wire Wire Line
	9090 3990 9310 3990
Wire Wire Line
	9310 3990 9310 4100
Wire Wire Line
	9420 3990 9310 3990
Connection ~ 9310 3990
Text GLabel 9900 3890 2    50   Input ~ 0
SDA
Wire Wire Line
	9090 3890 9800 3890
Wire Wire Line
	9800 4100 9800 3890
Connection ~ 9800 3890
Wire Wire Line
	9800 3890 9900 3890
$Comp
L Connector:Conn_01x04_Male J3
U 1 1 604F8C23
P 6210 3920
F 0 "J3" H 6318 4201 50  0000 C CNN
F 1 "Conn_01x04_Male" H 6318 4110 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6210 3920 50  0001 C CNN
F 3 "~" H 6210 3920 50  0001 C CNN
	1    6210 3920
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 604FB52D
P 6410 3920
F 0 "#PWR01" H 6410 3670 50  0001 C CNN
F 1 "GND" V 6410 3720 50  0000 C CNN
F 2 "" H 6410 3920 50  0001 C CNN
F 3 "" H 6410 3920 50  0001 C CNN
	1    6410 3920
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR02
U 1 1 604FBE91
P 6410 3820
F 0 "#PWR02" H 6410 3670 50  0001 C CNN
F 1 "+3.3V" V 6410 4080 50  0000 C CNN
F 2 "" H 6410 3820 50  0001 C CNN
F 3 "" H 6410 3820 50  0001 C CNN
	1    6410 3820
	0    1    1    0   
$EndComp
Text GLabel 6410 4020 2    50   Input ~ 0
TX
Text GLabel 6410 4120 2    50   Input ~ 0
RX
$Comp
L Connector:Conn_01x04_Male J7
U 1 1 604FCE85
P 8590 1400
F 0 "J7" H 8698 1681 50  0000 C CNN
F 1 "Conn_01x04_Male" H 8698 1590 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 8590 1400 50  0001 C CNN
F 3 "~" H 8590 1400 50  0001 C CNN
	1    8590 1400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR015
U 1 1 604FDD76
P 8790 1300
F 0 "#PWR015" H 8790 1150 50  0001 C CNN
F 1 "+5V" V 8780 1520 50  0000 C CNN
F 2 "" H 8790 1300 50  0001 C CNN
F 3 "" H 8790 1300 50  0001 C CNN
	1    8790 1300
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR018
U 1 1 604FEFAF
P 8790 1600
F 0 "#PWR018" H 8790 1450 50  0001 C CNN
F 1 "+3.3V" V 8790 1860 50  0000 C CNN
F 2 "" H 8790 1600 50  0001 C CNN
F 3 "" H 8790 1600 50  0001 C CNN
	1    8790 1600
	0    1    1    0   
$EndComp
Text GLabel 8790 1500 2    50   Input ~ 0
DriveButton
$Comp
L power:GND #PWR017
U 1 1 60500109
P 8790 1400
F 0 "#PWR017" H 8790 1150 50  0001 C CNN
F 1 "GND" V 8790 1180 50  0000 C CNN
F 2 "" H 8790 1400 50  0001 C CNN
F 3 "" H 8790 1400 50  0001 C CNN
	1    8790 1400
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x04_Male J5
U 1 1 60504CA9
P 8580 2000
F 0 "J5" H 8688 2281 50  0000 C CNN
F 1 "Conn_01x04_Male" H 8688 2190 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 8580 2000 50  0001 C CNN
F 3 "~" H 8580 2000 50  0001 C CNN
	1    8580 2000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR08
U 1 1 60504CAF
P 8780 1900
F 0 "#PWR08" H 8780 1750 50  0001 C CNN
F 1 "+5V" V 8770 2120 50  0000 C CNN
F 2 "" H 8780 1900 50  0001 C CNN
F 3 "" H 8780 1900 50  0001 C CNN
	1    8780 1900
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR011
U 1 1 60504CB5
P 8780 2200
F 0 "#PWR011" H 8780 2050 50  0001 C CNN
F 1 "+3.3V" V 8780 2460 50  0000 C CNN
F 2 "" H 8780 2200 50  0001 C CNN
F 3 "" H 8780 2200 50  0001 C CNN
	1    8780 2200
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 60504CBC
P 8780 2000
F 0 "#PWR09" H 8780 1750 50  0001 C CNN
F 1 "GND" V 8780 1780 50  0000 C CNN
F 2 "" H 8780 2000 50  0001 C CNN
F 3 "" H 8780 2000 50  0001 C CNN
	1    8780 2000
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x04_Male J6
U 1 1 605054CB
P 8580 2620
F 0 "J6" H 8688 2901 50  0000 C CNN
F 1 "Conn_01x04_Male" H 8688 2810 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 8580 2620 50  0001 C CNN
F 3 "~" H 8580 2620 50  0001 C CNN
	1    8580 2620
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR012
U 1 1 605054D1
P 8780 2520
F 0 "#PWR012" H 8780 2370 50  0001 C CNN
F 1 "+5V" V 8770 2740 50  0000 C CNN
F 2 "" H 8780 2520 50  0001 C CNN
F 3 "" H 8780 2520 50  0001 C CNN
	1    8780 2520
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR014
U 1 1 605054D7
P 8780 2820
F 0 "#PWR014" H 8780 2670 50  0001 C CNN
F 1 "+3.3V" V 8780 3080 50  0000 C CNN
F 2 "" H 8780 2820 50  0001 C CNN
F 3 "" H 8780 2820 50  0001 C CNN
	1    8780 2820
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 605054DE
P 8780 2620
F 0 "#PWR013" H 8780 2370 50  0001 C CNN
F 1 "GND" V 8780 2400 50  0000 C CNN
F 2 "" H 8780 2620 50  0001 C CNN
F 3 "" H 8780 2620 50  0001 C CNN
	1    8780 2620
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x04_Male J9
U 1 1 6050692F
P 9760 1390
F 0 "J9" H 9868 1671 50  0000 C CNN
F 1 "Conn_01x04_Male" H 9868 1580 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 9760 1390 50  0001 C CNN
F 3 "~" H 9760 1390 50  0001 C CNN
	1    9760 1390
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR024
U 1 1 60506935
P 9960 1290
F 0 "#PWR024" H 9960 1140 50  0001 C CNN
F 1 "+5V" V 9950 1510 50  0000 C CNN
F 2 "" H 9960 1290 50  0001 C CNN
F 3 "" H 9960 1290 50  0001 C CNN
	1    9960 1290
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR026
U 1 1 6050693B
P 9960 1590
F 0 "#PWR026" H 9960 1440 50  0001 C CNN
F 1 "+3.3V" V 9960 1850 50  0000 C CNN
F 2 "" H 9960 1590 50  0001 C CNN
F 3 "" H 9960 1590 50  0001 C CNN
	1    9960 1590
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR025
U 1 1 60506942
P 9960 1390
F 0 "#PWR025" H 9960 1140 50  0001 C CNN
F 1 "GND" V 9960 1170 50  0000 C CNN
F 2 "" H 9960 1390 50  0001 C CNN
F 3 "" H 9960 1390 50  0001 C CNN
	1    9960 1390
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x04_Male J10
U 1 1 605074E4
P 9800 2050
F 0 "J10" H 9908 2331 50  0000 C CNN
F 1 "Conn_01x04_Male" H 9908 2240 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 9800 2050 50  0001 C CNN
F 3 "~" H 9800 2050 50  0001 C CNN
	1    9800 2050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR027
U 1 1 605074EA
P 10000 1950
F 0 "#PWR027" H 10000 1800 50  0001 C CNN
F 1 "+5V" V 9990 2170 50  0000 C CNN
F 2 "" H 10000 1950 50  0001 C CNN
F 3 "" H 10000 1950 50  0001 C CNN
	1    10000 1950
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR031
U 1 1 605074F0
P 10000 2250
F 0 "#PWR031" H 10000 2100 50  0001 C CNN
F 1 "+3.3V" V 10000 2510 50  0000 C CNN
F 2 "" H 10000 2250 50  0001 C CNN
F 3 "" H 10000 2250 50  0001 C CNN
	1    10000 2250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR030
U 1 1 605074F7
P 10000 2050
F 0 "#PWR030" H 10000 1800 50  0001 C CNN
F 1 "GND" V 10000 1830 50  0000 C CNN
F 2 "" H 10000 2050 50  0001 C CNN
F 3 "" H 10000 2050 50  0001 C CNN
	1    10000 2050
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x04_Male J11
U 1 1 605083D1
P 9870 2680
F 0 "J11" H 9978 2961 50  0000 C CNN
F 1 "Conn_01x04_Male" H 9978 2870 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 9870 2680 50  0001 C CNN
F 3 "~" H 9870 2680 50  0001 C CNN
	1    9870 2680
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR032
U 1 1 605083D7
P 10070 2580
F 0 "#PWR032" H 10070 2430 50  0001 C CNN
F 1 "+5V" V 10060 2800 50  0000 C CNN
F 2 "" H 10070 2580 50  0001 C CNN
F 3 "" H 10070 2580 50  0001 C CNN
	1    10070 2580
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR034
U 1 1 605083DD
P 10070 2880
F 0 "#PWR034" H 10070 2730 50  0001 C CNN
F 1 "+3.3V" V 10070 3140 50  0000 C CNN
F 2 "" H 10070 2880 50  0001 C CNN
F 3 "" H 10070 2880 50  0001 C CNN
	1    10070 2880
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR033
U 1 1 605083E4
P 10070 2680
F 0 "#PWR033" H 10070 2430 50  0001 C CNN
F 1 "GND" V 10070 2460 50  0000 C CNN
F 2 "" H 10070 2680 50  0001 C CNN
F 3 "" H 10070 2680 50  0001 C CNN
	1    10070 2680
	0    -1   -1   0   
$EndComp
Text GLabel 8780 2100 2    50   Input ~ 0
LeftButton
Text GLabel 8780 2720 2    50   Input ~ 0
RightButton
Text GLabel 9960 1490 2    50   Input ~ 0
ReverseButton
Text GLabel 10000 2150 2    50   Input ~ 0
Sound1
Text GLabel 10070 2780 2    50   Input ~ 0
Sound2
Wire Notes Line
	11220 3060 11220 3070
Text Notes 8650 840  0    118  ~ 0
Input Headers
Text Notes 10360 2020 0    50   ~ 0
Sound Buttons \ndo not connect \nto the microcontroller.
Wire Notes Line
	3420 3060 11220 3060
Wire Notes Line
	3420 470  3420 4770
Wire Notes Line
	5160 460  5160 4770
Wire Notes Line
	3420 4770 11230 4770
Wire Notes Line
	8070 480  8070 4770
Text Notes 5410 830  0    118  ~ 0
ATTiny 814 Microcontroller
Text Notes 3850 1120 0    118  ~ 0
RJ45 to \nElectronics\nCaddy
Text Notes 3700 3540 0    118  ~ 0
Programming\nHeader
Text Notes 5440 3440 0    118  ~ 0
RX/TX Debugging Header
Text Notes 9400 3390 0    118  ~ 0
I2C
$EndSCHEMATC
