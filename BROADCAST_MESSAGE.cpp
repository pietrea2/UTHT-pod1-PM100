#include <iostream>
#include <bitset>
#include <vector>
//#include <C:\\adam\\utht\\extra low level\\BROADCAST_MESSAGE.h>
#include <BROADCAST_MESSAGE.h>

using namespace std;

std::ostream &operator<<(std::ostream &lhs, vsm_state state)
{
    switch (state) {
        case VSM_START: lhs << "VSM Start State"; break;
        case PRE_CHARGE_INIT: lhs << "Pre-Charge Init State"; break;
        case PRE_CHARGE_ACTIVE: lhs << "Pre-Charge Active State"; break;
        case PRE_CHARGE_COMPLETE: lhs << "Pre-Charge Complete State"; break;
        case VSM_WAIT: lhs << "VSM Wait State"; break;
        case VSM_READY: lhs << "VSM Ready State"; break;
        case MOTOR_RUNNING: lhs << "Motor Running State"; break;
        case BLINK_FAULT_CODE: lhs << "Blink Fault Code State"; break;
        case SHUTDOWN_IN_PROGRESS: lhs << "Shutdown in Process"; break;
        case RECYCLE_POWER: lhs << "Recycle Power State"; break;
        case NOT_A_VSM_STATE: lhs << "ERROR - NOT a VSM State - Invalid Value"; break;
    }

    return lhs;
}

int return_vsm_state_val(vsm_state state)
{
    int index_value = state;
    return index_value;
}

vsm_state broadcast_message::read_vsm_state(int CAN_mssg[9])
{
    vsm_state state;

    if (CAN_mssg[0] != 0x0AA)
    {
        cout << "Message CAN ID is not 0x0AA, this is NOT a VSM message" << endl;
        return state = NOT_A_VSM_STATE;
    }

    switch (CAN_mssg[2])
    {
    case 0:
        cout << "VSM State: VSM Start State";
        state = VSM_START; break;
    case 1:
        cout << "VSM State: Pre-charge Init State";
        state = PRE_CHARGE_INIT; break;
    case 2:
        cout << "VSM State: Pre-charge Active State";
        state = PRE_CHARGE_ACTIVE;  break;
    case 3:
        cout << "VSM State: Pre-charge Complete State";
        state = PRE_CHARGE_COMPLETE; break;
    case 4:
        cout << "VSM State: VSM Wait State";
        state = VSM_WAIT; break;
    case 5:
        cout << "VSM State: VSM Ready State";
        state = VSM_READY; break;
    case 6:
        cout << "VSM State: Motor Running State";
        state = MOTOR_RUNNING; break;
    case 7:
        cout << "VSM State: Blink Fault Code State";
        state = BLINK_FAULT_CODE; break;
    case 14:
        cout << "VSM State: Shutdown in Process";
        state = SHUTDOWN_IN_PROGRESS; break;
    case 15:
        cout << "VSM State: Recycle Power State";
        state = RECYCLE_POWER; break;
    default:
        cout << "Invalid VSM State";
        state = NOT_A_VSM_STATE;
    }

    return state;
}

std::ostream &operator<<(std::ostream &lhs, inverter_state state)
{
    switch (state) {
        case POWER_ON: lhs << "Power On State"; break;
        case STOP: lhs << "Stop State"; break;
        case OPEN_LOOP: lhs << "Open Loop State"; break;
        case CLOSED_LOOP: lhs << "Closed Loop State"; break;
        case WAIT: lhs << "Wait State"; break;
        case IDLE_RUN: lhs << "Idle Run State"; break;
        case IDLE_STOP: lhs << "Idle Stop State"; break;
        case NOT_AN_INVERTER_STATE: lhs << "ERROR - NOT an Inverter State - Invalid Value"; break;
    }

    return lhs;
}

int return_inverter_state_val(inverter_state state)
{
    int index_value = state;
    return index_value;
}

