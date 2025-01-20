#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_PHONE 15
#define MAX_EMAIL 50
#define MAX_HISTORY 10 // Batas riwayat perubahan dalam stack

// Struktur kontak
typedef struct Contact {
    int id;
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
} Contact;

// Node untuk Queue
typedef struct QueueNode {
    Contact contact;
    struct QueueNode *next;
} QueueNode;

// Queue
typedef struct {
    QueueNode *front, *rear;
} Queue;

// Node untuk Circular Linked List
typedef struct CLNode {
    Contact contact;
    struct CLNode *next;
} CLNode;

// Stack untuk riwayat perubahan
typedef struct {
    Contact history[MAX_HISTORY];
    int top;
} Stack;

// Fungsi untuk Queue
void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

int isQueueEmpty(Queue *q) {
    return q->front == NULL;
}

void enqueue(Queue *q, Contact c) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    if (!newNode) {
        printf("Gagal mengalokasikan memori.\n");
        return;
    }
    newNode->contact = c;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int isIdExistInQueue(Queue *q, int id) {
    QueueNode *temp = q->front;
    while (temp != NULL) {
        if (temp->contact.id == id) {
            return 1; // ID ditemukan
        }
        temp = temp->next;
    }
    return 0; // ID tidak ditemukan
}

Contact dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue kosong.\n");
        Contact emptyContact = {0, "", "", ""};
        return emptyContact;
    }
    QueueNode *temp = q->front;
    Contact c = temp->contact;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return c;
}

void displayQueue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("\nKontak Masih kosong...\n");
        return;
    }
    QueueNode *temp = q->front;
    while (temp) {
        printf("ID: %d\t, Nama: %s\t, Telepon: %s\t, Email: %s\t\n", temp->contact.id, temp->contact.name, temp->contact.phone, temp->contact.email);
        temp = temp->next;
    }
}

// Fungsi untuk Circular Linked List
void addToCircularList(CLNode **head, Contact c) {
    CLNode *newNode = (CLNode *)malloc(sizeof(CLNode));
    if (!newNode) {
        printf("Gagal mengalokasikan memori.\n");
        return;
    }
    newNode->contact = c;
    if (*head == NULL) {
        newNode->next = newNode;
        *head = newNode;
    } else {
        CLNode *temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}

void displayCircularList(CLNode *head) {
    if (head == NULL) {
        printf("Circular Linked List kosong.\n");
        return;
    }
    CLNode *temp = head;
    do {
        printf("ID: %d, Nama: %s, Telepon: %s, Email: %s\n", temp->contact.id, temp->contact.name, temp->contact.phone, temp->contact.email);
        temp = temp->next;
    } while (temp != head);
}

// Fungsi untuk Stack
void initStack(Stack *s) {
    s->top = -1;
}

int isStackFull(Stack *s) {
    return s->top == MAX_HISTORY - 1;
}

int isStackEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, Contact c) {
    if (isStackFull(s)) {
        printf("Riwayat penuh, tidak bisa menambahkan.\n");
        return;
    }
    s->history[++s->top] = c;
}

Contact pop(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Riwayat kosong.\n");
        Contact emptyContact = {0, "", "", ""};
        return emptyContact;
    }
    return s->history[s->top--];
}

