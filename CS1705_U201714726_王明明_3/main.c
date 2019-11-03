#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RetMenu -1
#define N 10
#define MaxS 65535
//�����������ʽ,�����е���Ʒ���б��
typedef struct
{
	char ProductName[10];//��Ʒ����
	char Discount;//�ۿ�
	short ProductPrice;//����
	short SellingPrice;//�ۼ�
	short StockNumber;//��������
	short SaleNumber;//������Ŀ
	short rec;//�Ƽ���
}PRO;
extern  void Search_Pro(PRO *ProductArray, char*pro, int len, int *flag);
extern  void Recommend_All_Index(PRO *ProductArray);
extern  void Rank_Recom_Score(PRO *ProductArray);
void ShowMenu(int AUTH);
void DividingLine();
void PrintfString(char* s);
void PrintfNumber(short x);
int Search(PRO *ProductArray);
void ShowProLogin(PRO ProductArray);
void ShowProUnlogin(PRO pro);
void ShowAllProduct(PRO *ProductArray);
void Assignment(PRO *ProductArray,int n, char*ProductName,  char Discount, short ProductPrice, short SellingPrice, short StockNumber, short SaleNumber, short rec);
void EditProduct(PRO *pro);

int main()
{
	int i;
	int AUTH = 0;//��ʼAUTH==0,δ��¼
	PRO ProductArray[N];//��Ʒ����
	char InputInformation[100];//������Ϣ�����С,���Ա���������û�������
	char Username[] = "WANGM";//���е��û���
	char Password[] = "TEST";//���е�����
	char op;
	//�����е���Ʒ���и�ֵ����,����ʼ��
	Assignment(ProductArray,0,"PEN", 10, 35, 56, 150, 25, 43);
	Assignment(ProductArray,1, "BOOK", 9, 12, 50, 25, 5, 75);
	for (i = 2; i <= N - 2; i++){
		Assignment(ProductArray,i, "TEMPVALUE", 8, 15, 20, 30, 2, 41);
	}
	Assignment(ProductArray,N-1, "BAG", 10, 35, 55, 500, 27, 39);
	while (1)
	{
		printf("*****THE SHOP IS SHOP_ONE*****\n");//��ӡ�̵�����
		DividingLine();//�ָ���
		printf("PLEASE INPUT YOUR NAME:\n");//��ʾ�����û���
		gets_s(InputInformation, 6);//����gets_s���÷�,CSDN���
		if (!InputInformation[0]) AUTH = 0;//�س������
		else if (!InputInformation[1] && InputInformation[0] == 'q') return 0;//����Ϊq�����
		else if (strcmp(InputInformation, Username) != 0)//���ȱȽ������ַ����Ĵ�С�Ƿ����,�����ֱ����ʾ����
		{
			printf("The Name Is Wrong!");
			continue;//����Ҫ�������û���
		}
		else
		{
			printf("The Name Is Right!\n");
			printf("PLEASE INPUT YOUR PASSWORD:\n");//��ʾ��������
			scanf_s("%s", InputInformation, 5);//���ƶ�ȡ5���ֽ�,�����÷����ղ���CSDN
			if (!strcmp(InputInformation, Password)){
			AUTH = 1;//�ȽϵĽ�����,���½�ɹ�
			printf("Landed Successfully!\n");
			} 
			else {//�ȽϽ�����������ʾ�������
				printf("The PWD Is Wrong!\n");
				continue;//������������
			}
		}
		while (1)
		{
			ShowMenu(AUTH);//����ShowMenu����,����ΪAUTH,����½״̬
			printf("Please input your selection[1-%d]:", AUTH ? 6 : 2);
			rewind(stdin);//���ڽ��ļ�ָ������ָ���ļ��Ŀ�ͷ,ͬʱ������ļ�����صĴ����eof���
			op = getchar();
			rewind(stdin);
			if (op == '\n') break;//������س�,������һ��,Ҫ�������û���
			if (op > '2'&&AUTH != 1)
			{
				//���δ��¼��������ֲ����ϣ���ô������ʾ����
				printf("The number is wrong,please input again!\n");
				continue;//��������ѡ��
			}
			switch (op)
			{
			case '1':
			{
				int num;
				num=Search(ProductArray);//�鿴��Ʒ��Ϣ�ĵ�һ������,�ҵ�����Ʒ
				if (num > 0)//���ݷ���ֵ,�ж��Ƿ��ҵ�
				{
					if (AUTH == 1)//��ʱΪ��½״̬,��δ��¼״̬��ʾ�������в�ͬ
						ShowProLogin(ProductArray[num - 1]);
					else ShowProUnlogin(ProductArray[num - 1]);
				}
				break;
			}
			case '2':
			{
				int num;
				if (!AUTH)
					return 0;//��Ӧδ��¼״̬ʱ���˳�,����¼״̬�µ�����6
				else
				{
					num=Search(ProductArray);
					if(num>0)
					EditProduct(&ProductArray[num-1]);
					break;
				}
			}
			case '3':
			{
				Recommend_All_Index(ProductArray);//�����е���Ʒ�����Ƽ��ȵļ���
				break;
			}
			case '4':
			{
				Rank_Recom_Score(ProductArray);//��������
				break;
			}
			case '5':
			{
				ShowAllProduct(ProductArray);//��ӡ������Ʒ����Ϣ
				//Display_All_Good(ProductArray, PrintfString, PrintfNumber,showPRO_ASM);
				break;
			}
			case '6':
				return 0;//�˳�����
			default:
				printf("Input Error,please input again!\n");
				continue;
			}
		}

	}

	return 0;
}