inverter_state broadcast_message::read_inverter_state(int CAN_mssg[9])
{
    inverter_state state;

    if (CAN_mssg[0] != 0x0AA)
    {
        cout << "Message CAN ID is not 0xAA" << endl;
        return state = NOT_AN_INVERTER_STATE;
    }

    switch (CAN_mssg[3])
    {
    case 0:
        cout << "Inverter State: Power on State" << endl;
        state = POWER_ON; break;
    case 1:
        cout << "Inverter State: Stop State" << endl;
        state = STOP; break;
    case 2:
        cout << "Inverter State: Open Loop State" << endl;
        state = OPEN_LOOP; break;
    case 3:
        cout << "Inverter State: Closed Loop State" << endl;
        state = CLOSED_LOOP; break;
    case 4:
        cout << "Inverter State: Wait State" << endl;
        state = WAIT; break;
    case 8:
        cout << "Inverter State: Idle Run State" << endl;
        state = IDLE_RUN; break;
    case 9:
        cout << "Inverter State: Idle Stop State" << endl;
        state = IDLE_STOP; break;
    default:
        cout << "Invalid Inverter State" << endl;
        state = NOT_AN_INVERTER_STATE; break;
    }

    return state;
}

/* Disable one or more messages at a time
 * Example usage: disable_broadcast_message(test_msg, TEMPERATURE_2 | CURRENT_INFORMATION | DIAG_DATA);
 */
void disable_broadcast_message(int CAN_mssg[9], int listOfMsgs)
{
    if (CAN_mssg[0] != 0x0C1) // CAN ID
    {
        cout << "Message CAN Address is not 0x0C1" << endl;
        return;
    }

    if (CAN_mssg[1] != 148) // Data Byte 0
    {
        cout << "Message Parameter Address is not 148" << endl;
        return;
    }

    int loWord = (CAN_mssg[6] << 8) | CAN_mssg[5]; // loWord = [6] concatenated with [5]

    if ((TEMPERATURE_1 & listOfMsgs) == TEMPERATURE_1)
        loWord &= ~(1U);
    if ((TEMPERATURE_2 & listOfMsgs) == TEMPERATURE_2)
        loWord &= ~(1U << 1);
    if ((TEMPERATURE_3 & listOfMsgs) == TEMPERATURE_3)
        loWord &= ~(1U << 2);
    if ((ANALOG_INPUT_VOLTAGES & listOfMsgs) == ANALOG_INPUT_VOLTAGES)
        loWord &= ~(1U << 3);
    if ((DIGITAL_INPUT_STATUS & listOfMsgs) == DIGITAL_INPUT_STATUS)
        loWord &= ~(1U << 4);
    if ((MOTOR_POSITION_INFORMATION & listOfMsgs) == MOTOR_POSITION_INFORMATION)
        loWord &= ~(1U << 5);
    if ((CURRENT_INFORMATION & listOfMsgs) == CURRENT_INFORMATION)
        loWord &= ~(1U << 6);
    if ((VOLTAGE_INFORMATION & listOfMsgs) == VOLTAGE_INFORMATION)
        loWord &= ~(1U << 7);

    if ((FLUX_INFORMATION & listOfMsgs) == FLUX_INFORMATION)
        loWord &= ~(1U << 8);
    if ((INTERNAL_VOLTAGES & listOfMsgs) == INTERNAL_VOLTAGES)
        loWord &= ~(1U << 9);
    if ((INTERNAL_STATES & listOfMsgs) == INTERNAL_STATES)
        loWord &= ~(1U << 10);
    if ((FAULT_CODES & listOfMsgs) == FAULT_CODES)
        loWord &= ~(1U << 11);
    if ((TORQUE_AND_TIMER_INFORMATION & listOfMsgs) == TORQUE_AND_TIMER_INFORMATION)
        loWord &= ~(1U << 12);
    if ((MOD_INDEX_FLUX_WEAKENING_OUTPUT_INFO & listOfMsgs) == MOD_INDEX_FLUX_WEAKENING_OUTPUT_INFO)
        loWord &= ~(1U << 13);
    if ((FIRMWARE_INFORMATION & listOfMsgs) == FIRMWARE_INFORMATION)
        loWord &= ~(1U << 14);
    if ((DIAG_DATA & listOfMsgs) == DIAG_DATA)
        loWord &= ~(1U << 15);

    // Separate loWord back into two bytes
    CAN_mssg[5] = loWord & 0xFF;
    CAN_mssg[6] = (loWord >> 8) & 0xFF;
}




//Fault Code Functions and Array defined below

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


