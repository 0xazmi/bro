#include <iostream>
using namespace std;

struct node {
    int data;
    node *next;
};

void tambahData(node **head);
void insertionSort(node **head);
void tranverse(node *head);

int main() {
    node *head = NULL;
    char pilih;

    do {
        system("cls");
        cout << "Masukkan pilihan" << endl;
        cout << "1. Tambah data" << endl;
        cout << "2. Insertion sort" << endl;
        cout << "3. Cetak isi list" << endl;
        cout << "MASUKKAN PILIHAN (tekan q untuk keluar): ";
        cin >> pilih;

        switch (pilih) {
            case '1':
                tambahData(&head);
                break;
            case '2':
                insertionSort(&head);
                break;
            case '3':
                tranverse(head);
                system("pause");
                break;
            default:
                if (pilih == 'q') {
                    return 0;
                } else {
                    cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                    system("pause");
                }
                break;
        }

    } while (true);

    return 0;
}

void tambahData(node **head) {
    int bil;
    node *pNew;

    system("cls");
    cout << "Masukkan bilangan yang ingin ditambahkan: ";
    cin >> bil;

    pNew = new node;

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;

        if (*head == NULL) {
            *head = pNew;
        } else {
            node *pLast = *head;
            while (pLast->next != NULL) {
                pLast = pLast->next;
            }
            pLast->next = pNew;
        }
    } else {
        cout << "\nAlokasi memori gagal" << endl;
        system("pause");
    }
}

void insertionSort(node **head) {
    node *sorted = NULL;
    node *current = *head;

    while (current != NULL) {
        node *next = current->next;

        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            node *temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }

    *head = sorted;
}

void tranverse(node *head) {
    node *pWalker;
    system("cls");
    pWalker = head;
    while (pWalker != NULL) {
        cout << pWalker->data << "\t";
        pWalker = pWalker->next;
        if (pWalker != NULL)
            cout << " -> ";
    }
    cout << "NULL" << endl;
}
