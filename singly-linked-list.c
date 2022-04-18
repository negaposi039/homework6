/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node { // Node 구조체
	int key; // 원소를 저장할 값
	struct Node* link; // 자신과 같은 구조체를 가리키는 포인터
} listNode;

typedef struct Head { // Head 구조체
	struct Node* first; // first 노드를 가리키는 포인터
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h); // list 초기화하는 함수
int freeList(headNode* h); // list 동적할당 해제 함수

int insertFirst(headNode* h, int key); // list 처음에 key에 대한 노드 추가 함수
int insertNode(headNode* h, int key); // 노드 삽입 함수
int insertLast(headNode* h, int key); // list 마지막에 key에 대한 노드 추가 함수

int deleteFirst(headNode* h); // list 첫번째 노드 삭제 함수
int deleteNode(headNode* h, int key); // list에서 key에 대한 노드 삭제 함수
int deleteLast(headNode* h); // list 마지막 노드 삭제 함수
int invertList(headNode* h); // list 링크 역순 재배치 함수

void printList(headNode* h); // 노드 출력 함수

int main()
{
	char command; // 명령어
	int key; // key
	headNode* headnode=NULL; // NULL로 초기화

	do{
		printf("\n[----- [Kim Hyeong Jin]  [2021041079] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 명령어 입력

		switch(command) {
		case 'z': case 'Z': // 명령어 z : initialize 함수 이용하여 list 초기화
			headnode = initialize(headnode);
			break;
		case 'p': case 'P': // 명령어 p : printList 함수 이용하여 노드 출력
			printList(headnode);
			break;
		case 'i': case 'I': // 명령어 i : key 출력, insertNode 함수 이용하여 노드 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D': // 명령어 d : key 출력, deleteNode 함수 이용하여 노드 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': // 명령어 n : key 출력, insertLast 함수 이용하여 list 마지막에 key에 대한 노드 추가
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E': // 명령어 e : deleteLast 함수 이용하여 list 마지막 노드 삭제
			deleteLast(headnode);
			break;
		case 'f': case 'F': // 명령어 f : key 출력, insertFirst 함수 이용하여 list 처음에 key에 대한 노드 추가
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T': // 명령어 t : deleteFirst 함수 이용하여 list 첫번째 노드 삭제
			deleteFirst(headnode);
			break;
		case 'r': case 'R': // 명령어 r : invertList 함수 이용하여 list 링크 역순 재배치
			invertList(headnode);
			break;
		case 'q': case 'Q': // 명령어 q : freeList 함수 이용하여 동적할당된 메모리 해제
			freeList(headnode);
			break;
		default: // 이외의 경우 : 에러 메시지
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 명령어 q : 종료

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // temp 동적할당
	temp->first = NULL; // temp->first에 NULL값 저장
	return temp; // temp 값 리턴
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; // 헤드 노드 주소값 포인터 p에 저장

	listNode* prev = NULL; // 포인터 prev NULL값으로 초기화
	while(p != NULL) { // p가 NULL이 아니면 반복
		prev = p; // prev에 p 저장
		p = p->link; // p->link p에 저장하여 다음 노드로 이동
		free(prev); // prev 해제
	}
	free(h); // 헤드 노드 해제
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node 동적할당
	node->key = key; // node->key에 key값 저장
	node->link = NULL; // node->link NULL로 초기화

	if (h->first == NULL) // h->first가 NULL이면
	{
		h->first = node; // h->first에 node 값 저장
		return 0;
	}

	listNode* n = h->first; // 포인터 n이 헤드 노드를 가리키도록 함
	listNode* trail = h->first; // 이전 노드 포인터 trail이 헤드 노드를 가리키도록 함

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { // n이 NULL이 아니면 반복
		if(n->key >= key) { // n->key가 더 클 때
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { // n==h->first이면
				h->first = node; // h->first에 node 저장
				node->link = n; //node->link에 n 저장
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n; // node->link에 n 저장
				trail->link = node; // trail->link에 node 저장
			}
			return 0;
		}

		trail = n; // trail에 n 저장
		n = n->link; // n에 n->link 저장 (다음 노드 이동)
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node; // 마지막 삽입
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node 동적 할당
	node->key = key; // 삽입하려는 노드의 key에 key값 저장
	node->link = NULL; // 노드의 링크 NULL 초기화

	if (h->first == NULL) // h->first == NULL일 경우
	{
		h->first = node; // 헤드 노드에 node 저장
		return 0;
	}

	listNode* n = h->first; // 포인터 n이 헤드 노드를 가리키도록 함
	while(n->link != NULL) { // n->link가 NULL이 아니면 반복
		n = n->link; // n에 n->link 저장 (다음 노드 이동)
	}
	n->link = node; // n->link가 삽입하려는 node를 가리키도록 함
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node 동적 할당
	node->key = key; // 노드의 key에 key값 저장

	node->link = h->first; // 헤드 노드가 가리키고 있는 값 node->link에 저장
	h->first = node; // 헤드 노드에 노드 주소값 저장

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) // h->first가 NULL이면 에러 메시지
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; // 포인터 n이 헤드 노드를 가리키도록 함
	listNode* trail = NULL; // 이전 노드, NULL로 초기화

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { // n이 NULL이 아니면 반복
		if(n->key == key) { // n->key가 key일 때
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { // n==h->first이면
				h->first = n->link; // h-first에 n->link 저장
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link; // trail->link에 n->link 저장
			}
			free(n); // n 해제
			return 0;
		}

		trail = n; // n이 가리키는 노드를 trail도 가리키도록 함
		n = n->link; // 다음 노드 이동
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key); // 에러 메시지
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) // h->first가 NULL인 경우 에러 메시지
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; // 포인터 n이 헤드 노드를 가리키도록 함
	listNode* trail = NULL; // 이전 노드, NULL로 초기화

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) { // n->link가 NULL이면
		h->first = NULL; // 헤드 노드 NULL 초기화
		free(n); // n 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) { // n->link가 NULL이 아니면
		trail = n; // trail이 n이 가리키는 값(헤드 노드)을 가리키도록 함
		n = n->link; // n에 n->link 저장 (다음 노드 이동)
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL; // 이전 노드 링크 NULL 초기화
	free(n); // n 해제

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) // h->first가 NULL이면 에러 메시지
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; // 포인터 n이 헤드 노드를 가리키도록 함

	h->first = n->link; // first가 가리키는 다음 노드 주소를 헤드 노드에 대입
	free(n); // n 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { // h->first가 NULL이면 에러 메시지
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; // 포인터 n이 헤드 노드를 가리키도록 함
	listNode *trail = NULL; // 포인터 trail NULL 초기화
	listNode *middle = NULL; // 포인터 middle NULL 초기화

	while(n != NULL){
		trail = middle; // middle이 가리키는 노드를 trail도 가리키도록 함
		middle = n; // n이 가리키는 노드를 middle도 가리키도록 함
		n = n->link; // 다음 노드 이동
		middle->link = trail; // middle의 link가 trail 노드를 가리키도록 함
	}

	h->first = middle; // 헤드 노드가 middle이 가리키는 노드를 가리키도록함

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // h == NULL 이면 에러 메시지
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; // p에 h->first (첫번째 노드 주소) 저장

	while(p != NULL) { // p가 NULL이 아니면 반복
		printf("[ [%d]=%d ] ", i, p->key); // 노드 번호와 p가 가리키는 key 값 출력
		p = p->link; // 다음 노드 이동
		i++;
	}

	printf("  items = %d\n", i); // 노드 총 개수 출력
}

