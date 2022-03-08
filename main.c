//열거형 상수 : 축구주 메뉴 선택 사용
enum MAIN_MENU {END, READ, PRINT, EDIT, WRITE};
enum MAIN_MENU main_select;

//열거형 상수 : 팀 관리 부 메뉴 선택 사용
enum EDIT_MENU {EXIT, PREV, NEXT, INSERT, MODIFY, DELETE, SEARCH};
enum EDIT_MENU edit_select;

#include "soccer.h"

void read_soccer_data();   //soccer_data.txt 데이터 읽어오기
void write_soccer_data();  //soccer_data.txt 데이터 저장하기

char soccer_file_name[] = "soccer_data.txt";

int main()
{
    int flag = 0;
    initialize_team();   //연결리스트 head 생성

    while(!flag && head != NULL){
        system("cls");
        puts("================================");
        puts("\t  축구 관리 프로그램 \t");
        puts("================================");
        puts("1.축구프로그램 파일에서 가져오기");
        puts("2.축구프로그램 현황보기");
        puts("3.축구프로그램 관리하기");
        puts("4.축구프로그램 파일에 저장하기");
        puts("0.종료");
        printf(">> ");
        scanf_s("%d",&main_select);
        getchar();

        switch(main_select){
            case READ:
                read_soccer_data();
                getchar();
                break;
            case PRINT:
                print_soccer_data();
                getchar();
                break;
            case EDIT:
                edit_soccer_data();
                break;
            case WRITE:
                write_soccer_data();
                getchar();
                break;
            case END:
                flag = 1;
                break;
            default:
                puts("다시선택 하세요.~");
                getchar();
                break;
        }//end of switch

    }//end of while

    return 0;
}

void read_soccer_data(){
    SOCCER_t* data = NULL;
    FILE* file = NULL;
    int flag = 0;
    int count = 0;

    printf("읽어올 팀 정보 파일이름 입력 >> ");
    scanf_s("%s",soccer_file_name, sizeof(soccer_file_name));
    getchar();

    file = fopen(soccer_file_name, "rt");

    if(file == NULL){
        printf("%s 파일을 읽지 못했습니다. \n",soccer_file_name);
        return;
    }

    while(!flag){
        data = (SOCCER_t *)calloc(1,sizeof(SOCCER_t));
        int result = fscanf(file,"%s %d %d %d %d %d %d %d %d %d",
               data->name,&data->lank_score,&data->game_number,&data->victory,&data->draw,&data->lose,
               &data->score,&data->lose_point,&data->goal_difference,&data->point);

        if(result == EOF){
           flag = 1;
           continue;
        }

        append_node(data);  //이중연결리스트 data 구조체 추가연결
        count++;

        printf("%s %d %d %d %d %d %d %d %d %d \n",
            data->name,data->lank_score,data->game_number,data->victory,data->draw,data->lose,
            data->score,data->lose_point,data->goal_difference,data->point);
    }

    printf("%d 개의 데이터를 읽었습니다. ",count);
    fclose(file);
    getchar();

    return;
}


void write_soccer_data(){
    SOCCER_t* p = head;
    FILE* file = NULL;
    int count = 0;

    file = fopen(soccer_file_name, "wt");

    if(file == NULL){
        printf("%s 파일을 저장하지 못했습니다. \n",soccer_file_name);
        return;
    }

    while(p->next != NULL){
        p = p->next;
        int result = fprintf(file,"%s %d %d %d %d %d %d %d %d %d \n",
              p->name,p->lank_score,p->game_number,p->victory,p->draw,p->lose,
              p->score,p->lose_point,p->goal_difference,p->point);

        if(result == EOF){
            printf("%s 파일을 저장도중에 문제가 발생했습니다. ",soccer_file_name);
            break;
        }
        count++;
    }

    printf("%d 개의 데이터를 저장했습니다. ",count);
    fclose(file);
    getchar();

return;
}

//이전 팀,다음 팀,팀 등록,팀 수정,팀 삭제,팀 검색
void edit_soccer_data(){
   SOCCER_t* data = NULL;
   current = head->next;     //실제 데이타가 저장된 노드위치 저장
   int flag = 0;

   while(!flag && head != NULL){
        system("cls");
        puts("================================");
        puts("\t 축구 팀관리 \t");
        puts("================================");

        if(current != NULL){
            print_one_soccer_data(current);
        }

        puts("1.이전 팀");
        puts("2.다음 팀");
        puts("3.팀 등록");
        puts("4.팀 수정");
        puts("5.팀 삭제");
        puts("6.팀 검색");
        puts("0.돌아가기");
        printf(">> ");
        scanf_s("%d",&edit_select);
        getchar();

        //보여줄 node가 없어서, 이전, 다음, 수정, 삭제, 검색기능 불허가
        //등록, 돌아가기 기능 허가
        if(current == NULL){
            switch(edit_select){
                case PREV:
                case NEXT:
                case MODIFY:
                case DELETE:
                case SEARCH:
                    continue;
            }
        }

        switch(edit_select){
            case PREV:
                if(current->prev != NULL){
                    current = current->prev;
                }
                break;
            case NEXT:
                if(current->next != NULL){
                    current = current->next;
                }
                break;
            case INSERT:
                data = new_team_data();
                //1,2,3,4 삽입 작전 1:head 삽입, 2:마지막노드 삽입, 3: 처음노드 삽입, 4:중간노드삽입
                insert_soccer_data(data);
                getchar();
                break;
            case MODIFY:
                update_soccer_data(current);
                getchar();
                break;
            case DELETE:
                delete_soccer_data();
                break;
           case SEARCH:
                data = search_team_data();
                if(data != NULL){
                    current = data;
                }
                break;
           case EXIT:
                flag = 1;
                break;
            default:
                puts("다시선택 하세요.~");
                getchar();
                break;
        }//end of switch

   }//end of while

return;
}
