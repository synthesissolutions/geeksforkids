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
P 6340 4100
F 0 "J1" H 6540 4350 50  0000 R CNN
F 1 "RC" H 6390 4350 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6340 4100 50  0001 C CNN
F 3 "~" H 6340 4100 50  0001 C CNN
	1    6340 4100
	1    0    0    -1  
$EndComp
Text Notes 8759 3700 3    59   ~ 0
3 Y X 2 1 5 G
Text Notes 6299 3950 3    59   ~ 0
S S G 3\n
$Comp
L power:+5V #PWR026
U 1 1 5D691EA1
P 5800 2700
F 0 "#PWR026" H 5800 2550 50  0001 C CNN
F 1 "+5V" V 5800 2850 50  0000 L CNN
F 2 "" H 5800 2700 50  0001 C CNN
F 3 "" H 5800 2700 50  0001 C CNN
	1    5800 2700
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR029
U 1 1 5D6B5159
P 8550 3850
F 0 "#PWR029" H 8550 3700 50  0001 C CNN
F 1 "+5V" V 8550 4000 50  0000 L CNN
F 2 "" H 8550 3850 50  0001 C CNN
F 3 "" H 8550 3850 50  0001 C CNN
	1    8550 3850
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR027
U 1 1 5D6B721D
P 4600 2200
F 0 "#PWR027" H 4600 2050 50  0001 C CNN
F 1 "+3.3V" V 4600 2350 50  0000 L CNN
F 2 "" H 4600 2200 50  0001 C CNN
F 3 "" H 4600 2200 50  0001 C CNN
	1    4600 2200
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR014
U 1 1 5D6C064F
P 6540 4100
F 0 "#PWR014" H 6540 3850 50  0001 C CNN
F 1 "GND" V 6540 3850 50  0000 C CNN
F 2 "" H 6540 4100 50  0001 C CNN
F 3 "" H 6540 4100 50  0001 C CNN
	1    6540 4100
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR03
U 1 1 5D6D576D
P 6540 4000
F 0 "#PWR03" H 6540 3850 50  0001 C CNN
F 1 "+3.3V" V 6540 4250 50  0000 C CNN
F 2 "" H 6540 4000 50  0001 C CNN
F 3 "" H 6540 4000 50  0001 C CNN
	1    6540 4000
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR030
U 1 1 5D6DC17C
P 8550 4350
F 0 "#PWR030" H 8550 4200 50  0001 C CNN
F 1 "+3.3V" V 8550 4500 50  0000 L CNN
F 2 "" H 8550 4350 50  0001 C CNN
F 3 "" H 8550 4350 50  0001 C CNN
	1    8550 4350
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR028
U 1 1 5D6DE9AA
P 8550 3750
F 0 "#PWR028" H 8550 3500 50  0001 C CNN
F 1 "GND" V 8550 3600 50  0000 R CNN
F 2 "" H 8550 3750 50  0001 C CNN
F 3 "" H 8550 3750 50  0001 C CNN
	1    8550 3750
	0    1    1    0   
$EndComp
$Comp
L Connector:8P8C J7
U 1 1 5D627B3B
P 8950 4050
F 0 "J7" H 8900 4400 50  0000 L CNN
F 1 "8P8C" H 8800 3850 50  0000 L CNN
F 2 "Useful Modifications:RJ45_x08_Tab_Up" V 8950 4075 50  0001 C CNN
F 3 "~" V 8950 4075 50  0001 C CNN
	1    8950 4050
	-1   0    0    1   
$EndComp
$Comp
L power:+12V #PWR0101
U 1 1 5EE21F5B
P 6800 5450
F 0 "#PWR0101" H 6800 5300 50  0001 C CNN
F 1 "+12V" V 6815 5578 50  0000 L CNN
F 2 "" H 6800 5450 50  0001 C CNN
F 3 "" H 6800 5450 50  0001 C CNN
	1    6800 5450
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5EE242AC
P 6800 5250
F 0 "#PWR0103" H 6800 5000 50  0001 C CNN
F 1 "GND" V 6800 5130 50  0000 R CNN
F 2 "" H 6800 5250 50  0001 C CNN
F 3 "" H 6800 5250 50  0001 C CNN
	1    6800 5250
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 5EE28E61
P 7130 5350
F 0 "#PWR0104" H 7130 5200 50  0001 C CNN
F 1 "+5V" V 7130 5450 50  0000 L CNN
F 2 "" H 7130 5350 50  0001 C CNN
F 3 "" H 7130 5350 50  0001 C CNN
	1    7130 5350
	0    1    1    0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J13
