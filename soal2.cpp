#include <iostream>
using namespace std;

struct Antrean {
    char nama[50];
    Antrean* next;
};

Antrean* front = nullptr;
Antrean* rear = nullptr;

void enqueue(char nama[]) {
    Antrean* baru = new Antrean();
    int i = 0;
    while (nama[i] != '\0') {
        baru->nama[i] = nama[i];
        i++;
    }
    baru->nama[i] = '\0';
    baru->next = nullptr;

    if (front == nullptr) {
        front = baru;
        rear = baru;
    } else {
        rear->next = baru;
        rear = baru;
    }
}

struct Riwayat {
    char nama[50];
    int idBuku;
    Riwayat* next;
};

Riwayat* top = nullptr;

void push(char nama[], int idBuku) {
    Riwayat* baru = new Riwayat();
    int i = 0;
    while (nama[i] != '\0') {
        baru->nama[i] = nama[i];
        i++;
    }
    baru->nama[i] = '\0';
    baru->idBuku = idBuku;
    baru->next = top;
    top = baru;
}

struct Buku {
    int id;
    Buku* kiri;
    Buku* kanan;
};

Buku* insert(Buku* root, int id) {
    if (root == NULL) {
        Buku* baru = new Buku();
        baru->id = id;
        baru->kiri = NULL;
        baru->kanan = NULL;
        return baru;
    }
    if (id < root->id)
        root->kiri = insert(root->kiri, id);
    else if (id > root->id)
        root->kanan = insert(root->kanan, id);
    return root;
}

bool cari(Buku* root, int id) {
    if (root == NULL) return false;
    if (id == root->id) return true;
    if (id < root->id) return cari(root->kiri, id);
    return cari(root->kanan, id);
}

void preOrder(Buku* root) {
    if (root != NULL) {
        cout << root->id << " ";
        preOrder(root->kiri);
        preOrder(root->kanan);
    }
}

void inOrder(Buku* root) {
    if (root != NULL) {
        inOrder(root->kiri);
        cout << root->id << " ";
        inOrder(root->kanan);
    }
}

void postOrder(Buku* root) {
    if (root != NULL) {
        postOrder(root->kiri);
        postOrder(root->kanan);
        cout << root->id << " ";
    }
}

int main() {
    int banyak;
    char nama[50];

    cout << "=== INPUT ANTREAN PEMINJAMAN ===" << endl;
    cout << "Jumlah mahasiswa antre : ";
    cin >> banyak;
    cin.ignore();
    for (int i = 1; i <= banyak; i++) {
        cout << "Nama mahasiswa ke-" << i << " : ";
        cin.getline(nama, 50);
        enqueue(nama);
    }

    cout << endl << "=== INPUT RIWAYAT PENGEMBALIAN ===" << endl;
    cout << "Jumlah pengembalian : ";
    cin >> banyak;
    for (int i = 1; i <= banyak; i++) {
        int idBuku;
        cout << "--------------------" << endl;
        cout << "Pengembalian ke-" << i << endl;
        cout << "Nama    : ";
        cin.ignore();
        cin.getline(nama, 50);
        cout << "ID Buku : ";
        cin >> idBuku;
        push(nama, idBuku);
    }

    Buku* root = NULL;
    cout << endl << "=== INPUT ID BUKU ===" << endl;
    cout << "Jumlah buku : ";
    cin >> banyak;
    for (int i = 1; i <= banyak; i++) {
        int id;
        cout << "ID buku ke-" << i << " : ";
        cin >> id;
        root = insert(root, id);
    }

    cout << endl << "=== ANTREAN PEMINJAMAN ===" << endl;
    Antrean* temp = front;
    cout << "Isi antrean : ";
    while (temp != nullptr) {
        cout << temp->nama;
        if (temp->next != nullptr) cout << " -> ";
        temp = temp->next;
    }
    cout << endl;
    if (front != nullptr) {
        cout << "Front : " << front->nama << endl;
        cout << "Rear  : " << rear->nama << endl;
    }

    cout << "--------------------" << endl;
    cout << "Proses peminjaman :" << endl;
    while (front != nullptr) {
        Antrean* hapus = front;
        cout << "Dequeue : " << front->nama << " meminjam buku" << endl;
        front = front->next;
        delete hapus;
    }
    cout << "Antrean sekarang kosong" << endl;

    cout << endl << "=== RIWAYAT PENGEMBALIAN ===" << endl;
    Riwayat* t = top;
    int size = 0;
    while (t != nullptr) {
        cout << t->nama << " | ID Buku " << t->idBuku << endl;
        size++;
        t = t->next;
    }
    if (top != nullptr) {
        cout << "--------------------" << endl;
        cout << "Top  : " << top->nama << " | ID Buku " << top->idBuku << endl;
        cout << "Size : " << size << endl;
    }

    cout << endl << "=== ID Buku ===" << endl;
    cout << "Pre Order  : ";
    preOrder(root);
    cout << endl;
    cout << "In Order   : ";
    inOrder(root);
    cout << endl;
    cout << "Post Order : ";
    postOrder(root);
    cout << endl;

    int idCari;
    cout << endl << "=== CARI ID BUKU ===" << endl;
    cout << "Masukkan ID buku : ";
    cin >> idCari;
    if (cari(root, idCari))
        cout << "ID buku ditemukan" << endl;
    else
        cout << "ID buku tidak ditemukan" << endl;

}