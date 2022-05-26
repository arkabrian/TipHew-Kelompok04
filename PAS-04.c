#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <omp.h>

#include "kandangKucing.h"
#include "kandangAnjing.h"

/* Program : TipHew 
	kelompok 4 : Arka Brian Dewara(2106731421), Daffa Anis Fahrizi (2106731365)
	*/
struct kandangKucing *catCage = NULL; //LinkedList untuk kucing
struct kandangAnjing *dogCage = NULL; //LinkedList untuk anjing

void addTxtToLinkedListAnjing(struct kandangAnjing **head){
	if(access("kandangAnjing.txt", F_OK) == 0){ //Ngecek apakah file ada atau engga
		struct anjing dog;
		
		char temp[100];
		char *token;
		
		FILE *kandang;
		kandang = fopen("kandangAnjing.txt", "r");
	
		while(fgets(temp, sizeof(temp), kandang)){
			token = strtok(temp, ","); //Username
			strcpy(dog.pemilik, token); //Username
			
			token = strtok(NULL, ","); //hari
			dog.hari = atoi(token); //hari
			
			token = strtok(NULL, ","); //Nama
			strcpy(dog.nama, token);//Nama
			
			token = strtok(NULL, ","); //Jenis
			strcpy(dog.jenis, token); //Jenis
			appendAnjing(&dogCage, dog); //Masukin struct ke linked list
		}
		fclose(kandang);
	}
	else return; // Klo gaada lgsg keluar dari function
}
void addTxtToLinkedListKucing(struct kandangKucing **head){
	if(access("kandangKucing.txt", F_OK) == 0){ //Ngecek apakah file ada atau engga
		struct kucing cat;
		
		char temp[100];
		char *token;
		
		FILE *kandang;
		kandang = fopen("kandangKucing.txt", "r");
		
		while(fgets(temp, sizeof(temp), kandang)){
			token = strtok(temp, ","); //Username
			strcpy(cat.pemilik, token); //Username
			
			token = strtok(NULL, ","); //hari
			cat.hari = atoi(token); //hari
			
			token = strtok(NULL, ","); //Nama
			strcpy(cat.nama, token);//Nama
			
			token = strtok(NULL, ","); //Jenis
			strcpy(cat.jenis, token); //Jenis
			appendKucing(&catCage, cat); //Masukin struct ke linked list
		}
		
		fclose(kandang);
	}
	else return; // Klo gaada lgsg keluar dari function
}

void nextDayAnjing(struct kandangAnjing **head){
	if(access("kandangAnjing.txt", F_OK) == 0){
		struct anjing dog;
		
		char temp[100];
		char *token;
		
		FILE *kandang;
		kandang = fopen("kandangAnjing.txt", "r");
		
		FILE *tempKandang;
		tempKandang = fopen("tempKandangAnjing.txt", "w+");
		
		while(fgets(temp, sizeof(temp), kandang)){
			token = strtok(temp, ","); //Username
			strcpy(dog.pemilik, token); //Username
			
			token = strtok(NULL, ","); //hari
			dog.hari = atoi(token) - 1; //sisa hari akan decrement 
			
			token = strtok(NULL, ","); //Nama
			strcpy(dog.nama, token);//Nama
			
			token = strtok(NULL, ","); //Jenis
			strcpy(dog.jenis, token); //Jenis
			fprintf(tempKandang, "%s,%d,%s,%s,\n", dog.pemilik, dog.hari, dog.nama, dog.jenis); 
		}
		fclose(kandang);
		remove("kandangAnjing.txt");
		fclose(tempKandang);
		rename("tempKandangAnjing.txt", "kandangAnjing.txt");
		
		struct kandangAnjing *tempL = *head;
		while(tempL != NULL){
			(tempL->data.hari)--; //sisa hari akan decrement 
			tempL = tempL->next;
		}
		
	} 
	else printf("Kandang anjing kosong!\n");
}
void nextDayKucing(struct kandangKucing **head){
	if(access("kandangKucing.txt", F_OK) == 0){
		struct kucing cat;
		
		char temp[100];
		char *token;
		
		FILE *kandang;
		kandang = fopen("kandangKucing.txt", "r");
		
		FILE *tempKandang;
		tempKandang = fopen("tempKandangKucing.txt", "w+");
		
		while(fgets(temp, sizeof(temp), kandang)){
			token = strtok(temp, ","); //Username
			strcpy(cat.pemilik, token); //Username
			
			token = strtok(NULL, ","); //hari
			cat.hari = atoi(token) - 1; //sisa hari akan decrement 
			
			token = strtok(NULL, ","); //Nama
			strcpy(cat.nama, token);//Nama
			
			token = strtok(NULL, ","); //Jenis
			strcpy(cat.jenis, token); //Jenis
			fprintf(tempKandang, "%s,%d,%s,%s,\n", cat.pemilik, cat.hari, cat.nama, cat.jenis);
		}
		fclose(kandang);
		remove("kandangKucing.txt");
		fclose(tempKandang);
		rename("tempKandangKucing.txt", "kandangKucing.txt");
		
		struct kandangKucing *tempL = *head;
		while(tempL != NULL){
			(tempL->data.hari)--; //sisa hari akan decrement 
			tempL = tempL->next;
		}
		
	} 
	else printf("Kandang kucing kosong!\n");
}

