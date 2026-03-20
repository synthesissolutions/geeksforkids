EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
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
L Device:R R5
U 1 1 5F5110EF
P 3800 3200
F 0 "R5" V 3700 3200 50  0000 C CNN
F 1 "20K" V 3800 3200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3730 3200 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RC_Group_51_RoHS_L_11.pdf" H 3800 3200 50  0001 C CNN
F 4 "	311-20.0KCRCT-ND" H 3800 3200 50  0001 C CNN "DigiKey ID"
	1    3800 3200
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 5F511E2A
P 3800 3550
F 0 "R6" V 3900 3550 50  0000 C CNN
F 1 "20K" V 3800 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3730 3550 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RC_Group_51_RoHS_L_11.pdf" H 3800 3550 50  0001 C CNN
F 4 "	311-20.0KCRCT-ND" H 3800 3550 50  0001 C CNN "DigiKey ID"
	1    3800 3550
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 5F512ADD
P 3300 3200
F 0 "C1" V 3050 3200 50  0000 C CNN
F 1 "0.47µF" V 3150 3200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3338 3050 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 3300 3200 50  0001 C CNN
F 4 "399-8099-1-ND" H 3300 3200 50  0001 C CNN "DigiKey ID"
	1    3300 3200
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 5F514F25
P 3300 3550
F 0 "C2" V 3550 3550 50  0000 C CNN
F 1 "0.47µF" V 3450 3550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3338 3400 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 3300 3550 50  0001 C CNN
F 4 "399-8099-1-ND" H 3300 3550 50  0001 C CNN "DigiKey ID"
	1    3300 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	3450 3550 3650 3550
Wire Wire Line
	3450 3200 3650 3200
Wire Wire Line
	4150 3450 4000 3550
Wire Wire Line
	4000 3550 3950 3550
Wire Wire Line
	4250 3550 4000 3550
Connection ~ 4000 3550
Wire Wire Line
	4150 3300 4000 3200
Wire Wire Line
	4000 3200 3950 3200
Wire Wire Line
	4250 3200 4000 3200
Connection ~ 4000 3200
Text GLabel 3150 3200 0    50   Input ~ 0
LeftIN
Text GLabel 3150 3550 0    50   Input ~ 0
RightIN
$Comp
L power:GND1 #PWR052
U 1 1 5F5FE8D5
P 3500 4300
F 0 "#PWR052" H 3500 4050 50  0001 C CNN
F 1 "GND1" V 3450 4100 50  0000 C CNN
F 2 "" H 3500 4300 50  0001 C CNN
F 3 "" H 3500 4300 50  0001 C CNN
	1    3500 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5F60DC42
P 3900 4050
F 0 "R9" V 4000 4050 50  0000 C CNN
F 1 "10K" V 3900 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3830 4050 50  0001 C CNN
F 3 "https://www.seielect.com/catalog/sei-rncp.pdf" H 3900 4050 50  0001 C CNN
F 4 "RNCP0805FTD10K0CT-ND" H 3900 4050 50  0001 C CNN "DigiKey ID"
	1    3900 4050
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR043
U 1 1 5F6D8A96
P 3900 3900
F 0 "#PWR043" H 3900 3750 50  0001 C CNN
F 1 "+3.3V" V 3915 4028 50  0000 L CNN
F 2 "" H 3900 3900 50  0001 C CNN
F 3 "" H 3900 3900 50  0001 C CNN
	1    3900 3900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3500 3900 3500 4300
Wire Wire Line
	3500 4300 3900 4300
Connection ~ 3500 4300
Connection ~ 3900 3900
Wire Wire Line
	3900 4200 3900 4300
Wire Wire Line
	4050 4400 3900 4300
Connection ~ 3900 4300
Wire Wire Line
	3500 3900 3650 3750
Wire Wire Line
	4000 3850 3900 3900
Wire Wire Line
	4550 3550 4750 3650
Wire Wire Line
	4550 3450 4750 3550
Wire Wire Line
	4150 3450 4550 3450
Wire Wire Line
	4550 3300 4750 3400
Wire Wire Line
	4150 3300 4550 3300
Wire Wire Line
	4550 3200 4750 3300
Wire Wire Line
	4850 3850 4000 3850
