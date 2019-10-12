#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>
#include<dos.h>
typedef struct{
        char name[30];
        int score;
}Score;

typedef struct{
   int left,top,right;
   int color;
}Object;


FILE *savescore;
int true = 1;
int false = 0;
int ballx,bally,brad=10;
int hscore=-1;
char hname[30]="No Any";
int halfy;
int maxy;
int halfx;
int maxx;
char title[15]="BALL FALL";
char str[50];
int done = 0;
int next = 0;
int optionid = 1;
int speed;
int currscore=0;
int level=1;

void drawPrevLetter();
void frame2();

void graph(){
     int gd=0,gm;
     initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
     maxx = getmaxx();
     maxy = getmaxy();
     halfy=maxy/2;
     halfx=maxx/2;
}
void drawNextLetter(int x,int y,char *draw){
       int i;
       for(i = 10 ; i > 4 && draw!=32; i--){
             drawPrevLetter();
             settextstyle(7,0,i);
             outtextxy(x,y,draw);
             delay(100);
             cleardevice();
       }
       done++;
}
void drawPrevLetter(){
             int i;
             if(done>0){
                 strncpy(str,title,done);
                 settextstyle(7,0,5);
                 outtextxy(200,halfy-100,str);
             }
}
void finalTitle(){
     settextstyle(7,0,5);
     setcolor(5);
     outtextxy(200,halfy-100,title);
}
void drawFullTitle(){
     int y = halfy-100;
     drawNextLetter(200,y,"B");
     drawNextLetter(230,y,"A");
     drawNextLetter(257,y,"L");
     drawNextLetter(280,y,"L");
     drawNextLetter(310,y," ");
     drawNextLetter(325,y,"F");
     drawNextLetter(360,y,"A");
     drawNextLetter(380,y,"L");
     drawNextLetter(410,y,"L");
     finalTitle();
}

void showProgressBar(){
     int i;
     delay(20);
     setfillstyle(2,6);
     settextstyle(2,0,6);
     setcolor(2);
     for(i = 0 ; i < 141 ; i++){
           sprintf(str,"%d %",(i*100)/140);
           bar(halfx-140,halfy+40,halfx+i,halfy+70);
           outtextxy(halfx-5,halfy+45,str);
           delay(50);
     }
     outtextxy(halfx-40,halfy+100,"PRESS ANY KEY");
}

void mainFrame(){
     graph();
     drawFullTitle();
     showProgressBar();
     getch();
     cleardevice();
}

void NEWGAME(int isselected){
     if(isselected)
     setfillstyle(4,1);
     else
     setfillstyle(4,8);
     bar(halfx-100, halfy-80, halfx+100,halfy-40);
     outtextxy(halfx-80,halfy-85,"NEW GAME");
}

void HIGHSCORE(int isselected){
      if(isselected)
     setfillstyle(4,1);
     else
     setfillstyle(4,8);
     bar(halfx-100, halfy-20, halfx+100,halfy+20);
     outtextxy(halfx-80,halfy-25,"HIGH SCORE");
}

void ABOUT(int isselected){
      if(isselected)
     setfillstyle(4,1);
     else
     setfillstyle(4,8);
     bar(halfx-100, halfy+40, halfx+100,halfy+80);
     outtextxy(halfx-40,halfy+35,"ABOUT");
}

void EXIT(int isselected){
     if(isselected) setfillstyle(4,1);
     else setfillstyle(4,8);
     bar(halfx-100, halfy+100, halfx+100,halfy+140);
     outtextxy(halfx-30,halfy+95,"EXIT");
}

