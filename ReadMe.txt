FMI Intelligent Identification System R/M Device Software
1 Software instructions
1.1 Open the software interface as follows
 

1.2 Open the device manager of your computer -Find（COM and LPT）
 
Choose COM7 Open Serial Port，Choose default BoundRate115200，Click ON。Show as follows
 
1.3 Click CheckBox Auto monitoring monitor each channel’s status including ETDLC and ETMPO. Refresh every 2s. Where Blue represents the chip object inserted normally；Yellow represents the inserted chip housing without a single bus EEPROM；RED indicates that the chip housing is not inserted.
 
1.4 Write EEPROM information in the existing chip housing
The message format is as follows：
The length of the message contains 0~32bytes.
Choose Block number,each block can write 32Bytes, 112Bytes in total；
For example：Select the channel that is correctly inserted into the chip housing。
Send：123456789ABCDEF		Click		Write2 or Write all
 
Receive:123456789ABCDEF0000000000000000000000000000000000000000000000000（Automatically fill 00 storage, and Block NO is automatically selected as 1）
 
1.5 Write RFID information，the method is as above.
Select the channel that is correctly inserted into the chip housing , and check the checkbox after RFID。
The message format is as follows：
The length of the message contains 0~32 bytes
Choose Block number,each block can write 32Bytes, 128Bytes in total；
For example：
Send：FEDCBA9876543212345，Click	Write2 or Write all
 
Receive：FEDCBA9876543212345000000000000000000000000000000000000000000000
 
1.6 Receiving。Select the correct channel number and chip housing, check the RFID you want to display, and select Block NO that needs to display 32Bytes.Click Read1/Read2/Read3/Read4/Read5 or One-click reading.
For example：
 
Click the Button One-click reading
 
Show all content,The returned messages will display the received report in real time.
1.7.Log
In the software directory, a log.txt file will be generated, which will record all the data frames sent to the device and received from the device.
For example：
 
2 Software designed data frame format
2.1 Message format
SD1	LE	LER	SD2	DA	SA	FC	DATA	FCS	ED
2.2 Message field definition
Name	ID	Length	Description
Frame start	SD2	8-bit unsigned number, 1 byte	68H
Data Length	LE	8-bit unsigned number, 1 byte	Data length in bytes, range 4-249
Data Length	LEr	8-bit unsigned number, 1 byte	Same as LE, discard this frame when LE is not equal to LEr
Frame start	SD2	8-bit unsigned number, 1 byte	68H
Destination address	DA	8-bit unsigned number, 1 byte	16H
source address	SA	8-bit unsigned number, 1 byte	19H
Control field	FC	8-bit unsigned number, 1 byte	Use this section to distinguish between different frame types
Data field	DATA UNIT	Variable length,LE-3	Unit is byte
Checksum	FCS	8-bit unsigned number, 1 byte	From the DA, to the end of the FCS (not included) for the sum check
End of frame	ED	8-bit unsigned number, 1 byte	16H

2.3 Detailed instruction
2.3.1 Serial port parameter reading：
Request frame control character：	0XC1
Response frame control character：	0XE1
Data field：			0XFF
Example of a frame：
[Sengding]68 04 04 68 16 19 C1 FF EF 16  
[Receiving]68 04 04 68 16 19 E1 40 50 16 
2.3.2 Serial port parameter setting：
Request frame control character：		0XC2
Response frame control character：		0XE1
Data field：1 byte, the high 4 bits are the baud rate control characters, and the low 4 bits are the status automatic reporting characters.
The high four bits are 0XH, 1XH, 2XH, 3XH, and 4XH, which represent the baud rate of 9600 bps, 19200 bps, 38400 bps, 57600 bps, and 115200 bps, respectively.
Example of a frame：
Sending:680404681619C2403116
Receiving:680404681619C2403116
2.3.3 Plug sensing status reading：
Request frame control character：		0XC3
Response frame control character：		0XE2
Data field:			OXFF
Example of a frame：
Sending:680404681619C3FFF116
Receiving:680D0D681619E2A553A5A5A5BAB5B5B5B58616
Data field definition: Control word 0XE2. The DLC1~5 status and the MPO1~5 status are then displayed. 0XAA means DLC and a clip are inserted, 0XA5 means DLC is not inserted; 0XBA means MPO and a clip are inserted, 0XB5 means MPO is not inserted.0XA9 means only a clip and no DLC cable inserted. 0XB9 means only a clip and no MPO cable inserted.
2.3.4 Plug EEPROM data reading：
Request frame control character：		0XC4
Response frame control character：		0XE3
Data field：One byte, the high four bits take the value 0XH/1XH/2XH/3XH, which represents the data block number. The low four bits take the value 1-A, which represents the channel number to be read. 1-5 corresponds to DLC1-DLC5, and 6-A corresponds to MPO1-MPO5.
Example of a frame：
Sending:680404681619C4160916
Receiving:682424681619E316123456789ABCDEF00000000000000000000000000000000000000000000000006016
2.3.5 Plug EEPROM data write：
Request frame control character：		0XC5
Response frame control character：		0XE3
Data field: 33 bytes, 1 channel and block number control, one byte, the high four bits are 0XH/1XH/2XH/3XH, which represents the data block number. The low four bits take the value 1-A, which represents the channel number to be read. 1-5 corresponds to DLC1-DLC5, and 6-A corresponds to MPO1-MPO5. 32 data bytes.
Example of a frame：
Sending:682424681619C526987654321FEDCBA00000000000000000000000000000000000000
000000000002516
Receiving:682424681619E326987654321FEDCBA00000000000000000000000000000000000000000000000004316
2.3.6 Plug RFTAG data reading：
Request frame control character：		0XC6
Response frame control character：		0XE4
Data field:one byte，the high four bits take the value 0XH/1XH/2XH/3XH, which represents the data block number. The low four bits take the value 1-5, which represents the channel number to be read. 1-5 corresponds to Channel1~Channel5.
Example of a frame：
Sending:680404681619C6221716
Receiving:682424681619E422CCCC000000000000000000000000000000000000000000000000000000000000CD16
2.3.7 Plug RFTAG data write：
Request frame control character：		0XC7
Response frame control character：		0XE4
Data field: 33 bytes, 1 channel and block number control, one byte, the high four bits are 0XH/1XH/2XH/3XH, which represents the data block number. The low four bits take the value 1-5, which represents the channel number to be read. 1-5 corresponds to Channel1-Channel5. 32 data bytes.
Example of a frame：
Sending:682424681619C721FEDCBA987654321234500000000000000000000000000000000
0000000000000D516
Receiving:682424681619E421FEDCBA9876543212345000000000000000000000000000000000000000000000F216
2.3.8 Error status upload：
Response frame control character：		0XEF
Example of a frame：
[Receiving 1]68 04 04 68 16 19 EF ERR FE 16
[Receiving  2]68 05 05 68 16 19 EF ERR FE 16
Data field:
ERR code interpretation	Channel+0X51	Channel+0X52	Channel+0X53	Channel+0X54	0XFF
	NO ETDLC	NO ETMPO	DLC without EEPROM	MPO without EEPROM	Communication Error or No RFID
Example of a frame1：680505681619EF07527716
Example of a frame2：680505681619EF03517216
Example of a frame3：680404681619EFFF1D16



