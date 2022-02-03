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
L Connector:Conn_01x04_Male J2
U 1 1 5D5BB7A8
P 1150 2240
F 0 "J2" H 1350 2490 50  0000 R CNN
F 1 "RC" H 1200 2490 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 1150 2240 50  0001 C CNN
F 3 "~" H 1150 2240 50  0001 C CNN
	1    1150 2240
	1    0    0    -1  
$EndComp
Text Notes 9639 1660 3    59   ~ 0
3 Y X 2 1 5 G
Text Notes 1109 2090 3    59   ~ 0
S S G 3\n
$Comp
L power:+5V #PWR020
U 1 1 5D691EA1
P 3740 1530
F 0 "#PWR020" H 3740 1380 50  0001 C CNN
F 1 "+5V" V 3740 1680 50  0000 L CNN
F 2 "" H 3740 1530 50  0001 C CNN
F 3 "" H 3740 1530 50  0001 C CNN
	1    3740 1530
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR036
U 1 1 5D6B5159
P 9430 1810
F 0 "#PWR036" H 9430 1660 50  0001 C CNN
F 1 "+5V" V 9430 1960 50  0000 L CNN
F 2 "" H 9430 1810 50  0001 C CNN
F 3 "" H 9430 1810 50  0001 C CNN
	1    9430 1810
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR017
U 1 1 5D6B721D
P 2740 1030
F 0 "#PWR017" H 2740 880 50  0001 C CNN
F 1 "+3.3V" V 2740 1180 50  0000 L CNN
F 2 "" H 2740 1030 50  0001 C CNN
F 3 "" H 2740 1030 50  0001 C CNN
	1    2740 1030
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5D6C064F
P 1350 2240
F 0 "#PWR04" H 1350 1990 50  0001 C CNN
F 1 "GND" V 1350 1990 50  0000 C CNN
F 2 "" H 1350 2240 50  0001 C CNN
F 3 "" H 1350 2240 50  0001 C CNN
	1    1350 2240
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR03
U 1 1 5D6D576D
P 1350 2140
F 0 "#PWR03" H 1350 1990 50  0001 C CNN
F 1 "+3.3V" V 1350 2390 50  0000 C CNN
F 2 "" H 1350 2140 50  0001 C CNN
F 3 "" H 1350 2140 50  0001 C CNN
	1    1350 2140
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR037
U 1 1 5D6DC17C
P 9430 2310
F 0 "#PWR037" H 9430 2160 50  0001 C CNN
F 1 "+3.3V" V 9430 2460 50  0000 L CNN
F 2 "" H 9430 2310 50  0001 C CNN
F 3 "" H 9430 2310 50  0001 C CNN
	1    9430 2310
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR035
U 1 1 5D6DE9AA
P 9430 1710
F 0 "#PWR035" H 9430 1460 50  0001 C CNN
F 1 "GND" V 9430 1560 50  0000 R CNN
F 2 "" H 9430 1710 50  0001 C CNN
F 3 "" H 9430 1710 50  0001 C CNN
	1    9430 1710
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J34
U 1 1 5D8359A2
P 4790 2590
F 0 "J34" H 4898 2771 50  0000 C CNN
F 1 "BT Switch" H 4898 2680 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4790 2590 50  0001 C CNN
F 3 "~" H 4790 2590 50  0001 C CNN
	1    4790 2590
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 5D8619B7
P 4990 2690
F 0 "#PWR026" H 4990 2440 50  0001 C CNN
F 1 "GND" V 4990 2490 50  0000 C CNN
F 2 "" H 4990 2690 50  0001 C CNN
F 3 "" H 4990 2690 50  0001 C CNN
	1    4990 2690
	0    -1   -1   0   
$EndComp
$Comp
L Connector:8P8C J46
U 1 1 5D627B3B
P 9830 2010
F 0 "J46" H 9780 2360 50  0000 L CNN
F 1 "Complex RJ45" H 9540 1560 50  0000 L CNN
F 2 "Useful Modifications:RJ45_x08_Tab_Up" V 9830 2035 50  0001 C CNN
F 3 "~" V 9830 2035 50  0001 C CNN
	1    9830 2010
	-1   0    0    1   
$EndComp
$Comp
L power:+12V #PWR012
U 1 1 5EE21F5B
P 2110 3410
F 0 "#PWR012" H 2110 3260 50  0001 C CNN
F 1 "+12V" V 2140 3470 50  0000 L CNN
F 2 "" H 2110 3410 50  0001 C CNN
F 3 "" H 2110 3410 50  0001 C CNN
	1    2110 3410
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5EE242AC
P 2110 3210
F 0 "#PWR011" H 2110 2960 50  0001 C CNN
F 1 "GND" V 2110 3090 50  0000 R CNN
F 2 "" H 2110 3210 50  0001 C CNN
F 3 "" H 2110 3210 50  0001 C CNN
	1    2110 3210
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR015
U 1 1 5EE28E61
P 2440 3310
F 0 "#PWR015" H 2440 3160 50  0001 C CNN
F 1 "+5V" V 2440 3410 50  0000 L CNN
F 2 "" H 2440 3310 50  0001 C CNN
F 3 "" H 2440 3310 50  0001 C CNN
	1    2440 3310
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP1
U 1 1 5EE709D2
P 2110 3210
F 0 "TP1" H 2060 3460 50  0000 L CNN
F 1 "Gnd" H 1920 3330 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_1.5x1.5mm" H 2310 3210 50  0001 C CNN
F 3 "~" H 2310 3210 50  0001 C CNN
	1    2110 3210
	1    0    0    -1  
