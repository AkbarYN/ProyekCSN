#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

struct kartu {
  string nama;
  int nilai;
};

struct login {  // Struktur untuk menu login
  string lgnemail;
  string lgnpass;
  string rgtemail;
  string rgpass;
};

struct wallet {  // Struktur untuk menu dompet
  int plhn_dompet;
  long long deposit;
  long long withdraw;
  long long balance = 0;
  long long bet;
};

struct Domino {  // Struktur untuk menentukan nilai Domino
  int sisi1;
  int sisi2;
};

struct Remi {
  string nama;
  int nilai;
};
Remi r;

void updateUserData(const string& email, wallet& d)
{
  ifstream inputFile("userID.txt");
  ofstream tempFile("temp.txt");

  if (!inputFile.is_open() || !tempFile.is_open()) {
    cout << "Gagal Membuka File!" << endl;
    return;
  }

  string line;
  string dataEmail, dataPass;
  bool userFound = false;

  while (getline(inputFile, line)) {
    if (line.find("Username: ") != string::npos) {
      dataEmail = line.substr(10);  // Extract email
    }
    if (line.find("Password: ") != string::npos) {
      dataPass = line.substr(10);  // Extract password
    }
    if (line.find("Saldo: ") != string::npos) {
      if (dataEmail == email) {
        // Update balance for this user
        tempFile << "Username: " << dataEmail << endl;
        tempFile << "Password: " << dataPass << endl;
        tempFile << "Saldo: " << d.balance << endl;  // Write updated balance
        tempFile << " " << endl;  // Blank line for separation
        userFound = true;
      }
      else {
        tempFile << "Saldo: " << d.balance << endl;  // Write original line
      }
    }
  }

  inputFile.close();
  tempFile.close();

  if (userFound) {
    // Replace original file with updated file
    remove("userID.txt");
    rename("temp.txt", "userID.txt");
  }
  else {
    cout << "User  data not found!" << endl;
    remove("temp.txt");  // Hapus file sementara jika tidak ada perubahan
  }
}

bool verifikasiLogin(const string& email, const string& pass, wallet& d)
{
  ifstream inputFile("userID.txt");
  string line;

  if (!inputFile.is_open()) {
    cout << "Gagal Membuka Database!" << endl;
    return false;
  }

  vector<vector<string>> dataPlayer;  // untuk menyimpan data player
  string dataEmail, dataPass;
  long long dataBalance;
  bool loginValid = false;

  while (getline(inputFile, line)) {
    if (line.find("Username: ") != string::npos) {
      dataEmail = line.substr(10);  // Extract email
    }
    else if (line.find("Password: ") != string::npos) {
      dataPass = line.substr(10);  // Extract password
    }
    else if (line.find("Saldo: ") != string::npos) {
      dataBalance = stoll(line.substr(7));  // Extract balance
      if (dataEmail == email && dataPass == pass) {
        loginValid = true;
        d.balance = dataBalance;
        break;
      }
    }
  }

  inputFile.close();
  return loginValid;
}

void loadingDot(int count, int delay)
{  // untuk menampilkan animasi loading
  for (int i = 0; i < count; i++) {
    cout << ". ";
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }
  cout << "\n";
}

//============BLACKJACK=========================
void initializeDeck(vector<Remi>& deck, Remi& r)
{
  string namak[] = { "2", "3",  "4", "5", "6", "7", "8",
                     "9", "10", "J", "Q", "K", "A" };
  int nilaik[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };

  for (int i = 0; i < 4;
       i++) {  // perulangan 4 jenis kartu {heart,spade,diamond,clubs}
    for (int j = 0; j < 13;
         j++) {  // perulangan 13 nama kartu {Ace,King.,Queen,Jack, DKK}
      Remi r;
      r.nama = namak[j];
      r.nilai = nilaik[j];
      deck.push_back(r);
    }
  }
}

void shuffleKartu(vector<Remi>& deck)
{
  srand(time(0));
  for (int i = 0; i < deck.size(); i++) {
    int j = rand() % deck.size();
    swap(deck[i], deck[j]);
  }
}

// fungsi untuk menarik kartu berikutnya dari deck
Remi drawKartu(vector<Remi>& deck, int& deckIndex)
{
  if (deckIndex < deck.size()) {
    return deck[deckIndex++];
  }
  // Jika deck habis, ulang dari awal (harusnya ada pemeriksaan lebih lanjut)
  return deck[0];
}

