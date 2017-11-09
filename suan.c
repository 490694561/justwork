#include<stdio.h>
int encode_miwen(int *s,unsigned __int8 *m);
int cmp_miwen(unsigned __int8 *m,char *mima_1,char *mima_2,char *mima_3);
int main(void)
{
	long long int number;
	unsigned int i,i1,qian;
	int j,j1,x;
//	char i1;
	int s[50];
	char mima_1[7]="$******";
	char mima_2[65]="*************$******$*********$$**$********$********************$";
	char mima_3[48]="*****$****$****$******$******$*****$****$***$***";
	unsigned __int8 m[]={51,103,179,17,30,207,16,87};
//	unsigned __int8 m[]={51,103,51,82,158,143,16,87};
	for(number=4294967295ll;number>=0;number--)
	{
		j=0x1D8;j1=0;
		i=number;
//		i=4294967039ll;
		printf("%u\n",i);
		do
		{
			i1=i;
			i>>=2;
			s[j1]=i1&3;
			j1++;
			j+=4;
		}
		while(j<0x218);
		encode_miwen(s,m);
		qian=cmp_miwen(m,mima_1,mima_2,mima_3);
//		for(x=0;x<=15;x++)
//		printf("%d ",s[x]);
//		printf("\n");
		if(qian==16)
		{
			for(x=0;x<=7;x++)
			printf("%02X ",m[x]);
			printf("\n");
			printf("money:$%d\n",qian);
		}
	}
//	system("pause");
	return 0;
}
int encode_miwen(int *s,unsigned __int8 *m)
{
	unsigned int v0,v1,v2,v6,v7,v9;
	unsigned __int8 v3;
//	unsigned int v3;
	unsigned __int8 v4,v5,v10;
	v0=0;
	do
	{
		v1=s[v0];
		if(v1!=0)
		{
			v2=v0&3;
			v9=2*(v0>>2);
			v10=m[v9];
			v3=((v10<<2*v2)%0x100)>>6;
			v4=((m[v9+1]<<2*v2)%0x100)>>6;
			do
			{
				v5 = v3 & 1;
				v3 = v4 & 254 | ((v3>>1)%0x100);
				v4 = v5|2*(v4&1);
				--v1;
			}
			while(v1!=0);
			v6 = 2*((v0 >> 2)%0x100);
			v7 = 2 * (3 - v2);
			m[v9] = v10&~((3 << v7)%0x100);
			m[v6+1] &= ~((3<<v7)%0x100);
			m[v6] |= (v3<<v7)%0x100;
			m[v6+1] |= (v4<<v7)%0x100;
		}
		++v0;
	}
	while(v0<16);
	return 0;
}
int cmp_miwen(unsigned __int8 *m,char *mima_1,char *mima_2,char *mima_3)
{
	int v0,v1,v2,v3,v5,v8,v9,money;
	unsigned int v4,v6,result;
	v0=0;
	money=0;
	v1=money;
	v9=0;
	v8=0;
	do
	{
		v2=0;
		v3=0;
		do
		{
			v4=(m[v0]%0x100)>>v3++;
			v2+=v4&1;
		}
		while(v3<8);
		if(*(&mima_3[v8] + v2)==36)
		{
			++v1;
		}
		v0=v9+1;
		v8+=6;
		++v9;
	}
	while(v8<48);
	v5=7;
	v6=m[0]%0x100;
	result=m[1]%0x100;
	money=v1;
	do
	{
		if(mima_2[8*((((unsigned __int8)m[7]>>v5)&1)+(((unsigned __int8)m[6]>>v5)&1)+(((unsigned __int8)m[5]>>v5)&1)+(((unsigned __int8)m[4]>>v5)&1)+(((unsigned __int8)m[3]>>v5)&1)+(((unsigned __int8)m[2]>>v5)&1)+((result>>v5)&1)+((v6>>v5)&1))-v5]==36)
		{
			++v1;
		}
		--v5;
		result=m[1];
		v6=m[0];
	}
	while(v5>=0);
	money=v1;
//	printf("%d\n",money);
	return money;
}
