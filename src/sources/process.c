#ifndef _PROCESS_C_
#define _PROCESS_C_

#include "definition.h"
#include "process.h"

void CopyObj()
{
	if (CURR_OBJ == NULL || IS_IN_TEXT)
		return;

	TEMP = GetBlock(sizeof(*(ptr_StartBox)CURR_OBJ));

	((ptr_StartBox)TEMP)->x = ((ptr_StartBox)CURR_OBJ)->x + ((ptr_StartBox)CURR_OBJ)->width / 3;
	((ptr_StartBox)TEMP)->y = ((ptr_StartBox)CURR_OBJ)->y - ((ptr_StartBox)CURR_OBJ)->height / 3;
	((ptr_StartBox)TEMP)->width = ((ptr_StartBox)CURR_OBJ)->width;
	((ptr_StartBox)TEMP)->height = ((ptr_StartBox)CURR_OBJ)->height;
	((ptr_StartBox)TEMP)->Degree = ((ptr_StartBox)CURR_OBJ)->Degree;
	((ptr_StartBox)TEMP)->PenSize = ((ptr_StartBox)CURR_OBJ)->PenSize;
	((ptr_StartBox)TEMP)->Color = ((ptr_StartBox)CURR_OBJ)->Color;
	((ptr_StartBox)TEMP)->Text = CopyString(((ptr_StartBox)CURR_OBJ)->Text);

	TEMP_KIND = CURR_OBJ_KIND;
}

void PasteObj()
{
	if (TEMP == NULL || IS_IN_TEXT)
		return;

	void *PastedObj = GetBlock(sizeof(*(ptr_StartBox)TEMP));

	if (CURR_OBJ_KIND != -1)
	{
		((ptr_StartBox)CURR_OBJ)->IsSelected = FALSE;
		((ptr_StartBox)CURR_OBJ)->Color = SYS_COLOR;
	}

	((ptr_StartBox)PastedObj)->ID = CURR_ID++;
	((ptr_StartBox)PastedObj)->x = ((ptr_StartBox)TEMP)->x;
	((ptr_StartBox)PastedObj)->y = ((ptr_StartBox)TEMP)->y;
	((ptr_StartBox)PastedObj)->width = ((ptr_StartBox)TEMP)->width;
	((ptr_StartBox)PastedObj)->height = ((ptr_StartBox)TEMP)->height;
	((ptr_StartBox)PastedObj)->Degree = ((ptr_StartBox)TEMP)->Degree;
	((ptr_StartBox)PastedObj)->PenSize = ((ptr_StartBox)TEMP)->PenSize;
	((ptr_StartBox)PastedObj)->Color = SEL_COLOR;
	((ptr_StartBox)PastedObj)->Text = CopyString(((ptr_StartBox)TEMP)->Text);
	((ptr_StartBox)PastedObj)->IsSelected = TRUE;

	((ptr_StartBox)TEMP)->x = ((ptr_StartBox)TEMP)->x + ((ptr_StartBox)TEMP)->width / 3;
	((ptr_StartBox)TEMP)->y = ((ptr_StartBox)TEMP)->y - ((ptr_StartBox)TEMP)->height / 3;
	CURR_OBJ = PastedObj;

	switch (TEMP_KIND)
	{
	case STARTBOX:
		InsertNode(List[STARTBOX], NULL, PastedObj);
		CURR_OBJ_KIND = STARTBOX;
		break;
	case PROCEDUREBOX:
		InsertNode(List[PROCEDUREBOX], NULL, PastedObj);
		CURR_OBJ_KIND = PROCEDUREBOX;
		break;
	case JUDGEBOX:
		InsertNode(List[JUDGEBOX], NULL, PastedObj);
		CURR_OBJ_KIND = JUDGEBOX;
		break;
	case INPUTANDOUTPUTBOX:
		InsertNode(List[INPUTANDOUTPUTBOX], NULL, PastedObj);
		CURR_OBJ_KIND = INPUTANDOUTPUTBOX;
		break;
	default:
		break;
	}

	IS_SELECTED = TRUE;
}

void EnLargeObj(double Times, void *ptr_Obj, void (*fptr_EnLargeObj)(double Times, void *ptr_Obj))
{
	if (fptr_EnLargeObj == NULL)
		return;
	(*fptr_EnLargeObj)(Times, ptr_Obj);
}

void EnLargeProcedureBox(double Times, void *ptr_Obj)
{
	ptr_ProcedureBox ptr_temp = (ptr_ProcedureBox)ptr_Obj;
	ptr_temp->width *= Times;
	ptr_temp->height *= Times;
}

void EnLargeJudgeBox(double Times, void *ptr_Obj)
{
	ptr_JudgeBox ptr_temp = (ptr_JudgeBox)ptr_Obj;
	ptr_temp->width *= Times;
	ptr_temp->height *= Times;
}

void EnLargeStartBox(double Times, void *ptr_Obj)
{
	ptr_StartBox ptr_temp = (ptr_StartBox)ptr_Obj;
	ptr_temp->width *= Times;
	ptr_temp->height *= Times;
}

