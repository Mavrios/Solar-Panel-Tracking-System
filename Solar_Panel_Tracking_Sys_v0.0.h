#ifndef SOLAR_PANEL_TRACKING_SYSTEM_H
#define SOLAR_PANEL_TRACKING_SYSTEM_H


/*THERE'S SOME SHORTCUTS NAMES IN CODE LIKE PB -> 'P'-> PORT , SO PB REFERE TO PORTB, SAME WITH PD, PC
 * u8 -> Refere UNSIGNED 8 BIT , 'u' Refere to UNSIGNED , Same WITH u16 , u32 ,etc
 */
            /* TYPE DEFINE */
    /* u -> UNSIGNED and '8' -> 8 bit */
    /* u -> UNSIGNED and '16' -> 16 bit */

typedef unsigned char       u8;                                    //Making new Type called u8
typedef unsigned short int u16;                                    //Making new Type called u16
typedef unsigned long      u32;                                    //Making new Type called u32
typedef float              s32;                                    //Making new Type called s32
    /*Macros TO SET AND CLR AND GET BITS*/
#define SET_BIT(BYTE,No_Bit)  BYTE |=(1<<No_Bit)                   //Macro To SET_BIT
#define CLR_BIT(BYTE,No_Bit)  BYTE &=~(1<<No_Bit)                  //Macro To CLR_BIT
#define GET_BIT(BYTE,Bit_NO) ((BYTE>>Bit_NO)&(0x01))               //Macro To GET_BIT

                          /*           FUNCTIONS PROTOTYPES            */
void vidLDR_Values(void);



                                 /*          LCD            */
//#define LCD                                                      //UNCOMMENT IF U WILL USE IT
#ifdef LCD                                                         //Check IF "LCD" Defined
#include <LiquidCrystal.h>                                         //Including "LCD" Library                              

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;        //Definition of LCD PINS as Const
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                         //define "lcd" as LiquidCrystal Type

#endif                                                             //Ending if condition



                                 /*          7-SEGMENT             */
#ifndef LCD                                                        //That Mean LCD Is no Avl -- So we will use 7-Seg

void ShiftRegister_voidStore(void);                                //Function Prototype
void voidSegment_Draw(u8 u8_Num,u8 u8_Digit);                      //Function Prototype

#define ShiftReg_SHIFT_PC  0                                       //SHIFT PORT BIT_NO   (PD -> PORTD)
#define ShiftReg_DATA_PC   1                                       //DATA PORT BIT_NO   (PD -> PORTD)
#define ShiftReg_STORE_PC  2                                       //STORE PORT BIT_NO   (PB -> PORTB)

#define ShiftReg_SHIFT     A0                                      //SHIFTREG(SHIFT PIN CONNECTED TO A0)
#define ShiftReg_DATA      A1                                      //SHIFTREG(DATA  PIN CONNECTED TO A1)


#define SevenSegment_D1_PB    2                                    //D1 PORT BIT_NO   (PB -> PORTB)
#define SevenSegment_D2_PB    3                                    //D2 PORT BIT_NO   (PB -> PORTB)
#define SevenSegment_D3_PB    4                                    //D3 PORT BIT_NO   (PB -> PORTB)
#define SevenSegment_D4_PB    5                                    //D4 PORT BIT_NO   (PB -> PORTB)

#define EIGHT_BITS            8                                    //FOR LOOP

#define FIRST_DIGIT        0x80                                    //TO SELECT FIRST DIGIT IN SEVEN SEGMENT
#define SECOND_DIGIT       0x40                                    //TO SELECT SECOND DIGIT IN SEVEN SEGMENT


u8 u8ShiftReg_7Seg[10]={0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xE6}; //7-Seg Numbers in hex  --> (0xFC will appear '0' in 7-Seg)

#endif                                                             //End Condition



        /*For LDR*/
/*We Got 4 LDR In each side*/

#define u8LDR_TOP     A4                                           //LDR_Top ON PIN    A4
#define u8LDR_button  A5                                           //LDR_button ON PIN A5
#define u8LDR_LEFT    A6                                           //LDR_LEFT ON PIN   A6
#define u8LDR_RIGHT   A7                                           //LDR_RIGHT ON PIN  A7


        /*For Motors*/
/*We Got 2 Motors to make 2 Axis*/
#define u8Solar_Motor1_1_PD  6                                     //Motor1 Step ON PORTD 6
#define u8Solar_Motor1_2_PD  7                                     //Motor1 Step ON PORTD 7

#define u8Solar_Motor2_1_PB   0                                    //Motor1 Dir ON PORTB 0
#define u8Solar_Motor2_2_PB   1                                    //Motor1 Dir ON PORTB 1


      /*For Moving Sys*/
#define u8Car_Motor1_1_PB  2                                       //Motor1 Step ON PORTB 2
#define u8Car_Motor1_2_PB  3                                       //Motor1 Step ON PORTB 3

#define u8Car_Motor2_1_PB   4                                      //Motor1 Dir ON PORTB 4
#define u8Car_Motor2_2_PC   3                                      //Motor1 Dir ON PORTC 3


      /*Bottons*/
#define bluetooth

#ifdef  bluetooth
  
  #define FORWARD   1
  #define BACKWARD  2
  #define LEFT      3
  #define RIGHT     4

  u8 u8Bluetooth_State=0; 
    
#endif

#ifndef bluetooth

  #define u8FORWARD_Button_PB     1                                //Forward button bit in PORTx
  #define u8BACKWARD_Button_PB    1                                //Forward button bit in PORTx
  #define u8LEFT_Button_PB        1                                //Forward button bit in PORTx
  #define u8RIGHT_Button_PB       1                                //Forward button bit in PORTx

#endif

    /*Variables*/
#define u8Safe_Zone 100                                           //That Zone to make solar panel less vaibrate.


u16 u16LDR_TOP =0;                                                //Define 16-bit Variable to Save LDR_Top analog Values
u16 u16LDR_button =0;                                             //Define 16-bit Variable to Save LDR_button analog Values
u16 u16LDR_LEFT =0;                                               //Define 16-bit Variable to Save LDR_LEFT analog Values
u16 u16LDR_RIGHT =0;                                              //Define 16-bit Variable to Save LDR_RIGHT analog Values

u8 i=0;                                                           //Define 8-bit Variable to be as Loop iterator

#define s32RESISTOR_FACTOR    511.5                               
#define u8REFERENCE_VOLTAGE   5
#define PANEL                 A0
#define u16ONE_SECOND         1000
s32 s32Volt_Temp =0;
s32 s32Volt=0;
u32 u32PreviousMillis=0;

#endif
