// Sudoko1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>

void intilize_sudoko();
int backtrack(int oldrow , int oldcol, int *newrow , int *newcol);
void read_no();
void BacktrackFor1stGird();
void InitilizeOutputMatrix();
void FindSolution();
void placeNumber(int row , int col);
int getno(int i,int j);
int checkNumber(int sno, int row ,int col);
int CheckRow(int sno , int row, int col);
int CheckCol(int sno , int row, int col);
int checkOriginal(int row,int col);
int CheckBox(int sno , int row, int col);
void printInputMatrix();
void printOutputMatrix();
void BacktrackFor1stGird();

int IndexCount=0;
int FirstGridRow=0 , FirstGirdCol=0;
//int *newi , *newj;
struct pos
{
	int row;
	int col;

} orgSudo[9],gridIndex[60];


int InputMatrix[9][9];
int OutputMatrix[9][9];
int BoxIndex[9][2]={ {2,2} , {2,5} , {2,8} , {5,2} , {5,5} , {5,8} , {8,2} , {8,5}, {8,8} };

/*void IntilizeBoxIndex()
{
	for(i=0;i<9;i++)
	{
		BoxIndex[i].row=3*((i % 3));
		BoxIndex[i].col=3*((i / 3)+1);
	}
}*/


void intilize_sudoko()
{
	int i, j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			InputMatrix[i][j]=0;
			OutputMatrix[i][j]=0;
		}
	}
}


void read_no()
{
	int gIndex=0;
	//Grid-1
	{
		InputMatrix[0][1] = 1;
		gridIndex[0].row = 0;
		gridIndex[0].col = 1;
	

		InputMatrix[0][3] = 2;
		gridIndex[1].row = 0;
		gridIndex[1].col = 3;

		InputMatrix[0][5] = 8;
		gridIndex[2].row = 0;
		gridIndex[2].col = 5;

		InputMatrix[1][3] = 9;
		gridIndex[3].row = 1;
		gridIndex[3].col = 3;

		InputMatrix[1][5] = 5;
		gridIndex[4].row = 1;
		gridIndex[4].col = 5;

		InputMatrix[1][7] = 7;
		gridIndex[5].row = 1;
		gridIndex[5].col = 7;


		InputMatrix[2][0] = 2;
		gridIndex[6].row = 2;
		gridIndex[6].col = 0;

		InputMatrix[2][1] = 5;
		gridIndex[7].row = 2;
		gridIndex[7].col = 1;
		
		InputMatrix[2][2] = 6;
		gridIndex[8].row = 2;
		gridIndex[8].col = 2;

		InputMatrix[2][3] = 1;
		gridIndex[9].row = 2;
		gridIndex[9].col = 3;
		
		InputMatrix[2][6] = 3;
		gridIndex[ 10].row = 2;
		gridIndex[10].col = 6;

		InputMatrix[2][7] = 8;
		gridIndex[11].row = 2;
		gridIndex[11].col = 7;
	}
	//Grid-2
	{
		InputMatrix[3][5] = 6;
		gridIndex[12].row = 3;
		gridIndex[12].col = 5;

		InputMatrix[3][7] = 1;
		gridIndex[13].row = 3;
		gridIndex[13].col = 7;

		InputMatrix[3][8] = 8;
		gridIndex[14].row = 3;
		gridIndex[14].col = 8;

		InputMatrix[4][0] = 5;
		gridIndex[15].row = 4;
		gridIndex[15].col = 0;

		InputMatrix[4][1] = 6;
		gridIndex[16].row = 4;
		gridIndex[16].col = 1;

		InputMatrix[4][4] = 1;
		gridIndex[17].row = 4;
		gridIndex[17].col = 4;

		InputMatrix[4][7] = 9;
		gridIndex[18].row = 4;
		gridIndex[18].col = 7;

		InputMatrix[4][8] = 2;
		gridIndex[19].row = 4;
		gridIndex[19].col = 8;

		InputMatrix[5][0] = 8;
		gridIndex[20].row = 5;
		gridIndex[20].col = 0;
		gIndex=21;

		InputMatrix[5][1] = 7;
		gridIndex[gIndex].row = 5;
		gridIndex[gIndex].col = 1;
		gIndex++;

		InputMatrix[5][3] = 4;
		gridIndex[gIndex].row = 5;
		gridIndex[gIndex].col = 3;
		gIndex++;


	}

	//Grid-3
	{
		InputMatrix[6][1] = 4;
		gridIndex[gIndex].row = 6;
		gridIndex[gIndex].col = 1;
		gIndex++;


		InputMatrix[6][2] = 2;
		gridIndex[gIndex].row = 6;
		gridIndex[gIndex].col = 2;
		gIndex++;


		InputMatrix[6][5] = 1;
		gridIndex[gIndex].row = 6;
		gridIndex[gIndex].col = 5;
		gIndex++;


		InputMatrix[6][6] = 9;
		gridIndex[gIndex].row = 6;
		gridIndex[gIndex].col = 6;
		gIndex++;


		InputMatrix[6][7] = 5;
		gridIndex[gIndex].row = 6;
		gridIndex[gIndex].col = 7;
		gIndex++;


		InputMatrix[6][8] = 7;
		gridIndex[gIndex].row = 6;
		gridIndex[gIndex].col = 8;
		gIndex++;


		InputMatrix[7][1] = 9;
		gridIndex[gIndex].row = 7;
		gridIndex[gIndex].col = 1;
		gIndex++;

		InputMatrix[7][3] = 3;
		gridIndex[gIndex].row = 7;
		gridIndex[gIndex].col = 2;
		gIndex++;

		InputMatrix[7][5] = 7;
		gridIndex[gIndex].row = 7;
		gridIndex[gIndex].col = 5;
		gIndex++;

		InputMatrix[8][3] = 5;
		gridIndex[gIndex].row = 8;
		gridIndex[gIndex].col = 3;
		gIndex++;

		InputMatrix[8][5] = 2;
		gridIndex[gIndex].row = 8;
		gridIndex[gIndex].col = 5;
		gIndex++;

		InputMatrix[8][7] = 3;
		gridIndex[gIndex].row = 8;
		gridIndex[gIndex].col = 7;
		
		IndexCount=gIndex;
	}

}
void Intilize1stValue()
{
	int i,j, flag=0;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(OutputMatrix[i][j]==0)
			{
				FirstGridRow=i;
				FirstGirdCol=j;
				flag=1;
				break;
			}
			if(flag==1)
				break;
		}
	}
}

