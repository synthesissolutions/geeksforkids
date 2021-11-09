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
L KMZ49:KMZ49_118 U2
U 1 1 6189BA90
P 5195 2460
F 0 "U2" H 5995 2847 60  0000 C CNN
F 1 "KMZ49_118" H 5995 2741 60  0000 C CNN
F 2 "UsefulModifications:KMZ49_118" H 5995 2700 60  0001 C CNN
F 3 "" H 5195 2460 60  0000 C CNN
	1    5195 2460
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 6189DE68
P 5150 4080
F 0 "R1" V 4943 4080 50  0000 C CNN
F 1 "100K" V 5034 4080 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5080 4080 50  0001 C CNN
F 3 "~" H 5150 4080 50  0001 C CNN
	1    5150 4080
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 6189E497
P 6045 3685
F 0 "R2" V 6252 3685 50  0000 C CNN
F 1 "560K" V 6161 3685 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5975 3685 50  0001 C CNN
F 3 "~" H 6045 3685 50  0001 C CNN
	1    6045 3685
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x03_Female J1
U 1 1 6189EBE1
P 3630 2545
F 0 "J1" H 3658 2571 50  0000 L CNN
F 1 "Conn_01x03_Female" H 3658 2480 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 3630 2545 50  0001 C CNN
F 3 "~" H 3630 2545 50  0001 C CNN
	1    3630 2545
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0101
U 1 1 6189F625
P 3430 2445
F 0 "#PWR0101" H 3430 2295 50  0001 C CNN
F 1 "+3.3V" H 3445 2618 50  0000 C CNN
F 2 "" H 3430 2445 50  0001 C CNN
F 3 "" H 3430 2445 50  0001 C CNN
	1    3430 2445
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 618A05B7
P 3430 2645
F 0 "#PWR0102" H 3430 2395 50  0001 C CNN
F 1 "GND" H 3435 2472 50  0000 C CNN
F 2 "" H 3430 2645 50  0001 C CNN
F 3 "" H 3430 2645 50  0001 C CNN
	1    3430 2645
	1    0    0    -1  
$EndComp
Text GLabel 3430 2545 0    50   Input ~ 0
AnalogSignal
$Comp
L power:+3.3V #PWR0103
U 1 1 618A1C2D
P 5085 2660
F 0 "#PWR0103" H 5085 2510 50  0001 C CNN
F 1 "+3.3V" V 5100 2788 50  0000 L CNN
F 2 "" H 5085 2660 50  0001 C CNN
F 3 "" H 5085 2660 50  0001 C CNN
	1    5085 2660
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5085 2660 5195 2660
Wire Wire Line
	5195 2760 5195 2660
Connection ~ 5195 2660
$Comp
L power:GND #PWR0104
U 1 1 618A8427
P 7115 2560
F 0 "#PWR0104" H 7115 2310 50  0001 C CNN
F 1 "GND" H 7120 2387 50  0000 C CNN
F 2 "" H 7115 2560 50  0001 C CNN
F 3 "" H 7115 2560 50  0001 C CNN
	1    7115 2560
	1    0    0    -1  
$EndComp
Wire Wire Line
	6795 2560 7115 2560
Wire Wire Line
	6795 2460 6795 2560
Connection ~ 6795 2560
$Comp
L power:GND #PWR0105
U 1 1 618A9DC5
P 3540 4290
F 0 "#PWR0105" H 3540 4040 50  0001 C CNN
F 1 "GND" H 3545 4117 50  0000 C CNN
F 2 "" H 3540 4290 50  0001 C CNN
F 3 "" H 3540 4290 50  0001 C CNN
	1    3540 4290
	1    0    0    -1  
$EndComp
Text GLabel 6545 4180 2    50   Input ~ 0
AnalogSignal
Text GLabel 6795 2760 3    50   Input ~ 0
Op1GndReference
Text GLabel 5695 4280 0    50   Input ~ 0
Op1GndReference
NoConn ~ 6795 2660
NoConn ~ 5195 2560
Text GLabel 5195 2460 0    50   Input ~ 0
SourceSignal
Text GLabel 5000 4080 0    50   Input ~ 0
SourceSignal
$Comp
L Amplifier_Operational:LM358 U1
U 1 1 618B4249
P 5995 4180
F 0 "U1" H 6010 3920 50  0000 C CNN
F 1 "LM358" H 6030 4000 50  0000 C CNN
F 2 "UsefulModifications:LM358PSR" H 5995 4180 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 5995 4180 50  0001 C CNN
	1    5995 4180
	1    0    0    1   
$EndComp
$Comp
L Amplifier_Operational:LM358 U1
U 3 1 618B5BE7
P 3640 3990
F 0 "U1" H 3598 4036 50  0000 L CNN
F 1 "LM358" H 3598 3945 50  0000 L CNN
F 2 "UsefulModifications:LM358PSR" H 3640 3990 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 3640 3990 50  0001 C CNN
	3    3640 3990
	1    0    0    -1  
$EndComp
Wire Wire Line
	6295 4180 6405 4180
Wire Wire Line
	6195 3685 6405 3685
Wire Wire Line
	6405 3685 6405 4180
Connection ~ 6405 4180
Wire Wire Line
	6405 4180 6545 4180
Wire Wire Line
	5505 4080 5695 4080
Wire Wire Line
	5505 3685 5505 4080
Wire Wire Line
	5895 3685 5505 3685
Wire Wire Line
	5300 4080 5505 4080
Connection ~ 5505 4080
$Comp
L power:+3.3V #PWR0106
U 1 1 618DFA0E
P 3540 3690
F 0 "#PWR0106" H 3540 3540 50  0001 C CNN
F 1 "+3.3V" H 3555 3863 50  0000 C CNN
F 2 "" H 3540 3690 50  0001 C CNN
F 3 "" H 3540 3690 50  0001 C CNN
	1    3540 3690
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM358 U1
U 2 1 618E9970
P 6115 4865
F 0 "U1" H 6115 5232 50  0000 C CNN
F 1 "LM358" H 6115 5141 50  0000 C CNN
F 2 "" H 6115 4865 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 6115 4865 50  0001 C CNN
	2    6115 4865
	1    0    0    -1  
$EndComp
$EndSCHEMATC
