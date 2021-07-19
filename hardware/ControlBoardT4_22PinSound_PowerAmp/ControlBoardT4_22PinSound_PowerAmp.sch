EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
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
P 4380 4700
F 0 "J1" H 4580 4950 50  0000 R CNN
F 1 "RC" H 4430 4950 50  0000 R CNN
F 2 "Useful Modifications:JST_XH_B4B-XH-A_1x04_P2.54mm_Vertical" H 4380 4700 50  0001 C CNN
F 3 "~" H 4380 4700 50  0001 C CNN
	1    4380 4700
	1    0    0    -1  
$EndComp
Text Notes 7129 4510 3    59   ~ 0
3 Y X 2 1 5 G
Text Notes 4339 4550 3    59   ~ 0
S S G 3\n
$Comp
L power:+5V #PWR026
U 1 1 5D691EA1
P 6290 2570
F 0 "#PWR026" H 6290 2420 50  0001 C CNN
F 1 "+5V" V 6290 2720 50  0000 L CNN
F 2 "" H 6290 2570 50  0001 C CNN
F 3 "" H 6290 2570 50  0001 C CNN
	1    6290 2570
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR033
U 1 1 5D6B4B0C
P 9490 2830
F 0 "#PWR033" H 9490 2680 50  0001 C CNN
F 1 "+5V" V 9490 2980 50  0000 L CNN
F 2 "" H 9490 2830 50  0001 C CNN
F 3 "" H 9490 2830 50  0001 C CNN
	1    9490 2830
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR029
U 1 1 5D6B5159
P 6920 4660
F 0 "#PWR029" H 6920 4510 50  0001 C CNN
F 1 "+5V" V 6920 4810 50  0000 L CNN
F 2 "" H 6920 4660 50  0001 C CNN
F 3 "" H 6920 4660 50  0001 C CNN
	1    6920 4660
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR014
U 1 1 5D6C064F
P 4580 4700
F 0 "#PWR014" H 4580 4450 50  0001 C CNN
F 1 "GND" V 4580 4450 50  0000 C CNN
F 2 "" H 4580 4700 50  0001 C CNN
F 3 "" H 4580 4700 50  0001 C CNN
	1    4580 4700
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR03
U 1 1 5D6D576D
P 4580 4600
F 0 "#PWR03" H 4580 4450 50  0001 C CNN
F 1 "+3.3V" V 4580 4850 50  0000 C CNN
F 2 "" H 4580 4600 50  0001 C CNN
F 3 "" H 4580 4600 50  0001 C CNN
	1    4580 4600
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR030
U 1 1 5D6DC17C
P 6920 5160
F 0 "#PWR030" H 6920 5010 50  0001 C CNN
F 1 "+3.3V" V 6920 5310 50  0000 L CNN
F 2 "" H 6920 5160 50  0001 C CNN
F 3 "" H 6920 5160 50  0001 C CNN
	1    6920 5160
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR034
U 1 1 5D6DD9CD
P 9490 2930
F 0 "#PWR034" H 9490 2680 50  0001 C CNN
F 1 "GND" V 9490 2780 50  0000 R CNN
F 2 "" H 9490 2930 50  0001 C CNN
F 3 "" H 9490 2930 50  0001 C CNN
	1    9490 2930
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR028
U 1 1 5D6DE9AA
P 6920 4560
F 0 "#PWR028" H 6920 4310 50  0001 C CNN
F 1 "GND" V 6920 4410 50  0000 R CNN
F 2 "" H 6920 4560 50  0001 C CNN
F 3 "" H 6920 4560 50  0001 C CNN
	1    6920 4560
	0    1    1    0   
$EndComp
NoConn ~ 8990 3530
NoConn ~ 8990 3430
NoConn ~ 8990 3330
NoConn ~ 8990 2830
NoConn ~ 8990 3630
NoConn ~ 8990 3730
NoConn ~ 8990 3830
NoConn ~ 8990 2930
NoConn ~ 8990 3230
NoConn ~ 9490 3030
Text Notes 9240 3430 0    50   ~ 0
T\nR\nU
Text Notes 9240 3830 0    50   ~ 0
R\nL\nG
$Comp
L Connector:8P8C J7
U 1 1 5D627B3B
P 7320 4860
F 0 "J7" H 7270 5210 50  0000 L CNN
F 1 "8P8C" H 7170 4660 50  0000 L CNN
F 2 "Useful Modifications:RJ45_x08_Tab_Up" V 7320 4885 50  0001 C CNN
F 3 "~" V 7320 4885 50  0001 C CNN
	1    7320 4860
	-1   0    0    1   
