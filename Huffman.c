#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct
{
    char CH;//�ַ�
    int weight;//Ȩֵ
    int parent, lchild, rchild;//˫�ף����ӣ��Һ���
}DATA;//���Ľṹ��
typedef struct
{
    char code[30];
    int cnt;
}codetype;
void Createtree(DATA *hfmTree, int N)//��������������������hfmTree���ַ�����N������
{
    int i, j, min, cmin;
    int m, c;
    hfmTree[0].CH = ' ';//�ո���0�ŵ�Ԫֱ�Ӵ棨���⴦��
    hfmTree[0].parent = hfmTree[0].lchild = hfmTree[0].rchild = -1;
    scanf("%d", &hfmTree[0].weight);//����ո��Ȩֵ
    /*����A~Z��Ȩֵ��ʼ����������*/
    for (i = 1; i<N; i++)
    {
        hfmTree[i].CH = 'A' + i - 1;
        hfmTree[i].parent = hfmTree[i].lchild = hfmTree[i].rchild = -1;
        scanf("%d", &hfmTree[i].weight);
    }
    /*�����������Ĺ���ע�� �ҵ�����Сֵ��Ϊ�¸������ӣ���Сֵ��Ϊ�Һ���*/
    for (i = N; i<2 * N - 1; i++)
    {
        min = 99999;//��Сֵ
        cmin = 99999;//��Сֵ
        m = 0; c = 0;//��¼��Сֵ�ʹ�Сֵ���±�
        for (j = 0; j<i; j++)
        {
            if (hfmTree[j].parent == -1)
                if (hfmTree[j].weight<min)
                {
                    c = m;
                    cmin = min;
                    min = hfmTree[j].weight;
                    m = j;
                }
                else if (hfmTree[j].weight<cmin)
                {
                    cmin = hfmTree[j].weight;
                    c = j;
                }

        }
        hfmTree[i].weight = min + cmin;//hfmTree[m].weight+hfmTree[c].weight;
        hfmTree[i].CH = ' ';//������������Ӹ��ַ��ո�
        hfmTree[i].lchild = m;
        hfmTree[i].rchild = c;
        hfmTree[m].parent = i;
        hfmTree[c].parent = i;
        hfmTree[i].parent = -1;//�½���˫��û��Ϊ-1

    }
}
void Hfmcode(DATA *hfmTree, codetype *codeFile, int N)//����������
{
    int i, p, c;
    codetype S;
    for (i = 0; i<N; i++)//��N���ַ����б���
    {
        c = i;//��˼�ǽ����еĵ�һ���ַ����±��c�ݴ�
        p = hfmTree[c].parent;//�ҵõ�c�±��ַ���˫�ף��ǵ�ַ����p�ݴ�
        S.cnt = N;//��cnt��ֵ��ʼ��ΪN��������������(S->code[])���ַ��ı���ʱ,���Ŵ�
        S.code[N] = '\0';
        while (p != -1)//Ҫ����i���ַ����������ҵ�����˫��Ϊֹ
        {
            if (hfmTree[p].lchild == c)//��i���ַ���˫��p�����ӣ�S.code[]�д桮0����
                S.code[--S.cnt] = '0';
            else//����桮1��
                S.code[--S.cnt] = '1';
            c = p;
            p = hfmTree[c].parent;
        }

        codeFile[i] = S;//��i���ַ��ı������codeFile
    }

}
void Decode(DATA *hfmTree,char *ToBeTran, int N)//�������
{
    int i,ct=0;
    char ch;
    scanf("%c", &ch);
    i = 2 * N - 2;//������С�꣨��ַ��Ϊ2*N-2
    while (ch!='#')//#�������ٷ���
    {
        if (ch == '0')//��0���ж�����
            i = hfmTree[i].lchild;
        else if (ch == '1')//��1���ж�����
            i = hfmTree[i].rchild;
        if (hfmTree[i].lchild == -1 || hfmTree[i].rchild == -1)//�Ӹ����һֱ�ҵ�Ҷ��
        {
            ToBeTran[ct++] = hfmTree[i].CH;
            i = 2 * N - 2;//����һ�α������Ϊͷ����������
        }
        scanf("%c", &ch);
    }
    if ((hfmTree[i].lchild != -1 || hfmTree[i].rchild != -1) && i != 2 * N - 2)
        printf("��������");
    ToBeTran[ct] = '\0';

}
int main()
{
    int N;
    int i, j;
    //char str[]="THIS PROGRAM IS MY FAVORITE";
    char str[200];
    char *ToBeTran,c;
    DATA *hfmTree;
    codetype *codeFile;//����һ���������Ϣ�����飬��С��̬����
    printf("�ַ�����С:");
    scanf("%d", &N);//�ַ�����
    ToBeTran = (char *)malloc(sizeof(char) * 40);
    codeFile = (codetype *)malloc(sizeof(codetype)*N);//��codeFile�������ռ�
    hfmTree = (DATA *)malloc(sizeof(DATA)*(2 * N - 1));//��������������
    printf("����ո��A~Z��ĸ��Ƶ�ȣ�\n");
    Createtree(hfmTree, N);//����
    Hfmcode(hfmTree, codeFile, N);//����
    /*for (i = 0; i<N; i++)
    {
        printf("%c�ַ��ı��룺", hfmTree[i].CH);
        printf("%s", codeFile[i].code + codeFile[i].cnt);
        printf("\n");
    }*/
    scanf("%c", &c);//���ջس����Ĳ�Ȼ�ᱻgets(str)���¼��
    printf("��������Ҫ������ַ�����\n");
    gets(str);
    printf("\n");
    printf("���ַ�������Ϊ��\n");
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == ' ')
            printf("%s", codeFile[0].code + codeFile[0].cnt);
        else
            printf("%s", codeFile[str[i] - 'A' + 1].code + codeFile[str[i] - 'A' + 1].cnt);//�����ǵ��Ŵ�������������ʱҪ�ҵ���ʼ��
    }
    printf("\n\n");
    printf("������Ҫ���ĵı��루��#�Ž�������\n");
    Decode(hfmTree, ToBeTran, N);
    printf("\n");
    printf("��������Ϊ��\n");
    printf("%s", ToBeTran);
    return 0;
}
