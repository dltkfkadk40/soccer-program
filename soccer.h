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

    struct SOCCER* prev; //struct SOCCER 가르키는 포인터변수(앞에 있는 구조체)
    struct SOCCER* next; //struct SOCCER 가르키느 포인터변수(뒤에 있는 구조체)
}SOCCER_t;

SOCCER_t* head = NULL;     //이중연결리스트 시작노드저장
SOCCER_t* current = NULL;  //현재화면에 표시되는 노드저장


//패턴 1 head 생성하기
void initialize_team(){
    head = (SOCCER_t *)calloc(1,sizeof(SOCCER_t));
    if(head == NULL){
        puts("힙영역에 STUDENT 구조체 생성 실패");
        getchar();
    }
return;
}

//패턴 2 노드 추가하기(처음 추가하기 , 마지막추가하기)
void append_node(SOCCER_t* data){
    SOCCER_t* p = head;

    //next NULL 인 마지막 노드로 이동
    while(p->next != NULL){
        p = p->next;
    }
    p->next = data;

    //추가된 node에서 바로 앞 node 가르킴.
    if(p != head){
        data->prev = p;
    }
return;
}

//패턴 3 노드 출력하기
void print_soccer_data(){
    SOCCER_t* p = head;

    if(p == NULL){
        puts("출력할 데이타가 없습니다.");
        return;
    }

    puts("=====================================================================");
    puts("팀이름 \t랭킹점수 경기수\t 승  무   패\t득점\t실점\t득실차\t승점");
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
        puts("출력할 SOCCER 구조체 없습니다. ");
        getchar();
        return;
    }

    printf("%14s [%s] \n","팀",current->name);
    printf("%14s [%d] \n","랭킹점수",current->lank_score);
    printf("%14s [%4d] \n","경기수",current->game_number);
    printf("%14s [%3d] \n","승",current->victory);
    printf("%14s [%3d] \n","무",current->draw);
    printf("%14s [%3d] \n","패",current->lose);
    printf("%14s [%3d] \n","득점",current->score);
    printf("%14s [%3d] \n","실점",current->lose_point);
    printf("%14s [%3d] \n","득실차",current->goal_difference);
    printf("%14s [%3d] \n","승점",current->point);
    puts("================================");

return;
}

SOCCER_t* new_team_data(){
    SOCCER_t* data = (SOCCER_t *)calloc(1,sizeof(SOCCER_t));

    if(data == NULL){
        puts("힙영역에 SOCCER 구조체 입력 실패");
        getchar();
        return NULL;
    }

    printf("%14s : ","팀");
    scanf_s("%s",data->name,sizeof(data->name));

    printf("%14s : ","랭킹점수");
    scanf_s("%d",&data->lank_score,sizeof(data->lank_score));
    data->game_number   = input_score("경기수");
    data->victory       = input_score("승");
    data->draw          = input_score("무");
    data->lose          = input_score("패");
    data->score         = input_score("득점");
    data->lose_point    = input_score("실점");
    data->goal_difference = data->score - data->lose_point;
    data->point = data->victory*3 + data->draw*1;

return data;
}

void update_soccer_data(SOCCER_t* current){

    if(current == NULL){
        puts("수정할 SOCCER 구조체 존재하지 않습니다.");
        getchar();
        return;
    }
    current->game_number   = input_score("수정 경기수");
    current->victory       = input_score("수정 승");
    current->draw          = input_score("수정 무");
    current->lose          = input_score("수정 패");
    current->score         = input_score("수정 득점");
    current->lose_point    = input_score("수정 실점");
    current->goal_difference = current->score - current->lose_point;
    current->point = current->victory*3 + current->draw*1;

return;
}

SOCCER_t* search_team_data(){
    SOCCER_t* p = head;
    SOCCER_t* data = NULL;
    int lank_score = 0;

    printf(" 검색할 팀(랭킹점수로 입력) : ");
    scanf("%d",&lank_score);

       //next NULL 인 마지막 노드로 이동
    while(p->next != NULL){
        p = p->next;
        if(p->lank_score == lank_score){
            data = p;
            break;
        }
    }

    if(data == NULL){
        printf("팀 랭킹점수[%4d] 없는 팀입니다. \n",lank_score);
        getchar();
        getchar();
    }

return data;
}

void insert_soccer_data(SOCCER_t* data){
    //1:head->next null 처음 위치 삽입
    if(head->next == NULL){
        head->next = data;
        return;
    }

    if(current->prev == NULL){            //3 처음노드 삽입
        data->next = head->next;
        data->next->prev = data;
        head->next = data;
    }else if(current->next == NULL){      //2.마지막 노드 삽입
        data->prev = current;
        current->next = data;
    }else if(current->next != NULL && current->prev != NULL){  //4.중간노드 삽입
        data->next = current->next;
        data->next->prev = data;
        current->next = data;
        data->prev = current;
    }else{
        puts("삽입에 문제 발생햇습니다.");
        getchar();
        getchar();
    }

return;
}

void delete_soccer_data(){
  SOCCER_t* p = current;

  //current 노드가 삭제되기 때문 current 이전노드, 다음노드, NULL변경
  if(current->next != NULL){
    current = current->next;
  }else if(current->next == NULL && current->prev != NULL){
    current = current->prev;
  }else{
    current = NULL;
  }

  if(p->next != NULL && p->prev == NULL){        //처음노드
    p->next->prev = NULL;
    head->next = p->next;
  }else if(p->next != NULL && p->prev != NULL){  //중간노드
    p->next->prev = p->prev;
    p->prev->next = p->next;
  }else if(p->next == NULL && p->prev != NULL){  //마지막 노드
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
            printf("%s 점수는(0~100) 입력하세요.\n",team);
            continue;
        }
        flag = 1;
    }//end of while

return score;
}



