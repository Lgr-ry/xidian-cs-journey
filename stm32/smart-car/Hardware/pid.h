/**
 ******************************************************************************
 * @file    pid.h
 * @brief   通用位置式 PID（带积分限幅、输出限幅），用于速度闭环和方向控制
 ******************************************************************************
 */
#ifndef __PID_H
#define __PID_H

typedef struct
{
    float kp;            /* 比例系数 */
    float ki;            /* 积分系数 */
    float kd;            /* 微分系数 */

    float target;        /* 目标值 */
    float integral;      /* 积分累计 */
    float prevError;     /* 上一次误差，用于微分 */

    float outMin;        /* 输出下限 */
    float outMax;        /* 输出上限 */
    float intMin;        /* 积分下限（抗积分饱和） */
    float intMax;        /* 积分上限 */
} PID_t;

/**
 * @brief 初始化一个 PID 控制器（输出对称限幅）。
 * @param p      控制器指针
 * @param kp/ki/kd 三个系数
 * @param outMax 输出最大绝对值（最小自动取 -outMax）
 * @param intMax 积分项最大绝对值
 */
void  PID_Init(PID_t *p, float kp, float ki, float kd, float outMax, float intMax);

void  PID_SetTarget(PID_t *p, float target);   /* 设置目标值 */
void  PID_Reset(PID_t *p);                     /* 清积分和历史误差（换向时调用） */
float PID_Calc(PID_t *p, float measure);       /* 输入当前测量值，返回控制输出 */

#endif /* __PID_H */