void extendAnjing(struct kandangAnjing **head, char username[], int hari){
	struct anjing dog;
	char temp[100];
	char *token;
	
	FILE *kandang;
	FILE *tempKandang;
	kandang = fopen("kandangAnjing.txt", "r");
	tempKandang = fopen("tempKandangAnjing.txt", "w+");
	
	while(fgets(temp, sizeof(temp), kandang)){
		token = strtok(temp, ","); //Username
		if(strcmp(token, username) == 0){
			strcpy(dog.pemilik, token); //Username
		
			token = strtok(NULL, ","); //hari
			dog.hari = atoi(token) + hari; //sisa hari akan ditambah
			
			token = strtok(NULL, ","); //Nama
			strcpy(dog.nama, token);//Nama
			
			token = strtok(NULL, ","); //Jenis
			strcpy(dog.jenis, token); //Jenis
			fprintf(tempKandang, "%s,%d,%s,%s,\n", dog.pemilik, dog.hari, dog.nama, dog.jenis);	
		}
		else fprintf(tempKandang, temp);
	}
	fclose(kandang);
	remove("kandangAnjing.txt");
	fclose(tempKandang);
	rename("tempKandangAnjing.txt", "kandangAnjing.txt");
	
	struct kandangAnjing *tempL = *head;
	while(tempL != NULL){
		if(strcmp(tempL->data.pemilik, username) == 0)
			(tempL->data.hari) += hari; //sisa hari akan ditambah
		tempL = tempL->next;
	}
}
void extendKucing(struct kandangKucing **head, char username[], int hari){
	struct kucing cat;
	char temp[100];
	char *token;
	
	FILE *kandang;
	FILE *tempKandang;
	kandang = fopen("kandangKucing.txt", "r");
	tempKandang = fopen("tempKandangKucing.txt", "w+");
	
	while(fgets(temp, sizeof(temp), kandang)){
		token = strtok(temp, ","); //Username
		if(strcmp(token, username) == 0){
			strcpy(cat.pemilik, token); //Username
		
			token = strtok(NULL, ","); //hari
			cat.hari = atoi(token) + hari; //sisa hari akan ditambah
			
			token = strtok(NULL, ","); //Nama
			strcpy(cat.nama, token);//Nama
			
			token = strtok(NULL, ","); //Jenis
			strcpy(cat.jenis, token); //Jenis
			fprintf(tempKandang, "%s,%d,%s,%s,\n", cat.pemilik, cat.hari, cat.nama, cat.jenis);	
		}
		else fprintf(tempKandang, temp);
	}
	fclose(kandang);
	remove("kandangKucing.txt");
	fclose(tempKandang);
	rename("tempKandangKucing.txt", "kandangKucing.txt");
	
	struct kandangKucing *tempL = *head;
	while(tempL != NULL){
		if(strcmp(tempL->data.pemilik, username) == 0)
			(tempL->data.hari) += hari; //sisa hari akan ditambah
		tempL = tempL->next;
	}
}

