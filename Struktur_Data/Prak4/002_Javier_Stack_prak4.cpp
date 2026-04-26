#include <iostream>

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

struct PlayerData {
    string playerName;
    int playerScore;
    double playerAcc;

    PlayerData *next;
};

PlayerData *head = nullptr;

void initProgram(string namaPlayer, int skorPlayer, double akurasiPlayer) {
    PlayerData *newPlayer = new PlayerData;

    newPlayer->playerName = namaPlayer;
    newPlayer->playerScore = skorPlayer;
    newPlayer->playerAcc = akurasiPlayer;
    
    newPlayer->next = head;
    head = newPlayer;
}

void SplitList(PlayerData* source, PlayerData** frontRef, PlayerData** backRef) {
    PlayerData* fast;
    PlayerData* slow;

    slow = source;
    fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

PlayerData* MergeScore(PlayerData* a, PlayerData* b) {
    PlayerData* result = nullptr;

    if (a == nullptr) return b;
    else if (b == nullptr) return a;

    if (a->playerScore >= b->playerScore) { // Urutan skor terbesar
        result = a;
        result->next = MergeScore(a->next, b);
    } else {
        result = b;
        result->next = MergeScore(a, b->next);
    }

    return result;
}

PlayerData* MergeAcc(PlayerData* a, PlayerData* b) {
    PlayerData* result = nullptr;

    if (a == nullptr) return b;
    else if (b == nullptr) return a;

    if (a->playerAcc >= b->playerAcc) { // Urutan akurasi terbesar
        result = a;
        result->next = MergeAcc(a->next, b);
    } else {
        result = b;
        result->next = MergeAcc(a, b->next);
    }

    return result;
}

void MergeSort(PlayerData** headRef, bool sortByScore) {
    PlayerData* headPtr = *headRef;
    PlayerData *a, *b;

    if ((headPtr == nullptr) || (headPtr->next == nullptr)) return;

    SplitList(headPtr, &a, &b);
    MergeSort(&a, sortByScore);
    MergeSort(&b, sortByScore);

    if (sortByScore) *headRef = MergeScore(a, b);
    else *headRef = MergeAcc(a, b);
}

void DisplayList() {
    PlayerData* temp = head;

    cout << "\nRank\tNama\t\tSkor\tAkurasi" << endl;
    int rank = 1;

    while (temp != nullptr) {
        cout << rank++ << "\t" << temp->playerName << "\t" << temp->playerScore << "\t" << temp->playerAcc << "%" << endl;
        temp = temp->next;
    }
    cout << "======================================" << endl;

    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

void SortByScore() {
    MergeSort(&head, true);
    cout << "\n[Sistem]: Berhasil mengurutkan berdasarkan Skor." << endl;
    DisplayList();
}

void SortByAccuracy() {
    MergeSort(&head, false);
    cout << "\n[Sistem]: Berhasil mengurutkan berdasarkan Akurasi." << endl;
    DisplayList();
}

int main() {
    initProgram("lifeline", 506496, 99.06);
    initProgram("Hakui Koyori", 545064, 98.71);
    initProgram("GNX     ", 386827, 97.98);
    initProgram("MineFrostID", 581780, 98.93);
    int pilih = 0;

    while (true) {
        clearScreen();
        cout << "======================================" << endl;
        cout << "           SELAMAT DATANG" << endl;
        cout << "======================================" << endl;
        cout << "(Data sudah tersedia)" << endl;
        cout << "|1. Urutkan berdasarkan skor" << endl;
        cout << "|2. Urutkan berdasarkan akurasi" << endl;
        cout << "|0. Keluar" << endl;
        cout << "> ";
        cin >> pilih;
    
        if (pilih == 1) {
            SortByScore();
        } else if (pilih == 2) {
            SortByAccuracy();
        } else if (pilih == 0) {
            return 0;
        }
    }
    return 0;
}