// Fungsi untuk menghitung total nilai kartu di tangan
int kalkulasiNilai(vector<Remi>& hand)
{
  int totalValue = 0;
  int aceCount = 0;

  // Hitung total nilai kartu
  for (Remi& remi : hand) {
    totalValue += remi.nilai;
    if (remi.nama == "A") {
      aceCount++;
    }
  }

  // Mengatur Ace menjadi 1 jika total nilai lebih dari 21
  while (totalValue > 21 && aceCount > 0) {
    totalValue -= 10;  // Ubah nilai Ace dari 11 menjadi 1
    aceCount--;
  }

  return totalValue;
}

void printHands(vector<Remi>& hand, string playerName)
{
  cout << playerName << " Hand: ";
  for (Remi& r : hand) {
    cout << r.nama << " ";
  }
  cout << "Total: " << kalkulasiNilai(hand) << endl;
}

int gameBlackJ(wallet& d, login& l)
{
  vector<Remi> deck;
  vector<Remi> playerHand;
  vector<Remi> dealerHand;
  int deckIndex = 0;  // Indeks untuk kartu yang ada di deck

  // Inisialisasi dan kocok deck
  initializeDeck(deck, r);
  shuffleKartu(deck);

  // Bagikan 2 kartu ke pemain dan dealer
  playerHand.push_back(drawKartu(deck, deckIndex));
  playerHand.push_back(drawKartu(deck, deckIndex));
  dealerHand.push_back(drawKartu(deck, deckIndex));
  dealerHand.push_back(drawKartu(deck, deckIndex));

  // Tampilkan kartu pemain dan dealer
  printHands(playerHand, "Pemain");
  loadingDot(10, 100);
  cout << "Dealer Hand: " << dealerHand[0].nama
       << " ?\n";  // Hanya kartu pertama dealer yang ditampilkan

  // Giliran pemain untuk memilih apakah ingin 'hit' atau 'stand'
  while (true) {
    cout << "\nApakah Anda ingin [1] Hit atau [2] Stand? ";
    int choice;
    cin >> choice;

    if (choice == 1) {
      playerHand.push_back(drawKartu(deck, deckIndex));
      printHands(playerHand, "Pemain");
      loadingDot(10, 100);

      // Cek apakah pemain telah melewati 21
      if (kalkulasiNilai(playerHand) > 21) {
        cout << "Pemain over 21! Anda kalah.\n";
        d.balance -= d.bet;
        cout << "Anda memenangkan sebesar: " << d.bet << endl;
        loadingDot(10, 100);
        updateUserData(l.lgnemail, d);
        return 0;
      }
    }
    else if (choice == 2) {
      break;
    }
    else {
      cout << "Pilihan tidak valid! Masukkan 1 untuk Hit atau 2 untuk Stand.\n";
    }
  }

  // Tampilkan kartu dealer
  printHands(dealerHand, "Dealer");
  loadingDot(10, 100);

  // Dealer bermain sesuai aturan: dealer harus hit jika nilai total <= 16
  while (kalkulasiNilai(dealerHand) <= 16) {
    dealerHand.push_back(drawKartu(deck, deckIndex));
    printHands(dealerHand, "Dealer");
  }

  // Bandingkan nilai kartu pemain dan dealer
  int playerValue = kalkulasiNilai(playerHand);
  int dealerValue = kalkulasiNilai(dealerHand);

  if (kalkulasiNilai(dealerHand) > 21) {
    cout << "Anda bermain sebesar: " << d.bet << endl;
    cout << "Nilai Dealer lebih dari 21!\n Anda menang.\n";
    d.balance = 2 * d.bet;
    cout << "Anda memenangkan sebesar: " << d.bet << endl;
    updateUserData(l.lgnemail, d);
    return 0;
  }
  if (playerValue > dealerValue) {
    cout << "Selamat, Anda menang!\n";
    cout << "Anda bermain sebesar: " << d.bet << endl;
    d.balance += 2 * d.bet;
    cout << "Anda memenangkan sebesar: " << d.bet << endl;
    loadingDot(10, 100);
  }
  else if (playerValue < dealerValue) {
    cout << "Sayang, Dealer menang.\n";
    cout << "Anda bermain sebesar: " << d.bet << endl;
    d.balance -= d.bet;
    cout << "Anda kalah sebesar: " << d.bet << endl;
    loadingDot(10, 100);
  }
  else {
    cout << "Seri!\n";
    loadingDot(10, 100);
  }
  updateUserData(l.lgnemail, d);
  return 0;
}
//======================================================================//