$EndComp
NoConn ~ 9490 3530
NoConn ~ 9490 3130
$Comp
L power:+12V #PWR0101
U 1 1 5EE21F5B
P 4840 6050
F 0 "#PWR0101" H 4840 5900 50  0001 C CNN
F 1 "+12V" V 4855 6178 50  0000 L CNN
F 2 "" H 4840 6050 50  0001 C CNN
F 3 "" H 4840 6050 50  0001 C CNN
	1    4840 6050
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5EE242AC
P 4840 5850
F 0 "#PWR0103" H 4840 5600 50  0001 C CNN
F 1 "GND" V 4840 5730 50  0000 R CNN
F 2 "" H 4840 5850 50  0001 C CNN
F 3 "" H 4840 5850 50  0001 C CNN
	1    4840 5850
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 5EE28E61
P 5170 5950
F 0 "#PWR0104" H 5170 5800 50  0001 C CNN
F 1 "+5V" V 5170 6050 50  0000 L CNN
F 2 "" H 5170 5950 50  0001 C CNN
F 3 "" H 5170 5950 50  0001 C CNN
	1    5170 5950
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP1
U 1 1 5EE709D2
P 4840 5850
F 0 "TP1" H 4790 6100 50  0000 L CNN
F 1 "Gnd" H 4650 5970 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_1.5x1.5mm" H 5040 5850 50  0001 C CNN
F 3 "~" H 5040 5850 50  0001 C CNN
	1    4840 5850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J13
U 1 1 5EE8257A
P 3590 5650
F 0 "J13" H 3508 5325 50  0000 C CNN
F 1 "Main Power" H 3508 5416 50  0000 C CNN
F 2 "Useful Modifications:TerminalBlock_bornier-2_P5.08mm" H 3590 5650 50  0001 C CNN
F 3 "~" H 3590 5650 50  0001 C CNN
	1    3590 5650
	-1   0    0    1   
$EndComp
$Comp
L power:+12V #PWR024
U 1 1 5EE8644F
P 3790 5550
F 0 "#PWR024" H 3790 5400 50  0001 C CNN
F 1 "+12V" V 3805 5678 50  0000 L CNN
F 2 "" H 3790 5550 50  0001 C CNN
F 3 "" H 3790 5550 50  0001 C CNN
	1    3790 5550
	0    1    1    0   
$EndComp
$Sheet
S 700  700  1250 950 
U 5F4AD486
F0 "MAX9744" 50
F1 "MAX9744.sch" 50
$EndSheet
$Comp
L power:GNDA #PWR019
U 1 1 5F571777
P 9490 3830
F 0 "#PWR019" H 9490 3580 50  0001 C CNN
F 1 "GNDA" V 9490 3580 50  0000 C CNN
F 2 "" H 9490 3830 50  0001 C CNN
F 3 "" H 9490 3830 50  0001 C CNN
	1    9490 3830
	0    -1   -1   0   
$EndComp
Text GLabel 9490 3730 2    50   Input ~ 0
LeftIN
Text GLabel 9490 3630 2    50   Input ~ 0
RightIN
$Comp
L power:GND #PWR0107
U 1 1 5F5C3B2C
P 3790 5650
F 0 "#PWR0107" H 3790 5400 50  0001 C CNN
F 1 "GND" V 3790 5550 50  0000 R CNN
F 2 "" H 3790 5650 50  0001 C CNN
F 3 "" H 3790 5650 50  0001 C CNN
	1    3790 5650
	0    -1   -1   0   
$EndComp
Text GLabel 8990 3030 0    50   Input ~ 0
Sound1
Text GLabel 8990 3130 0    50   Input ~ 0
Sound2
Text GLabel 6920 4760 0    50   Input ~ 0
Sound1
Text GLabel 6920 4860 0    50   Input ~ 0
Sound2
Text GLabel 6920 5060 0    50   Input ~ 0
Throttle
Text GLabel 6920 4960 0    50   Input ~ 0
Steering
Text GLabel 6290 3670 2    50   Input ~ 0
LinAct_Position
NoConn ~ 9490 3230
NoConn ~ 9490 3330
NoConn ~ 9490 3430
Text Notes 9840 3780 0    50   ~ 0
Connects to Amp\non other sheet.
$Comp
L power:GND #PWR02
U 1 1 5FA43531
P 2180 3470
F 0 "#PWR02" H 2180 3220 50  0001 C CNN
F 1 "GND" V 2180 3270 50  0000 C CNN
F 2 "" H 2180 3470 50  0001 C CNN
F 3 "" H 2180 3470 50  0001 C CNN
	1    2180 3470
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR01
U 1 1 5FA43537
P 2180 3270
F 0 "#PWR01" H 2180 3120 50  0001 C CNN
F 1 "+3.3V" V 2180 3470 50  0000 C CNN
F 2 "" H 2180 3270 50  0001 C CNN
F 3 "" H 2180 3270 50  0001 C CNN
	1    2180 3270
	0    1    1    0   
