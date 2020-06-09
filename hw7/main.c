#include <stdio.h>
#include <stdlib.h>
//是否输出调试信息
//#define DEBUGINFO_ENABLED
#define N   10
#define min(x,y) (x)<(y)?(x):(y)

//int minfunc(int x,int y)
//{
//    return (x)<(y)?(x):(y);
//}
//
//void test()
//{
//    //min(3,5);
//    3<5?3:5;
//    //min(7,9);
//    7<9?7:9;
//    //重复写1000次，编译后的代码量会+1份*1000，1份是7<9?7:9;全套代码的量
//    minfunc(3,5);
//    minfunc(7,9);
//    //重复写1000次，编译后的代码量会+1份*1000，1份函数地址及参数的量
//
//}

typedef enum { false, true } bool;

struct TwoDimPos{
    int x;
    int y;
};

// 将参数给出的整个二维数组内容输出到屏幕
void Show(int iData[N][N])
{
    int i,j;
    // 左上角空格
    printf("%3c ",' ');
    // 第一行列序号
    for(j=0;j<N;j++){
        printf("%03d ",j);
    }
    printf("\n");
    for(i=0;i<N;i++){
        // 第一列行序号
        printf("%03d ",i);
        // 第i行内容
        for(j=0;j<N;j++){
            printf("%3d ",iData[i][j]);
        }
        printf("\n");
    }
}

