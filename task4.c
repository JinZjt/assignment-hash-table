#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUCKETCOUNT 99991

struct character{
	char* PersonID;
	char* Deposition;
	char* Surname;
	char* Forename;
	char* Age;
	char* PersonType;
	char* Gender;
	char* Nationality;
	char* Religion;
	char* Occupation;
};
typedef struct hashEntry{
	struct character info;
	char* key;
	struct hashEntry *next;
}entry;
typedef struct hashTable{
	entry bucket[BUCKETCOUNT];
}table;

table t;

void initHashTable(table* t){
	int i;
	if(t==NULL) return;
	for(i=0;i<BUCKETCOUNT;i++){
		t->bucket[i].info.PersonID =NULL;
		t->bucket[i].info.Deposition =NULL;
		t->bucket[i].info.Surname =NULL;
		t->bucket[i].info.Forename =NULL;
		t->bucket[i].info.Age =NULL;
		t->bucket[i].info.PersonType =NULL;
		t->bucket[i].info.Gender =NULL;
		t->bucket[i].info.Nationality =NULL;
		t->bucket[i].info.Religion =NULL;
		t->bucket[i].info.Occupation =NULL; 
		t->bucket[i].key = NULL;
		t->bucket[i].next = NULL;
	}
}

int hash1(char* s){
	int hash = 0, length = 0,i=0;
	length = strlen(s);
	for(i=0;i<length;i++){
		hash+=(int)(s[i])*i;
	}
	return hash%BUCKETCOUNT;
}

int hash2(char* s){
	int hash = 0, length = 0,i=0;
	length = strlen(s);
	for(i=0;i<length;i++){
		hash+=(int)(s[i])*i;
	}
	return 1+hash%99971;
}

int insertentry(table* t, struct character list,int* result){
	int index=0,length=0,i=0, temp=0;
	entry* tail;
	entry* start;
	tail = (entry*)malloc(sizeof(entry));
	start = (entry*)malloc(sizeof(entry));
	index = (hash1(list.Surname)+i*hash2(list.Surname))%BUCKETCOUNT;
	//printf("%d\n",index);
	if(t->bucket[index].key==NULL){
		t->bucket[index].info = list;
		length = strlen(list.Surname);
		t->bucket[index].key = (char*)malloc(sizeof(char));
		strcpy(t->bucket[index].key, list.Surname);
		result[0] +=1;
	}
	else if(t->bucket[index].key!=NULL&&(strcmp(t->bucket[index].key, list.Surname)!=0)){
		while(t->bucket[index].key!=NULL){
			i+=1;
			index=(hash1(list.Surname)+i*hash2(list.Surname))%BUCKETCOUNT;
			//index=(index+i*i)%BUCKETCOUNT;
			result[1]+=1;
		}
		t->bucket[index].info = list;
		length = strlen(list.Surname);
		t->bucket[index].key = (char*)malloc(sizeof(char));
		strcpy(t->bucket[index].key, list.Surname);
	}
	else if(strcmp(t->bucket[index].key, list.Surname)==0&&t->bucket[index].key!=NULL){
		start = &t->bucket[index];
		while(start->next!=NULL){
			start = start->next;
		}
		tail->info = list;
		start->next = tail;
		tail->next = NULL; 
	}
	return *result;
}
void search(char* s, table* t){
	int value=0,i=1;
	value = hash1(s);
	entry* start;
	start = (entry*)malloc(sizeof(entry));
	if(strcmp(t->bucket[value].key, s)==0){
		start= &t->bucket[value];
		while(start!=NULL){
			printf("%s  %s  %s\n", start->info.PersonID, start->info.Surname, start->info.Forename);
			start = start->next;
		}
	}
	else {
		while(strcmp(t->bucket[value].key, s)!=0){
			value = (hash1(s)+i*hash2(s))%BUCKETCOUNT;
			i++;
			if(i==10) {
				printf("not found\n");
				return;
			} 
		}
		printf("%s  %s  %s\n", start->info.PersonID, start->info.Surname, start->info.Forename);
	}
}
int main(){
	FILE* fp;
	int length = 0, count = 0, quotation=0, i=0,result[2]={0},res=0;
	float load=0.0;
	char temp[200], str[200], check[20],c;
	check[0]='\0';
	temp[0]='\0';
	str[0] = '\0';
	struct character pok;
	initHashTable(&t); 
	fp = fopen("truncated.csv", "r");
	fgets(str,190,fp);
	while((c=fgetc(fp))!=EOF){
		if(c=='"') {++quotation;
		continue;}
		++length;
		if (c==',' && quotation%2!=0 ) temp[length-1] = c;
		if (c!=','&& c!='\n') temp[length-1] = c;
		if (c==',' && count==0){
			pok.PersonID = (char*)malloc(sizeof(char)*length);
			strcpy(pok.PersonID, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		} 
		else if (c==',' && count==1) {
			pok.Deposition = (char*)malloc(sizeof(char)*length);
			strcpy(pok.Deposition, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==2){
			pok.Surname = (char*)malloc(sizeof(char)*length);
			strcpy(pok.Surname, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==3){
			pok.Forename = (char*)malloc(sizeof(char)*length);
			strcpy(pok.Forename, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==4){
			pok.Age = (char*)malloc(sizeof(char)*length);
			strcpy(pok.Age, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==5){
			pok.PersonType = (char*)malloc(sizeof(char)*length);
			strcpy(pok.PersonType, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==6){
			pok.Gender = (char*)malloc(sizeof(char)*length);
			strcpy(pok.Gender, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==7){
			pok.Nationality = (char*)malloc(sizeof(char)*length);
			strcpy(pok.Nationality, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c==',' && count==8){
			pok.Religion = (char*)malloc(sizeof(char)*length);
			strcpy(pok.Religion, temp);
			length = 0;
			memset(temp,0,200);
			++count;
		}
		else if (c=='\n' && count==9){
			pok.Occupation = (char*)malloc(sizeof(char)*length);
			strcpy(pok.Occupation, temp);
			length = 0;
			memset(temp,0,200);
			count = 0;
			insertentry(&t, pok, result);
		}
}
	load = result[1]/99991;
	printf("capacity: 99991\n");
	printf("Num Terms: %d\n", result[0]+1);
	printf("collisions: %d\n",result[1]);
	printf("Load: %4f\n", load);
	printf("Enter term to get frequency or type quit to escape\n");
	while(1){
	scanf("%s", check);
	if(strcmp(check,"quit")==0) {
		printf("end\n");
		return 0;}
	else{
		printf("PersonID    Surname    Forename\n");
		search(check, &t);
	}
}
	fclose(fp);
	return 0;
}