$EndComp
Text Notes 1939 3220 3    59   ~ 0
G S 3
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 5FA4353E
P 1980 3370
F 0 "J3" H 2280 3620 50  0000 R CNN
F 1 "SpeedCtrl" H 2130 3620 50  0000 R CNN
F 2 "Useful Modifications:JST_XH_B3B-XH-A_1x03_P2.54mm_Vertical" H 1980 3370 50  0001 C CNN
F 3 "~" H 1980 3370 50  0001 C CNN
	1    1980 3370
	1    0    0    -1  
$EndComp
Text GLabel 2180 3370 2    50   Input ~ 0
SpeedCtrl
Text GLabel 6290 3770 2    50   Input ~ 0
SpeedCtrl
$Comp
L power:GND #PWR010
U 1 1 5FA56C07
P 7890 3630
F 0 "#PWR010" H 7890 3380 50  0001 C CNN
F 1 "GND" V 7890 3430 50  0000 C CNN
F 2 "" H 7890 3630 50  0001 C CNN
F 3 "" H 7890 3630 50  0001 C CNN
	1    7890 3630
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x03_Female J11
U 1 1 5FA5BE7E
P 7690 3530
F 0 "J11" H 7790 3530 50  0000 C CNN
F 1 "LinAct_M3" H 7880 3420 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7690 3530 50  0001 C CNN
F 3 "~" H 7690 3530 50  0001 C CNN
	1    7690 3530
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Female J8
U 1 1 5FA5B276
P 7690 3130
F 0 "J8" H 7790 3130 50  0000 C CNN
F 1 "Right_M2" H 7870 3030 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7690 3130 50  0001 C CNN
F 3 "~" H 7690 3130 50  0001 C CNN
	1    7690 3130
	-1   0    0    1   
$EndComp
Text GLabel 7890 3430 2    50   Input ~ 0
LinAct_PWM
Text GLabel 7890 3530 2    50   Input ~ 0
LinAct_DIR
$Comp
L Connector:Conn_01x03_Female J6
U 1 1 5FA534CD
P 7690 2680
F 0 "J6" H 7718 2706 50  0000 L CNN
F 1 "Left_M1" H 7690 2580 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7690 2680 50  0001 C CNN
F 3 "~" H 7690 2680 50  0001 C CNN
	1    7690 2680
	-1   0    0    1   
$EndComp
Text GLabel 7890 3030 2    50   Input ~ 0
Right_PWM
Text GLabel 7890 3130 2    50   Input ~ 0
Right_DIR
Text GLabel 7890 2580 2    50   Input ~ 0
Left_PWM
Text GLabel 7890 2680 2    50   Input ~ 0
Left_DIR
Text GLabel 2080 2820 2    50   Input ~ 0
LinAct_Position
$Comp
L Connector:Conn_01x03_Male J2
U 1 1 5D5BCD6A
P 1880 2720
F 0 "J2" H 2180 2970 50  0000 R CNN
F 1 "LinAct" H 2030 2970 50  0000 R CNN
F 2 "Useful Modifications:JST_XH_B3B-XH-A_1x03_P2.54mm_Vertical" H 1880 2720 50  0001 C CNN
F 3 "~" H 1880 2720 50  0001 C CNN
	1    1880 2720
	1    0    0    -1  
$EndComp
Text Notes 1839 2570 3    59   ~ 0
S G 3
$Comp
L power:+3.3V #PWR04
U 1 1 5D6D67AA
P 2080 2620
F 0 "#PWR04" H 2080 2470 50  0001 C CNN
F 1 "+3.3V" V 2080 2820 50  0000 C CNN
F 2 "" H 2080 2620 50  0001 C CNN
F 3 "" H 2080 2620 50  0001 C CNN
	1    2080 2620
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5D6CA869
P 2080 2720
F 0 "#PWR015" H 2080 2470 50  0001 C CNN
F 1 "GND" V 2080 2520 50  0000 C CNN
F 2 "" H 2080 2720 50  0001 C CNN
F 3 "" H 2080 2720 50  0001 C CNN
	1    2080 2720
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5D6BF649
P 7890 3230
F 0 "#PWR013" H 7890 2980 50  0001 C CNN
F 1 "GND" V 7890 3030 50  0000 C CNN
F 2 "" H 7890 3230 50  0001 C CNN
F 3 "" H 7890 3230 50  0001 C CNN
	1    7890 3230
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5D6BCEFD
P 7890 2780
F 0 "#PWR012" H 7890 2530 50  0001 C CNN
F 1 "GND" V 7890 2580 50  0000 C CNN
F 2 "" H 7890 2780 50  0001 C CNN
F 3 "" H 7890 2780 50  0001 C CNN
	1    7890 2780
	0    -1   -1   0   
