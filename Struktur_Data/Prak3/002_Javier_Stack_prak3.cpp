#include <iostream>
#include <ctime>
using namespace std;

struct bookshelf {
    string id;
    string title;
    string author;
    int year;
    string genre;
    bool available;

    bookshelf *next;
    bookshelf *prev;
};

bookshelf *head = nullptr;

struct book_borrow_data {
    string id;
    string BookID;
    string title;
    string name;
    long long NIM;
    string date;

    book_borrow_data *next;
    book_borrow_data *prev;
};

book_borrow_data *headHistoryBorrowedBook = nullptr;
book_borrow_data *headReturnBook = nullptr;

book_borrow_data *front = nullptr;
book_borrow_data *rear = nullptr;
int urutanPinjaman = 1;

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[80];
    strftime(buf, sizeof(buf), "%d %B %Y %H:%M", ltm);
    return string(buf);
}

string generateBorrowID(bookshelf *b, string name) {
    time_t now = time(0);
    tm* LocalTime = localtime(&now);
    string TwoDigitYear = to_string(LocalTime->tm_year);

    string id = b->id;

    id += (char)tolower(b->genre[0]);

    id += (to_string(LocalTime->tm_year)).substr(1, 2);

    id += (char)tolower(name[0]);
    id += (char)tolower(name[1]);

    if (urutanPinjaman < 10) {
        id += "0" + to_string(urutanPinjaman);
        urutanPinjaman++;
    } else {
        id += to_string(urutanPinjaman);
        urutanPinjaman++;
    };

    return id;
}

string generateIDBook(string title, int year) {
    int titleID = abs(int(title[title.length() - 1]) - int(title[0]));
    string realTitleID = (titleID < 10) ? "0" + to_string(titleID) : to_string(titleID).substr(0,2);
    
    int yearID = 0;
    while (year > 0) {
        yearID += year % 10;
        year /= 10;
    }
    
    int increment = 0;
    bookshelf *curr = head;
    
    while (true) {
        string currentCheck = realTitleID + to_string(yearID) + to_string(increment);
        bool found = false;
        
        if (head != nullptr) {
            bookshelf *temp = head;
            do {
                if (temp->id == currentCheck) {
                    found = true;
                    break;
                }
                temp = temp->next;
            } while (temp != head);
        }

        if (found) {
            increment++;
        } else {
            return realTitleID + to_string(abs(yearID)) + to_string(increment);
        };
    }
}

void initProgram(string judul, string author, int tahun, string genre) {
    bookshelf *newBook = new bookshelf;

    newBook->title = judul;
    newBook->author = author;
    newBook->year = tahun;
    newBook->genre = genre;

    newBook->id = generateIDBook(newBook->title, newBook->year);
    newBook->available = true;

    if (head == nullptr) {
        head = newBook;
        newBook->next = head;
        newBook->prev = head;
    } else {
        bookshelf *tail = head->prev;
        
        tail->next = newBook;
        newBook->prev = tail;
        newBook->next = head;
        head->prev = newBook;
    }
}

void addBook() {
    bookshelf *newBook = new bookshelf;

    system("cls");
    cout << "======================================\n"
            "              TAMBAH BUKU\n"
            "======================================\n";
    cout << "Masukkan data buku" << endl;
    cout << "Judul : > ";
    cin.ignore(); getline(cin, newBook->title);
    cout << "Penulis : > ";
    getline(cin, newBook->author);
    cout << "Tahun : > ";
    cin >> newBook->year;
    cout << "Genre : > ";
    cin.ignore(); getline(cin, newBook->genre);

    newBook->id = generateIDBook(newBook->title, newBook->year);
    newBook->available = true;

    if (head == nullptr) {
        head = newBook;
        newBook->next = head;
        newBook->prev = head;
    } else {
        bookshelf *tail = head->prev;
        
        tail->next = newBook;
        newBook->prev = tail;
        newBook->next = head;
        head->prev = newBook;
    }

    cout << "Buku berhasil ditambahkan dengan ID: " << newBook->id << endl;
    cout << "Tekan enter untuk melanjutkan...";
    cin.get();
}

