#ifndef BROADCAST_FAULTS_H
#define BROADCAST_FAULTS_H

#include <C:\adam\utht\extra low level\COMMAND_MESSAGE.h>
//#include <COMMAND_MESSAGE.h>
#include <iostream>
#include <vector>
//types of CAN messages
typedef enum fault_code {
	//POST FAULTS
	//Byte 0
	Hardware_Gate_Desaturation_Fault,
	HW_Over_current_Fault,
	Accelerator_Shorted,
	Accelerator_Open,
	Current_Sensor_Low,
	Current_Sensor_High,
	Module_Temperature_Low,
	Module_Temperature_High,
	//Byte 1
	Control_PCB_Temperature_Low,
	Control_PCB_Temperature_High,
	Gate_Drive_PCB_Temperature_Low,
	Gate_Drive_PCB_Temperature_High,
	Sense_Voltage_Low_5V,
	Sense_Voltage_High_5V,
	Sense_Voltage_Low_12V,
	Sense_Voltage_High_12V,
	//Byte 2
	Sense_Voltage_Low_2_5V,
	Sense_Voltage_High_2_5V,
	Sense_Voltage_Low_1_5V,
	Sense_Voltage_High_1_5V,
	DC_Bus_Voltage_High,
	DC_Bus_Voltage_Low,
	Pre_charge_Timeout,
	Pre_charge_Voltage_Failure,
	//Byte 3
	EEPROM_Checksum_Invalid,
	EEPROM_Data_Out_of_Range,
	EEPROM_Update_Required,
	RESERVED_1,
	RESERVED_2,
	RESERVED_3,
	Brake_Shorted,
	Brake_Open,
	//Byte 4
	//RUN FAULTS
	Motor_Over_speed_Fault,
	Over_current_Fault,
	Over_voltage_Fault,
	Inverter_Over_temperature_Fault,
	Accelerator_Input_Shorted_Fault,
	Accelerator_Input_Open_Fault,
	Direction_Command_Fault,
	Inverter_Response_Time_out_Fault,
	//Byte 5
	Hardware_Gate_Desaturation_RUN_Fault,
	Hardware_Over_current_Fault,
	Under_voltage_Fault,
	CAN_Command_Message_Lost_Fault,
	Motor_Over_temperature_Fault,
	RESERVED_4,
	RESERVED_5,
	RESERVED_6,
	//Byte 6
	Brake_Input_Shorted_Fault,
	Brake_Input_Open_Fault,
	Module_A_Over_temperature_Fault,
	Module_B_Over_temperature_Fault,
	Module_C_Over_temperature_Fault,
	PCB_Over_temperature_Fault,
	Gate_Drive_Board_1_Over_temperature_Fault,
	Gate_Drive_Board_2_Over_temperature_Fault,
	//Byte 7
	Gate_Drive_Board_3_Over_temperature_Fault,
	Current_Sensor_Fault,
	RESERVED_7,
	Hardware_Over_Voltage_Fault,
	RESERVED_8,
	RESERVED_9,
	Resolver_Not_Connected,
	Inverter_Discharge_Active,
	
	//Finally, error if the CAN mssg is NOT for fault codes
	NOT_FAULT_CAN_MSSG
		
  
} PM100_FAULT_CODE;



using namespace std;



class broadcast_message{

  public:
  
    message_type command_message;
	
	friend ostream& operator<<( ostream& lhs, PM100_FAULT_CODE fault );
    
    friend int return_fault_index_val( PM100_FAULT_CODE fault );
    
    vector<PM100_FAULT_CODE> read_fault_codes_VER_2( int CAN_mssg[9] );
    
    
	
	



  
};

#endif
