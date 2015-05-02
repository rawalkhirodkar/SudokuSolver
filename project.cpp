#include<simplecpp>
#include<fstream>
#include<time.h>

string itos(int i) // function for converting an integer to a string
{
	
	string s=""; string temp;
	
	if(i>0){ 
			while(i>0)
			{
			  char ch=(i%10)+48;
			  s=s+ch; i=i/10;
			}
			temp="";
			
			for(unsigned int i=0;i<s.length();i++)
			{ temp=temp+s[s.length()-1-i]; } 
		   }
		
	else if(i==0){ temp="0"; }
	else if(i<0)
			{ 
				int m=-i;
				while(m>0)
				{
				   char ch=(m%10)+48;
				   s=s+ch; m=m/10;
				}
				temp="-";
				
				for(unsigned int i=0;i<s.length();i++)
				{ temp=temp+s[s.length()-1-i]; } 
			}
	return temp;
 }//function ends

class griddata{ // class used in game interface
	public:
	char type;
    short num;
    
    griddata(){ type = 'u'; num = 0; return; }//CONSTRUCTOR
    
    griddata operator=(griddata p){ type=p.type; num=p.num; return*this;}//operator overloaded
};//class definition ends

int numbergrid() // function for displaying number grid
{
	Rectangle array[9]; Text txt[9];
	
	for(int i=0;i<9;i++){ 
		array[i].reset(470+i*20,800,20,20);
		string s=itos(i+1);
		txt[i].reset(470+i*20,801,s); }
		
	int x=getClick(); return x;	
}//function ends

void clickfunction(int x,int y, griddata tempdata[9][9], Text grid[9][9], int& moves, Text& movenum, int w6) 
{
   if(!((x<0||x>8) || (y<0 || y>8))){
				   cout<<x<<" "<<y<<endl; string s;
				   
				   if(tempdata[x][y].type=='u') // filling number in empty square
					   {
					   moves=moves+1; cout<<moves;
					   movenum.reset(910+w6+20,450,itos(moves));
					   
					   int k=numbergrid(); int x1=(k/65536-460)/20; int y1= ((k % 65536)-790)/20;
					   
					   if(x1>=0 && x1<9 && y1==0)
					   {
						  string s=itos(x1+1);
						  grid[x][y].reset(470+x*20,370+y*20,s);
						  tempdata[x][y].num=x1+1;
						} 
					   else{ grid[x][y].reset(470+x*20,370+y*20,"");
							 tempdata[x][y].num=0;
						    }
						    
					   for(int i=0;i<9;i++) // checking conflicts for number filled in empty square
							{ 
						   if(tempdata[x][i].num==tempdata[x][y].num && y!=i && tempdata[x][i].num!=0)
						      { 
							   Rectangle red(470+x*20,370+y*20,20,20); red.setFill(true);   
							   repeat(2){ red.show(); wait(1); red.hide(); wait(1); } 
							   }
						   if(tempdata[i][y].num==tempdata[x][y].num && x!=i && tempdata[i][y].num!=0)
						      { 
							   Rectangle red(470+x*20,370+y*20,20,20); red.setFill(true);   
							   repeat(2){ red.show(); wait(1); red.hide(); wait(1); }
						      }   
							 }//for loop ends
							 
					   for(int i=3*(x/3);i<(3*(x/3))+3;i++)
					       {
						   for(int j=3*(y/3);j<(3*(y/3))+3;j++)
						       {
							   if(tempdata[i][j].num==tempdata[x][y].num && (y!=j || x!=i) && tempdata[i][j].num!=0){ 
							   Rectangle red(470+x*20,370+y*20,20,20); red.setFill(true);   
							   repeat(2){ red.show(); wait(1); red.hide(); wait(1); } }
							   } 
							}
						}
				}//end of bigger if statement
}//function ends

void filldata( griddata tempdata[9][9], Text grid[9][9], int x, int y, Rectangle fixednum[9][9], int& moves, Text& movenum, int w6)
{
	   for(int i=0;i<9;i++) // function used for loading previos game and refreshing grid
	   {
		   for(int j=0;j<9;j++)
		   {
			fixednum[i][j].reset(470+i*20,370+j*20,20,20);
		   }
       }
	for(int i=0;i<9;i++)
	{
	        for(int j=0;j<9;j++)
	        { 
			  if(tempdata[i][j].type=='f')
			  {
		       fixednum[i][j].reset(470+i*20,370+j*20,16,16);
               string conf=itos(tempdata[i][j].num);
               grid[i][j].reset(470+i*20,370+j*20,conf); 
               }
               
              else{ 
					  if(tempdata[i][j].num!=0)
					  {   
					  string conf=itos(tempdata[i][j].num);
					  grid[i][j].reset(470+i*20,370+j*20,conf);
					  }
						 else{ grid[i][j].reset(470+i*20,370+j*20,"");}
                    }
                    
              clickfunction(x,y,tempdata,grid,moves,movenum,w6);  
            }
     }
     
}//function ends

