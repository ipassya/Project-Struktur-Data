#include <iostream>
#include <string.h>
#include <fstream>
#include <malloc.h>
using namespace std;

struct data {
	char nama[30], barang[30];
	int harga, pk = 0;
};
struct dataLog {
	char logActivity[100];
	int pkLog = 0;
};
typedef struct typeQueue *ptrQueue;
typedef struct typeStack *ptrStack;
typedef struct typePtb *ptrPtb;
struct typeQueue{
	data queue;
	ptrQueue nextQueue;
};
struct typeStack{
	data stack;
	ptrStack nextStack;
};
struct typePtb{
	dataLog ptb;
	ptrPtb nextPtb, prevPtb;
};

ptrQueue firstQueue, lastQueue;
ptrStack firstStack, lastStack;
ptrPtb root, p, b;
int getOption(int *choose);
void createData();
int emptyQueue();
int emptyStack();
int emptyPtb();
void writeDataArchives(data inputData);
void writeDataLog(data inputData, int log, data inputData2);
void enqueue(data inputData);
void insertArchives(data inputData);
void insertLog(dataLog inputDataLog);
void printLog();
void inorder(ptrPtb root);
void inputData();
void dequeue();
void printQueue();
void printArchives();
void editData();
void deleteData();
void history();

int main() {
	createData();
	int choose;
	char is_continue;
	enum option{CREATE = 1, READ, DEQUEUE, UPDATE, DELETE, ARCHIVES, EXIT};
	int is_choose = getOption(&choose);
	
	while(is_choose != EXIT){
		switch(is_choose){
			case CREATE :
				inputData();
				break;
			case READ :
				system("cls");
				cout << " ___________________________" << endl;
				cout << "|                           |" << endl;
				cout << "|       Daftar Pembeli      |" << endl;
				cout << "|___________________________|" << endl;
				if(emptyQueue()) {
					cout << "\n-------- Menu daftar pembeli masih kosong ['.'] --------" << endl << endl;
				} else {
					printQueue();
				}
				break;
			case DEQUEUE :
				system("cls");
				cout << " ___________________________" << endl;
				cout << "|                           |" << endl;
				cout << "|         Pembayaran        |" << endl;
				cout << "|___________________________|" << endl;
				if(emptyQueue()) {
					cout << "\n-------- Antrian pembeli masih kosong ['.'] --------" << endl << endl;
				} else {
					dequeue();
					printQueue();
				}
				break;
			case UPDATE :
				system("cls");
				cout << " ___________________________" << endl;
				cout << "|                           |" << endl;
				cout << "|       Ubah Pembelian      |" << endl;
				cout << "|___________________________|" << endl;
				if(emptyQueue()) {
					cout << "\n-------- Antrian pembeli masih kosong ['.'] --------" << endl << endl;
				} else {
					printQueue();
					editData();
				}
				break;
			case DELETE :
				system("cls");
				cout << " ___________________________" << endl;
				cout << "|                           |" << endl;
				cout << "|     Batalkan Pembelian    |" << endl;
				cout << "|___________________________|" << endl;
				if(emptyQueue()) {
					cout << "\n-------- Antrian pembeli masih kosong ['.'] --------" << endl << endl;
				} else {
					printQueue();
					deleteData();
				}
				break;
			case ARCHIVES :
				history();
				break;
			default:
				cout << "Pilihan tidak ditemukan" << endl;
				break;
		}
		
		label_continue:
		
		cout << "\nKembali Kemenu Utama? (y/n) : ";
		cin >> is_continue;
		if ( (is_continue == 'y') | (is_continue == 'Y')){
			system("cls");
			is_choose = getOption(&choose);
		} else if ((is_continue == 'n') | (is_continue == 'N')){
			break;
		} else {
			goto label_continue;
		}
	}
	
	cout << "\n\n  TERIMA KASIH ['-']" << endl;
	
	
	return 0;
}

