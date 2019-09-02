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
*����ָ����λ�ò���ͼƬ,��ָ��λ�øı�����Ҫ��ͼƬ
*����:
*		pos	ָ��λ��
*		props  ָ��ͼƬ
*���:
*		��
********************************************************/
void ChangeImage(POST *pos,PROPS props){
	map[pos->x][pos->y]=props;
	putimage(150+pos->y* RATIO,100+pos->x* RATIO,&mages[props]);

}
/*************************************************
*�ж�С����Ҫ�ƶ������Ƿ�����ƶ����ƶ���ֽ
*����:
*		direct С���ƶ��ķ���
*���:
*		��
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
	if(isValid(next_pos)&&map[next_pos.x][next_pos.y]==FLOOR||map[next_pos.x][next_pos.y]==BOX_DES){//С��ǰ���ǵذ��������ֽĿ�ĵ�
			ChangeImage(&next_pos,MAN);	
			if(man.x==point1.x&&man.y==point1.y||man.x==point3.x&&man.y==point3.y){
				ChangeImage(&man,BOX_DES);
			}else{
			ChangeImage(&man,FLOOR);
			}
			man=next_pos;			
	}else if(isValid(next_pos)&&map[next_pos.x][next_pos.y]==HIT){//С��ǰ����HIT �������
				
		if(map[next_next_pos.x][next_next_pos.y]==FLOOR){
			ChangeImage(&next_next_pos,BOX);
			ChangeImage(&next_pos,MAN);			
			ChangeImage(&man,FLOOR);			
			man=next_pos;
		}
		//С��ǰ������ֽ�������
	}else if(isValid(next_next_pos)&&map[next_pos.x][next_pos.y]==BOX){
		//��ֽǰ���ǵذ�������
		if(map[next_next_pos.x][next_next_pos.y]==FLOOR){
			ChangeImage(&next_next_pos,BOX);
			ChangeImage(&next_pos,MAN);	
			if(man.x==point3.x&&man.y==point3.y){
				ChangeImage(&man,BOX_DES);
			}else{
			ChangeImage(&man,FLOOR);
			}
			man=next_pos;
			//��ֽǰ������ֽĿ�ĵ������
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
*�ж���Ϸ�Ƿ����
*����:
*		��
*���:
*		�ǻ��߷�
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
*��Ϸ�����Ļ���
*����:
*		image ��Ϸ����ͼƬ��ַ
*���:
*		��
***********************************************************************/	
void gameOverScreen(IMAGE *image){
	putimage(0,0,image);
	settextcolor(WHITE);
	RECT ret={0,0,SCREEN_WIDTH,SCREEN_HIGTH};
	settextstyle(20,0,_T("����"));
	drawtext(_T("��ϲ��,�ѳ�Ϊ��˾����"),&ret,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

}

void gameOverScreen1(IMAGE *image){
	putimage(0,0,image);
	settextcolor(WHITE);
	RECT ret={0,0,SCREEN_WIDTH,SCREEN_HIGTH};
	settextstyle(20,0,_T("����"));
	drawtext(_T("��ʧ����"),&ret,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

}


int main(void){
	
	IMAGE bg_img;
	initgraph(SCREEN_WIDTH,SCREEN_HIGTH);
	loadimage(&bg_img,_T("blackground.bmp"),SCREEN_WIDTH,SCREEN_HIGTH,true);
	putimage(0,0,&bg_img);

	//����ͼƬ

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
	//����ͼƬ
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