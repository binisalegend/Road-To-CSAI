#include<bits/stdc++.h>
using namespace std;
    
typedef struct Node
{
    int StockCode;
    float StockPrice;
    int StockQuantity;
    char BS_Operations;
    int CommissionNo;
    struct Node *next;
}StockInformation;
    
int DelegateType = 0, OrderID = 1;
StockInformation *Buy_first, *Sell_first, *p, *q, *SearchNode;
    
void InitBuyQueue()   //初始化买队列的头节点
{
    Buy_first = (StockInformation *)malloc(sizeof(StockInformation));
    Buy_first->StockCode = -1;
    Buy_first->BS_Operations = ' ';
    Buy_first->StockPrice = -1;
    Buy_first->StockQuantity = -1;
    Buy_first->CommissionNo = 0;
    Buy_first->next = NULL;
}

void InitSellQueue()  //初始化卖操作的头节点
{
    Sell_first = (StockInformation *)malloc(sizeof(StockInformation));
    Sell_first->StockCode = -1;
    Sell_first->BS_Operations = ' ';
    Sell_first->StockPrice = -1;
    Sell_first->StockQuantity = -1;
    Sell_first->CommissionNo = 0;
    Sell_first->next = NULL;
}

void StockApplicationBuy(int Code, float Price, int Quantity, char BS)  //执行买操作
{
    StockInformation *Buy = (StockInformation *)malloc(sizeof(StockInformation));

    Buy->CommissionNo = OrderID;
    printf("orderid: %04d\n", Buy->CommissionNo);

    if (Quantity == 0)
    {
        return;
    }

    Buy->StockCode = Code;
    Buy->StockPrice = Price;
    Buy->StockQuantity = Quantity;
    Buy->BS_Operations = BS;

    SearchNode = Sell_first;
    while (SearchNode->next != NULL)
    {
        if (SearchNode->next->StockCode != Buy->StockCode)   //不是同一款股票，跳过继续遍历
        {
            SearchNode = SearchNode->next;
            continue;
        }
        else
        {
            if (SearchNode->next->StockPrice <= Buy->StockPrice)
            {
                if (SearchNode->next->StockQuantity > Buy->StockQuantity)  //当前想买的量全部买到
                {
                    SearchNode->next->StockQuantity -= Buy->StockQuantity;   //当前卖操作减去买走的量
                    printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (SearchNode->next->StockPrice + Buy->StockPrice) / 2, Buy->StockQuantity, OrderID, SearchNode->next->CommissionNo);
                    return;
                }
                else if(SearchNode->next->StockQuantity == Buy->StockQuantity)
                {
                    printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (SearchNode->next->StockPrice + Buy->StockPrice) / 2, Buy->StockQuantity, OrderID, SearchNode->next->CommissionNo);
                    SearchNode->next = SearchNode->next->next;
                    return;
                }
                else 
                {
                    printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (SearchNode->next->StockPrice + Buy->StockPrice) / 2, SearchNode->next->StockQuantity, OrderID, SearchNode->next->CommissionNo);
                    Buy->StockQuantity -= SearchNode->next->StockQuantity;
                    SearchNode->next->StockQuantity = 0;
                    StockInformation *loc = SearchNode->next;
                    SearchNode->next = loc->next;
                    continue;
                }
            }
            SearchNode = SearchNode->next;
        }
    }

    //排序，寻找应该插入链表的前一个位置
    SearchNode = Buy_first;
    while(SearchNode->next != NULL)
    {
        if (SearchNode->next->StockCode != Buy->StockCode)
        {
            SearchNode = SearchNode->next;
        }
        else
        {
            if (SearchNode->next->StockPrice >= Buy->StockPrice)
            {
                SearchNode = SearchNode->next;
            }
            else
            {
                break;
            }
        }
    }

    Buy->next = SearchNode->next;
    SearchNode->next = Buy;
    return;
}