$EndComp
Text GLabel 9430 1910 0    50   Input ~ 0
Sound1
Text GLabel 9430 2010 0    50   Input ~ 0
Sound2
Text GLabel 8790 2670 0    50   Input ~ 0
Throttle
Text GLabel 8820 2090 0    50   Input ~ 0
Steering
Text GLabel 2840 1530 0    50   Input ~ 0
LinAct_Position
Text GLabel 4990 2590 2    50   Input ~ 0
BT_Switch
Text GLabel 3740 2230 2    50   Input ~ 0
BT_Switch
$Comp
L power:GND #PWR06
U 1 1 5FA43531
P 1370 1590
F 0 "#PWR06" H 1370 1340 50  0001 C CNN
F 1 "GND" V 1370 1390 50  0000 C CNN
F 2 "" H 1370 1590 50  0001 C CNN
F 3 "" H 1370 1590 50  0001 C CNN
	1    1370 1590
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR05
U 1 1 5FA43537
P 1370 1390
F 0 "#PWR05" H 1370 1240 50  0001 C CNN
F 1 "+3.3V" V 1370 1590 50  0000 C CNN
F 2 "" H 1370 1390 50  0001 C CNN
F 3 "" H 1370 1390 50  0001 C CNN
	1    1370 1390
	0    1    1    0   
$EndComp
Text Notes 1129 1340 3    59   ~ 0
G S 3
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 5FA4353E
P 1170 1490
F 0 "J3" H 1510 1740 50  0000 R CNN
F 1 "SpeedCtrl" H 1370 1750 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1170 1490 50  0001 C CNN
F 3 "~" H 1170 1490 50  0001 C CNN
	1    1170 1490
	1    0    0    -1  
$EndComp
Text GLabel 1370 1490 2    50   Input ~ 0
SpeedCtrl
Text GLabel 2840 1630 0    50   Input ~ 0
SpeedCtrl
$Comp
L power:GND #PWR029
U 1 1 5FA56C07
P 5010 2150
F 0 "#PWR029" H 5010 1900 50  0001 C CNN
F 1 "GND" V 5010 1950 50  0000 C CNN
F 2 "" H 5010 2150 50  0001 C CNN
F 3 "" H 5010 2150 50  0001 C CNN
	1    5010 2150
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x03_Female J37
U 1 1 5FA5BE7E
P 4810 2050
F 0 "J37" H 4910 2050 50  0000 C CNN
F 1 "LinAct_M3" H 5000 1940 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4810 2050 50  0001 C CNN
F 3 "~" H 4810 2050 50  0001 C CNN
	1    4810 2050
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Female J36
U 1 1 5FA5B276
P 4810 1650
F 0 "J36" H 4910 1650 50  0000 C CNN
F 1 "Right_M2" H 4990 1550 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4810 1650 50  0001 C CNN
F 3 "~" H 4810 1650 50  0001 C CNN
	1    4810 1650
	-1   0    0    1   
$EndComp
Text GLabel 5010 1950 2    50   Input ~ 0
LinAct_PWM
Text GLabel 5010 2050 2    50   Input ~ 0
LinAct_DIR
$Comp
L Connector:Conn_01x03_Female J35
U 1 1 5FA534CD
P 4810 1200
F 0 "J35" H 4838 1226 50  0000 L CNN
F 1 "Left_M1" H 4810 1100 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4810 1200 50  0001 C CNN
F 3 "~" H 4810 1200 50  0001 C CNN
	1    4810 1200
	-1   0    0    1   
$EndComp
Text GLabel 5010 1550 2    50   Input ~ 0
Right_PWM
Text GLabel 5010 1650 2    50   Input ~ 0
Right_DIR
Text GLabel 5010 1100 2    50   Input ~ 0
Left_PWM
Text GLabel 5010 1200 2    50   Input ~ 0
Left_DIR
Text GLabel 1310 990  2    50   Input ~ 0
LinAct_Position
$Comp
L Connector:Conn_01x03_Male J1
U 1 1 5D5BCD6A
P 1110 890
F 0 "J1" H 1320 1150 50  0000 R CNN
F 1 "LinAct" H 1190 1140 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1110 890 50  0001 C CNN
F 3 "~" H 1110 890 50  0001 C CNN
	1    1110 890 
	1    0    0    -1  
$EndComp
Text Notes 1069 740  3    59   ~ 0
S G 3
$Comp
L power:+3.3V #PWR01
U 1 1 5D6D67AA
P 1310 790
F 0 "#PWR01" H 1310 640 50  0001 C CNN
F 1 "+3.3V" V 1310 990 50  0000 C CNN
F 2 "" H 1310 790 50  0001 C CNN
F 3 "" H 1310 790 50  0001 C CNN
	1    1310 790 
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5D6CA869
P 1310 890
F 0 "#PWR02" H 1310 640 50  0001 C CNN
F 1 "GND" V 1310 690 50  0000 C CNN
F 2 "" H 1310 890 50  0001 C CNN
F 3 "" H 1310 890 50  0001 C CNN
	1    1310 890 
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR028
U 1 1 5D6BF649
P 5010 1750
F 0 "#PWR028" H 5010 1500 50  0001 C CNN
F 1 "GND" V 5010 1550 50  0000 C CNN
F 2 "" H 5010 1750 50  0001 C CNN
F 3 "" H 5010 1750 50  0001 C CNN
	1    5010 1750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR027