void viewBook() {
    if (head == nullptr) {
        system("cls");
        cout << "======================================\n"
                "              DAFTAR BUKU\n"
                "======================================\n";
        cout << "Daftar buku kosong..." << endl;
        cout << "Tekan enter untuk melanjutkan...";
        cin.ignore(); cin.get();
    } else {
        bookshelf *curr = head;
        int pilih;

        do {
            system("cls");
            cout << "======================================\n"
                    "              DAFTAR BUKU\n"
                    "======================================\n";
            cout << "\n--------------------------------------" << endl;
            cout << "| Judul         : " << curr->title << endl;
            cout << "| Id            : " << curr->id << endl;
            cout << "| Penulis       : " << curr->author << endl;
            cout << "| Tahun         : " << curr->year << endl;
            cout << "| Genre         : " << curr->genre << endl;
            cout << "| Ketersediaan  : " << (curr->available ? "Tersedia" : "Dipinjam") << endl;
            cout << "--------------------------------------" << endl;
            cout << "1. Selanjutnya" << endl;
            cout << "2. Sebelumnya" << endl;
            cout << "0. Keluar" << endl;
            cout << "> "; cin >> pilih;

            if (pilih == 1) {
                curr = curr->next;
            } else if (pilih == 2) {
                curr = curr->prev;
            }
        } while (pilih != 0);
    }
}

void editBook() {
    if (head == nullptr) {
        system("cls");
        cout << "======================================\n"
                "               UBAH BUKU\n"
                "======================================\n";
        cout << "Data buku kosong..." << endl;
        cout << "Tekan enter untuk melanjutkan...";
        cin.ignore(); cin.get();
        return;
    } else {
        string targetID;
        system("cls");
        cout << "======================================\n"
                "               UBAH BUKU\n"
                "======================================\n";
        cout << "Masukkan Id Buku yang ingin diubah > ";
        cin >> targetID;

        bookshelf *curr = head;
        bool found = false;
        do {
            if (curr->id == targetID) {
                found = true;
                break;
            }
            curr = curr->next;
        } while (curr != head);

        if (!found) {
            cout << "Buku dengan Id " << targetID << " tidak ditemukan." << endl;
            cout << "Tekan enter untuk melanjutkan...";
            cin.ignore(); cin.get();
            return;
        }

        int pilih;
        bool idPerluUpdate = false;
        bool isNowChanging = false;

        do {
            system("cls");
            cout << "======================================\n"
                    "               UBAH BUKU\n"
                    "======================================\n";
            cout << "- Mengubah buku dengan Id " << curr->id << " -" << endl;
            cout << "|1. Ubah judul" << endl;
            cout << "|2. Ubah penulis" << endl;
            cout << "|3. Ubah tahun" << endl;
            cout << "|4. Ubah genre" << endl;
            cout << "|0. Kembali" << endl;
            cout << "> "; cin >> pilih;

            switch (pilih) {
                case 1:
                    isNowChanging = true;
                    cout << "Masukkan judul buku baru > ";
                    cin.ignore(); getline(cin, curr->title);
                    idPerluUpdate = true;
                    break;
                case 2:
                    isNowChanging = true;
                    cout << "Masukkan nama penulis baru > ";
                    cin.ignore(); getline(cin, curr->author);
                    break;
                case 3:
                    isNowChanging = true;
                    cout << "Masukkan tahun terbit baru > ";
                    cin >> curr->year;
                    idPerluUpdate = true;
                    break;
                case 4:
                    isNowChanging = true;
                    cout << "Masukkan genre baru > ";
                    cin.ignore(); getline(cin, curr->genre);
                    break;
                case 0:
                    isNowChanging = false;
                    return;
            }

            if (isNowChanging) {
                system("cls");
                cout << "======================================\n"
                        "               UBAH BUKU\n"
                        "======================================\n";
                if (idPerluUpdate) {
                    string oldID = curr->id;
                    curr->id = "";
                    curr->id = generateIDBook(curr->title, curr->year);
                    cout << "Data Id " << oldID << " telah berubah menjadi " << curr->id << " !" << endl;
                    idPerluUpdate = false; 
                } else {
                    cout << "Data Id " << curr->id << " telah berubah !";
                }
    
                cout << "\n--------------------------------------" << endl;
                cout << "| Judul         : " << curr->title << endl;
                cout << "| Id            : " << curr->id << endl;
                cout << "| Penulis       : " << curr->author << endl;
                cout << "| Tahun         : " << curr->year << endl;
                cout << "| Genre         : " << curr->genre << endl;
                cout << "| Ketersediaan  : " << (curr->available ? "Tersedia" : "Dipinjam") << endl;
                cout << "--------------------------------------" << endl;
                isNowChanging = false;
                cout << "Tekan enter untuk melanjutkan...";
                cin.ignore(); cin.get();
            }
        } while (pilih != 0);
    }
}

