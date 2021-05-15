#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//���չʾ���к���
#define ROW 9
#define COL 9

//ʵ�ʵ��к���
#define ROWS ROW+2
#define COLS COL+2

//�׵�����
#define COUNT 10

void init_board(char board[ROWS][COLS],int rows,int cols,char a);//��ʼ������
void print_board(char board[ROWS][COLS],int row,int col);//��ӡ����
void set_mine(char board[ROWS][COLS], int row, int col);//������
char count_mine(char mine[ROWS][COLS], int x, int y);//������Χ�׵�����
int count_now(char show[ROWS][COLS]);//ͳ������������δ�Ų����������
void open_fun(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y);//ʵ������չ������
void open_board(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y);//չ��
void sweep_mine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);//ɨ��
void game(void);//��Ϸ
void menu(void);//�˵�

//��ʼ������
void init_board(char board[ROWS][COLS],int rows,int cols,char a)
{
    int i,j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            board[i][j] = a;//��ʼ��������
        }
    }
}

//��ӡ����
void print_board(char board[ROWS][COLS],int row,int col)
{
    int i, j;
    printf("   |");
    for(i = 1; i <= row; i++)//��ӡ������
    {
        printf(" %d |",i);
    }
    printf("\n");
	
    for(j = 0; j <= row; j++)
    {
        printf("---|");
    }
    printf("\n");
    //��ӡ���������������
    for(i = 1; i <= row; i++)
    {
        printf(" %d |",i);//��ӡ������
		
        for(j = 1; j <= col; j++)//��ӡ��������
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

//�����׺���
void set_mine(char board[ROWS][COLS], int row, int col)
{
    int count = COUNT;
    int x, y;
    while(count)
    {
        x = rand() % row + 1;//����1-9�������
        y = rand() % col + 1;
        if(board[x][y] == '0')//�ж����λ���Ƿ�����
        {
            board[x][y] = '1';
            count--;
        }
    }
}

//����������
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

//ͳ������������δ�Ų����������
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

//ʵ��չ������
void open_fun(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
    //����Χ8��λ�ý���չ��
    open_board(mine, show, x, y+1);
    open_board(mine, show, x, y-1);
    open_board(mine, show, x+1, y);
    open_board(mine, show, x-1, y);
    open_board(mine, show, x+1, y-1);
    open_board(mine, show, x-1, y+1);
    open_board(mine, show, x-1, y-1);
    open_board(mine, show, x+1, y+1);
}

//չ��ɨ��
void open_board(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
    if(mine[x][y]== '0'&& show[x][y] == '*'  && x>0 && y>0 && x<=ROW && y<=COL || show[x][y]=='?')
    {
        if(count_mine(mine, x, y) == '0')//�жϸô���Χ�Ƿ�����
        {
            show[x][y] = ' ';//�����Χû�׸ó�����ʾ��
            open_fun(mine, show, x, y);//����Χ8�����ӽ����ж��Ƿ����չ��
        }
        else
        {
            show[x][y] = count_mine(mine, x, y);
        }
    }
}

//������
void flag(char show[ROWS][COLS])
{
    int x = 0, y=0;
    char c;
    do
    {
        printf("_______________________\n");
        printf("�Ƿ��������׵�����:(y/n):");
        scanf(" %c",&c);
		
        if (c == 'y' || c == 'Y')//ѡ���Ƿ������
        {
            do
            {
                printf("______________\n");
                printf("����Ҫ��ǵ�����:");
                scanf(" %d%d",&x,&y);
                if (show[x][y] == '*' && x > 0 && y>0 && x <= ROW && y<=COL)//�жϸ�λ���Ƿ���������
                {
                    show[x][y] = '?';
                    break;
                }
                else
                    printf("��������ȷ����!\n");
            }while (1);
        }
    }while(c == 'y' || c == 'Y');//��ν��б��
}

//ɨ��
void sweep_mine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
    int x, y;
	
    while(count_now(show) > COUNT)
    {
        printf(">>>>>>>>>>>>>>\n");
        printf("����Ҫ�Ų������:");
        scanf("%d%d", &x, &y);
        if (x >= 1 && x <= row && y >= 1 && y <= col)
        {
            if (mine[x][y] == '1')//�ȵ��׽�������
            {
                printf("boom!!��ը����\n");
                printf("***GAME OVER***\n");
                print_board(mine,ROW,COL);
                printf("boom!!��ը����\n");
                printf("***GAME OVER***\n");
                break;
            }
            else
            {
                show[x][y] = count_mine(mine, x, y);
                if(show[x][y] == '0')
                {
                    open_fun(mine, show, x, y);//չ����ΧͬΪ�հ׵ĵط�
                    show[x][y] = ' ';
                }
                print_board(show,ROW,COL);
				
                if (count_now(show) == COUNT)//�ж��Ƿ��Ų��������
                {
                    printf("��ϲ��ɨ�׳ɹ�������\n");
                    print_board(mine,ROW,COL);
                    printf("��ϲ��ɨ�׳ɹ�������\n");
                }
                else
                {
                    flag(show);//�������
                    print_board(show, ROW, COL);
                }
            }
        }
        else
            printf("����������������룡\n");
    }
}

//��Ϸ����
void game(void)
{
    //���沼�õ�������
    char mine[ROWS][COLS]={0};
    //�����Ų���׵�����
    char show[ROWS][COLS]={0};
    //��ʼ��
    init_board(mine,ROWS,COLS,'0');
    init_board(show,ROWS,COLS,'*');
    //������
    set_mine(mine,ROW,COL);
    print_board(show,ROW,COL);
    //ɨ��
    sweep_mine(mine, show, ROW, COL);
}

//��ʼ�˵�
void menu(void)
{
    printf("***********************\n");
    printf("********  ɨ��  *******\n");
    printf("***********************\n");
    printf("***** 1. ��ʼ��Ϸ *****\n");
    printf("***** 0. �˳���Ϸ *****\n");
    printf("***********************\n");
}

//������
int main(void)
{
    int input;
    srand((unsigned)time(NULL));//���²������������
    do{ //�ɶ�ν�����Ϸ
        menu();
        printf("������:");
        scanf("%d",&input);
        switch(input)//������Ϸ�����˳���Ϸ
        {
		    case 1:
			   game();
			   break;
		    case 0:
			   printf("�˳���Ϸ\n");
			   break;
	   	    default:
			   printf("��������ȷ��ѡ��\n");
			   break;
        }
    }while(input);
    return 0;
}
