#include <iostream>
using namespace std;

struct node {
    int nim;
    char nama[50];
    int nilai;
    node* next;
};

node* head = nullptr;
node* tail = nullptr;

int* nilaiArr = new int[2];
int jumlah = 0;
int kapasitas = 2;

void tambahNilai(int nilai) {
    if (jumlah == kapasitas) {
        kapasitas = kapasitas * 2;
        int* baru = new int[kapasitas];
        for (int i = 0; i < jumlah; i++) {
            baru[i] = nilaiArr[i];
        }
        delete[] nilaiArr;
        nilaiArr = baru;
    }
    nilaiArr[jumlah] = nilai;
    jumlah++;
}

void tambahMahasiswa() {
    node* baru = new node();
    cout << "NIM   : ";
    cin >> baru->nim;
    cout << "Nama  : ";
    cin.ignore();
    cin.getline(baru->nama, 50);
    cout << "Nilai : ";
    cin >> baru->nilai;
    baru->next = nullptr;

    if (head == nullptr) {
        head = baru;
        tail = baru;
    } else {
        tail->next = baru;
        tail = baru;
    }

    tambahNilai(baru->nilai);
}

void tampilMahasiswa() {
    node* temp = head;
    while (temp != nullptr) {
        cout << temp->nim << " | " << temp->nama << " | " << temp->nilai << endl;
        temp = temp->next;
    }
}

void tampilNilai(int data[], int n) {
    for (int i = 0; i < n; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

void insertionSort(int data[], int n) {
    for (int i = 1; i < n; i++) {
        int key = data[i];
        int j = i - 1;

        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

node* linearSearch(int target) {
    node* temp = head;
    while (temp != nullptr) {
        if (temp->nim == target) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

int binarySearch(int data[], int n, int target) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (data[mid] == target) {
            return mid;
        } else if (target < data[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

int main() {
    int banyak;

    cout << "=== INPUT DATA ===" << endl;
    cout << "Jumlah mahasiswa : ";
    cin >> banyak;

    for (int i = 1; i <= banyak; i++) {
        cout << "--------------------" << endl;
        cout << "Mahasiswa ke-" << i << endl;
        tambahMahasiswa();
    }

    cout << endl << "=== DATA MAHASISWA ===" << endl;
    cout << "NIM | Nama | Nilai" << endl;
    cout << "--------------------" << endl;
    tampilMahasiswa();

    cout << endl << "=== NILAI SEBELUM DIURUTKAN ===" << endl;
    tampilNilai(nilaiArr, jumlah);

    insertionSort(nilaiArr, jumlah);
    cout << endl << "=== NILAI SETELAH DIURUTKAN ===" << endl;
    tampilNilai(nilaiArr, jumlah);

    int nimCari;
    cout << endl << "=== CARI NIM ===" << endl;
    cout << "Masukkan NIM : ";
    cin >> nimCari;
    node* hasil = linearSearch(nimCari);
    if (hasil != nullptr) {
        cout << "Ditemukan : " << hasil->nim << " | " << hasil->nama
             << " | " << hasil->nilai << endl;
    } else {
        cout << "Data tidak ditemukan" << endl;
    }

    int nilaiCari;
    cout << endl << "=== CARI NILAI (Binary Search) ===" << endl;
    cout << "Masukkan nilai : ";
    cin >> nilaiCari;
    int idx = binarySearch(nilaiArr, jumlah, nilaiCari);
    if (idx != -1) {
        cout << "Data ditemukan pada indeks : " << idx << endl;
    } else {
        cout << "Data tidak ditemukan" << endl;
    }

}