Wire Wire Line
	4900 3900 4850 3850
Wire Wire Line
	4850 3750 3650 3750
Wire Wire Line
	4900 3800 4850 3750
Connection ~ 4900 4200
Wire Wire Line
	4700 4300 3900 4300
Wire Wire Line
	4900 4200 4700 4300
Wire Wire Line
	4700 4400 4050 4400
Wire Wire Line
	4900 4300 4700 4400
Wire Wire Line
	4650 4450 4900 4450
Wire Wire Line
	4550 4550 4650 4450
Wire Wire Line
	4750 4050 4900 4000
Wire Wire Line
	4450 4050 4750 4050
Wire Wire Line
	4900 4100 4900 4200
Wire Wire Line
	4750 3650 4900 3650
Wire Wire Line
	4750 3550 4900 3550
Wire Wire Line
	4750 3400 4900 3400
Wire Wire Line
	4750 3300 4900 3300
$Comp
L power:+3.3V #PWR046
U 1 1 5F6E11D3
P 4550 4850
F 0 "#PWR046" H 4550 4700 50  0001 C CNN
F 1 "+3.3V" V 4565 4978 50  0000 L CNN
F 2 "" H 4550 4850 50  0001 C CNN
F 3 "" H 4550 4850 50  0001 C CNN
	1    4550 4850
	-1   0    0    1   
$EndComp
Connection ~ 5600 2900
$Comp
L power:+3.3V #PWR049
U 1 1 5F6D9887
P 5600 2900
F 0 "#PWR049" H 5600 2750 50  0001 C CNN
F 1 "+3.3V" H 5615 3073 50  0000 C CNN
F 2 "" H 5600 2900 50  0001 C CNN
F 3 "" H 5600 2900 50  0001 C CNN
	1    5600 2900
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR044
U 1 1 5F6D687C
P 4450 3950
F 0 "#PWR044" H 4450 3800 50  0001 C CNN
F 1 "+3.3V" V 4465 4078 50  0000 L CNN
F 2 "" H 4450 3950 50  0001 C CNN
F 3 "" H 4450 3950 50  0001 C CNN
	1    4450 3950
	0    1    1    0   
$EndComp
$Comp
L Device:R R10
U 1 1 5F61FA59
P 4550 4700
F 0 "R10" V 4650 4700 50  0000 C CNN
F 1 "10K" V 4550 4700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4480 4700 50  0001 C CNN
F 3 "https://www.seielect.com/catalog/sei-rncp.pdf" H 4550 4700 50  0001 C CNN
F 4 "RNCP0805FTD10K0CT-ND" H 4550 4700 50  0001 C CNN "DigiKey ID"
	1    4550 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 4850 7200 4850
Connection ~ 7050 4850
Wire Wire Line
	6900 4850 7050 4850
Text Notes 9450 3600 0    50   ~ 0
+\n-
$Comp
L power:GND1 #PWR045
U 1 1 5F5BDED0
P 4450 4150
F 0 "#PWR045" H 4450 3900 50  0001 C CNN
F 1 "GND1" V 4450 3900 50  0000 C CNN
F 2 "" H 4450 4150 50  0001 C CNN
F 3 "" H 4450 4150 50  0001 C CNN
	1    4450 4150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4500 2200 5050 2200
Connection ~ 4500 2200
Wire Wire Line
	3950 2200 4500 2200
Connection ~ 3950 2200
Wire Wire Line
	3700 2200 3950 2200
$Comp
L Device:C C5
U 1 1 5F58FC50
P 5050 2350
F 0 "C5" H 4850 2300 50  0000 C CNN
F 1 "10µF" H 4850 2400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5088 2200 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1006_X5R_SMD.pdf" H 5050 2350 50  0001 C CNN
F 4 "	399-8012-1-ND" H 5050 2350 50  0001 C CNN "DigiKey ID"
	1    5050 2350
	-1   0    0    1   
$EndComp
$Comp
L power:GND1 #PWR057
U 1 1 5F58FC4A
P 5050 2500
F 0 "#PWR057" H 5050 2250 50  0001 C CNN
F 1 "GND1" H 5055 2327 50  0000 C CNN
F 2 "" H 5050 2500 50  0001 C CNN
F 3 "" H 5050 2500 50  0001 C CNN
	1    5050 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5F58AC3C
