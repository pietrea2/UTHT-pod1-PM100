#ifndef BROADCAST_MESSAGE_H
#define BROADCAST_MESSAGE_H

//#include <C:\adam\utht\extra low level\COMMAND_MESSAGE.h>
#include <COMMAND_MESSAGE.h>
#include <iostream>
#include <vector>

// Reference 0x0AA - Internal States, Byte #0,1
typedef enum vsm_state
{
    VSM_START,
    PRE_CHARGE_INIT,
    PRE_CHARGE_ACTIVE,
    PRE_CHARGE_COMPLETE,
    VSM_WAIT,
    VSM_READY,
    MOTOR_RUNNING,
    BLINK_FAULT_CODE,
    SHUTDOWN_IN_PROGRESS = 14,
    RECYCLE_POWER,
    NOT_A_VSM_STATE
} vsm_state;

// Reference 0x0AA - Internal States, Byte #2
typedef enum inverter_state
{
    POWER_ON,
    STOP,
    OPEN_LOOP,
    CLOSED_LOOP,
    WAIT,
    IDLE_RUN = 8,
    IDLE_STOP,
    NOT_AN_INVERTER_STATE = 13
} inverter_state;

// Reference Param Address 148
typedef enum can_active_messages_lo_word
{
    // Data Byte 4
    TEMPERATURE_1 = 0x0001,
    TEMPERATURE_2 = 0x0002,
    TEMPERATURE_3 = 0x0004,
    ANALOG_INPUT_VOLTAGES = 0x0008,
    DIGITAL_INPUT_STATUS = 0x0010,
    MOTOR_POSITION_INFORMATION = 0x0020,
    CURRENT_INFORMATION = 0x0040,
    VOLTAGE_INFORMATION = 0x0080,
    // Data Byte 5
    FLUX_INFORMATION = 0x0100,
    INTERNAL_VOLTAGES = 0x0200,
    INTERNAL_STATES = 0x0400,
    FAULT_CODES = 0x0800,
    TORQUE_AND_TIMER_INFORMATION = 0x1000,
    MOD_INDEX_FLUX_WEAKENING_OUTPUT_INFO = 0x2000,
    FIRMWARE_INFORMATION = 0x4000,
    DIAG_DATA = 0x8000
} can_active_messages_lo_word;

// Reference Param Address 148, should always be enabled (default)
typedef enum can_active_messages_hi_word
{
    // Data Byte 6
    SLAVE_MODE_COMMAND_MESSAGE = 6,
    BMS_COMMAND_MESSAGE,
    // Data Byte 7
    OBD2_GENERAL_QUERY,
    OBD2_SPECIFIC_QUERY,
    OBD2_RESPONSE,
    U2C_TX_MESSAGE,
    U2C_RX_MESSAGE,
    PARAMETER_RESPONSE_MESAGE,
    PARAMETER_COMMAND_MESSAGE,
    CAN_COMMAND_MESSAGE
} can_active_messages_hi_word;

//All types of Fault Codes
typedef enum fault_code 
{
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



class broadcast_message
{
public:
    message_type broadcast_message;

    vsm_state read_vsm_state(int message_arr[9]);
    friend std::ostream &operator<<(std::ostream &lhs, vsm_state state);
    friend int return_vsm_state_val(vsm_state state);

    inverter_state read_inverter_state(int message_arr[9]);
    friend std::ostream &operator<<(std::ostream &lhs, inverter_state state);
    friend int return_inverter_state_val(inverter_state state);

    void disable_broadcast_message(int CAN_mssg[9], int listOfMsgs);
    
    vector<PM100_FAULT_CODE> read_fault_codes_VER_2( int CAN_mssg[9] );
    friend ostream& operator<<( ostream& lhs, PM100_FAULT_CODE fault );
    friend int return_fault_index_val( PM100_FAULT_CODE fault );
};

#endif
