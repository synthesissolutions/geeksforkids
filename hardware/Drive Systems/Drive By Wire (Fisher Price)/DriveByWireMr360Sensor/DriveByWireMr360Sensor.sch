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
P 5220 4120
F 0 "R1" V 5013 4120 50  0000 C CNN
F 1 "10K" V 5104 4120 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5150 4120 50  0001 C CNN
F 3 "~" H 5220 4120 50  0001 C CNN
	1    5220 4120
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 6189E497
P 6115 3725
F 0 "R2" V 6322 3725 50  0000 C CNN
F 1 "100K" V 6231 3725 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6045 3725 50  0001 C CNN
F 3 "~" H 6115 3725 50  0001 C CNN
	1    6115 3725
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
Text GLabel 6615 4220 2    50   Input ~ 0
AnalogSignal1
Text GLabel 6795 2760 3    50   Input ~ 0
Op1GndReference
Text GLabel 5670 4320 0    50   Input ~ 0
Op1GndReference
Text GLabel 5195 2460 0    50   Input ~ 0
SourceSignal1
Text GLabel 5070 4120 0    50   Input ~ 0
SourceSignal1
$Comp
L Amplifier_Operational:LM358 U1
U 1 1 618B4249
P 6065 4220
F 0 "U1" H 6080 3960 50  0000 C CNN
F 1 "LM358" H 6100 4040 50  0000 C CNN
F 2 "UsefulModifications:LM358PSR" H 6065 4220 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 6065 4220 50  0001 C CNN
	1    6065 4220
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
	6365 4220 6475 4220
Wire Wire Line
	6265 3725 6475 3725
Wire Wire Line
	6475 3725 6475 4220
Connection ~ 6475 4220
Wire Wire Line
	6475 4220 6615 4220
Wire Wire Line
	5575 4120 5765 4120
Wire Wire Line
	5575 3725 5575 4120
Wire Wire Line
	5965 3725 5575 3725
Wire Wire Line
	5370 4120 5575 4120
Connection ~ 5575 4120
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
P 8090 5280
F 0 "U1" H 8130 5520 50  0000 C CNN
F 1 "LM358" H 8175 5430 50  0000 C CNN
F 2 "UsefulModifications:LM358PSR" H 8090 5280 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 8090 5280 50  0001 C CNN
	2    8090 5280
	1    0    0    1   
$EndComp
$Comp
L Device:R R4
U 1 1 618DED44
P 8030 4900
F 0 "R4" V 8237 4900 50  0000 C CNN
F 1 "100K" V 8146 4900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7960 4900 50  0001 C CNN
F 3 "~" H 8030 4900 50  0001 C CNN
	1    8030 4900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 618E050D
P 7445 5180
F 0 "R3" V 7238 5180 50  0000 C CNN
F 1 "10K" V 7329 5180 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7375 5180 50  0001 C CNN
F 3 "~" H 7445 5180 50  0001 C CNN
	1    7445 5180
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
Text GLabel 7090 5180 0    50   Input ~ 0
SourceSignal2
Text GLabel 7790 5380 0    50   Input ~ 0
Op2GndReference
Text GLabel 8635 5280 2    50   Input ~ 0
AnalogSignal2
Wire Wire Line
	8390 5280 8505 5280
Wire Wire Line
	8180 4900 8505 4900
Wire Wire Line
	8505 4900 8505 5280
Connection ~ 8505 5280
Wire Wire Line
	8505 5280 8635 5280
Wire Wire Line
	7595 5180 7685 5180
Wire Wire Line
	7880 4900 7685 4900
Wire Wire Line
	7685 4900 7685 5180
Connection ~ 7685 5180
Wire Wire Line
	7685 5180 7790 5180
Wire Wire Line
	7090 5180 7295 5180
$Comp
L LM358:LM358PSR U3
U 1 1 619970C4
P 1660 6460
F 0 "U3" H 2860 6847 60  0000 C CNN
F 1 "LM358PSR" H 2860 6741 60  0000 C CNN
F 2 "UsefulModifications:DFN-8-LM358" H 2860 6700 60  0001 C CNN
F 3 "" H 1660 6460 60  0000 C CNN
	1    1660 6460
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 61998A96
P 1660 6760
F 0 "#PWR0107" H 1660 6510 50  0001 C CNN
F 1 "GND" H 1665 6587 50  0000 C CNN
F 2 "" H 1660 6760 50  0001 C CNN
F 3 "" H 1660 6760 50  0001 C CNN
	1    1660 6760
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0108
U 1 1 61999CB9
P 4060 6460
F 0 "#PWR0108" H 4060 6310 50  0001 C CNN
F 1 "+3.3V" H 4075 6633 50  0000 C CNN
F 2 "" H 4060 6460 50  0001 C CNN
F 3 "" H 4060 6460 50  0001 C CNN
	1    4060 6460
	1    0    0    -1  
$EndComp
Text GLabel 4060 6560 2    50   Input ~ 0
LM358_Out2
Text GLabel 4060 6660 2    50   Input ~ 0
LM358_InM2
Text GLabel 4060 6760 2    50   Input ~ 0
LM358_InP2
Text GLabel 1660 6460 0    50   Input ~ 0
LM358_Out1
Text GLabel 1660 6560 0    50   Input ~ 0
LM358_InM1
Text GLabel 1660 6660 0    50   Input ~ 0
LM358_InP1
Text GLabel 7790 5380 3    50   Input ~ 0
LM358_InP2
Text GLabel 8420 5280 3    50   Input ~ 0
LM358_Out2
Text GLabel 7790 5180 1    50   Input ~ 0
LM358_InM2
Text GLabel 6400 4220 3    50   Input ~ 0
LM358_Out1
Text GLabel 5760 4120 1    50   Input ~ 0
LM358_InM1
Text GLabel 5765 4320 3    50   Input ~ 0
LM358_InP1
Wire Wire Line
	5765 4320 5670 4320
$EndSCHEMATC
