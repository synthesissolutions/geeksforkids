EESchema Schematic File Version 4
EELAYER 29 0
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
L PowerBreakout:LM2596Adj U1
U 1 1 5D990B47
P 6500 4000
F 0 "U1" H 6500 4500 50  0000 C CNN
F 1 "LM2596Adj" H 6500 4424 50  0000 C CNN
F 2 "PowerBreakout:LM2596Adj" H 6500 4000 50  0001 C CNN
F 3 "" H 6500 4000 50  0001 C CNN
	1    6500 4000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 5D99419C
P 7550 3900
F 0 "J2" H 7522 3782 50  0000 R CNN
F 1 "Conn_01x02_Male" H 7522 3873 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7550 3900 50  0001 C CNN
F 3 "~" H 7550 3900 50  0001 C CNN
	1    7550 3900
	-1   0    0    1   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5D99545E
P 5400 3900
F 0 "J1" H 5318 3575 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 5318 3666 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 5400 3900 50  0001 C CNN
F 3 "~" H 5400 3900 50  0001 C CNN
	1    5400 3900
	-1   0    0    1   
$EndComp
Wire Wire Line
	7100 3750 7350 3750
Wire Wire Line
	7350 3750 7350 3800
Wire Wire Line
	7100 3950 7350 3950
Wire Wire Line
	7350 3950 7350 3900
Wire Wire Line
	5600 3800 5600 3750
Wire Wire Line
	5600 3750 5900 3750
Wire Wire Line
	5600 3900 5600 3950
Wire Wire Line
	5600 3950 5900 3950
$EndSCHEMATC
