#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int isLeapYear(int year)
{
	return (year%4==0&&year%100!=0)||(year%400==0);
}
int dayget(int year,int month)
{
	int daysinmonth[]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(month==2&&isLeapYear(year))
	{
		return 29;
	}
	return daysinmonth[month-1];
}
     
int caile(int year,int month)
{
	if(month==1||month==2)
	{
		month+=12;
		year--;
	}
	 
	int d=1; 
	int j=year/100;
	int k=year%100;
	int h = (d + 13 * (month + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    return (h+5)%7;
 } 
	

void print(int year,int month)
{
	int days=dayget(year,month);
	int start=caile(year,month); 
	printf("\n     %d-%02d\n", year, month);
    printf("Mon  Tue  Wed  Thu  Fri  Sat  Sun\n");
    for (int i = 0; i < start;i++)
	{
    printf("     ");
}
   for(int day=1;day<=days;day++)
   {
   	printf("%-5d",day); 
   	if((start+day)%7==0)
   	{
   		printf("\n");
	   }  	
   }
   printf("\n");
}

void clean()
{
	system("cls");
}
int main ()
{
	
	int year,month;
	printf("输入你的年份及月份（格式：2024-8):"); 
	scanf("%d-%d",&year,&month);
	print(year,month);
	
while (1) {
    clean(); 
    print(year, month); 
    printf("(*) Press ↑ and ↓ to switch the year.\n");
    printf("(*) Press ← and → to switch months.\n");
    printf("(*) Press P to go to particular year and month.\n");
    printf("(*) Press ESC to exit.\n");
    char ch = _getch(); 

    if (ch == 27) { // ESC（27） 键退出
        break;
    } else if (ch == 75) { // 左
        month--;
        if (month < 1) {
            month = 12;
            year--; // 如果月变成0，调整为上一年的12月
        }
    } else if (ch == 77) { // 右
        month++;
        if (month > 12) {
            month = 1;
            year++; // 如果月超过12，调整为下一年的1月
        }
    } else if (ch == 72) { // 上
        year++;
    } else if (ch == 80) { // 下
        year--;
    }
}
    return 0;	
 } 