void BacktrackFor1stGird()
{
	int i, value;
	value=OutputMatrix[FirstGridRow][FirstGirdCol];
	for(i=1;i<9;i++)
	{
	
	   if((i != value) && (checkNumber(i, FirstGridRow  ,FirstGirdCol)))
	   {
		   OutputMatrix[FirstGridRow][FirstGirdCol]=i;
		   //return 1;
	   }
	}

	
    //printf("Invalid Sudoko");
	//return -1;
}

void InitilizeOutputMatrix()
{
	int i,j;
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			OutputMatrix[i][j]=InputMatrix[i][j];
	printf("\nAfter Copy:\n");
	printOutputMatrix();
}



void FindSolution()
{  
	int i,j;
	FILE *fp=0;
	for(i=0;i<9;i++)
	{
	  for(j=0;j<9;j++)
	  {
         if(OutputMatrix[i][j]==0) 
		 {
			 placeNumber(i,j);

		     fp = fopen("test.txt", "a");
			 fprintf(fp, "%d, %d, %d\n", i, j, OutputMatrix[i][j]);
			 fclose(fp);

		 }

	  }
	}
	fclose(fp);
}

void placeNumber(int row , int col)
{ 
	int i=row,j=col;
  	int newrow, newcolumn;
	int value;
	if (row > 9 || col > 9 || row < 0 || col < 0)
		return;
	value=getno(i,j);
	if(value!=-1)
		 OutputMatrix[i][j]=value;
	else 
	{
		OutputMatrix[i][j] = 0;
		int retVal = backtrack(i,j, &newrow, &newcolumn);
		if (retVal == -1)
		{
			return;
		}
        placeNumber(newrow , newcolumn);
		placeNumber(i,j);
	}

}

int getno(int i,int j)
{
	int sno=OutputMatrix[i][j]+1;
	if(checkOriginal(i,j))
	{
		return OutputMatrix[i][j];
	}

	while(!checkNumber(sno , i , j) && sno <= 9)
	{
		sno++;
	}
	if(sno==10)
		return -1;
	return sno;
}

int checkNumber(int sno, int row ,int col)
{
	if(CheckRow(sno , row , col))
	{
		if(CheckCol(sno ,row, col))
		{
			if(CheckBox( sno , row, col))
			{
				return true;
			}
		}
	}
	return false;
}

int CheckRow(int sno , int row, int col)
{
	int i;
	for(i=0;i<9;i++)
	{
		if(sno==OutputMatrix[row][i] && col != i)
			return false;
	}
	return true;
}

int CheckCol(int sno , int row, int col)
{
	int i;
	for(i=0;i<9;i++)
		if(sno==OutputMatrix[i][col] && row != i)
			return false;
	return true;
}

int CheckBox(int sno , int row, int col)
{
	int i,j, boxrow , boxcol;
	for(i=0;i<9;i++)
	{
		if(row <= BoxIndex[i][0] && col <= BoxIndex[i][1])
		{
			boxrow=BoxIndex[i][0]-2;
			boxcol=BoxIndex[i][1]-2;
			break;
		}
	}

	for(i=0;i<3;i++)
	{
        for(j=0;j<3;j++)
		{
			if(i+boxrow!=row && j+boxcol!=col && OutputMatrix[i+boxrow][j+boxcol]==sno)
				return false;
		}
	}
	return true;
}
int checkOriginal(int row,int col)
{
	int i;
	for(i=0;i<IndexCount;i++)
	{
		if(row==gridIndex[i].row && col==gridIndex[i].col)
			return true;
	}
	return false;
}

int backtrack(int oldrow , int oldcol, int *newrow , int *newcol)
{
	*newrow=oldrow;
	*newcol=oldcol;
	if(*newrow==0 && *newcol==0)
		return -1;
	if(oldcol< 9 && oldcol>0)
		*newcol=oldcol-1;
	else if(oldcol==0 && *newrow > 0)
	{
		*newrow=oldrow-1;
		*newcol=8;
	}

	if(*newrow < 0 || *newcol < 0)
	{
		*newrow = 0;
		*newcol = 0;
		return -1;
	}
	if(checkOriginal(*newrow, *newcol))
		return backtrack(*newrow, *newcol , newrow, newcol);
	else
		return 1;
}

void printInputMatrix()
{
	int i,j;
	printf("Input Matrix \n");
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			printf("%3d", InputMatrix[i][j]);
		}
		printf("\n");
	}
}
void printOutputMatrix()
{
	int i,j;
	printf("Output Matrix \n");
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			printf("%3d", OutputMatrix[i][j]);
		}
		printf("\n");
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	intilize_sudoko();
	read_no();
	InitilizeOutputMatrix();	
	Intilize1stValue();
	FindSolution();
	printInputMatrix();
	printOutputMatrix();
	getch();
	return 0;
}