int getOption(int *choose){
	cout << " ___________________________" << endl;
	cout << "|                           |" << endl;
	cout << "|            Menu           |" << endl;
	cout << "|___________________________|" << endl;
	cout << "|                           |" << endl;
	cout << "|1. Beli Barang             |" << endl;
	cout << "|2. Daftar Pembeli          |" << endl;
	cout << "|3. Pembayaran              |" << endl;
	cout << "|4. Ubah Pembelian          |" << endl;
	cout << "|5. Batal Pembelian         |" << endl;
	cout << "|6. Riwayat Pelayanan       |" << endl;
	cout << "|7. Exit                    |" << endl;
	cout << "|___________________________|" << endl;
	cout << "  Pilih Menu [1-6]? : "; cin >> *choose;
	
	return *choose;
}

void createData() {
	firstQueue = (typeQueue *) malloc(sizeof(typeQueue));
	firstQueue = NULL;
	lastQueue = firstQueue;

	ptrStack newStack;
	newStack = NULL;
	firstStack = newStack;
	lastStack = newStack;

	ptrPtb newPtb;
	newPtb = NULL;
	root = newPtb;
}

int emptyQueue() {
	if(firstQueue == NULL)
		return true;
	else
		return false;
}

int emptyStack() {
	if(firstStack == NULL)
		return true;
	else
		return false;
}

int emptyPtb() {
	if(root == NULL)
		return true;
	else
		return false;
}

void writeDataArchives(data inputData) {
	ofstream dataOut;
	dataOut.open("archives.txt", ios::out | ios::app);
	dataOut << inputData.pk << endl;
	dataOut << inputData.nama << endl;
	dataOut << inputData.barang << endl;
	dataOut << inputData.harga << endl;
	dataOut.close();
}

void writeDataLog(data inputData, int log, data inputData2) {
	ofstream dataOut;
	ifstream dataIn;
	dataLog temp;
	dataIn.open("logActivity.txt", ios::in);
	while(!dataIn.eof()) {
		dataIn >> temp.pkLog;
		dataIn.getline(temp.logActivity, 100);
		dataIn.getline(temp.logActivity, 100);
	}
	if(temp.pkLog == 0) {
		temp.pkLog = 0;
	}
	dataIn.close();
	dataOut.open("logActivity.txt", ios::out | ios::app);
	temp.pkLog += 1;
	if(log == 1) {
		dataOut << temp.pkLog << endl; // harusnya urutan dari file
		dataOut << "ID : " << inputData.pk << " melakukan Pembelian " << inputData.barang << " dengan harga Rp " << inputData.harga << " oleh " << inputData.nama << endl;
	} else if(log == 2) {
		dataOut << temp.pkLog << endl;
		dataOut << "ID : " << inputData.pk << " melakukan Pembayaran " << inputData.barang << " dengan harga Rp " << inputData.harga << " oleh " << inputData.nama << " berhasil" << endl;
	} else if(log == 3) {
		dataOut << temp.pkLog << endl;
		dataOut << "ID : " << inputData.pk << " melakukan Perubahan pembelian barang " << inputData.barang << " menjadi " << inputData2.barang << " oleh " << inputData.nama << " berhasil" << endl;
	} else if(log == 4) {
		dataOut << temp.pkLog << endl;
		dataOut << "ID : " << inputData.pk << " melakukan Pembatalan pembelian barang " << inputData.barang << " oleh " << inputData.nama << " berhasil" << endl;
	} 
	
	dataOut.close();
}

void enqueue(data inputData) {
	ptrQueue newData;
	newData = (typeQueue *) malloc(sizeof(typeQueue));
	newData->queue = inputData;
	if (firstQueue == NULL)
		firstQueue = newData;
	else
		lastQueue->nextQueue = newData;
	lastQueue = newData;
	lastQueue->nextQueue = NULL;
}

void insertArchives(data inputData) {
	ptrStack newData;
	newData = (typeStack *) malloc(sizeof(typeStack));
	newData->stack = inputData;
	if (firstStack == NULL)
		firstStack = newData;
	else
		lastStack->nextStack = newData;
	lastStack = newData;
	lastStack->nextStack = NULL;
}

