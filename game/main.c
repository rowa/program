#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <winuser.h>
void gotoxy(int x,int y);//��ӡ��λ����
int color(int c);//��ɫ����
void welcometogame();//��ӡ��ʼ����
void hide_cursor();//���ع��
void control();//ͨ�������������̸ı��������֧꣬��������ͬʱ��
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
    //��ӡ���
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
    {   //GetAsyncKeyState()����ֵ���λ������ʱΪ1���ɿ�Ϊ2����0x8000�����㼴ȡ���λ
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
        //�Ż�����仯�ٶ�
        Sleep(50);
    }
}