void complgame(griddata tempdata[9][9], griddata soldata[9][9], griddata newdata[9][9], bool& next, int h, int w4, bool& a, int moves, int hints, int& hscore, int& level)
{ // checks the matching of tempdata and soldata 
	bool val;
	for(int i=0;i<9; i++)
	{
		for(int j=0;j<9;j++)
		{
			if(tempdata[i][j].num==soldata[i][j].num)
			{ val=true; }
			
			else if(tempdata[i][j].num!=soldata[i][j].num)
				  { val=false; break;}
				  
		} 
		
		if(val==false)
		{ break; }
     }
     
	if(val==true)
	{ 
		   Text complete(200,700,"CONGRATULATIONS! GAME COMPLETE..."); // displays score of user
		   Text scorelabel(200,650,"YOUR SCORE :");
		   int score= (100-moves) - pow(2,(3-hints)) ;
		   
		   if(score>hscore)
		   { hscore = score;  
		   Text congohscore(200,750,"NEW HIGH SCORE"); 
		   
		   if(level==1)
				   {
						ofstream onpsol1("l1",ios::out);
						for(int i=0;i<9;i++){
						  for(int j=0;j<9;j++){ onpsol1<<newdata[i][j].type<<" "<<newdata[i][j].num<<" ";}cout<<endl; } onpsol1<<level<<endl<<hscore; 
					}
					
			else if(level==2)
			       { 
					ofstream onpsol2("l2",ios::out);
					for(int i=0;i<9;i++)
					{
					  for(int j=0;j<9;j++)
							 { onpsol2<<newdata[i][j].type<<" "<<newdata[i][j].num<<" ";
							 } 
							 
					  cout<<endl;
					 } 
					 onpsol2<<level<<endl<<hscore;
			       }
			       
			else if(level==3)
			{
				ofstream onpsol3("l3",ios::out);
				
				for(int i=0;i<9;i++)
				{
	              for(int j=0;j<9;j++)
					  { onpsol3<<newdata[i][j].type<<" "<<newdata[i][j].num<<" ";
					  } 
					  
	              cout<<endl; 
	             } 
	              onpsol3<<level<<endl<<hscore;
			 }
		   }
		   
		   Text your_sc(250,650,itos(score));
		   
		   Rectangle newBox(700,650,textWidth("NEXT LEVEL")+5,h+5); // pathway to next level
		   int w_newBox=(textWidth("QUIT GAME")+5)/2;
		   Text txt_newBox(700,650,"NEXT LEVEL");
		   
		   while(getClick())
		   { 
             int position = getClick(); 
             int x=position/65536; int y=position % 65536;
             
		     if(x>700-w4 && x<700+w4 && y>695-h && y<705+h)
				 {
				   a=false; break; 
				 }
			 
		     else if(x>700-w_newBox && x<700+w_newBox && y>645-h && y<655+h)
				 {
				   next=true; break;
				  }
			}
		}//end of bigger if statement  
}//end of function
	
