#include "Solar_Panel_Tracking_Sys_v0.0.h"


void setup() {
  #ifdef bluetooth                                                                                   //CHECK IF BLUETOOTH IS DEFINE
  Serial.begin(38400);                                                                               //ENABLE SERIAL BEGIN FOR BLUETOOTH MODULE
  #endif                                                                                             //ENDING IF CONDTION
  SET_BIT(DDRD,u8Solar_Motor1_1_PD);                                                                 //SETTING Solar Motor 1 'Pin 1' bit in PORTB (SETTING MOTOR PIN AS OUTPUT)
  SET_BIT(DDRD,u8Solar_Motor1_2_PD);                                                                 //SETTING Solar Motor 1 'Pin 2' bit in PORTB (SETTING MOTOR PIN AS OUTPUT)
  SET_BIT(DDRB,u8Solar_Motor2_1_PB);                                                                 //SETTING Solar Motor 2 'Pin 1' bit in PORTB (SETTING MOTOR PIN AS OUTPUT)
  SET_BIT(DDRB,u8Solar_Motor2_2_PB);                                                                 //SETTING Solar Motor 2 'Pin 2' bit in PORTB (SETTING MOTOR PIN AS OUTPUT)
  
  SET_BIT(DDRB,u8Car_Motor1_1_PB);                                                                   //SETTING CAR Motor 1 'Pin 1' bit in PORTB (SETTING MOTOR PIN AS OUTPUT)
  SET_BIT(DDRB,u8Car_Motor1_2_PB);                                                                   //SETTING CAR Motor 1 'Pin 2' bit in PORTB (SETTING MOTOR PIN AS OUTPUT)
  SET_BIT(DDRB,u8Car_Motor2_1_PB);                                                                   //SETTING CAR Motor 2 'Pin 1' bit in PORTB (SETTING MOTOR PIN AS OUTPUT)
  SET_BIT(DDRC,u8Car_Motor2_2_PC);                                                                   //SETTING CAR Motor 2 'Pin 2' bit in PORTB (SETTING MOTOR PIN AS OUTPUT)
  
  SET_BIT(DDRC,ShiftReg_SHIFT_PC);                                                                   //SET SHIFT PIN AS OUTPUT
  SET_BIT(DDRC,ShiftReg_DATA_PC);                                                                    //SET DATA PIN AS OUTPUT
  SET_BIT(DDRC,ShiftReg_STORE_PC);                                                                   //SET STORE PIN AS OUTPUT
  
  SET_BIT(DDRB,SevenSegment_D1_PB);                                                                  //SET SEGMENT_1 PIN AS OUTPUT
  SET_BIT(DDRB,SevenSegment_D2_PB);                                                                  //SET SEGMENT_2 PIN AS OUTPUT
  SET_BIT(DDRB,SevenSegment_D3_PB);                                                                  //SET SEGMENT_3 PIN AS OUTPUT
  SET_BIT(DDRB,SevenSegment_D4_PB);                                                                  //SET SEGMENT_4 PIN AS OUTPUT
  #ifndef bluetooth
  SET_BIT(PORTB,u8FORWARD_Button_PB);                                                                //SET PULLUP RESISTOR FOR FORWARD BUTTON
  SET_BIT(PORTB,u8BACKWARD_Button_PB);                                                               //SET PULLUP RESISTOR FOR BACKWARD BUTTON
  SET_BIT(PORTB,u8LEFT_Button_PB);                                                                   //SET PULLUP RESISTOR FOR LEFT BUTTON
  SET_BIT(PORTB,u8RIGHT_Button_PB);                                                                  //SET PULLUP RESISTOR FOR RIGHT BUTTON
  #endif
  u32PreviousMillis= millis();                                                                       //COUNTING MILLIS
  
}

