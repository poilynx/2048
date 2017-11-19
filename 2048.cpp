/*
 * This Program Is a 2048 game with EasyX library
 * Released on 2017.4.7
 * Writed by tinkrr
 * Email: i@tinkrr.cc
 */
#include <graphics.h>
#include <CONIO.H>
#include <STDIO.H>
#include <MATH.H>
#include <TIME.H>
#define Ixil
#define NORMAL		0
#define TRYAGAIN	1
#define EXIT		2
unsigned char nummap[4][4];
unsigned char imgcount=0;
IMAGE img[11];
COLORREF commonBackColor=RGB(150,100,100);
unsigned long score=0;
unsigned long bestScore;
unsigned short nums[12]={0,2,4,8,16,32,64,128,256,512,1024,2048};

bool init();
void whirlToLeft();
void whirlToRight();
void reverse();
bool moveMapL2R();
void restart();
bool newimg();
void refresh();
void about();
unsigned char youwin();
unsigned char gamestate();
bool moveimg(unsigned char dir);

void whirlToLeft()
{
	char tmpmap[4][4];
	char i,j;
	for(i=0;i<=3;i++)
		for(j=0;j<=3;j++)
		{
			tmpmap[j][3-i]=nummap[i][j];
		}
	memcpy(nummap,tmpmap,16);
}
void whirlToRight()
{
	char tmpmap[4][4];
	char i,j;
	for(i=0;i<=3;i++)
		for(j=0;j<=3;j++)
		{
			tmpmap[3-j][i]=nummap[i][j];//10 31
		}
	memcpy(nummap,tmpmap,16);
}
void reverse()
{
	char tmpmap[4][4];
	char i,j;
	for(i=0;i<=3;i++)
		for(j=0;j<=3;j++)
		{
			tmpmap[3-i][3-j]=nummap[i][j];//10 23
		}
	memcpy(nummap,tmpmap,16);
}
bool moveMapL2R()
{
	int i,j,k;
	bool ret=false;
	for (i=0;i<=3;i++)
	{
		for(j=0;j<=2;j++)
		{
			if(nummap[i][j]==0) continue;
			for (k=j+1;k<=3;k++)
			{
				if(nummap[i][k]==0) continue;
				if(nummap[i][j]==nummap[i][k])
				{
					nummap[i][j]++,nummap[i][k]=0;
					score+=nums[nummap[i][j]];
					imgcount--;
					j=3;
					ret=true;
				}
				break;
			}
		}
		k=1;
		for(j=0;j<=2;j++)
		{
			if(nummap[i][j]!=0)
			{
				k++;
				continue;
			}
			for(;k<=3;k++)
			{
				if(nummap[i][k]==0) continue;
				nummap[i][j]=nummap[i][k];
				nummap[i][k]=0;
				ret=true;
				break;
			}
		}
		
	}
	return ret;
}
bool init()
{
	initgraph(250,300);
	setbkcolor(commonBackColor);
	setfillcolor(RGB(200,150,150));
	HWND hWnd=GetHWnd();
	SetWindowText(hWnd,"2048");
	srand(time(NULL));
	char filename[20];
	char tmp[20];
	for (int i=0;i<=10;i++)
	{
		strcpy(filename,"img/");
		itoa(nums[i],tmp,10);
		strcat(filename,tmp);
		strcat(filename,".bmp");
		
		loadimage(img+i,filename);
	}
	memset(nummap,0,sizeof(nummap));
	
	return false;

}