void deleteBook() {
    if (head == nullptr) {
        system("cls");
        cout << "======================================\n"
                "             HAPUS BUKU\n"
                "======================================\n";
        cout << "Tidak ada data buku yang bisa dihapus..." << endl;
        cout << "Tekan enter untuk melanjutkan...";
        cin.ignore(); cin.get();
        return;
    }
    system("cls");
    cout << "======================================\n"
            "              HAPUS BUKU\n"
            "======================================\n";

    string target;
    cout << "Masukkan ID Buku yang ingin dihapus > ";
    cin >> target;

    bookshelf *curr = head;
    bool found = false;

    do {
        if (curr->id == target) {
            found = true;
            char pilih;

            cout << "\n- Detail Buku -" << endl;
            cout << "--------------------------------------" << endl;
            cout << "| Judul         : " << curr->title << endl;
            cout << "| Id            : " << curr->id << endl;
            cout << "| Penulis       : " << curr->author << endl;
            cout << "| Tahun         : " << curr->year << endl;
            cout << "| Genre         : " << curr->genre << endl;
            cout << "--------------------------------------" << endl;
            
            cout << "Yakin ingin menghapus buku " << curr->title << " ? (y/n) > ";
            cin >> pilih;
            if (pilih == 'y' || pilih == 'Y') {
                if (curr == head && curr->next == head) {
                    head = nullptr;
                } else {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    if (curr == head) head = curr->next;
                }
                delete curr;

                system("cls");
                cout << "======================================\n"
                        "              HAPUS BUKU\n"
                        "======================================\n";
                cout << "Buku berhasil dihapus!" << endl;
                cout << "Tekan enter untuk melanjutkan...";
                cin.ignore(); cin.get();
            }
            return;
        }
        curr = curr->next;
    } while (curr != head);
    if (!found) {
        cout << "ID tidak ditemukan." << endl;
        cout << "Tekan enter untuk melanjutkan...";
        cin.ignore(); cin.get();
    }
}

void addToHistory(book_borrow_data *data) {
    data->next = nullptr;
    data->prev = nullptr;

    if (headHistoryBorrowedBook == nullptr) {
        headHistoryBorrowedBook = data;
    } else {
        book_borrow_data *temp = headHistoryBorrowedBook;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = data;
        data->prev = temp;
    }
}