P 4500 2350
F 0 "C4" H 4300 2300 50  0000 C CNN
F 1 "10µF" H 4300 2400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4538 2200 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1006_X5R_SMD.pdf" H 4500 2350 50  0001 C CNN
F 4 "	399-8012-1-ND" H 4500 2350 50  0001 C CNN "DigiKey ID"
	1    4500 2350
	-1   0    0    1   
$EndComp
$Comp
L power:GND1 #PWR053
U 1 1 5F58783B
P 4500 2500
F 0 "#PWR053" H 4500 2250 50  0001 C CNN
F 1 "GND1" H 4505 2327 50  0000 C CNN
F 2 "" H 4500 2500 50  0001 C CNN
F 3 "" H 4500 2500 50  0001 C CNN
	1    4500 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND1 #PWR051
U 1 1 5F586250
P 3950 2500
F 0 "#PWR051" H 3950 2250 50  0001 C CNN
F 1 "GND1" H 3955 2327 50  0000 C CNN
F 2 "" H 3950 2500 50  0001 C CNN
F 3 "" H 3950 2500 50  0001 C CNN
	1    3950 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C3
U 1 1 5F58422B
P 3950 2350
F 0 "C3" H 4068 2396 50  0000 L CNN
F 1 "470µF" H 4068 2305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 3988 2200 50  0001 C CNN
F 3 "http://www.rubycon.co.jp/en/catalog/e_pdfs/aluminum/e_zlh.pdf" H 3950 2350 50  0001 C CNN
F 4 "1189-1859-ND" H 3950 2350 50  0001 C CNN "DigiKey ID"
	1    3950 2350
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR?
U 1 1 5F5809E2
P 3300 2200
AR Path="/5F5809E2" Ref="#PWR?"  Part="1" 
AR Path="/5F4AD486/5F5809E2" Ref="#PWR047"  Part="1" 
F 0 "#PWR047" H 3300 2050 50  0001 C CNN
F 1 "+12V" V 3315 2328 50  0000 L CNN
F 2 "" H 3300 2200 50  0001 C CNN
F 3 "" H 3300 2200 50  0001 C CNN
	1    3300 2200
	0    -1   -1   0   
$EndComp
$Comp
L Transistor_FET:AO3401A Q1
U 1 1 5F57597E
P 3500 2300
F 0 "Q1" V 3842 2300 50  0000 C CNN
F 1 "AOD417" V 3751 2300 50  0000 C CNN
F 2 "Useful Modifications:TO-252-2pin3D" H 3700 2225 50  0001 L CIN
F 3 "http://aosmd.com/res/data_sheets/AOD417.pdf" H 3500 2300 50  0001 L CNN
F 4 "	785-1106-1-ND" H 3500 2300 50  0001 C CNN "DigiKey ID"
	1    3500 2300
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x03_Male J14
U 1 1 5F516D0D
P 4250 4050
F 0 "J14" H 4200 4000 50  0000 C CNN
F 1 "Volume" H 4450 3850 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4250 4050 50  0001 C CNN
F 3 "~" H 4250 4050 50  0001 C CNN
	1    4250 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 5F5103EF
P 4400 3550
F 0 "R8" V 4500 3550 50  0000 C CNN
F 1 "20K" V 4400 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4330 3550 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RC_Group_51_RoHS_L_11.pdf" H 4400 3550 50  0001 C CNN
F 4 "	311-20.0KCRCT-ND" H 4400 3550 50  0001 C CNN "DigiKey ID"
	1    4400 3550
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 5F50EFC2
P 4400 3200
F 0 "R7" V 4300 3200 50  0000 C CNN
F 1 "20K" V 4400 3200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4330 3200 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RC_Group_51_RoHS_L_11.pdf" H 4400 3200 50  0001 C CNN
F 4 "	311-20.0KCRCT-ND" H 4400 3200 50  0001 C CNN "DigiKey ID"
	1    4400 3200
	0    1    1    0   
