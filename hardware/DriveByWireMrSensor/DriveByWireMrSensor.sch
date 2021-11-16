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
F 1 "10K" V 5034 4080 50  0000 C CNN
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
F 1 "100K" V 6161 3685 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5975 3685 50  0001 C CNN
F 3 "~" H 6045 3685 50  0001 C CNN
	1    6045 3685
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR0101
U 1 1 6189F625
P 3470 2515
F 0 "#PWR0101" H 3470 2365 50  0001 C CNN
F 1 "+3.3V" H 3485 2688 50  0000 C CNN
F 2 "" H 3470 2515 50  0001 C CNN
F 3 "" H 3470 2515 50  0001 C CNN
	1    3470 2515
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 618A05B7
P 3470 2815
F 0 "#PWR0102" H 3470 2565 50  0001 C CNN
F 1 "GND" H 3475 2642 50  0000 C CNN
F 2 "" H 3470 2815 50  0001 C CNN
F 3 "" H 3470 2815 50  0001 C CNN
	1    3470 2815
	1    0    0    -1  
$EndComp
Text GLabel 3470 2615 0    50   Input ~ 0
AnalogSignal1
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
AnalogSignal1
Text GLabel 6795 2760 3    50   Input ~ 0
Op1GndReference
Text GLabel 5695 4280 0    50   Input ~ 0
Op1GndReference
Text GLabel 5195 2460 0    50   Input ~ 0
SourceSignal1
Text GLabel 5000 4080 0    50   Input ~ 0
SourceSignal1
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
P 6050 5060
F 0 "U1" H 6090 5300 50  0000 C CNN
F 1 "LM358" H 6135 5210 50  0000 C CNN
F 2 "UsefulModifications:LM358PSR" H 6050 5060 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 6050 5060 50  0001 C CNN
	2    6050 5060
	1    0    0    1   
$EndComp
$Comp
L Device:R R4
U 1 1 618DED44
P 5990 4680
F 0 "R4" V 6197 4680 50  0000 C CNN
F 1 "100K" V 6106 4680 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5920 4680 50  0001 C CNN
F 3 "~" H 5990 4680 50  0001 C CNN
	1    5990 4680
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 618E050D
P 5405 4960
F 0 "R3" V 5198 4960 50  0000 C CNN
F 1 "10K" V 5289 4960 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5335 4960 50  0001 C CNN
F 3 "~" H 5405 4960 50  0001 C CNN
	1    5405 4960
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x04_Female J1
U 1 1 618E11C5
P 3670 2615
F 0 "J1" H 3698 2591 50  0000 L CNN
F 1 "Conn_01x04_Female" H 3698 2500 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 3670 2615 50  0001 C CNN
F 3 "~" H 3670 2615 50  0001 C CNN
	1    3670 2615
	1    0    0    -1  
$EndComp
Text GLabel 3470 2715 0    50   Input ~ 0
AnalogSignal2
Text GLabel 6945 2660 3    50   Input ~ 0
Op2GndReference
Wire Wire Line
	6795 2660 6945 2660
Text GLabel 5195 2560 0    50   Input ~ 0
SourceSignal2
Text GLabel 5050 4960 0    50   Input ~ 0
SourceSignal2
Text GLabel 5750 5160 0    50   Input ~ 0
Op2GndReference
Text GLabel 6595 5060 2    50   Input ~ 0
AnalogSignal2
Wire Wire Line
	6350 5060 6465 5060
Wire Wire Line
	6140 4680 6465 4680
Wire Wire Line
	6465 4680 6465 5060
Connection ~ 6465 5060
Wire Wire Line
	6465 5060 6595 5060
Wire Wire Line
	5555 4960 5645 4960
Wire Wire Line
	5840 4680 5645 4680
Wire Wire Line
	5645 4680 5645 4960
Connection ~ 5645 4960
Wire Wire Line
	5645 4960 5750 4960
Wire Wire Line
	5050 4960 5255 4960
$EndSCHEMATC
