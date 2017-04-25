#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<sys/types.h>


#define d 256

/** 
 * @Brief  return the index of the character t in string s
 * 
 * @Param s origin string
 * @Param t single character
 * 
 * @Returns  the index, start at 1  
 */
int Str_CharIndex(const char *s, char t){
	assert(s == NULL);
	
	const char *p = s;
	int ret = 0;
	int len = strlen(s);

	while(*p++ != t)
	{
		ret++;
	}

	if(ret >= len)
	{
		return 0;	
	}

	return ret + 1;
}



/** 
 * @Brief  return the index of the string t in string s
 * if not contain, return 0
 * 
 * @Param s source string
 * @Param t target string
 * 
 * @Returns   the index , start at 1 or 0 if not find
 */
int Str_StrIndex(const char *s, char *t){
	if(t == NULL)
		return 0;

	int slen = strlen(s);
	int tlen = strlen(t);
	int i, j;

	for(i = 0; i < slen-tlen; i++){
		for(j = 0; j < tlen; j++)
		{
			if(s[i+j] != t[j]){
				break;
			}
		}

		if(j == tlen)
			return i+1;
	}

	return 0;
}


int RK_Search(const char *s, char *t, int q){
	int slen = strlen(s);
	int tlen = strlen(t);

	int i, j;
	int hashS = 0;
	int hashT = 0;
	int h = 1;

	/*This step is reserved for calculating new target hash value */
	for(i = 0; i< (tlen-1); i++)
		h = (h * d) % q;

	for(i = 0; i< tlen; i++){
		hashT = (d*hashT + t[i])%q;
		hashS = (d*hashS + s[i])%q;
	}

	for(i = 0; i <= (slen-tlen); i++){
		if(hashT == hashS){
		    for(j = 0; j< tlen; j++){
				if(s[i+j] != t[j])
					break;
			}
			if(j == tlen)
				return i + 1;
		}

		/*recalculate hash value of the source string*/
		if(i < (slen-tlen)){
		   hashS = (d *(hashS - s[i]*h) + s[i+tlen]) % q;

		   if(hashS < 0)
			   hashS = (hashS + q);
		}
	}

	return 0;
}


int Str_StrIndexKR(const char *s, char *t){
	int q = 101;
	int ret = 0;

	ret = RK_Search(s,t,q);

	return ret;
}



char *mystrstr(const char *s, const char *t){
	if(t == NULL)
		return (char *)s;

	size_t slen, tlen;
	slen = strlen(s);
	tlen = strlen(t);

	while(slen >= tlen){
		slen--;
		if(!memcmp(s,t,tlen)){
		      return (char *)s;
		}
		s++;
	}

	return NULL;
}

char * left_trim(char *s){
	int len = strlen(s);
	char *cur = s;

	while(*cur && isspace(*cur)){
		cur++;
		--len;
	}

	if(s != cur) memmove(s, cur, len+1);
}

char * right_trim(char *s){
	int len = strlen(s);
	char *cur = s + len - 1;
	short is_space;

	while(cur != s && (isspace(*cur) || *cur == '\n'))
		--cur;

	is_space = (isspace(*cur) || *cur == '\n');
	cur[is_space ? 0 : 1] = '\0';

	return s;
}



char * strtrim(char *s){
	s = left_trim(s);
	s = right_trim(s);
	
	return s;
}