void ShowMenu(int AUTH)
{
	DividingLine();
	if (AUTH)//��½״̬��ӡ���еĲ˵�
	{
		printf("1==Query product information\n");     
		printf("2==Modify product information\n");
		printf("3==Calculate the recommendation\n");
		printf("4==Calculate the recommendation rank\n");  
		printf("5==Output all commodity information\n");
		printf("6==Exit(Input Enter to return)\n");
	}
	
	else//δ��¼״̬����ӡһ���ֲ˵�
	{
		printf("1==Query product information\n");
		printf("2==Exit(Input Enter to return)\n");
	}
	DividingLine();//�ָ���
}
void DividingLine()//�ָ���,Ϊ������
{
	printf("**********************************************************\n");
}
void PrintfString(char*s)
{
	printf("%s", s);//��Ҫ������ӡ��Ʒ������
}
void PrintfNumber(short x)
{
	printf("%d", x);//��ӡ��Ʒ��������Ϣ
}
void Assignment(PRO *ProductArray,int n, char*ProductName, char Discount, short ProductPrice, short SellingPrice, short StockNumber, short SaleNumber, short rec)
{
	//�ú�����������ֵ
	strcpy_s(ProductArray[n].ProductName,10,ProductName);
	ProductArray[n].Discount = Discount;
	ProductArray[n].ProductPrice = ProductPrice;
	ProductArray[n].SellingPrice = SellingPrice;
	ProductArray[n].StockNumber = StockNumber;
	ProductArray[n].SaleNumber = SaleNumber;
	ProductArray[n].rec = rec;
}
int Search(PRO *ProductArray)//������Ʒ�ĺ���
{
	int flag = -1;//������flag��ʾδ�ҵ�����Ʒ
	char pro[12];
	int len;
	while (1)
	{
		printf("Please Input The Good You Want!\n");
		rewind(stdin);//���ڽ��ļ�ָ������ָ���ļ��Ŀ�ͷ,ͬʱ������ļ�����صĴ����eof���
		gets_s(pro, 11);
		for (len = 0; pro[len]; len++);
		if (!pro[0]) return RetMenu;
		Search_Pro(ProductArray, pro, len, &flag);
		if (flag == 0)
		{
			//��Ʒδ�ҵ�
			printf("Product has not been found!\n");
			DividingLine();
		}
		else break;
	}
	return flag;
}

void EditProduct(PRO *pro)
{
	//�����༭��Ʒ��Ϣ
	char InputInformation[6];//�������Ʒ��Ϣ
	short x;
	while (1)//����ѭ����ģʽ,ÿ���޸�һ������ 
	{
		printf("Discount:%d->",pro->Discount);
		gets_s(InputInformation, 6);
		if (!InputInformation[0]) break;//�������س�,���޸���һ������
		else if (ChectInput(InputInformation, &x,10))
		{
			pro->Discount = x;//�����޸��ۿۼ۸�
			break;
		}
	}
	while (1)
	{
		printf("PURCHASE:%d->", pro->ProductPrice);//ͬ��һ��ģ��
		gets_s(InputInformation, 6);
		if (!InputInformation[0]) break;
		else if (ChectInput(InputInformation, &x, MaxS))
		{
			pro->ProductPrice = x;
			break;
		}
	}
	while (1)
	{
		printf("SALE PRICE:%d->", pro->SellingPrice);
		gets_s(InputInformation, 6);
		if (!InputInformation[0]) break;
		else if (ChectInput(InputInformation, &x, MaxS))
		{
			pro->SellingPrice = x;
			break;
		}
	}
	while (1)
	{
		printf("STOCK NUMBER:%d->", pro->StockNumber);
		gets_s(InputInformation, 6);
		if (!InputInformation[0]) break;
		else if (ChectInput(InputInformation, &x, MaxS))
		{
			pro->StockNumber = x;
			break;
		}
	}
}
int ChectInput(char *input, short *x, int max)
{
	//�޸���Ϣʱ�����ж������Ƿ�Ϸ�
	int i;
	short temp=0,s=0;
	for (i = 0; input[i]; i++)
	{
		if (input[i] >= '0'&&input[i] <= '9')
		{
			temp = input[i] - '0';
			s *= 10;
			s += temp;
		}
		else return 0;
	}
	if (s <= max)
	{
		*x = s;
		return 1;
	}
	else return 0;
}
void ShowAllProduct(PRO *ProductArray)
{
	//���������Ʒ����Ϣ
	int i = 0;
	int j = 1;
	for (i = 0; i < N; i++)
	{
		if (!i)
		{
			printf("1:\n");
		}
		else 
		{
			if (ProductArray[i].rec < ProductArray[i - 1].rec)
				j++;
			printf("%d:\n", j);
		}
		ShowProLogin(ProductArray[i]);
	}
}

void ShowProLogin(PRO pro)
{
	//��½״̬�´�ӡ����
	printf("%s\n", pro.ProductName);
	printf("%hd,%hd,%hd,", pro.Discount, pro.ProductPrice, pro.SellingPrice);
	printf("%hd,%hd,%hd\n", pro.StockNumber, pro.SaleNumber, pro.rec);
}
void ShowProUnlogin(PRO pro)
{
	//δ��½״̬�´�ӡ����
	printf("%s\n", pro.ProductName);
	printf("%hd,%hd,%hd,", pro.Discount, pro.ProductPrice, pro.SellingPrice);
	printf("%hd,%hd,", pro.StockNumber, pro.SaleNumber);
	//�Ƽ��ȵ����
	if (pro.rec > 100) putchar('A');
	else if(pro.rec > 50)putchar('B');
	else if(pro.rec>10) putchar('C');
	else putchar('F');
	printf("\n");
}
