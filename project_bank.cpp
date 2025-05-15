#include <iostream>
#include <conio.h>
#include <iomanip>
#define max 10
using namespace std;

struct user
{
    string nama, email, password;
    int pin, UserId, noRekening;
    double balance;
    string mutasi[100]; //dipecah buat nampung data transaksi(nominal,no tujuan tf)
    int mutasi_count = 0;
};

int pengguna = 0, lastUserID = 0, lastNoRek = 123240000;
char ulang;
user user1[max];
double balance[max]; //ganti nama variabel

struct bank
{
    string namaBank;
    int kodeBank;
};

bank daftarBank[] = {
    {"Bank A", 101},
    {"Bank B", 102},
    {"Bank C", 103},
    {"Bank D", 104},
    {"Bank E", 105}};

void menu();
void daftar();
void cariBank();
void login(int kesempatan);
void inputPin();
void menuUtama(int UserID);
void setor(int UserID);
void tarik(int UserID);
void cariDataUser(int userID);
void dataUser(int UserID);
void transfer(int UserID);
void riwayat(string mutasi[], int mutasi_count);

int main()
{
    menu();
}

void menu()
{
    int pilihan;
    do
    {
        system("cls");
        cout << "+=======================+" << endl;
        cout << "|    Selamat Datang!    | " << endl;
        cout << "+=======================+" << endl;
        cout << "| 1. Daftar             |" << endl;
        cout << "| 2. Login              |" << endl;
        cout << "| 3. Cari Bank          |" << endl;
        cout << "| 4. Keluar             |" << endl;
        cout << "+=======================+" << endl;
        cout << "Pilih menu nomor : ";
        cin >> pilihan;
        cin.ignore();
        switch (pilihan)
        {
        case 1:
            daftar();
            break;
        case 2:
            login(3);
            break;
        case 3:
            cariBank();
            break;
        case 4:
            cout << "Terima Kasih Telah Menggunakan Program ini";
            exit(0);
            break;
        default:
            cout << "Pilihan tidak valid!";
        }
    } while (pilihan < 4);
}

void login(int kesempatan)
{
    system("cls");
    if (pengguna > 0)
    {
        string username;
        int pin;

        if (kesempatan == 0)
        {
            cout << "Kesempatan anda habis. Silahkan menghubungi call center!";
            getch();
            exit(0);
        }
        else
        {
            cout << "+=======================+" << endl;
            cout << "|         Login         | " << endl;
            cout << "+=======================+" << endl;
            cout << "Nama   : ";
            getline(cin, username);
            cout << "Pin    : ";
            cin >> pin;
            cin.ignore();
            cout << "+=======================+" << endl;

            bool valid = false;
            for (int i = 0; i < pengguna; i++)
            {
                if (username == user1[i].nama && pin == user1[i].pin)
                {
                    valid = true;
                    cout << "Selamat datang " << user1[i].nama << endl;
                    getch();
                    menuUtama(user1[i].UserId);
                    break;
                }
            }
            if (!valid)
            {
                if (kesempatan != 1)
                {
                    cout << "\nUsername atau Pin tidak ditemukan!!\nKesempatan anda tersisa " << kesempatan - 1 << " kali percobaan!";
                    getch();
                }
                login(kesempatan - 1);
            }
        }
    }
    else
    {
        cout << "!!! Tidak ada pengguna terdaftar. Silakan daftar terlebih dahulu !!!" << endl;
        getch();
        daftar();
    }
}

void daftar()
{
    char pilihan;
    do
    {
        system("cls");
        if (pengguna >= max)
        {
            cout << "Jumlah pengguna maksimum telah tercapai." << endl;
            getch();
            return;
        }

        lastUserID++;
        user1[pengguna].UserId = lastUserID;

        lastNoRek++;
        user1[pengguna].noRekening = lastNoRek;

        cout << "+===========================+" << endl;
        cout << "| Input Data Nasabah ke - " << pengguna + 1 << " | " << endl;
        cout << "+===========================+" << endl;
        cout << "User ID                : " << user1[pengguna].UserId << endl;
        cout << "Nomor Rekening         : " << user1[pengguna].noRekening << endl;
        cout << "Masukkan nama anda     : ";
        getline(cin, user1[pengguna].nama);
        cout << "Masukkan email anda    : ";
        cin >> user1[pengguna].email;
        cin.ignore();
        cout << "Masukkan password anda : ";
        getline(cin, user1[pengguna].password);
        inputPin();

        // Set saldo awal ke 50.000
        user1[pengguna].balance = 50000;
        balance[pengguna] = 50000;

        cout << "============================" << endl;
        pengguna++;

        cout << "Apakah anda ingin mendaftar lagi? (y/n): ";
        cin >> pilihan;
        cin.ignore();
    } while (pilihan == 'y' && pengguna < max);
}

