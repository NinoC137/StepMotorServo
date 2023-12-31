#ifndef __STEP_H
#define __STEP_H

#include "main.h"
#include "cmsis_os.h"
#include "stdlib.h"

//motor enable
#define ENABLE 1
#define DISABLE 0
//motor direct
#define FORWARD 1
#define BACK	0

#define ONEPERIOD 6000  //6000个脉冲一圈

//Sub_Box Position ID
//这部分的数值改为各个位置相对于原点的圈数
//如: ID_BOX1 20 代表从原点走到BOX1需要20圈
#define ID_INIT 46
#define ID_BOX1 0
#define ID_BOX2 9
#define ID_BOX3 18
#define ID_OUT  46

typedef struct StepMotor_OOP{
    //elements
    char* name;
    TIM_HandleTypeDef* TIMER;
    uint32_t Channel;
    uint32_t PulseCounter;

    uint32_t CurrentPlace;
    uint32_t TargetPlace;

    uint8_t MotorState;

    //API functions
    char* (*Reset)(struct StepMotor_OOP *);                             //Reset to default place
    char* (*Step2PointPlace)(struct StepMotor_OOP *, uint32_t PlaceName);  //Step to NamedPlace
}StepMotor;

//Create an Oriented
StepMotor StepMotor_Create(char* name ,TIM_HandleTypeDef* TIMER, uint32_t Channel);

//OOP function define
char* prReset(StepMotor * SM);
char* prStep2PointPlace(StepMotor * SM, uint32_t PlaceName);

//Application functions
void StepMotor_init(void);
char* Step_OnePeriod(StepMotor * aStepMotor, uint8_t direct);
char* Step_KeepMoving(const StepMotor * aStepMotor, uint8_t direct, uint8_t Enable);

char* AngleControl(StepMotor * aStepMotor, float targetAngle, float PulsePerOneCircle);

extern StepMotor pitchMotor;
extern StepMotor yawMotor;

#endif