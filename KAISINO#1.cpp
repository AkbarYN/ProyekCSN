#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

struct login
{
  string lgnemail;
  string lgnpass;
  string rgtemail;
  string rgpass;
};
login l;

struct wallet
{
  int plhn_dompet;
  int deposit;
  int withdraw;
  int balance = 0;
  int bet;
};
wallet d;

struct Domino
{
  int sisi1;
  int sisi2;
};
Domino dm;

void shuffleDeck(Domino deck[], int size)
{
  for (int i = size - 1; i > 0; i--)
  {
    int j = rand() % (i + 1);

    Domino temp = deck[i];
    deck[i] = deck[j];
    deck[j] = temp;
  }
}

int menghitungNilaiValue(Domino d1, Domino d2)
{
  int sum = (d1.sisi1 + d1.sisi2 + d2.sisi1 + d2.sisi2) % 10;
  return sum;
};

void printHand(Domino d1, Domino d2)
{
  cout << "Domino ke 1 = [" << d1.sisi1 << " , " << d1.sisi2 << " ] " << endl;
  cout << "Domino ke 2 = [" << d2.sisi1 << " , " << d2.sisi2 << " ] " << endl;
};

int getValidatedInput(int min, int max)
{
  int input;
  while (true)
  {
    cin >> input;
    if (cin.fail())
    {
      cout << "Salah input! Masukkan sebuah angka!" << endl;
      cin.clear(); // clear error flag
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n'); // ignore invalid input
    }
    else if (input < min || input > max)
    {
      cout << "Masukkan angka antara " << min << " dan " << max << "." << endl;
    }
    else
    {
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n'); // ignore remaining input
      return input;
    }
  }
}

int gameQQ()
{
  Domino deck[28];
  int k = 0;
  for (int i = 0; i <= 6; i++)
  {
    for (int j = i; j <= 6; j++)
    { // memverifikasi data domino
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

  int value1 = menghitungNilaiValue(p1_bg1, p1_bg2);
  int value2 = menghitungNilaiValue(p2_bg1, p2_bg2);

  cout << "Pemain 1 : ";
  printHand(p1_bg1, p1_bg2);
  cout << "Nilai Pemain ke 1 adalah: " << value1 << endl;
  cout << endl;
  cout << "Host : ";
  printHand(p2_bg1, p2_bg2);
  cout << "Nilai Pemain ke 2 adalah: " << value2 << endl;
  cout << endl;

  if (value1 > value2)
  {
    cout << "Selamat Anda Menang";
  }
  else if (value2 > value1)
  {
    cout << "Anda Kalah";
  }
  else
  {
    cout << "Seri";
  }

  return 0;
}

int gameMenu()
{
  int plhGame;
  cout << "Pilih Game Yang ingin dimainkan\n1. QiuQiu\n2. Roulette\n3. Slot"
       << endl;
  while (true)
  {
    cout << "Pilih [1-3]: " << endl;
    cin >> plhGame;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cin.fail())
    {
      cout << "salah input! masukkan sebuah angka!" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else
    {
      break;
    }
  }
  return plhGame;
}

int get_option()
{
  int plhnlogin;
  system("cls");
  cout << "=====================" << endl;
  cout << "=      KAISINO      =" << endl;
  cout << "=====================" << endl;
  cout << "1. Login" << endl;
  cout << "2. Register" << endl;
  cout << "=====================" << endl;
  return getValidatedInput(1, 2);
}

int menu_lobby()
{
  int plhnlobby;
  system("cls");
  cout << "====================" << endl;
  cout << "=      LOBBY       =" << endl;
  cout << "====================" << endl;
  cout << "1. Menu Game" << endl;
  cout << "2. Dompet" << endl;
  cout << "====================" << endl;
  return getValidatedInput(1, 2);
}

void dompet()
{
  system("cls");
  cout << "1. Deposit" << endl;
  cout << "2. Withdraw" << endl;
  cout << "3. Tunjukkan Saldo" << endl;
  d.plhn_dompet = getValidatedInput(1, 3);

  switch (d.plhn_dompet)
  {
  case 1:
    cout << "masukan jumlah deposit anda: ";
    cin >> d.deposit;
    d.balance += d.deposit;
    break;

  case 2:
    cout << "Masukan jumlah wihtdraw: ";
    cin >> d.withdraw;
    if (d.withdraw > d.balance)
    {
      cout << "Saldo tidak cukup";
    }
    else
    {
      d.balance -= d.withdraw;
    }
    break;

  case 3:
    cout << "Saldo Anda : " << d.balance;
    break;

  default:
    cout << "Pilihan tidak ditemukan";
    break;
  }
}

int main()
{
  int pilihan = get_option();

  while (pilihan == 1 || pilihan == 2)
  {
    switch (pilihan)
    {
    case 1:
      cout << "Username: ";
      cin >> l.lgnemail;
      cout << "Password: ";
      cin >> l.lgnpass;
      break;

    case 2:
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

  int plhn_lobby = menu_lobby();
  while (plhn_lobby == 1 || plhn_lobby == 2)
  {
    switch (plhn_lobby)
    {
    case 1:
      switch (gameMenu())
      {
      case 1:
        cout << "Memilih QiuQiu...." << endl;

        cout << "Selamat Datang di QiuQiu KAISINO\nMasukkan Taruhan Anda: \n";
        cin >> d.bet;

        if (d.bet > d.balance)
        {
          cout << "Saldo anda tidak cukup";
        }
        else if (d.bet <= d.balance)
        {
          cout << "Selamat bermain";
          cout << endl;
        }

        gameQQ();

        break;

      case 2:
        cout << "Memilih Roulette.....";
        break;

      case 3:
        cout << "Memilih Slot.....";
        break;
      }
      break;

    case 2:
      dompet();
      break;

    default:
      cout << "Pilihan tidak ditemukan";
      break;
    }

    break;
  }

  cin.get();
}
