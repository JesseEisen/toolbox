#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 256
#define MAX(a,b)  ((a)>(b))?(a):(b)


void CreateBadCharTable(const char *t, int *bc){
	int i, len;

	len = strlen(t);
	
	for(i = 0; i< SIZE; i++){
		bc[i]=len;
	}

	for(i = 0; i < len; i++){
		bc[t[i]] = len - 1- i;
	}
}

void CreateSuffix(const char *t , int *suffix){
	int i, j;
	int k, len;

	len = strlen(t);
	suffix[len-1] = len;

	for(i = len - 2; i>=0; i--){
	    j = i;
		while(j > 0 && t[len - 1 - i +j] == t[j])
			j--;

		suffix[i] = j;
	}


}


void CreateGoodSuffixTable(const char *t, int *goodSuff){
	int i, j;
	int suff[SIZE];
    int tlen = strlen(t);

	CreateSuffix(t,suff);

	/*if there are no substring match the good suffix,
	 * move the ently string*/
	for(i = 0; i < tlen; i++){
		goodSuff[i] = tlen;	
	}

	/*if there are substirng match the good suffix and
	 * index begin with 0, rewrite the new move step*/
	j = 0;
	for(i = tlen -1; i>= 0;i--){
		if(suff[i] == i + 1) {//means the first character of t
			for(; j < tlen - 1- i; j++){
				if(goodSuff[j] == tlen){
				       goodSuff[j] = tlen - 1- i;
				}
			}
		}

	}

	for(i = 0; i <= tlen - 2; i++){
		goodSuff[tlen - 1- suff[i]] = tlen - 1- i;
	
	}

}


int BM(const char *s, const char *t){
	int i,j;

	int badChar[SIZE];  //Store the bad character table
	int goodSuff[SIZE]; //store the good suffix table

	int slen, tlen; 
	int ret = 0;


	slen = strlen(s);
	tlen = strlen(t);


	CreateBadCharTable(t,badChar);
	CreateGoodSuffixTable(t,goodSuff);

	/*real searching procedure*/
	j = 0;
	while(j <= slen - tlen){
		for(i = tlen - 1; i >= 0 && t[i] == s[i+j];i--)
			;
		if(i < 0){
			return j + 1;
			//j += goodSuff[0];
			//return ;
		}else{
			j += MAX(badChar[t[i+j]]- tlen + 1 + j, goodSuff[i]);
		
		}
	
	}

	return 0;
}


int main(int argc, char **argv){
	
	printf("At index of %d\n",BM("gooogle", "gle"));

	return 0;

