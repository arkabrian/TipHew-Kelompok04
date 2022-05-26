#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct anjing{
	char pemilik[50];
	char nama[50];
	char jenis[50];
	int hari;
};

struct kandangAnjing{
	struct anjing data;
	struct kandangAnjing *next;
};

int countNodeAnjing(struct kandangAnjing *head){
	int count = 0;
	while(head != NULL){
		head = head->next;
		count++;
	}
	return count;
}

void appendAnjing(struct kandangAnjing **head, struct anjing input){
	//Buat Node baru
	struct kandangAnjing *newNode;
	newNode = (struct kandangAnjing*)malloc(sizeof(struct kandangAnjing));
	
	//Linkedlist last memiliki alamat yang sama dengan head
	struct kandangAnjing *last = *head;
	
	//Memasukkan Input ke dalam Node
	(*newNode).data = input;
	(*newNode).next = NULL;
	
	//Jika linkedlist kosong,
	//maka Node baru otomatis jadi Head
	if(*head == NULL){
		*head = newNode;
	}
	//Jika linkedlist tidak kosong
	else{
		//Ngeloop sampe kandangAnjing yang nextnya null (kandangAnjing terakhir)
		while((*last).next != NULL){
			last = (*last).next;
		}
		(*last).next = newNode;
	}
}

void pushAnjing(struct kandangAnjing **head, struct anjing input){
	//Buat Node baru
	struct kandangAnjing *newNode;
	newNode = (struct kandangAnjing*)malloc(sizeof(struct kandangAnjing));
	
	//Input dimasukkan
	(*newNode).data = input;
	
	//Linkedlist awalnya akan dijadiin next,
	//karena headnya jadi data
	(*newNode).next = *head;
	
	//Dicopas ke linkedlist barunya
	*head = newNode;
}

void insertInAnjing(struct kandangAnjing **head, struct anjing input, int pos){
	int i;
	//Buat kandangAnjing baru
	int size = countNodeAnjing(*head);
	struct kandangAnjing *newNode;
	newNode = (struct kandangAnjing*)malloc(sizeof(struct kandangAnjing));
	
	//Masukin input ke kandangAnjing
	(*newNode).data = input;
	
	//Jika posisi tidak sesuai
	if(pos > size+1 || pos < 1){
		printf("Invalid Insertion position\n");
	}
	//Jika posisi = 1, maka akan push
	else if (pos == 1){
		(*newNode).data = input;
		(*newNode).next = *head;
		*head = newNode;
	}
	//Jika posisi antara 1 sampai size + 1
	else{
		//Linkedlist temp memiliki alamat yang sama dengan head
		struct kandangAnjing *temp = *head;
	
		for(i=2; i < pos; i++) {
  			if(temp->next != NULL) {
  		  		temp = temp->next;
  			}
		}
		newNode->next = temp->next;
		temp->next = newNode;
		
	}
}

void deleteHeadAnjing(struct kandangAnjing **head){
	//Head akan ditujukan ke kandangAnjing kedua
	*head = (*head)->next;
}

void deleteTailAnjing(struct kandangAnjing **head){
	struct kandangAnjing *temp = *head;
	
	//Ngambil data kedua terakhir
	while(temp->next->next != NULL){
		temp = temp->next;
	}
	//Ngubah pointer next jadi NULL
	temp->next = NULL;
}

void deleteInAnjing(struct kandangAnjing **head, int pos){
	int size = countNodeAnjing(*head);
	
	//Jika posisi bukan dalam rentang size linkedlist
	if(pos > size || pos < 1){
		printf("Invalid deletion position\n");
	}
	//Jika posisi = 1, maka deleteHead
	else if (pos == 1){
		*head = (*head)->next;
	}
	//Jika posisi 1 sampai size
	else{
		struct kandangAnjing *temp = *head;
		for(int i=2; i< pos; i++) {
			if(temp->next!=NULL) {
    			temp = temp->next;
  			}
		}
		temp->next = temp->next->next;
	}
}

void viewKandangAnjing(struct kandangAnjing **head){
	struct kandangAnjing *temp = *head;
	int i = 1;
	while(temp != NULL){
		printf("%d.\n", i);
		printf("Pemilik  : %s\n", temp->data.pemilik);
		printf("Nama     : %s\n", temp->data.nama);
		printf("Jenis    : %s\n", temp->data.jenis);
		printf("Sisa hari: %d\n", temp->data.hari);
		temp = temp->next;
		i++;
	}
}

void clearKandangAnjing(struct kandangAnjing **head){
	struct kandangAnjing *current = *head;
	struct kandangAnjing *next;
	
	while(current != NULL){
		next = current ->next;
		free(current);
		current = next;
	}
	
	*head = NULL;
	
}