U 1 1 5D6BCEFD
P 5010 1300
F 0 "#PWR027" H 5010 1050 50  0001 C CNN
F 1 "GND" V 5010 1100 50  0000 C CNN
F 2 "" H 5010 1300 50  0001 C CNN
F 3 "" H 5010 1300 50  0001 C CNN
	1    5010 1300
	0    -1   -1   0   
$EndComp
Text GLabel 3740 1630 2    50   Input ~ 0
Left_PWM
Text GLabel 3740 1730 2    50   Input ~ 0
Left_DIR
Text GLabel 3740 1830 2    50   Input ~ 0
Right_PWM
Text GLabel 3740 1930 2    50   Input ~ 0
Right_DIR
Text GLabel 3740 2030 2    50   Input ~ 0
LinAct_PWM
Text GLabel 3740 2130 2    50   Input ~ 0
LinAct_DIR
$Comp
L power:GND #PWR018
U 1 1 5FA68CC8
P 2840 1230
F 0 "#PWR018" H 2840 980 50  0001 C CNN
F 1 "GND" V 2840 1030 50  0000 C CNN
F 2 "" H 2840 1230 50  0001 C CNN
F 3 "" H 2840 1230 50  0001 C CNN
	1    2840 1230
	0    1    1    0   
$EndComp
$Comp
L UsefulModifications:Feather_nRF52840 U1
U 1 1 5FA6E9E8
P 3290 1580
F 0 "U1" H 3290 2477 60  0000 C CNN
F 1 "Feather_nRF52840" H 3290 2371 60  0000 C CNN
F 2 "Useful Modifications:Feather_nRF52840" H 3290 730 60  0001 C CNN
F 3 "" H 3290 730 60  0000 C CNN
	1    3290 1580
	1    0    0    -1  
$EndComp
NoConn ~ 3740 1430
NoConn ~ 3740 1330
NoConn ~ 2840 2330
NoConn ~ 2840 2130
NoConn ~ 2840 2030
NoConn ~ 2840 1930
NoConn ~ 2840 1130
NoConn ~ 2840 930 
$Comp
L Connector:Conn_01x04_Male J27
U 1 1 5FA762AC
P 4160 3070
F 0 "J27" H 4360 3320 50  0000 R CNN
F 1 "I2C" H 4210 3320 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 4160 3070 50  0001 C CNN
F 3 "~" H 4160 3070 50  0001 C CNN
	1    4160 3070
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 5FA762B2
P 4360 2970
F 0 "#PWR023" H 4360 2720 50  0001 C CNN
F 1 "GND" V 4360 2720 50  0000 C CNN
F 2 "" H 4360 2970 50  0001 C CNN
F 3 "" H 4360 2970 50  0001 C CNN
	1    4360 2970
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR024
U 1 1 5FA762B8
P 4360 3070
F 0 "#PWR024" H 4360 2920 50  0001 C CNN
F 1 "+3.3V" V 4360 3320 50  0000 C CNN
F 2 "" H 4360 3070 50  0001 C CNN
F 3 "" H 4360 3070 50  0001 C CNN
	1    4360 3070
	0    1    1    0   
$EndComp
Text GLabel 4360 3170 2    50   Input ~ 0
I2C_SDA
Text GLabel 4360 3270 2    50   Input ~ 0
I2C_SCL
Text GLabel 3740 2430 2    50   Input ~ 0
I2C_SDA
Text GLabel 3740 2330 2    50   Input ~ 0
I2C_SCL
Text GLabel 9430 2410 0    50   Input ~ 0
ActiveSW
$Comp
L Connector:TestPoint TP3
U 1 1 5FA61138
P 2740 1030
F 0 "TP3" H 2640 1230 50  0000 L CNN
F 1 "3.3V" H 2540 1180 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_1.5x1.5mm" H 2940 1030 50  0001 C CNN
F 3 "~" H 2940 1030 50  0001 C CNN
	1    2740 1030
	1    0    0    -1  
$EndComp
Wire Wire Line
	2740 1030 2840 1030
Connection ~ 2740 1030
Text GLabel 4970 5180 1    50   Input ~ 0
RCAnalogThrottle
Text GLabel 5070 5180 1    50   Input ~ 0
RCAnalogSteering
Text GLabel 2840 1430 0    50   Input ~ 0
Steering
Text GLabel 2840 1330 0    50   Input ~ 0
Throttle
Text GLabel 4550 4030 2    50   Input ~ 0
Steering
Text GLabel 4550 3930 2    50   Input ~ 0
Throttle
$Comp
L Jumper:SolderJumper_3_Open JP3
U 1 1 5FB889CD
P 8790 2470
F 0 "JP3" V 8836 2537 50  0000 L CNN
F 1 "Throttle Jumper" V 8745 2537 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8790 2470 50  0001 C CNN
F 3 "~" H 8790 2470 50  0001 C CNN
	1    8790 2470
	0    -1   -1   0   
$EndComp
$Comp
L Jumper:SolderJumper_3_Open JP4
U 1 1 5FB8BA5A
P 8820 1890
F 0 "JP4" V 8866 1958 50  0000 L CNN
F 1 "Steering Jumper" V 8775 1958 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8820 1890 50  0001 C CNN
F 3 "~" H 8820 1890 50  0001 C CNN
	1    8820 1890
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8970 1890 8970 2110
Wire Wire Line
	8970 2110 9430 2110
Wire Wire Line
	8940 2470 8940 2210
Wire Wire Line
	8940 2210 9430 2210
