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
L power:+5V #PWR026
U 1 1 5D691EA1
P 5760 2180
F 0 "#PWR026" H 5760 2030 50  0001 C CNN
F 1 "+5V" V 5760 2330 50  0000 L CNN
F 2 "" H 5760 2180 50  0001 C CNN
F 3 "" H 5760 2180 50  0001 C CNN
	1    5760 2180
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR027
U 1 1 5D6B721D
P 5760 2380
F 0 "#PWR027" H 5760 2230 50  0001 C CNN
F 1 "+3.3V" V 5760 2530 50  0000 L CNN
F 2 "" H 5760 2380 50  0001 C CNN
F 3 "" H 5760 2380 50  0001 C CNN
	1    5760 2380
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5FA68CC8
P 5760 2280
F 0 "#PWR07" H 5760 2030 50  0001 C CNN
F 1 "GND" V 5760 2080 50  0000 C CNN
F 2 "" H 5760 2280 50  0001 C CNN
F 3 "" H 5760 2280 50  0001 C CNN
	1    5760 2280
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x04_Male J5
U 1 1 5FA762AC
P 5250 4200
F 0 "J5" H 5450 4450 50  0000 R CNN
F 1 "I2C" H 5300 4450 50  0000 R CNN
F 2 "Connector_JST:JST_SH_SM05B-SRSS-TB_1x05-1MP_P1.00mm_Horizontal" H 5250 4200 50  0001 C CNN
F 3 "~" H 5250 4200 50  0001 C CNN
	1    5250 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5FA762B2
P 5450 4100
F 0 "#PWR08" H 5450 3850 50  0001 C CNN
F 1 "GND" V 5450 3850 50  0000 C CNN
F 2 "" H 5450 4100 50  0001 C CNN
F 3 "" H 5450 4100 50  0001 C CNN
	1    5450 4100
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR09
U 1 1 5FA762B8
P 5450 4200
F 0 "#PWR09" H 5450 4050 50  0001 C CNN
F 1 "+3.3V" V 5450 4450 50  0000 C CNN
F 2 "" H 5450 4200 50  0001 C CNN
F 3 "" H 5450 4200 50  0001 C CNN
	1    5450 4200
	0    1    1    0   
$EndComp
Text GLabel 6055 4300 2    50   Input ~ 0
I2C_SDA
Text GLabel 5740 4400 2    50   Input ~ 0
I2C_SCL
Text GLabel 5760 2980 2    50   Input ~ 0
I2C_SDA
Text GLabel 5760 2880 2    50   Input ~ 0
I2C_SCL
Text GLabel 3310 3480 0    50   Input ~ 0
MI
Text GLabel 3310 2380 0    50   Input ~ 0
TX
$Comp
L power:+5V #PWR0102
U 1 1 6046EC2B
P 7800 2700
F 0 "#PWR0102" H 7800 2550 50  0001 C CNN
F 1 "+5V" V 7800 2850 50  0000 L CNN
F 2 "" H 7800 2700 50  0001 C CNN
F 3 "" H 7800 2700 50  0001 C CNN
	1    7800 2700
	0    1    1    0   
$EndComp
Text GLabel 7800 3300 2    50   Input ~ 0
D6
Text GLabel 7800 3400 2    50   Input ~ 0
D5
Text GLabel 7800 3500 2    50   Input ~ 0
I2C_SCL
Text GLabel 7800 3600 2    50   Input ~ 0
I2C_SDA
$Comp
L power:+3.3V #PWR0105
U 1 1 6046F8DC
P 6900 2200
F 0 "#PWR0105" H 6900 2050 50  0001 C CNN
F 1 "+3.3V" V 6900 2350 50  0000 L CNN
F 2 "" H 6900 2200 50  0001 C CNN
F 3 "" H 6900 2200 50  0001 C CNN
	1    6900 2200
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 6047001F
P 6900 2400
F 0 "#PWR0106" H 6900 2150 50  0001 C CNN
F 1 "GND" V 6900 2200 50  0000 C CNN
F 2 "" H 6900 2400 50  0001 C CNN
F 3 "" H 6900 2400 50  0001 C CNN
	1    6900 2400
	0    1    1    0   
