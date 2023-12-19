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
L Connector:Conn_01x04_Male J1
U 1 1 5D5BB7A8
P 6570 4280
F 0 "J1" H 6770 4530 50  0000 R CNN
F 1 "RC" H 6620 4530 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6570 4280 50  0001 C CNN
F 3 "~" H 6570 4280 50  0001 C CNN
	1    6570 4280
	1    0    0    -1  
$EndComp
Text Notes 4259 4020 3    59   ~ 0
3 Y X 2 1 5 G
Text Notes 6529 4130 3    59   ~ 0
S S G 3\n
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
L power:+5V #PWR029
U 1 1 5D6B5159
P 4050 4170
F 0 "#PWR029" H 4050 4020 50  0001 C CNN
F 1 "+5V" V 4050 4320 50  0000 L CNN
F 2 "" H 4050 4170 50  0001 C CNN
F 3 "" H 4050 4170 50  0001 C CNN
	1    4050 4170
	0    -1   -1   0   
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
L power:GND #PWR014
U 1 1 5D6C064F
P 6770 4280
F 0 "#PWR014" H 6770 4030 50  0001 C CNN
F 1 "GND" V 6770 4030 50  0000 C CNN
F 2 "" H 6770 4280 50  0001 C CNN
F 3 "" H 6770 4280 50  0001 C CNN
	1    6770 4280
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR03
U 1 1 5D6D576D
P 6770 4180
F 0 "#PWR03" H 6770 4030 50  0001 C CNN
F 1 "+3.3V" V 6770 4430 50  0000 C CNN
F 2 "" H 6770 4180 50  0001 C CNN
F 3 "" H 6770 4180 50  0001 C CNN
	1    6770 4180
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR030
U 1 1 5D6DC17C
P 4050 4670
F 0 "#PWR030" H 4050 4520 50  0001 C CNN
F 1 "+3.3V" V 4050 4820 50  0000 L CNN
F 2 "" H 4050 4670 50  0001 C CNN
F 3 "" H 4050 4670 50  0001 C CNN
	1    4050 4670
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR028
U 1 1 5D6DE9AA
P 4050 4070
F 0 "#PWR028" H 4050 3820 50  0001 C CNN
F 1 "GND" V 4050 3920 50  0000 R CNN
F 2 "" H 4050 4070 50  0001 C CNN
F 3 "" H 4050 4070 50  0001 C CNN
	1    4050 4070
	0    1    1    0   
$EndComp
$Comp
L Connector:8P8C J7
U 1 1 5D627B3B
P 4450 4370
F 0 "J7" H 4400 4720 50  0000 L CNN
F 1 "8P8C" H 4300 4170 50  0000 L CNN
F 2 "Useful Modifications:RJ45_x08_Tab_Up" V 4450 4395 50  0001 C CNN
F 3 "~" V 4450 4395 50  0001 C CNN
	1    4450 4370
	-1   0    0    1   
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
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 5250 4200 50  0001 C CNN
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
Text GLabel 5450 4300 2    50   Input ~ 0
I2C_SDA
Text GLabel 5450 4400 2    50   Input ~ 0
I2C_SCL
Text GLabel 5760 2980 2    50   Input ~ 0
I2C_SDA
Text GLabel 5760 2880 2    50   Input ~ 0
I2C_SCL
Text GLabel 4050 4770 0    50   Input ~ 0
ActiveSW
Text GLabel 5760 3080 2    50   Input ~ 0
Steering
Text GLabel 5760 3180 2    50   Input ~ 0
Throttle
Text GLabel 6770 4480 2    50   Input ~ 0
RCPWMSteering
Text GLabel 6770 4380 2    50   Input ~ 0
RCPWMThrottle
Text GLabel 3310 3180 0    50   Input ~ 0
ActiveSW
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
Text GLabel 6900 2700 0    50   Input ~ 0
Throttle
Text GLabel 6900 2800 0    50   Input ~ 0
Steering
Text GLabel 6900 3100 0    50   Input ~ 0
SCK
Text GLabel 6900 3300 0    50   Input ~ 0
MI
Text GLabel 6900 3500 0    50   Input ~ 0
TX
Text GLabel 6900 3600 0    50   Input ~ 0
D2
Wire Wire Line
	7170 4990 7500 4990