void setSelected(int id){
     if(id==1){
          NEWGAME(1);
          HIGHSCORE(0);
          ABOUT(0);
          EXIT(0);
     }
      if(id==2){
          NEWGAME(0);
          HIGHSCORE(1);
          ABOUT(0);
          EXIT(0);
    }
      if(id==3){
          NEWGAME(0);
          HIGHSCORE(0);
          ABOUT(1);
          EXIT(0);
          }
      if(id==4){
          NEWGAME(0);
          HIGHSCORE(0);
          ABOUT(0);
          EXIT(1);
     }
}
void optionSelectedListner(){
     char item;
     int RUN = 1;
     setSelected(optionid);
     while(RUN){
     notanoption:
     item = getch();
          if(item=='w'||item=='W'){
           if(optionid>1) --optionid;
           }
          else if(item=='S'||item=='s'){
           if(optionid<4) ++optionid;
           }
          else if(item=='h'||item=='H')
           break;
          else goto notanoption;
          setSelected(optionid);
     }
}
void aboutFrame(){
    int back[]={30,459,
        40,449,
        160,449,
        160,469,
        40,469,
        30,459};
    char ch;
    settextstyle(3,0,5);
    setcolor(14);
    outtextxy(halfx-200,halfy-100,"Thanks For Playing!");
    settextstyle(7,0, 1);
    setcolor(7);
    outtextxy(halfx-100,halfy,"Contributers");
    outtextxy(halfx-300,halfy+40,"github.com/jainrocky/Computer-Graphics/Contributors.md");
    drawpoly(6,back);
    settextstyle(1,0,1);
    setcolor(10);
    outtextxy(60,447,"BACK (B)");
    while(true){
            ch = getch();
            if(ch=='b'||ch=='B') break;
    }
    cleardevice();
    frame2();
}
void highScoreFrame(){
     FILE *sheet;
     int i,j,y=120,k=-1;
     Score s[50],temp={"",0};
     int roll[]={150,95,
     160,100,
     480,100,
     490,95,
     490,115,
     480,110,
     160,110,
     150,115,
     150,95};
     int back[]={30,459,
        40,449,
        160,449,
        160,469,
        40,469,
        30,459};
    char ch;
    sheet = fopen("scoresheet","rb");
    while(fread(&temp,1,sizeof(Score),sheet)){
     s[++k]=temp;
    }
    for(i=0;i<k+1;i++){
       for(j=0;j<k+1;j++){
           if(s[i].score > s[j].score){
                temp=s[i];
                s[i]=s[j];
                s[j]=temp;
           }
        }
     }
     setcolor(14);
     setfillstyle(1,14);
     fillpoly(8,roll);
     settextstyle(4,0,5);
     setcolor(6);
     outtextxy(halfx-140,halfy-200,"HIGH SCORE");

     setcolor(4);
     setfillstyle(1,4);
     fillpoly(6,back);
    settextstyle(1,0,1);
    setcolor(10);
    outtextxy(60,447,"BACK (B)");

    setfillstyle(8,10);
     for(i=150;i<446;i++){
         bar(200,100,440,i);
         delay(1);
     }
     settextstyle(1,0,2);
     setcolor(WHITE);
     for(i=0;i<k+1;i++,y-= 30){
           outtextxy(halfx-100,halfy-y,s[i].name);
           sprintf(str,"%d",s[i].score);
           outtextxy(halfx+80,halfy-y,str);
     }
     fclose(sheet);
     while(true){
        ch = getch();
        if(ch=='b'||ch=='B') break;
     }
     cleardevice();
     frame2();
}
void gameWindow(){
     setfillstyle(1,3);
     bar(0,0,halfx+100,maxy);
}
void scoreCardWindow(){
     setfillstyle(1,8);
     bar(halfx+101,0,maxx,halfy-30);
     settextstyle(10,0,2);
     sprintf(str,"Level: %d",level);
     outtextxy(halfx+120,50,str);
     sprintf(str,"Score: %d",currscore);
     outtextxy(halfx+120,110,str);
}
void intializeWindow(){
         int nowcolor;
         int left[]={485,379,
         525,359,
         525,399,
         485,379
         };
         int right[]={575,379,
         535,359,
         535,399,
         575,379
         };
         setcolor(WHITE);
         gameWindow();
         setfillstyle(1,8);
         scoreCardWindow(level,currscore);
         bar(halfx+100,halfy-30,maxx,maxy);
         settextstyle(2,0,4);
         outtextxy(halfx+115,maxy-50,"QUIT: T");
         settextstyle(1,0,3);
         outtextxy(halfx+140,halfy-10,"High Score");
         settextstyle(0,0,1);
         setcolor(11);
         sprintf(str,"%s   %d",hname,hscore);
         outtextxy(halfx+135,halfy+30,str);
         setfillstyle(1,6);
         nowcolor = getcolor();
         setcolor(6);
         fillpoly(4,left);
         fillpoly(4,right);
         setcolor(nowcolor);
         settextstyle(6,0,3);
         outtextxy(510,362,"A");
         outtextxy(540,362,"D");
}
void searchHighScore()
{
    Score temp;
    savescore=fopen("scoresheet","r");
         while(fread(&temp,1,sizeof(Score),savescore))
         {
            if(temp.score > hscore){
            hscore = temp.score;
            strcpy(hname,temp.name);
            }
         }
         fclose(savescore);
}
void quitDialogBox(){
     int i;
     setfillstyle(1,12);
         //dialog box
               for(i=50;i<150;i++){
                   bar(halfx-i,halfy+50-i,halfx+i,halfy-50+i);
                   delay(2);
               }
               //final bar halfx-150,halfy-100,halfx+150,halfy+100
                   settextstyle(3,0,3);
                   setcolor(14);
                   outtextxy(halfx-130,halfy-80,"Save Score?");
                   line(halfx-150,halfy-50,halfx+150,halfy-50);
                   settextstyle(5,0,4);
                   setcolor(5);
                   sprintf(str,"Your Score: %d",currscore);
                 outtextxy(halfx-130,halfy-30,str);
                 settextstyle(0,0,1);
                 setcolor(6);
                 outtextxy(halfx-130,halfy+50,"Note: Always Save Your Score");
               setcolor(9);
               setfillstyle(1,10);
               bar(halfx-150,halfy+80,halfx-50,halfy+100);
               outtextxy(halfx-120, halfy+87,"YES: Y");

               setfillstyle(1,7);
               bar(halfx-50,halfy+80,halfx+50,halfy+100);
               outtextxy(halfx-15, halfy+87,"NO: N");
               setfillstyle(1,5);
               bar(halfx+50,halfy+80,halfx+150,halfy+100);
               outtextxy(halfx+55, halfy+87,"CANCLE: C");
}

