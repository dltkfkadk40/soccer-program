#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SOCCER{
    char name[20];
    int lank_score;
    int game_number;
    int victory;
    int draw;
    int lose;
    int score;
    int lose_point;
    int goal_difference;
    int point;

    struct SOCCER* prev; //struct SOCCER ����Ű�� �����ͺ���(�տ� �ִ� ����ü)
    struct SOCCER* next; //struct SOCCER ����Ű�� �����ͺ���(�ڿ� �ִ� ����ü)
}SOCCER_t;

SOCCER_t* head = NULL;     //���߿��Ḯ��Ʈ ���۳������
SOCCER_t* current = NULL;  //����ȭ�鿡 ǥ�õǴ� �������


//���� 1 head �����ϱ�
void initialize_team(){
    head = (SOCCER_t *)calloc(1,sizeof(SOCCER_t));
    if(head == NULL){
        puts("�������� STUDENT ����ü ���� ����");
        getchar();
    }
return;
}

//���� 2 ��� �߰��ϱ�(ó�� �߰��ϱ� , �������߰��ϱ�)
void append_node(SOCCER_t* data){
    SOCCER_t* p = head;

    //next NULL �� ������ ���� �̵�
    while(p->next != NULL){
        p = p->next;
    }
    p->next = data;

    //�߰��� node���� �ٷ� �� node ����Ŵ.
    if(p != head){
        data->prev = p;
    }
return;
}

//���� 3 ��� ����ϱ�
void print_soccer_data(){
    SOCCER_t* p = head;

    if(p == NULL){
        puts("����� ����Ÿ�� �����ϴ�.");
        return;
    }

    puts("=====================================================================");
    puts("���̸� \t��ŷ���� ����\t ��  ��   ��\t����\t����\t�����\t����");
    puts("=====================================================================");

    while(p->next != NULL){
        p = p->next;
        printf("%s\t%5d\t%4d\t%3d %3d %3d\t%3d\t%3d\t%3d\t%3d\n",
           p->name,p->lank_score,p->game_number,p->victory,p->draw,p->lose,
           p->score,p->lose_point,p->goal_difference,p->point);
    }
return;
}

void print_one_soccer_data(SOCCER_t* current){
    if(current == NULL){
        puts("����� SOCCER ����ü �����ϴ�. ");
        getchar();
        return;
    }

    printf("%14s [%s] \n","��",current->name);
    printf("%14s [%d] \n","��ŷ����",current->lank_score);
    printf("%14s [%4d] \n","����",current->game_number);
    printf("%14s [%3d] \n","��",current->victory);
    printf("%14s [%3d] \n","��",current->draw);
    printf("%14s [%3d] \n","��",current->lose);
    printf("%14s [%3d] \n","����",current->score);
    printf("%14s [%3d] \n","����",current->lose_point);
    printf("%14s [%3d] \n","�����",current->goal_difference);
    printf("%14s [%3d] \n","����",current->point);
    puts("================================");

return;
}

SOCCER_t* new_team_data(){
    SOCCER_t* data = (SOCCER_t *)calloc(1,sizeof(SOCCER_t));

    if(data == NULL){
        puts("�������� SOCCER ����ü �Է� ����");
        getchar();
        return NULL;
    }

    printf("%14s : ","��");
    scanf_s("%s",data->name,sizeof(data->name));

    printf("%14s : ","��ŷ����");
    scanf_s("%d",&data->lank_score,sizeof(data->lank_score));
    data->game_number   = input_score("����");
    data->victory       = input_score("��");
    data->draw          = input_score("��");
    data->lose          = input_score("��");
    data->score         = input_score("����");
    data->lose_point    = input_score("����");
    data->goal_difference = data->score - data->lose_point;
    data->point = data->victory*3 + data->draw*1;

return data;
}

void update_soccer_data(SOCCER_t* current){

    if(current == NULL){
        puts("������ SOCCER ����ü �������� �ʽ��ϴ�.");
        getchar();
        return;
    }
    current->game_number   = input_score("���� ����");
    current->victory       = input_score("���� ��");
    current->draw          = input_score("���� ��");
    current->lose          = input_score("���� ��");
    current->score         = input_score("���� ����");
    current->lose_point    = input_score("���� ����");
    current->goal_difference = current->score - current->lose_point;
    current->point = current->victory*3 + current->draw*1;

return;
}

SOCCER_t* search_team_data(){
    SOCCER_t* p = head;
    SOCCER_t* data = NULL;
    int lank_score = 0;

    printf(" �˻��� ��(��ŷ������ �Է�) : ");
    scanf("%d",&lank_score);

       //next NULL �� ������ ���� �̵�
    while(p->next != NULL){
        p = p->next;
        if(p->lank_score == lank_score){
            data = p;
            break;
        }
    }

    if(data == NULL){
        printf("�� ��ŷ����[%4d] ���� ���Դϴ�. \n",lank_score);
        getchar();
        getchar();
    }

return data;
}

void insert_soccer_data(SOCCER_t* data){
    //1:head->next null ó�� ��ġ ����
    if(head->next == NULL){
        head->next = data;
        return;
    }

    if(current->prev == NULL){            //3 ó����� ����
        data->next = head->next;
        data->next->prev = data;
        head->next = data;
    }else if(current->next == NULL){      //2.������ ��� ����
        data->prev = current;
        current->next = data;
    }else if(current->next != NULL && current->prev != NULL){  //4.�߰���� ����
        data->next = current->next;
        data->next->prev = data;
        current->next = data;
        data->prev = current;
    }else{
        puts("���Կ� ���� �߻��޽��ϴ�.");
        getchar();
        getchar();
    }

return;
}

void delete_soccer_data(){
  SOCCER_t* p = current;

  //current ��尡 �����Ǳ� ���� current �������, �������, NULL����
  if(current->next != NULL){
    current = current->next;
  }else if(current->next == NULL && current->prev != NULL){
    current = current->prev;
  }else{
    current = NULL;
  }

  if(p->next != NULL && p->prev == NULL){        //ó�����
    p->next->prev = NULL;
    head->next = p->next;
  }else if(p->next != NULL && p->prev != NULL){  //�߰����
    p->next->prev = p->prev;
    p->prev->next = p->next;
  }else if(p->next == NULL && p->prev != NULL){  //������ ���
    p->prev->next = NULL;
  }else{
    head->next = NULL;
  }

  free(p);
return;
}


int input_score(char *team){
    int score = 0;
    int flag = 0;
    while(!flag){
        printf("%14s : ",team);
        scanf_s("%d",&score);
        if(score < 0 || score > 100){
            printf("%s ������(0~100) �Է��ϼ���.\n",team);
            continue;
        }
        flag = 1;
    }//end of while

return score;
}



