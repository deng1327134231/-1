#include <graphics.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "box_man.h"

using namespace std;
#define BOX_COUNT 4

#define isValid(pos) pos.x>=0&&pos.x<LINE&&pos.y>=0&&pos.y<ROWS

#define LINE 9
#define ROWS 12
IMAGE mages[ALL];
int map[LINE][ROWS]={
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,1,1,1,1,1,1,1,0,0},
	{0,1,3,1,0,2,1,0,0,1,0,0},
	{0,1,0,1,0,1,0,0,0,1,1,0},
	{0,1,0,2,0,1,1,1,1,3,1,0},
	{0,1,1,1,0,4,1,1,1,3,1,0},
	{0,2,1,1,3,1,1,1,1,1,1,0},
	{0,1,0,0,1,1,1,1,0,0,2,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
};
struct _POST point1, point2[BOX_COUNT],point3;
int k=40;



/*******************************************************
*传入指定的位置并和图片,在指定位置改变所需要的图片
*输入:
*		pos	指定位置
*		props  指定图片
*输出:
*		无
********************************************************/
void ChangeImage(POST *pos,PROPS props){
	map[pos->x][pos->y]=props;
	putimage(150+pos->y* RATIO,100+pos->x* RATIO,&mages[props]);

}
/*************************************************
*判断小人需要移动方向是否可以移动和推动相纸
*输入:
*		direct 小人移动的方向
*输出:
*		无
**************************************************/
void GameControl( DIRECT direct){
	POST man1=man;
	POST next_pos=man;
	POST next_next_pos=man;
	switch(direct){
	case UP:
		next_pos.x--;
		next_next_pos.x-=2;
			break;
	case DOWN:
		next_pos.x++;
		next_next_pos.x+=2;
		break;
	case LEFT:
		next_pos.y--;
		next_next_pos.y-=2;
		break;
	case RIGHT:
		next_pos.y++;
		next_next_pos.y+=2;
		break;
	}
	if(map[next_pos.x][next_pos.y]==BOX_DES){
		point1=next_pos;
	}
	if(map[next_pos.x][next_pos.y]==HIT){
		point3.x=next_pos.x;
		point3.y=next_pos.y;
	}
	if(isValid(next_pos)&&map[next_pos.x][next_pos.y]==FLOOR||map[next_pos.x][next_pos.y]==BOX_DES){//小人前面是地板或者是相纸目的地
			ChangeImage(&next_pos,MAN);	
			if(man.x==point1.x&&man.y==point1.y||man.x==point3.x&&man.y==point3.y){
				ChangeImage(&man,BOX_DES);
			}else{
			ChangeImage(&man,FLOOR);
			}
			man=next_pos;			
	}else if(isValid(next_pos)&&map[next_pos.x][next_pos.y]==HIT){//小人前面是HIT 的情况下
				
		if(map[next_next_pos.x][next_next_pos.y]==FLOOR){
			ChangeImage(&next_next_pos,BOX);
			ChangeImage(&next_pos,MAN);			
			ChangeImage(&man,FLOOR);			
			man=next_pos;
		}
		//小人前面是相纸的情况下
	}else if(isValid(next_next_pos)&&map[next_pos.x][next_pos.y]==BOX){
		//相纸前面是地板的情况下
		if(map[next_next_pos.x][next_next_pos.y]==FLOOR){
			ChangeImage(&next_next_pos,BOX);
			ChangeImage(&next_pos,MAN);	
			if(man.x==point3.x&&man.y==point3.y){
				ChangeImage(&man,BOX_DES);
			}else{
			ChangeImage(&man,FLOOR);
			}
			man=next_pos;
			//相纸前面是相纸目的地情况下
	     }else if(map[next_next_pos.x][next_next_pos.y]==BOX_DES){
			ChangeImage(&next_next_pos,HIT);			
			ChangeImage(&next_pos,MAN);			
			ChangeImage(&man,FLOOR);
				
			man=next_pos;
		 }
	}
	if(man1.x!=man.x||man1.y!=man.y){
	k--;
	}

}
/*****************************************************************
*判断游戏是否结束
*输入:
*		无
*输出:
*		是或者否
*******************************************************************/
bool isGameOver(void){

		for(int i=0;i<LINE;i++){
			for(int j=0; j<ROWS;j++){
				if(map[i][j]==BOX_DES){
					return false;
				}
			}
		}
		return true;
		
}
/******************************************************************
*游戏结束的画面
*输入:
*		image 游戏结束图片地址
*输出:
*		无
***********************************************************************/	
void gameOverScreen(IMAGE *image){
	putimage(0,0,image);
	settextcolor(WHITE);
	RECT ret={0,0,SCREEN_WIDTH,SCREEN_HIGTH};
	settextstyle(20,0,_T("宋体"));
	drawtext(_T("恭喜你,已成为老司机了"),&ret,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

}

void gameOverScreen1(IMAGE *image){
	putimage(0,0,image);
	settextcolor(WHITE);
	RECT ret={0,0,SCREEN_WIDTH,SCREEN_HIGTH};
	settextstyle(20,0,_T("宋体"));
	drawtext(_T("你失败了"),&ret,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

}


int main(void){
	
	IMAGE bg_img;
	initgraph(SCREEN_WIDTH,SCREEN_HIGTH);
	loadimage(&bg_img,_T("blackground.bmp"),SCREEN_WIDTH,SCREEN_HIGTH,true);
	putimage(0,0,&bg_img);

	//加载图片

	loadimage(&mages[WALL],_T("wall_right.bmp"), RATIO, RATIO,true);
	loadimage(&mages[FLOOR],_T("floor.bmp"), RATIO, RATIO,true);
	loadimage(&mages[BOX_DES],_T("des.bmp"), RATIO, RATIO,true);
	loadimage(&mages[BOX],_T("box.bmp"), RATIO, RATIO,true);
	loadimage(&mages[MAN],_T("man.bmp"), RATIO, RATIO,true);
	loadimage(&mages[HIT],_T("box.bmp"), RATIO, RATIO,true);

	for(int i=0;i<LINE;i++){
		for(int j=0;j<ROWS;j++){
			if(map[i][j]==MAN){
				man.x=i;
				man.y=j;
			}
				
			putimage(150+j* RATIO,100+i* RATIO,&mages[map[i][j]]);
		}
	}
	//更换图片
	bool quit=false;
	do{
		if(_kbhit()){
			char ch=_getch();
			if(ch==KEY_UP){
				GameControl(UP);
			}else if(ch==KEY_LEFT){
				GameControl(LEFT);
			}else if(ch==KEY_RIGTH){
				GameControl(RIGHT);
			}else if(ch==KEY_DOWN){
				GameControl(DOWN);
			}else if(ch==KEY_QUIT){
				quit=true;
		
			}
			if(k<=0){
					gameOverScreen1(&bg_img);
				quit=true;
			}
			if(isGameOver()){
				 gameOverScreen(&bg_img);
				quit=true;
			}
		}
		
		Sleep(100);
	}while(quit==false);
	system("pause");
	closegraph();
	return 0;
}