void approvalBorrowBook() {
    int choice;
    int counter = 1;
    bool isBorrowed = false;

    do {
        if (front == nullptr) {
            system("cls");
            cout << "======================================" << endl;
            cout << "          PERMINTAAN PINJAMAN" << endl;
            cout << "======================================" << endl;
            cout << "Tidak ada pinjaman untuk diproses!!" << endl;
            cout << "Tekan apapun untuk melanjutkan..." << endl;
            system("pause>nul");
            return;
        }

        system("cls");
        cout << "======================================" << endl;
        cout << "          PERMINTAAN PINJAMAN" << endl;
        cout << "======================================" << endl;
        cout << "PINJAMAN KE-" << counter << endl;
        cout << "--------------------------------------" << endl;
        cout << "| Id      : " << front->id << endl;
        cout << "| Judul   : " << front->title << endl;
        cout << "| Nama    : " << front->name << endl;
        cout << "| NIM     : " << front->NIM << endl;
        cout << "| Tanggal : " << front->date << endl;
        cout << "--------------------------------------" << endl;
        cout << "1. Setujui\n";
        cout << "2. Tolak\n";
        cout << "0. Keluar\n> ";
        cin >> choice;
    
        if (choice == 1 || choice == 2) {
            book_borrow_data *hapus = front;

            if (choice == 1) {
                bookshelf *temp = head;
                do {
                    if (temp->id == front->BookID) {
                        if (temp->available == false) {
                            isBorrowed = true;
                            delete hapus;
                            break;
                        } else {
                            isBorrowed = false;
                            temp->available = false;
                            
                            book_borrow_data *approved = front;
                            
                            addToHistory(approved);
                            break;
                        }
                    }
                    temp = temp->next;
                } while (temp != head);
            } else if (choice == 2) {
                delete hapus;
                break;
            }
    
            system("cls");
            cout << "======================================" << endl;
            cout << "          PERMINTAAN PINJAMAN" << endl;
            cout << "======================================\n" << endl;
            if (isBorrowed) {
                cout << "Buku telah dipinjam oleh mahasiswa lain!" << endl;
            }
            cout << "Pinjaman dengan id " << hapus->id << " telah diproses !!" << endl;
            front = front->next;
            if (front == nullptr) rear = nullptr;
            // delete hapus;
            counter++;
            
            cout << "Tekan enter untuk melanjutkan...";
            cin.ignore(); cin.get();
        }
    } while (choice != 0);
}

void processReturn() {
    int choice;
    int counter = 1;

    do {
        if (headReturnBook == nullptr) {
            system("cls");
            cout << "======================================\n"
                    "           PENGEMBALIAN BUKU\n"
                    "======================================\n";
            cout << "Tidak ada pengembalian untuk diproses !!" << endl;
            cout << "Tekan enter untuk melanjutkan...";
            cin.ignore(); cin.get();
            return;
        }

        book_borrow_data *toProcess = headReturnBook;
        headReturnBook = headReturnBook->next;

        system("cls");
        cout << "======================================\n"
                "           PENGEMBALIAN BUKU\n"
                "======================================\n";
        cout << "PENGEMBALIAN KE-" << counter << endl;
        cout << "--------------------------------------" << endl;
        cout << "| Id      : " << toProcess->id << endl;
        cout << "| Judul   : " << toProcess->title << endl;
        cout << "| Nama    : " << toProcess->name << endl;
        cout << "| NIM     : " << toProcess->NIM << endl;
        cout << "| Tanggal : " << toProcess->date << endl;
        cout << "--------------------------------------" << endl;
        cout << "1. Proses\n"
                "0. Keluar\n"
                "> ";
        cin >> choice;
    
        if (choice == 1) {
            bookshelf *temp = head;
            do {
                if (temp->id == toProcess->BookID) {
                    temp->available = true;
                    break;
                }
                temp = temp->next;
            } while (temp != head);
    
            cout << "Buku \"" << toProcess->title << "\" telah dikembalikan !!\n";
            cout << "Tekan enter untuk melanjutkan...";
            cin.ignore(); cin.get();
            counter++;
            delete toProcess;
        } else {
            toProcess->next = headReturnBook;
            headReturnBook = toProcess;
        }
    } while (choice != 0);
}

