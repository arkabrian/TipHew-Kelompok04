#include <stdio.h>
#include <stdlib.h>

struct kucing{
	char pemilik[50];
	char nama[50];
	char jenis[50];
	int hari;
};

struct kandangKucing{
	struct kucing data;
	struct kandangKucing *next;
};

int countNodeKucing(struct kandangKucing *head){
	int count = 0;
	while(head != NULL){
		head = head->next;
		count++;
	}
	return count;
}

void appendKucing(struct kandangKucing **head, struct kucing input){
	//Buat Node baru
	struct kandangKucing *newNode;
	newNode = (struct kandangKucing*)malloc(sizeof(struct kandangKucing));
	
	//Linkedlist last memiliki alamat yang sama dengan head
	struct kandangKucing *last = *head;
	
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
		//Ngeloop sampe kandangKucing yang nextnya null (kandangKucing terakhir)
		while((*last).next != NULL){
			last = (*last).next;
		}
		(*last).next = newNode;
	}
}

void pushKucing(struct kandangKucing **head, struct kucing input){
	//Buat Node baru
	struct kandangKucing *newNode;
	newNode = (struct kandangKucing*)malloc(sizeof(struct kandangKucing));
	
	//Input dimasukkan
	(*newNode).data = input;
	
	//Linkedlist awalnya akan dijadiin next,
	//karena headnya jadi data
	(*newNode).next = *head;
	
	//Dicopas ke linkedlist barunya
	*head = newNode;
}

void insertInKucing(struct kandangKucing **head, struct kucing input, int pos){
	int i;
	//Buat kandangKucing baru
	int size = countNodeKucing(*head);
	struct kandangKucing *newNode;
	newNode = (struct kandangKucing*)malloc(sizeof(struct kandangKucing));
	
	//Masukin input ke kandangKucing
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
		struct kandangKucing *temp = *head;
	
		for(i=2; i < pos; i++) {
  			if(temp->next != NULL) {
  		  		temp = temp->next;
  			}
		}
		newNode->next = temp->next;
		temp->next = newNode;
		
	}
}

void deleteHeadKucing(struct kandangKucing **head){
	//Head akan ditujukan ke kandangKucing kedua
	*head = (*head)->next;
}

void deleteTailKucing(struct kandangKucing **head){
	struct kandangKucing *temp = *head;
	
	//Ngambil data kedua terakhir
	while(temp->next->next != NULL){
		temp = temp->next;
	}
	//Ngubah pointer next jadi NULL
	temp->next = NULL;
}

void deleteInKucing(struct kandangKucing **head, int pos){
	int size = countNodeKucing(*head);
	
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
		struct kandangKucing *temp = *head;
		for(int i=2; i< pos; i++) {
			if(temp->next!=NULL) {
    			temp = temp->next;
  			}
		}
		temp->next = temp->next->next;
	}
	
}

void viewKandangKucing(struct kandangKucing **head){
	struct kandangKucing *temp = *head;
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

void clearKandangKucing(struct kandangKucing **head){
	struct kandangKucing *current = *head;
	struct kandangKucing *next;
	
	while(current != NULL){
		next = current ->next;
		free(current);
		current = next;
	}
	
	*head = NULL;
	
}