NoConn ~ 7170 5190
$Comp
L Connector:Conn_01x04_Male J4
U 1 1 5FBAF7AC
P 6970 4990
F 0 "J4" H 7078 5271 50  0000 C CNN
F 1 "Power Input" H 6670 5040 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 6970 4990 50  0001 C CNN
F 3 "~" H 6970 4990 50  0001 C CNN
	1    6970 4990
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5F5C3B2C
P 5490 5010
F 0 "#PWR0107" H 5490 4760 50  0001 C CNN
F 1 "GND" V 5490 4910 50  0000 R CNN
F 2 "" H 5490 5010 50  0001 C CNN
F 3 "" H 5490 5010 50  0001 C CNN
	1    5490 5010
	0    -1   -1   0   
$EndComp
$Comp
L power:+12V #PWR024
U 1 1 5EE8644F
P 5490 4910
F 0 "#PWR024" H 5490 4760 50  0001 C CNN
F 1 "+12V" V 5505 5038 50  0000 L CNN
F 2 "" H 5490 4910 50  0001 C CNN
F 3 "" H 5490 4910 50  0001 C CNN
	1    5490 4910
	0    1    1    0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J13
U 1 1 5EE8257A
P 5290 5010
F 0 "J13" H 5208 4685 50  0000 C CNN
F 1 "Main Power" H 5208 4776 50  0000 C CNN
F 2 "Useful Modifications:TerminalBlock_bornier-2_P5.08mm" H 5290 5010 50  0001 C CNN
F 3 "~" H 5290 5010 50  0001 C CNN
	1    5290 5010
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 5EE28E61
P 7500 4990
F 0 "#PWR0104" H 7500 4840 50  0001 C CNN
F 1 "+5V" V 7500 5090 50  0000 L CNN
F 2 "" H 7500 4990 50  0001 C CNN
F 3 "" H 7500 4990 50  0001 C CNN
	1    7500 4990
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5EE242AC
P 7170 4890
F 0 "#PWR0103" H 7170 4640 50  0001 C CNN
F 1 "GND" V 7170 4770 50  0000 R CNN
F 2 "" H 7170 4890 50  0001 C CNN
F 3 "" H 7170 4890 50  0001 C CNN
	1    7170 4890
	0    -1   -1   0   
$EndComp
$Comp
L power:+12V #PWR0101
U 1 1 5EE21F5B
P 7170 5090
F 0 "#PWR0101" H 7170 4940 50  0001 C CNN
F 1 "+12V" V 7185 5218 50  0000 L CNN
F 2 "" H 7170 5090 50  0001 C CNN
F 3 "" H 7170 5090 50  0001 C CNN
	1    7170 5090
	0    1    1    0   
$EndComp
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
Text GLabel 3310 3280 0    50   Input ~ 0
RCPWMThrottle
Text GLabel 3310 3380 0    50   Input ~ 0
RCPWMSteering
Text GLabel 4050 4470 0    50   Input ~ 0
Steering
Text GLabel 4050 4570 0    50   Input ~ 0
Throttle
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
NoConn ~ 6900 2900
NoConn ~ 6900 3000
Text GLabel 6900 3200 0    50   Input ~ 0
RCPWMSteering
Text GLabel 7800 3200 2    50   Input ~ 0
ActiveSW
Text GLabel 7800 3100 2    50   Input ~ 0
RCPWMThrottle
Text GLabel 7800 3000 2    50   Input ~ 0
RCPWMSteering
NoConn ~ 7800 2800
NoConn ~ 7800 2900
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
Text GLabel 4050 4270 0    50   Input ~ 0
D7
Text GLabel 4050 4370 0    50   Input ~ 0
D8
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
$EndSCHEMATC
