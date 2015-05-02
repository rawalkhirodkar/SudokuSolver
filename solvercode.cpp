#include<simplecpp>
#include<fstream>

class Emptycell{// class for emptycells
public:
int column;int row;
int probable[9],probable_size;//probable_size is number of possible candidates after extraction
bool single;
Emptycell(){for(int i=0;i<9;i++){probable[i]=0;}
			single=false;return;}//constructor
};
	
void input(int board[9][9])//function for grid input
{int num;

	for(int i=0;i<9;i++)//i is row and j is column
		{for(int j=0;j<9;j++)
			{cin>>num;board[i][j]=num;}
		}
}

bool check(int board[9][9],int row,int column,int p)//p is value,,,,,function for conflict check
{int bigrow,bigcolumn;
for(int j=0;j<9;j++)
	{if(board[row][j]==p)
		{return false;}
	}//checking row-wise
		
	for(int i=0;i<9;i++)
	{if(board[i][column]==p)
		{return false;}
	}	//checking column-wise
		
if(row/3==0){bigrow=0;}if(row/3==1){bigrow=1;}if(row/3==2){bigrow=2;}//assigning big square family
if(column/3==0){bigcolumn=0;}if(column/3==1){bigcolumn=1;}if(column/3==2){bigcolumn=2;}

int br=bigrow,bc=bigcolumn;
for(int i=0;i<3;i++)
	{for(int j=0;j<3;j++)
		{if(board[br*3+i][bc*3+j]==p)//checking big squarewise
			{return false;}
			}
	}
return true;}

int emptyfill(int board[9][9],Emptycell empty[])//function to fill emptycell addresses
{int count=0;
for(int i=0;i<9;i++)
		{for(int j=0;j<9;j++)
		if(board[i][j]==0)
		{empty[count].column=j;empty[count].row=i;count++;}
		}
return count;}

void candidate(int board[9][9],Emptycell empty[],int size)//function to extract probable candidates ....size of emptycell
{int junk[9];
int r,c;
for(int i=0;i<size;i++)
{r=empty[i].row;c=empty[i].column;

	for(int b=0;b<9;b++){junk[b]=-1;}//filling with "-1"	
		
		for(int a=0;a<9;a++)//checking row-wise
		{if(board[r][a]!=0)
			{junk[board[r][a]-1]=0;}
		}
	
			
		for(int a=0;a<9;a++)//checking column-wise
		{if(board[a][c]!=0)
			{junk[board[a][c]-1]=0;}
		}
		
		int bigrow,bigcolumn;
		if(r/3==0){bigrow=0;}if(r/3==1){bigrow=1;}if(r/3==2){bigrow=2;}//assigning big square family
		if(c/3==0){bigcolumn=0;}if(c/3==1){bigcolumn=1;}if(c/3==2){bigcolumn=2;}

		int br=bigrow,bc=bigcolumn;
		for(int k=0;k<3;k++)
			{for(int j=0;j<3;j++)
				{if(board[br*3+k][bc*3+j]!=0)//checking big squarewise
					{junk[board[br*3+k][bc*3+j]-1]=0;}
				}	
			}
int count=0;				
for(int a=0;a<9;a++){if(junk[a]==-1){empty[i].probable[count]=a+1;count++;}}
}
}

void singlet(Emptycell empty[],int& size)//function to check for single probabilities
 {for(int i=0;i<size;i++){if(empty[i].probable[1]==0&&empty[i].probable[0]!=0){empty[i].single=true;}}
 }
 
 
void update_emptycell(int board[9][9],Emptycell empty[],int& size)//function to update emptycell...itself can solve easy grids
{singlet(empty,size);
for(int i=0;i<size;i++)
	{if(empty[i].single==true){board[empty[i].row][empty[i].column]=empty[i].probable[0];
								for(int j=i;j<size-1;j++){empty[j]=empty[j+1];}
								size=size-1;}
								}

for(int i=0;i<size;i++){
  for(int j=0;j<9;j++){empty[i].probable[j]=0;} }//Recreating the probable array to "0"
  
candidate(board,empty,size);
singlet(empty,size);bool a;
for(int i=0;i<size;i++){if(empty[i].single==true){a=true;break;}else{a=false;}}

if(a==true){update_emptycell(board,empty,size);}//recursion
for(int i=0;i<size;i++)
  {for(int j=0;j<9;j++){if(empty[i].probable[j]==0){empty[i].probable_size=j;break;} }}
  }

void solver(int board[9][9],Emptycell empty[],int element[], int& size, int& k,bool& verify,int& count)
{while(k<size)
	{
		if(element[k]<empty[k].probable_size){
	int row=empty[k].row; int column=empty[k].column; int val=empty[k].probable[element[k]];
	verify=check(board,row,column,val);
	element[k]=element[k]+1;
	if(verify==true){
		       board[empty[k].row][empty[k].column]=empty[k].probable[element[k]-1];
		       k++;  }
	else if(verify==false){
		        if(element[k]<empty[k].probable_size)
				{   board[empty[k].row][empty[k].column]=0;
					}
				
				else{element[k]=0;
					board[empty[k].row][empty[k].column]=0;
					if(k>0){ k--;count=count+1; 
						 }
			}
	}
	}
	  else{element[k]=0;
					board[empty[k].row][empty[k].column]=0;
					if(k>0){ k--;count =count+1;
					         	} }   
}
}//end of function

	
main_program{
int board[9][9];
Emptycell empty[81];//class object
input(board);
cout<<endl<<endl;	
for(int i=0;i<9;i++)//displaying
	{for(int j=0;j<9;j++)
		{
		cout<<board[i][j];
		}
		cout<<endl;
	}

int m=emptyfill(board,empty);	
candidate(board,empty,m);
update_emptycell(board,empty,m);

if(m!=0){
	bool verify;
	int element[m];
		for(int i=0;i<m;i++)
			{element[i]=0;}
	int k=0;int count=0;
	solver(board,empty,element,m,k,verify,count);
	cout<<count;
}

cout<<endl<<check(board,0,2,4)<<endl;

	for(int i=0;i<9;i++)//displaying
	{for(int j=0;j<9;j++)
		{
		cout<<board[i][j]<<" ";
		}
		cout<<endl;
	}
}





	