void saveDialogBox(){
     int i;
     int currpos = 125;
     Score temp={"",0};
     char ch,curr[1];
     setfillstyle(1,12);
     savescore=fopen("scoresheet","ab+");
                   bar(halfx-150,halfy-100,halfx+150,halfy+100);
                   settextstyle(3,0,3);
                   setcolor(14);
                   outtextxy(halfx-130,halfy-80,"SAVE SCORE");
                   line(halfx-150,halfy-50,halfx+150,halfy-50);
                   settextstyle(0,0,1);
                   setcolor(5);
                   outtextxy(halfx-130,halfy-30,"Enter Your Name");
                   //edit text
                   setfillstyle(1,WHITE);
                   bar(halfx-130,halfy-10,halfx+130,halfy+10);
                   sprintf(str,"Score: %d",currscore);
                   outtextxy(halfx-130,halfy+50,str);
                   //save button start
                   bar(halfx-30,halfy+70,halfx+30,halfy+90);
                   setcolor(2);
                   outtextxy(halfx-25,halfy+77,"SAVE(;)");
                   //save button end
                   i=-1;
                   setcolor(BLACK);
                   while((ch=getch())!=';'){
                       if(ch==8 && currpos < 125){
                        temp.name[i--]=32;
                        currpos+=10;
                        setfillstyle(1,WHITE);
                        bar(halfx-currpos,halfy-10,halfx+130,halfy+10);
                       }else if(ch!=8){
                         temp.name[++i]=ch;
                         sprintf(curr,"%c",ch);
                         outtextxy(halfx-currpos,halfy-4,curr);
                         currpos-=10;
                       }
                   }
                   fseek(savescore,0,SEEK_END);
                   temp.score=currscore;
                   //strncpy(s.name,currname,i+1);
                   fwrite(&temp,1,sizeof(Score),savescore);
                   fclose(savescore);
}

void drawCircle(int x,int y){
 circle(x,y,brad);
 }
int isGameOver();

void moveBall(char dir){
   gameWindow();
   if(dir=='D'&& !isGameOver())
      bally++;
   else if(dir=='U' && !isGameOver())
      bally--;
   else if(dir=='L' && ballx > brad+10)
      ballx-=10;
   else if(dir=='R'&& ballx < halfx+100-brad-10)
      ballx+=10;
   circle(ballx,bally,brad);
}

int isGameOver(){
   if(bally >= maxy-brad || bally <= brad ) return 1;
   return 0;
}

void gameOverDialog(){
     int i;
     setfillstyle(1,12);
     for(i=50;i<=100;i++){
         bar(220-i,halfy-40,220+i,halfy+40);
         delay(10);
     }
     settextstyle(11,0,2);
     outtextxy(137,halfy-20,"BETTER LUCK NEXT TIME!");
     settextstyle(6,0,4);
     outtextxy(145,halfy-10,"Game Over!");
}
void intialiseObject(Object *objects,int count){
     int i=0;
     int randpos;
     for(i=0;i<count;i++){
        randpos = rand() % 15;
        if(randpos<0) randpos *=-1;
        (objects+i)->top=maxy+10+(i*200);
        if(randpos!=3 && randpos!=0 && randpos!=7)
        (objects+i)->color =randpos;
        else
        (objects+i)->color = BROWN;
     }
}

void drawObject(Object*);