void tambahData(login& l, wallet& d)
{
  ofstream outputFile("userID.txt", ios::app);

  if (!outputFile.is_open()) {
    cout << "Gagal Membuka File!" << endl;
    return;
  }

  cout << "Registrasi Baru" << endl;
  cout << "Username: ";
  cin >> l.rgtemail;

  // Cek apakah username sudah ada
  ifstream inputFile("userID.txt");
  string line;
  while (getline(inputFile, line)) {
    if (line.find("Username: " + l.rgtemail) != string::npos) {
      cout << "Username sudah terdaftar. Silakan pilih username lain." << endl;
      inputFile.close();
      return tambahData(l, d);
    }
  }
  inputFile.close();

  cout << "Password: ";
  cin >> l.rgpass;

  outputFile << "userID\n";
  outputFile << "Username: " << l.rgtemail << endl;
  outputFile << "Password: " << l.rgpass << endl;
  d.balance = 1000;
  outputFile << "Saldo: " << d.balance << endl;
  outputFile << " " << endl;

  cout << "Registrasi Berhasil" << endl;
}

//=================================================================================//

void shuffleLoading()  // Fungsi untuk menampilkan loading saat mengocok
{
  cout << "Mengocok Domino";
  for (int i = 0; i < 10; i++) {
    cout << ". ";  // Perulangan untuk membuat animasi loading
    std::this_thread::sleep_for(std::chrono::milliseconds(
      100));  // Sintaks Sleep untuk menentukan berapa milliseconds untuk
              // melakukan setiap perulangan
  }
  cout << "\n";
}

// FUNGSI&PROSEDUR UNTUK QIUQIU//
void shuffleDeck(Domino deck[], int size)  // Mengacak deck domino
{
  for (int i = size - 1; i > 0;
       i--) {  // mengacak dari paling belakang dengan size jumlah domino 28
               // dimana disetiap perulangan
    int j = rand() % (i + 1);  // akan mengurangi jumlah yang belum diacak
                               // sebanyak 1 per perulangan

    Domino temp = deck[i];
    deck[i] = deck[j];
    deck[j] = temp;
  }
}

int menghitungNilai(Domino d1,
                    Domino d2)  // Fungsi untuk menghitung nilai Domino
                                // menggunakan %10 sesuai peraturan dari QiuQiu
{
  int sum = (d1.sisi1 + d1.sisi2 + d2.sisi1 + d2.sisi2) % 10;
  return sum;
};

void printHand(Domino d1,
               Domino d2)  // Menampilkan Hasil dari 2 Domino yang di acak dan
                           // didapatkan oleh Host/Player
{
  cout << "Domino ke 1 = [" << d1.sisi1 << " , " << d1.sisi2 << " ] " << endl;
  cout << "Domino ke 2 = [" << d2.sisi1 << " , " << d2.sisi2 << " ] " << endl;
};

int gameQQ(wallet& d, login& l)
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

  if (value1 >
      value2) {  // pengkondisian jika nilai lebih besar, lebih kecil atau sama
                 // dan mengupdate hasil dari permainan ke dompet pemain
    cout << "Selamat Anda Menang\n";
    d.balance += d.bet;
    cout << endl;
    loadingDot(10, 100);
  }
  else if (value2 > value1) {
    cout << "Anda Kalah\n";
    d.balance -= d.bet;
    cout << endl;
    loadingDot(10, 100);
  }
  else {
    cout << "Seri\n";
    cout << endl;
    loadingDot(10, 100);
  }
  updateUserData(l.lgnemail, d);

  return 0;
}

//=========================================================//

