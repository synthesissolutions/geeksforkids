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
L Connector:Screw_Terminal_01x02 J13
U 1 1 5EE8257A
P 4050 2450
F 0 "J13" H 3968 2125 50  0000 C CNN
F 1 "Main Power" H 3968 2216 50  0000 C CNN
F 2 "Useful Modifications:TerminalBlock_bornier-2_P5.08mm" H 4050 2450 50  0001 C CNN
F 3 "~" H 4050 2450 50  0001 C CNN
	1    4050 2450
	-1   0    0    1   
$EndComp
$Comp
L power:+12V #PWR024
U 1 1 5EE8644F
P 4250 2350
F 0 "#PWR024" H 4250 2200 50  0001 C CNN
F 1 "+12V" V 4265 2478 50  0000 L CNN
F 2 "" H 4250 2350 50  0001 C CNN
F 3 "" H 4250 2350 50  0001 C CNN
	1    4250 2350
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
P 5410 2500
F 0 "#PWR019" H 5410 2250 50  0001 C CNN
F 1 "GNDA" V 5410 2250 50  0000 C CNN
F 2 "" H 5410 2500 50  0001 C CNN
F 3 "" H 5410 2500 50  0001 C CNN
	1    5410 2500
	0    1    1    0   
$EndComp
Text GLabel 5410 2200 0    50   Input ~ 0
LeftIN
Text GLabel 5410 2300 0    50   Input ~ 0
RightIN
$Comp
L power:GND #PWR0107
U 1 1 5F5C3B2C
P 4250 2450
F 0 "#PWR0107" H 4250 2200 50  0001 C CNN
F 1 "GND" V 4250 2350 50  0000 R CNN
F 2 "" H 4250 2450 50  0001 C CNN
F 3 "" H 4250 2450 50  0001 C CNN
	1    4250 2450
	0    -1   -1   0   
$EndComp
Text Notes 5950 2430 0    50   ~ 0
Connects to Amp\non other sheet.
$Comp
L Connector:AudioJack4 J1
U 1 1 5FCB1547
P 5610 2400
F 0 "J1" H 5567 2725 50  0000 C CNN
F 1 "AudioJack4" H 5567 2634 50  0000 C CNN
F 2 "Useful Modifications:Jack_3.5mm_PJ320A_Horizontal_Short" H 5610 2400 50  0001 C CNN
F 3 "~" H 5610 2400 50  0001 C CNN
	1    5610 2400
	-1   0    0    1   
$EndComp
NoConn ~ 5410 2400
$EndSCHEMATC