$EndComp
$Comp
L power:GNDA #PWR061
U 1 1 5F50DA8D
P 7050 4850
F 0 "#PWR061" H 7050 4600 50  0001 C CNN
F 1 "GNDA" H 7150 4700 50  0000 R CNN
F 2 "" H 7050 4850 50  0001 C CNN
F 3 "" H 7050 4850 50  0001 C CNN
	1    7050 4850
	1    0    0    -1  
$EndComp
$Comp
L power:GND1 #PWR064
U 1 1 5F50B05E
P 7600 4850
F 0 "#PWR064" H 7600 4600 50  0001 C CNN
F 1 "GND1" V 7600 4650 50  0000 C CNN
F 2 "" H 7600 4850 50  0001 C CNN
F 3 "" H 7600 4850 50  0001 C CNN
	1    7600 4850
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C8
U 1 1 5F5070CC
P 6750 4850
F 0 "C8" V 6600 4850 50  0000 C CNN
F 1 "2.2µF" V 6900 4850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6788 4700 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 6750 4850 50  0001 C CNN
F 4 "399-11941-1-ND" H 6750 4850 50  0001 C CNN "DigiKey ID"
	1    6750 4850
	0    -1   -1   0   
$EndComp
$Comp
L UsefulModifications:MPZ2012S221AT00 FB1
U 1 1 5F50891D
P 7400 4600
F 0 "FB1" H 7400 4200 50  0000 C CNN
F 1 "MPZ2012S221AT00" H 7400 4500 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7400 4600 50  0001 C CNN
F 3 "https://product.tdk.com/info/en/catalog/datasheets/beads_commercial_power_mpz2012_en.pdf" H 7400 4600 50  0001 C CNN
F 4 "445-1568-1-ND" H 7400 4600 50  0001 C CNN "DigiKey ID"
	1    7400 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 4850 6600 4850
$Comp
L Device:C C13
U 1 1 5F4F3A11
P 8650 3600
F 0 "C13" V 8800 3600 50  0000 C CNN
F 1 "470pF" V 8489 3600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8688 3450 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 8650 3600 50  0001 C CNN
F 4 "399-1142-1-ND" H 8650 3600 50  0001 C CNN "DigiKey ID"
	1    8650 3600
	0    1    1    0   
$EndComp
NoConn ~ 6500 4700
NoConn ~ 4900 4650
NoConn ~ 6500 4550
NoConn ~ 6500 4450
NoConn ~ 6500 4350
NoConn ~ 6500 4200
NoConn ~ 6500 4100
NoConn ~ 6500 4000
Connection ~ 6500 3500
Wire Wire Line
	6500 3400 6500 3500
Wire Wire Line
	7150 3300 7300 3300
Connection ~ 7150 3300
Wire Wire Line
	7000 3500 7150 3300
Wire Wire Line
	6500 3500 7000 3500
Wire Wire Line
	7150 3850 7300 3850
Connection ~ 7150 3850
Connection ~ 6500 3650
Wire Wire Line
	7000 3650 7150 3850
Wire Wire Line
	6500 3650 7000 3650
Wire Wire Line
	7000 3850 7150 3850
Wire Wire Line
	7000 3300 7150 3300
Wire Wire Line
	6500 3300 6700 3300
Wire Wire Line
	6500 3750 6500 3650
Wire Wire Line
	7950 3300 8900 3300
Connection ~ 7950 3300
Wire Wire Line
	7950 3600 7950 3300
Connection ~ 8800 3850
Wire Wire Line
	8900 3850 9200 3600
Wire Wire Line
	8800 3850 8900 3850
Wire Wire Line
	8900 3300 9200 3500
Wire Wire Line
	7700 3300 7950 3300
Wire Wire Line
	8400 3600 8500 3600
Connection ~ 8400 3600
Wire Wire Line
	8250 3600 8400 3600
$Comp
L power:GND1 #PWR065
U 1 1 5F4FAF9C
P 8400 3600
F 0 "#PWR065" H 8400 3350 50  0001 C CNN
F 1 "GND1" H 8405 3427 50  0000 C CNN
F 2 "" H 8400 3600 50  0001 C CNN
F 3 "" H 8400 3600 50  0001 C CNN
	1    8400 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 3600 8800 3850
Wire Wire Line
	7700 3850 8800 3850
Wire Wire Line
	6500 3850 6700 3850