U 1 1 5EE8257A
P 5550 5050
F 0 "J13" H 5468 4725 50  0000 C CNN
F 1 "Main Power" H 5468 4816 50  0000 C CNN
F 2 "Useful Modifications:TerminalBlock_bornier-2_P5.08mm" H 5550 5050 50  0001 C CNN
F 3 "~" H 5550 5050 50  0001 C CNN
	1    5550 5050
	-1   0    0    1   
$EndComp
$Comp
L power:+12V #PWR024
U 1 1 5EE8644F
P 5750 4950
F 0 "#PWR024" H 5750 4800 50  0001 C CNN
F 1 "+12V" V 5765 5078 50  0000 L CNN
F 2 "" H 5750 4950 50  0001 C CNN
F 3 "" H 5750 4950 50  0001 C CNN
	1    5750 4950
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5F5C3B2C
P 5750 5050
F 0 "#PWR0107" H 5750 4800 50  0001 C CNN
F 1 "GND" V 5750 4950 50  0000 R CNN
F 2 "" H 5750 5050 50  0001 C CNN
F 3 "" H 5750 5050 50  0001 C CNN
	1    5750 5050
	0    -1   -1   0   
$EndComp
Text GLabel 7910 4710 0    50   Input ~ 0
Throttle
Text GLabel 7940 4130 0    50   Input ~ 0
Steering
Text GLabel 5800 3400 2    50   Input ~ 0
D5
Text GLabel 5800 2800 2    50   Input ~ 0
D13
Text GLabel 5800 2900 2    50   Input ~ 0
D12
Text GLabel 5800 3000 2    50   Input ~ 0
D11
Text GLabel 5800 3100 2    50   Input ~ 0
D10
Text GLabel 5800 3200 2    50   Input ~ 0
D9
Text GLabel 5800 3300 2    50   Input ~ 0
D6
$Comp
L power:GND #PWR07
U 1 1 5FA68CC8
P 4900 2400
F 0 "#PWR07" H 4900 2150 50  0001 C CNN
F 1 "GND" V 4900 2200 50  0000 C CNN
F 2 "" H 4900 2400 50  0001 C CNN
F 3 "" H 4900 2400 50  0001 C CNN
	1    4900 2400
	0    1    1    0   
$EndComp
$Comp
L UsefulModifications:Feather_nRF52840 U1
U 1 1 5FA6E9E8
P 5350 2750
F 0 "U1" H 5350 3647 60  0000 C CNN
F 1 "Feather_nRF52840" H 5350 3541 60  0000 C CNN
F 2 "Useful Modifications:Feather_nRF52840" H 5350 1900 60  0001 C CNN
F 3 "" H 5350 1900 60  0000 C CNN
	1    5350 2750
	1    0    0    -1  
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
Text GLabel 5800 3600 2    50   Input ~ 0
I2C_SDA
Text GLabel 5800 3500 2    50   Input ~ 0
I2C_SCL
Text GLabel 8550 4450 0    50   Input ~ 0
ActiveSW
$Comp
L ltc2645:LTC2645CMS-L8-PBF U2
U 1 1 5FB7335A
P 1660 4520
F 0 "U2" H 3060 4907 60  0000 C CNN
F 1 "LTC2645CMS-L8-PBF" H 3060 4801 60  0000 C CNN
F 2 "Useful Modifications:LTC2645CMS-L8-PBF" H 3060 4760 60  0001 C CNN
F 3 "" H 1660 4520 60  0000 C CNN
	1    1660 4520
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5FB77027
P 3760 4520
F 0 "#PWR020" H 3760 4270 50  0001 C CNN
F 1 "GND" V 3760 4420 50  0000 R CNN
F 2 "" H 3760 4520 50  0001 C CNN
F 3 "" H 3760 4520 50  0001 C CNN
	1    3760 4520
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR011
U 1 1 5FB78432
P 2260 4520
F 0 "#PWR011" H 2260 4370 50  0001 C CNN
F 1 "+3.3V" V 2260 4770 50  0000 C CNN
F 2 "" H 2260 4520 50  0001 C CNN
F 3 "" H 2260 4520 50  0001 C CNN
	1    2260 4520
	0    -1   -1   0   
