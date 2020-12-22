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
L Connector_Generic:Conn_02x11_Odd_Even J5
U 1 1 5DD617CB
P 5600 2900
F 0 "J5" H 5650 3617 50  0000 C CNN
F 1 "FX_Sound" H 5650 3526 50  0000 C CNN
F 2 "Useful Modifications:FXSound_2x11_P2.54mm" H 5600 2900 50  0001 C CNN
F 3 "~" H 5600 2900 50  0001 C CNN
	1    5600 2900
	1    0    0    -1  
$EndComp
$Comp
L Connector:RJ45 J2
U 1 1 5DD687C7
P 3900 2600
F 0 "J2" H 3957 3267 50  0000 C CNN
F 1 "RJ45" H 3957 3176 50  0000 C CNN
F 2 "Useful Modifications:RJ45_x08_Tab_Up" V 3900 2625 50  0001 C CNN
F 3 "~" V 3900 2625 50  0001 C CNN
	1    3900 2600
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5DD6CC27
P 4300 2700
F 0 "#PWR04" H 4300 2450 50  0001 C CNN
F 1 "GND" V 4300 2550 50  0000 R CNN
F 2 "" H 4300 2700 50  0001 C CNN
F 3 "" H 4300 2700 50  0001 C CNN
	1    4300 2700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5DD703B3
P 5900 2500
F 0 "#PWR010" H 5900 2250 50  0001 C CNN
F 1 "GND" V 5900 2350 50  0000 R CNN
F 2 "" H 5900 2500 50  0001 C CNN
F 3 "" H 5900 2500 50  0001 C CNN
	1    5900 2500
	0    -1   -1   0   
$EndComp
$Comp
L power:+12V #PWR05
U 1 1 5DD7C79B
P 4340 3880
F 0 "#PWR05" H 4340 3730 50  0001 C CNN
F 1 "+12V" V 4355 4008 50  0000 L CNN
F 2 "" H 4340 3880 50  0001 C CNN
F 3 "" H 4340 3880 50  0001 C CNN
	1    4340 3880
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR07
U 1 1 5DD7F84B
P 4340 3780
F 0 "#PWR07" H 4340 3630 50  0001 C CNN
F 1 "+5V" V 4355 3908 50  0000 L CNN
F 2 "" H 4340 3780 50  0001 C CNN
F 3 "" H 4340 3780 50  0001 C CNN
	1    4340 3780
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR09
U 1 1 5DD847BF
P 5900 2400
F 0 "#PWR09" H 5900 2250 50  0001 C CNN
F 1 "+5V" V 5900 2550 50  0000 L CNN
F 2 "" H 5900 2400 50  0001 C CNN
F 3 "" H 5900 2400 50  0001 C CNN
	1    5900 2400
	0    1    1    0   
$EndComp
NoConn ~ 5900 3100
NoConn ~ 5900 3000
NoConn ~ 5900 2900
NoConn ~ 5900 2800
NoConn ~ 5900 2700
NoConn ~ 5900 2600
NoConn ~ 5400 2400
NoConn ~ 5400 2500
NoConn ~ 5400 2800
NoConn ~ 5400 2900
NoConn ~ 5400 3000
NoConn ~ 5400 3100
NoConn ~ 5400 3200
NoConn ~ 5400 3300
NoConn ~ 5400 3400
$Comp
L power:GND #PWR03
U 1 1 5DD8903C
P 4300 2500
F 0 "#PWR03" H 4300 2250 50  0001 C CNN
F 1 "GND" V 4300 2350 50  0000 R CNN
F 2 "" H 4300 2500 50  0001 C CNN
F 3 "" H 4300 2500 50  0001 C CNN
	1    4300 2500
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 5DD6A29E
P 4500 3000
F 0 "J3" H 4472 2882 50  0000 R CNN
F 1 "Other Button" H 4472 2973 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4500 3000 50  0001 C CNN
F 3 "~" H 4500 3000 50  0001 C CNN
	1    4500 3000
	-1   0    0    1   
$EndComp
Wire Wire Line
	4700 2700 4550 2800
Wire Wire Line
	4550 2800 4300 2800
Wire Wire Line
	4300 2600 5400 2600
Wire Wire Line
	4700 2700 5400 2700
$Comp
L power:+12V #PWR01
U 1 1 5DD7BD56
P 4600 2050
F 0 "#PWR01" H 4600 1900 50  0001 C CNN
F 1 "+12V" V 4600 2350 50  0000 C CNN
F 2 "" H 4600 2050 50  0001 C CNN
F 3 "" H 4600 2050 50  0001 C CNN
	1    4600 2050
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J1
U 1 1 5E48F627
P 4800 2050
F 0 "J1" H 4880 2092 50  0000 L CNN
F 1 "Power and GoBtn" H 4880 2001 50  0000 L CNN
F 2 "Useful Modifications:TerminalBlock_bornier-3_P5.08mm" H 4800 2050 50  0001 C CNN
F 3 "~" H 4800 2050 50  0001 C CNN
	1    4800 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 2150 4300 2400
Wire Wire Line
	4300 2300 4600 2050