void swapAnjing(struct kandangAnjing *a, struct kandangAnjing *b){
	struct anjing temp = a->data;
	a->data = b->data;
	b->data = temp;
}
void bubbleSortAscAnjing(struct kandangAnjing *head){
	int swapped, i;
	struct kandangAnjing *ptr1;
	struct kandangAnjing *lptr = NULL;
	
	if(head == NULL) return;
	do{
		swapped = 0;
		ptr1 = head;
		while(ptr1->next != lptr){
			if(ptr1->data.hari > ptr1->next->data.hari){
				swapAnjing(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}while(swapped);
}
void bubbleSortDescAnjing(struct kandangAnjing *head){
	int swapped, i;
	struct kandangAnjing *ptr1;
	struct kandangAnjing *lptr = NULL;
	
	if(head == NULL) return;
	do{
		swapped = 0;
		ptr1 = head;
		while(ptr1->next != lptr){
			if(ptr1->data.hari < ptr1->next->data.hari){
				swapAnjing(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}while(swapped);
}

void swapKucing(struct kandangKucing *a, struct kandangKucing *b){
	struct kucing temp = a->data;
	a->data = b->data;
	b->data = temp;
}
void bubbleSortAscKucing(struct kandangKucing *head){
	int swapped, i;
	struct kandangKucing *ptr1;
	struct kandangKucing *lptr = NULL;
	
	if(head == NULL) return;
	do{
		swapped = 0;
		ptr1 = head;
		while(ptr1->next != lptr){
			if(ptr1->data.hari > ptr1->next->data.hari){
				swapKucing(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}while(swapped);
}
void bubbleSortDescKucing(struct kandangKucing *head){
	int swapped, i;
	struct kandangKucing *ptr1;
	struct kandangKucing *lptr = NULL;
	
	if(head == NULL) return;
	do{
		swapped = 0;
		ptr1 = head;
		while(ptr1->next != lptr){
			if(ptr1->data.hari < ptr1->next->data.hari){
				swapKucing(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}while(swapped);
}

void lihatKandang(){
	int pilih, sort;
	do{
		system("cls");
		printf("Mau lihat kandang apa?\n");
		printf("1. Kucing\n");
		printf("2. Anjing\n");
		printf("3. Kembali\n");
		printf("Pilihan anda: ");
		scanf("%d", &pilih);
		switch(pilih){
			case 1:
				do{
					viewKandangKucing(&catCage);
					printf("\n1. Sort Hari Descending");
					printf("\n2. Sort Hari Ascending");
					printf("\n3. Kembali");
					printf("\nPilihan anda: ");
					scanf("%d", &sort);
					switch(sort){
						case 1:
							bubbleSortDescKucing(catCage);
							break;
						case 2:
							bubbleSortAscKucing(catCage);
							break;
						case 3:
							break;
						default:
							printf("Salah Input!\n");
					}
				}while(sort != 3);
				system("pause");
				break;
			case 2:
				do{
					viewKandangAnjing(&dogCage);
					printf("\n1. Sort Hari Descending");
					printf("\n2. Sort Hari Ascending");
					printf("\n3. Kembali");
					printf("\nPilihan anda: ");
					scanf("%d", &sort);
					switch(sort){
						case 1:
							bubbleSortDescAnjing(dogCage);
							break;
						case 2:
							bubbleSortAscAnjing(dogCage);
							break;
						case 3:
							break;
						default:
							printf("Salah Input!\n");
					}
				}while(sort != 3);
				system("pause");
				break;
			case 3:
				break;
			default:
				printf("Salah Input!\n");
		}
	}while(pilih != 3);
	
}

void tambahHewanKeKandang(){
	struct kucing cat;
	struct anjing dog;
	
	system("cls");
	
	int kucingAnjing;
	
	FILE *kandangKucing;
	FILE *kandangAnjing;
	int fileExist = 0;
	
	printf("=======================\n");
	printf("Tambah Antrian TipHew!!\n");
	printf("=======================\n");
	
	printf("\n[1]Kucing atau [2]Anjing?\n> ");
	scanf("%d", &kucingAnjing);
	
	//Kucing
	if(kucingAnjing == 1){
		//Kapasistas kandang hanya 20, gabisa lebih
		if(countNodeKucing(catCage) >= 20){
			printf("Kandang kucing sudah penuh!\n");
			sleep(1);
			return;
		}
		
		printf("\nMasukkan username penitip: ");
		scanf(" %[^\n]s", &cat.pemilik);
		printf("\nMasukkan lama penitipan (hari): ");
		scanf("%d", &cat.hari);
		printf("\nNama Kucing: ");
		scanf(" %[^\n]s", &cat.nama);
		printf("\nJenis Kucing: ");
		scanf(" %[^\n]s", &cat.jenis);
		
		while(fileExist == 0){
			if(access("kandangKucing.txt", F_OK) == 0){
				fileExist = 1;
				kandangKucing = fopen("kandangKucing.txt", "a");
			}
			else{
				kandangKucing = fopen("kandangKucing.txt", "w");
				fclose(kandangKucing);
			}
		}
		
		if(fprintf(kandangKucing, "%s,%d,%s,%s,\n", cat.pemilik, cat.hari, cat.nama, cat.jenis)){
			appendKucing(&catCage, cat);
			printf("Kucing berhasil ditampung\n");
		}
		else printf("Kucing gagal ditampung\n");
		
		fclose(kandangKucing);
	}
	
	//Anjing
	else if(kucingAnjing == 2){
		//Kapasistas kandang hanya 20, gabisa lebih
		if(countNodeAnjing(dogCage) >= 20){
			printf("Kandang anjing sudah penuh!\n");
			sleep(1);
			return;
		}
		
		printf("\nMasukkan username penitip: ");
		scanf(" %[^\n]s", &dog.pemilik);
		printf("\nMasukkan lama penitipan (hari): ");
		scanf("%d", &dog.hari);
		printf("\nNama Anjing: ");
		scanf(" %[^\n]s", &dog.nama);
		printf("\nJenis Anjing: ");
		scanf(" %[^\n]s", &dog.jenis);
		
		while(fileExist == 0){
			if(access("kandangAnjing.txt", F_OK) == 0){
				fileExist = 1;
				kandangAnjing = fopen("kandangAnjing.txt", "a");
			}
			else {
				kandangAnjing = fopen("kandangAnjing.txt", "w");
				fclose(kandangAnjing);	
			}
		}	
					
		if(fprintf(kandangAnjing, "%s,%d,%s,%s,\n", dog.pemilik, dog.hari, dog.nama, dog.jenis)){
			appendAnjing(&dogCage, dog);
			printf("Anjing berhasil ditampung\n");
		}
		else printf("Anjing gagal ditampung\n");	
		
		fclose(kandangAnjing);
	}
	
}

int isUserExist(char username[]){
	FILE *kandangDog;
	FILE *kandangCat;
	kandangDog = fopen("kandangAnjing.txt", "r");
	kandangCat = fopen("kandangKucing.txt", "r");
	
	char temp[100];
	char *token;
	int dogFound = 0, catFound = 0;
	
	while(fgets(temp, sizeof(temp), kandangDog)){
		token = strtok(temp, ",");
		if(strcmp(username, token) == 0){
			dogFound = 1;
			break;
		}
	}
	
	while(fgets(temp, sizeof(temp), kandangCat)){
		token = strtok(temp, ",");
		if(strcmp(username, token) == 0){
			catFound = 2;
			break;
		}
	}
	
	//0 = GAADA
	//1 = ANJING
	//2 = KUCING
	//3 = 2 2NYA ADA
	int found = dogFound + catFound;
	
	fclose(kandangDog);
	fclose(kandangCat);
	return found;
}

void extendPenitipan(){
	char username[20];
	int hari;	
	
	system("cls");
	
	printf("Masukkan Username: ");
	scanf(" %[^\n]s", &username);
	
	if(isUserExist(username) == 0){
		printf("\nUsername tidak terdaftar!\n");
	}
	else if(isUserExist(username) == 1){
		printf("\nAnda menitipkan Anjing!\n");
		printf("Masukkan jumlah hari untuk diextend: ");
		scanf("%d", &hari);
		extendAnjing(&dogCage, username, hari);
		printf("\nBerhasil extend %d hari!\n", hari);
	}
	else if(isUserExist(username) == 2){
		printf("\nAnda menitipkan Kucing!\n");
		printf("Masukkan jumlah hari untuk diextend: ");
		scanf("%d", &hari);
		extendKucing(&catCage, username, hari);
		printf("\nBerhasil extend %d hari!\n", hari);
	}
	else if(isUserExist(username) == 3){
		printf("\nAnda menitipkan Kucing dan Anjing!\n");
		printf("Masukkan jumlah hari untuk diextend: ");
		scanf("%d", &hari);
		extendAnjing(&dogCage, username, hari);
		extendKucing(&catCage, username, hari);
		printf("\nBerhasil extend %d hari!\n", hari);
	}
	else printf("\nSomething's wrong!\n");
	
}	

void pelepasanHewan(struct kandangKucing **headCat, struct kandangAnjing **headDog){
	struct kandangKucing *tempCat = *headCat;
	struct kandangAnjing *tempDog = *headDog;
	int i = 1;
	int hari;
	int found = 0;
	char nama[100];
	char temp[100];
	char temp2[100];
	char *token;
	system("cls");
	printf("Berikut adalah beberapa hewan yang sisa penitipan harinya sudah habis:\n");
	printf("===KUCING===\n");
	while(tempCat != NULL){
		if(tempCat->data.hari == 0){
			printf("%d.\n", i);
			printf("Pemilik  : %s\n", tempCat->data.pemilik);
			printf("Nama     : %s\n", tempCat->data.nama);
			printf("Jenis    : %s\n", tempCat->data.jenis);
			printf("Sisa hari: %d\n", tempCat->data.hari);
			i++;
			found++;
		}
		tempCat = tempCat->next;
	}
	i = 1;
	printf("===ANJING===\n");
	while(tempDog != NULL){
		if(tempDog->data.hari == 0){
			printf("%d.\n", i);
			printf("Pemilik  : %s\n", tempDog->data.pemilik);
			printf("Nama     : %s\n", tempDog->data.nama);
			printf("Jenis    : %s\n", tempDog->data.jenis);
			printf("Sisa hari: %d\n", tempDog->data.hari);
			i++;
			found++;
		}
		tempDog = tempDog->next;
	}
	if(found > 0){
		printf("Username yang akan dilepas: ");
		scanf(" %[^\n]s", &nama);
		FILE *kandangAnjing;
		FILE *kandangKucing;
		FILE *tempKandangAnjing;
		FILE *tempKandangKucing;

		kandangAnjing = fopen("kandangAnjing.txt", "r");
		kandangKucing = fopen("kandangKucing.txt", "r");
		tempKandangAnjing = fopen("tempKandangAnjing.txt", "w+");
		tempKandangKucing = fopen("tempKandangKucing.txt", "w+");
		
		while(fgets(temp, sizeof(temp), kandangAnjing)){
			strcpy(temp2, temp);
			token = strtok(temp, ",");
			if(strcmp(token, nama) == 0){
				token = strtok(NULL, ",");
				hari = atoi(token);
				if(hari == 0) continue;
				else fprintf(tempKandangAnjing, temp2);
			}
			else fprintf(tempKandangAnjing, temp2);
		}
		
		while(fgets(temp, sizeof(temp), kandangKucing)){
			strcpy(temp2, temp);
			token = strtok(temp, ",");
			if(strcmp(token, nama) == 0){
				token = strtok(NULL, ",");
				hari = atoi(token);
				if(hari == 0) continue;
				else fprintf(tempKandangKucing, temp2);
			}
			else fprintf(tempKandangKucing, temp2);
		}
		
		fclose(kandangAnjing);
		fclose(kandangKucing);
		remove("kandangAnjing.txt");
		remove("kandangKucing.txt");
		fclose(tempKandangAnjing);
		fclose(tempKandangKucing);
		rename("tempKandangAnjing.txt", "kandangAnjing.txt");
		rename("tempKandangKucing.txt", "kandangKucing.txt");
		clearKandangAnjing(&dogCage);
		clearKandangKucing(&catCage);
		addTxtToLinkedListAnjing(&dogCage);
		addTxtToLinkedListKucing(&catCage);
	}
	else{
		printf("---------------\n");
		printf("Tidak ada hewan yang sisa harinya habis\n");
	}
}

void menuAdmin(){
	int pilih;
	clearKandangAnjing(&dogCage);
	clearKandangKucing(&catCage);
	addTxtToLinkedListAnjing(&dogCage);
	addTxtToLinkedListKucing(&catCage);
	do{
		system("cls");
		printf("============================\n");
		printf("Selamat Datang Admin TipHew!\n");
		printf("============================\n");
		printf("[1] Lihat Isi Kandang\n");
		printf("[2] Tambah Hewan ke Kandang\n");
		printf("[3] Pelepasan Hewan\n");
		printf("[4] Extend Penitipan\n");
		printf("[5] HARI SELANJUTNYA\n");
		printf("[9] Log Out\n");
		printf("Pilihan anda: ");
		scanf("%d", &pilih);
		
		switch(pilih){
			case 1:
				lihatKandang();
				break;
			case 2:
				tambahHewanKeKandang();
				break;
			case 3:
				pelepasanHewan(&catCage, &dogCage);
				break;
			case 4:
				extendPenitipan();
				break;
			case 5:
				nextDayAnjing(&dogCage);
				nextDayKucing(&catCage);
				printf("BERTAMBAH 1 HARI!\n");
				break;
			case 9:
				break;
			default:
				printf("\nSalah input!");
		}
		printf("\nWait...\n");
		sleep(1);
	}while(pilih != 9);
}

const char* encrypt(char password[100], int angkaUnik){
	int i;
	
	int maxThread = omp_get_max_threads();
	
	if(strlen(password) < maxThread){
		omp_set_num_threads(strlen(password));
	}
	
	#pragma omp parallel for schedule(static)
	for(i = 0; i < strlen(password); i++){
		password[i] += angkaUnik;
	}
	
	omp_set_num_threads(maxThread);
	
	return password;
}

const char* decrypt(char password[100], int angkaUnik){
	int i;
	
	int maxThread = omp_get_max_threads();
	
	if(strlen(password) < maxThread){
		omp_set_num_threads(strlen(password));
	}
	
	#pragma omp parallel for schedule(static)
	for(i = 0; i < strlen(password); i++){
		password[i] -= angkaUnik;
	}
	
	omp_set_num_threads(maxThread);
	
	return password;
}

int logIn(){
	char nama[100], password[100], temp[100];
	char *token;
	int found = 0;
	FILE *dataUser;
	dataUser = fopen("admin/admin.txt", "r");
	
	system("cls");
	printf("Nama    : ");
	scanf(" %[^\n]s", &nama);
	
	while(fgets(temp, sizeof(temp), dataUser)){
		token = strtok(temp, ",");
		if(strcmp(token, nama) == 0){
			printf("Password: ");
			scanf(" %[^\n]s", &password);
			
			token = strtok(NULL, ",");
			int key = atoi(token);
			token = strtok(NULL, ",");
			if(strcmp(decrypt(token, key), password) == 0){
				printf("\n ------------------\n");
		    	printf(" | LOGIN SUCCESS! |");
		    	printf("\n ------------------\n\n");
				found = 1;
				system("pause");
				
			}
		}
	}
	fclose(dataUser);
	
	return found;
}

void regist(){
	FILE *dataUser;
	int angkaUnik;
	char nama[100], password[100];
	while(1){
		system("cls");
		if(access("admin/admin.txt", F_OK) == 0){
			dataUser = fopen("admin/admin.txt", "a");
			printf("Masukkan nama: ");
			scanf(" %[^\n]s", &nama);
			printf("Masukkan password: ");
			scanf(" %[^\n]s", &password);
			do{
				printf("Masukkan angka unik: ");
				scanf("%d", &angkaUnik);
				if(angkaUnik <= 0) printf("\nAngka unik tidak bisa dibawah 1!\n");
			}while(angkaUnik <= 0);
			if(fprintf(dataUser, "%s,%d,%s,\n", nama,angkaUnik,encrypt(password, angkaUnik))){
				printf("Admin %s berhasil terdaftar!\n", &nama);
				system("pause");
				break;
			}
		}
		else{
			mkdir("admin");
			dataUser = fopen("admin/admin.txt", "w");
			fclose(dataUser);
		}
	}
	fclose(dataUser);
}

int main() {
	int pilih;
	do{	
		system("cls");
		printf("===================================\n");
		printf("Admin Access Program TipHew!\n");
		printf("===================================\n");
		printf("Menu\n");
		printf("[1] Log In\n[2] Register New Admin\n[3] Exit\n");
		printf("\nPilih : ");
		scanf("%d", &pilih);
		switch (pilih){
			case 1 :
				if(logIn() == 1){
					menuAdmin();
				}
				else printf("Anda belum terdaftar!\n"); 
				system("pause");
				break;
			case 2 :
				regist();
				break;
			case 3:
				system("cls");
				printf("Terima kasih\n");
				break;
			default:
				printf("\nSalah input!\n\n");
		}
	}while(pilih != 3);
	
	return 0;
}
