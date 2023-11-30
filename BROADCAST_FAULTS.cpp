//#include <Serial_CAN_Module_2.h>
//#include <SoftwareSerial.h>
//#include <Arduino.h>
#include <iostream>
#include <BROADCAST_FAULTS.h>
//#include <C:\adam\utht\extra low level\BROADCAST_FAULTS.h>
#include <bitset>
#include <vector>

using namespace std;

PM100_FAULT_CODE FAULT_CODE_ARRAY[65] = { 
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
	
};


std::ostream& operator<<(std::ostream& lhs, PM100_FAULT_CODE fault) {
	
	switch(fault) {
        
		case Hardware_Gate_Desaturation_Fault: lhs << "Hardware_Gate_Desaturation_Fault"; break;
		case HW_Over_current_Fault: lhs << "HW_Over_current_Fault"; break;
		case Accelerator_Shorted: lhs << "Accelerator_Shorted"; break;
		case Accelerator_Open: lhs << "Accelerator_Open"; break;
		case Current_Sensor_Low: lhs << "Current_Sensor_Low"; break;
		case Current_Sensor_High: lhs << "Current_Sensor_High"; break;
		case Module_Temperature_Low: lhs << "Module_Temperature_Low"; break;
		case Module_Temperature_High: lhs << "Module_Temperature_High"; break;
		case Control_PCB_Temperature_Low: lhs << "Control_PCB_Temperature_Low"; break;
		case Control_PCB_Temperature_High: lhs << "Control_PCB_Temperature_High"; break;
		case Gate_Drive_PCB_Temperature_Low: lhs << "Gate_Drive_PCB_Temperature_Low"; break;
		case Gate_Drive_PCB_Temperature_High: lhs << "Gate_Drive_PCB_Temperature_High"; break;
		case Sense_Voltage_Low_5V: lhs << "Sense_Voltage_Low_5V"; break;
		case Sense_Voltage_High_5V: lhs << "Sense_Voltage_High_5V"; break;
		case Sense_Voltage_Low_12V: lhs << "Sense_Voltage_Low_12V"; break;
		case Sense_Voltage_High_12V: lhs << "Sense_Voltage_High_12V"; break;
		case Sense_Voltage_Low_2_5V: lhs << "Sense_Voltage_Low_2_5V"; break;
		case Sense_Voltage_High_2_5V: lhs << "Sense_Voltage_High_2_5V"; break;
		case Sense_Voltage_Low_1_5V: lhs << "Sense_Voltage_Low_1_5V"; break;
		case Sense_Voltage_High_1_5V: lhs << "Sense_Voltage_High_1_5V"; break;
		case DC_Bus_Voltage_High: lhs << "DC_Bus_Voltage_High"; break;
		case DC_Bus_Voltage_Low: lhs << "DC_Bus_Voltage_Low"; break;
		case Pre_charge_Timeout: lhs << "Pre_charge_Timeout"; break;
		case Pre_charge_Voltage_Failure: lhs << "Pre_charge_Voltage_Failure"; break;
		case EEPROM_Checksum_Invalid: lhs << "EEPROM_Checksum_Invalid"; break;
		case EEPROM_Data_Out_of_Range: lhs << "EEPROM_Data_Out_of_Range"; break;
		case EEPROM_Update_Required: lhs << "EEPROM_Update_Required"; break;
		case RESERVED_1: lhs << "RESERVED_1"; break;
		case RESERVED_2: lhs << "RESERVED_2"; break;
		case RESERVED_3: lhs << "RESERVED_3"; break;
		case Brake_Shorted: lhs << "Brake_Shorted"; break;
		case Brake_Open: lhs << "Brake_Open"; break;
		case Motor_Over_speed_Fault: lhs << "Motor_Over_speed_Fault"; break;
		case Over_current_Fault: lhs << "Over_current_Fault"; break;
		case Over_voltage_Fault: lhs << "Over_voltage_Fault"; break;
		case Inverter_Over_temperature_Fault: lhs << "Inverter_Over_temperature_Fault"; break;
		case Accelerator_Input_Shorted_Fault: lhs << "Accelerator_Input_Shorted_Fault"; break;
		case Accelerator_Input_Open_Fault: lhs << "Accelerator_Input_Open_Fault"; break;
		case Direction_Command_Fault: lhs << "Direction_Command_Fault"; break;
		case Inverter_Response_Time_out_Fault: lhs << "Inverter_Response_Time_out_Fault"; break;
		case Hardware_Gate_Desaturation_RUN_Fault: lhs << "Hardware_Gate_Desaturation_RUN_Fault"; break;
		case Hardware_Over_current_Fault: lhs << "Hardware_Over_current_Fault"; break;
		case Under_voltage_Fault: lhs << "Under_voltage_Fault"; break;
		case CAN_Command_Message_Lost_Fault: lhs << "CAN_Command_Message_Lost_Fault"; break;
		case Motor_Over_temperature_Fault: lhs << "Motor_Over_temperature_Fault"; break;
		case RESERVED_4: lhs << "RESERVED_4"; break;
		case RESERVED_5: lhs << "RESERVED_5"; break;
		case RESERVED_6: lhs << "RESERVED_6"; break;
		case Brake_Input_Shorted_Fault: lhs << "Brake_Input_Shorted_Fault"; break;
		case Brake_Input_Open_Fault: lhs << "Brake_Input_Open_Fault"; break;
		case Module_A_Over_temperature_Fault: lhs << "Module_A_Over_temperature_Fault"; break;
		case Module_B_Over_temperature_Fault: lhs << "Module_B_Over_temperature_Fault"; break;
		case Module_C_Over_temperature_Fault: lhs << "Module_C_Over_temperature_Fault"; break;
		case PCB_Over_temperature_Fault: lhs << "PCB_Over_temperature_Fault"; break;
		case Gate_Drive_Board_1_Over_temperature_Fault: lhs << "Gate_Drive_Board_1_Over_temperature_Fault"; break;
		case Gate_Drive_Board_2_Over_temperature_Fault: lhs << "Gate_Drive_Board_2_Over_temperature_Fault"; break;
		case Gate_Drive_Board_3_Over_temperature_Fault: lhs << "Gate_Drive_Board_3_Over_temperature_Fault"; break;
		case Current_Sensor_Fault: lhs << "Current_Sensor_Fault"; break;
		case RESERVED_7: lhs << "RESERVED_7"; break;
		case Hardware_Over_Voltage_Fault: lhs << "Hardware_Over_Voltage_Fault"; break;
		case RESERVED_8: lhs << "RESERVED_8"; break;
		case RESERVED_9: lhs << "RESERVED_9"; break;
		case Resolver_Not_Connected: lhs << "Resolver_Not_Connected"; break;
		case Inverter_Discharge_Active: lhs << "Inverter_Discharge_Active"; break;
		case NOT_FAULT_CAN_MSSG: lhs << "ERROR - This CAN Message is NOT for FAULT CODES!"; break;
	}
    
	return lhs;
}