Text GLabel 8820 1690 0    50   Input ~ 0
PWMSteering
Text GLabel 8790 2270 0    50   Input ~ 0
PWMThrottle
Text GLabel 5270 5180 1    50   Input ~ 0
RCPWMSteering
Text GLabel 5170 5180 1    50   Input ~ 0
RCPWMThrottle
Text GLabel 1350 2440 2    50   Input ~ 0
RCPWMSteering
Text GLabel 1350 2340 2    50   Input ~ 0
RCPWMThrottle
Text GLabel 2840 1730 0    50   Input ~ 0
RCAnalogThrottle
Text GLabel 2840 1830 0    50   Input ~ 0
RCAnalogSteering
NoConn ~ 2840 2430
Text GLabel 2840 2230 0    50   Input ~ 0
ActiveSW
$Comp
L Connector:Conn_01x04_Male J12
U 1 1 5FBAF7AC
P 1910 3310
F 0 "J12" H 2018 3591 50  0000 C CNN
F 1 "Power Input" H 1610 3360 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 1910 3310 50  0001 C CNN
F 3 "~" H 1910 3310 50  0001 C CNN
	1    1910 3310
	1    0    0    -1  
$EndComp
NoConn ~ 2110 3510
Text GLabel 4870 5180 1    50   Input ~ 0
PWMSteering
Text GLabel 4770 5180 1    50   Input ~ 0
PWMThrottle
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 5FC7038F
P 4400 3930
F 0 "JP1" H 5010 3930 50  0000 C CNN
F 1 "LTC Throttle Jumper" H 4740 4030 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4400 3930 50  0001 C CNN
F 3 "~" H 4400 3930 50  0001 C CNN
	1    4400 3930
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP2
U 1 1 5FC719D5
P 4400 4030
F 0 "JP2" H 5000 4040 50  0000 C CNN
F 1 "LTC Steering Jumper" H 4750 3920 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4400 4030 50  0001 C CNN
F 3 "~" H 4400 4030 50  0001 C CNN
	1    4400 4030
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP2
U 1 1 5FCBA64C
P 2440 3310
F 0 "TP2" H 2400 3510 50  0000 L CNN
F 1 "5v" H 2500 3430 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_1.5x1.5mm" H 2640 3310 50  0001 C CNN
F 3 "~" H 2640 3310 50  0001 C CNN
	1    2440 3310
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J6
U 1 1 5EE8257A
P 1460 4270
F 0 "J6" H 1590 3960 50  0000 C CNN
F 1 "Main Power" H 1560 4060 50  0000 C CNN
F 2 "Useful Modifications:TerminalBlock_bornier-2_P5.08mm" H 1460 4270 50  0001 C CNN
F 3 "~" H 1460 4270 50  0001 C CNN
	1    1460 4270
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5F5C3B2C
P 1660 4270
F 0 "#PWR08" H 1660 4020 50  0001 C CNN
F 1 "GND" V 1660 4170 50  0000 R CNN
F 2 "" H 1660 4270 50  0001 C CNN
F 3 "" H 1660 4270 50  0001 C CNN
	1    1660 4270
	0    -1   -1   0   
$EndComp
$Comp
L power:+12V #PWR022
U 1 1 5FF972E7
P 4270 5180
F 0 "#PWR022" H 4270 5030 50  0001 C CNN
F 1 "+12V" V 4250 5310 50  0000 L CNN
F 2 "" H 4270 5180 50  0001 C CNN
F 3 "" H 4270 5180 50  0001 C CNN
	1    4270 5180
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J?
U 1 1 5FF90FC6
P 6240 3180
AR Path="/5F4AD486/5FF90FC6" Ref="J?"  Part="1" 
AR Path="/5FF90FC6" Ref="J43"  Part="1" 
F 0 "J43" H 6190 3130 50  0000 C CNN
F 1 "Volume" H 6440 2980 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 6240 3180 50  0001 C CNN
F 3 "~" H 6240 3180 50  0001 C CNN
	1    6240 3180
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5FF90FBA
P 6440 3080
AR Path="/5F4AD486/5FF90FBA" Ref="#PWR?"  Part="1" 
AR Path="/5FF90FBA" Ref="#PWR030"  Part="1" 
F 0 "#PWR030" H 6440 2930 50  0001 C CNN
F 1 "+3.3V" V 6455 3208 50  0000 L CNN
F 2 "" H 6440 3080 50  0001 C CNN
F 3 "" H 6440 3080 50  0001 C CNN
	1    6440 3080
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_02x11_Odd_Even J45
U 1 1 5FA2F68D
P 8950 4130
F 0 "J45" H 9000 4847 50  0000 C CNN
F 1 "22Pin_FXSound" H 9000 4756 50  0000 C CNN
F 2 "Useful Modifications:FXSound_2x11_P2.54mm_Short" H 8950 4130 50  0001 C CNN
F 3 "~" H 8950 4130 50  0001 C CNN
	1    8950 4130
	1    0    0    -1  
$EndComp
NoConn ~ 9250 4230
NoConn ~ 9250 4130
NoConn ~ 9250 4030
Text GLabel 8750 3930 0    50   Input ~ 0
Sound2
Text GLabel 8750 3830 0    50   Input ~ 0
Sound1
Text GLabel 9250 4430 2    50   Input ~ 0
RightIN
Text GLabel 9250 4530 2    50   Input ~ 0
LeftIN
$Comp
L power:GNDA #PWR034
U 1 1 5F571777
P 9250 4630
F 0 "#PWR034" H 9250 4380 50  0001 C CNN
F 1 "GNDA" V 9250 4380 50  0000 C CNN
F 2 "" H 9250 4630 50  0001 C CNN
F 3 "" H 9250 4630 50  0001 C CNN
	1    9250 4630
	0    -1   -1   0   
