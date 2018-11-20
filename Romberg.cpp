#include<stdio.h>
#include<iostream>
#include<math.h>
struct Romberg
{
	//  四种方式求的的近似值
	float ctf;
	float simp;
	float cotes;
	float rom;
	int n;
	int k;
};
/**
龙贝格（Romberg）求积分公式
**/
float romberg(float c1,float c2){
	return (4*4*4*c2-c1)/(4*4*4-1);
}
/**
复化Cotes公式的方法体
**/
float cotes(float s1,float s2){
	return (4*4*s2-s1)/(4*4-1);
}
/**
复化梯形公式的计算
**/
float CTF(float step){
	    float result = 0.0;
	    float h = (1.0/2.0)/step;
		//  步长由2开始，到10停止
		// 根据复化梯形归公式：
		for(int j=1.0;j<step;j++){
			result=result + 2.0*(sin(j/step)/(j/step));
			
		}
		result = h*(result + sin(1)/1.0+1);
		return result;
}
/**
Simpson公式的计算
**/
float Simpson(float t1,float t2){
	//  利用Sn=4（T2n-Tn/(4-1)）
	return (4*t2-t1)/3.0;
}
int main(int argc, char const *argv[])
{
	Romberg rom[10]={0.0};
	int flag = 0;
	/* code */
	for(int i=0;i<10;i++)
	{
		//  先计算ctf
		rom[flag].ctf = CTF(pow(2,i));
		rom[flag].n = i;
		rom[flag].k = pow(2,i);
		if(i>=1){
			//  计算simpson
			rom[flag].simp = Simpson(rom[i-1].ctf,rom[i].ctf);
		}else rom[flag].simp = 0.0;
		if(i>=2){
			//  计算cotes
			rom[flag].cotes=cotes(rom[i-1].simp,rom[i].simp);
		}else rom[flag].cotes = 0.0;
		if(i>=3){
			//  计算romberg
			rom[flag].rom = romberg(rom[i-1].cotes,rom[i].cotes);
		}
		else rom[flag].rom = 0.0;
		flag++;
	}
	printf("%s\n", "复化梯形公式的近似值        Simpson公式求的近似值          cotes公式求得的近似值        romberg公式求得的近似值            n    k");
	for(int k = 0;k<10;k++){
	     printf("%.7f                   %.7f                      %.7f                    %.7f                          %d    %d\n",rom[k].ctf,rom[k].simp,rom[k].cotes,rom[k].rom,rom[k].n,rom[k].k); 
    }
	return 0;
}