int getValidatedInput(int min, int max)
{
  int input;
  string inputStr;

  while (true) {
    // membaca input sebagai string untuk mengecek invalid karakter
    cin >> inputStr;

    // membuat stringstream untuk mengonversi string menjadi integer
    stringstream ss(inputStr);

    // mencoba mengonversi string menjadi integer dan memastikan tidak ada huruf
    // ekstra
    if (ss >> input && ss.eof()) {
      if (input >= min && input <= max) {
        return input;  // Valid input
      }
      else {
        cout << "Masukkan angka antara " << min << " dan " << max << "."
             << endl;
      }
    }
    else {
      cout << "Salah input! Masukkan sebuah angka!" << endl;
    }

    // membersihankan input buffer untuk menyingkirkan invalid input jika
    // diperlukan
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
  cout << "\n=====================" << endl;
  cout << "=      KAISINO      =" << endl;
  cout << "=====================" << endl;
  cout << "1. Login" << endl;
  cout << "2. Register" << endl;
  cout << "=====================" << endl;
  cout << "Pilih [1-2]: \n";
  return getValidatedInput(1, 2);
}

int menu_lobby()  // Fungsi untuk menampilkan menu lobby dimana player bisa
                  // memilih antara menu game dan dompet
{
  int plhnlobby;
  // system("cls");
  cout << "\n====================" << endl;
  cout << "=      LOBBY       =" << endl;
  cout << "====================" << endl;
  cout << "1. Menu Game" << endl;
  cout << "2. Dompet" << endl;
  cout << "3. Keluar" << endl;
  cout << "====================" << endl;
  cout << "Pilih [1-3] ";
  return getValidatedInput(1, 3);
}

void dompet(wallet& d, login& l)
// Fungsi untuk membuat menu dompet dan pemanggilan structure wallet menggunakan
// past by reference
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
      loadingDot(10, 100);
      if (d.deposit <= 100000000) {
        cout << "Deposit berhasil\n";
        d.balance += d.deposit;
        updateUserData(l.lgnemail, d);
      }
      else {
        cout << "Deposit Gagal\nMaksimal Deposit hanya 100000000\n";
      }

      break;

    case 2:  // Mengurangi/Menarik Saldo di dompet
      cout << "Masukan jumlah withdraw: ";
      cin >> d.withdraw;
      loadingDot(10, 100);

      if (d.withdraw <= 100000000) {
        cout << "Withdraw berhasil.\n";
      }
      else {
        cout << "Withdraw Gagal\nMaksimal withdraw hanya 100000000\n" << endl;
      }

      if (d.withdraw > d.balance) {  // Membatalkan withdraw dikarenakan balance
                                     // yang tidak cukup
        cout << "Saldo tidak cukup\n";
      }
      else {
        d.balance -= d.withdraw;
        updateUserData(l.lgnemail, d);
      }
      break;

    case 3:  // Menampilkan saldo pemain
      cout << "Saldo Anda : " << d.balance << endl;
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

  while (true) {
    int pilihan = get_option(l);
    switch (pilihan) {
      case 1:  // menu login
        cout << "\nMasukkan Username dan Password mu\n";
        cout << "Username: ";
        cin >> l.lgnemail;
        cout << "Password: ";
        cin >> l.lgnpass;

        if (verifikasiLogin(l.lgnemail, l.lgnpass, d)) {
          cout << "Login Berhasil!" << endl;
          break;
        }
        else {
          cout << "Login Gagal!\nUsername atau password salah" << endl;
        }
        continue;

      case 2:  // menu register
        tambahData(l, d);
        break;

      default:
        cout << "Pilihan tidak ditemukan";
        break;
    }

    break;  //keluar dari loop login/register
  }
  while (
    true) {  // perulangan agar dapat kembali ke menu setelah memilih di lobby
    cin.clear();
    int plhn_lobby = menu_lobby();
    if (plhn_lobby == 3) {
      cout << "Keluar dari lobby. Kembali ke menu login/register.\n";
      break;
    }  // Kembali ke menu login/register

    while (plhn_lobby == 1 || plhn_lobby == 2) {
      switch (plhn_lobby) {
        case 1:
          switch (gameMenu()) {
            case 1:
              cout << "Memilih QiuQiu...." << endl;
              loadingDot(10, 100);
              cout
                << "============================================================"
                << endl;
              cout << "Selamat Datang di QiuQiu KAISINO" << endl;
              cout << "Tata Cara Bermain QiuQiu" << endl;
              cout << "1. Pemain dan Host akan diberikan masing masing 2 domino"
                   << endl;
              cout << "2. Setelah diberikan nilai domino akan ditotalkan"
                   << endl;
              cout << "3. Setelah di totalkan hanya angka terakhir yang dibaca"
                   << endl;
              cout
                << "4. Semakin tinggi angkamu semakin besar peluang untuk menang"
                << endl;
              cout << "5. Jika mengalami seri. Host akan memenangkan permainan"
                   << endl;
              cout
                << "============================================================"
                   "\n"
                << endl;
              cout << "Masukkan Taruhan Anda: \n";
              cin >> d.bet;
              cout
                << "============================================================"
                   "\n";

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

              gameQQ(d, l);

              break;

            case 2:
              cout << "Memilih BlackJack\n";
              loadingDot(10, 100);

              cout
                << "============================================================"
                << endl;
              cout << "Selamat Datang di BlackJack KAISINO" << endl;
              cout << "Tata Cara Bermain BlackJack" << endl;
              cout << "1. " << endl;
              cout << "2. " << endl;
              cout << "3. " << endl;
              cout << "4. " << endl;
              cout << "5. " << endl;
              cout
                << "============================================================"
                   "\n"
                << endl;
              cout << "Masukkan Taruhan Anda: ";
              cin >> d.bet;
              cout
                << "============================================================"
                   "\n";

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

                loadingDot(10, 100);
                gameBlackJ(d, l);
              }
              break;

            case 3:
              break;
          }
          break;

        case 2:
          dompet(d, l);
          break;

        default:
          cout << "Pilihan tidak ditemukan";
          break;
      }

      break;
    }
  }
}