void Sudoku(griddata newdata[9][9],griddata soldata[9][9],griddata userdata[9][9], int h, bool& a, int w1, bool& next, int& level, int& hscore){
   Rectangle Box2(400,100,textWidth("SAVE GAME")+5,h+5); int w2=(textWidth("SAVE GAME")+5)/2;
   Text txtBox2(400,100,"SAVE GAME"); 
   Rectangle Box3(700,100,textWidth("LOAD PREVIOUS GAME")+5,h+5); int w3=(textWidth("LOAD PREVIOUS GAME")+5)/2;
   Text txtBox3(700,100,"LOAD PREVIOUS GAME");
   Rectangle Box4(700,700,textWidth("QUIT GAME")+5,h+5); int w4=(textWidth("QUITGAME")+5)/2;
   Text txtBox4(700,700,"QUIT GAME"); 
   Rectangle Box5(900,500,textWidth("HINTS LEFT")+5,h+5); int w5=(textWidth("HINTS LEFT")+5)/2;
   Text txtBox5(900,500,"HINTS LEFT"); int hints=3;
   string hint=itos(hints); Text hintnum(910+w5,500,hint);
   Rectangle Box6(900,450,textWidth("NUMBER OF MOVES :")+5,h+5); int w6=(textWidth("MOVES LEFT")+5)/2;
   Text txtBox6(900,450,"NUMBER OF MOVES:"); int moves=0;
   string move=itos(moves); Text movenum(910+w6+20,450,move);
   Rectangle r1(550,450,190,190); Text grid[9][9];
   Rectangle array[9][9]; Rectangle fixednum[9][9]; // making the entire Sudoku grid
   for(int i=0;i<9;i++){
	   for(int j=0;j<9;j++){
		   fixednum[i][j].reset(470+i*20,370+j*20,20,20);
	   }
   }
   for(int j=0;j<9;j++){ 
   for(int i=0;i<9;i++){ array[i][j].reset(470+i*20,370+j*20,20,20) ; 
                          }
   }
   
   Rectangle junk1[4],junk2[4];
   for(int i=0;i<4;i++){
	   junk1[i].reset(460+i*20*3,450,2,180); junk1[i].setFill(true); 
	   junk2[i].reset(550,360+i*3*20,180,2); junk1[i].setFill(true);
   }
   griddata tempdata[9][9];
   for(int i=0;i<9;i++){
	   for(int j=0;j<9;j++){ tempdata[i][j]=newdata[i][j]; }}
   
   for(int i=0;i<9;i++){
	   for(int j=0;j<9;j++){ if(tempdata[i][j].type=='f'){
		       fixednum[i][j].reset(470+i*20,370+j*20,16,16);
               string conf=itos(tempdata[i][j].num);
               grid[i][j].reset(470+i*20,370+j*20,conf); } } }
   
   while(getClick()){ // using getClick to use features
       int position = getClick(); 
       int x=((position/65536)-460)/20; int y=((position % 65536)-360)/20;
       clickfunction(x,y,tempdata,grid,moves,movenum,w6);
       complgame(tempdata,soldata,newdata,next,h,w4,a,moves,hints,hscore,level); 
	   if(next==true){ break; }
	   if(a==false){ break; }
       if(position/65536>400-w2 && position/65536<400+w2 && (position % 65536)>100-h-5 && (position % 65536)<100+h+5){
          ofstream output("userfile",ios::out);
          for(int i=0;i<9;i++){
			  for(int j=0;j<9;j++){ userdata[i][j]=tempdata[i][j]; } }
          for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){ output<<userdata[i][j].type<<" "<<userdata[i][j].num<<endl; } }
            output<<hints<<endl; output<<level<<endl; output<<moves<<endl<<hscore;
        }
       else if(position/65536>700-w3 && position/65536<700+w3 && (position % 65536)>100-h-5 && (position % 65536)<100+h+5){       
          ifstream inp2("userfile",ios::in);
          for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){ inp2>>userdata[i][j].type>>userdata[i][j].num; } }
            inp2>>hints; inp2>>level; inp2>>moves; inp2>>hscore;
            if(level==1){ 
				ifstream inpsol1("soldata_l1",ios::in);
				for(int i=0;i<9;i++){
	              for(int j=0;j<9;j++){ inpsol1>>soldata[i][j].type>>soldata[i][j].num;} }
			  }
			else if(level==2){ 
				ifstream inpsol2("soldata_l2",ios::in);
				for(int i=0;i<9;i++){
	              for(int j=0;j<9;j++){ inpsol2>>soldata[i][j].type>>soldata[i][j].num;} }
			  }
			else if(level==3){
				ifstream inpsol3("soldata_l3",ios::in);
				for(int i=0;i<9;i++){
	              for(int j=0;j<9;j++){ inpsol3>>soldata[i][j].type>>soldata[i][j].num;} }
			  }
			  for(int i=0;i<9;i++){
			  for(int j=0;j<9;j++){ tempdata[i][j] = userdata[i][j]; } } 
          filldata(tempdata,grid,x,y,fixednum,moves,movenum,w6);
          hint=itos(hints); hintnum.reset(910+w5,500,hint);
          movenum.reset(910+w6+5,450,itos(moves));
         }
        else if(position/65536>100-w1 && position/65536<100+w1 && (position % 65536)>100-h && (position % 65536)<100+h){
			for(int i=0;i<9;i++){
	          for(int j=0;j<9;j++){ tempdata[i][j]=newdata[i][j]; }} hints=3;
            filldata(tempdata,grid,x,y,fixednum,moves=0,movenum,w6);
            hint=itos(hints); hintnum.reset(910+w5,500,hint);
         }
        else if(position/65536>700-w4 && position/65536<700+w4 && (position % 65536)>695-h && (position % 65536)<705+h){
			a=false; break; 
         }
        else if(position/65536>900-w5 && position/65536<900+w5 && (position % 65536)>495-h && (position % 65536)<505+h){
		    if(hints>0){
				int gridpos=getClick();
				int gridpos_x=((gridpos/65536)-460)/20; int gridpos_y=((gridpos % 65536)-360)/20;
				if(!((gridpos_x<0||gridpos_x>8) || (gridpos_y<0 || gridpos_y>8))){
					int actual=soldata[gridpos_x][gridpos_y].num;
					tempdata[gridpos_x][gridpos_y].num=soldata[gridpos_x][gridpos_y].num;
					grid[gridpos_x][gridpos_y].reset(470+gridpos_x*20,370+gridpos_y*20,itos(actual));
                    hints=hints-1;
                    hintnum.reset(910+w5,500,itos(hints));
				}
			}
			if(hints==0){
				hintnum.reset(910+w5,500,"0");
				Rectangle red(900,500,textWidth("HINTS LEFT")+5,h+5); red.setFill(true);   
                repeat(2){ red.show(); wait(1); red.hide(); wait(1); }
			}
         }           
}
   wait(0);
}