$EndComp
Text GLabel 3840 2870 0    50   Input ~ 0
Left_PWM
Text GLabel 3840 2970 0    50   Input ~ 0
Left_DIR
Text GLabel 3840 3070 0    50   Input ~ 0
Right_PWM
Text GLabel 3840 3170 0    50   Input ~ 0
Right_DIR
Text GLabel 3840 3270 0    50   Input ~ 0
LinAct_PWM
Text GLabel 3840 3370 0    50   Input ~ 0
LinAct_DIR
$Comp
L power:GND #PWR07
U 1 1 5FA68CC8
P 6290 2670
F 0 "#PWR07" H 6290 2420 50  0001 C CNN
F 1 "GND" V 6290 2470 50  0000 C CNN
F 2 "" H 6290 2670 50  0001 C CNN
F 3 "" H 6290 2670 50  0001 C CNN
	1    6290 2670
	0    -1   -1   0   
$EndComp
NoConn ~ 3840 2770
NoConn ~ 3840 3870
NoConn ~ 3840 2670
$Comp
L Connector:Conn_01x04_Male J5
U 1 1 5FA762AC
P 3290 4800
F 0 "J5" H 3490 5050 50  0000 R CNN
F 1 "I2C" H 3340 5050 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 3290 4800 50  0001 C CNN
F 3 "~" H 3290 4800 50  0001 C CNN
	1    3290 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5FA762B2
P 3490 4700
F 0 "#PWR08" H 3490 4450 50  0001 C CNN
F 1 "GND" V 3490 4450 50  0000 C CNN
F 2 "" H 3490 4700 50  0001 C CNN
F 3 "" H 3490 4700 50  0001 C CNN
	1    3490 4700
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR09
U 1 1 5FA762B8
P 3490 4800
F 0 "#PWR09" H 3490 4650 50  0001 C CNN
F 1 "+3.3V" V 3490 5050 50  0000 C CNN
F 2 "" H 3490 4800 50  0001 C CNN
F 3 "" H 3490 4800 50  0001 C CNN
	1    3490 4800
	0    1    1    0   
$EndComp
Text GLabel 3490 4900 2    50   Input ~ 0
I2C_SDA
Text GLabel 3490 5000 2    50   Input ~ 0
I2C_SCL
Text GLabel 6290 3370 2    50   Input ~ 0
I2C_SDA
Text GLabel 6290 3270 2    50   Input ~ 0
I2C_SCL
Text GLabel 6920 5260 0    50   Input ~ 0
ActiveSW
$Comp
L Connector_Generic:Conn_02x11_Odd_Even J9
U 1 1 5FA2F68D
P 9190 3330
F 0 "J9" H 9240 4047 50  0000 C CNN
F 1 "22Pin_FXSound" H 9240 3956 50  0000 C CNN
F 2 "Useful Modifications:FXSound_2x11_P2.54mm_Short" H 9190 3330 50  0001 C CNN
F 3 "~" H 9190 3330 50  0001 C CNN
	1    9190 3330
	1    0    0    -1  
$EndComp
Text GLabel 6290 3470 2    50   Input ~ 0
Steering
Text GLabel 6290 3570 2    50   Input ~ 0
Throttle
Text GLabel 4580 4900 2    50   Input ~ 0
RCPWMSteering
Text GLabel 4580 4800 2    50   Input ~ 0
RCPWMThrottle
Text GLabel 3840 3670 0    50   Input ~ 0
RCPWMThrottle
Text GLabel 3840 3770 0    50   Input ~ 0
RCPWMSteering
Text GLabel 6290 2870 2    50   Input ~ 0
ActiveSW
$Comp
L Connector:Conn_01x04_Male J4
U 1 1 5FBAF7AC
P 4640 5950
F 0 "J4" H 4748 6231 50  0000 C CNN
F 1 "Power Input" H 4340 6000 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 4640 5950 50  0001 C CNN
F 3 "~" H 4640 5950 50  0001 C CNN
	1    4640 5950
	1    0    0    -1  