$EndComp
Text GLabel 6900 3100 0    50   Input ~ 0
SCK
Text GLabel 6900 3300 0    50   Input ~ 0
MI
Text GLabel 6900 3500 0    50   Input ~ 0
TX
Text GLabel 6900 3600 0    50   Input ~ 0
D2
$Comp
L UsefulModifications:Teensy4.0_NoMid U1
U 1 1 60F91404
P 4510 2830
F 0 "U1" H 4535 3727 60  0000 C CNN
F 1 "Teensy4.0_NoMid" H 4535 3621 60  0000 C CNN
F 2 "Useful Modifications:Teensy40_NoMid" H 4460 1880 60  0001 C CNN
F 3 "" H 4460 1880 60  0000 C CNN
	1    4510 2830
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 60F95507
P 3310 2180
F 0 "#PWR0108" H 3310 1930 50  0001 C CNN
F 1 "GND" V 3310 1980 50  0000 C CNN
F 2 "" H 3310 2180 50  0001 C CNN
F 3 "" H 3310 2180 50  0001 C CNN
	1    3310 2180
	0    1    1    0   
$EndComp
Text GLabel 5760 3480 2    50   Input ~ 0
SCK
$Comp
L UsefulModifications:Feather_nRF52840 U3
U 1 1 6046C9DA
P 7350 2750
F 0 "U3" H 7350 3647 60  0000 C CNN
F 1 "OLED Feather" H 7350 3541 60  0000 C CNN
F 2 "Useful Modifications:Feather_nRF52840" H 7350 1900 60  0001 C CNN
F 3 "" H 7350 1900 60  0000 C CNN
	1    7350 2750
	1    0    0    -1  
$EndComp
NoConn ~ 7800 2500
NoConn ~ 7800 2600
NoConn ~ 6900 2300
Text GLabel 6900 3200 0    50   Input ~ 0
RCPWMSteering
Text GLabel 3310 2780 0    50   Input ~ 0
D5
Text GLabel 3310 2880 0    50   Input ~ 0
D6
Text GLabel 6900 2500 0    50   Input ~ 0
A0
Text GLabel 6900 2600 0    50   Input ~ 0
A1
Text GLabel 5760 3380 2    50   Input ~ 0
A0
Text GLabel 5760 3280 2    50   Input ~ 0
A1
Text GLabel 3310 3080 0    50   Input ~ 0
D8
Text GLabel 3310 2480 0    50   Input ~ 0
D2
Text GLabel 6900 3400 0    50   Input ~ 0
RX
Text GLabel 3310 2280 0    50   Input ~ 0
RX
NoConn ~ 6900 2100
NoConn ~ 5760 2480
NoConn ~ 5760 2580
NoConn ~ 5760 2680
NoConn ~ 5760 2780
NoConn ~ 3310 2580
NoConn ~ 3310 2680
Text GLabel 3310 2980 0    50   Input ~ 0
D7
$Comp
L Device:R_Small R2
U 1 1 61FBBBDB
P 5955 4300
F 0 "R2" V 5759 4300 50  0000 C CNN
F 1 "10K" V 5850 4300 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5955 4300 50  0001 C CNN
F 3 "~" H 5955 4300 50  0001 C CNN
	1    5955 4300
	0    1    1    0   
$EndComp
Wire Wire Line
	5450 4300 5855 4300
$Comp
L Device:R_Small R1
U 1 1 61FC07E2
P 5640 4400
F 0 "R1" V 5800 4405 50  0000 C CNN
F 1 "10K" V 5720 4400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5640 4400 50  0001 C CNN
F 3 "~" H 5640 4400 50  0001 C CNN
	1    5640 4400
	0    1    1    0   
$EndComp
Wire Wire Line
	5450 4400 5540 4400
Text GLabel 6900 2900 0    50   Input ~ 0
I2C_SDA
Text GLabel 6900 3000 0    50   Input ~ 0
I2C_SCL
Text GLabel 7800 2800 2    50   Input ~ 0
SCK
Text GLabel 3310 3180 0    50   Input ~ 0
D9
Text GLabel 3310 3280 0    50   Input ~ 0
D10
Text GLabel 3310 3380 0    50   Input ~ 0
D11
Text GLabel 5760 3180 2    50   Input ~ 0
A2
Text GLabel 5760 3080 2    50   Input ~ 0
A3
Text GLabel 6900 2700 0    50   Input ~ 0
A2
Text GLabel 6900 2800 0    50   Input ~ 0
A3
Text GLabel 7800 3200 2    50   Input ~ 0
D9
Text GLabel 7800 3100 2    50   Input ~ 0
D10
Text GLabel 7800 3000 2    50   Input ~ 0
D11
Text GLabel 7800 2900 2    50   Input ~ 0
MI
$EndSCHEMATC
