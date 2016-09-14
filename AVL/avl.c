/*
 * avl.c
 *
 *  Created on: 2016年9月1日
 *      Author: bill
 */

#include<stdio.h>
#include<stdlib.h>
#define EH  0
#define LH  1
#define RH  -1

typedef struct Bitree
{
    int data;
    int bf;                                          //该根结点的平衡度
    struct Bitree * lchild,*rchild;
}Bitree,*BiNtree;

void R_Roate(BiNtree *t);                             //以*t为节点右旋转树
void L_Roate(BiNtree *t);                             //以*t为节点左旋转树
void LeftBalance(BiNtree *t);                         //左旋转以平衡该树
void ReftBalance(BiNtree *t);                         //右旋转以平衡该树
void inserttree(BiNtree *t,int number,int *taller);   //插入节点
void createtree(BiNtree *t);                          //创建平衡二叉树
int SearchBST(BiNtree t,int key,int count);           //查找元素key是否在树Ｔ中并返回查找次数
void LeftBalance_div(BiNtree *p,int *shorter);        //删除结点时左平衡旋转处理
void RightBalance_div(BiNtree *p,int *shorter);       //删除结点时右平衡旋转处理
void Delete(BiNtree q,BiNtree *r,int *shorter);       //删除结点
int DeleteAVL(BiNtree *p,int x,int *shorter);         //平衡二叉树的删除操作

void main()
{
    int input,search,m;
    //int taller=false;
    int count;
    int shorter=0;
    int taller=0;
    BiNtree T,T1,T2;
    //T=(BSTree)malloc(sizeof(BSTNode));
    T=T1=T2=NULL;
    while(1)
    {
        count=1;
        system("cls");
        printf("             ******************************************\n");
        printf(" ╱◥██◣  *1.创建\t2.查找\t3.插入\t4.删除\t5.退出*\n");
        printf("｜田｜田田│ ******************************************\n");
        printf("╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬╬<平衡二叉树 制作V1.0>\n");
        printf("请输入您所需的操作功能:\t");
        scanf("%d",&input);getchar();
        switch(input)
        {
           case 1:
               createtree(&T); break;
           case 2:
               printf("请输入你要查找的关键字");
               scanf("%d",&search); getchar();
               if(SearchBST(T,search,count))
               {
                   count=SearchBST(T,search,count);
                   printf("该二叉树中存在关键字%d，%d,查找成功!\n",search,count);
               }
               else printf("查找失败!\n");
               break;
           case 3:
               printf("请输入你要插入的关键字");
               scanf("%d",&search); getchar();
               inserttree(&T,search,&taller); m = 0;
               //PrintBST(T,m);
               break;
           case 4:
               printf("请输入你要删除的关键字");
               scanf("%d",&search); getchar();
               DeleteAVL(&T,search,&shorter);
              // m=0; PrintBST(T,m);
               break;
           case 5:
               printf("\t\tbyebye!\n");break;
           default:printf("输入错误，请重新选择。");break;
        }
        if(input == 5) break;
        printf("\t\t按任意键继续..."); getchar();
    }
}

//以*t为节点右旋转树
void R_Roate(BiNtree *t)
{
    BiNtree temp;
    temp= (*t)->lchild;
    (*t)->lchild=temp->rchild;
    temp->rchild=*t;
    *t=temp;
}

//以*t为节点左旋转树
void L_Roate(BiNtree *t)
{
    BiNtree temp;
    temp =(*t)->rchild;
    (*t)->rchild=temp->lchild;
    temp->lchild=*t;
    *t=temp;
}

//左旋转以平衡该树
void LeftBalance(BiNtree *t)
{
    BiNtree lc,rd;
    lc=(*t)->lchild;
    switch(lc->bf)
    {
    case LH:                          //新结点插入在*T的左孩子的左子树上，要作单右旋处理
        (*t)->bf = lc->bf = EH;
        R_Roate(t);
        break;
    case RH:                          //新结点插入在*T的左孩子的右子树上，要作双旋处理
        rd = lc->rchild;     //rd指向*T的左孩子的右子树根
        switch(rd->bf)       //修改*T及其左孩子的平衡因子
        {
        case LH:(*t)->bf = RH; lc->bf = EH; break;
        case EH:(*t)->bf = lc->bf = EH; break;
        case RH:(*t)->bf = EH; lc->bf = LH; break;
        }
        rd->bf = EH;
        L_Roate(&(*t)->lchild);    //对*T的左子树作左旋平衡处理
        R_Roate(t);                //对*T作右旋平衡处理
    }
}

