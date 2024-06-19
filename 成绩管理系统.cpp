#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
  
// ����ѧ���ɼ���Ϣ�ṹ��  
typedef struct Student 
{  
    char name[100];  
    int score;  
    struct Student *next;  
} Student;  
  
// ��ʼ�����Ա�����������  
void InitList(Student **head) 
{  
    *head = NULL; // ��ͷָ����Ϊ�գ���ʾ��ʼ����Ϊ��
	printf("�������ѳ�ʼ�����\n"); 
}  
  
// ����ѧ����Ϣ  
void InsertStudent(Student **head, char name[], int score) 
{  
    Student *newNode = (Student *)malloc(sizeof(Student)); // �����µĽڵ��ڴ� 
    if (!newNode) 
	{  
        printf("�ڴ�ڵ����ʧ��");  
        exit(EXIT_FAILURE);  // ��ֹ���� 
    }  
    strcpy(newNode->name, name); // ����ѧ���������½ڵ� 
    newNode->score = score;  // �����½ڵ��ϵķ���
    newNode->next = *head;  //���½ڵ���뵽����ͷ��
    *head = newNode;  // ����ͷָ��
}  
  
// ����ѧ����Ϣ  
void TraverseList(Student *head) 
{  
	printf("�����Ϣ����: \n");
    Student *current = head;  // ��ͷ�ڵ㿪ʼ����
    while (current) 
	{  
        printf("Name: %s, Score: %d\n", current->name, current->score); 
        current = current->next;  // ��ѧ����Ϣ�ƶ�����һ���ڵ�
    }  
}  
  
// ɾ��ѧ����Ϣ��������ɾ����  
void DeleteStudent(Student **head, char name[]) 
{  
    Student *current = *head;  
    Student *prev = NULL;  //�ȶ���ͷ�ڵ�Ϊ�� 
  
    while (current) 
	{  
        if (strcmp(current->name, name) == 0) // ����ҵ�ƥ���ѧ��
		{  
            if (prev) 
			{  
                prev->next = current->next;  // �������ͷ�ڵ㣬����ǰһ���ڵ��nextָ��
            } 
			else 
			{  
                *head = current->next;  // �����ͷ�ڵ㣬����ͷָ��
            }  
            free(current);  // �ͷŵ�ǰ�ڵ��ڴ�
            return;  
        }  
        prev = current;  // ����ǰһ���ڵ�
        current = current->next;  // ����Ϣ�ƶ�����һ���ڵ�
        printf("��Ϣɾ���ɹ�\n");
    }  
    printf("δ�ҵ���ѧ��\n"); // ���û���ҵ�ƥ���ѧ���������ʾ��Ϣ 
}  
  
// �޸�ѧ����Ϣ���޸ĳɼ���  
void ModifyStudent(Student *head, char name[], int newScore) 
{  
    Student *current = head;  
    while (current) 
	{  
        if (strcmp(current->name, name) == 0) 
		{ // ����ҵ�ƥ���ѧ��  
            current->score = newScore; // ����ѧ������  
            printf("ѧ���������޸�\n");  
            return;  
        }  
        current = current->next; // �ƶ�����һ���ڵ�  
    }  
    printf("δ�ҵ���ѧ��\n"); // ���������Ϣ��ѧ��δ�ҵ�  
}  
  
// ��ѯѧ����Ϣ����������ѯ��  
void QueryStudent(Student *head, char name[]) 
{  
    printf("��ѧ������Ϣ����:\n");  
    Student *current = head;  
    while (current) 
	{  
        if (strcmp(current->name, name) == 0) 
		{    
		// ����ҵ�ƥ���ѧ��  
            printf("Name: %s, Score: %d\n", current->name, current->score);  //��ӡѧ���������ɼ� 
            return;  
        }  
        current = current->next; // �ƶ�����һ���ڵ�  
    }  
    printf("δ�ҵ���ѧ��\n");  
}   

// ����ѧ����Ϣ������ͷ��  
void insertStudent(Student **head, char name[], int score) 
{  
    Student *newNode = (Student *)malloc(sizeof(Student)); // �����µĽڵ��ڴ�  
    if (!newNode) {  
        printf("�ڴ�ڵ����ʧ��\n");  
        exit(EXIT_FAILURE); // ��ֹ����  
    }  
    strcpy(newNode->name, name); // ����ѧ���������½ڵ�  
    newNode->score = score; // �����½ڵ��ϵķ���  
    newNode->next = *head; // ���½ڵ���뵽����ͷ��  
    *head = newNode; // ����ͷָ��  
    printf("ѧ����Ϣ�Ѳ���\n");  
}
  