$EndComp
NoConn ~ 9250 3930
NoConn ~ 9250 4330
Text Notes 9000 4630 0    50   ~ 0
R\nL\nG
Text Notes 9000 4230 0    50   ~ 0
T\nR\nU
NoConn ~ 9250 3830
NoConn ~ 8750 4030
NoConn ~ 8750 3730
NoConn ~ 8750 4630
NoConn ~ 8750 4530
NoConn ~ 8750 4430
NoConn ~ 8750 3630
NoConn ~ 8750 4130
NoConn ~ 8750 4230
NoConn ~ 8750 4330
$Comp
L power:GND #PWR033
U 1 1 5D6DD9CD
P 9250 3730
F 0 "#PWR033" H 9250 3480 50  0001 C CNN
F 1 "GND" V 9250 3580 50  0000 R CNN
F 2 "" H 9250 3730 50  0001 C CNN
F 3 "" H 9250 3730 50  0001 C CNN
	1    9250 3730
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR032
U 1 1 5D6B4B0C
P 9250 3630
F 0 "#PWR032" H 9250 3480 50  0001 C CNN
F 1 "+5V" V 9250 3780 50  0000 L CNN
F 2 "" H 9250 3630 50  0001 C CNN
F 3 "" H 9250 3630 50  0001 C CNN
	1    9250 3630
	0    1    1    0   
$EndComp
Text Notes 6670 3980 0    50   ~ 0
+\n-
$Comp
L Connector:Screw_Terminal_01x02 J44
U 1 1 5FFC4ADF
P 6620 3880
AR Path="/5FFC4ADF" Ref="J44"  Part="1" 
AR Path="/5F4AD486/5FFC4ADF" Ref="J?"  Part="1" 
F 0 "J44" H 6820 3800 50  0000 C CNN
F 1 "Left Speaker" H 7000 3900 50  0000 C CNN
F 2 "Useful Modifications:TerminalBlock_bornier-2_P5.08mm" H 6620 3880 50  0001 C CNN
F 3 "~" H 6620 3880 50  0001 C CNN
	1    6620 3880
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5FF3D070
P 2730 3960
F 0 "#PWR016" H 2730 3710 50  0001 C CNN
F 1 "GND" V 2730 3710 50  0000 C CNN
F 2 "" H 2730 3960 50  0001 C CNN
F 3 "" H 2730 3960 50  0001 C CNN
	1    2730 3960
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR031
U 1 1 5FF3DECD
P 6440 3280
F 0 "#PWR031" H 6440 3030 50  0001 C CNN
F 1 "GND" V 6440 3030 50  0000 C CNN
F 2 "" H 6440 3280 50  0001 C CNN
F 3 "" H 6440 3280 50  0001 C CNN
	1    6440 3280
	0    -1   -1   0   
$EndComp
Connection ~ 2110 3210
$Comp
L Device:CP C?
U 1 1 5FF9AA6A
P 2580 3960
AR Path="/5F4AD486/5FF9AA6A" Ref="C?"  Part="1" 
AR Path="/5FF9AA6A" Ref="C1"  Part="1" 
F 0 "C1" V 2730 3910 50  0000 L CNN
F 1 "470µF" V 2720 3610 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 2618 3810 50  0001 C CNN
F 3 "http://www.rubycon.co.jp/en/catalog/e_pdfs/aluminum/e_zlh.pdf" H 2580 3960 50  0001 C CNN
F 4 "1189-1859-ND" H 2580 3960 50  0001 C CNN "DigiKey ID"
	1    2580 3960
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2110 3310 2440 3310
Connection ~ 2440 3310
$Comp
L power:+3.3V #PWR025
U 1 1 5FB78432
P 4470 5180
F 0 "#PWR025" H 4470 5030 50  0001 C CNN
F 1 "+3.3V" V 4470 5430 50  0000 C CNN
F 2 "" H 4470 5180 50  0001 C CNN
F 3 "" H 4470 5180 50  0001 C CNN
	1    4470 5180
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR021
U 1 1 5FB77027
P 4070 5180
F 0 "#PWR021" H 4070 4930 50  0001 C CNN
F 1 "GND" V 4070 5080 50  0000 R CNN
F 2 "" H 4070 5180 50  0001 C CNN
F 3 "" H 4070 5180 50  0001 C CNN
	1    4070 5180
	-1   0    0    1   
$EndComp
$Comp
L power:+12V #PWR07
U 1 1 5FF2D516
P 1660 4170
F 0 "#PWR07" H 1660 4020 50  0001 C CNN
F 1 "+12V" V 1640 4300 50  0000 L CNN
F 2 "" H 1660 4170 50  0001 C CNN
F 3 "" H 1660 4170 50  0001 C CNN
	1    1660 4170
	0    1    1    0   