void insertLog(dataLog inputDataLog) {
	ptrPtb newData;
	newData = (typePtb *) malloc(sizeof(typePtb));
	newData->ptb = inputDataLog;
	newData->prevPtb = NULL;
	newData->nextPtb = NULL;
	if (emptyPtb()) {
		root = newData;
	} else {
		b = root;
		p = root;
		// mencari tempat untuk menyisipkan node
		while(p != NULL && inputDataLog.pkLog != b->ptb.pkLog) {
			b = p;
			if (inputDataLog.pkLog < p->ptb.pkLog) {
				p = b->prevPtb;
			} else {
				p = b->nextPtb;
			}
		}
		if (inputDataLog.pkLog == b->ptb.pkLog) {
			//cout << "\n\nID " << inputDataLog.pkLog << " sudah ada !\n\n";
		} else {
			if (inputDataLog.pkLog < b->ptb.pkLog) {
				b->prevPtb = newData;
			} else {
				b->nextPtb = newData;
			}
		}
	}
}

void inputData() {
	int choose;
	data inputData;
	char is_continue;
	ifstream dataIn;
	
	dataIn.open("archives.txt", ios::in);
	while(!dataIn.eof()) {
		dataIn >> inputData.pk;
		dataIn >> inputData.nama;
		dataIn >> inputData.barang;
		dataIn >> inputData.harga;
	}
	if(inputData.pk == 0) {
		inputData.pk = 0;
	}
	dataIn.close();
	do {
		system("cls");
		cout << " ___________________________" << endl;
		cout << "|                           |" << endl;
		cout << "|         Beli Barang       |" << endl;
		cout << "|___________________________|" << endl;
		inputData.pk += 1;
		cout << "\nInput Nama Pembeli : "; cin >> inputData.nama;
		cout << "\n         Daftar Barang         " << endl;
		cout << " ________________________________" << endl;
		cout << "|                                |" << endl;
		cout << "| No   Nama Barang   Harga Barang|" << endl;
		cout << "|________________________________|" << endl;
		cout << "|    |             |             |" << endl;
		cout << "| 1  |    Kaos     | Rp. 150.000 |" << endl;
		cout << "| 2  |    Kemeja   | Rp. 300.000 |" << endl;
		cout << "| 3  |    Polo     | Rp. 175.000 |" << endl;
		cout << "| 4  |    Jaket    | Rp. 500.000 |" << endl;
		cout << "| 5  |    Hoodie   | Rp. 400.000 |" << endl;
		cout << "|____|_____________|_____________|" << endl;
		cout << "  Pilih Satu Barang [1-5]? : "; cin >> choose;
		switch(choose) {
			case 1:
				strcpy(inputData.barang, "Kaos");
				inputData.harga = 150000;
				break;
			case 2:
				strcpy(inputData.barang, "Kemeja");
				inputData.harga = 300000;
				break;
			case 3:
				strcpy(inputData.barang, "Polo");
				inputData.harga = 175000;
				break;
			case 4:
				strcpy(inputData.barang, "Jaket");
				inputData.harga = 500000;
				break;
			case 5:
				strcpy(inputData.barang, "Hoodie");
				inputData.harga = 400000;
				break;
			default:
				cout << "Pilihan tidak ditemukan" << endl;
		}
		enqueue(inputData);
		cout << "\n\nAda antrian lagi?(y/n) : "; cin >> is_continue;
		cout << "_________________________________" << endl;
		writeDataArchives(inputData);
		writeDataLog(inputData, 1, inputData);
		cout << endl;
	} while ((is_continue == 'y') | (is_continue == 'Y'));
}

void dequeue() {
	ptrQueue deleteData;
	data temp;
	if (emptyQueue()) { 
		cout << "Antrian masih kosong !";
	} else {
		deleteData = firstQueue;
		firstQueue = deleteData->nextQueue;
		cout << "\n\nPembayaran oleh " << deleteData->queue.nama << " berhasil ['.']";
		temp = deleteData->queue;
		writeDataLog(temp, 2, temp);
		cout << endl;
		free(deleteData);
	}
}

void printQueue() {
	ptrQueue help;
	help = firstQueue;
	do {
		cout << "\n\nID Pembeli\t: " << help->queue.pk << endl;
		cout << "Nama\t\t: " << help->queue.nama << endl;
		cout << "Barang yang di beli adalah " << help->queue.barang << " harga Rp. " << help->queue.harga << endl;
		cout << "_____________________________________________________" << endl;
		cout << endl;
		help = help->nextQueue;
	} while(help != NULL);
}

