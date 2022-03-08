//������ ��� : �౸�� �޴� ���� ���
enum MAIN_MENU {END, READ, PRINT, EDIT, WRITE};
enum MAIN_MENU main_select;

//������ ��� : �� ���� �� �޴� ���� ���
enum EDIT_MENU {EXIT, PREV, NEXT, INSERT, MODIFY, DELETE, SEARCH};
enum EDIT_MENU edit_select;

#include "soccer.h"

void read_soccer_data();   //soccer_data.txt ������ �о����
void write_soccer_data();  //soccer_data.txt ������ �����ϱ�

char soccer_file_name[] = "soccer_data.txt";

int main()
{
    int flag = 0;
    initialize_team();   //���Ḯ��Ʈ head ����

    while(!flag && head != NULL){
        system("cls");
        puts("================================");
        puts("\t  �౸ ���� ���α׷� \t");
        puts("================================");
        puts("1.�౸���α׷� ���Ͽ��� ��������");
        puts("2.�౸���α׷� ��Ȳ����");
        puts("3.�౸���α׷� �����ϱ�");
        puts("4.�౸���α׷� ���Ͽ� �����ϱ�");
        puts("0.����");
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
                puts("�ٽü��� �ϼ���.~");
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

    printf("�о�� �� ���� �����̸� �Է� >> ");
    scanf_s("%s",soccer_file_name, sizeof(soccer_file_name));
    getchar();

    file = fopen(soccer_file_name, "rt");

    if(file == NULL){
        printf("%s ������ ���� ���߽��ϴ�. \n",soccer_file_name);
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

        append_node(data);  //���߿��Ḯ��Ʈ data ����ü �߰�����
        count++;

        printf("%s %d %d %d %d %d %d %d %d %d \n",
            data->name,data->lank_score,data->game_number,data->victory,data->draw,data->lose,
            data->score,data->lose_point,data->goal_difference,data->point);
    }

    printf("%d ���� �����͸� �о����ϴ�. ",count);
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
        printf("%s ������ �������� ���߽��ϴ�. \n",soccer_file_name);
        return;
    }

    while(p->next != NULL){
        p = p->next;
        int result = fprintf(file,"%s %d %d %d %d %d %d %d %d %d \n",
              p->name,p->lank_score,p->game_number,p->victory,p->draw,p->lose,
              p->score,p->lose_point,p->goal_difference,p->point);

        if(result == EOF){
            printf("%s ������ ���嵵�߿� ������ �߻��߽��ϴ�. ",soccer_file_name);
            break;
        }
        count++;
    }

    printf("%d ���� �����͸� �����߽��ϴ�. ",count);
    fclose(file);
    getchar();

return;
}

//���� ��,���� ��,�� ���,�� ����,�� ����,�� �˻�
void edit_soccer_data(){
   SOCCER_t* data = NULL;
   current = head->next;     //���� ����Ÿ�� ����� �����ġ ����
   int flag = 0;

   while(!flag && head != NULL){
        system("cls");
        puts("================================");
        puts("\t �౸ ������ \t");
        puts("================================");

        if(current != NULL){
            print_one_soccer_data(current);
        }

        puts("1.���� ��");
        puts("2.���� ��");
        puts("3.�� ���");
        puts("4.�� ����");
        puts("5.�� ����");
        puts("6.�� �˻�");
        puts("0.���ư���");
        printf(">> ");
        scanf_s("%d",&edit_select);
        getchar();

        //������ node�� ���, ����, ����, ����, ����, �˻���� ���㰡
        //���, ���ư��� ��� �㰡
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
                //1,2,3,4 ���� ���� 1:head ����, 2:��������� ����, 3: ó����� ����, 4:�߰�������
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
                puts("�ٽü��� �ϼ���.~");
                getchar();
                break;
        }//end of switch

   }//end of while

return;
}