$EndComp
Text GLabel 2430 3960 0    50   Input ~ 0
ECap
Text GLabel 6440 3180 2    50   Input ~ 0
VOL
Text GLabel 4250 3930 0    50   Input ~ 0
LTCThrottle
Text GLabel 4250 4030 0    50   Input ~ 0
LTCSteering
Text GLabel 4570 5180 1    50   Input ~ 0
LTCThrottle
Text GLabel 4670 5180 1    50   Input ~ 0
LTCSteering
Text GLabel 4170 5180 1    50   Input ~ 0
ECap
Text GLabel 3970 5180 1    50   Input ~ 0
VOL
Text GLabel 3370 5180 1    50   Input ~ 0
Sound2
Text GLabel 3270 5180 1    50   Input ~ 0
Sound1
Text GLabel 3470 5180 1    50   Input ~ 0
RightIN
Text GLabel 3570 5180 1    50   Input ~ 0
LeftIN
$Comp
L power:GNDA #PWR019
U 1 1 5FF37123
P 3670 5180
F 0 "#PWR019" H 3670 4930 50  0001 C CNN
F 1 "GNDA" V 3670 4930 50  0000 C CNN
F 2 "" H 3670 5180 50  0001 C CNN
F 3 "" H 3670 5180 50  0001 C CNN
	1    3670 5180
	-1   0    0    1   
$EndComp
Text GLabel 6420 3980 0    50   Input ~ 0
Speaker-
Text GLabel 6420 3880 0    50   Input ~ 0
Speaker+
Text GLabel 3770 5180 1    50   Input ~ 0
Speaker-
Text GLabel 3870 5180 1    50   Input ~ 0
Speaker+
$Comp
L Connector:Conn_01x01_Male J18
U 1 1 5FF43453
P 3270 5380
F 0 "J18" H 2660 5380 50  0000 R CNN
F 1 "Sound1 Pogo" H 3200 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3270 5380 50  0001 C CNN
F 3 "~" H 3270 5380 50  0001 C CNN
	1    3270 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J19
U 1 1 5FF48388
P 3370 5380
F 0 "J19" H 2770 5380 50  0000 R CNN
F 1 "Sound2 Pogo" H 3300 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3370 5380 50  0001 C CNN
F 3 "~" H 3370 5380 50  0001 C CNN
	1    3370 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J20
U 1 1 5FF4865C
P 3470 5380
F 0 "J20" H 2870 5380 50  0000 R CNN
F 1 "RightIN Pogo" H 3400 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3470 5380 50  0001 C CNN
F 3 "~" H 3470 5380 50  0001 C CNN
	1    3470 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J21
U 1 1 5FF48881
P 3570 5380
F 0 "J21" H 3020 5390 50  0000 R CNN
F 1 "LeftIN Pogo" H 3500 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3570 5380 50  0001 C CNN
F 3 "~" H 3570 5380 50  0001 C CNN
	1    3570 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J22
U 1 1 5FF48AFF
P 3670 5380
F 0 "J22" H 3130 5390 50  0000 R CNN
F 1 "GNDA Pogo" H 3600 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3670 5380 50  0001 C CNN
F 3 "~" H 3670 5380 50  0001 C CNN
	1    3670 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J23
U 1 1 5FF48C85
P 3770 5380
F 0 "J23" H 3090 5390 50  0000 R CNN
F 1 "Speaker- Pogo" H 3700 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3770 5380 50  0001 C CNN
F 3 "~" H 3770 5380 50  0001 C CNN
	1    3770 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J24
U 1 1 5FF49028
P 3870 5380
F 0 "J24" H 3200 5390 50  0000 R CNN
F 1 "Speaker+ Pogo" H 3800 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3870 5380 50  0001 C CNN
F 3 "~" H 3870 5380 50  0001 C CNN
	1    3870 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J25
U 1 1 5FF491D5
P 3970 5380
F 0 "J25" H 3480 5390 50  0000 R CNN
F 1 "Vol Pogo" H 3900 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3970 5380 50  0001 C CNN
F 3 "~" H 3970 5380 50  0001 C CNN
	1    3970 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J26
U 1 1 5FF493E4
P 4070 5380
F 0 "J26" H 3570 5390 50  0000 R CNN
F 1 "Gnd Pogo" H 4000 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4070 5380 50  0001 C CNN
F 3 "~" H 4070 5380 50  0001 C CNN
	1    4070 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J28
U 1 1 5FF495BD
P 4170 5380
F 0 "J28" H 3630 5380 50  0000 R CNN
F 1 "ECap Pogo" H 4100 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4170 5380 50  0001 C CNN
F 3 "~" H 4170 5380 50  0001 C CNN
	1    4170 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J29
U 1 1 5FF49731
P 4270 5380
F 0 "J29" H 3760 5380 50  0000 R CNN
F 1 "12v Pogo" H 4200 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4270 5380 50  0001 C CNN
F 3 "~" H 4270 5380 50  0001 C CNN
	1    4270 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J30
U 1 1 5FF49BF9
P 4470 5380
F 0 "J30" H 3930 5390 50  0000 R CNN
F 1 "3.3v Pogo" H 4400 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4470 5380 50  0001 C CNN
F 3 "~" H 4470 5380 50  0001 C CNN
	1    4470 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J31
U 1 1 5FF49E2C
P 4570 5380
F 0 "J31" H 3840 5390 50  0000 R CNN
F 1 "LTCThrottle Pogo" H 4500 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4570 5380 50  0001 C CNN
F 3 "~" H 4570 5380 50  0001 C CNN
	1    4570 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J32
U 1 1 5FF4A0B0
P 4670 5380
F 0 "J32" H 3900 5390 50  0000 R CNN
F 1 "LTCSteering Pogo" H 4600 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4670 5380 50  0001 C CNN
F 3 "~" H 4670 5380 50  0001 C CNN
	1    4670 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J33
U 1 1 5FF4A332
P 4770 5380
F 0 "J33" H 3980 5400 50  0000 R CNN
F 1 "PWMThrottle Pogo" H 4700 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4770 5380 50  0001 C CNN
F 3 "~" H 4770 5380 50  0001 C CNN
	1    4770 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J38
