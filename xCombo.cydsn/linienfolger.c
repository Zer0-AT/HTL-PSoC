#include "project.h"

#include <stdio.h>
int * getIREcho(){
    
    static int state[3];
    
    if(inIR_R_Read()==0)state[0] = 1;
    else state[0] = 0;
        
    if(inIR_M_Read()==0)state[1] = 1;
    else state[1] = 0;
        
    if(inIR_L_Read()==0)state[2] = 1;
    else state[2] = 0;
    
    return &state[0];
}

void setIRDirection(void){
    
        //UART_PutString("Yes \r\n");
    int * lfRichtung;
    lfRichtung = getIREcho();
    if (lfRichtung[0] == 1 && lfRichtung[2] == 0){
        //UART_PutString("Right \r\n");
        setPWM_left_back_Write(1);
        setPWM_left_for_Write(0);
        setPWM_right_back_Write(0);
        setPWM_right_for_Write(1);
        
    }
    if (lfRichtung[0] == 0 && lfRichtung[1] == 1 && lfRichtung[2] == 0){
        //UART_PutString("For \r\n");
        setPWM_left_back_Write(0);
        setPWM_left_for_Write(1);
        setPWM_right_back_Write(0);
        setPWM_right_for_Write(1);
    }
    if (lfRichtung[0] == 0 && lfRichtung[2] == 1){
        //UART_PutString("Left \r\n");
        setPWM_left_back_Write(0);
        setPWM_left_for_Write(1);
        setPWM_right_back_Write(1);
        setPWM_right_for_Write(0);
    }
    if ((lfRichtung[0] == 0 && lfRichtung[1] == 0 && lfRichtung[2] == 0)||(lfRichtung[0] == 1 && lfRichtung[1] == 1 && lfRichtung[2] == 1)){
        UART_PutString("Stop \r\n");
        setPWM_left_back_Write(0);
        setPWM_left_for_Write(0);
        setPWM_right_back_Write(0);
        setPWM_right_for_Write(0);
    }
}