void dashboardEmploy() {
    int pilih = -1;

    while (true) {
        system("cls");
        cout << "======================================\n"
                "            DASHBOARD ADMIN\n"
                "======================================\n"
                "|1. Menambah Data Buku\n"
                "|2. Tampilkan Data Buku\n"
                "|3. Mengubah Data Buku\n"
                "|4. Menghapus Data Buku\n"
                "|5. Proses Permintaan Pinjaman\n"
                "|6. Proses Pengembalian Buku\n"
                "|0. Keluar\n"
                "> ";
        cin >> pilih;
    
        switch (pilih) {
            case 1:
                addBook();
                break;
            case 2:
                viewBook();
                break;
            case 3:
                editBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                approvalBorrowBook();
                break;
            case 6:
                processReturn();
                break;
            case 0:
                return;
        }
    }
}

void borrowBook(bookshelf *book) {
    book_borrow_data *DataBaru = new book_borrow_data;

    cout << "\nMasukkan nama peminjam > ";
    cin.ignore(); getline(cin, DataBaru->name);
    cout << "Masukkan NIM peminjam > ";
    cin.ignore(); cin >> DataBaru->NIM;

    DataBaru->id = generateBorrowID(book, DataBaru->name);
    DataBaru->title = book->title;
    DataBaru->date = getCurrentDate();
    DataBaru->BookID = book->id;
    DataBaru->next = nullptr;

    if (rear == nullptr) {
        front = rear = DataBaru;
    } else {
        rear->next = DataBaru;
        rear = DataBaru;
    }

    system("cls");
    cout << "======================================\n"
            "         DASHBOARD PENGUNJUNG\n"
            "======================================\n";
    cout << "Permintaan pinjaman telah berhasil dibuat !!" << endl;
    cout << "--------------------------------------" << endl;
    cout << "| Id      : " << DataBaru->id << endl;
    cout << "| Judul   : " << DataBaru->title << endl;
    cout << "| Nama    : " << DataBaru->name << endl;
    cout << "| NIM     : " << DataBaru->NIM << endl;
    cout << "| Tanggal : " << DataBaru->date << endl;
    cout << "--------------------------------------" << endl;
    cout << "Menunggu persetujuan pegawai...\n" << endl;

    cout << "Tekan enter untuk melanjutkan...";
    cin.ignore(); cin.get();
}

void viewBookselfGuest() {
    bookshelf *curr = head;
    int pilih = -1;

    if (head == nullptr) {
        system("cls");
        cout << "======================================\n"
                "         DASHBOARD PENGUNJUNG\n"
                "======================================\n";
        cout << "Daftar buku kosong..." << endl;
        cout << "Tekan enter untuk melanjutkan...";
        cin.ignore(); cin.get();
    } else {
        do {
            system("cls");
            cout << "======================================\n"
                    "         DASHBOARD PENGUNJUNG\n"
                    "======================================\n"
                    "Silahkan lihat-lihat buku yang tersedia!\n"
                    "--------------------------------------\n";
            cout << "| Judul         : " << curr->title << endl;
            cout << "| Id            : " << curr->id << endl;
            cout << "| Penulis       : " << curr->author << endl;
            cout << "| Tahun         : " << curr->year << endl;
            cout << "| Genre         : " << curr->genre << endl;
            cout << "| Ketersediaan  : " << (curr->available ? "Tersedia" : "Dipinjam") << endl;
            cout << "--------------------------------------\n"
                    "| 1. Selanjutnya\n"
                    "| 2. Sebelumnya\n"
                    "| 3. Pinjam\n"
                    "| 0. Keluar\n"
                    "> ";
            cin >> pilih;
    
             if (pilih == 1) {
                curr = curr->next;
            } else if (pilih == 2) {
                curr = curr->prev;
            } else if (pilih == 3) {
                borrowBook(curr);
            }
        } while (pilih != 0);
    }
}

void pushReturnStack(book_borrow_data *data) {
    data->next = headReturnBook;
    headReturnBook = data;
}