void moveObject(Object *object){
     int newcolor;
     if(object->top > maxy){
       object->top--;
       return;
     }
     else if(object->top > 0 && object->top <= maxy){
       object->top--;
     }
     else{
         object->top=maxy+1850;
         newcolor = rand() % 15;

         if(newcolor==3) newcolor = 6;
         object->color = newcolor;
         drawObject(object);
     }
     setfillstyle(1,object->color);
     bar(object->left,object->top,object->right,object->top+2);
}

void drawObject(Object *object){
   int len,l,r;
   len=rand() % 200-(currscore*2);
   l=rand() % (halfx+100-len-10);
   if(len<25) len=25;
   r=l+len;
   if(l < 2){
        l=5;
        r=l+len;
   }
   else if(r > halfx+98){
        r=halfx+93;
        l=r-len;
   }
   object->left=l;
   object->right=r;
}
int isBallOnObject(Object *object){
    int ydiff = (object->top)-(bally+brad);
    if(ydiff < 2 && ydiff > 0 && ballx < (object->right) && ballx > (object->left)) return 1;
    return 0;
}

void changeTopMost(Object *topmost,int *pos){
     int k;// = *pos;
     if((topmost->top+2) < bally)
     {
       *pos = (*pos + 1) % 10;
       if(topmost->color == BROWN)
         currscore+=5;
       else
         currscore += 1;

       k=currscore/10;
       if(level<=k){
          level++;
          outtextxy(180,halfy,"Level Up!");
          delay(200);
          speed-=5;
         }
        scoreCardWindow();
     }
}
void startGame(){
         float bonus=0;
         int uplevelafter=0;
         Object objects[10];
         int pos = 0;
         Object *topmost=&objects[pos];
         char dir='D';
         int i=0;
         int xinit,yinit=50;
         char ch;
           currscore=0;
           level=1;
           speed = 25;
           intialiseObject(objects,10);
           xinit = rand() % (halfx+100);
           if(xinit<0) xinit*=-1;
           if(xinit < brad) xinit+=brad;
           if(xinit > halfx+100-brad) xinit-=brad;
           ballx = xinit;
           bally = yinit;
           searchHighScore();
           intializeWindow();
           drawCircle(xinit,yinit);
           for(i=0;i<10;i++)
             drawObject(&objects[i]);
 while(true){
         changeTopMost(&objects[pos],&pos);
         moveBall(dir);
         for(i=0;i<10;i++){
           moveObject(&objects[i]);
         }
         delay(speed);
         if(kbhit()){
         ch = getch();
         if(ch=='t'||ch=='T'){
               quitDialogBox();
          notlisten:
               ch = getch();
               if(ch=='y'||ch=='Y'){
                   saveDialogBox();
                   cleardevice();
                   frame2();
               }//dialog box
               else if(ch=='n'||ch=='N'){
                cleardevice();
                frame2();
                }
                else if(ch=='c'||ch=='C'){
                    intializeWindow();
                }else goto notlisten;
          }//if END || if(t)
         else if(ch=='a'||ch=='A' /*&& kbhit()*/){
            //dir='L';
           moveBall('L');
         }
         else if(ch=='d'||ch=='D' /*&& kbhit()*/){
            moveBall('R');
            //dir='R';
         }
      }//kbhit if end

      if(isBallOnObject(&objects[pos])){
       dir='U';
       }
      else dir='D';

      if(isGameOver()){
       gameOverDialog();
       delay(1000);
       intializeWindow();
       saveDialogBox();
       cleardevice();
       frame2();
      }
  }//while end
}

void optionHit(){
     cleardevice();
     if(optionid==4){
      closegraph();
      exit(0);
      }
     if(optionid==3)
         aboutFrame();
     if(optionid==2)
         highScoreFrame();
     if(optionid==1)
         startGame();
}

void createOptions(){
     int enter[]={609,459,
        599,449,
        500,449,
        500,469,
        599,469,
        609,459};
     int up[]={30,409,
        70,409,
        50,379,
        30,409};
     int down[]={50,459,
     30,419,
     70,419,
     50,459
     };
     settextstyle(10,0,1);
     NEWGAME(1);
     HIGHSCORE(0);
     ABOUT(0);
     EXIT(0);
     setfillstyle(1,6);
     fillpoly(6,enter);
     fillpoly(4,up);
     fillpoly(4,down);
     settextstyle(1,0,1);
     outtextxy(75,380,"W");
     outtextxy(75,430,"S");
     outtextxy(520,447,"Hit: H");
     settextstyle(10,0,1);
     optionSelectedListner();
     optionHit();
}


void frame2(){
    setcolor(WHITE);
     createOptions();

}
         //639 479
void main(){
    // FILE *p;
   //  p=fopen("scoresheet","w");
    // fclose(p);

     graph();
     mainFrame();
     frame2();
     //highScoreFrame();
     getch();
}