//右旋转以平衡该树
void RightBalance(BiNtree *t)
{
    BiNtree rc,ld;
    rc = (*t)->rchild;         //rc指向*T的右子树根结点
    switch(rc->bf)          //检查*T的右子树的平衡度，并作相应平衡处理
    {
    case RH:                //新结点插入在*T的右孩子的右子树上，要作单左旋处理
        (*t)->bf = rc->bf =EH;
        L_Roate(t); break;
    case LH:                //新结点插入在*T的右孩子的左子树上，要作双旋处理
        ld = rc->lchild;    //ld指向*T的右孩子的左子树根
        switch(ld->bf)      //修改*T及其右孩子的平衡因子
        {
        case LH: (*t)->bf = EH; rc->bf = RH; break;
        case EH: (*t)->bf = rc->bf =EH; break;
        case RH: (*t)->bf = LH; rc->bf = EH; break;
        }
        ld->bf = EH;
        R_Roate(&(*t)->rchild);//对*T的右子树作左旋平衡处理
        L_Roate(t);        //对*T作左旋平衡处理
    }
}

//向树中插入节点
void inserttree(BiNtree *t,int number,int *taller)
{
    if(*t==NULL)
    {
        *t=(BiNtree)malloc(sizeof(Bitree));
        (*t)->data=number;
        (*t)->lchild=(*t)->rchild=NULL;
        (*t)->bf=EH;
        *taller=1;
    }
    else
    {
        if(number<(*t)->data)
        {
            inserttree(&(*t)->lchild,number,taller);
            if(*taller)
               switch((*t)->bf)
                {
                    case LH:                  //原本左子树比右子树高，需要作左平衡处理
                        LeftBalance(t);
                        *taller = 0;
                        break;
                    case EH:
                        (*t)->bf = LH;        //原本左子树、右子等高，现因左子树增高而使树增高
                        *taller = 1;
                        break;
                    case RH:                  //原本右子树比左子树高，现左、右子树等高
                        (*t)->bf = EH;
                        *taller = 0;
                        break;
                }//switch(T->bf)
        }
        if(number>(*t)->data)  //应继续在*T的右子树中进行搜索
        {
            inserttree(&(*t)->rchild,number,taller);
            if(taller)                       //已插入到*T的右子树中且右子树“长高”
               switch((*t)->bf)             //检查*T的平衡度
            {
              case LH:                  //原本左子树比右子树高，现左、右子树等高
                (*t)->bf = EH;
                *taller = 0;
                break;
              case EH:                  //原本左子树、右子等高，现因右子树增高而使树增高
                (*t)->bf = RH;
                *taller = 1;
                break;
              case RH:                 //原本右子树比左子树高，需要作右平衡处理
                RightBalance(t);
                *taller = 0;
                break;
            }   //switch(T->bf)
        }
    }
}

//创建平衡二叉树，（注意：以输入－１为二叉树建立的结束）
void createtree(BiNtree *t)
{
    int e,m;
    int taller=0;          //0表示树没有长高，1表示树长高了
    *t= NULL;
    printf("\n请输入关键字(以-1结束建立平衡二叉树):");
    scanf("%d",&e);getchar();
    while(e != -1)
    {
        inserttree(t,e,&taller);
        printf("\n请输入关键字(以-1结束建立平衡二叉树):");
        scanf("%d",&e);getchar();
        taller=0;
    }

}

//查找元素key是否在树Ｔ中并返回查找次数
int SearchBST(BiNtree t,int key,int count)
{
    if(!t) return -1;
    else if(key==t->data) return count;
    else if(key<t->data) return SearchBST(t->lchild,key,count+1);
    else return SearchBST(t->rchild,key,count+1);
}