void fill_solver(int x, int y, Text grid[9][9], Rectangle fixednum[9][9],int board[9][9]){ // getting input for sudoku_solver
	if(!((x<0||x>8) || (y<0 || y>8))){
	   string s;
	   int k=numbergrid(); int x1=(k/65536-460)/20; int y1= ((k % 65536)-790)/20;
       if(x1>=0 && x1<9 && y1==0){
		  string s=itos(x1+1);
          grid[x][y].reset(470+x*20,370+y*20,s);
          fixednum[x][y].reset(470+x*20,370+y*20,16,16); board[x][y]=(x1+1); } 
       else{ grid[x][y].reset(470+x*20,370+y*20,""); 
             fixednum[x][y].reset(470+x*20,370+y*20,20,20); board[x][y]=0;}
   }
}

class Emptycell{// class for emptycells
public:
int column;int row;
int probable[9],probable_size;//probable_size is number of possible candidates after extraction
bool single;
Emptycell(){for(int i=0;i<9;i++){probable[i]=0;}
			single=false;return;}//constructor
};

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

void solver(int board[9][9],Emptycell empty[],int element[], int& size, int& k,bool& verify,bool& invalid,int& count)
{while(k<size) // algorithm implemented
	{count=count+1;
	if(element[k]<empty[k].probable_size)	
	{int row=empty[k].row; int column=empty[k].column; int val=empty[k].probable[element[k]];
	verify=check(board,row,column,val);
	element[k]=element[k]+1;
	if(verify==true){
		       board[empty[k].row][empty[k].column]=empty[k].probable[element[k]-1];
		       k++;}
	else if(verify==false){
		        if(element[k]<empty[k].probable_size)
				{   board[empty[k].row][empty[k].column]=0; invalid=false;
					}
				
				else{element[k]=0;
					 board[empty[k].row][empty[k].column]=0;
					 if(k>0){ k--;
					 board[empty[k].row][empty[k].column]=0;} 
					 else if(k==0){ invalid=true; break;  }
					 } }
			}
	
	else{ element[k]=0;
		  board[empty[k].row][empty[k].column]=0;
					 if(k>0){ k--;
					 board[empty[k].row][empty[k].column]=0; }
					 else if(k==0){ invalid=true; break;  }
					 } 		
			
	}
}
//end of function