std::ostream& operator<<(std::ostream& lhs, PM100_FAULT_CODE fault) 
{
    switch(fault) 
    {
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



int return_fault_index_val( PM100_FAULT_CODE fault )
{
    int index_value = fault;
    return index_value;
}

 
 
std::vector<PM100_FAULT_CODE> broadcast_message::read_fault_codes_VER_2( int CAN_mssg[9] )
{
    //extract the CAN ID & define return vector of fault codes
    int CAN_ID = CAN_mssg[0];
    vector<PM100_FAULT_CODE> faults_found;
    PM100_FAULT_CODE fault;

    //check if CAN message is FAULT message
    if( CAN_ID != 0x0AB )
    {
        cout << NOT_FAULT_CAN_MSSG;
        faults_found.push_back( NOT_FAULT_CAN_MSSG );
    }
    else if( CAN_ID == 0x0AB )
    {
        int fault_code_index = 0; //var used for indexing fault code array

        //here we'll loop 8 times, analyze each CAN data byte
        for( int i = 1; i < 9; i++  )
        {
            int byte_i = CAN_mssg[i];
            cout << "Byte " << i << " Faults: " << endl;

            //vars to check each bit of current byte
            int current_bit;
            int int_to_binary = byte_i;
            for( int i = 0; i < 8; i++ )
            {
                current_bit = int_to_binary % 2;
                int_to_binary = int_to_binary / 2;

                if( current_bit )
                {
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



int main()
{
    cout << "Testing print_vms_state function: " << endl;

    broadcast_message testing_class;
    vsm_state CAN_MSSG_VSM_STATE;

    int test_CAN_message[9] = {0x0AA, 0, 1, 0, 0, 0, 0, 0, 0};

    cout << "CAN Message--------------------" << endl;
    cout << "{";
    for (int i = 0; i < 9; i++)
    {

        cout << " " << test_CAN_message[i];
        if (i != 8)
        {
            cout << ",";
        }
    }
    cout << " }\n" << endl;

    CAN_MSSG_VSM_STATE = testing_class.read_vsm_state(test_CAN_message);
    cout << "\n\nThe VSM State retrieved from the CAN Message is: " << CAN_MSSG_VSM_STATE << endl;
    cout << "Value of VSM State: " << return_vsm_state_val(CAN_MSSG_VSM_STATE) << endl;

    
    ///////////////////////////////////////////////////////////////////////////////////////////////

    
    cout << "\n\n\nTesting print_inverter_state function: " << endl;
    inverter_state CAN_MSSG_INVERTER_STATE;

    int test_CAN_message_2[9] = {0x0AA, 0, 0, 2, 0, 0, 0, 0, 0};

    cout << "CAN Message--------------------" << endl;
    cout << "{";
    for (int i = 0; i < 9; i++)
    {

        cout << " " << test_CAN_message_2[i];
        if (i != 8)
        {
            cout << ",";
        }
    }
    cout << " }\n" << endl;

    CAN_MSSG_INVERTER_STATE = testing_class.read_inverter_state(test_CAN_message_2);
    cout << "\nThe Inverter State retrieved from the CAN Message is: " << CAN_MSSG_INVERTER_STATE << endl;
    cout << "Value of Inverter State: " << return_inverter_state_val(CAN_MSSG_INVERTER_STATE) << endl;

    
    ///////////////////////////////////////////////////////////////////////////////////////////////

    
    cout << "\n\n\nTesting disable_broadcast_message function: " << endl;

    int test_msg[9] = {0x0C1, 148, 0, 1, 0, 0xFF, 0xFF, 0xFF, 0xFF};

    cout << "CAN Message--------------------" << endl;
    cout << "{ " << test_msg[0];
    for (int i = 1; i < 9; i++)
        cout << ", " << test_msg[i];
    cout << " }\n" << endl;

    disable_broadcast_message(test_msg, TEMPERATURE_2 | DIAG_DATA);

    cout << "New CAN Message--------------------" << endl;
    cout << "{ " << test_msg[0];
    for (int i = 1; i < 9; i++)
        cout << ", " << test_msg[i];
    cout << " }\n" << endl;
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////


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
    for ( int i = 0; i < 8; i++ )
    {
        /*
        if(i == 0)
        {
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