void StockApplicationSell(int Code, float Price, int Quantity, char BS)
{
    StockInformation *Sell = (StockInformation *)malloc(sizeof(StockInformation));

    Sell->CommissionNo = OrderID;
    printf("orderid: %04d\n", Sell->CommissionNo);
    
    if (Quantity == 0)
    {
        return;
    }

    Sell->StockCode = Code;
    Sell->StockPrice = Price;
    Sell->StockQuantity = Quantity;
    Sell->BS_Operations = BS;

    SearchNode = Buy_first;
    while (SearchNode->next != NULL)
    {
        if (SearchNode->next->StockCode != Sell->StockCode)
        {
            SearchNode = SearchNode->next;
            continue;
        }
        else
        {
            if (SearchNode->next->StockPrice >= Sell->StockPrice)
            {
                if (SearchNode->next->StockQuantity > Sell->StockQuantity)
                {
                    SearchNode->next->StockQuantity -= Sell->StockQuantity;
                    printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (SearchNode->next->StockPrice + Sell->StockPrice) / 2, Sell->StockQuantity, OrderID, SearchNode->next->CommissionNo);
                    return;
                }
                else if (SearchNode->next->StockQuantity == Sell->StockQuantity)
                {
                    printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (SearchNode->next->StockPrice + Sell->StockPrice) / 2, Sell->StockQuantity, OrderID, SearchNode->next->CommissionNo);
                    SearchNode->next = SearchNode->next->next;
                    return;
                }
                else 
                {
                    printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (SearchNode->next->StockPrice + Sell->StockPrice) / 2, SearchNode->next->StockQuantity, OrderID, SearchNode->next->CommissionNo);
                    Sell->StockQuantity -= SearchNode->next->StockQuantity;
                    SearchNode->next->StockQuantity = 0;
                    StockInformation *loc = SearchNode->next;
                    SearchNode->next = loc->next;
                    continue;
                }
            }
            SearchNode = SearchNode->next;
        }
    }

    SearchNode = Sell_first;
    while(SearchNode->next != NULL)
    {
        if (SearchNode->next->StockCode != Sell->StockCode)
        {
            SearchNode = SearchNode->next;
        }
        else
        {
            if (SearchNode->next->StockPrice <= Sell->StockPrice)
            {
                SearchNode = SearchNode->next;
            }
            else
            {
                break;
            }
        }
    }

    Sell->next = SearchNode->next;
    SearchNode->next = Sell;
    return;
}

void StockQuery()  //查询未成交委托操作函数
{
    int code;
    scanf("%d", &code);
    p = Buy_first->next;
    q = Sell_first->next;
    printf("buy orders:\n");
    while (p != NULL)
    {
        if (p->StockCode == code && p->StockQuantity != 0)
        {
            printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", p->CommissionNo, p->StockCode, p->StockPrice, p->StockQuantity, p->BS_Operations);
        }
        p = p->next;
    }
    printf("sell orders:\n");
    while (q != NULL)
    {
        if (q->StockCode == code && q->StockQuantity != 0)
        {
            printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", q->CommissionNo, q->StockCode, q->StockPrice, q->StockQuantity, q->BS_Operations);
        }
        q = q->next;
    }
}

void StockRevoke() //撤销委托操作函数
{
    int RevokeId;
    scanf("%d", &RevokeId);

    SearchNode = Buy_first;
    while (SearchNode->next != NULL)
    {
        if (SearchNode->next->CommissionNo == RevokeId)
        {
            printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", SearchNode->next->CommissionNo, SearchNode->next->StockCode, SearchNode->next->StockPrice, SearchNode->next->StockQuantity, SearchNode->next->BS_Operations);
            StockInformation *loc = SearchNode->next;
            SearchNode->next = loc->next;
            return;
        }
        SearchNode = SearchNode->next;
    }

    SearchNode = Sell_first;
    while (SearchNode->next != NULL)
    {
        if (SearchNode->next->CommissionNo == RevokeId)
        {
            printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", SearchNode->next->CommissionNo, SearchNode->next->StockCode, SearchNode->next->StockPrice, SearchNode->next->StockQuantity, SearchNode->next->BS_Operations);
            StockInformation *loc = SearchNode->next;
            SearchNode->next = loc->next;
            return;
        }
        SearchNode = SearchNode->next;
    }
    printf("not found\n");
    return;    
}

int main()
{
    scanf("%d", &DelegateType);
    InitBuyQueue();
    InitSellQueue();

    while (DelegateType != 0)
    {
        int code = 0, quantity = -1;
        float price = -1;
        char BS = ' ';
        switch (DelegateType)
        {
            case 1:
                scanf("%d %f %d %c", &code, &price, &quantity, &BS);
                if (BS == 'b')
                {
                    StockApplicationBuy(code, price, quantity, BS);
                }
                else if (BS == 's')
                {
                    StockApplicationSell(code, price, quantity, BS);
                }
                OrderID++;
                break;
            case 2:
                StockQuery();
                break;
            case 3:
                StockRevoke();
                break;
        }
        scanf("%d", &DelegateType);
    }
    system("pause");
    return 0;
}