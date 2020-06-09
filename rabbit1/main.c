#include <stdio.h>

//是否输出调试信息
//#define DEBUGINFO_ENABLED

//是在月尾生小兔子，若未定义则缺省为在月头生小兔子
#define BORN_IN_ENDOFMONTH

#define DEBUG_ENABLED

//计数值用数据类型
#define CNT_DATA_TYPE      long long
//计数值打印用格式化符
#define CNT_FMT            "I64d"

//输出表格单元格宽度
#define TABLECELLWIDTH     "20"
struct CounterInfo{
    //每个月龄的兔子对数,及总兔子对数
    //[0] - 新生，[1] - 1月大，[2] - 2月大,[3] - 3月及以上大
    //[4] - 总兔子对数
    CNT_DATA_TYPE iCntofAge[5];
};
//得到第month个月的月尾，
//各年龄段的兔子对数和兔子总对数
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
            //3月龄兔子数 = 上月3月龄兔子数 + 上月2月龄兔子数
            cntCurMonth.iCntofAge[3] = cntLastMonth.iCntofAge[3] + cntLastMonth.iCntofAge[2];
            //2月龄兔子数 = 上月1月龄兔子数
            cntCurMonth.iCntofAge[2] = cntLastMonth.iCntofAge[1];
#ifdef BORN_IN_ENDOFMONTH
            cntCurMonth.iCntofAge[1] = cntLastMonth.iCntofAge[0];
            //注意书写顺序，新兔子要最后获得，先生兔子再统计
            //先得到3月以上的兔子数，再基于该数得到本月新兔子数
            cntCurMonth.iCntofAge[0] = cntCurMonth.iCntofAge[3];
            ////本月兔子总数 = 上月总数+本月新生
            //cntCurMonth.iCntofAge[4] = cntLastMonth.iCntofAge[4] + cntCurMonth.iCntofAge[0];
#else
            //如果月头生兔子，则新生兔子数为本月月头刚到3月龄，月尾足3月龄的兔子数
            //到月尾，新生兔子已经1个月大
            cntCurMonth.iCntofAge[1] = cntCurMonth.iCntofAge[3];
            cntCurMonth.iCntofAge[0] = 0;
            ////本月兔子总数 = 上月总数+本月已长到1个月大的新生兔子数
            //cntCurMonth.iCntofAge[4] = cntLastMonth.iCntofAge[4] + cntCurMonth.iCntofAge[1];
#endif
            //本月兔子总数 = 上月总数+本月底已足3月龄的兔子数
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
