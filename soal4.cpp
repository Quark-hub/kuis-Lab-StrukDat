#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int TABLE_SIZE = 20;

class HashTable {
    private:
        vector <pair<int, string>> table;
        vector <int> status; 

        int hash1 (int key) {
            return key % TABLE_SIZE;
        }

        int hash2 (int key) {
            return 19 - (key % 19);
        }

    public:
        HashTable() {
            table.resize(TABLE_SIZE);
            status.resize(TABLE_SIZE, 0);
        }

        void insert (int key, string value) {
            int index = hash1(key);
            int step = hash2(key);
            int initialIndex = index;

            int deletedIndex = -1;

            while (true) {
                if (status[index] == 1 && table[index].first == key) {
                    table[index].second = value;
                    cout << "NIM " << key << " sudah ada, nama diperbarui" << endl;
                    return;
                }

                if (status[index] == 2 && deletedIndex == -1) {
                    deletedIndex = index;
                }

                if (status[index] == 0) {
                    if (deletedIndex != -1) {
                        index = deletedIndex;
                    }

                    table[index] = make_pair(key, value);
                    status[index] = 1;
                    tampilInsert(key, hash1(key), index);
                    return;
                }

                index = (index + step) % TABLE_SIZE;

                if (index == initialIndex) {
                    break;
                }
            }

            if (deletedIndex != -1) {
                table[deletedIndex] = make_pair(key, value);
                status[deletedIndex] = 1;
                tampilInsert(key, hash1(key), deletedIndex);
            } else {
                cout << "Table penuh, NIM " << key << " gagal disimpan" << endl;
            }
        }

        void tampilInsert(int key, int indexAwal, int indexAkhir) {
            cout << "Insert " << key << " -> indeks " << indexAkhir;
            if (indexAwal != indexAkhir) {
                cout << "  (COLLISION, indeks awal " << indexAwal << ")";
            }
            cout << endl;
        }

        void search(int key) {
            int index = hash1(key);
            int step = hash2(key);
            int initialIndex = index;

            while (status[index] != 0) {
                if (status[index] == 1 && table[index].first == key) {
                    cout << "Data ditemukan pada indeks " << index
                         << " : " << table[index].second << endl;
                    return;
                }

                index = (index + step) % TABLE_SIZE;

                if (index == initialIndex) {
                    break;
                }
            }

            cout << "Data tidak ditemukan" << endl;
        }

        void remove (int key) {
            int index = hash1(key);
            int step = hash2(key);
            int initialIndex = index;

            while (status[index] != 0) {
                if (status[index] == 1 && table[index].first == key) {
                    status[index] = 2;
                    cout << "Data berhasil dihapus dari indeks " << index << endl;
                    return;
                }

                index = (index + step) % TABLE_SIZE;

                if (index == initialIndex) {
                    break;
                }
            }

            cout << "Data tidak ditemukan" << endl;
        }

        void display() {
            for (int i = 0; i < TABLE_SIZE; i++) {
                cout << i << " : ";

                if (status[i] == 1) {
                    cout << table[i].first << " - " << table[i].second;
                } else if (status[i] == 2) {
                    cout << "DELETED";
                } else {
                    cout << "EMPTY";
                }

                cout << endl;
            }
        }
};

int main() {
    HashTable ht;

    cout << "=== INSERT 15 DATA MAHASISWA ===" << endl;
    ht.insert(251401001, "Andi");
    ht.insert(251401021, "Budi");
    ht.insert(251401041, "Citra");
    ht.insert(251401005, "Dewi");
    ht.insert(251401025, "Eka");
    ht.insert(251401010, "Fajar");
    ht.insert(251401030, "Gita");
    ht.insert(251401012, "Hadi");
    ht.insert(251401019, "Indah");
    ht.insert(251401039, "Joko");
    ht.insert(251401003, "Kiki");
    ht.insert(251401061, "Lina");
    ht.insert(251401032, "Mira");
    ht.insert(251401008, "Nanda");
    ht.insert(251401028, "Oki");

    cout << endl << "=== ISI HASH TABLE ===" << endl;
    ht.display();

    cout << endl << "=== SEARCH ===" << endl;
    cout << "Cari NIM 251401041 : ";
    ht.search(251401041);
    cout << "Cari NIM 251401099 : ";
    ht.search(251401099);

    cout << endl << "=== REMOVE ===" << endl;
    cout << "Hapus NIM 251401021 : ";
    ht.remove(251401021);
    cout << "Hapus NIM 251401099 : ";
    ht.remove(251401099);

    cout << endl << "=== SEARCH SETELAH REMOVE ===" << endl;
    cout << "Cari NIM 251401021 : ";
    ht.search(251401021);
    cout << "Cari NIM 251401041 : ";
    ht.search(251401041);

    cout << endl << "=== HASH TABLE SETELAH PENGHAPUSAN ===" << endl;
    ht.display();

    cout << endl << "=== INSERT ULANG (pakai slot DELETED) ===" << endl;
    ht.insert(251401401, "Qori");

    cout << endl << "=== HASH TABLE AKHIR ===" << endl;
    ht.display();

}