void DeleteObj(void *ptr_Obj)
{
	linkedlistADT deletednode = NULL;
	do
	{
		deletednode = DeleteNode(List[LINE], &(((ptr_StartBox)ptr_Obj)->ID), equalfunptr_Line);
	} while (deletednode != NULL);

	switch (CURR_OBJ_KIND)
	{
	case STARTBOX:
		DeleteNode(List[STARTBOX], &(((ptr_StartBox)ptr_Obj)->ID), equalfunptr_SBox);
		COUNT[0]--;
		break;
	case PROCEDUREBOX:
		DeleteNode(List[PROCEDUREBOX], &(((ptr_ProcedureBox)ptr_Obj)->ID), equalfunptr_PBox);
		COUNT[1]--;
		break;
	case JUDGEBOX:
		DeleteNode(List[JUDGEBOX], &(((ptr_JudgeBox)ptr_Obj)->ID), equalfunptr_JBox);
		COUNT[2]--;
		break;
	case INPUTANDOUTPUTBOX:
		DeleteNode(List[INPUTANDOUTPUTBOX], &(((ptr_InputAndOutputBox)ptr_Obj)->ID), equalfunptr_IBox);
		COUNT[3]--;
		break;
	default:
		break;
	}
}

void *SearchObj(int ID)
{
	int i;
	linkedlistADT ptr_SearchObj = NULL;
	for (i = 0; i < NLIST; i++)
	{
		if (i == 0)
			ptr_SearchObj = SearchNode(List[STARTBOX], &ID, equalfunptr_PBox);
		else if (i == 1)
			ptr_SearchObj = SearchNode(List[PROCEDUREBOX], &ID, equalfunptr_JBox);
		else if (i == 2)
			ptr_SearchObj = SearchNode(List[JUDGEBOX], &ID, equalfunptr_SBox);
		else if (i == 3)
			ptr_SearchObj = SearchNode(List[INPUTANDOUTPUTBOX], &ID, equalfunptr_IBox);
		if (ptr_SearchObj != NULL)
			break;
	}

	return ptr_SearchObj->dataptr;
}

bool equalfunptr_Line(void *obj1, void *obj2)
{
	ptr_Line ptr_temp = (ptr_Line)obj1;
	int *id_temp = (int *)obj2;

	if (ptr_temp->ID_1 == *id_temp || ptr_temp->ID_2 == *id_temp)
		return TRUE;
	else
		return FALSE;
}
bool equalfunptr_PBox(void *obj1, void *obj2)
{
	ptr_ProcedureBox ptr_temp = (ptr_ProcedureBox)obj1;
	int *id_temp = (int *)obj2;

	if (ptr_temp->ID == *id_temp)
		return TRUE;
	else
		return FALSE;
}
bool equalfunptr_JBox(void *obj1, void *obj2)
{
	ptr_JudgeBox ptr_temp = (ptr_JudgeBox)obj1;
	int *id_temp = (int *)obj2;

	if (ptr_temp->ID == *id_temp)
		return TRUE;
	else
		return FALSE;
}
bool equalfunptr_SBox(void *obj1, void *obj2)
{
	ptr_StartBox ptr_temp = (ptr_StartBox)obj1;
	int *id_temp = (int *)obj2;

	if (ptr_temp->ID == *id_temp)
		return TRUE;
	else
		return FALSE;
}
bool equalfunptr_IBox(void *obj1, void *obj2)
{
	ptr_InputAndOutputBox ptr_temp = (ptr_InputAndOutputBox)obj1;
	int *id_temp = (int *)obj2;

	if (ptr_temp->ID == *id_temp)
		return TRUE;
	else
		return FALSE;
}

void PickNearestObj(double mx, double my)
{
	double MinDistance = 100000000;
	double ObjDistance = -1;
	void *MinObj = NULL;
	int i;
	bool Found = FALSE;

	linkedlistADT nodeptr = NULL;

	for (i = STARTBOX; i < NLIST; i++)
	{
		nodeptr = List[i]->next;
		while (nodeptr != NULL)
		{
			ObjDistance = LtsDistance(nodeptr->dataptr, mx, my);
			if (IsInZone(mx, my, nodeptr->dataptr) && ObjDistance < MinDistance)
			{
				Found = TRUE;
				MinDistance = ObjDistance;
				CURR_OBJ = nodeptr->dataptr;
				CURR_OBJ_KIND = i;
			}
			nodeptr = nodeptr->next;
		}
	}

	if (!Found)
	{
		CURR_OBJ = NULL;
		CURR_OBJ_KIND = -1;
	}
}

double LtsDistance(void *ptr_Obj, double mx, double my)
{
	double x0, y0;
	x0 = ((ptr_StartBox)ptr_Obj)->x;
	y0 = ((ptr_StartBox)ptr_Obj)->y;

	return (fabs(x0 - mx) + fabs(y0 - my));
}

bool IsInZone(double mx, double my, void *Obj)
{
	double ObjX = ((ptr_StartBox)Obj)->x;
	double ObjY = ((ptr_StartBox)Obj)->y;
	double ObjW = ((ptr_StartBox)Obj)->width;
	double ObjH = ((ptr_StartBox)Obj)->height;

	if (mx < ObjX + ObjW && mx > ObjX - ObjW && my < ObjY + ObjH && my > ObjY - ObjH)
		return TRUE;
	else
		return FALSE;
}

#endif