$EndComp
Text GLabel 2260 4620 0    50   Input ~ 0
RCAnalogThrottle
Text GLabel 2260 4720 0    50   Input ~ 0
RCAnalogSteering
$Comp
L power:GND #PWR018
U 1 1 5FB7B9F0
P 2260 5220
F 0 "#PWR018" H 2260 4970 50  0001 C CNN
F 1 "GND" V 2260 5120 50  0000 R CNN
F 2 "" H 2260 5220 50  0001 C CNN
F 3 "" H 2260 5220 50  0001 C CNN
	1    2260 5220
	0    1    1    0   
$EndComp
Text GLabel 4900 2600 0    50   Input ~ 0
Steering
Text GLabel 4900 2500 0    50   Input ~ 0
Throttle
Text GLabel 4470 4720 2    50   Input ~ 0
Steering
Text GLabel 4470 4620 2    50   Input ~ 0
Throttle
$Comp
L power:+3.3V #PWR017
U 1 1 5FB8588A
P 2260 5120
F 0 "#PWR017" H 2260 4970 50  0001 C CNN
F 1 "+3.3V" V 2260 5370 50  0000 C CNN
F 2 "" H 2260 5120 50  0001 C CNN
F 3 "" H 2260 5120 50  0001 C CNN
	1    2260 5120
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5FB85F34
P 2260 4820
F 0 "#PWR016" H 2260 4570 50  0001 C CNN
F 1 "GND" V 2260 4720 50  0000 R CNN
F 2 "" H 2260 4820 50  0001 C CNN
F 3 "" H 2260 4820 50  0001 C CNN
	1    2260 4820
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR022
U 1 1 5FB868BE
P 3760 5220
F 0 "#PWR022" H 3760 5070 50  0001 C CNN
F 1 "+3.3V" V 3760 5470 50  0000 C CNN
F 2 "" H 3760 5220 50  0001 C CNN
F 3 "" H 3760 5220 50  0001 C CNN
	1    3760 5220
	0    1    1    0   
$EndComp
$Comp
L Jumper:SolderJumper_3_Open JP1
U 1 1 5FB889CD
P 7910 4510
F 0 "JP1" V 7956 4577 50  0000 L CNN
F 1 "Throttle Jumper" V 7865 4577 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7910 4510 50  0001 C CNN
F 3 "~" H 7910 4510 50  0001 C CNN
	1    7910 4510
	0    -1   -1   0   
$EndComp
$Comp
L Jumper:SolderJumper_3_Open JP2
U 1 1 5FB8BA5A
P 7940 3930
F 0 "JP2" V 7986 3998 50  0000 L CNN
F 1 "Steering Jumper" V 7895 3998 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7940 3930 50  0001 C CNN
F 3 "~" H 7940 3930 50  0001 C CNN
	1    7940 3930
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8090 3930 8090 4150
Wire Wire Line
	8090 4150 8550 4150
Wire Wire Line
	8060 4510 8060 4250
Wire Wire Line
	8060 4250 8550 4250
Text GLabel 7940 3730 0    50   Input ~ 0
PWMSteering
Text GLabel 7910 4310 0    50   Input ~ 0
PWMThrottle
$Comp
L power:GND #PWR021
U 1 1 5FB909D6
P 3760 4820
F 0 "#PWR021" H 3760 4570 50  0001 C CNN
F 1 "GND" V 3760 4720 50  0000 R CNN
F 2 "" H 3760 4820 50  0001 C CNN
F 3 "" H 3760 4820 50  0001 C CNN
	1    3760 4820
	0    -1   -1   0   
$EndComp
NoConn ~ 3760 4920
Text GLabel 2260 4920 0    50   Input ~ 0
RCPWMSteering
Text GLabel 2260 5020 0    50   Input ~ 0
RCPWMThrottle
Text GLabel 6540 4300 2    50   Input ~ 0
RCPWMSteering
Text GLabel 6540 4200 2    50   Input ~ 0
RCPWMThrottle
Text GLabel 4900 2900 0    50   Input ~ 0
RCAnalogThrottle
Text GLabel 4900 3000 0    50   Input ~ 0
RCAnalogSteering
Text GLabel 4900 3400 0    50   Input ~ 0
ActiveSW
$Comp
L Connector:Conn_01x04_Male J4
U 1 1 5FBAF7AC
P 6600 5350
F 0 "J4" H 6708 5631 50  0000 C CNN
F 1 "Power Input" H 6300 5400 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 6600 5350 50  0001 C CNN
F 3 "~" H 6600 5350 50  0001 C CNN
	1    6600 5350
	1    0    0    -1  
