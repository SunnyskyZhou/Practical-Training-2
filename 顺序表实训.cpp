#define maxsize 100  
#include <stdio.h>  
#include <stdlib.h>  

int data[maxsize];  
int last = -1; // ��ʼ��Ԫ��lastΪ-1����ʾ˳���Ϊ��

int i,j; 
  
// ���뺯������  
void insert() {  
    int num, value;  //valueΪ������ֵ  
    printf("������Ҫ�����λ�ú�Ҫ����������ÿո��������\n");  
    scanf("%d %d", &num, &value);  
    if (last >= maxsize - 1) {  
        printf("˳����������޷�������Ԫ�ء�\n");  
        return;  
    }  
    if (num < 1 || num > last + 1) {  
        printf("����λ����Ч��\n");  
        return;  
    }  
    for (int j = last; j >= num - 1; j--) {  
        data[j + 1] = data[j];  
    }  
    data[num - 1] = value; // ��Ҫ��������ŵ���ȷ��λ��  
    last++; // ����last��ֵ  
}  
  
// ɾ����������  
void delete1(int j) {  
    if (j < 0 || j > last) {  
        printf("��Ч���������޷�ɾ��Ԫ�ء�\n");  
        return;  
    }  
    for (int i = j; i < last; i++) {  
        data[i] = data[i + 1]; // ����Ϊ�մ�����ȷ�ؽ�����Ԫ����ǰ�ƶ�  
    }  
    last--;  
}  
  
// ���Һ�������  
int search(int n) {  
    for (int i = 0; i <= last; i++) {  
        if (data[i] == n) {  
            return i; // ����Ԫ�ص�����  
        }  
    }  
    return -1; // ���δ�ҵ�Ԫ�أ�����-1  
}  
 
//  ����������  
int main() {  
    int n, i, x;  
    printf("��������2�������2023103020122 ��˳���\n");  
    printf("�������ʼԪ�ظ���\n");  
    scanf("%d", &n);  
    printf("������������\n");  
    for (i = 0; i < n; i++) {  
        scanf("%d", &data[i]);  
    }  
    last = n - 1; // �����˸�ֵ��λ�ã������������ݺ����last��Ԫ��  
  
    // �ڲ���֮ǰ�������û�����Ҫ�����λ�ú�ֵ  
    insert();  
  
    // ���������˳���  
    printf("���˳���\n");  
    for (i = 0; i <= last; i++) {  
        printf("%6d", data[i]);  
    }  
    printf("\n");  
  
    // ���Һ�ɾ������  
    printf("������Ҫɾ����λ��\n");  
    scanf("%d", &i);  
    delete1(i - 1); // λ�ü�1����Ϊ�û������λ���Ǵ�1��ʼ�ģ������������Ǵ�0��ʼ��  
  
    // ���ɾ�����˳���  
    printf("���˳���\n");  
    for (i = 0; i <= last; i++) {  
        printf("%6d", data[i]);  
    }  
    printf("\n");  
  
    printf("������Ҫ���ҵ�����\n");  
    scanf("%d", &x);  
    int j = search(x);  
    if (j != -1) {  
        printf("�ҵ�����%d��λ��Ϊ%d\n", x, j + 1); // λ��+1����Ϊ�û�ͨ��ϰ�ߴ�1��ʼ����  
    } else {  
        printf("δ�ҵ�����%d\n", x);  
    }  
  
    return 0;  
}

