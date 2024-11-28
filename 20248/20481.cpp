#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define SIZE 4

int board[SIZE][SIZE];

void game() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}
//初始化，均为0 
void print() {
    printf("\033[94m"); // 34 是蓝色的 ANSI 颜色代码.把框和数字设置成蓝色 
    printf("+-------------------+\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                printf("|    "); //无数字就空格子 
            } else {
                printf("|%4d", board[i][j]); // 格子中有数字时显示数字
            }
        }
        printf("|\n");
        if (i != SIZE - 1) {
            printf("|----+----+----+----|\n");
        }
    }
    printf("+-------------------+\n");
    printf("\033[0m"); // 重置为默认颜色
}


void number() {
    int x, y;
    do {
        x = rand() % SIZE;//令x生成0到3（SIZE-1）的 数字 
        y = rand() % SIZE;
    } while (board[x][y] != 0);
    board[x][y] = (rand() % 10 < 9) ? 2 : 4; // 随机生成2或4
}
//随机数的诞生 

void clean() {
#ifdef _WIN32
    system("cls");
#endif
}
//清屏大法 
void compress(int* row)/*  这个*就是类似【】，row[]  */ {
    int temp[SIZE] = {0};
    int index = 0; 

    for (int i = 0; i < SIZE; i++) {
        if (row[i] != 0) {
            temp[index++] = row[i];
        }
    }
//储存非0的东西 
    for (int i = 0; i < SIZE -1; i++) {
        if (temp[i] == temp[i + 1] && temp[i] != 0) {
            temp[i] *= 2;     // 合并
            temp[i + 1] = 0;  // 清除合并的部分
        }
    }
 //合并 
    index = 0;
    for (int i = 0; i < SIZE; i++) {
        if (temp[i] != 0) {
            row[index++] = temp[i];
        } else {
            row[index++] = 0;
        }
    }
}

/*            移      动      的     地     方                           */ 
int move_left() {
    int moved = 0;
    for (int i = 0; i < SIZE; i++) {
        int original[SIZE];
        for (int j = 0; j < SIZE; j++) {
            original[j] = board[i][j];
        }

        compress(board[i]); // 压缩行

        // 检查是否有移动或合并
        for (int j = 0; j < SIZE; j++) {
            if (original[j] != board[i][j]) {
                moved = 1;
                break;
            }
        }
    }
    return moved;
}

int move_right() {
    int moved = 0;
    for (int i = 0; i < SIZE; i++) {
        int reversed[SIZE];
        for (int j = 0; j < SIZE; j++){
            reversed[j] = board[i][SIZE - j - 1]; // 倒着来的 
        }

        compress(reversed); // 压缩行

        for (int j = 0; j < SIZE; j++) {
            board[i][SIZE - j - 1] = reversed[j]; // 放回原行
        }

        // 检查是否有移动或合并
        for (int j = 0; j < SIZE; j++) {
            if (reversed[j] != board[i][SIZE - j - 1]) {
                moved = 1;
                break;
            }
        }
    }
    return moved;
}

int move_up() {
    int moved = 0;
    for (int j = 0; j < SIZE; j++) {
        int col[SIZE];
        for (int i = 0; i < SIZE; i++) {
            col[i] = board[i][j]; // 提取列
        }

        int original[SIZE];
        for (int i = 0; i < SIZE; i++) {
            original[i] = col[i]; // 备份原始列
        }

        compress(col); // 压缩列

        for (int i = 0; i < SIZE; i++) {
            board[i][j] = col[i]; // 放回列
        }

        // 检查是否有移动或合并
        for (int i = 0; i < SIZE; i++) {
            if (original[i] != board[i][j]) {
                moved = 1; // 发生了移动
                break;
            }
        }
    }
    return moved;
}

int move_down() {
    int moved = 0;
    for (int j = 0; j < SIZE; j++) {
        int col[SIZE];
        for (int i = 0; i < SIZE; i++) {
            col[i] = board[SIZE - i - 1][j]; // 提取反转列
        }

        int original[SIZE];
        for (int i = 0; i < SIZE; i++) {
            original[i] = col[i]; // 备份原始列
        }

        compress(col); // 压缩列

        for (int i = 0; i < SIZE; i++) {
            board[SIZE - i - 1][j] = col[i]; // 放回原列
        }

        // 检查是否有移动或合并
        for (int i = 0; i < SIZE; i++) {
            if (original[i] != board[SIZE - i - 1][j]) {
                moved = 1; // 发生了移动
                break;
            }
        }
    }
    return moved;
}


void handle() {
    int ch = getch();
    if (ch == 224) {
        ch = getch();
        int moved = 0; // 标记是否有移动发生
        switch (ch) {
            case 72: moved = move_up(); break;    // 上
            case 80: moved = move_down(); break;  // 下
            case 75: moved = move_left(); break;  // 左
            case 77: moved = move_right(); break; // 右
            default: break;
        }
        if (moved) {
            number(); // 仅在发生移动后生成新数字
        }
    }
}

int game_over() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return 0; // 还有空位
            }
        }
    }
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) {
                return 0; // 可以合并
            }
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) {
                return 0; // 可以合并
            }
        }
    }
    return 1; // 游戏结束
}



void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x); //用ANSI转义序列移动光标
}
//别去找什么windows 的函数了，太长了。。。。

void game_over_message() {
	gotoxy(5,2);//移动光标 
	printf("\033[1;32m");//设置颜色为绿色 
    printf("+---------+\n");
    gotoxy(5,3);
    printf("|You Lost!|\n");
    gotoxy(5,4);
    printf("+---------+\n");
    printf("\033[0m");
}
//ANSI转义符的格式貌似是\033[..... 
int main() {
    srand(time(0));
    game(); 
    number(); 
    number(); 
    print(); 

    while (1) {
        handle(); 
        clean(); 
        print(); 
        printf("\033[34m") ;//BULE!
        printf("  UP:↑   DOWN:↓\n");
        printf("LEFT:←  RIGHT:→\n");
        printf("\033[0m");
        if (game_over()) {
            game_over_message(); 
            break; 
        }
    }

    return 0;
}

