#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct
{
    char CH;//字符
    int weight;//权值
    int parent, lchild, rchild;//双亲，左孩子，右孩子
}DATA;//树的结构体
typedef struct
{
    char code[30];
    int cnt;
}codetype;
void Createtree(DATA *hfmTree, int N)//构建哈夫曼树，传数组hfmTree和字符个数N做参数
{
    int i, j, min, cmin;
    int m, c;
    hfmTree[0].CH = ' ';//空格用0号单元直接存（特殊处理）
    hfmTree[0].parent = hfmTree[0].lchild = hfmTree[0].rchild = -1;
    scanf("%d", &hfmTree[0].weight);//输入空格的权值
    /*输入A~Z的权值初始化哈夫曼树*/
    for (i = 1; i<N; i++)
    {
        hfmTree[i].CH = 'A' + i - 1;
        hfmTree[i].parent = hfmTree[i].lchild = hfmTree[i].rchild = -1;
        scanf("%d", &hfmTree[i].weight);
    }
    /*构建哈夫曼的过程注意 找到的最小值作为新根的左孩子，次小值作为右孩子*/
    for (i = N; i<2 * N - 1; i++)
    {
        min = 99999;//最小值
        cmin = 99999;//次小值
        m = 0; c = 0;//记录最小值和次小值的下标
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
        hfmTree[i].CH = ' ';//方便整体输出加个字符空格
        hfmTree[i].lchild = m;
        hfmTree[i].rchild = c;
        hfmTree[m].parent = i;
        hfmTree[c].parent = i;
        hfmTree[i].parent = -1;//新结点的双亲没有为-1

    }
}
void Hfmcode(DATA *hfmTree, codetype *codeFile, int N)//哈夫曼编码
{
    int i, p, c;
    codetype S;
    for (i = 0; i<N; i++)//对N的字符进行编码
    {
        c = i;//意思是将树中的第一个字符的下标给c暂存
        p = hfmTree[c].parent;//找得到c下标字符的双亲（是地址）给p暂存
        S.cnt = N;//把cnt的值初始化为N，后续再用数组(S->code[])存字符的编码时,倒着存
        S.code[N] = '\0';
        while (p != -1)//要将第i个字符从它自身找到它的双亲为止
        {
            if (hfmTree[p].lchild == c)//第i个字符是双亲p的左孩子，S.code[]中存‘0’；
                S.code[--S.cnt] = '0';
            else//否则存‘1’
                S.code[--S.cnt] = '1';
            c = p;
            p = hfmTree[c].parent;
        }

        codeFile[i] = S;//第i个字符的编码存入codeFile
    }

}
void Decode(DATA *hfmTree,char *ToBeTran, int N)//解码过程
{
    int i,ct=0;
    char ch;
    scanf("%c", &ch);
    i = 2 * N - 2;//根结点的小标（地址）为2*N-2
    while (ch!='#')//#结束后不再翻译
    {
        if (ch == '0')//‘0’判断左走
            i = hfmTree[i].lchild;
        else if (ch == '1')//‘1’判断右走
            i = hfmTree[i].rchild;
        if (hfmTree[i].lchild == -1 || hfmTree[i].rchild == -1)//从根结点一直找到叶子
        {
            ToBeTran[ct++] = hfmTree[i].CH;
            i = 2 * N - 2;//译完一段编码后置为头结点继续翻译
        }
        scanf("%c", &ch);
    }
    if ((hfmTree[i].lchild != -1 || hfmTree[i].rchild != -1) && i != 2 * N - 2)
        printf("编码有误！");
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
    codetype *codeFile;//定义一个存编码信息的数组，大小动态分配
    printf("字符集大小:");
    scanf("%d", &N);//字符个数
    ToBeTran = (char *)malloc(sizeof(char) * 40);
    codeFile = (codetype *)malloc(sizeof(codetype)*N);//给codeFile数组分配空间
    hfmTree = (DATA *)malloc(sizeof(DATA)*(2 * N - 1));//哈夫曼树结点个数
    printf("输入空格和A~Z字母的频度：\n");
    Createtree(hfmTree, N);//建树
    Hfmcode(hfmTree, codeFile, N);//编码
    /*for (i = 0; i<N; i++)
    {
        printf("%c字符的编码：", hfmTree[i].CH);
        printf("%s", codeFile[i].code + codeFile[i].cnt);
        printf("\n");
    }*/
    scanf("%c", &c);//接收回车符的不然会被gets(str)这句录入
    printf("请输入需要编码的字符串：\n");
    gets(str);
    printf("\n");
    printf("该字符串编码为：\n");
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == ' ')
            printf("%s", codeFile[0].code + codeFile[0].cnt);
        else
            printf("%s", codeFile[str[i] - 'A' + 1].code + codeFile[str[i] - 'A' + 1].cnt);//由于是倒着存的所以正着输出时要找到起始点
    }
    printf("\n\n");
    printf("输入需要译文的编码（以#号结束）：\n");
    Decode(hfmTree, ToBeTran, N);
    printf("\n");
    printf("编码译文为：\n");
    printf("%s", ToBeTran);
    return 0;
}