U 1 1 5FF4A59A
P 4870 5380
F 0 "J38" H 4060 5390 50  0000 R CNN
F 1 "PWMSteering Pogo" H 4800 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4870 5380 50  0001 C CNN
F 3 "~" H 4870 5380 50  0001 C CNN
	1    4870 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J39
U 1 1 5FF4A92E
P 4970 5380
F 0 "J39" H 3960 5380 50  0000 R CNN
F 1 "RCAnnalogThrottle Pogo" H 4900 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4970 5380 50  0001 C CNN
F 3 "~" H 4970 5380 50  0001 C CNN
	1    4970 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J40
U 1 1 5FF4AC9E
P 5070 5380
F 0 "J40" H 4090 5380 50  0000 R CNN
F 1 "RCAnalogSteering Pogo" H 5000 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 5070 5380 50  0001 C CNN
F 3 "~" H 5070 5380 50  0001 C CNN
	1    5070 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J41
U 1 1 5FF4AEF6
P 5170 5380
F 0 "J41" H 4280 5390 50  0000 R CNN
F 1 "RCPWMThrottle Pogo" H 5100 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 5170 5380 50  0001 C CNN
F 3 "~" H 5170 5380 50  0001 C CNN
	1    5170 5380
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J42
U 1 1 5FF4B1D0
P 5270 5380
F 0 "J42" H 4350 5390 50  0000 R CNN
F 1 "RCPWMSteering Pogo" H 5200 5390 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 5270 5380 50  0001 C CNN
F 3 "~" H 5270 5380 50  0001 C CNN
	1    5270 5380
	0    -1   -1   0   
$EndComp
$Comp
L power:+12V #PWR013
U 1 1 5FF5FE3B
P 2270 5190
F 0 "#PWR013" H 2270 5040 50  0001 C CNN
F 1 "+12V" V 2250 5320 50  0000 L CNN
F 2 "" H 2270 5190 50  0001 C CNN
F 3 "" H 2270 5190 50  0001 C CNN
	1    2270 5190
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5FF5FE41
P 2070 5190
F 0 "#PWR010" H 2070 4940 50  0001 C CNN
F 1 "GND" V 2070 5090 50  0000 R CNN
F 2 "" H 2070 5190 50  0001 C CNN
F 3 "" H 2070 5190 50  0001 C CNN
	1    2070 5190
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR014
U 1 1 5FF5FE47
P 2370 5190
F 0 "#PWR014" H 2370 5040 50  0001 C CNN
F 1 "+5V" V 2370 5290 50  0000 L CNN
F 2 "" H 2370 5190 50  0001 C CNN
F 3 "" H 2370 5190 50  0001 C CNN
	1    2370 5190
	1    0    0    -1  
$EndComp
Text GLabel 2170 5190 1    50   Input ~ 0
ECap
Text GLabel 1970 5190 1    50   Input ~ 0
VOL
Text GLabel 1370 5190 1    50   Input ~ 0
Sound2
Text GLabel 1270 5190 1    50   Input ~ 0
Sound1
Text GLabel 1470 5190 1    50   Input ~ 0
RightIN
Text GLabel 1570 5190 1    50   Input ~ 0
LeftIN
$Comp
L power:GNDA #PWR09
U 1 1 5FF5FE53
P 1670 5190
F 0 "#PWR09" H 1670 4940 50  0001 C CNN
F 1 "GNDA" V 1670 4940 50  0000 C CNN
F 2 "" H 1670 5190 50  0001 C CNN
F 3 "" H 1670 5190 50  0001 C CNN
	1    1670 5190
	-1   0    0    1   
