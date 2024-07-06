#define maxsize 100  
#include <stdio.h>  
#include <stdlib.h>  

int data[maxsize];  
int last = -1; // 初始化元素last为-1，表示顺序表为空

int i,j; 
  
// 插入函数部分  
void insert() {  
    int num, value;  //value为个数总值  
    printf("请输入要插入的位置和要插入的数（用空格隔开）：\n");  
    scanf("%d %d", &num, &value);  
    if (last >= maxsize - 1) {  
        printf("顺序表已满，无法插入新元素。\n");  
        return;  
    }  
    if (num < 1 || num > last + 1) {  
        printf("插入位置无效！\n");  
        return;  
    }  
    for (int j = last; j >= num - 1; j--) {  
        data[j + 1] = data[j];  
    }  
    data[num - 1] = value; // 将要插入的数放到正确的位置  
    last++; // 更新last的值  
}  
  
// 删除函数部分  
void delete1(int j) {  
    if (j < 0 || j > last) {  
        printf("无效的索引，无法删除元素。\n");  
        return;  
    }  
    for (int i = j; i < last; i++) {  
        data[i] = data[i + 1]; // 修正为空错误，正确地将后续元素向前移动  
    }  
    last--;  
}  
  
// 查找函数部分  
int search(int n) {  
    for (int i = 0; i <= last; i++) {  
        if (data[i] == n) {  
            return i; // 返回元素的索引  
        }  
    }  
    return -1; // 如果未找到元素，返回-1  
}  
 
//  主函数部分  
int main() {  
    int n, i, x;  
    printf("这是网工2班周润德2023103020122 的顺序表\n");  
    printf("请输入初始元素个数\n");  
    scanf("%d", &n);  
    printf("请输入表的数字\n");  
    for (i = 0; i < n; i++) {  
        scanf("%d", &data[i]);  
    }  
    last = n - 1; // 修正了赋值的位置，在输入完数据后更新last的元素  
  
    // 在插入之前，先让用户输入要插入的位置和值  
    insert();  
  
    // 输出插入后的顺序表  
    printf("输出顺序表\n");  
    for (i = 0; i <= last; i++) {  
        printf("%6d", data[i]);  
    }  
    printf("\n");  
  
    // 查找和删除操作  
    printf("请输入要删除的位置\n");  
    scanf("%d", &i);  
    delete1(i - 1); // 位置减1是因为用户输入的位置是从1开始的，而数组索引是从0开始的  
  
    // 输出删除后的顺序表  
    printf("输出顺序表\n");  
    for (i = 0; i <= last; i++) {  
        printf("%6d", data[i]);  
    }  
    printf("\n");  
  
    printf("请输入要查找的数字\n");  
    scanf("%d", &x);  
    int j = search(x);  
    if (j != -1) {  
        printf("找到数字%d，位置为%d\n", x, j + 1); // 位置+1是因为用户通常习惯从1开始计数  
    } else {  
        printf("未找到数字%d\n", x);  
    }  
  
    return 0;  
}

