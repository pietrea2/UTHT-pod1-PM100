#ifndef COMMAND_MESSAGE_H
#define COMMAND_MESSAGE_H

//types of CAN messages
typedef enum m_type {
  BROADCAST_M,
  COMMAND_TOURQUE_M,
  COMMAND_SPEED_M
} message_type;

//command message variables for inverter
typedef enum i_direction {
  REVERSE, //clock-wise
  FORWARD  //counter-clock-wise
} inverter_direction;

typedef enum i_enable {
  ENABLE,
  DISABLE
} inverter_enable;



class command_message{

  public:
  
    message_type command_message;
    
    int* create_command_message( message_type command_message, 
                                 float torque_val, //Value in N.m
                                 float speed_val,  //RPM
                                 inverter_direction direction_command, 
                                 inverter_enable enable_command );


                              

  



  
};

#endif