void loop() {
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                               SUN FOLLOWER SOLAR PANEL SYSTEM                                                     //
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  vidLDR_Values();                                                                                   //Reading LDR Function
  
  if((u16LDR_TOP+u8Safe_Zone)<u16LDR_button){                                                        //Condition To Check if The button LDR has light more than TOP LDR   
             /*Action of motors*/
    SET_BIT(PORTD,u8Solar_Motor1_1_PD);
    CLR_BIT(PORTD,u8Solar_Motor1_2_PD);
  }
  else if((u16LDR_button+u8Safe_Zone)<u16LDR_TOP){                                                   //Condition To Check if The TOP LDR has light more than button LDR   
             /*Action of motors*/
    SET_BIT(PORTD,u8Solar_Motor1_2_PD);
    CLR_BIT(PORTD,u8Solar_Motor1_1_PD);
  } 
  else if((u16LDR_LEFT+u8Safe_Zone)<u16LDR_RIGHT){                                                   //Condition To Check if The RIGHT LDR has light more than LEFT LDR   
             /*Action of motors*/
    SET_BIT(PORTB,u8Solar_Motor2_1_PB);
    CLR_BIT(PORTB,u8Solar_Motor2_2_PB);
  }
  else if((u16LDR_RIGHT+u8Safe_Zone)<u16LDR_LEFT){                                                   //Condition To Check if The LEFT LDR has light more than RIGHT LDR   
             /*Action of motors*/
    SET_BIT(PORTB,u8Solar_Motor2_2_PB);
    CLR_BIT(PORTB,u8Solar_Motor2_1_PB);
  }
  else{
            /*Action of motors*/
    CLR_BIT(PORTD,u8Solar_Motor1_1_PD);
    CLR_BIT(PORTD,u8Solar_Motor1_2_PD);
    CLR_BIT(PORTB,u8Solar_Motor2_1_PB);
    CLR_BIT(PORTB,u8Solar_Motor2_2_PB);
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                                  Solar Panel Moving System                                                        //
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  #ifdef bluetooth                                                                              //CHECKING IF BLUETOOTH DEFINED
  if(Serial.available() > 0){                                                                   //CHECKING IF THERES DATA SEND
    u8Bluetooth_State= Serial.read();                                                           //SAVING RECIEVED DATA FROM BLUETOOTH
  }
  switch(u8Bluetooth_State){                                                                    //CHECKING THE BLUETOOTH STATEMNET
    case FORWARD:                                                                               //CHECKING IF THE RECIEVED DATA IS FORWARD
    /*    SET MOTOR FORWARD DIRECTION   */
      SET_BIT(PORTB,u8Car_Motor1_1_PB);                                                         
      CLR_BIT(PORTB,u8Car_Motor1_2_PB);
      SET_BIT(PORTB,u8Car_Motor2_1_PB);
      CLR_BIT(PORTC,u8Car_Motor2_2_PC);
      u8Bluetooth_State=0;                                                                      //Reset Bluetooth State
      break;                                                                                    //STOP THE FORWARD CONDITION CODE

    case BACKWARD:                                                                              //CHECKING IF THE RECIEVED DATA IS BACKWARD
    /*    SET MOTOR BACKWARD DIRECTION   */
      SET_BIT(PORTB,u8Car_Motor1_2_PB);
      CLR_BIT(PORTB,u8Car_Motor1_1_PB);
      SET_BIT(PORTC,u8Car_Motor2_2_PC);
      CLR_BIT(PORTB,u8Car_Motor2_1_PB);
      u8Bluetooth_State=0;                                                                      //Reset Bluetooth State

      break;                                                                                    //STOP THE BACKWARD CONDITION CODE

    case LEFT:                                                                                  //CHECKING IF THE RECIEVED DATA IS LEFT
    /*    SET MOTOR LEFT DIRECTION   */
      SET_BIT(PORTB,u8Car_Motor1_1_PB);
      CLR_BIT(PORTB,u8Car_Motor1_2_PB);
      SET_BIT(PORTC,u8Car_Motor2_2_PC);
      CLR_BIT(PORTB,u8Car_Motor2_1_PB);
      u8Bluetooth_State=0;                                                                      //Reset Bluetooth State
      break;                                                                                    //STOP THE LEFT CONDITION CODE

    case RIGHT:                                                                                 //CHECKING IF THE RECIEVED DATA IS RIGHT
    /*    SET MOTOR RIGHT DIRECTION   */
      SET_BIT(PORTB,u8Car_Motor1_2_PB);
      CLR_BIT(PORTB,u8Car_Motor1_1_PB);
      SET_BIT(PORTB,u8Car_Motor2_1_PB);
      CLR_BIT(PORTC,u8Car_Motor2_2_PC);
      u8Bluetooth_State=0;                                                                      //Reset Bluetooth State
      break;                                                                                    //STOP THE FORWARD CONDITION CODE

    default:                                                                                    //PUT DEFAULT CONDITION
    /*    STOP ALL THE MOTORS   */
      CLR_BIT(PORTB,u8Car_Motor1_1_PB);
      CLR_BIT(PORTB,u8Car_Motor1_1_PB);
      CLR_BIT(PORTB,u8Car_Motor2_1_PB);
      CLR_BIT(PORTC,u8Car_Motor2_2_PC);
      u8Bluetooth_State=0;                                                                      //Reset Bluetooth State      
      break;                                                                                    //STOP THE DEAFULT CONDITION CODE
  }
  
  #endif
  
  #ifndef bluetooth
  if(!GET_BIT(PINB,u8FORWARD_Button_PB)){
             /*Action of motors*/
    SET_BIT(PORTB,u8Car_Motor1_1_PB);
    CLR_BIT(PORTB,u8Car_Motor1_2_PB);
    SET_BIT(PORTB,u8Car_Motor2_1_PB);
    CLR_BIT(PORTC,u8Car_Motor2_2_PC);
  }
  else if(!GET_BIT(PINB,u8BACKWARD_Button_PB)){
             /*Action of motors*/
    SET_BIT(PORTB,u8Car_Motor1_2_PB);
    CLR_BIT(PORTB,u8Car_Motor1_1_PB);
    SET_BIT(PORTC,u8Car_Motor2_2_PC);
    CLR_BIT(PORTB,u8Car_Motor2_1_PB);
  }
  else if(!GET_BIT(PINB,u8LEFT_Button_PB)){
             /*Action of motors*/
    SET_BIT(PORTB,u8Car_Motor1_1_PB);
    CLR_BIT(PORTB,u8Car_Motor1_2_PB);
    SET_BIT(PORTC,u8Car_Motor2_2_PC);
    CLR_BIT(PORTB,u8Car_Motor2_1_PB);
  }
  else if(!GET_BIT(PINB,u8RIGHT_Button_PB)){
             /*Action of motors*/
    SET_BIT(PORTB,u8Car_Motor1_2_PB);
    CLR_BIT(PORTB,u8Car_Motor1_1_PB);
    SET_BIT(PORTB,u8Car_Motor2_1_PB);
    CLR_BIT(PORTC,u8Car_Motor2_2_PC);
  }
  else{
             /*Action of motors*/
    CLR_BIT(PORTB,u8Car_Motor1_1_PB);
    CLR_BIT(PORTB,u8Car_Motor1_1_PB);
    CLR_BIT(PORTB,u8Car_Motor2_1_PB);
    CLR_BIT(PORTC,u8Car_Motor2_2_PC);
  }
  #endif


 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //                                                 DISPLAY SOLAR PANEL VOLTAGE                                                       //
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (millis() - u32PreviousMillis > u16ONE_SECOND) {                                                //CALCULATE 1 SECOND
    s32Volt_Temp=analogRead(PANEL);                                                                  //CALCULATE RPM (60 SECOND * NO_PULSES) / (24 ONE REV)
    s32Volt=(s32Volt_Temp/s32RESISTOR_FACTOR)*5;                                                     //SET ENCODER COUNTER = 0
    u32PreviousMillis=millis();                                                                      //RESET TIMER TO RECALCULTE 1 SECOND
  }
 
    /* PRINT IN D1-SEVEN SEGMENT */ 
  voidSegment_Draw((u16)s32Volt%10 , FIRST_DIGIT);                                                   //DRAW FRIST NUMBER IN Voltage i.e (32'1')
  delay(1);
  
  /* PRINT IN D2-SEVEN SEGMENT */ 
  voidSegment_Draw((u16)s32Volt%10 , SECOND_DIGIT);                                                  //DRAW FRIST NUMBER IN Voltage i.e (32'1')
  delay(1);




 }
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //                                                          FUNCTIONS                                                                //
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void vidLDR_Values(void){
  u16LDR_TOP=analogRead(u8LDR_TOP);                                                                  //Reading TOP LDR Values AND STORE IT INTO 16-BIT VARIABLE 
  u16LDR_button=analogRead(u8LDR_button);                                                            //Reading button LDR Values AND STORE IT INTO 16-BIT VARIABLE 
  u16LDR_LEFT=analogRead(u8LDR_LEFT);                                                                //Reading LEFT LDR Values AND STORE IT INTO 16-BIT VARIABLE 
  u16LDR_RIGHT=analogRead(u8LDR_RIGHT);                                                              //Reading RIGHT LDR Values AND STORE IT INTO 16-BIT VARIABLE 
}

#ifndef LCD                                                                                          //Just USE THIS IF THERE'S NO LCD

void ShiftRegister_voidStore(void){
  SET_BIT(PORTC,ShiftReg_STORE_PC);                                                                  //SET BIT 0 IN PORTB 1 (PIN 8 HIGH)
  delayMicroseconds(10);                                                                             // DELAY 10us
  CLR_BIT(PORTC,ShiftReg_STORE_PC);                                                                  // CLR BIT 0 IN PORTB 1 (PIN 8 LOW)
  delayMicroseconds(10);                                                                             // DELAY 10us
}


void voidSegment_Draw(u8 u8_Num,u8 u8_Digit){
    shiftOut(ShiftReg_DATA, ShiftReg_SHIFT, LSBFIRST,u8_Digit);                                      //Choose Which Digit
    shiftOut(ShiftReg_DATA, ShiftReg_SHIFT, LSBFIRST,u8ShiftReg_7Seg[u8_Num]);                       //PRINT ON 7-SEGEMENT RECIVED BITS
    ShiftRegister_voidStore();                                                                       //STORING
}

#endif