//删除结点时左平衡旋转处理
void LeftBalance_div(BiNtree *p,int *shorter)
{
    BiNtree  p1,p2;
    if((*p)->bf==1)                     //p结点的左子树高，删除结点后p的bf减1,树变矮
    { (*p)->bf=0; *shorter=1; }
    else if((*p)->bf==0)                //p结点左、右子树等高，删除结点后p的bf减1,树高不变
    { (*p)->bf=-1; *shorter=0; }
    else                             //p结点的右子树高
    {
        p1=(*p)->rchild;                //p1指向p的右子树
        if(p1->bf==0)                //p1结点左、右子树等高,删除结点后p的bf为-2,进行左旋处理，树高不变
        {
            L_Roate(p);
            p1->bf=1; (*p)->bf=-1; *shorter=0;
        }
        else if(p1->bf==-1)          //p1的右子树高，左旋处理后，树变矮
        {
            L_Roate(p);
            p1->bf=(*p)->bf=0; *shorter=1;
        }
        else                         //p1的左子树高,进行双旋处理(先右旋后左旋)，树变矮
        {
            p2=p1->lchild;
            p1->lchild=p2->rchild;
            p2->rchild=p1;
            (*p)->rchild=p2->lchild;
            p2->lchild=*p;
            if(p2->bf==0)
            { (*p)->bf=0; p1->bf=0; }
            else if(p2->bf==-1)
            { (*p)->bf=1;p1->bf=0; }
            else
            { (*p)->bf=0;p1->bf=-1; }
            p2->bf=0; *p=p2; *shorter=1;
        }
    }
}

//删除结点时右平衡旋转处理
void RightBalance_div(BiNtree *p,int *shorter)
{
    BiNtree p1,p2;
    if((*p)->bf==RH)
    { (*p)->bf=EH; *shorter=1; }
    else if((*p)->bf==EH)
    { (*p)->bf=LH; *shorter=0; }
    else
    {
        p1=(*p)->lchild;
        if(p1->bf==EH)
        {
            R_Roate(p);
            p1->bf=RH;
            (*p)->bf=LH;
            *shorter=0;
        }
        else if(p1->bf==LH)
        {
            R_Roate(p);
            p1->bf=(*p)->bf=EH;
            *shorter=1;
        }
        else
        {
            p2=p1->rchild;
            p1->rchild=p2->lchild;
            p2->lchild=p1;
            (*p)->lchild=p2->rchild;
            p2->rchild=*p;
            if(p2->bf==EH)
            { (*p)->bf=EH; p1->bf=EH; }
            else if(p2->bf==LH)
            { (*p)->bf=RH; p1->bf=EH; }
            else
            { (*p)->bf=EH; p1->bf=LH; }
            p2->bf=EH;
            *p=p2;
            *shorter=1;
        }
    }
}

//删除结点
void Delete(BiNtree q,BiNtree *r,int *shorter)
{
    if((*r)->rchild==NULL)
    {
        q->data=(*r)->data;
        q=*r;
        *r=(*r)->lchild;
        free(q);
        *shorter=1;
    }
    else
    {
        Delete(q,&(*r)->rchild,shorter);
        if(*shorter==1)
            RightBalance_div(r,shorter);
    }
}
//平衡二叉树的删除操作
int DeleteAVL(BiNtree *p,int x,int *shorter)
{
    int k;
    BiNtree q;
    if(p==NULL)  { printf("不存在要删除的关键字!!\n"); return 0;}
    else if(x<(*p)->data)//在p的左子树中进行删除
    {
        k=DeleteAVL(&(*p)->lchild,x,shorter);
        if(*shorter==1)
            LeftBalance_div(p,shorter);
        return k;
    }
    else if(x>(*p)->data)//在p的右子树中进行删除
    {
        k=DeleteAVL(&(*p)->rchild,x,shorter);
        if(*shorter==1)
            RightBalance_div(p,shorter);
        return k;
    }
    else
    {
        q=*p;
        if((*p)->rchild==NULL) //右子树空则只需重接它的左子树
        {
            *p=(*p)->lchild;
            free(q);
            *shorter=1; }
        else if((*p)->lchild==NULL)//左子树空则只需重接它的右子树
        {
            *p=(*p)->rchild;
            free(q);
            *shorter=1; }
        else//左右子树均不空
        {
            Delete(q,&q->lchild,shorter);
            if(*shorter==1)
                LeftBalance_div(p,shorter);
            *p=q;
        }
       return 1;
    }
}