$Comp
L Connector:Screw_Terminal_01x02 J?
U 1 1 5F4F76D1
P 9400 3500
AR Path="/5F4F76D1" Ref="J?"  Part="1" 
AR Path="/5F4AD486/5F4F76D1" Ref="J15"  Part="1" 
F 0 "J15" H 9318 3175 50  0000 C CNN
F 1 "Left Speaker" H 9318 3266 50  0000 C CNN
F 2 "Useful Modifications:TerminalBlock_bornier-2_P5.08mm" H 9400 3500 50  0001 C CNN
F 3 "~" H 9400 3500 50  0001 C CNN
	1    9400 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 5F4F23E8
P 8100 3600
F 0 "C12" V 8250 3600 50  0000 C CNN
F 1 "470pF" V 7939 3600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8138 3450 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 8100 3600 50  0001 C CNN
F 4 "399-1142-1-ND" H 8100 3600 50  0001 C CNN "DigiKey ID"
	1    8100 3600
	0    1    1    0   
$EndComp
$Comp
L UsefulModifications:MPZ2012S221AT00 FB3
U 1 1 5F4F1FAD
P 7500 3600
F 0 "FB3" H 7500 3200 50  0000 C CNN
F 1 "MPZ2012S221AT00" H 7500 3491 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7500 3600 50  0001 C CNN
F 3 "https://product.tdk.com/info/en/catalog/datasheets/beads_commercial_power_mpz2012_en.pdf" H 7500 3600 50  0001 C CNN
F 4 "445-1568-1-ND" H 7500 3600 50  0001 C CNN "DigiKey ID"
	1    7500 3600
	1    0    0    -1  
$EndComp
$Comp
L UsefulModifications:MPZ2012S221AT00 FB2
U 1 1 5F4F1648
P 7500 3050
F 0 "FB2" H 7500 2700 50  0000 C CNN
F 1 "MPZ2012S221AT00" H 7500 2941 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7500 3050 50  0001 C CNN
F 3 "https://product.tdk.com/info/en/catalog/datasheets/beads_commercial_power_mpz2012_en.pdf" H 7500 3050 50  0001 C CNN
F 4 "445-1568-1-ND" H 7500 3050 50  0001 C CNN "DigiKey ID"
	1    7500 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 5F4EFD08
P 6850 3850
F 0 "C10" V 7000 3850 50  0000 C CNN
F 1 "0.1µF" V 6689 3850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6888 3700 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 6850 3850 50  0001 C CNN
F 4 "	399-8000-1-ND" H 6850 3850 50  0001 C CNN "DigiKey ID"
	1    6850 3850
	0    1    1    0   
$EndComp
$Comp
L Device:C C9
U 1 1 5F4EF5C5
P 6850 3300
F 0 "C9" V 7000 3300 50  0000 C CNN
F 1 "0.1µF" V 6689 3300 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6888 3150 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 6850 3300 50  0001 C CNN
F 4 "	399-8000-1-ND" H 6850 3300 50  0001 C CNN "DigiKey ID"
	1    6850 3300
	0    1    1    0   
$EndComp
$Comp
L power:GND1 #PWR060
U 1 1 5F4EEB60
P 6700 2350
F 0 "#PWR060" H 6700 2100 50  0001 C CNN
F 1 "GND1" H 6705 2177 50  0000 C CNN
F 2 "" H 6700 2350 50  0001 C CNN
F 3 "" H 6700 2350 50  0001 C CNN
	1    6700 2350
	0    -1   -1   0   
$EndComp
$Comp
L power:GND1 #PWR055
U 1 1 5F4ED503
P 5700 5300
F 0 "#PWR055" H 5700 5050 50  0001 C CNN
F 1 "GND1" H 5705 5127 50  0000 C CNN
F 2 "" H 5700 5300 50  0001 C CNN
F 3 "" H 5700 5300 50  0001 C CNN
	1    5700 5300
	1    0    0    -1  
$EndComp
Connection ~ 5800 2700
Wire Wire Line
	5800 2700 6050 2700
Connection ~ 5800 2900
Wire Wire Line
	5800 2900 5800 2700
