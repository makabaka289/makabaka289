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
//��ʼ������Ϊ0 
void print() {
    printf("\033[94m"); // 34 ����ɫ�� ANSI ��ɫ����.�ѿ���������ó���ɫ 
    printf("+-------------------+\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                printf("|    "); //�����־Ϳո��� 
            } else {
                printf("|%4d", board[i][j]); // ������������ʱ��ʾ����
            }
        }
        printf("|\n");
        if (i != SIZE - 1) {
            printf("|----+----+----+----|\n");
        }
    }
    printf("+-------------------+\n");
    printf("\033[0m"); // ����ΪĬ����ɫ
}


void number() {
    int x, y;
    do {
        x = rand() % SIZE;//��x����0��3��SIZE-1���� ���� 
        y = rand() % SIZE;
    } while (board[x][y] != 0);
    board[x][y] = (rand() % 10 < 9) ? 2 : 4; // �������2��4
}
//������ĵ��� 

void clean() {
#ifdef _WIN32
    system("cls");
#endif
}
//������ 
void compress(int* row)/*  ���*�������ơ�����row[]  */ {
    int temp[SIZE] = {0};
    int index = 0; 

    for (int i = 0; i < SIZE; i++) {
        if (row[i] != 0) {
            temp[index++] = row[i];
        }
    }
//�����0�Ķ��� 
    for (int i = 0; i < SIZE -1; i++) {
        if (temp[i] == temp[i + 1] && temp[i] != 0) {
            temp[i] *= 2;     // �ϲ�
            temp[i + 1] = 0;  // ����ϲ��Ĳ���
        }
    }
 //�ϲ� 
    index = 0;
    for (int i = 0; i < SIZE; i++) {
        if (temp[i] != 0) {
            row[index++] = temp[i];
        } else {
            row[index++] = 0;
        }
    }
}

/*            ��      ��      ��     ��     ��                           */ 
int move_left() {
    int moved = 0;
    for (int i = 0; i < SIZE; i++) {
        int original[SIZE];
        for (int j = 0; j < SIZE; j++) {
            original[j] = board[i][j];
        }

        compress(board[i]); // ѹ����

        // ����Ƿ����ƶ���ϲ�
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
            reversed[j] = board[i][SIZE - j - 1]; // �������� 
        }

        compress(reversed); // ѹ����

        for (int j = 0; j < SIZE; j++) {
            board[i][SIZE - j - 1] = reversed[j]; // �Ż�ԭ��
        }

        // ����Ƿ����ƶ���ϲ�
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
            col[i] = board[i][j]; // ��ȡ��
        }

        int original[SIZE];
        for (int i = 0; i < SIZE; i++) {
            original[i] = col[i]; // ����ԭʼ��
        }

        compress(col); // ѹ����

        for (int i = 0; i < SIZE; i++) {
            board[i][j] = col[i]; // �Ż���
        }

        // ����Ƿ����ƶ���ϲ�
        for (int i = 0; i < SIZE; i++) {
            if (original[i] != board[i][j]) {
                moved = 1; // �������ƶ�
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
            col[i] = board[SIZE - i - 1][j]; // ��ȡ��ת��
        }

        int original[SIZE];
        for (int i = 0; i < SIZE; i++) {
            original[i] = col[i]; // ����ԭʼ��
        }

        compress(col); // ѹ����

        for (int i = 0; i < SIZE; i++) {
            board[SIZE - i - 1][j] = col[i]; // �Ż�ԭ��
        }

        // ����Ƿ����ƶ���ϲ�
        for (int i = 0; i < SIZE; i++) {
            if (original[i] != board[SIZE - i - 1][j]) {
                moved = 1; // �������ƶ�
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
        int moved = 0; // ����Ƿ����ƶ�����
        switch (ch) {
            case 72: moved = move_up(); break;    // ��
            case 80: moved = move_down(); break;  // ��
            case 75: moved = move_left(); break;  // ��
            case 77: moved = move_right(); break; // ��
            default: break;
        }
        if (moved) {
            number(); // ���ڷ����ƶ�������������
        }
    }
}

int game_over() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return 0; // ���п�λ
            }
        }
    }
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) {
                return 0; // ���Ժϲ�
            }
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) {
                return 0; // ���Ժϲ�
            }
        }
    }
    return 1; // ��Ϸ����
}



void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x); //��ANSIת�������ƶ����
}
//��ȥ��ʲôwindows �ĺ����ˣ�̫���ˡ�������

void game_over_message() {
	gotoxy(5,2);//�ƶ���� 
	printf("\033[1;32m");//������ɫΪ��ɫ 
    printf("+---------+\n");
    gotoxy(5,3);
    printf("|You Lost!|\n");
    gotoxy(5,4);
    printf("+---------+\n");
    printf("\033[0m");
}
//ANSIת����ĸ�ʽò����\033[..... 
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
        printf("  UP:��   DOWN:��\n");
        printf("LEFT:��  RIGHT:��\n");
        printf("\033[0m");
        if (game_over()) {
            game_over_message(); 
            break; 
        }
    }

    return 0;
}