void printArchives() {
	ptrStack help, print;
	help = firstStack;
	print = lastStack;
	cout << endl;
	while (print != firstStack) {
		while (help->nextStack != print) {
			help = help->nextStack;
		}
		cout << "\nID Pembeli\t: " << print->stack.pk << endl;
		cout << "Nama\t\t: " << print->stack.nama << endl;
		cout << "Barang yang di beli adalah " << print->stack.barang << " harga Rp. " << print->stack.harga << endl;
		cout << "_____________________________________________________" << endl;
		cout << endl;
		print = help;
		help = firstStack;
	}
	cout << "\nID Pembeli\t: " << print->stack.pk << endl;
	cout << "Nama\t\t: " << print->stack.nama << endl;
	cout << "Barang yang di beli adalah " << print->stack.barang << " harga Rp. " << print->stack.harga << endl;
	cout << "_____________________________________________________" << endl;
	cout << endl;
}

void printLog() {
  inorder(root);
  return;
}

void inorder(ptrPtb root) {
	if (root != NULL) {
		inorder(root->prevPtb);
		cout << endl << root->ptb.pkLog << ". " << root->ptb.logActivity << endl;
		cout << "_______________________________________________________________________________________" << endl;
		inorder(root->nextPtb);
	}
}

void editData() {
	data temp, temp2;
	int pilih;
	ptrQueue help;
	cout << "\nMasukan ID pembeli : "; cin >> temp.pk;
	help = firstQueue;
	while(help != NULL) {
		if(help->queue.pk == temp.pk) {
			cout << "\n------------------Data Ditemukan------------------\n\n";
			cout << "ID Pembeli\t: " << help->queue.pk << endl;
			cout << "Nama\t\t: " << help->queue.nama << endl;
			cout << "Barang yang di beli adalah " << help->queue.barang << " harga Rp. " << help->queue.harga << endl;
			cout << endl;
			cout << "\n  Ubah Data Barang Belanjaan   " << endl;
			cout << " ________________________________" << endl;
			cout << "|                                |" << endl;
			cout << "| No   Nama Barang   Harga Barang|" << endl;
			cout << "|________________________________|" << endl;
			cout << "|    |             |             |" << endl;
			cout << "| 1  |    Kaos     | Rp. 150.000 |" << endl;
			cout << "| 2  |    Kemeja   | Rp. 300.000 |" << endl;
			cout << "| 3  |    Polo     | Rp. 175.000 |" << endl;
			cout << "| 4  |    Jaket    | Rp. 500.000 |" << endl;
			cout << "| 5  |    Hoodie   | Rp. 400.000 |" << endl;
			cout << "|____|_____________|_____________|" << endl;
			cout << "  Pilih Satu Barang [1-5]? : "; cin >> pilih;
			switch(pilih) {
				case 1:
					temp = help->queue;
					strcpy(help->queue.barang, "Kaos");
					help->queue.harga = 150000;
					temp2 = help->queue;
					break;
				case 2:
					temp = help->queue;
					strcpy(help->queue.barang, "Kemeja");
					help->queue.harga = 300000;
					temp2 = help->queue;
					break;
				case 3:
					temp = help->queue;
					strcpy(help->queue.barang, "Polo");
					help->queue.harga = 175000;
					temp2 = help->queue;
					break;
				case 4:
					temp = help->queue;
					strcpy(help->queue.barang, "Jaket");
					help->queue.harga = 500000;
					temp2 = help->queue;
					break;
				case 5:
					temp = help->queue;
					strcpy(help->queue.barang, "Hoodie");
					help->queue.harga = 400000;
					temp2 = help->queue;
					break;
				default:
					cout << "Pilihan tidak ditemukan" << endl;
			}
			cout << "\n-----Perubahan Barang Belanjaan Berhasil ['.']-----" << endl;
			cout << "\nID Pembeli\t: " << help->queue.pk << endl;
			cout << "Nama\t\t: " << help->queue.nama << endl;
			cout << "Barang yang di beli adalah " << help->queue.barang << " harga Rp. " << help->queue.harga << endl;
			cout << "_____________________________________________________" << endl << endl;
			
			writeDataLog(temp, 3, temp2);
			break;
		}
		help = help->nextQueue;
	}
}