void inputPin()
{
    cout << "Masukkan pin anda      : ";
    cin >> user1[pengguna].pin;
    cin.ignore();

    if (user1[pengguna].pin < 1000 || user1[pengguna].pin > 9999)
    {
        cout << "PIN harus 4 digit! Silahkan coba lagi" << endl;
        return inputPin();
    }
}

void cariBank()
{
    system("cls");
    string nama;

    cout << "+====================================+" << endl;
    cout << "|          Daftar Semua Bank         |" << endl;
    cout << "+====================================+" << endl;
    for (int i = 0; i < sizeof(daftarBank) / sizeof(daftarBank[0]); i++)
    {

        cout << "| " << "Nama Bank: " << daftarBank[i].namaBank << " | Kode Bank: " << daftarBank[i].kodeBank << " |" << endl;
    }
    cout << "+====================================+" << endl;
    cout << "Masukkan nama bank yang ingin dicari: ";
    getline(cin, nama);

    bool ditemukan = false;
    for (int i = 0; i < sizeof(daftarBank) / sizeof(daftarBank[0]); i++)
    {
        if (daftarBank[i].namaBank == nama)
        {
            cout << "Bank ditemukan!" << endl;
            cout << "Nama Bank: " << daftarBank[i].namaBank << endl;
            cout << "Kode Bank: " << daftarBank[i].kodeBank << endl;
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan)
    {
        cout << "Bank tidak ditemukan." << endl;
    }
    getch();
}

void menuUtama(int UserID)
{
    int pilihan;
    bool nabil = false;
    do
    {
        system("cls");
        cout << "+=======================+" << endl;
        cout << "|      MENU UTAMA!      | " << endl;
        cout << "+=======================+" << endl;
        cout << "| 1. Setor Tunai        |" << endl;
        cout << "| 2. Tarik Tunai        |" << endl;
        cout << "| 3. Transfer           |" << endl;
        cout << "| 4. Riwayat Transaksi  |" << endl;
        cout << "| 5. Tampilkan Data     |" << endl;
        cout << "| 6. Keluar             |" << endl;
        cout << "+=======================+" << endl;
        cout << "Pilih menu : ";
        cin >> pilihan;
        cin.ignore();
        switch (pilihan)
        {
        case 1:
            setor(UserID);
            nabil = false;
            break;
        case 2:
            tarik(UserID);
            nabil = false;
            break;
        case 3:
            transfer(UserID);
            nabil = false;
            break;
        case 4:
            riwayat(user1[UserID - 1].mutasi, user1[UserID - 1].mutasi_count); //index pertama disesuaikan
            nabil = false;
            break;
        case 5:
            dataUser(UserID);
            nabil = false;
            break;
        case 6:
            menu();
            nabil = true;
            break;
        default:
            cout << "Pilihan tidak valid!";
            nabil = false;
        }
    } while (nabil == false);
}

void setor(int UserID)
{
    int jumlah;
    cout << "Rekening Tujuan : " << user1[UserID - 1].noRekening << endl;
    cout << "Masukan jumlah setor tunai : Rp.";
    cin >> jumlah;
    if (jumlah > 0)
    {
        balance[UserID - 1] += jumlah;
        user1[UserID - 1].balance = balance[UserID - 1];
        user1[UserID - 1].mutasi[user1[UserID - 1].mutasi_count++] = "Setor tunai: +" + to_string(jumlah); //gausah to string, pake int biasa(nominal)
        cout << "Setor tunai berhasil. " << endl
             << endl;
    }
    else
    {
        cout << "Jumlah setor harus lebih dari 0. Silahkan coba lagi." << endl
             << endl;
        setor(UserID);
    }
    getch();
}

void tarik(int UserID)
{
    int jumlah;
    cout << "Masukan jumlah tarik tunai : Rp";
    cin >> jumlah;
    if (jumlah <= user1[UserID - 1].balance)
    {
        balance[UserID - 1] -= jumlah;
        user1[UserID - 1].balance = balance[UserID - 1];
        user1[UserID - 1].mutasi[user1[UserID - 1].mutasi_count++] = "Tarik tunai: -" + to_string(jumlah); //gausah to string, pake int biasa(nominal)
        cout << "Tarik tunai berhasil. " << endl
             << endl;
    }
    else
    {
        cout << "Saldo tidak mencukupi. " << endl
             << endl;
        getch();
        menuUtama(UserID);
    }
    getch();
}

void cariDataUser(int userID)
{
    bool found = false;
    int awal, tengah, akhir;

    awal = 0;
    akhir = pengguna - 1;

    while ((!found) && (awal <= akhir))
    {
        tengah = (awal + akhir) / 2;
        if (userID == user1[tengah].UserId)
        {
            found = true;
        }
        else
        {
            if (userID < user1[tengah].UserId)
            {
                akhir = tengah - 1;
            }
            else
            {
                awal = tengah + 1;
            }
        }
    }

    if (found)
    {
        cout << "Nomor Rekening     : " << user1[tengah].noRekening << endl;
        cout << "Nama               : " << user1[tengah].nama << endl;
        cout << "Email              : " << user1[tengah].email << endl;
        cout << "Password           : " << user1[tengah].password << endl;
        cout << "Pin                : " << user1[tengah].pin << endl;
        cout << fixed << setprecision(2) << "Saldo              : Rp. " << user1[tengah].balance << endl;
        // cout << "Mutasi Transaksi   : " << endl;
        // for (int i = 0; i < user1[tengah].mutasi_count; i++)
        // {
        //     cout << user1[tengah].mutasi[i] << endl;
        // }
    }
    else
    {
        cout << "Data user tidak ditemukan!";
    }
}

void dataUser(int UserID)
{
    system("cls");
    if (pengguna > 0)
    {
        cout << "+=======================+" << endl;
        cout << "|       Data User       | " << endl;
        cout << "+=======================+" << endl;
        cariDataUser(UserID);
        getch();
        menuUtama(UserID);
    }
    else
    {
        cout << "!!! Tidak ada pengguna terdaftar. Silakan daftar terlebih dahulu !!!" << endl;
        getch();
        daftar();
    }
}

void transfer(int UserID)
{
    system("cls");
    int transferPilihan, rekTujuan, indexTujuan = -1;
    double jumlahTransfer;

    cout << "Pilih jenis transfer:\n";
    cout << "1. Transfer ke bank yang sama\n";
    cout << "2. Transfer ke bank lain\n";
    cin >> transferPilihan;

    cout << "Masukkan nomor rekening tujuan: ";
    cin >> rekTujuan;
    cout << "Masukkan jumlah transfer: ";
    cin >> jumlahTransfer;

    for (int i = 0; i < pengguna; i++)
    {
        if (user1[i].noRekening == rekTujuan)
        {
            // nambahin rek tujuan ke array transaksi
            indexTujuan = i;
            break;
        }
    }

    if (indexTujuan == -1)
    {
        cout << "Rekening tujuan tidak ditemukan.\n";
    }
    else if (jumlahTransfer < 10000)
    {
        cout << "Nominal transfer kurang dari batas minimum\nBatas minimum transfer : Rp10.000";
    }
    else if (jumlahTransfer > user1[UserID - 1].balance)
    {
        cout << "Saldo tidak mencukupi untuk transfer.\n";
    }
    else
    {
        user1[UserID - 1].balance -= jumlahTransfer;
        user1[indexTujuan].balance += jumlahTransfer;
        user1[UserID - 1].mutasi[user1[UserID - 1].mutasi_count++] = "Transfer ke " + to_string(rekTujuan) + ": -" + to_string(jumlahTransfer);
        user1[indexTujuan].mutasi[user1[indexTujuan].mutasi_count++] = "Transfer dari " + to_string(user1[UserID - 1].noRekening) + ": +" + to_string(jumlahTransfer);
        cout << "Transfer berhasil! Sisa saldo Anda: " << user1[UserID - 1].balance << endl;

        if (transferPilihan == 2)
        {
            cout << "Karena transfer ke bank lain, biaya admin dikenakan.\n";
            int biayaAdmin = 5000;
            if (user1[UserID - 1].balance >= biayaAdmin)
            {
                user1[UserID - 1].balance -= biayaAdmin;
                user1[UserID - 1].mutasi[user1[UserID - 1].mutasi_count++] = "Biaya admin: -" + to_string(biayaAdmin);
                cout << "Biaya admin sebesar " << biayaAdmin << " telah dipotong dari saldo Anda.\n";
            }
            else
            {
                cout << "Saldo tidak mencukupi untuk membayar biaya admin.\n";
            }
        }
    }
    getch();
}

// int Partition(int angka[], int kiri, int kanan)
// {
//     int pivot = angka[kanan];
//     int i = kiri - 1;
//     for (int j = kiri; j < kanan; j++)
//     {
//         if (angka[j] < pivot)
//         {
//             i++;
//             int temp = angka[i];
//             angka[i] = angka[j];
//             angka[j] = temp;
//         }
//     }
//     int temp = angka[i + 1];
//     angka[i + 1] = angka[kanan];
//     angka[kanan] = temp;
//     return i + 1;
// }

void riwayat(string mutasi[], int mutasi_count)
{
    int pilihan;
    bool ulang = true;
    do
    {
        system("cls");
        cout << "+===========================+" << endl;
        cout << "|       Riwayat Transaksi   |" << endl;
        cout << "+===========================+" << endl;
        cout << "Urutkan menurut?" << endl;
        cout << "[1] Terbesar" << endl;
        cout << "[2] Terkecil" << endl;
        cout << "Pilihan Anda : ";
        cin >> pilihan;
        system("cls");

        cout << "+===========================+" << endl;
        cout << "|       Riwayat Transaksi   |" << endl;
        cout << "+===========================+" << endl;

        switch (pilihan)
        {
        case 1:
            if (mutasi_count == 0)
            {
                cout << "Tidak ada riwayat transaksi." << endl;
            }
            else
            {
                for (int i = 0; i < mutasi_count - 1; i++)
                {
                    for (int j = 0; j < mutasi_count - i - 1; j++)
                    {
                        int nilai1 = stoi(mutasi[j].substr(mutasi[j].find(":") + 2));
                        int nilai2 = stoi(mutasi[j + 1].substr(mutasi[j + 1].find(":") + 2));
                        if (nilai1 > nilai2)
                        {
                            string temp = mutasi[j];
                            mutasi[j] = mutasi[j + 1];
                            mutasi[j + 1] = temp;
                        }
                    }
                }
                for (int i = 0; i < mutasi_count; i++)
                {
                    cout << mutasi[i] << endl;
                }
            }

            cout << "+===========================+" << endl;
            ulang = false;
            break;
        case 2:
            if (mutasi_count == 0)
            {
                cout << "Tidak ada riwayat transaksi." << endl;
            }
            else
            {
                for (int i = 0; i < mutasi_count - 1; i++)
                {
                    for (int j = 0; j < mutasi_count - i - 1; j++)
                    {
                        int nilai1 = stoi(mutasi[j].substr(mutasi[j].find(":") + 2));
                        int nilai2 = stoi(mutasi[j + 1].substr(mutasi[j + 1].find(":") + 2));
                        if (nilai1 < nilai2)
                        {
                            string temp = mutasi[j];
                            mutasi[j] = mutasi[j + 1];
                            mutasi[j + 1] = temp;
                        }
                    }
                }
                for (int i = 0; i < mutasi_count; i++)
                {
                    cout << mutasi[i] << endl;
                }
            }

            cout << "+===========================+" << endl;
            ulang = false;
            break;
        default:
            cout << "Mohon masukkan pilihan yang benar" << endl;
            break;
        }
        getch();
    } while (ulang == true);
}
