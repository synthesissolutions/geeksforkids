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
P 5200 2800
F 0 "J1" V 5211 3330 50  0000 L CNN
F 1 "8P8C" V 5302 3330 50  0000 L CNN
F 2 "Connector_RJ:RJ45_Amphenol_54602-x08_Horizontal" V 5200 2825 50  0001 C CNN
F 3 "~" V 5200 2825 50  0001 C CNN
	1    5200 2800
	0    1    1    0   
$EndComp
Text Notes 4850 3100 0    59   ~ 0
G 5 1 2 X Y 3
$Comp
L power:GND #PWR01
U 1 1 5D6AB4B0
P 3340 2670
F 0 "#PWR01" H 3340 2420 50  0001 C CNN
F 1 "GND" V 3345 2497 50  0000 C CNN
F 2 "" H 3340 2670 50  0001 C CNN
F 3 "" H 3340 2670 50  0001 C CNN
	1    3340 2670
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5D6AC60C
P 3340 2770
F 0 "#PWR03" H 3340 2520 50  0001 C CNN
F 1 "GND" V 3345 2597 50  0000 C CNN
F 2 "" H 3340 2770 50  0001 C CNN
F 3 "" H 3340 2770 50  0001 C CNN
	1    3340 2770
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5D6AE98C
P 4900 3200
F 0 "#PWR05" H 4900 2950 50  0001 C CNN
F 1 "GND" V 4900 2980 50  0000 C CNN
F 2 "" H 4900 3200 50  0001 C CNN
F 3 "" H 4900 3200 50  0001 C CNN
	1    4900 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5D6AF2D0
P 3320 3510
F 0 "#PWR07" H 3320 3260 50  0001 C CNN
F 1 "GND" V 3320 3300 50  0000 C CNN
F 2 "" H 3320 3510 50  0001 C CNN
F 3 "" H 3320 3510 50  0001 C CNN
	1    3320 3510
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5D6AFA73
P 3320 3610
F 0 "#PWR08" H 3320 3360 50  0001 C CNN
F 1 "GND" V 3320 3410 50  0000 C CNN
F 2 "" H 3320 3610 50  0001 C CNN
F 3 "" H 3320 3610 50  0001 C CNN
	1    3320 3610
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR010
U 1 1 5D6B449C
P 5500 3200
F 0 "#PWR010" H 5500 3050 50  0001 C CNN
F 1 "+3.3V" V 5500 3460 50  0000 C CNN
F 2 "" H 5500 3200 50  0001 C CNN
F 3 "" H 5500 3200 50  0001 C CNN
	1    5500 3200
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR06
U 1 1 5D6B4DCC
P 5000 3200
F 0 "#PWR06" H 5000 3050 50  0001 C CNN
F 1 "+5V" V 4990 3420 50  0000 C CNN
F 2 "" H 5000 3200 50  0001 C CNN
F 3 "" H 5000 3200 50  0001 C CNN
	1    5000 3200
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR04
U 1 1 5D6B5352
P 3840 2770
F 0 "#PWR04" H 3840 2620 50  0001 C CNN
F 1 "+5V" V 3855 2943 50  0000 C CNN
F 2 "" H 3840 2770 50  0001 C CNN
F 3 "" H 3840 2770 50  0001 C CNN
	1    3840 2770
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 5D6B5AB7
P 3840 2670
F 0 "#PWR02" H 3840 2520 50  0001 C CNN
F 1 "+5V" V 3855 2843 50  0000 C CNN
F 2 "" H 3840 2670 50  0001 C CNN
F 3 "" H 3840 2670 50  0001 C CNN
	1    3840 2670
	0    1    1    0   
$EndComp
Text GLabel 3820 3510 2    50   Input ~ 0
Sound1
Text GLabel 5100 3200 3    50   Input ~ 0
Sound1
Text GLabel 5200 3200 3    50   Input ~ 0
Sound2
Text GLabel 3820 3610 2    50   Input ~ 0
Sound2
Text GLabel 5300 3200 3    50   Input ~ 0
JoyX
Text GLabel 5400 3200 3    50   Input ~ 0
JoyY
Text GLabel 6110 2790 0    50   Input ~ 0
JoyY
$Comp
L MCU_Microchip_ATtiny:ATtiny814-SS U1
U 1 1 6015A26B
P 6710 3090
F 0 "U1" H 6300 3760 50  0000 C CNN
F 1 "ATtiny814-SS" H 7070 3740 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 6710 3090 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/40001912A.pdf" H 6710 3090 50  0001 C CNN
	1    6710 3090
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 6016B82C
P 3340 3070
F 0 "#PWR011" H 3340 2820 50  0001 C CNN
F 1 "GND" V 3345 2897 50  0000 C CNN
F 2 "" H 3340 3070 50  0001 C CNN
F 3 "" H 3340 3070 50  0001 C CNN
	1    3340 3070
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR012
U 1 1 6016B832
P 3840 3070
F 0 "#PWR012" H 3840 2920 50  0001 C CNN
F 1 "+5V" V 3855 3243 50  0000 C CNN
F 2 "" H 3840 3070 50  0001 C CNN
F 3 "" H 3840 3070 50  0001 C CNN
	1    3840 3070
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR016
U 1 1 60170FA0
P 6710 3790
F 0 "#PWR016" H 6710 3540 50  0001 C CNN
F 1 "GND" V 6710 3570 50  0000 C CNN
F 2 "" H 6710 3790 50  0001 C CNN
F 3 "" H 6710 3790 50  0001 C CNN
	1    6710 3790
	1    0    0    -1  