int return_fault_index_val( PM100_FAULT_CODE fault ){
	
	int index_value = fault;
	return index_value;
}

 
 
std::vector<PM100_FAULT_CODE> broadcast_message::read_fault_codes_VER_2( int CAN_mssg[9] ){

    	//extract the CAN ID & define return vector of fault codes
	int CAN_ID = CAN_mssg[0];
	vector<PM100_FAULT_CODE> faults_found;
	PM100_FAULT_CODE fault;
	
    	//check if CAN message is FAULT message
	if( CAN_ID != 0x0AB ){
		cout << NOT_FAULT_CAN_MSSG;
		faults_found.push_back( NOT_FAULT_CAN_MSSG );
	}
	else if( CAN_ID == 0x0AB ){
		
		int fault_code_index = 0; //var used for indexing fault code array

        	//here we'll loop 8 times, analyze each CAN data byte
		for( int i = 1; i < 9; i++  ){
			
			int byte_i = CAN_mssg[i];
			cout << "Byte " << i << " Faults: " << endl;

			//vars to check each bit of current byte
			int current_bit;
			int int_to_binary = byte_i;
			for( int i = 0; i < 8; i++ ){

				current_bit = int_to_binary % 2;
				int_to_binary = int_to_binary / 2;
                
				if( current_bit ){
				    fault = FAULT_CODE_ARRAY[ fault_code_index + i ];
				    cout << "    " << fault << " -- Fault #" << return_fault_index_val( fault ) << endl;
						faults_found.push_back( fault );
				}
            		}

            		fault_code_index = fault_code_index + 8;
		}
		
	}

	return faults_found;
}






int main(){
	
	cout << "----------------------------------------------------------------" << endl;
	cout << "-                                                              -" << endl;
	cout << "-                         CAN PM100                            -" << endl;
	cout << "-                 Fault Code Function Testing                  -" << endl;
	cout << "-                                                              -" << endl;
	cout << "-                                                              -" << endl;
	cout << "-                                                              -" << endl;
	cout << "----------------------------------------------------------------\n" << endl;
	
	cout << "< Hello there! Here we'll test out reading Fault Codes from the PM100 >" << endl;
	cout << "<                                                                     >" << endl;
	cout << "<                                                                     >" << endl;
	cout << "<                                                                     >\n" << endl;
	
	cout << "<                  The CAN message we're testing is:                  >" << endl;
	
	broadcast_message testing_class;
    	int test_message_2[9] = { 0x0AB, 128, 32, 0, 0, 0, 0, 2, 0 };
	
	cout << "<                  {";
	for ( int i = 0; i < 8; i++ ){
		/*
		if(i == 0){
			cout << " 0x0" << hex << test_message_2[i] << ",";
			continue;
		}
		*/
		cout << " " << test_message_2[i] << ",";
	}
	cout << " }\n" << endl;
	
	
   
	vector<PM100_FAULT_CODE> returned_faults_vector;
	returned_faults_vector = testing_class.read_fault_codes_VER_2( test_message_2 );
   
   
   
	
	
}

