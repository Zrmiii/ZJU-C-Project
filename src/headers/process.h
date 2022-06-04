#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "definition.h"

void CopyObj();

void PasteObj();

/* 功能:缩放对象
 * 参数1:缩放倍数
 * 参数2:对象指针
 * 参数3:给定缩放函数
 * 返回值:无
 * 说明:调用 给定缩放函数，缩放 给定指针指向的任意类型对象
 */
void EnLargeObj(double Times, void *ptr_Obj, void (*fptr_EnLargeObj)(double Times, void *ptr_Obj));

/* 功能:EnLargeObj辅助函数
 * 参数1:缩放倍数
 * 参数2:对象指针
 * 返回值:无
 * 说明:缩放 给定指针指向的特定类型对象
 */
void EnLargeProcedureBox(double Times, void *ptr_Obj);
void EnLargeJudgeBox(double Times, void *ptr_Obj);
void EnLargeStartBox(double Times, void *ptr_Obj);

/* 功能:删除对象
 * 参数:对象指针，即CURR_OBJ
 * 返回值:无
 */
void DeleteObj(void *ptr_Obj);

/* 功能:遍历链表,找到给定 ID 对应的对象
 * 参数:对象ID
 * 返回值:找到的对象指针
 */
void *SearchObj(int ID);

/* 功能:SearchObj辅助函数
 * 参数1:待查找data指针
 * 参数2:给定ID
 * 返回值:是否相等,相等为TRUE
 */
bool equalfunptr_Line(void *obj1, void *obj2);
bool equalfunptr_PBox(void *obj1, void *obj2);
bool equalfunptr_JBox(void *obj1, void *obj2);
bool equalfunptr_SBox(void *obj1, void *obj2);
bool equalfunptr_IBox(void *obj1, void *obj2);

void PickNearestObj(double mx, double my);
double LtsDistance(void *ptr_Obj, double mx, double my);
bool IsInZone(double mx, double my, void *Obj);
#endif