$EndComp
Text GLabel 3820 3710 2    50   Input ~ 0
LeftButton
Text GLabel 3820 3810 2    50   Input ~ 0
RightButton
Text GLabel 7310 3190 2    50   Input ~ 0
RightButton
Text GLabel 7310 2990 2    50   Input ~ 0
LeftButton
$Comp
L power:GND #PWR017
U 1 1 60176FC9
P 3340 2970
F 0 "#PWR017" H 3340 2720 50  0001 C CNN
F 1 "GND" V 3345 2797 50  0000 C CNN
F 2 "" H 3340 2970 50  0001 C CNN
F 3 "" H 3340 2970 50  0001 C CNN
	1    3340 2970
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR018
U 1 1 60176FCF
P 3840 2970
F 0 "#PWR018" H 3840 2820 50  0001 C CNN
F 1 "+5V" V 3855 3143 50  0000 C CNN
F 2 "" H 3840 2970 50  0001 C CNN
F 3 "" H 3840 2970 50  0001 C CNN
	1    3840 2970
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR019
U 1 1 601776DB
P 3340 2870
F 0 "#PWR019" H 3340 2620 50  0001 C CNN
F 1 "GND" V 3345 2697 50  0000 C CNN
F 2 "" H 3340 2870 50  0001 C CNN
F 3 "" H 3340 2870 50  0001 C CNN
	1    3340 2870
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR020
U 1 1 601776E1
P 3840 2870
F 0 "#PWR020" H 3840 2720 50  0001 C CNN
F 1 "+5V" V 3855 3043 50  0000 C CNN
F 2 "" H 3840 2870 50  0001 C CNN
F 3 "" H 3840 2870 50  0001 C CNN
	1    3840 2870
	0    1    1    0   
$EndComp
Text GLabel 5600 3200 3    50   Input ~ 0
Other
NoConn ~ 6110 2990
NoConn ~ 6110 2890
$Comp
L power:GND #PWR021
U 1 1 6018923D
P 3320 4110
F 0 "#PWR021" H 3320 3860 50  0001 C CNN
F 1 "GND" V 3320 3910 50  0000 C CNN
F 2 "" H 3320 4110 50  0001 C CNN
F 3 "" H 3320 4110 50  0001 C CNN
	1    3320 4110
	0    1    1    0   
$EndComp
Text GLabel 3820 4010 2    50   Input ~ 0
ReverseButton
Text GLabel 7310 3090 2    50   Input ~ 0
ReverseButton
Text GLabel 6110 2690 0    50   Input ~ 0
JoyX
Text GLabel 3820 3910 2    50   Input ~ 0
DriveButton
Text GLabel 7310 2790 2    50   Input ~ 0
DriveButton
$Comp
L power:GND #PWR09
U 1 1 601B4E8A
P 3320 3710
F 0 "#PWR09" H 3320 3460 50  0001 C CNN
F 1 "GND" V 3320 3500 50  0000 C CNN
F 2 "" H 3320 3710 50  0001 C CNN
F 3 "" H 3320 3710 50  0001 C CNN
	1    3320 3710
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 601B4E90
P 3320 3810
F 0 "#PWR013" H 3320 3560 50  0001 C CNN
F 1 "GND" V 3320 3610 50  0000 C CNN
F 2 "" H 3320 3810 50  0001 C CNN
F 3 "" H 3320 3810 50  0001 C CNN
	1    3320 3810
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR014
U 1 1 601B5530
P 3320 3910
F 0 "#PWR014" H 3320 3660 50  0001 C CNN
F 1 "GND" V 3320 3700 50  0000 C CNN
F 2 "" H 3320 3910 50  0001 C CNN
F 3 "" H 3320 3910 50  0001 C CNN
	1    3320 3910
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR022
U 1 1 601B5536
P 3320 4010
F 0 "#PWR022" H 3320 3760 50  0001 C CNN
F 1 "GND" V 3320 3810 50  0000 C CNN
F 2 "" H 3320 4010 50  0001 C CNN
F 3 "" H 3320 4010 50  0001 C CNN
	1    3320 4010
	0    1    1    0   