void restart()
{
	memset(nummap,0,sizeof(nummap));
	score=0;
	imgcount=0;
	newimg();
}
unsigned char gamestate()//0正常1重试2关闭
{
	char i,j;
	for (i=0;i<=3;i++)
	{
		for (j=0;j<=3;j++)
		{
			if(nummap[i][j]==11) return youwin();
		}
	}
	if(imgcount<16) return 0;

	for (i=0;i<=3;i++)
		for(j=0;j<=2;j++)
		{
			if(nummap[i][j]==nummap[i][j+1])return NORMAL;
			if(nummap[j][i]==nummap[j+1][i])return NORMAL;
		}


	bool isBest=score>bestScore;
	if(isBest)bestScore=score;
	refresh();
	setfillcolor(RGB(250,80,2));
	fillrectangle(0,100,249,200);
	setbkcolor(RGB(250,80,2));
	settextcolor(RGB(0,150,250));
	settextstyle(20, 0, "Verdana");
	RECT rc={0,110,250,200};
	char textOut[100];
	sprintf(textOut,"Game Over\n\rScore %d %s\n\n"
		"Try Again[T]    Exit[E]",
		score,isBest?"The Best!":"");
	drawtext(textOut,&rc,DT_CENTER);
	setbkcolor(commonBackColor);
	setfillcolor(RGB(200,150,150));
	while(1)
	{
		while (!kbhit());
		char ch=getch();
		switch(ch)
		{
		case 't':
		case 'T':
			return TRYAGAIN;
		case 'e':
		case 'E':
			return EXIT;
		}
	}
}
unsigned char youwin()
{
	bool isBest=score>bestScore;
	if(isBest)bestScore=score;
	refresh();
	setfillcolor(RGB(250,80,2));
	fillrectangle(0,100,249,200);
	setbkcolor(RGB(250,80,2));
	settextcolor(RGB(0,150,250));
	settextstyle(20, 0, "Verdana");
	RECT rc={0,110,250,200};
	char textOut[100];
	sprintf(textOut,
		"You Win!\n\rScore %d %s\n\n"
		"Try Again[T]    Exit[E]",
		score,isBest?"The Best!":"");
	drawtext(textOut,&rc,DT_CENTER);
	setbkcolor(commonBackColor);
	setfillcolor(RGB(200,150,150));
	while(1)
	{
		while (!kbhit());
		char ch=getch();
		switch(ch)
		{
		case 't':
		case 'T':
			return TRYAGAIN;
		case 'e':
		case 'E':
			return NORMAL;
		}
	}
}
void about()
{
	setfillcolor(RGB(250,80,2));
	fillrectangle(0,100,249,200);
	setbkcolor(RGB(250,80,2));
	settextcolor(RGB(0,150,250));
	settextstyle(18, 0, "Verdana");
	RECT rc={0,105,250,220};
	char textOut[100]="About 2048\n"
		"Programming By Ixil\n"
		"bluesolos@gmail.com\n"
		"www.ixil.com.nu\nClose[C]";
	drawtext(textOut,&rc,DT_CENTER);
	setbkcolor(commonBackColor);
	setfillcolor(RGB(200,150,150));
	while(1)
	{
		while (!kbhit());
		char ch=getch();
		if(ch=='c' || ch=='C') break;
	}
}
bool newimg()
{
	unsigned char limit=16-imgcount;
	if(limit<=0) return true;
	unsigned char n=rand()%limit;

	unsigned char k=0,i=0;
	while(k<=n)
	{
		if(((unsigned char *)nummap)[i]==0)
			k++;
		i++;
	}
	i--;
	((unsigned char *)nummap)[i]=1;
	imgcount++;
	return false;
}
void refresh()
{
	cleardevice();
	int i,j;
	for (i=0;i<=3;i++)
	{
		for(j=0;j<=3;j++)
		{
			putimage(60*j+10,60*i+10,&img[nummap[i][j]]);
		}
	}

	setfillcolor(RGB(200,150,150));
	fillrectangle(0,250,249,299);
	setbkcolor(RGB(200,150,150));
	settextcolor(RGB(0,100,255));
	settextstyle(20, 0, "Verdana");
	RECT rc={0,251,250,300};
	char textOut[100];
	sprintf(textOut,"Score %d\t  Best %d  \nNew[N] About[B] Exit[E]",score,bestScore);
	drawtext(textOut,&rc,DT_CENTER);
	setbkcolor(commonBackColor);
}
bool moveimg(unsigned char dir)//0 left,1 up,2 right ,3 down
{
	bool ret;
	switch(dir)
	{
	case 0:
		ret=moveMapL2R();
		break;
	case 1:
		whirlToRight();
		ret=moveMapL2R();
		whirlToLeft();
		break;
	case 2:

		reverse();
		ret=moveMapL2R();
		reverse();
		break;
	case 3:
		whirlToLeft();
		ret=moveMapL2R();
		whirlToRight();
		break;
	default:
		ret=false;
	}
	return ret;
}

int main()
{
	init();
	restart();
	newimg();
	refresh();
	while(1)
	{
		while (!kbhit());
		char ch=getch();
		bool moved=true;
		switch(ch)
		{
		case 'a':
		case 'A':
			moved=moveimg(0);
			break;
		case 'w':
		case 'W':
			moved=moveimg(1);
			break;
		case 'd':
		case 'D':
			moved=moveimg(2);
			break;

		case 's':
		case 'S':
			moved=moveimg(3);
			break;
		case 'n':
		case 'N':
			restart();
			break;
		case 'e':
		case 'E':
			return 0;
		case 'b':
		case 'B':
			about();
			moved=false;
			break;
		default:
			moved=false;
		}
		if(moved)
		if(newimg())
		{
			return 1;
		}
		refresh();
		unsigned char state=gamestate();
		switch(state)
		{
		case TRYAGAIN:
			restart();
			newimg();
			break;
		case EXIT:
			return 0;
		}
	}

	getch();
	return 0;
}
