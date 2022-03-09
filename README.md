- 팀정보 구조체 

typedef struct SOCCER{

    char name[20];
    
    int game_number;
    
    int victory;
    
    int draw;
    
    int lose;
    
    int score;
    
    int lose_point;
    
    int goal_difference;
    
    int point;

    struct SOCCER* prev; 
    
    struct SOCCER* next; 
    
}SOCCER_t;

- name

        팀 이름의 의미를 가지고있음

        20자리까지 사용

- game_number

        랭킹점수의 의미를 가지고 있음

- victory

        승리의 의미를 가지고 있음

- draw

        무승부의 의미를 가지고 있음

- lose

        패배의 의미를 가지고있음

- score

        득점의 의미를 가지고있음

- lose_point

        실점의 의미를 가지고있음

- goal_difference

        득실차의 의미를 가지고있음

- point

        승점의 의미를 가지고있음

- struct SOCCER* prev, struct SOCCER* next;

        이중연결리스틑 위한 구조

        각각 전의 팀/ 다음 팀 을 가리킴

- SOCCER_t* head = NULL, SOCCER_t* current

        이중연결 리스트를 위한 구조

- read_soccer_data()

        키보드로 문자열을 입력받아 값을 읽어옴

        읽어온값을 구조체끼리 연결

- write_soccer_data()

        현재 팀 정보를 저장한다

- SOCCER_t* new_team_data()

        새로운 팀을 키보드로 입력받아 값을 저장한다

- SOCCER_t* search_team_data()

        저장되어있는 팀을 검색하여 정보를 보여준다

- void insert_soccer_data(SOCCER_t* data)

        저장된 값을 뒤에다가 저장한다

- update_soccer_data(current)

        보여주고있는 팀을 키보드로 수정한다

- delete_soccer_data()

        보여주고있는 팀을 삭제한다


