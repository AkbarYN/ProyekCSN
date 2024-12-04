#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

struct Domino {
  int sisi1;
  int sisi2;
};

void shuffleDeck(Domino deck[], int size) {
  for (int i = size - 1; i > 0; i--) {
    int j = rand() % (i + 1);

    Domino temp = deck[i];
    deck[i] = deck[j];
    deck[j] = temp;
  }
}

int menghitungNilaiValue(Domino d1, Domino d2) {
  int sum = (d1.sisi1 + d1.sisi2 + d2.sisi1 + d2.sisi2) % 10;
  return sum;
};

void printHand(Domino d1, Domino d2) {
  cout << "Domino ke 1 = [" << d1.sisi1 << " , " << d1.sisi2 << " ] " << endl;
  cout << "Domino ke 2 = [" << d2.sisi1 << " , " << d2.sisi2 << " ] " << endl;
};

int main() {

  Domino deck[28];
  int k = 0;
  for (int i = 0; i <= 6; i++) {
    for (int j = i; j <= 6; j++) { // memverifikasi data domino
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

  if (value1 > value2) {
    cout << "Selamat Anda Menang";
  } else if (value2 > value1) {
    cout << "Anda Kalah";
  } else {
    cout << "Seri";
  }

  return 0;
}
// 1. bikin domino
// 2. ngitung 2 sisi domino = {a,b} = cd | c tdk dihitung;
// 2.1 inputan dengan rand ex rand % 7 / sisi;  cari hasil player sama host
// 3. 2 sisi domino ditambahin
// 4. ngitung jika domino kita ><= host
// 5. nampilin hasil [X,Y]
// 6. mengupdate dompet player jika menang/kalah