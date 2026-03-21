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
P 5800 2700
F 0 "#PWR026" H 5800 2550 50  0001 C CNN
F 1 "+5V" V 5800 2850 50  0000 L CNN
F 2 "" H 5800 2700 50  0001 C CNN
F 3 "" H 5800 2700 50  0001 C CNN
	1    5800 2700
	0    1    1    0   
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
L power:GND #PWR0103
U 1 1 5EE242AC
P 7360 5745
F 0 "#PWR0103" H 7360 5495 50  0001 C CNN
F 1 "GND" V 7360 5625 50  0000 R CNN
F 2 "" H 7360 5745 50  0001 C CNN
F 3 "" H 7360 5745 50  0001 C CNN
	1    7360 5745
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 5EE28E61
P 7690 5845
F 0 "#PWR0104" H 7690 5695 50  0001 C CNN
F 1 "+5V" V 7690 5945 50  0000 L CNN
F 2 "" H 7690 5845 50  0001 C CNN
F 3 "" H 7690 5845 50  0001 C CNN
	1    7690 5845
	0    1    1    0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J13
U 1 1 5EE8257A
P 5550 5050
F 0 "J13" H 5468 4725 50  0000 C CNN
F 1 "Main Power In" H 5468 4816 50  0000 C CNN
F 2 "Useful Modifications:TerminalBlock_bornier-2_P5.08mm" H 5550 5050 50  0001 C CNN
F 3 "~" H 5550 5050 50  0001 C CNN
	1    5550 5050
	-1   0    0    1   
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
Text GLabel 5800 3400 2    50   Input ~ 0
D5
Text GLabel 5800 2800 2    50   Input ~ 0
D13
Text GLabel 5800 2900 2    50   Input ~ 0
D12
Text GLabel 5800 3000 2    50   Input ~ 0
D11
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
F 2 "Connector_JST:JST_SH_BM04B-SRSS-TB_1x04-1MP_P1.00mm_Vertical" H 5250 4200 50  0001 C CNN
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
$Comp
L Connector:Conn_01x04_Male J4
U 1 1 5FBAF7AC
P 7160 5845
F 0 "J4" H 7268 6126 50  0000 C CNN
F 1 "Buck Converter" H 6860 5895 50  0000 C CNN
F 2 "Useful Modifications:AdaFruit_MPM3610" H 7160 5845 50  0001 C CNN
F 3 "~" H 7160 5845 50  0001 C CNN
	1    7160 5845
	1    0    0    -1  
$EndComp
NoConn ~ 7360 6045
Wire Wire Line
	7360 5845 7690 5845
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
Text GLabel 6900 2700 0    50   Input ~ 0
A2
Text GLabel 6900 2800 0    50   Input ~ 0
A3
Text GLabel 6900 3100 0    50   Input ~ 0
SCK
Text GLabel 6900 3200 0    50   Input ~ 0
MO
Text GLabel 6900 3300 0    50   Input ~ 0
MI
Text GLabel 6900 3500 0    50   Input ~ 0
TX
Text GLabel 6900 3600 0    50   Input ~ 0
D2
$Comp
L Connector:Conn_01x03_Male J1
U 1 1 61B6931B
P 3680 4245
F 0 "J1" H 3788 4526 50  0000 C CNN
F 1 "RC Throttle" H 3788 4435 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 3680 4245 50  0001 C CNN
F 3 "~" H 3680 4245 50  0001 C CNN
	1    3680 4245
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 61B6C8EA
P 3880 4145
F 0 "#PWR01" H 3880 3895 50  0001 C CNN
F 1 "GND" V 3880 3895 50  0000 C CNN
F 2 "" H 3880 4145 50  0001 C CNN
F 3 "" H 3880 4145 50  0001 C CNN
	1    3880 4145
	0    -1   -1   0   
$EndComp
Text GLabel 3880 4345 2    50   Input ~ 0
RCPWMThrottle
$Comp
L Connector:Conn_01x03_Male J2
U 1 1 61B6DF5F
P 3690 4865
F 0 "J2" H 3798 5146 50  0000 C CNN
F 1 "RC Steering" H 3798 5055 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 3690 4865 50  0001 C CNN
F 3 "~" H 3690 4865 50  0001 C CNN
	1    3690 4865
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 61B6EC1D
P 3890 4765
F 0 "#PWR02" H 3890 4515 50  0001 C CNN
F 1 "GND" V 3890 4515 50  0000 C CNN
F 2 "" H 3890 4765 50  0001 C CNN
F 3 "" H 3890 4765 50  0001 C CNN
	1    3890 4765
	0    -1   -1   0   