void deleteData() {
	ptrQueue deleteData, help;
	data temp;
	cout << "\nMasukan ID Pembeli : "; cin >> temp.pk;
	if (emptyQueue()){
		cout << "Antrian masih kosong";
	} else if (firstQueue->queue.pk == temp.pk) { // deleteData di firstQueue
		deleteData = firstQueue;                      
		firstQueue = deleteData->nextQueue;
		cout << "\n----- Pembatalan oleh " << deleteData->queue.nama << " berhasil ['.'] -----" << endl << endl;
		temp = deleteData->queue;
		writeDataLog(temp, 4, temp);
		free(deleteData);
	} else {
		help = firstQueue;
		while (help->nextQueue->nextQueue != NULL && temp.pk != help->nextQueue->queue.pk)
			help = help->nextQueue;
		if (temp.pk == help->nextQueue->queue.pk) {
			deleteData = help->nextQueue;
			if (deleteData == lastQueue) { // deleteData di lastQueue
				lastQueue = help;
				lastQueue->nextQueue = NULL;
			} else {
				help->nextQueue = deleteData->nextQueue;   // deleteData di middle
			}
			cout << "\n----- Pembatalan oleh " << deleteData->queue.nama << " berhasil ['.'] -----" << endl << endl;
			temp = deleteData->queue;
			writeDataLog(temp, 4, temp);
			free(deleteData);
		} else {
			cout << "Node tidak ditemukan!\n";
		}
	}
}

void history() {
	int choose;
	char is_continue;
	data inputData;
	dataLog inputDataLog;
	ifstream dataIn, dataInLog;
	do {
		system("cls");
		cout << " ___________________________" << endl;
		cout << "|                           |" << endl;
		cout << "|      Riwayat Pelayanan    |" << endl;
		cout << "|___________________________|" << endl;
		cout << "|                           |" << endl;
		cout << "|  1. Archives              |" << endl;
		cout << "|  2. Log Activity          |" << endl;
		cout << "|  3. Reset History         |" << endl;
		cout << "|___________________________|" << endl;
		cout << "  Pilih [1-3]? : "; cin >> choose;
		switch(choose) {
			case 1:
				if(emptyStack()) {
					dataIn.open("archives.txt", ios::in);
					while(!dataIn.eof()) {
						inputData.pk = 0;
						dataIn >> inputData.pk;
						dataIn >> inputData.nama;
						dataIn >> inputData.barang;
						dataIn >> inputData.harga;
						if(inputData.pk != 0) {
							insertArchives(inputData);
						}
					}
					dataIn.close();
				}
				if(emptyStack()) {
					cout << "\n-------- Menu archives masih kosong ['.'] --------" << endl << endl;
				} else {
					printArchives();
				}
				break;
			case 2:
				if(emptyPtb()) {
					dataInLog.open("logActivity.txt", ios::in);
					while(!dataInLog.eof()) {
						dataInLog >> inputDataLog.pkLog;
						dataInLog.getline(inputDataLog.logActivity, 100);
						dataInLog.getline(inputDataLog.logActivity, 100);
						if(inputDataLog.pkLog != 0) {
							insertLog(inputDataLog);
						}
					}
					dataInLog.close();
				}
				if(emptyPtb()) {
					cout << "\n-------- Menu log activity masih kosong ['.'] --------" << endl << endl;
				} else {
					printLog();
				}
				break;
			case 3:
				dataIn.open("archives.txt", ios::trunc | ios::out);
				dataIn.close();
				dataIn.open("logActivity.txt", ios::trunc | ios::out);
				dataIn.close();
				root = NULL;
				p = NULL;
				b = NULL;
				firstStack = NULL;
				lastStack = NULL;
				cout << "\n-------- History berhasil di reset ['.'] --------" << endl << endl;
				break;
			default:
				cout << "Pilihan tidak ditemukan" << endl;
		}
		cout << "\nKe menu riwayat pelayanan lagi [y/n]? : "; cin >> is_continue;
		cout << endl;
	} while ((is_continue == 'y') | (is_continue == 'Y'));
}