$Comp
L Device:C C7
U 1 1 5F4EBC99
P 6550 2350
F 0 "C7" V 6298 2350 50  0000 C CNN
F 1 "0.1µF" V 6389 2350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6588 2200 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 6550 2350 50  0001 C CNN
F 4 "	399-8000-1-ND" H 6550 2350 50  0001 C CNN "DigiKey ID"
	1    6550 2350
	0    1    1    0   
$EndComp
$Comp
L Device:C C6
U 1 1 5F4EB6A2
P 6200 2700
F 0 "C6" V 5948 2700 50  0000 C CNN
F 1 "0.1µF" V 6039 2700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6238 2550 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1002_X7R_SMD.pdf" H 6200 2700 50  0001 C CNN
F 4 "	399-8000-1-ND" H 6200 2700 50  0001 C CNN "DigiKey ID"
	1    6200 2700
	0    1    1    0   
$EndComp
$Comp
L power:GND1 #PWR058
U 1 1 5F4EA408
P 6350 2700
F 0 "#PWR058" H 6350 2450 50  0001 C CNN
F 1 "GND1" H 6355 2527 50  0000 C CNN
F 2 "" H 6350 2700 50  0001 C CNN
F 3 "" H 6350 2700 50  0001 C CNN
	1    6350 2700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6000 2900 6100 2900
Connection ~ 6000 2900
Wire Wire Line
	5900 2900 6000 2900
Connection ~ 5900 2900
Wire Wire Line
	5800 2900 5900 2900
Wire Wire Line
	5500 2900 5600 2900
Connection ~ 5500 2900
Wire Wire Line
	5400 2900 5500 2900
Connection ~ 5400 2900
Wire Wire Line
	5300 2900 5400 2900
Wire Wire Line
	6150 5300 6250 5300
Connection ~ 6150 5300
Wire Wire Line
	6050 5300 6150 5300
Connection ~ 6050 5300
Wire Wire Line
	5950 5300 6050 5300
Connection ~ 5950 5300
Wire Wire Line
	5850 5300 5950 5300
Connection ~ 5850 5300
Wire Wire Line
	5700 5300 5850 5300
Connection ~ 5700 5300
Wire Wire Line
	5550 5300 5700 5300
Connection ~ 5550 5300
Wire Wire Line
	5450 5300 5550 5300
Connection ~ 5450 5300
Wire Wire Line
	5350 5300 5450 5300
Connection ~ 5350 5300
Wire Wire Line
	5250 5300 5350 5300
Connection ~ 5250 5300
Wire Wire Line
	5150 5300 5250 5300
$Comp
L UsefulModifications:MAX9744 U4
U 1 1 5F4E616F
P 5700 3900
F 0 "U4" H 5700 4150 50  0000 C CNN
F 1 "MAX9744" H 5700 3900 50  0000 C CNN
F 2 "Useful Modifications:max9744eth&plus_Mod" H 5700 4150 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX9744.pdf" H 5700 4150 50  0001 C CNN
F 4 "MAX9744ETH+-ND" H 5700 3900 50  0001 C CNN "DigiKey ID"
	1    5700 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 2200 5350 2200
Connection ~ 5050 2200
Wire Wire Line
	5350 2200 5800 2350
Wire Wire Line
	5800 2350 5800 2700
Wire Wire Line
	5800 2350 6400 2350
Connection ~ 5800 2350
$Comp
L power:GND #PWR0105
U 1 1 5F59C02E
P 3500 2500
F 0 "#PWR0105" H 3500 2250 50  0001 C CNN
F 1 "GND" H 3505 2327 50  0000 C CNN
F 2 "" H 3500 2500 50  0001 C CNN
F 3 "" H 3500 2500 50  0001 C CNN
	1    3500 2500
	0    -1   -1   0   
$EndComp
$Comp
L power:GND1 #PWR0106
U 1 1 5F59C7EF
P 3500 2500
F 0 "#PWR0106" H 3500 2250 50  0001 C CNN
F 1 "GND1" H 3505 2327 50  0000 C CNN
F 2 "" H 3500 2500 50  0001 C CNN
F 3 "" H 3500 2500 50  0001 C CNN
	1    3500 2500
	0    1    1    0   
$EndComp
Connection ~ 3500 2500
$EndSCHEMATC