$EndComp
NoConn ~ 6800 5550
Text GLabel 3760 5020 2    50   Input ~ 0
PWMSteering
Text GLabel 3760 5120 2    50   Input ~ 0
PWMThrottle
$Comp
L Jumper:SolderJumper_2_Open JP3
U 1 1 5FC7038F
P 4320 4620
F 0 "JP3" H 4930 4620 50  0000 C CNN
F 1 "LTC Throttle Jumper" H 4510 4710 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4320 4620 50  0001 C CNN
F 3 "~" H 4320 4620 50  0001 C CNN
	1    4320 4620
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP4
U 1 1 5FC719D5
P 4320 4720
F 0 "JP4" H 4920 4730 50  0000 C CNN
F 1 "LTC Steering Jumper" H 4520 4610 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4320 4720 50  0001 C CNN
F 3 "~" H 4320 4720 50  0001 C CNN
	1    4320 4720
	1    0    0    -1  
$EndComp
Wire Wire Line
	4170 4720 3760 4720
Wire Wire Line
	4170 4620 3760 4620
Wire Wire Line
	6800 5350 7130 5350
Text GLabel 5800 2600 2    50   Input ~ 0
EN
Text GLabel 5800 2500 2    50   Input ~ 0
BAT
Text GLabel 4900 2100 0    50   Input ~ 0
RST
Text GLabel 4900 2300 0    50   Input ~ 0
AREF
Text GLabel 4900 2700 0    50   Input ~ 0
A2
Text GLabel 4900 2800 0    50   Input ~ 0
A3
Text GLabel 4900 3100 0    50   Input ~ 0
SCK
Text GLabel 4900 3200 0    50   Input ~ 0
MO
Text GLabel 4900 3300 0    50   Input ~ 0
MI
Text GLabel 4900 3500 0    50   Input ~ 0
TX
Text GLabel 4900 3600 0    50   Input ~ 0
D2
Wire Wire Line
	4600 2200 4900 2200
Text GLabel 8550 3950 0    50   Input ~ 0
D12
Text GLabel 8550 4050 0    50   Input ~ 0
D13
$Comp
L UsefulModifications:Feather_nRF52840 U3
U 1 1 6046C9DA
P 7350 2750
F 0 "U3" H 7350 3647 60  0000 C CNN
F 1 "Feather_nRF52840" H 7350 3541 60  0000 C CNN
F 2 "Useful Modifications:Feather_nRF52840" H 7350 1900 60  0001 C CNN
F 3 "" H 7350 1900 60  0000 C CNN
	1    7350 2750
	1    0    0    -1  
$EndComp
Text GLabel 7800 2500 2    50   Input ~ 0
BAT
Text GLabel 7800 2600 2    50   Input ~ 0
EN
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
Text GLabel 7800 2800 2    50   Input ~ 0
D13
Text GLabel 7800 2900 2    50   Input ~ 0
D12
Text GLabel 7800 3000 2    50   Input ~ 0
D11
Text GLabel 7800 3100 2    50   Input ~ 0
D10
Text GLabel 7800 3200 2    50   Input ~ 0
D9
Text GLabel 7800 3300 2    50   Input ~ 0
D6
Text GLabel 7800 3400 2    50   Input ~ 0
D5
Text GLabel 7800 3500 2    50   Input ~ 0
I2C_SCL
Text GLabel 7800 3600 2    50   Input ~ 0
I2C_SDA
Text GLabel 6900 2100 0    50   Input ~ 0
RST
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
Text GLabel 6900 2300 0    50   Input ~ 0
AREF
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
Text GLabel 6900 2500 0    50   Input ~ 0
Throttle
Text GLabel 6900 2600 0    50   Input ~ 0
Steering
Text GLabel 6900 2700 0    50   Input ~ 0
A2
Text GLabel 6900 2800 0    50   Input ~ 0
A3
Text GLabel 6900 2900 0    50   Input ~ 0
RCAnalogThrottle
Text GLabel 6900 3000 0    50   Input ~ 0
RCAnalogSteering
Text GLabel 6900 3100 0    50   Input ~ 0
SCK
Text GLabel 6900 3200 0    50   Input ~ 0
MO
Text GLabel 6900 3300 0    50   Input ~ 0
MI
Text GLabel 6900 3400 0    50   Input ~ 0
ActiveSW
Text GLabel 6900 3500 0    50   Input ~ 0
TX
Text GLabel 6900 3600 0    50   Input ~ 0
D2
$EndSCHEMATC