Connection ~ 4600 2050
$Sheet
S 1080 940  1570 1110
U 5FCAE1D8
F0 "MAX9744" 50
F1 "MAX9744.sch" 50
$EndSheet
$Comp
L power:GND #PWR02
U 1 1 5FCAF5DB
P 4340 3680
F 0 "#PWR02" H 4340 3430 50  0001 C CNN
F 1 "GND" V 4340 3530 50  0000 R CNN
F 2 "" H 4340 3680 50  0001 C CNN
F 3 "" H 4340 3680 50  0001 C CNN
	1    4340 3680
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5FCB0B7E
P 4600 1950
F 0 "#PWR06" H 4600 1700 50  0001 C CNN
F 1 "GND" V 4600 1800 50  0000 R CNN
F 2 "" H 4600 1950 50  0001 C CNN
F 3 "" H 4600 1950 50  0001 C CNN
	1    4600 1950
	0    1    1    0   
$EndComp
$Comp
L power:GNDA #PWR?
U 1 1 5FCB2725
P 5900 3400
AR Path="/5FCAE1D8/5FCB2725" Ref="#PWR?"  Part="1" 
AR Path="/5FCB2725" Ref="#PWR08"  Part="1" 
F 0 "#PWR08" H 5900 3150 50  0001 C CNN
F 1 "GNDA" V 5900 3280 50  0000 R CNN
F 2 "" H 5900 3400 50  0001 C CNN
F 3 "" H 5900 3400 50  0001 C CNN
	1    5900 3400
	0    -1   -1   0   
$EndComp
Text GLabel 5900 3300 2    50   Input ~ 0
LeftIN
Text GLabel 5900 3200 2    50   Input ~ 0
RightIN
$Comp
L Connector:Conn_01x04_Male J4
U 1 1 5FCB5633
P 4140 3780
F 0 "J4" H 3990 3900 50  0000 C CNN
F 1 "Power" H 3960 3770 50  0000 C CNN
F 2 "Useful Modifications:AdaFruit_MPM3610" H 4140 3780 50  0001 C CNN
F 3 "~" H 4140 3780 50  0001 C CNN
	1    4140 3780
	1    0    0    -1  
$EndComp
NoConn ~ 4340 3980
$Comp
L Regulator_Linear:AP2112K-3.3 U1
U 1 1 5FD9B9E5
P 5470 4710
F 0 "U1" H 5470 4970 50  0000 C CNN
F 1 "AP2112K-3.3" H 5930 4460 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 5470 5035 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/AP2112.pdf" H 5470 4810 50  0001 C CNN
	1    5470 4710
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR013
U 1 1 5FD9D63F
P 5170 4710
F 0 "#PWR013" H 5170 4560 50  0001 C CNN
F 1 "+5V" V 5185 4838 50  0000 L CNN
F 2 "" H 5170 4710 50  0001 C CNN
F 3 "" H 5170 4710 50  0001 C CNN
	1    5170 4710
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR012
U 1 1 5FD9E04C
P 5170 4610
F 0 "#PWR012" H 5170 4460 50  0001 C CNN
F 1 "+5V" V 5185 4738 50  0000 L CNN
F 2 "" H 5170 4610 50  0001 C CNN
F 3 "" H 5170 4610 50  0001 C CNN
	1    5170 4610
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FDA2BD7
P 5170 4460
AR Path="/5FCAE1D8/5FDA2BD7" Ref="C?"  Part="1" 
AR Path="/5FDA2BD7" Ref="C11"  Part="1" 
F 0 "C11" H 4920 4470 50  0000 C CNN
F 1 "1µF" H 4930 4580 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5208 4310 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 5170 4460 50  0001 C CNN
F 4 "	399-8000-1-ND" H 5170 4460 50  0001 C CNN "DigiKey ID"
	1    5170 4460
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5FDA4CB9
P 5170 4310
F 0 "#PWR011" H 5170 4060 50  0001 C CNN
F 1 "GND" V 5170 4160 50  0000 R CNN
F 2 "" H 5170 4310 50  0001 C CNN
F 3 "" H 5170 4310 50  0001 C CNN
	1    5170 4310
	-1   0    0    1   
$EndComp
Connection ~ 5170 4610
$Comp
L power:GND #PWR014
U 1 1 5FDA5E51
P 5470 5010
F 0 "#PWR014" H 5470 4760 50  0001 C CNN
F 1 "GND" V 5470 4860 50  0000 R CNN
F 2 "" H 5470 5010 50  0001 C CNN
F 3 "" H 5470 5010 50  0001 C CNN
	1    5470 5010
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5FDA73BA
P 5770 4610
AR Path="/5FCAE1D8/5FDA73BA" Ref="#PWR?"  Part="1" 
AR Path="/5FDA73BA" Ref="#PWR016"  Part="1" 
F 0 "#PWR016" H 5770 4460 50  0001 C CNN
F 1 "+3.3V" V 5785 4738 50  0000 L CNN
F 2 "" H 5770 4610 50  0001 C CNN
F 3 "" H 5770 4610 50  0001 C CNN
	1    5770 4610
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FDA8602
P 5770 4460
AR Path="/5FCAE1D8/5FDA8602" Ref="C?"  Part="1" 
AR Path="/5FDA8602" Ref="C14"  Part="1" 
F 0 "C14" H 5960 4470 50  0000 C CNN
F 1 "1µF" H 5980 4580 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5808 4310 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 5770 4460 50  0001 C CNN
F 4 "	399-8000-1-ND" H 5770 4460 50  0001 C CNN "DigiKey ID"
	1    5770 4460
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5FDA8608
P 5770 4310
F 0 "#PWR015" H 5770 4060 50  0001 C CNN
F 1 "GND" V 5770 4160 50  0000 R CNN
F 2 "" H 5770 4310 50  0001 C CNN
F 3 "" H 5770 4310 50  0001 C CNN
	1    5770 4310
	-1   0    0    1   
$EndComp
Connection ~ 5770 4610
$EndSCHEMATC
