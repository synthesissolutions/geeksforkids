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
L Connector:Conn_01x03_Male J1
U 1 1 5F0310D3
P 5500 3370
F 0 "J1" H 5472 3302 50  0000 R CNN
F 1 "Conn_01x03_Male" H 5472 3393 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 5500 3370 50  0001 C CNN
F 3 "~" H 5500 3370 50  0001 C CNN
	1    5500 3370
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Male J2
U 1 1 5F031F15
P 5500 3690
F 0 "J2" H 5472 3622 50  0000 R CNN
F 1 "Conn_01x03_Male" H 5472 3713 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 5500 3690 50  0001 C CNN
F 3 "~" H 5500 3690 50  0001 C CNN
	1    5500 3690
	-1   0    0    1   
$EndComp
Wire Wire Line
	4920 3790 5300 3790
Wire Wire Line
	5070 3690 5300 3690
Wire Wire Line
	4920 3220 5140 3220
Wire Wire Line
	5140 3220 5140 3590
Wire Wire Line
	5140 3590 5300 3590
Wire Wire Line
	5140 3220 5220 3220
Wire Wire Line
	5220 3220 5220 3370
Wire Wire Line
	5220 3370 5300 3370
Connection ~ 5140 3220
Wire Wire Line
	5070 3380 5180 3380
Wire Wire Line
	5180 3380 5180 3270
Wire Wire Line
	5180 3270 5300 3270
Wire Wire Line
	5070 3380 5070 3690
Wire Wire Line
	5070 3370 5070 3380
Connection ~ 5070 3380
$Comp
L Device:R_POT RV1
U 1 1 5F03080C
P 4920 3370
F 0 "RV1" H 4851 3416 50  0000 R CNN
F 1 "R_POT" H 4851 3325 50  0000 R CNN
F 2 "PotentiometerToServoWire:Potentiometer_5.08mm" H 4920 3370 50  0001 C CNN
F 3 "~" H 4920 3370 50  0001 C CNN
	1    4920 3370
	1    0    0    -1  
$EndComp
Wire Wire Line
	4920 3520 4920 3790
Wire Wire Line
	4920 3520 5010 3520
Wire Wire Line
	5010 3520 5010 3470
Wire Wire Line
	5010 3470 5300 3470
Connection ~ 4920 3520
$EndSCHEMATC
