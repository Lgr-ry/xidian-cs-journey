/**
 ******************************************************************************
 * @file    pid.c
 * @brief   通用位置式 PID 实现（纯算法，不依赖任何单片机库）
 ******************************************************************************
 */
#include "pid.h"

void PID_Init(PID_t *p, float kp, float ki, float kd, float outMax, float intMax)
{
    p->kp = kp;
    p->ki = ki;
    p->kd = kd;

    p->target    = 0.0f;
    p->integral  = 0.0f;
    p->prevError = 0.0f;

    p->outMin = -outMax;
    p->outMax =  outMax;
    p->intMin = -intMax;
    p->intMax =  intMax;
}

void PID_SetTarget(PID_t *p, float target)
{
    p->target = target;
}

void PID_Reset(PID_t *p)
{
    p->integral  = 0.0f;
    p->prevError = 0.0f;
}

float PID_Calc(PID_t *p, float measure)
{
    float error = p->target - measure;
    float dError;
    float out;

    /* 积分累计并限幅，防止长时间偏差导致积分“爆掉” */
    p->integral += error;
    if (p->integral > p->intMax) p->integral = p->intMax;
    if (p->integral < p->intMin) p->integral = p->intMin;

    dError = error - p->prevError;
    p->prevError = error;

    out = p->kp * error + p->ki * p->integral + p->kd * dError;

    if (out > p->outMax) out = p->outMax;
    if (out < p->outMin) out = p->outMin;

    return out;
}