void displayStack(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Riwayat kosong...\n");
        return;
    }
    for (int i = s->top; i >= 0; i--) {
        printf("ID: %d, Nama: %s, Telepon: %s, Email: %s\n", s->history[i].id, s->history[i].name, s->history[i].phone, s->history[i].email);
    }
}// Tambahkan fungsi untuk mengedit kontak
void editContact(Queue *q, CLNode *clHead) {
    if (isQueueEmpty(q)) {
        printf("Tidak ada kontak untuk diedit.\n");
        printf("\nTekan Enter untuk kembali ke menu utama...");
        getchar();
        getchar();
        return;
    }

    int id;
    printf("Masukkan ID kontak yang ingin diedit: ");
    scanf("%d", &id);

    QueueNode *temp = q->front;
    int found = 0;

    // Cari kontak di Queue
    while (temp != NULL) {
        if (temp->contact.id == id) {
            found = 1;
            printf("Kontak ditemukan!\n");
            printf("ID: %d, Nama: %s, Telepon: %s, Email: %s\n", temp->contact.id, temp->contact.name, temp->contact.phone, temp->contact.email);

            printf("\nMasukkan data baru (tekan Enter untuk mempertahankan data lama):\n");

            printf("Nama baru: ");
            getchar(); // Membersihkan newline dari input sebelumnya
            char newName[MAX_NAME];
            fgets(newName, MAX_NAME, stdin);
            newName[strcspn(newName, "\n")] = 0; // Hapus newline jika ada
            if (strlen(newName) > 0) {
                strcpy(temp->contact.name, newName);
            }

            printf("Nomor telepon baru: ");
            char newPhone[MAX_PHONE];
            fgets(newPhone, MAX_PHONE, stdin);
            newPhone[strcspn(newPhone, "\n")] = 0;
            if (strlen(newPhone) > 0) {
                strcpy(temp->contact.phone, newPhone);
            }

            printf("Email baru: ");
            char newEmail[MAX_EMAIL];
            fgets(newEmail, MAX_EMAIL, stdin);
            newEmail[strcspn(newEmail, "\n")] = 0;
            if (strlen(newEmail) > 0) {
                strcpy(temp->contact.email, newEmail);
            }

            printf("\nKontak berhasil diperbarui!\n");
            printf("ID: %d, Nama: %s, Telepon: %s, Email: %s\n", temp->contact.id, temp->contact.name, temp->contact.phone, temp->contact.email);

            // Sinkronisasi dengan Circular Linked List
            CLNode *clTemp = clHead;
            do {
                if (clTemp->contact.id == id) {
                    clTemp->contact = temp->contact;
                    break;
                }
                clTemp = clTemp->next;
            } while (clTemp != clHead);

            break;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Kontak dengan ID %d tidak ditemukan.\n", id);
    }

    printf("\nTekan Enter untuk kembali ke menu utama...");
    getchar();
    getchar();
}


// Menu utama
void menu() {
    Queue q;
    initQueue(&q);

    CLNode *clHead = NULL;

    Stack history;
    initStack(&history);

    int choice;
    do {
        system("cls");
        printf("===============================\n");
        printf("  Sistem Manajemen Kontak  \n");
        printf("===============================\n");
        printf("1. Tambah Kontak\n");
        printf("2. Tampilkan Daftar Kontak (Queue)\n");
        printf("3. Cari Kontak (Circular Linked List)\n");
        printf("4. Edit Kontak\n");
        printf("5. Hapus Kontak\n");
        printf("6. Keluar\n");
        printf("Pilihan Anda: ");
        if (scanf("%d", &choice) != 1) { // Validasi input non-numerik
            while (getchar() != '\n');  // Membersihkan buffer
            printf("\nPilihan tidak valid...\n");
            printf("Tekan Enter untuk melanjutkan...");
            getchar();
            continue;
        }

        switch (choice) {
            case 1: {
                Contact c;
                int isDuplicateId = 0; // Flag untuk cek duplikasi ID
                do {
                    system("cls");
                    printf("===============================\n");
                    printf("     Menu Tambah Kontak    \n");
                    printf("===============================\n");

                    if (isDuplicateId) {
                        printf("Peringatan: ID sudah ada. Masukkan ID yang berbeda!!!\n\n");
                    }
                    printf("Masukkan ID: ");
                    scanf("%d", &c.id);
                    isDuplicateId = isIdExistInQueue(&q, c.id); // Cek apakah ID sudah ada
                } while (isDuplicateId);

                printf("Masukkan nama: ");
                getchar();
                fgets(c.name, MAX_NAME, stdin);
                c.name[strcspn(c.name, "\n")] = 0;
                printf("Masukkan nomor telepon: ");
                fgets(c.phone, MAX_PHONE, stdin);
                c.phone[strcspn(c.phone, "\n")] = 0;
                printf("Masukkan email: ");
                fgets(c.email, MAX_EMAIL, stdin);
                c.email[strcspn(c.email, "\n")] = 0;

                enqueue(&q, c);
                addToCircularList(&clHead, c);
                printf("\nKontak berhasil ditambahkan...");
                getchar();
                break;
            }
            case 2:
             system("cls");
             printf("===============================\n");
                printf("     Menu Daftar Kontak    \n");
                printf("===============================\n");
                displayQueue(&q);
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                break;
            case 3:
                printf("Kontak dalam Circular Linked List:\n");
                displayCircularList(clHead);
                printf("\nTekan Enter untuk kembali ke menu utama...");
                getchar();
                getchar();
                break;
            case 4:
               system("cls");
       printf("===============================\n");
       printf("      Menu Edit Kontak      \n");
       printf("===============================\n");
       editContact(&q, clHead);
       break;

            case 5:
                if (!isQueueEmpty(&q)) {
                    Contact deleted = dequeue(&q);
                    push(&history, deleted);
                    printf("Kontak '%s' berhasil dihapus...\n", deleted.name);
                } else {
                    printf("Tidak ada kontak untuk dihapus...\n");
                }
                printf("\nTekan Enter untuk kembali ke menu utama...");
                getchar();
                getchar();
                break;
            case 6:
                printf("\nKeluar dari program...\n");
                break;
            default:
                printf("\nPilihan anda tidak valid, coba kembali...");
                getchar();
                getchar();
                break;
        }
    } while (choice != 6);
}

int main() {
    menu();
    return 0;
}