$EndComp
Connection ~ 4840 5850
NoConn ~ 4840 6150
$Comp
L Connector:TestPoint TP3
U 1 1 5FCBA64C
P 5170 5950
F 0 "TP3" H 5130 6150 50  0000 L CNN
F 1 "5v" H 5470 6050 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_1.5x1.5mm" H 5370 5950 50  0001 C CNN
F 3 "~" H 5370 5950 50  0001 C CNN
	1    5170 5950
	1    0    0    -1  
$EndComp
Connection ~ 5170 5950
Wire Wire Line
	4840 5950 5170 5950
$Comp
L power:GND #PWR05
U 1 1 60CEF843
P 3840 2570
F 0 "#PWR05" H 3840 2320 50  0001 C CNN
F 1 "GND" V 3840 2370 50  0000 C CNN
F 2 "" H 3840 2570 50  0001 C CNN
F 3 "" H 3840 2570 50  0001 C CNN
	1    3840 2570
	0    1    1    0   
$EndComp
NoConn ~ 6290 2970
NoConn ~ 6290 3870
$Comp
L Connector:TestPoint TP2
U 1 1 5FA61138
P 6830 2770
F 0 "TP2" H 6730 2970 50  0000 L CNN
F 1 "3.3V" H 6630 2920 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_1.5x1.5mm" H 7030 2770 50  0001 C CNN
F 3 "~" H 7030 2770 50  0001 C CNN
	1    6830 2770
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR027
U 1 1 5D6B721D
P 6830 2770
F 0 "#PWR027" H 6830 2620 50  0001 C CNN
F 1 "+3.3V" V 6830 2920 50  0000 L CNN
F 2 "" H 6830 2770 50  0001 C CNN
F 3 "" H 6830 2770 50  0001 C CNN
	1    6830 2770
	-1   0    0    1   
$EndComp
Wire Wire Line
	6830 2770 6290 2770
Connection ~ 6830 2770
$Comp
L UsefulModifications:Teensy4.0_NoMid U1
U 1 1 60C0083C
P 5040 3220
F 0 "U1" H 5065 4117 60  0000 C CNN
F 1 "Teensy4.0_NoMid" H 5065 4011 60  0000 C CNN
F 2 "Useful Modifications:Teensy40_NoMid" H 4990 2270 60  0001 C CNN
F 3 "" H 4990 2270 60  0000 C CNN
	1    5040 3220
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J12
U 1 1 60C48DE9
P 5780 4800
F 0 "J12" H 5888 5081 50  0000 C CNN
F 1 "Conn_01x04_Male" H 5888 4990 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 5780 4800 50  0001 C CNN
F 3 "~" H 5780 4800 50  0001 C CNN
	1    5780 4800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J10
U 1 1 60C49653
P 2490 4150
F 0 "J10" H 2598 4331 50  0000 C CNN
F 1 "Conn_01x02_Male" H 2598 4240 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2490 4150 50  0001 C CNN
F 3 "~" H 2490 4150 50  0001 C CNN
	1    2490 4150
	1    0    0    -1  
$EndComp
Text GLabel 2690 4150 2    50   Input ~ 0
PgSwitch
Text GLabel 3840 3570 0    50   Input ~ 0
PgSwitch
$Comp
L power:GND #PWR06
U 1 1 60C818C0
P 2690 4250
F 0 "#PWR06" H 2690 4000 50  0001 C CNN
F 1 "GND" V 2690 4050 50  0000 C CNN
F 2 "" H 2690 4250 50  0001 C CNN
F 3 "" H 2690 4250 50  0001 C CNN
	1    2690 4250
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR016
U 1 1 60C9688B
P 5980 5000
F 0 "#PWR016" H 5980 4850 50  0001 C CNN
F 1 "+5V" V 5980 5100 50  0000 L CNN
F 2 "" H 5980 5000 50  0001 C CNN
F 3 "" H 5980 5000 50  0001 C CNN
	1    5980 5000
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 60C97F9F
P 5980 4900
F 0 "#PWR011" H 5980 4650 50  0001 C CNN
F 1 "GND" V 5980 4780 50  0000 R CNN
F 2 "" H 5980 4900 50  0001 C CNN
F 3 "" H 5980 4900 50  0001 C CNN
	1    5980 4900
	0    -1   -1   0   
$EndComp
Text GLabel 5980 4800 2    50   Input ~ 0
RxA7
Text GLabel 5980 4700 2    50   Input ~ 0
TxA6
Text GLabel 6290 3070 2    50   Input ~ 0
RxA7
Text GLabel 6290 3170 2    50   Input ~ 0
TxA6
NoConn ~ 3840 3470
$EndSCHEMATC