$EndComp
Text GLabel 1770 5190 1    50   Input ~ 0
Speaker-
Text GLabel 1870 5190 1    50   Input ~ 0
Speaker+
$Comp
L Connector:Conn_01x01_Male J5
U 1 1 5FF5FE61
P 1370 5390
F 0 "J5" H 490 5400 50  0000 R CNN
F 1 "Simple Sound2 Pogo" H 1300 5400 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1370 5390 50  0001 C CNN
F 3 "~" H 1370 5390 50  0001 C CNN
	1    1370 5390
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J7
U 1 1 5FF5FE67
P 1470 5390
F 0 "J7" H 590 5400 50  0000 R CNN
F 1 "Simple RightIN Pogo" H 1400 5400 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1470 5390 50  0001 C CNN
F 3 "~" H 1470 5390 50  0001 C CNN
	1    1470 5390
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J8
U 1 1 5FF5FE6D
P 1570 5390
F 0 "J8" H 730 5400 50  0000 R CNN
F 1 "Simple LeftIN Pogo" H 1500 5400 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1570 5390 50  0001 C CNN
F 3 "~" H 1570 5390 50  0001 C CNN
	1    1570 5390
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J10
U 1 1 5FF5FE79
P 1770 5390
F 0 "J10" H 800 5400 50  0000 R CNN
F 1 "Simple Speaker- Pogo" H 1700 5400 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1770 5390 50  0001 C CNN
F 3 "~" H 1770 5390 50  0001 C CNN
	1    1770 5390
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J11
U 1 1 5FF5FE7F
P 1870 5390
F 0 "J11" H 900 5390 50  0000 R CNN
F 1 "Simple Speaker+ Pogo" H 1800 5400 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1870 5390 50  0001 C CNN
F 3 "~" H 1870 5390 50  0001 C CNN
	1    1870 5390
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J13
U 1 1 5FF5FE85
P 1970 5390
F 0 "J13" H 1230 5400 50  0000 R CNN
F 1 "Simple Vol Pogo" H 1900 5400 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1970 5390 50  0001 C CNN
F 3 "~" H 1970 5390 50  0001 C CNN
	1    1970 5390
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J14
U 1 1 5FF5FE8B
P 2070 5390
F 0 "J14" H 1300 5400 50  0000 R CNN
F 1 "Simple Gnd Pogo" H 2000 5400 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 2070 5390 50  0001 C CNN
F 3 "~" H 2070 5390 50  0001 C CNN
	1    2070 5390
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J15
U 1 1 5FF5FE91
P 2170 5390
F 0 "J15" H 1370 5390 50  0000 R CNN
F 1 "Simple ECap Pogo" H 2100 5400 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 2170 5390 50  0001 C CNN
F 3 "~" H 2170 5390 50  0001 C CNN
	1    2170 5390
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J16
U 1 1 5FF5FE97
P 2270 5390
F 0 "J16" H 1520 5400 50  0000 R CNN
F 1 "Simple 12v Pogo" H 2200 5400 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 2270 5390 50  0001 C CNN
F 3 "~" H 2270 5390 50  0001 C CNN
	1    2270 5390
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J17
U 1 1 5FF5FE9D
P 2370 5390
F 0 "J17" H 1660 5390 50  0000 R CNN
F 1 "Simple 5v Pogo" H 2300 5400 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 2370 5390 50  0001 C CNN
F 3 "~" H 2370 5390 50  0001 C CNN
	1    2370 5390
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J4
U 1 1 5FF5FE5B
P 1270 5390
F 0 "J4" H 380 5400 50  0000 R CNN
F 1 "Simple Sound1 Pogo" H 1200 5400 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1270 5390 50  0001 C CNN
F 3 "~" H 1270 5390 50  0001 C CNN
	1    1270 5390
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J9
U 1 1 5FF5FE73
P 1670 5390
F 0 "J9" H 870 5400 50  0000 R CNN
F 1 "Simple GNDA Pogo" H 1600 5400 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1670 5390 50  0001 C CNN
F 3 "~" H 1670 5390 50  0001 C CNN
	1    1670 5390
	0    -1   -1   0   
$EndComp
$Comp
L Connector:8P8C J48
U 1 1 6009BD56
P 7780 5030
F 0 "J48" H 7730 5380 50  0000 L CNN
F 1 "Simple RJ45" H 7520 4580 50  0000 L CNN
F 2 "Useful Modifications:RJ45_x08_Tab_Up" V 7780 5055 50  0001 C CNN
F 3 "~" V 7780 5055 50  0001 C CNN
	1    7780 5030
	-1   0    0    1   
$EndComp
Text GLabel 7380 5230 0    50   Input ~ 0
Sound2
Text GLabel 7380 5030 0    50   Input ~ 0
Sound1
$Comp
L Connector:Conn_01x02_Male J47
U 1 1 600A05EE
P 7180 5330
F 0 "J47" H 7100 5260 50  0000 C CNN
F 1 "Other Button" H 7110 5140 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7180 5330 50  0001 C CNN
F 3 "~" H 7180 5330 50  0001 C CNN
	1    7180 5330
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 600A2450
P 7380 4930
F 0 "#PWR0101" H 7380 4680 50  0001 C CNN
F 1 "GND" V 7380 4680 50  0000 C CNN
F 2 "" H 7380 4930 50  0001 C CNN
F 3 "" H 7380 4930 50  0001 C CNN
	1    7380 4930
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 600A2861
P 7380 5130
F 0 "#PWR0102" H 7380 4880 50  0001 C CNN
F 1 "GND" V 7380 4880 50  0000 C CNN
F 2 "" H 7380 5130 50  0001 C CNN
F 3 "" H 7380 5130 50  0001 C CNN
	1    7380 5130
	0    1    1    0   
$EndComp
NoConn ~ 7380 4730
NoConn ~ 7380 4830
$Comp
L Switch:SW_SPST SW1
U 1 1 600CF1BB
P 6500 4480
F 0 "SW1" H 6500 4715 50  0000 C CNN
F 1 "SW_SPST" H 6500 4624 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 6500 4480 50  0001 C CNN
F 3 "~" H 6500 4480 50  0001 C CNN
	1    6500 4480
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW2
U 1 1 600CF778
P 6430 4860
F 0 "SW2" H 6430 5095 50  0000 C CNN
F 1 "SW_SPST" H 6430 5004 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 6430 4860 50  0001 C CNN
F 3 "~" H 6430 4860 50  0001 C CNN
	1    6430 4860
	1    0    0    -1  
$EndComp
Text GLabel 6300 4480 0    50   Input ~ 0
Sound1
Text GLabel 6230 4860 0    50   Input ~ 0
Sound2
$Comp
L power:GND #PWR039
U 1 1 600D08C2
P 6700 4480
F 0 "#PWR039" H 6700 4230 50  0001 C CNN
F 1 "GND" V 6700 4230 50  0000 C CNN
F 2 "" H 6700 4480 50  0001 C CNN
F 3 "" H 6700 4480 50  0001 C CNN
	1    6700 4480
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR038
U 1 1 600D0D8F
P 6630 4860
F 0 "#PWR038" H 6630 4610 50  0001 C CNN
F 1 "GND" V 6630 4610 50  0000 C CNN
F 2 "" H 6630 4860 50  0001 C CNN
F 3 "" H 6630 4860 50  0001 C CNN
	1    6630 4860
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
