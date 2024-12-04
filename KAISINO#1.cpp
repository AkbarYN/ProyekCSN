#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include <vector>
using namespace std;

struct kartu {
  string nama;
  int value;
};

struct login {  // Struktur untuk menu login
  string lgnemail;
  string lgnpass;
  string rgtemail;
  string rgpass;
};

struct wallet {  // Struktur untuk menu dompet
  int plhn_dompet;
  int deposit;
  int withdraw;
  int balance = 0;
  int bet;
};

struct Domino {  // Struktur untuk menentukan nilai Domino
  int sisi1;
  int sisi2;
};
void shuffleDeck(kartu deck[], int size)  // Mengacak domino
{
  for (
    int i = size - 1; i > 0;
    i--) {  //mengacak dari paling belakang dengan size jumlah 52 kartu dimana disetiap perulangan
    int j =
      rand() %
      (i +
       1);  //akan mengurangi jumlah yang belum diacak sebanyak 1 per perulangan

    kartu temp = deck[i];
    deck[i] = deck[j];
    deck[j] = temp;
  }
}

void shuffleLoading()  // Fungsi untuk menampilkan loading saat mengocok domino
{
  cout << "Mengocok Domino";
  for (int i = 0; i < 10; i++) {
    cout << ". ";  // Perulangan untuk membuat animasi loading
    std::this_thread::sleep_for(std::chrono::milliseconds(
      100));  //Sintaks Sleep untuk menentukan berapa milliseconds untuk melakukan setiap perulangan
  }
  cout << "\n";
}

//FUNGSI&PROSEDUR UNTUK QIUQIU//
void shuffleDeck(Domino deck[], int size)  // Mengacak domino
{
  for (
    int i = size - 1; i > 0;
    i--) {  //mengacak dari paling belakang dengan size jumlah domino 28 dimana disetiap perulangan
    int j =
      rand() %
      (i +
       1);  //akan mengurangi jumlah yang belum diacak sebanyak 1 per perulangan

    Domino temp = deck[i];
    deck[i] = deck[j];
    deck[j] = temp;
  }
}

int menghitungNilai(
  Domino d1,
  Domino
    d2)  // Fungsi untuk menghitung nilai Domino menggunakan %10 sesuai peraturan dari QiuQiu
{
  int sum = (d1.sisi1 + d1.sisi2 + d2.sisi1 + d2.sisi2) % 10;
  return sum;
};

void printHand(
  Domino d1,
  Domino
    d2)  // Menampilkan Hasil dari 2 Domino yang di acak dan didapatkan oleh Host/Player
{
  cout << "Domino ke 1 = [" << d1.sisi1 << " , " << d1.sisi2 << " ] " << endl;
  cout << "Domino ke 2 = [" << d2.sisi1 << " , " << d2.sisi2 << " ] " << endl;
};

int gameQQ(wallet& d)
{
  Domino deck[28];
  int k = 0;
  for (int i = 0; i <= 6; i++) {
    for (int j = i; j <= 6; j++) {  // memverifikasi data domino
      deck[k].sisi1 = i;
      deck[k].sisi2 = j;
      k++;
    }
  }
  srand(static_cast<unsigned int>(time(0)));

  shuffleDeck(deck, 28);

  Domino p1_bg1 = deck[0];
  Domino p1_bg2 = deck[1];
  Domino p2_bg1 = deck[2];
  Domino p2_bg2 = deck[3];

  int value1 = menghitungNilai(p1_bg1, p1_bg2);  // Menghitung nilai dari player
  int value2 = menghitungNilai(p2_bg1, p2_bg2);  // Menghitung nilai dari host

  cout << "Pemain 1 : " << endl;
  shuffleLoading();  // Menampilkan loading screen ....
  printHand(p1_bg1, p1_bg2);
  cout << "Nilai Pemain ke 1 adalah: " << value1 << endl;
  cout << endl;
  cout << "Host : " << endl;
  shuffleLoading();  // Menampilkan loading screen ....
  printHand(p2_bg1, p2_bg2);
  cout << "Nilai Pemain ke 2 adalah: " << value2 << endl;
  cout << endl;

  if (
    value1 >
    value2) {  //pengkondisian jika nilai lebih besar, lebih kecil atau sama dan mengupdate hasil dari permainan ke dompet pemain
    cout << "Selamat Anda Menang\n";
    d.balance += d.bet;
  }
  else if (value2 > value1) {
    cout << "Anda Kalah\n";
    d.balance -= d.bet;
  }
  else {
    cout << "Seri\n";
  }

  return 0;
}

//=========================================================//

int getValidatedInput(
  int min,
  int
    max)  //Fungsi untuk memvalidasi input sehingga hanya bisa memasukkan angka yang telah dicantumkan
{
  int input;
  while (true) {
    cin >> input;
    cout << endl;
    if (cin.fail()) {
      cout << "Salah input! Masukkan sebuah angka!" << endl;
      cin.clear();  // clear error flag
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n');  // ignore invalid input
    }
    else if (input < min || input > max) {
      cout << "Masukkan angka antara " << min << " dan " << max << "." << endl;
    }
    else {
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n');  // ignore remaining input
      return input;
    }
  }
}

