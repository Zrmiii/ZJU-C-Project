#ifndef _DRAW_C_
#define _DRAW_C_

#include "draw.h"

void DrawAllObj()
{
	TraverseLinkedList(List[STARTBOX], DrawStartBox);
	TraverseLinkedList(List[PROCEDUREBOX], DrawProcedureBox);
	TraverseLinkedList(List[JUDGEBOX], DrawJudgeBox);
}

void EnLargeObj(double Times, void* ptr_Obj, void (*fptr_EnLargeObj)(double Times, void* ptr_Obj))
{
	if(fptr_EnLargeObj == NULL) return;
	(*fptr_EnLargeObj)(Times, ptr_Obj);
}

void EnLargeProcedureBox(double Times, void* ptr_Obj)
{
	ptr_ProcedureBox ptr_temp = (ptr_ProcedureBox)ptr_Obj;
	ptr_temp->width *= Times;
	ptr_temp->height *= Times;
}

void EnLargeJudgeBox(double Times,void* ptr_Obj)
{
	ptr_JudgeBox ptr_temp = (ptr_JudgeBox)ptr_Obj;
	ptr_temp->width *= Times;
	ptr_temp->height *= Times;
}

void EnLargeStartBox(double Times,void* ptr_Obj)
{
	ptr_StartBox ptr_temp = (ptr_StartBox)ptr_Obj;
	ptr_temp->width *= Times;
	ptr_temp->height *= Times;
}

void CopyObj()
{
	if(CURR_OBJ == NULL) return;
	TEMP = CURR_OBJ;
	TEMP_KIND = CURR_OBJ_KIND;
}

void PasteObj()
{
	if(TEMP == NULL) return;

	ptr_StartBox StartBox_Obj;
	ptr_JudgeBox JudgeBox_Obj;
	ptr_ProcedureBox ProcedureBox_Obj;

	switch (TEMP_KIND)
	{
	case PROCEDUREBOX:
		StartBox_Obj = (ptr_ProcedureBox)GetBlock(sizeof(*StartBox_Obj));

		StartBox_Obj = (ptr_ProcedureBox)TEMP;
		StartBox_Obj->x = StartBox_Obj->x + StartBox_Obj->width/10;
		StartBox_Obj->y = StartBox_Obj->y + StartBox_Obj->height/10;

		DrawStartBox(StartBox_Obj);
		InsertNode(List[STARTBOX],NULL,StartBox_Obj);
		
		break;
	case JUDGEBOX:
		//
		break;
	case STARTBOX:
		//
		break;
	default:
		break;
	}
}

#endif
