#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 99991

typedef struct element{
    char* key;
    int freq;
}elem;

typedef struct hashtable{
    elem bucket[N];
}table;
table t;
int hash(char*s){
	int hash = 0, length = 0, i=0;
	length = strlen(s);
	for(i=0;i<length;i++){
		hash += (int)(s[i]);
	}
	return hash;
}


int inserthash(table *t, char* s, int* record){
    int index=0, length=0;
    length = strlen(s);
    index = hash(s);
    if(t->bucket[index].key==NULL){
        t->bucket[index].key = (char*)malloc(sizeof(char)*length);
        strcpy(t->bucket[index].key,s);
        t->bucket[index].freq++;
        record[0]++;
    }
    else if(strcmp(s, t->bucket[index].key)==0){
        t->bucket[index].freq++;
    }
    else {
        while(t->bucket[index].freq!=0){
            index++;
            record[1]++;
        }
        t->bucket[index].key = (char*)malloc(sizeof(char)*length);
        strcpy(t->bucket[index].key,s);
        t->bucket[index].freq++;
    }
}

void search(table* t, char *s){
    int index=0, length=0,flag=0;
    char* name;
    length = strlen(s);
    index = hash(s);
    if(t->bucket[index].key!=NULL &&(strcmp(t->bucket[index].key,s)==0)){
		printf("%d\n",t->bucket[index].freq);
	}
	else {
		while(strcmp(t->bucket[index].key, s)!=0){
			index++;
            flag++;
			if(flag==3) {printf("%s not in the table\n",s);
			break;}
		}
		if(index < N-1) printf("%d\n", t->bucket[index].freq);
	}
}

int main(){
	FILE *fp;
	char str[20], check[20];
	str[0] = '\0';
	check[0] = '\0';
	int i=0, tmplen=0, j=0, flag=0,Index=0, record[2]={0};
	float load=0.0;
	//Hashtable H;
	fp = fopen("names.csv","r");
	if(fp==NULL){
		perror("error opening files");
	}
	else{
		printf("names.csv loaded!\n\t");
		while(fgets(str, 20, fp)!=NULL){
			tmplen = strlen(str);
			str[tmplen-1] = 0x0; 
			inserthash(&t, str, record);
	}
	load = record[0]/N;
	printf("Capacity: 99991\n\t");
	printf("Num Terms: %d\n\t", record[0]);
	printf("Collisions: %d\n\t", record[1]);
	printf("Load: %4f\n\t", load);
	printf("Enter term to get frequency or type quit to escape\n");
	while(1){
	scanf("%s", check);
	if(strcmp(check,"quit")==0) {
		printf("end\n");
		return 0;}
	else{
		search(&t, check);
	}
}
	fclose(fp);
	return 0;
}
} 