$EndComp
Text GLabel 3820 4110 2    50   Input ~ 0
Other
$Comp
L power:GND #PWR023
U 1 1 601EFEBA
P 5140 4200
F 0 "#PWR023" H 5140 3950 50  0001 C CNN
F 1 "GND" V 5140 4000 50  0000 C CNN
F 2 "" H 5140 4200 50  0001 C CNN
F 3 "" H 5140 4200 50  0001 C CNN
	1    5140 4200
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Male J4
U 1 1 601EFEC4
P 5240 4400
F 0 "J4" V 5394 4212 50  0000 R CNN
F 1 "Programmer" V 5303 4212 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 5240 4400 50  0001 C CNN
F 3 "~" H 5240 4400 50  0001 C CNN
	1    5240 4400
	0    -1   -1   0   
$EndComp
Text GLabel 5240 4200 1    50   Input ~ 0
Program
$Comp
L Connector_Generic:Conn_02x07_Odd_Even J2
U 1 1 6015CAAC
P 3520 3810
F 0 "J2" H 3570 4327 50  0000 C CNN
F 1 "Inputs" H 3570 4236 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x07_P2.54mm_Vertical" H 3520 3810 50  0001 C CNN
F 3 "~" H 3520 3810 50  0001 C CNN
	1    3520 3810
	1    0    0    -1  
$EndComp
Text GLabel 7310 2690 2    50   Input ~ 0
Program
NoConn ~ 7310 3390
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J3
U 1 1 601A11BC
P 3540 2870
F 0 "J3" H 3590 3287 50  0000 C CNN
F 1 "LEDs" H 3590 3196 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x05_P2.54mm_Vertical" H 3540 2870 50  0001 C CNN
F 3 "~" H 3540 2870 50  0001 C CNN
	1    3540 2870
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR028
U 1 1 6019E5D0
P 5340 4200
F 0 "#PWR028" H 5340 4050 50  0001 C CNN
F 1 "+3.3V" V 5340 4460 50  0000 C CNN
F 2 "" H 5340 4200 50  0001 C CNN
F 3 "" H 5340 4200 50  0001 C CNN
	1    5340 4200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR029
U 1 1 601A23F4
P 6710 2390
F 0 "#PWR029" H 6710 2240 50  0001 C CNN
F 1 "+3.3V" V 6710 2650 50  0000 C CNN
F 2 "" H 6710 2390 50  0001 C CNN
F 3 "" H 6710 2390 50  0001 C CNN
	1    6710 2390
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male J5
U 1 1 601A3741
P 3390 4790
F 0 "J5" H 3498 5171 50  0000 C CNN
F 1 "RefVoltage" H 3498 5080 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 3390 4790 50  0001 C CNN
F 3 "~" H 3390 4790 50  0001 C CNN
	1    3390 4790
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR015
U 1 1 601A560F
P 3590 4590
F 0 "#PWR015" H 3590 4440 50  0001 C CNN
F 1 "+3.3V" V 3590 4850 50  0000 C CNN
F 2 "" H 3590 4590 50  0001 C CNN
F 3 "" H 3590 4590 50  0001 C CNN
	1    3590 4590
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR024
U 1 1 601A58BA
P 3590 4690
F 0 "#PWR024" H 3590 4540 50  0001 C CNN
F 1 "+3.3V" V 3590 4950 50  0000 C CNN
F 2 "" H 3590 4690 50  0001 C CNN
F 3 "" H 3590 4690 50  0001 C CNN
	1    3590 4690
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR025
U 1 1 601A5EFC
P 3590 4790
F 0 "#PWR025" H 3590 4640 50  0001 C CNN
F 1 "+3.3V" V 3590 5050 50  0000 C CNN
F 2 "" H 3590 4790 50  0001 C CNN
F 3 "" H 3590 4790 50  0001 C CNN
	1    3590 4790
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR026
U 1 1 601A6330
P 3590 4890
F 0 "#PWR026" H 3590 4740 50  0001 C CNN
F 1 "+3.3V" V 3590 5150 50  0000 C CNN
F 2 "" H 3590 4890 50  0001 C CNN
F 3 "" H 3590 4890 50  0001 C CNN
	1    3590 4890
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR027
U 1 1 601A66F1
P 3590 4990
F 0 "#PWR027" H 3590 4840 50  0001 C CNN
F 1 "+3.3V" V 3590 5250 50  0000 C CNN
F 2 "" H 3590 4990 50  0001 C CNN
F 3 "" H 3590 4990 50  0001 C CNN
	1    3590 4990
	0    1    1    0   
$EndComp
NoConn ~ 7310 2890
NoConn ~ 7310 3290
$EndSCHEMATC