void Sudoku_solver(bool& quit_solver, int h,int w1) // initCanvas implementation for Sudoku_solver
{
	 Rectangle Box3(700,100,textWidth("SOLVE IT")+5,h+5); int w3=(textWidth("SOLVE IT")+5)/2;
     Text txtBox3(700,100,"SOLVE IT");
     
	 Rectangle Box4(700,700,textWidth("QUIT SOLVER")+5,h+5); int w4=(textWidth("QUIT SOLVER")+5)/2;
     Text txtBox4(700,700,"QUIT SOLVER");
     
     Rectangle Box6(900,450,textWidth("DONE INPUTTING")+5,h+5); int w6=(textWidth("DONE INPUTTING")+5)/2;
     Text txtBox6(900,450,"DONE INPUTTING"); bool input=true;
     
     Rectangle r1(550,450,190,190); Text grid[9][9]; // making the grid
     Rectangle array[9][9]; Rectangle fixednum[9][9]; Text unsolvable;
     int board[9][9];
     
     for(int i=0;i<9;i++)
     { 
		 for(int j=0;j<9;j++)
			{ board[i][j]=0 ; 
			}
     }
     
     for(int i=0;i<9;i++)
     {
		   for(int j=0;j<9;j++)
			   {
				 fixednum[i][j].reset(470+i*20,370+j*20,20,20);
			   }
     }
     
     for(int j=0;j<9;j++)
     { 
		 for(int i=0;i<9;i++)
				 { array[i][j].reset(470+i*20,370+j*20,20,20) ; 
				 }
     }
   
     Rectangle junk1[4],junk2[4];
     for(int i=0;i<4;i++)
     {
	   junk1[i].reset(460+i*20*3,450,2,180); junk1[i].setFill(true); 
	   junk2[i].reset(550,360+i*3*20,180,2); junk1[i].setFill(true);
     }
     
	 while(getClick()) // using getClick for features
	 { 
       int position = getClick(); 
       int x=((position/65536)-460)/20; int y=((position % 65536)-360)/20;
       
       if(input==true)
       { fill_solver(x,y,grid,fixednum,board);
       }
	   if(position/65536>700-w4 && position/65536<700+w4 && (position % 65536)>695-h && (position % 65536)<705+h)
	   {
		quit_solver=true; break; // quitting solver
        }
        
       else if(position/65536>900-w6 && position/65536<900+w6 && (position % 65536)>445-h && (position % 65536)<455+h)
       {
	         input=false; // completing input
	         
	   }
	   
	   else if(position/65536>700-w3 && position/65536<700+w3 &&(position % 65536)>95-h && (position % 65536)<105+h)
	   {
		     
		     Emptycell empty[81];//class object
			
	         int m=emptyfill(board,empty);	
             candidate(board,empty,m);
             update_emptycell(board,empty,m);

             int k=0;int count=0;bool invalid=false;
             
             if(m!=0)
             {
	            bool verify;
	            int element[m];
		        for(int i=0;i<m;i++)
			      {element[i]=0;}
	
	            solver(board,empty,element,m,k,verify,invalid,count);
	             
             }
            
		     ofstream out1;
		     out1.open("solved_grid",ios::out);
		     
	         for(int i=0;i<9;i++)
				 { 
					 for(int j=0;j<9;j++)
				         { out1<<board[j][i]<<" "; 
				         }
				  out1<<endl; 
			     }
			     
	         out1.close();
			// filling the solved grid for valid sudoku grid
				if(invalid==true)
				{unsolvable.reset(200,700,"INVALID INPUT!! NOT SOLVED!!!");
				}
				
				else
				{ unsolvable.reset(200,700,"SUDOKU SOLVED!!!");
				
					 for(int i=0;i<9;i++)
					 {
						 for(int j=0;j<9;j++)
						 {
							fixednum[i][j].reset(470+i*20,370+j*20,20,20);
							grid[i][j].reset(470+i*20,370+j*20,itos(board[i][j]));
						 }
					 
					  }
	             }
	    }
	    
	   else if(position/65536>100-w1 && position/65536<100+w1 && (position % 65536)>100-h && (position % 65536)<100+h)
	   {
		   for(int i=0;i<9;i++) // refreshing grid for new input
		   {
			   for(int j=0;j<9;j++)
			   {
				   fixednum[i][j].reset(470+i*20,370+j*20,20,20);
				   grid[i][j].reset(470+i*20,370+j*20,"");
				   input=true; 
				   board[i][j]=0;
				   unsolvable.reset(200,700,"");
			   }
		   }
	    }
      }//end of while loop
}//end of function

