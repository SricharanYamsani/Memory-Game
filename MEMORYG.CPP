#include<fstream.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
const int size=15;
char arr[4][6]={"ABCDEF","GHIJKL","MNOPQR","STUVWX"};
char dup[4][6]={"ABCDEF","GHIJKL","MNOPQR","STUVWX"};
char vl3[4][6]={"-+~0!@","#$%&*=","-+~0!@","#$%&*=" };
struct players
{
 char name[20];
 int score;
}Player[15];
int dcd=0,try=18;
int i,j,l,flag=-1;
char ex,ex1;

void swap(char &a,char &b);
void shufflev();
void board();
void checkwin();
int play();
void highscore();
void placescore();


void main()
{
clrscr();
int choice;
char esc;
cout<<"\t\t\t  MEMORY GAME:INSTRUCTIONS";
cout<<"  \n  Memory Game is a Single Player Game. The game consists of a grid of";
cout<<"  \n  24 tiles arranged in 4 rows and 6 columns marked by the letters A ";
cout<<"  \n  to X. There a set of 12 symbols each appearing twice in the grid, ";
cout<<"  \n  hidden beneath the 24 letters.";
cout<<"  \n  The player is made to open two tiles of the grid, and if both tiles";
cout<<"  \n  are the same i.e. they contain the same symbol, the tiles remain open";
cout<<"  \n  for the rest of the game, Otherwise the tiles are again turned upside";
cout<<"  \n  with the letters being shown on the grid";
cout<<"  \n  The game continues until the player successfully opens all tiles or he/she";
cout<<"\n  is out of tries.";
cout<<"\n\n  The player with the least no. of tries used enters the HIGHSCORES";
cout<<"\n   CHART.";
cout<<"\n   PRESS ANY CHARACTER TO CONTINUE";
cin>>esc;
clrscr();
cout<<"\t\t\tMEMORY GAME:";
cout<<"\n\t\t\t1.Play\n\t\t\t2.Highscores\n\t\t\t3.Exit";
cout<<"\n\t\t\tEnter Choice:";
cin>>choice;
switch(choice)
{
case 1:if(play());
       placescore();
       if(flag!=-1)
       highscore();
       break;
case 2:highscore();
       break;
case 3:exit(0);
default:{cout<<"Wrong Choice. Breaking...";exit(0);}
}

getch();
}

//To swap two characters
void swap(char &a,char &b)
{
char ch1,ch2;
ch1=a ;
ch2=b;
a=ch2;
b=ch1;
}

//To Shuffle the characters of the vl3 array
void shufflev()
{
  randomize();
  cout<<"\n";
  for(l=0;l<(random(25)+20);l++)
  {
   if(random(4))
   { int sch1,sch2,sch3,sch4;
     sch1=random(4);
     sch2=random(6);
     sch3=random(4);
     sch4=random(6);
     swap(vl3[sch1][sch2],vl3[sch3][sch4]);
   }
  }
}

//To set the display for playing the game
void board()
{
cout<<"\n\t\t\t _____ _____ _____ _____ _____ _____";
for(i=0;i<4;i++)
{ cout<<"\n\t\t\t|     |     |     |     |     |     |\n";
  for( j=0;j<6;j++)
    { if(j%6==0)
       cout<<"\t\t\t|  "<<arr[i][j]<<"  ";
       else
       cout<<"|  "<<arr[i][j]<<"  ";
     }
   cout<<"|\n\t\t\t|_____|_____|_____|_____|_____|_____|";
}

}

//To decide if the has won
void checkwin()
{
  int count=0;
  for(i=0;i<4;i++)
  for(j=0;j<6;j++)
  {  if(arr[i][j]!=dup[i][j])
     count++;
  }
  if(count==24)
  dcd=1;
}

//The main mechanism of the game
int play()
{
 char chc1,chc2;
 int ch1,ch2;
 clrscr();
 for(i=0;i<4;i+=4)
 for(j=0;j<4;j++)
 arr[(i+j)/6][(i+j)%6]=dup[(i+j)/6][(i+j)%6];
 shufflev();
 cout<<"\n";
 while(try!=0)
 {
 clrscr();
 board();
 cout<<"\n\t\t\t  PRESS 'Z' to Exit\n\t\t\t  No. of Tries Left="<<try<<"\n\t\t\t    Enter 1st Choice: ";
 cin>>chc1;
 if(islower(chc1))
 chc1=toupper(chc1);
 ch1=chc1-65;
 if(ch1==25)exit(0);
 arr[ch1/6][ch1%6]=vl3[ch1/6][ch1%6];
 clrscr();
 board();
 cout<<"\n\t\t\t  PRESS 'Z' to Exit\n\t\t\t  No. of Tries Left="<<try<<"\n\t\t\t    Enter 2nd Choice: ";
 cin>>chc2;
 if(islower(chc2))
 chc2=toupper(chc2);
 ch2=chc2-65;
 if(ch2==25)exit(0);
 arr[ch2/6][ch2%6]=vl3[ch2/6][ch2%6];
 clrscr();
 board();
 if(arr[ch1/6][ch1%6]==arr[ch2/6][ch2%6])
 try++;
 if(arr[ch1/6][ch1%6]!=arr[ch2/6][ch2%6])
 {
  arr[ch1/6][ch1%6]=dup[ch1/6][ch1%6];
  arr[ch2/6][ch2%6]=dup[ch2/6][ch2%6];
 }
 cout<<"\n"<<"\t\t\tPress any Character and Enter";
 cin>>ex;
 checkwin();
 if(dcd)
 {
  cout<<"\n\t\t\tYou Win";
  cout<<"\n\t\t\tEnter a Char";
  cin>>ex1;
  return 1;
 }
  try--;
}
if(try==0)
cout<<"\n\t\t\tOut of Tries\n\t\t\t Enter a Char" ;
cin>>ex1;
return 0;

}

//For the High Scores table
void highscore()
{clrscr();
 ifstream fin;
 fin.open("highscore.dat",ios::in|ios::binary);
 players temp;
 cout<<"\tNAME\tSCORE\n\n";
 for(i=0;i<size;i++)
 { fin.read((char*)&temp,sizeof(temp));
   cout<<"\t"<<temp.name<<"\t"<<temp.score<<"\n";
 }
}

//To check if the player's score enters the HighScores chart
void placescore()
{
  players p[15];
  ifstream filin;
  filin.open("highscore.dat",ios::in|ios::binary);
  for(i=0;i<size;i++)
  {
   filin.read((char*)&p[i],sizeof(p[i]));
  }
  for(i=(size-2);i>0;i--)
  { if((try>p[i+1].score)&&(try<=p[i-1].score))
    flag=i;
  }
  if(try>p[0].score)
  flag=0;
  else if((try>p[size-1].score)&&(try<=p[size-2].score))
  flag=size-1;
 if(flag!=-1)
  for(i=(size-1);i>flag;i--)
  { strcpy(p[i].name,p[i-1].name);
    p[i].score=p[i-1].score;
  }

 if(flag!=-1)
 { cout<<"Enter your name:";
   cin>>p[flag].name;
   p[flag].score=try;
 }
 filin.close();
 ofstream filout;
 filout.open("highscore.dat",ios::out|ios::binary);
 for(i=0;i<size;i++)
 filout.write((char*)&p[i],sizeof(p[i]));
 filout.close();
}