$EndComp
Text GLabel 3890 4965 2    50   Input ~ 0
RCPWMSteering
Text GLabel 4900 2500 0    50   Input ~ 0
A0
Text GLabel 4900 2600 0    50   Input ~ 0
A1
Text GLabel 4900 2900 0    50   Input ~ 0
A4
Text GLabel 4900 3000 0    50   Input ~ 0
A5
Text GLabel 4900 3400 0    50   Input ~ 0
RX
Text GLabel 6900 2500 0    50   Input ~ 0
A0
Text GLabel 6900 2600 0    50   Input ~ 0
A1
Text GLabel 6900 2900 0    50   Input ~ 0
A4
Text GLabel 6900 3000 0    50   Input ~ 0
A5
Text GLabel 6900 3400 0    50   Input ~ 0
RX
$Comp
L Connector:Conn_01x04_Male J6
U 1 1 61B7375D
P 6470 4250
F 0 "J6" H 6670 4500 50  0000 R CNN
F 1 "UART" H 6520 4500 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6470 4250 50  0001 C CNN
F 3 "~" H 6470 4250 50  0001 C CNN
	1    6470 4250
	1    0    0    -1  
$EndComp
Text GLabel 3880 4245 2    50   Input ~ 0
RCPower
Text GLabel 3890 4865 2    50   Input ~ 0
RCPower
$Comp
L power:+3.3V #PWR05
U 1 1 61B74DD6
P 6670 4150
F 0 "#PWR05" H 6670 4000 50  0001 C CNN
F 1 "+3.3V" V 6670 4400 50  0000 C CNN
F 2 "" H 6670 4150 50  0001 C CNN
F 3 "" H 6670 4150 50  0001 C CNN
	1    6670 4150
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 61B76113
P 6670 4250
F 0 "#PWR06" H 6670 4000 50  0001 C CNN
F 1 "GND" V 6670 4000 50  0000 C CNN
F 2 "" H 6670 4250 50  0001 C CNN
F 3 "" H 6670 4250 50  0001 C CNN
	1    6670 4250
	0    -1   -1   0   
$EndComp
Text GLabel 6670 4450 2    50   Input ~ 0
TX
Text GLabel 6670 4350 2    50   Input ~ 0
RX
$Comp
L Connector:Screw_Terminal_01x02 J3
U 1 1 61B77620
P 6830 5065
F 0 "J3" H 6748 4740 50  0000 C CNN
F 1 "RC Power Out" H 6748 4831 50  0000 C CNN
F 2 "Useful Modifications:TerminalBlock_bornier-2_P5.08mm" H 6830 5065 50  0001 C CNN
F 3 "~" H 6830 5065 50  0001 C CNN
	1    6830 5065
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 61B7A00F
P 7030 5065
F 0 "#PWR04" H 7030 4815 50  0001 C CNN
F 1 "GND" V 7030 4965 50  0000 R CNN
F 2 "" H 7030 5065 50  0001 C CNN
F 3 "" H 7030 5065 50  0001 C CNN
	1    7030 5065
	0    -1   -1   0   
$EndComp
Text GLabel 5800 3100 2    50   Input ~ 0
RCPWMThrottle
Text GLabel 7800 3100 2    50   Input ~ 0
RCPWMThrottle
Text GLabel 5800 3200 2    50   Input ~ 0
RCPWMSteering
Text GLabel 7800 3200 2    50   Input ~ 0
RCPWMSteering
$Comp
L Connector:Conn_01x03_Male J7
U 1 1 61B7D6A0
P 5600 5890
F 0 "J7" H 5708 6171 50  0000 C CNN
F 1 "Power Selector" H 5708 6080 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 5600 5890 50  0001 C CNN
F 3 "~" H 5600 5890 50  0001 C CNN
	1    5600 5890
	1    0    0    -1  
$EndComp
Text GLabel 5800 5890 2    50   Input ~ 0
PowerIn
Text GLabel 5750 4950 2    50   Input ~ 0
MainPowerIn
Text GLabel 7030 4965 2    50   Input ~ 0
MainPowerIn
Text GLabel 5800 5990 2    50   Input ~ 0
RCPower
Text GLabel 5800 5790 2    50   Input ~ 0
MainPowerIn
Text GLabel 7360 5945 2    50   Input ~ 0
PowerIn
$EndSCHEMATC
