#include <stdio.h>

//�Ƿ����������Ϣ
//#define DEBUGINFO_ENABLED

//������β��С���ӣ���δ������ȱʡΪ����ͷ��С����
#define BORN_IN_ENDOFMONTH

#define DEBUG_ENABLED

//����ֵ����������
#define CNT_DATA_TYPE      long long
//����ֵ��ӡ�ø�ʽ����
#define CNT_FMT            "I64d"

//������Ԫ����
#define TABLECELLWIDTH     "20"
struct CounterInfo{
    //ÿ����������Ӷ���,�������Ӷ���
    //[0] - ������[1] - 1�´�[2] - 2�´�,[3] - 3�¼����ϴ�
    //[4] - �����Ӷ���
    CNT_DATA_TYPE iCntofAge[5];
};
//�õ���month���µ���β��
//������ε����Ӷ����������ܶ���
struct CounterInfo rabbit(int month)
{
#ifdef DEBUGINFO_ENABLED
    printf("Get month:(%d)\n",month);
#endif
    struct CounterInfo cntLastMonth,cntCurMonth;
    if(month <= 0){
        printf("month error...\n");
        cntCurMonth.iCntofAge[0] = 0;
        cntCurMonth.iCntofAge[1] = 0;
        cntCurMonth.iCntofAge[2] = 0;
        cntCurMonth.iCntofAge[3] = 0;
        cntCurMonth.iCntofAge[4] = 0;
    }
    else{
        if(1 == month){
            cntCurMonth.iCntofAge[0] = 0;
            cntCurMonth.iCntofAge[1] = 1;
            cntCurMonth.iCntofAge[2] = 0;
            cntCurMonth.iCntofAge[3] = 0;
            cntCurMonth.iCntofAge[4] = 1;
        }
        else{
            cntLastMonth = rabbit(month-1);
            //3���������� = ����3���������� + ����2����������
            cntCurMonth.iCntofAge[3] = cntLastMonth.iCntofAge[3] + cntLastMonth.iCntofAge[2];
            //2���������� = ����1����������
            cntCurMonth.iCntofAge[2] = cntLastMonth.iCntofAge[1];
#ifdef BORN_IN_ENDOFMONTH
            cntCurMonth.iCntofAge[1] = cntLastMonth.iCntofAge[0];
            //ע����д˳��������Ҫ����ã�����������ͳ��
            //�ȵõ�3�����ϵ����������ٻ��ڸ����õ�������������
            cntCurMonth.iCntofAge[0] = cntCurMonth.iCntofAge[3];
            ////������������ = ��������+��������
            //cntCurMonth.iCntofAge[4] = cntLastMonth.iCntofAge[4] + cntCurMonth.iCntofAge[0];
#else
            //�����ͷ�����ӣ�������������Ϊ������ͷ�յ�3���䣬��β��3�����������
            //����β�����������Ѿ�1���´�
            cntCurMonth.iCntofAge[1] = cntCurMonth.iCntofAge[3];
            cntCurMonth.iCntofAge[0] = 0;
            ////������������ = ��������+�����ѳ���1���´������������
            //cntCurMonth.iCntofAge[4] = cntLastMonth.iCntofAge[4] + cntCurMonth.iCntofAge[1];
#endif
            //������������ = ��������+���µ�����3�����������
            cntCurMonth.iCntofAge[4] = cntLastMonth.iCntofAge[4] + cntCurMonth.iCntofAge[3];
        }
    }

    return cntCurMonth;
}

int main()
{
    int i,j;

    struct CounterInfo cnt;

    printf("%s","Month");

    for(j=0;j<4;j++){
            printf("%" TABLECELLWIDTH CNT_FMT,(CNT_DATA_TYPE)j);
    }
    printf("%"TABLECELLWIDTH"s","Total");
    printf("\n");
    for(i=1;i<=10;i++){
        cnt = rabbit(i);
        printf("%5d",i);
        for(j=0;j<5;j++){
            printf("%" TABLECELLWIDTH CNT_FMT,cnt.iCntofAge[j]);
        }
        printf("\n");

    }

    return 0;
}
