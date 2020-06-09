#include <stdio.h>
#include <stdlib.h>
//�Ƿ����������Ϣ
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
//    //�ظ�д1000�Σ������Ĵ�������+1��*1000��1����7<9?7:9;ȫ�״������
//    minfunc(3,5);
//    minfunc(7,9);
//    //�ظ�д1000�Σ������Ĵ�������+1��*1000��1�ݺ�����ַ����������
//
//}

typedef enum { false, true } bool;

struct TwoDimPos{
    int x;
    int y;
};

// ������������������ά���������������Ļ
void Show(int iData[N][N])
{
    int i,j;
    // ���Ͻǿո�
    printf("%3c ",' ');
    // ��һ�������
    for(j=0;j<N;j++){
        printf("%03d ",j);
    }
    printf("\n");
    for(i=0;i<N;i++){
        // ��һ�������
        printf("%03d ",i);
        // ��i������
        for(j=0;j<N;j++){
            printf("%3d ",iData[i][j]);
        }
        printf("\n");
    }
}

// ���ڿ���һά�߼�������±� ת��Ϊ ԭʼ��ά�����е��±�
// iLogicOneDimPos - �ڿ���һά�߼�������±�
// tdpLeftUp - �ڿ����Ͻ��ڶ�ά�����е��±�
// iEdgeLen - �ڿ���߱߳�
struct TwoDimPos LogicOneDimPos2TwoDimPos(int iLogicOneDimPos,struct TwoDimPos tdpLeftUp ,int iEdgeLen[4])
{
    struct TwoDimPos tdpRet = {tdpLeftUp.x,tdpLeftUp.y};
    // ˳ʱ�������ϱߡ��ұߡ��±ߡ�����߶�һ��ʱ��X,Y��ƫ����
    int offset[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
    int i=0;

    // �㷨��
    // �����Ͻǿ�ʼ˳ʱ�������ϡ��ҡ��¡�������ߣ�
    // ���ҳ��߼�һά������±��ڶ�Ӧ�ߵ�λ��

    // ֻҪ�±껹����0�����������һ������
    while(iLogicOneDimPos>0){
        // �߼�һά������±� - ��i���ߵı߳�
        iLogicOneDimPos -= iEdgeLen[i];

        if(iLogicOneDimPos > 0){
            //���>0,��ʾ�߼�һά������±��ڵ�i���߳�֮��
            tdpRet.x += offset[i][0]*iEdgeLen[i];
            tdpRet.y += offset[i][1]*iEdgeLen[i];
            i++;
            if(i >= 4){
                printf("error occured at iLogicOneDimPos");
                return tdpRet;
            }
        }
        else{
            //���<=0,��ʾ�߼�һά������±��ڵ�i��������
            tdpRet.x += offset[i][0]*(iEdgeLen[i] + iLogicOneDimPos);
            tdpRet.y += offset[i][1]*(iEdgeLen[i] + iLogicOneDimPos);
        }
    }
#ifdef DEBUGINFO_ENABLED
    printf("Get (row col):(%d,%d)\n",tdpRet.y,tdpRet.x);
#endif
    return tdpRet;
}
// ���߼�һά�����д�begin��ʼ��end����������end����һϵ��Ԫ������
// iData - ԭʼ��ά����
// begin - �߼�һά�����������ʼ�±�
// end - �߼�һά�����������ֹ�±�
// tdpLeftUp - �ڿ����Ͻ��ڶ�ά�����е��±�
// iEdgeLen - �ڿ���߱߳�

void Reverse(int iData[N][N],int begin,int end,struct TwoDimPos tdpLeftUp,int iEdgeLen[4])
{
    int i,temp,len;
    struct TwoDimPos tdp1,tdp2;
#ifdef DEBUGINFO_ENABLED
    printf("reverse %d-%d\n",begin,end);
#endif
    len = (end-begin+1)/2;
    for(i=0;i<len;i++){
        //���߼�һά�����begin+1Ԫ����end-iԪ�ضԵ�λ��
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
    //��ʼ��ԭʼ����
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            iData[i][j] = i*100+j;
        }
    }
    printf("orignal array\n");
    Show(iData);

    //ѡȡ���������ת��
    int iRowSelect,iColSelect,iDistanceofRotate;
    bool bContinue;

    do{
        printf("please input corner element pos(row col):");
        scanf("%d %d",&iRowSelect,&iColSelect);
        if(iRowSelect>=N || iColSelect>=N || iRowSelect<0 || iColSelect<0){//�ٿ����˸���
            printf("input out of range\n");
            continue;
        }
        printf("please input distance to Rotate:");
        scanf("%d",&iDistanceofRotate);
        printf("rotate %d while (%d,%d) as corner,result is:\n",iDistanceofRotate,iRowSelect,iColSelect);

        #define min(x,y) (x)<(y)?(x):(y)

        // ��ȡ�ǵ�����
        struct TwoDimPos tdpLeftUp;
        tdpLeftUp.x = min(iColSelect,N-iColSelect-1);//ԭ��
        tdpLeftUp.x = (iColSelect)<(N-iColSelect-1)?(iColSelect):(N-iColSelect-1);//����ʱ���������Ĵ���

        tdpLeftUp.y = min(iRowSelect,N-iRowSelect-1);

        // ��ȡ���߿��
        int iWidth = N - tdpLeftUp.x*2;
        int iHeight = N - tdpLeftUp.y*2;

        //������Ԫ�ظ���
        int iNumofSelectedElements = 0;
        //�����ϡ��ҡ��¡���ߵ�Ԫ�ظ���
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
                //ÿ���߲�����ǰһ���ߵ��յ�
                iEdgeLen[0] = iWidth-1;
                iEdgeLen[1] = iHeight-1;
                iEdgeLen[2] = iWidth-1;
                iEdgeLen[3] = iHeight-1;
                iNumofSelectedElements = 2*iWidth + 2*iHeight -4;
            }
        }


        // ��ת��ת������Χ[0~iNumofSelectedElements-1]��
        // �㷨Ϊ��
        // ������õ�[-iNumofSelectedElements+1 ~ iNumofSelectedElements-1]
        // ��+iNumofSelectedElements��֤�õ�����
        // ������õ�[0 iNumofSelectedElements-1]
        iDistanceofRotate = ((iDistanceofRotate%iNumofSelectedElements) + iNumofSelectedElements)%iNumofSelectedElements;
        // ��ת
        // �㷨��n��Ԫ�أ�˳ʱ����תp��λ�õķ����ǣ�
        // 1��ȫ��n��Ԫ������
        // 2��ǰn-p��Ԫ������
        // 3����p��Ԫ������

        //�ƶ�����Ϊ0������������3������
        if(iDistanceofRotate>0){
            // ȫ������
            Reverse(iData,0,iNumofSelectedElements-1,tdpLeftUp,iEdgeLen);
            // iDistanceofRotate��Ԫ������
            Reverse(iData,0,iDistanceofRotate-1,tdpLeftUp,iEdgeLen);
            // ��ǰiNumofSelectedElements - iDistanceofRotate��Ԫ������
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

//�걸���ԣ����У����У�4���߽ǣ�������ת������������ת��
