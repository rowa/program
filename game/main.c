#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <winuser.h>
void gotoxy(int x,int y);//打印方位函数
int color(int c);//颜色函数
void welcometogame();//打印初始画面
void hide_cursor();//隐藏光标
void control();//通过按两个方向盘改变两个坐标，支持连按、同时按
int x1=0;
int y1=0;
int x2=0;
int y2=0;
int main()
{
    welcometogame();
    hide_cursor();
	control();
}
void welcometogame()
{
    system("cls");
    color(FOREGROUND_BLUE|FOREGROUND_RED);
    int i,j;
    //打印框架
    for (i = 6; i <= 10; i++)
	{
		for (j = 26; j <= 39; j++)
		{
			gotoxy(j, i);
			if (i == 6 || i == 10) printf("*");
			else if (j == 26 || j == 39) printf("*");
		}

	}
	for (i = 6; i <= 10; i++)
	{
		for (j = 66; j <= 79; j++)
		{
			gotoxy(j, i);
			if (i == 6 || i == 10) printf("*");
			else if (j == 66 || j == 79) printf("*");
		}

	}

    gotoxy(30,8);
    printf("(%d,%d)",x1,y1);
    gotoxy(70,8);
    printf("(%d,%d)",x2,y2);
}
int color(int n)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
    return 0;
}
void gotoxy(int x,int y)
{
    COORD n;
    n.X=x;
    n.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),n);
}
void hide_cursor()
{
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = FALSE;
    cci.dwSize = sizeof(cci);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &cci);
}
void control()
{
    while(1)
    {   //GetAsyncKeyState()返回值最高位当按下时为1，松开为2，与0x8000与运算即取最高位
        if(GetAsyncKeyState('W') & 0x8000)
        {
            x1++;
            welcometogame();

        }
        if(GetAsyncKeyState('S') & 0x8000)
        {
            x1--;
            welcometogame();

        }

        if(GetAsyncKeyState('A') & 0x8000)
        {

            y1--;
            welcometogame();

        }
        if(GetAsyncKeyState('D') & 0x8000)
        {
            y1++;
            welcometogame();

        }
        if(GetAsyncKeyState(VK_UP) & 0x8000)
        {
            x2++;
            welcometogame();

        }
        if(GetAsyncKeyState(VK_DOWN) & 0x8000)
        {
            x2--;
            welcometogame();

        }
        if(GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            y2--;
            welcometogame();

        }
        if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            y2++;
            welcometogame();

        }
        //放缓坐标变化速度
        Sleep(50);
    }
}