void viewHistory() {
    if (headHistoryBorrowedBook == nullptr) {
        system("cls");
        cout << "======================================\n"
                "         DASHBOARD PENGUNJUNG\n"
                "======================================\n";
        cout << "Daftar riwayat pinjaman kosong..." << endl;
        cout << "Tekan enter untuk melanjutkan...";
        cin.ignore(); cin.get();
        return;
    }

    book_borrow_data *curr = headHistoryBorrowedBook;
    int pilih;
    int confirm;

    do {
        system("cls");
        cout << "======================================\n"
                "         DASHBOARD PENGUNJUNG\n"
                "======================================\n";
        cout << "--------------------------------------\n";
        cout << "| Id      : " << curr->id << endl;
        cout << "| Judul   : " << curr->title << endl;
        cout << "| Nama    : " << curr->name << endl;
        cout << "| NIM     : " << curr->NIM << endl;
        cout << "| Tanggal : " << curr->date << endl;
        cout << "--------------------------------------\n";
        cout << "1. Selanjutnya\n"
                "2. Sebelumnya\n"
                "3. Kembalikan Buku\n"
                "0. Keluar\n"
                "> ";
        cin >> pilih;

        if (pilih == 1 && curr->next != nullptr) {
            curr = curr->next;
        } else if (pilih == 2 && curr->prev != nullptr) {
            curr = curr->prev;
        } else if (pilih == 3) {
            system("cls");
            cout << "======================================\n"
                    "         DASHBOARD PENGUNJUNG\n"
                    "======================================\n";
            cout << "Apakah Anda yakin ingin mengembalikan buku \"" << curr->title << "\"?\n"
                    "| 1. Ya\n"
                    "| 2. Tidak\n"
                    "> ";
            cin >> confirm;

            if (confirm == 1) {
                string daBook = "";
                daBook = curr->title;

                book_borrow_data *toReturn = curr;

                if (toReturn->prev != nullptr) {
                    toReturn->prev->next = toReturn->next;
                };
                
                if (toReturn->next != nullptr) {
                    toReturn->next->prev = toReturn->prev;
                };

                if (toReturn == headHistoryBorrowedBook) {
                    headHistoryBorrowedBook = toReturn->next;
                };

                if (curr->next != nullptr) {
                    curr = curr->next;
                } else if (curr->prev != nullptr) {
                    curr = curr->prev;
                } else {
                    curr = nullptr;
                };

                pushReturnStack(toReturn);
                cout << "Buku \"" << daBook << "\" telah dikembalikan !!" << endl;
                cout << "Tekan enter untuk melanjutkan...";
                cin.ignore(); cin.get();

                if (curr == nullptr) break;
            }
        };
    } while (pilih != 0);
}

void dashboardGuest() {
    int pilih = -1;

    while (true) {
        system("cls");
        cout << "======================================\n"
                "         DASHBOARD PENGUNJUNG\n"
                "======================================\n"
                "|1. Daftar Buku\n"
                "|2. Riwayat Pinjaman\n"
                "|0. Keluar\n"
                "> ";
        cin >> pilih;
    
        switch (pilih) {
            case 1:
                viewBookselfGuest();
                break;
            case 2:
                viewHistory();
                break;
            case 0:
                return;
        }
    }
}

int main() {
    initProgram("BUMI MANUSIA", "Pramoedya Ananta Toer", 1980, "Fiksi");
    initProgram("Jalanan", "Joko Kristian", 2020, "Non-fiksi");
    initProgram("Dia sangat manis", "Budi Setyawan", 2019, "Fiksi");
    initProgram("Tutorial Basic Java", "Devier", 2020, "Edukasi");
    initProgram("Terkadang... Merenung...", "Cahyadi VSync", 2015, "Non-Fiksi");
    int pilih = 0;

    while (true) {
        system("cls");
        cout << "======================================" << endl;
        cout << "           SELAMAT DATANG !!" << endl;
        cout << "======================================" << endl;
        cout << "|1. Masuk sebagai Pegawai" << endl;
        cout << "|2. Masuk sebagai Pengunjung" << endl;
        cout << "|0. Keluar" << endl;
        cout << "> ";
        cin >> pilih;
    
        if (pilih == 1) {
            dashboardEmploy();
        } else if (pilih == 2) {
            dashboardGuest();
        } else if (pilih == 0) {
            return 0;
        }
    }
    return 0;
}