main_program
{
   cout<<"WELCOME TO THE WORLD OF SUDOKU"<<endl;
   cout<<"PRESS P: for playing a game"<<endl<<"PRESS S: for giving an unfilled sudoku as input and computer will solve it!";
   cout<<endl<<"PRESS X: for exiting the program";
   
   char ch;
   while(cin>>ch)
   {
	   
	   if(ch=='P')
	   {
		   initCanvas("Sudoku",1100,900);  
		   Rectangle Box1(100,100,textWidth("NEW GAME")+5,textHeight()+5); 
		   
		   int w1=(textWidth("NEW GAME")+5)/2; 
		   int h=(textHeight()+5)/2;
		   Text txtBox1(100,100,"NEW GAME"); 
		   bool a=true; 
		   bool next=false;
		   int level;
		   int hscore;
		   
		   int pos=getClick(); 
		   int x=pos/65536; 
		   int y=pos%65536;
		   
		   if(x>100-w1 && x<100+w1 && y>100-h && y<100+h)
		   {
		   
				   griddata newdata[9][9],	soldata[9][9], userdata[9][9];
				   
				   ifstream inp1("l1",ios::in);
				   
				   for(int i=0;i<9;i++)
				   {
					   for(int j=0;j<9;j++)
						   { inp1>>newdata[i][j].type>>newdata[i][j].num;
						   }
				   }  
				   
				   inp1>>level; 
				   inp1>>hscore;
				   
				   ifstream inp2("soldata_l1",ios::in);
				   
				   for(int i=0;i<9;i++)
				   {
					   for(int j=0;j<9;j++)
					   { inp2>>soldata[i][j].type>>soldata[i][j].num;
					   } 
					}
					
				   Sudoku(newdata, soldata, userdata, h, a, w1, next,level, hscore);
				   
				   if(a==false)
				   { wait(0);
				   }
				   
				   else if(next==true)
				   { 
					   a=true; next=false;
					   griddata newdata[9][9];
					   
					   ifstream inp1_2("l2",ios::in);
					   
					   for(int i=0;i<9;i++)
					   {
							for(int j=0;j<9;j++)
							{ inp1_2>>newdata[i][j].type>>newdata[i][j].num;
							}
					   }  
					   
					   inp1_2>>level; inp1_2>>hscore;
					   
					   ifstream inp2_2("soldata_l2",ios::in);
					   
					   for(int i=0;i<9;i++)
					   {
							for(int j=0;j<9;j++)
							{ inp2_2>>soldata[i][j].type>>soldata[i][j].num;
							}
					   }
					   
					   Sudoku(newdata, soldata, userdata,h, a, w1, next, level, hscore);
					   	
					   if(a==false)
					   { wait(0);
					   }
					   
					   else if(next==true)
					   {
						   a=true; next=false;   
						   griddata newdata[9][9];
						   
						   ifstream inp1_3("l3",ios::in);
						   
						   for(int i=0;i<9;i++)
						   {
								for(int j=0;j<9;j++)
								{ inp1_3>>newdata[i][j].type>>newdata[i][j].num;}
						   } 
						   
						   inp1_3>>level;
						   inp1_3>>hscore;
						   
						   ifstream inp2_3("soldata_l3",ios::in);
						   
						   for(int i=0;i<9;i++)
						   {
								for(int j=0;j<9;j++)
								{ inp2_3>>soldata[i][j].type>>soldata[i][j].num;} 
						    }
						    
						   Sudoku(newdata, soldata, userdata,h, a, w1, next,level, hscore);	
						   
						   if(a==false)
						   { wait(0);
						   }
						   
						   else if(next==true)
						   {wait(0);
						   } 
						}
				   } 
		   } 
       
       
        }
        
   else if(ch=='S')
   {
	   initCanvas("Sudoku_Solver",1100,900);
	   bool quit_solver=false;
	   
	   Rectangle Box1(100,100,textWidth("NEW INPUT")+5,textHeight()+5); 
	   int w1=(textWidth("NEW INPUT")+5)/2; int h=(textHeight()+5)/2;
       Text txtBox1(100,100,"NEW INPUT");
       
	   while(getClick())
	   { 
        int pos=getClick(); int x=pos/65536; int y=pos%65536;
        
        if(x>100-w1 && x<100+w1 && y>100-h && y<100+h)
			{
				Sudoku_solver(quit_solver,h,w1);
				
				if(quit_solver==true)
					{ break; }
            }
	   }
	   
   }
   
   else if(ch=='X')
   {
	   break; 
	}
	   
   else
   { 
	   cout<<"INVALID COMMAND"<<endl;
       cout<<"ENTER COMMAND AGAIN";
	   
   }
  }//end of while loop
}// end of main program



