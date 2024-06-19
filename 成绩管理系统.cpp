#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
  
// 定义学生成绩信息结构体  
typedef struct Student 
{  
    char name[100];  
    int score;  
    struct Student *next;  
} Student;  
  
// 初始化线性表（单链表）函数  
void InitList(Student **head) 
{  
    *head = NULL; // 将头指针置为空，表示初始链表为空
	printf("单链表已初始化完毕\n"); 
}  
  
// 插入学生信息  
void InsertStudent(Student **head, char name[], int score) 
{  
    Student *newNode = (Student *)malloc(sizeof(Student)); // 分配新的节点内存 
    if (!newNode) 
	{  
        printf("内存节点分配失败");  
        exit(EXIT_FAILURE);  // 终止程序 
    }  
    strcpy(newNode->name, name); // 复制学生姓名到新节点 
    newNode->score = score;  // 设置新节点上的分数
    newNode->next = *head;  //将新节点插入到链表头部
    *head = newNode;  // 更新头指针
}  
  
// 遍历学生信息  
void TraverseList(Student *head) 
{  
	printf("输出信息表结果: \n");
    Student *current = head;  // 从头节点开始遍历
    while (current) 
	{  
        printf("Name: %s, Score: %d\n", current->name, current->score); 
        current = current->next;  // 将学生信息移动到下一个节点
    }  
}  
  
// 删除学生信息（按姓名删除）  
void DeleteStudent(Student **head, char name[]) 
{  
    Student *current = *head;  
    Student *prev = NULL;  //先定义头节点为空 
  
    while (current) 
	{  
        if (strcmp(current->name, name) == 0) // 如果找到匹配的学生
		{  
            if (prev) 
			{  
                prev->next = current->next;  // 如果不是头节点，更新前一个节点的next指针
            } 
			else 
			{  
                *head = current->next;  // 如果是头节点，更新头指针
            }  
            free(current);  // 释放当前节点内存
            return;  
        }  
        prev = current;  // 覆盖前一个节点
        current = current->next;  // 将信息移动到下一个节点
        printf("信息删除成功\n");
    }  
    printf("未找到该学生\n"); // 如果没有找到匹配的学生，输出提示信息 
}  
  
// 修改学生信息（修改成绩）  
void ModifyStudent(Student *head, char name[], int newScore) 
{  
    Student *current = head;  
    while (current) 
	{  
        if (strcmp(current->name, name) == 0) 
		{ // 如果找到匹配的学生  
            current->score = newScore; // 更新学生分数  
            printf("学生分数已修改\n");  
            return;  
        }  
        current = current->next; // 移动到下一个节点  
    }  
    printf("未找到该学生\n"); // 否则输出信息：学生未找到  
}  
  
// 查询学生信息（按姓名查询）  
void QueryStudent(Student *head, char name[]) 
{  
    printf("该学生的信息如下:\n");  
    Student *current = head;  
    while (current) 
	{  
        if (strcmp(current->name, name) == 0) 
		{    
		// 如果找到匹配的学生  
            printf("Name: %s, Score: %d\n", current->name, current->score);  //打印学生姓名及成绩 
            return;  
        }  
        current = current->next; // 移动到下一个节点  
    }  
    printf("未找到该学生\n");  
}   

// 插入学生信息到链表头部  
void insertStudent(Student **head, char name[], int score) 
{  
    Student *newNode = (Student *)malloc(sizeof(Student)); // 分配新的节点内存  
    if (!newNode) {  
        printf("内存节点分配失败\n");  
        exit(EXIT_FAILURE); // 终止程序  
    }  
    strcpy(newNode->name, name); // 复制学生姓名到新节点  
    newNode->score = score; // 设置新节点上的分数  
    newNode->next = *head; // 将新节点插入到链表头部  
    *head = newNode; // 更新头指针  
    printf("学生信息已插入\n");  
}
  
// 对链表进行插入排序  
void SortList(Student **head) 
{  
    Student *sorted = NULL;  // 用于保存已排序部分的头指针  
    Student *current = *head;  // 当前遍历的节点  
    Student *next;  
  
    while (current != NULL) 
	{  
        next = current->next;  // 保存下一个节点  
        Student *prev = NULL;  
        Student *tail = sorted;  
  
        // 将当前节点插入到已排序部分的正确位置  
        while (tail != NULL && tail->score < current->score) 
		{  
            prev = tail;  
            tail = tail->next;  
        }  
  
        current->next = tail;  // 插入节点  
        if (prev == NULL) 
		{  
            sorted = current;  // 插入到已排序部分的开头  
        } else 
		{  
            prev->next = current;  // 插入到已排序部分的中间或末尾  
        }  
  
        current = next;  // 继续遍历下一个节点  
    }  
  
    *head = sorted;  // 更新头指针  
}  

  
// 菜单函数部分  
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
    printf("\t\t||          -广科23网络本科成绩管理系统-         ||\n");
    printf("\t\t||===============================================||\n");
    printf("\t\t||           -作者：23网络本科2班周润德-         ||\n");
    printf("\t\t||===============================================||\n");
    printf("\t\t||                                               ||\n");
    printf("\t\t||                                               ||\n");
    printf("\t\t||                1.录入学生信息                 ||\n");
    printf("\t\t||                2.遍历信息表                   ||\n");
    printf("\t\t||                3.删除学生信息                 ||\n");
    printf("\t\t||                4.修改学生成绩                 ||\n");
    printf("\t\t||                5.搜索学生信息                 ||\n");
    printf("\t\t||                6.插入学生信息                 ||\n");
    printf("\t\t||                7.排序学生成绩                 ||\n");
    printf("\t\t||                  8.退出系统                   ||\n");
    printf("\t\t||                                               ||\n");
    printf("\t\t||                请选择<1-8>                    ||\n");
    printf("\t\t---------------------------------------------------\n");   
        scanf("%d", &choice);  
  
        switch (choice) {  
            case 1:  
                printf("请输入学生姓名和成绩（之间请用一个空格隔开，使用Enter键确认）: ");  
                scanf("%s %d", name, &score);  
                InsertStudent(&head, name, score);  
                break;  
            case 2:  
                TraverseList(head);  
                break;  
            case 3:  
                printf("请输入要删除的学生姓名: ");  
                scanf("%s", name);  
                DeleteStudent(&head, name);  
                break;  
            case 4:  
                printf("请输入需要修改的学生的成绩（之间请用一个空格隔开，使用Enter键确认）:");  
                scanf("%s %d", name, &score);  
                ModifyStudent(head, name, score);  
                break;  
            case 5:  
                printf("请输入查询的学生姓名: ");  
                scanf("%s", name);  
                QueryStudent(head, name);  
                break;
            case 6:
            	printf("请输入要插入的学生信息（之间请用一个空格隔开，使用Enter键确认）: ");
            	scanf("%s %d", name, &score);
            	insertStudent(&head, name, score); 
            	break;
			case 7:
    			printf("正在进行排序...\n");
    			SortList(&head);
    			printf("排序后的学生信息如下（顺序依照成绩从低到高）:\n");
    			TraverseList(head);
				break; 	  
            case 8:  
                printf("程序已退出...\n");  
                return;  
            default:  
                printf("选项不存在!\n");  
        }  
    }  
}  
  
int main() 
{  
	Student *head = NULL; // 定义头指针并初始化为NULL
	InitList(&head);  //创建链表 
    Menu();
	}