int gameMenu()  // Fungsi untuk menampilkan menu game
{
  int plhGame;
  cout << "====================" << endl;
  cout << "=       GAME       =" << endl;
  cout << "====================" << endl;
  cout << "1. QiuQiu" << endl;
  cout << "2. BlackJack" << endl;
  cout << "3. Keluar" << endl;
  cout << "====================" << endl;
  while (true) {
    cout << "Pilih [1-3]: " << endl;
    cin >> plhGame;
    if (plhGame == 3) {
      break;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cin.fail()) {
      cout << "salah input! masukkan sebuah angka!" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else {
      break;
    }
  }
  return plhGame;
}

int get_option(login& l)  // Fungsi untuk menampilkan login menu
{
  int plhnlogin;
  // system("cls");
  cout << "=====================" << endl;
  cout << "=      KAISINO      =" << endl;
  cout << "=====================" << endl;
  cout << "1. Login" << endl;
  cout << "2. Register" << endl;
  cout << "=====================" << endl;
  return getValidatedInput(1, 2);
}

int menu_lobby()  // Fungsi untuk menampilkan menu lobby dimana player bisa memilih antara menu game dan dompet
{
  int plhnlobby;
  // system("cls");
  cout << "====================" << endl;
  cout << "=      LOBBY       =" << endl;
  cout << "====================" << endl;
  cout << "1. Menu Game" << endl;
  cout << "2. Dompet" << endl;
  cout << "3. Keluar" << endl;
  cout << "====================" << endl;
  return getValidatedInput(1, 3);
}

void dompet(
  wallet&
    d)  // Fungsi untuk membuat menu dompet dan pemanggilan structure wallet menggunakan past by reference
{
  // system("cls");
  cout << "====================" << endl;
  cout << "=      LOBBY       =" << endl;
  cout << "====================" << endl;
  cout << "1. Deposit" << endl;
  cout << "2. Withdraw" << endl;
  cout << "3. Tunjukkan Saldo" << endl;
  cout << "4. Kembali" << endl;
  cout << "====================" << endl;
  cout << "Pilih [1-4]" << endl;
  d.plhn_dompet = getValidatedInput(1, 4);

  switch (d.plhn_dompet) {
    case 1:  // Menambahkan Saldo di dompet
      cout << "masukan jumlah deposit anda: ";
      cin >> d.deposit;
      d.balance += d.deposit;
      break;

    case 2:  //Mengurangi/Menarik Saldo di dompet
      cout << "Masukan jumlah wihtdraw: ";
      cin >> d.withdraw;
      if (
        d.withdraw >
        d.balance) {  //Membatalkan withdraw dikarenakan balance yang tidak cukup
        cout << "Saldo tidak cukup";
      }
      else {
        d.balance -= d.withdraw;
      }
      break;

    case 3:  // Menampilkan saldo pemain
      cout << "Saldo Anda : " << d.balance;
      break;

    case 4:
      break;

    default:
      cout << "Pilihan tidak ditemukan";
      break;
  }
}

int main()  // Fungsi utama

{
  login l;   // pemanggilan struktur login
  wallet d;  // pemanggilan struktur dompet
  int pilihan = get_option(l);
  while (pilihan == 1 || pilihan == 2) {  //percabangan
    switch (pilihan) {
      case 1:  // menu login
        cout << "Username: ";
        cin >> l.lgnemail;
        cout << "Password: ";
        cin >> l.lgnpass;
        break;

      case 2:  // menu register
        cout << "Username: ";
        cin >> l.rgtemail;
        cout << "Password: ";
        cin >> l.rgpass;
        break;

      default:
        cout << "Pilihan tidak ditemukan";
        break;
    }

    break;
  }
  while (
    true) {  // perulangan agar dapat kembali ke menu setelah memilih di lobby
    int plhn_lobby = menu_lobby();
    while (plhn_lobby == 1 || plhn_lobby == 2) {
      switch (plhn_lobby) {
        case 1:
          switch (gameMenu()) {
            case 1:
              cout << "Memilih QiuQiu...." << endl;
              for (int i = 0; i < 10; i++) {
                cout << ". ";
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
              }
              cout << "\n";
              cout
                << "============================================================"
                << endl;
              cout << "Selamat Datang di QiuQiu KAISINO" << endl;
              cout << "Tata Cara Bermain QiuQiu";
              cout
                << "1. Pemain dan Host akan diberikan masing masing 2 domino";
              cout << "2. Setelah diberikan nilai domino akan ditotalkan";
              cout << "3. Setelah di totalkan hanya angka terakhir yang dibaca";
              cout
                << "4. Semakin tinggi angkamu semakin besar peluang untuk menang";
              cout << "5. Jika mengalami seri. Host akan memenangkan permainan";
              cout
                << "============================================================"
                << endl;
              cout << "Masukkan Taruhan Anda: \n";
              cout
                << "============================================================\n";
              cin >> d.bet;

              if (d.bet > d.balance) {
                cout << "Saldo anda tidak cukup\n";
                break;
              }
              else if (d.bet == 0) {
                cout << "NGAPAIN SIH\n";
                break;
              }
              else if (d.bet <= d.balance) {
                cout << "Selamat bermain";
                cout << endl;
              }

              gameQQ(d);

              break;

            case 2:
              cout << "Memilih BlackJack.....";
              for (int i = 0; i < 10; i++) {
                cout << ". ";
                cout << endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
              }
              cout << "\n";
              break;

            case 3:
              break;
          }
          break;

        case 2:
          dompet(d);
          break;

        default:
          cout << "Pilihan tidak ditemukan";
          break;
      }

      break;
    }

    cin.get();
  }
}
