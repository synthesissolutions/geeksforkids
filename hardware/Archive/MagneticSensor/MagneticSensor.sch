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
L Connector:Conn_01x03_Female J1
U 1 1 617804DA
P 5200 4060
F 0 "J1" H 5228 4086 50  0000 L CNN
F 1 "Conn_01x03_Female" H 5228 3995 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 5200 4060 50  0001 C CNN
F 3 "~" H 5200 4060 50  0001 C CNN
	1    5200 4060
	1    0    0    -1  
$EndComp
$Comp
L MagneticSensorRR112:RR112 U1
U 1 1 61780D7E
P 6360 4030
F 0 "U1" H 6688 4076 50  0000 L CNN
F 1 "RR112" H 6688 3985 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 6360 4030 50  0001 C CNN
F 3 "https://media.cotorelay.com/wp-content/uploads/2020/10/04163217/RedRock-RR112-1G42-1G43-531-532-Datasheet-1.pdf" H 6360 4030 50  0001 C CNN
	1    6360 4030
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 61781ACB
P 6210 4650
F 0 "C1" H 6302 4696 50  0000 L CNN
F 1 "1uF" H 6302 4605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6210 4650 50  0001 C CNN
F 3 "~" H 6210 4650 50  0001 C CNN
	1    6210 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 617822BA
P 7260 4640
F 0 "C2" H 7352 4686 50  0000 L CNN
F 1 "100pF" H 7352 4595 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7260 4640 50  0001 C CNN
F 3 "~" H 7260 4640 50  0001 C CNN
	1    7260 4640
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 61782D4C
P 6920 4440
F 0 "R1" V 6724 4440 50  0000 C CNN
F 1 "47k" V 6815 4440 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6920 4440 50  0001 C CNN
F 3 "~" H 6920 4440 50  0001 C CNN
	1    6920 4440
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR01
U 1 1 6178AA44
P 5000 3960
F 0 "#PWR01" H 5000 3810 50  0001 C CNN
F 1 "+3.3V" V 5010 4100 50  0000 L CNN
F 2 "" H 5000 3960 50  0001 C CNN
F 3 "" H 5000 3960 50  0001 C CNN
	1    5000 3960
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 6178C555
P 5000 4160
F 0 "#PWR02" H 5000 3910 50  0001 C CNN
F 1 "GND" V 5005 4032 50  0000 R CNN
F 2 "" H 5000 4160 50  0001 C CNN
F 3 "" H 5000 4160 50  0001 C CNN
	1    5000 4160
	0    1    1    0   
$EndComp
Text GLabel 5000 4060 0    50   Input ~ 0
AnalogOutput
Text GLabel 7430 4440 2    50   Input ~ 0
AnalogOutput
Wire Wire Line
	6560 4380 6560 4440
Wire Wire Line
	6560 4440 6820 4440
Wire Wire Line
	7020 4440 7260 4440
Wire Wire Line
	7260 4440 7260 4540
Wire Wire Line
	7430 4440 7260 4440
Connection ~ 7260 4440
$Comp
L power:GND #PWR05
U 1 1 6178F12D
P 6360 3680
F 0 "#PWR05" H 6360 3430 50  0001 C CNN
F 1 "GND" H 6365 3507 50  0000 C CNN
F 2 "" H 6360 3680 50  0001 C CNN
F 3 "" H 6360 3680 50  0001 C CNN
	1    6360 3680
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR03
U 1 1 61790BA1
P 6060 4480
F 0 "#PWR03" H 6060 4330 50  0001 C CNN
F 1 "+3.3V" V 6070 4620 50  0000 L CNN
F 2 "" H 6060 4480 50  0001 C CNN
F 3 "" H 6060 4480 50  0001 C CNN
	1    6060 4480
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6060 4480 6210 4480
Wire Wire Line
	6210 4380 6210 4480
Connection ~ 6210 4480
Wire Wire Line
	6210 4480 6210 4550
$Comp
L power:GND #PWR04
U 1 1 6178FA93
P 6210 4750
F 0 "#PWR04" H 6210 4500 50  0001 C CNN
F 1 "GND" H 6215 4577 50  0000 C CNN
F 2 "" H 6210 4750 50  0001 C CNN
F 3 "" H 6210 4750 50  0001 C CNN
	1    6210 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61793E7B
P 7260 4740
F 0 "#PWR?" H 7260 4490 50  0001 C CNN
F 1 "GND" H 7265 4567 50  0000 C CNN
F 2 "" H 7260 4740 50  0001 C CNN
F 3 "" H 7260 4740 50  0001 C CNN
	1    7260 4740
	1    0    0    -1  
$EndComp
$EndSCHEMATC
