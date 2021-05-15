#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//玩家展示的行和列
#define ROW 9
#define COL 9

//实际的行和列
#define ROWS ROW+2
#define COLS COL+2

//雷的数量
#define COUNT 10

void init_board(char board[ROWS][COLS],int rows,int cols,char a);//初始化棋盘
void print_board(char board[ROWS][COLS],int row,int col);//打印棋盘
void set_mine(char board[ROWS][COLS], int row, int col);//布置雷
char count_mine(char mine[ROWS][COLS], int x, int y);//计算周围雷的数量
int count_now(char show[ROWS][COLS]);//统计现在棋盘上未排查坐标的数量
void open_fun(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y);//实现连续展开功能
void open_board(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y);//展开
void sweep_mine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);//扫雷
void game(void);//游戏
void menu(void);//菜单

//初始化棋盘
void init_board(char board[ROWS][COLS],int rows,int cols,char a)
{
    int i,j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            board[i][j] = a;//初始化的内容
        }
    }
}

//打印棋盘
void print_board(char board[ROWS][COLS],int row,int col)
{
    int i, j;
    printf("   |");
    for(i = 1; i <= row; i++)//打印列坐标
    {
        printf(" %d |",i);
    }
    printf("\n");
	
    for(j = 0; j <= row; j++)
    {
        printf("---|");
    }
    printf("\n");
    //打印行坐标和棋盘内容
    for(i = 1; i <= row; i++)
    {
        printf(" %d |",i);//打印行坐标
		
        for(j = 1; j <= col; j++)//打印棋盘内容
        {
            printf(" %c |",board[i][j]);
        }
        printf("\n");
        for(j = 0; j <= row; j++)
        {
            printf("---|");
        }
        printf("\t\n");
    }
}

//布置雷函数
void set_mine(char board[ROWS][COLS], int row, int col)
{
    int count = COUNT;
    int x, y;
    while(count)
    {
        x = rand() % row + 1;//产生1-9的随机数
        y = rand() % col + 1;
        if(board[x][y] == '0')//判断随机位置是否有雷
        {
            board[x][y] = '1';
            count--;
        }
    }
}

//计算雷数量
char count_mine(char mine[ROWS][COLS], int x, int y)
{
    int t = 0;
    char c;
    if (mine[x][y+1] == '1')
        t++;
    if (mine[x][y-1] == '1')
        t++;
    if (mine[x+1][y] == '1')
        t++;
    if (mine[x-1][y] == '1')
        t++;
    if (mine[x+1][y-1] == '1')
        t++;
    if (mine[x-1][y+1] == '1')
        t++;
    if (mine[x-1][y-1] == '1')
        t++;
    if (mine[x+1][y+1] == '1')
        t++;
    c = t + '0';
    return c;
}

//统计现在棋盘上未排查坐标的数量
int count_now(char show[ROWS][COLS])
{
    int i,j,t;
    t = 0;
    for (i = 1; i <= ROW; i++)
        for (j = 1; j <= COL; j++)
            if(show[i][j] == '*' || show[i][j] == '?')
                t++;
			return t;
}

//实现展开功能
void open_fun(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
    //对周围8个位置进行展开
    open_board(mine, show, x, y+1);
    open_board(mine, show, x, y-1);
    open_board(mine, show, x+1, y);
    open_board(mine, show, x-1, y);
    open_board(mine, show, x+1, y-1);
    open_board(mine, show, x-1, y+1);
    open_board(mine, show, x-1, y-1);
    open_board(mine, show, x+1, y+1);
}

//展开扫雷
void open_board(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
    if(mine[x][y]== '0'&& show[x][y] == '*'  && x>0 && y>0 && x<=ROW && y<=COL || show[x][y]=='?')
    {
        if(count_mine(mine, x, y) == '0')//判断该处周围是否有雷
        {
            show[x][y] = ' ';//如果周围没雷该出处显示空
            open_fun(mine, show, x, y);//对周围8个格子进行判断是否继续展开
        }
        else
        {
            show[x][y] = count_mine(mine, x, y);
        }
    }
}

//插旗子
void flag(char show[ROWS][COLS])
{
    int x = 0, y=0;
    char c;
    do
    {
        printf("_______________________\n");
        printf("是否标记疑似雷的坐标:(y/n):");
        scanf(" %c",&c);
		
        if (c == 'y' || c == 'Y')//选择是否做标记
        {
            do
            {
                printf("______________\n");
                printf("输入要标记的坐标:");
                scanf(" %d%d",&x,&y);
                if (show[x][y] == '*' && x > 0 && y>0 && x <= ROW && y<=COL)//判断该位置是否可以做标记
                {
                    show[x][y] = '?';
                    break;
                }
                else
                    printf("请输入正确坐标!\n");
            }while (1);
        }
    }while(c == 'y' || c == 'Y');//多次进行标记
}

//扫雷
void sweep_mine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
    int x, y;
	
    while(count_now(show) > COUNT)
    {
        printf(">>>>>>>>>>>>>>\n");
        printf("输入要排查的坐标:");
        scanf("%d%d", &x, &y);
        if (x >= 1 && x <= row && y >= 1 && y <= col)
        {
            if (mine[x][y] == '1')//踩到雷结束本局
            {
                printf("boom!!爆炸！！\n");
                printf("***GAME OVER***\n");
                print_board(mine,ROW,COL);
                printf("boom!!爆炸！！\n");
                printf("***GAME OVER***\n");
                break;
            }
            else
            {
                show[x][y] = count_mine(mine, x, y);
                if(show[x][y] == '0')
                {
                    open_fun(mine, show, x, y);//展开周围同为空白的地方
                    show[x][y] = ' ';
                }
                print_board(show,ROW,COL);
				
                if (count_now(show) == COUNT)//判断是否排查出所有雷
                {
                    printf("恭喜你扫雷成功！！！\n");
                    print_board(mine,ROW,COL);
                    printf("恭喜你扫雷成功！！！\n");
                }
                else
                {
                    flag(show);//标记坐标
                    print_board(show, ROW, COL);
                }
            }
        }
        else
            printf("坐标错误，请重新输入！\n");
    }
}

//游戏函数
void game(void)
{
    //储存布置的雷数据
    char mine[ROWS][COLS]={0};
    //储存排查的雷的数据
    char show[ROWS][COLS]={0};
    //初始化
    init_board(mine,ROWS,COLS,'0');
    init_board(show,ROWS,COLS,'*');
    //布置雷
    set_mine(mine,ROW,COL);
    print_board(show,ROW,COL);
    //扫雷
    sweep_mine(mine, show, ROW, COL);
}

//开始菜单
void menu(void)
{
    printf("***********************\n");
    printf("********  扫雷  *******\n");
    printf("***********************\n");
    printf("***** 1. 开始游戏 *****\n");
    printf("***** 0. 退出游戏 *****\n");
    printf("***********************\n");
}

//主函数
int main(void)
{
    int input;
    srand((unsigned)time(NULL));//重新播种生成随机数
    do{ //可多次进行游戏
        menu();
        printf("请输入:");
        scanf("%d",&input);
        switch(input)//继续游戏或者退出游戏
        {
		    case 1:
			   game();
			   break;
		    case 0:
			   printf("退出游戏\n");
			   break;
	   	    default:
			   printf("请输入正确的选项\n");
			   break;
        }
    }while(input);
    return 0;
}
