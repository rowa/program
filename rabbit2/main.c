#include <stdio.h>
//�Ƿ����������Ϣ
//#define DEBUGINFO_ENABLED

//����ֵ����������
#define CNT_DATA_TYPE      long long
//����ֵ��ӡ�ø�ʽ����
#define CNT_FMT            "I64d"

//������Ԫ����
#define TABLECELLWIDTH     "20"

CNT_DATA_TYPE f3(int m);

CNT_DATA_TYPE f0(int m)
{
#ifdef DEBUGINFO_ENABLED
    printf("Get month:(%d)\n",m);
#endif
    return f3(m);
}
CNT_DATA_TYPE f1(int m)
{
    return 1==m?1:f0(m-1);
}
CNT_DATA_TYPE f2(int m)
{
    return 1==m?0:f1(m-1);
}
long long f3(int m)
{
    return 1==m?0:f3(m-1) + f2(m-1);
}
long long f(int m)
{

    return 1==m?1:(f(m-1)+f3(m));
}


int main()
{
    int i;
    CNT_DATA_TYPE cnt;

    printf("%s","Month");

    printf("%"TABLECELLWIDTH"s","Total");
    printf("\n");
    for(i=1;i<=10;i++){
        cnt = f(i);
        printf("%5d",i);

        printf("%" TABLECELLWIDTH CNT_FMT,cnt);

        printf("\n");

    }
    getchar();

    return 0;
}