// ��������в�������  
void SortList(Student **head) 
{  
    Student *sorted = NULL;  // ���ڱ��������򲿷ֵ�ͷָ��  
    Student *current = *head;  // ��ǰ�����Ľڵ�  
    Student *next;  
  
    while (current != NULL) 
	{  
        next = current->next;  // ������һ���ڵ�  
        Student *prev = NULL;  
        Student *tail = sorted;  
  
        // ����ǰ�ڵ���뵽�����򲿷ֵ���ȷλ��  
        while (tail != NULL && tail->score < current->score) 
		{  
            prev = tail;  
            tail = tail->next;  
        }  
  
        current->next = tail;  // ����ڵ�  
        if (prev == NULL) 
		{  
            sorted = current;  // ���뵽�����򲿷ֵĿ�ͷ  
        } else 
		{  
            prev->next = current;  // ���뵽�����򲿷ֵ��м��ĩβ  
        }  
  
        current = next;  // ����������һ���ڵ�  
    }  
  
    *head = sorted;  // ����ͷָ��  
}  

  
// �˵���������  
void Menu() {  
    int choice;  
    char name[50];  
    int score;  
    Student *head = NULL;  
  
    while (1) 
	{
	    printf("\n\n\n\n");
    printf("\t\t---------------------------------------------------\n");
    printf("\t\t||                                               ||\n");
    printf("\t\t||          -���23���籾�Ƴɼ�����ϵͳ-         ||\n");
    printf("\t\t||===============================================||\n");
    printf("\t\t||           -���ߣ�23���籾��2�������-         ||\n");
    printf("\t\t||===============================================||\n");
    printf("\t\t||                                               ||\n");
    printf("\t\t||                                               ||\n");
    printf("\t\t||                1.¼��ѧ����Ϣ                 ||\n");
    printf("\t\t||                2.������Ϣ��                   ||\n");
    printf("\t\t||                3.ɾ��ѧ����Ϣ                 ||\n");
    printf("\t\t||                4.�޸�ѧ���ɼ�                 ||\n");
    printf("\t\t||                5.����ѧ����Ϣ                 ||\n");
    printf("\t\t||                6.����ѧ����Ϣ                 ||\n");
    printf("\t\t||                7.����ѧ���ɼ�                 ||\n");
    printf("\t\t||                  8.�˳�ϵͳ                   ||\n");
    printf("\t\t||                                               ||\n");
    printf("\t\t||                ��ѡ��<1-8>                    ||\n");
    printf("\t\t---------------------------------------------------\n");   
        scanf("%d", &choice);  
  
        switch (choice) {  
            case 1:  
                printf("������ѧ�������ͳɼ���֮������һ���ո������ʹ��Enter��ȷ�ϣ�: ");  
                scanf("%s %d", name, &score);  
                InsertStudent(&head, name, score);  
                break;  
            case 2:  
                TraverseList(head);  
                break;  
            case 3:  
                printf("������Ҫɾ����ѧ������: ");  
                scanf("%s", name);  
                DeleteStudent(&head, name);  
                break;  
            case 4:  
                printf("��������Ҫ�޸ĵ�ѧ���ĳɼ���֮������һ���ո������ʹ��Enter��ȷ�ϣ�:");  
                scanf("%s %d", name, &score);  
                ModifyStudent(head, name, score);  
                break;  
            case 5:  
                printf("�������ѯ��ѧ������: ");  
                scanf("%s", name);  
                QueryStudent(head, name);  
                break;
            case 6:
            	printf("������Ҫ�����ѧ����Ϣ��֮������һ���ո������ʹ��Enter��ȷ�ϣ�: ");
            	scanf("%s %d", name, &score);
            	insertStudent(&head, name, score); 
            	break;
			case 7:
    			printf("���ڽ�������...\n");
    			SortList(&head);
    			printf("������ѧ����Ϣ���£�˳�����ճɼ��ӵ͵��ߣ�:\n");
    			TraverseList(head);
				break; 	  
            case 8:  
                printf("�������˳�...\n");  
                return;  
            default:  
                printf("ѡ�����!\n");  
        }  
    }  
}  
  
int main() 
{  
	Student *head = NULL; // ����ͷָ�벢��ʼ��ΪNULL
	InitList(&head);  //�������� 
    Menu();
	}