// 将内框上一维逻辑数组的下标 转换为 原始二维数组中的下标
// iLogicOneDimPos - 内框上一维逻辑数组的下标
// tdpLeftUp - 内框左上角在二维数组中的下标
// iEdgeLen - 内框各边边长
struct TwoDimPos LogicOneDimPos2TwoDimPos(int iLogicOneDimPos,struct TwoDimPos tdpLeftUp ,int iEdgeLen[4])
{
    struct TwoDimPos tdpRet = {tdpLeftUp.x,tdpLeftUp.y};
    // 顺时针沿着上边、右边、下边、左边走动一格时，X,Y的偏移量
    int offset[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
    int i=0;

    // 算法：
    // 从左上角开始顺时针沿着上、右、下、左边行走，
    // 并找出逻辑一维数组的下标在对应边的位置

    // 只要下标还大于0，则继续往下一条边走
    while(iLogicOneDimPos>0){
        // 逻辑一维数组的下标 - 第i条边的边长
        iLogicOneDimPos -= iEdgeLen[i];

        if(iLogicOneDimPos > 0){
            //如果>0,表示逻辑一维数组的下标在第i条边长之外
            tdpRet.x += offset[i][0]*iEdgeLen[i];
            tdpRet.y += offset[i][1]*iEdgeLen[i];
            i++;
            if(i >= 4){
                printf("error occured at iLogicOneDimPos");
                return tdpRet;
            }
        }
        else{
            //如果<=0,表示逻辑一维数组的下标在第i条边以内
            tdpRet.x += offset[i][0]*(iEdgeLen[i] + iLogicOneDimPos);
            tdpRet.y += offset[i][1]*(iEdgeLen[i] + iLogicOneDimPos);
        }
    }
#ifdef DEBUGINFO_ENABLED
    printf("Get (row col):(%d,%d)\n",tdpRet.y,tdpRet.x);
#endif
    return tdpRet;
}
// 对逻辑一维数组中从begin开始到end结束（包括end）的一系列元素逆序
// iData - 原始二维数组
// begin - 逻辑一维数组逆序的起始下标
// end - 逻辑一维数组逆序的终止下标
// tdpLeftUp - 内框左上角在二维数组中的下标
// iEdgeLen - 内框各边边长

void Reverse(int iData[N][N],int begin,int end,struct TwoDimPos tdpLeftUp,int iEdgeLen[4])
{
    int i,temp,len;
    struct TwoDimPos tdp1,tdp2;
#ifdef DEBUGINFO_ENABLED
    printf("reverse %d-%d\n",begin,end);
#endif
    len = (end-begin+1)/2;
    for(i=0;i<len;i++){
        //将逻辑一维数组的begin+1元素与end-i元素对调位置
        tdp1 = LogicOneDimPos2TwoDimPos(begin+i,tdpLeftUp,iEdgeLen);
        tdp2 = LogicOneDimPos2TwoDimPos(end-i,tdpLeftUp,iEdgeLen);
        temp=iData[tdp1.y][tdp1.x];
        iData[tdp1.y][tdp1.x]=iData[tdp2.y][tdp2.x];
        iData[tdp2.y][tdp2.x]=temp;
    }

}
int main()
{
    static int iData[N][N];
    //初始化原始数据
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            iData[i][j] = i*100+j;
        }
    }
    printf("orignal array\n");
    Show(iData);

    //选取点坐标和旋转量
    int iRowSelect,iColSelect,iDistanceofRotate;
    bool bContinue;

    do{
        printf("please input corner element pos(row col):");
        scanf("%d %d",&iRowSelect,&iColSelect);
        if(iRowSelect>=N || iColSelect>=N || iRowSelect<0 || iColSelect<0){//少考虑了负数
            printf("input out of range\n");
            continue;
        }
        printf("please input distance to Rotate:");
        scanf("%d",&iDistanceofRotate);
        printf("rotate %d while (%d,%d) as corner,result is:\n",iDistanceofRotate,iRowSelect,iColSelect);

        #define min(x,y) (x)<(y)?(x):(y)

        // 获取角点坐标
        struct TwoDimPos tdpLeftUp;
        tdpLeftUp.x = min(iColSelect,N-iColSelect-1);//原本
        tdpLeftUp.x = (iColSelect)<(N-iColSelect-1)?(iColSelect):(N-iColSelect-1);//编译时真正采样的代码

        tdpLeftUp.y = min(iRowSelect,N-iRowSelect-1);

        // 获取框线宽高
        int iWidth = N - tdpLeftUp.x*2;
        int iHeight = N - tdpLeftUp.y*2;

        //框线上元素个数
        int iNumofSelectedElements = 0;
        //保存上、右、下、左边的元素个数
        int iEdgeLen[4];
        if(1 == iHeight){
            iEdgeLen[0] = iWidth-1;
            iEdgeLen[1] = 0;
            iEdgeLen[2] = 0;
            iEdgeLen[3] = 0;
            iNumofSelectedElements = iWidth;
        }
        else{
            if(1 == iWidth){
                iEdgeLen[0] = 0;
                iEdgeLen[1] = iHeight-1;
                iEdgeLen[2] = 0;
                iEdgeLen[3] = 0;
                iNumofSelectedElements = iHeight;
            }
            else{
                //每条边不包括前一条边的终点
                iEdgeLen[0] = iWidth-1;
                iEdgeLen[1] = iHeight-1;
                iEdgeLen[2] = iWidth-1;
                iEdgeLen[3] = iHeight-1;
                iNumofSelectedElements = 2*iWidth + 2*iHeight -4;
            }
        }


        // 旋转量转换到范围[0~iNumofSelectedElements-1]内
        // 算法为：
        // 先求余得到[-iNumofSelectedElements+1 ~ iNumofSelectedElements-1]
        // 再+iNumofSelectedElements保证得到正数
        // 再求余得到[0 iNumofSelectedElements-1]
        iDistanceofRotate = ((iDistanceofRotate%iNumofSelectedElements) + iNumofSelectedElements)%iNumofSelectedElements;
        // 旋转
        // 算法：n个元素，顺时针旋转p个位置的方法是：
        // 1、全部n个元素逆序
        // 2、前n-p个元素逆序
        // 3、后p个元素逆序

        //移动量不为0才真正做后续3步操作
        if(iDistanceofRotate>0){
            // 全部逆序
            Reverse(iData,0,iNumofSelectedElements-1,tdpLeftUp,iEdgeLen);
            // iDistanceofRotate个元素逆序
            Reverse(iData,0,iDistanceofRotate-1,tdpLeftUp,iEdgeLen);
            // 后前iNumofSelectedElements - iDistanceofRotate个元素逆序
            Reverse(iData,iDistanceofRotate,iNumofSelectedElements-1,tdpLeftUp,iEdgeLen);
        }

        Show(iData);
        printf("do you want to continue?(y/n)");
        char chKey;
        bool bValidInput = false;
        do{
            scanf("%c",&chKey);
            if('y' == chKey || 'Y' == chKey){
                bContinue = true;
                bValidInput = true;
            }
            if('n' == chKey || 'N' == chKey){
                bContinue = false;
                bValidInput = true;
            }
        }while(!bValidInput);
    }while(bContinue);


    return 0;
}

//完备测试：单行，单列，4个边角，正负旋转量，超周期旋转量
