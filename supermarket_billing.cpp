#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


// for xep balo
int w[100],W, v[100], f[100][100];
int n,i,j,GT=0;

// for kruskal
const int MAXN = 10000;
const int MAXM = 1000;

// tao class items
class Items {
  private:
  string name_items;
  int quantity;
  long price_items;
  long total_price;
  public:
  long totalprice() {
    total_price = quantity * price_items;
    return total_price;
  }

  Items(string name_items, int quantity, long price_items) {
    this->name_items = name_items;
    this->quantity = quantity;
    this->price_items = price_items;
  }

  void setName(string name) {
    this->name_items = name;
  }
  
  string getName() {
    return name_items;
  }

  void setQuantity(int quantity) {
    this->quantity = quantity;
  }

  int getQuantity() {
    return quantity;
  }

  void setPriceItems(long price_items) {
    this->price_items = price_items;
  }

  long getPriceItems() {
    return price_items;
  }

  void displayItems () {
    cout << setw(25) << left <<  name_items
		<< setw(14) << left << quantity << setw(22) << left << setprecision(16) << price_items <<
		setw(10) << left << totalprice() << endl;
    // cout << "Name of the item: " << name_items << endl;
    // cout << "Quantity: " << quantity << endl;
    // cout << "Price: " << price_items << endl;
    // cout << "Total price: " << totalprice() << endl;
  }
  friend istream& operator>> (istream& fi, Items& it) {
    fi >> it.name_items >> it.quantity >> it.price_items >> it.total_price;
    return fi;
  }
  
};

// tao class Date
class Date {
  public:
  int day;
  int month;
  int year;
  void inputDate() {
    cout << "Nhap ngay/thang/nam: ";
    cin >> day >> month >> year;
  }
  void displayDate() {
    cout << day <<"-" << month << "-" << year << endl;
  }
  friend istream& operator>>(istream& fi, Date& d) {
    fi >> d.day >> d.month >> d.year;
    return fi;
  }
  friend ostream& operator<<(ostream& os, Date& d) {
    os << d.day << "-" << d.month << "-" << d.year;
    return os;
  }
};

// tao class Time
class Time {
  public:
  int hour;
  int minute;
  int second;
  void inputTime() {
    cout << "Nhap gio/phut/giay: ";
    cin >> hour >> minute >> second;
  }
  void displayTime() {
    cout << hour << ":" << minute << ":" << second << endl;
  }
  friend istream& operator>>(istream& fi, Time& t) {
    fi >> t.hour >> t.minute >> t.second;
    return fi;
  }
  friend ostream& operator<<(ostream& os, Time& t) {
    os << t.hour << ":" << t.minute << ":" << t.second;
    return os;
  }
};

// Tao NodeBill hoa don
class NodeBill {
public: 
// bo sung thong tin khach hang
  string name_customer;
  int id_customer;
  //
  int idBill;
  int amount_items;
  Date date;
  Time time;
  vector<Items> listOfItems;
  long totalPrices;
  int totalQuantity;
  NodeBill* next;
};

NodeBill* head = new NodeBill();

// tao danh sach lien ket don
struct dshoadon
{
	NodeBill* head;
	NodeBill* tail;
};

dshoadon* createList()
{
	dshoadon* p = new dshoadon;
	p->head = NULL;
  p->tail = NULL;
	return p;
}

// ham kiem tra xem hoa don nay da co trong danh sach chua
bool checkBill(int id_bill)
{
    if (head == NULL)
        return false;
    NodeBill* t = new NodeBill;
    t = head;
    while (t != NULL) {
        if (t->idBill == id_bill)
            return true;
        t = t->next;
    }
    return false;
}

// ham them mot bill moi
void insert_record(dshoadon* ds, int idBill, int amount_items, Date date, Time time, vector<Items> listOfItems) {
  // if Record Already Exist
    if (checkBill(idBill)) {
        cout << "Bill with this record Already Exists\n";
        return;
    } else {
    NodeBill* t = new NodeBill();
    t->idBill = idBill;
    t->amount_items = amount_items;
    t->date = date;
    t->time = time;
    t->listOfItems = listOfItems;
    t->next = NULL;
      // Insert at Begin
    if (head == NULL
        || (head->idBill >= t->idBill)) {
        t->next = head;
        head = t;
    }
    // Insert at middle or End
    else {
        NodeBill* c = head;
        while (c->next != NULL
               && c->next->idBill < t->idBill) {
            c = c->next;
        }
        t->next = c->next;
        c->next = t;
    }
    if (ds->head == NULL)
    {
      ds->head = t;
      ds->tail = t;
    }
    else
    {
      ds->tail->next = t;
      ds->tail = t;
    }
    cout << "Record Inserted Successfully\n";    
    }
}

// ham show danh sach cac bill
void show_record()
{
  NodeBill* p = head;
  if (p == NULL) {
    cout << "No Record Available\n";
  }
  else {    
      // Until p is not NULL
    while (p != NULL) {
      cout << "============================ CASH RECEIPT ============================" << endl;
    cout << "\t\t            SUPERMARKET 123" << endl;
    cout << "\t\t        33 PLANET EARTH DISTRICT BT" << endl;
    cout << "\t\t            123-456-789" << endl;
    cout << endl;
       cout << "RECEIPT ID: " << p->idBill <<  "\t\t\t\t\tAMOUNT OF ITEMS: " << p->amount_items << endl;
      cout << "DATE: ";
      p->date.displayDate();
      cout << "TIME: ";
      p->time.displayTime();
      cout << "CASHIER: TCHENG NHU QUAN\n";
      cout << "-----------------------------------------------------------------------------\n";
      cout << setfill(' ');
	    cout << setw(8) << left << "No." << setw(25) << left << "Description"
		<< setw(14) << left << "Quantity" << setw(22) << left << setprecision(16) << "Price" <<
		setw(10) << left << "Total price" << endl;
    long k = 0;
      for (int i = 0; i < p->amount_items; i++) {
        k += p->listOfItems[i].totalprice();
        cout << setw(8) << left << i;
        p->listOfItems[i].displayItems();
        
      }
      cout << "TOTAL: " << k << "VND";
      p = p->next;
    }
  }
}

// ham delete mot hoa don dua tren idBill
int delete_record(int idBill) {
  NodeBill* t = head;
  NodeBill* p = NULL;

  //delete at begin
  if(t != NULL && t->idBill == idBill) {
    head = t->next;
    delete t;
    cout << "Xoa hoa don thanh cong!!\n";
    return 0;
  }

  //delete other than begin
  while(t!=NULL && t->idBill != idBill) {
    p = t;
    t = t->next;
  }
  if (t==NULL) {
    cout << "Ma hoa don can xoa khong ton tai!\n";
    return -1;    
  } else {
    p->next = t->next;
    delete t;
    cout << "Xoa hoa don voi ma " << idBill << " thanh cong!\n";
    return 0;
  }
}

//sua hoa don dua tren idBill
void modify_record(int idBill) {
  NodeBill * temp = head;
	while(temp!=NULL){
		
		if(temp->idBill==idBill){
      cout << "Record with id " << idBill << " found !!!\n";
      cout << "Enter new amount of items: ";
			cin >> temp->amount_items;
      cout << "Enter new date: ";
      Date newDate;
      newDate.inputDate();
      temp->date = newDate;
      cout << "Enter new time: ";
      Time newTime;
      newTime.inputTime();
      temp->time = newTime;
			cout << "Enter new list of items: ";
      vector<Items> new_listOfItems;
      for (int i = 0; i < temp->amount_items; i++) {
        cout << "-- Vat pham so " << i << endl;
        string name_items;
        cout << "Nhap ten vat pham: ";
        cin.ignore();
        getline(cin, name_items);
        int quantity;
        cout << "Nhap so luong: ";
        cin >> quantity;
        cout << "Nhap gia tien: ";
        long price_items;
        cin >> price_items;
        Items new_items(name_items, quantity, price_items);
        new_listOfItems.push_back(new_items);
        cout << "Updation Successful!!!\n";
		  }
      temp->listOfItems = new_listOfItems;		  
	  }
    temp = temp->next;	
  }
	cout << "bill with this " << idBill << " was not found!!!\n";
}

// tim kiem hoa don
void search_record(int idBill) {
  if (!head) {
    cout << "Empty List!! No such Bill with id " << idBill << " available!\n";
    return;
  } else {
    NodeBill* p =head;
    while (p) {
      if (p->idBill == idBill) {
        cout << "Id: " << p->idBill << endl;
        cout << "Amount of Items: " << p->amount_items << endl;
        p->date.displayDate();
        p->time.displayTime();
        cout << "---Detailed list of Items---\n";
        for (int i = 0; i < p->amount_items; i++) {
          p->listOfItems[i].displayItems();
          cout << endl;
        }
      }
      p = p->next;
    }
      cout << "No such Bill with id " << idBill << " available!\n";
  }
}



void addEndhd(dshoadon*& ds, NodeBill* temp)
{
	if (ds->head == NULL)
	{
		ds->head = temp;
		ds->tail = temp;
	}
	else
	{
		ds->tail->next = temp;
		ds->tail = temp;
	}
}
// xuatHoaDon danh sach hang hoa
void xuatHoaDon(dshoadon* ds)
{
	if (ds->head == NULL)
	{
		cout << "danh sach trong." << endl;
		return;
	}
	NodeBill* p = ds->head;
	cout << setfill(' ');
  
  
    
      // Until p is not NULL
  do  {
    cout << "============================ CASH RECEIPT ============================" << endl;
    cout << "\t\t            SUPERMARKET 123" << endl;
    cout << "\t\t            33 PLANET EARTH" << endl;
    cout << "\t\t            123-456-789" << endl;
    cout << endl;

      cout << "RECEIPT ID: " << p->idBill <<  "\t\t\t\t\tAMOUNT OF ITEMS: " << p->amount_items << endl;
      cout << "DATE: ";
      p->date.displayDate();
      cout << "TIME: ";
      p->time.displayTime();
      cout << "CASHIER: TCHENG NHU QUAN\n";
      cout << "-----------------------------------------------------------------------------\n";
      cout << setfill(' ');
	    cout << setw(8) << left << "No." << setw(25) << left << "Description"
		<< setw(14) << left << "Quantity" << setw(22) << left << setprecision(16) << "Price" <<
		setw(10) << left << "Total price" << endl;
      long k = 0;
      for (int i = 0; i < p->amount_items; i++) {
        k += p->listOfItems[i].totalprice();
        cout << setw(8) << left << i;
        p->listOfItems[i].displayItems();
        
      }
      cout << "TOTAL: " << k << " VND";
      p = p->next;
      cout << endl;
  } while((p != NULL));
}

void docFileHoaDon(dshoadon* ds) {
  cout << "Nhap ten file: ";
	string filename; 
  cin.ignore();
	getline(cin, filename);
	ifstream fi(filename);
		if (!fi.is_open()) 
			cout << "Co loi xay ra !! Vui long kiem tra lai.\n";
		char t;
		int m; 
		fi >> m; 
		cout << "Danh sach co " << m << " hoa don\n"; 
		int i = 0;
		char c; 
		fi.get(c);
		// ds = createList();
		while (i < m)
			{
				NodeBill* p = new NodeBill; 
				p->next = NULL;
				getline(fi, p->name_customer); 
				fi >> p->id_customer;
        fi.get(t);
        fi >> p->idBill;
        fi.get(t);
        fi >> p->amount_items;
        fi.get(t);
        fi >> p->date;
        fi.get(t);
        fi >> p->time;
        fi.get(t);
        int k = 0;
        while(k < p->amount_items) {
          string name_items;
          getline(fi, name_items);
          int quantity;
          fi >> quantity;
          fi.get(t);
          long price_items;
          fi >> price_items;
          fi.get(t);
          long total_price;
          fi >> total_price;
          fi.get(t);
          Items items(name_items, quantity, price_items);
          p->listOfItems.push_back(items);
          k++;
          // cout << "Xin chao ban Quan lan 4 nha!!\n";
        } 
        fi >> p->totalQuantity;
        fi.get(t);
        fi >> p->totalPrices;
        fi.get(t);
        addEndhd(ds, p);
        
				i++;
			}
		cout << "Da doc file thanh cong voi ten file la: " << filename << endl;
		fi.close();
    // xuatHoaDon(ds);
}

int soluongHoaDon(dshoadon* l)
{
	int i = 0;
	if (l->head == NULL) return 0;
	for (NodeBill* p = l->head; p != NULL; p = p->next)
	{
		i++;
	}
	return i;
}

void ghiFileHoaDon(dshoadon* ds) {
  cout << "Nhap ten file: ";
	string filename; 
  cin.ignore();
	getline(cin, filename);
	ofstream fo;
	fo.open(filename, ios::out | ios::trunc);
	int m = soluongHoaDon(ds); 
	fo << m << endl;
	for (NodeBill* p = ds->head; p != NULL; p = p->next)
		{
			fo << p->name_customer << endl;
			fo << p->id_customer << endl;
			fo << p->idBill << endl;
			fo << p->amount_items << endl;
			fo << p->date << endl;
			fo << p->time << endl;
      for (int i = 0; i < p->amount_items; i++) {
        fo << p->listOfItems[i].getName() << endl;
        fo << p->listOfItems[i].getQuantity() << endl;
        fo << p->listOfItems[i].getPriceItems() << endl;
        fo << p->listOfItems[i].totalprice() << endl;
      }
      fo << p->totalQuantity;
      fo << p->totalPrices;
		}
	fo.close();
	cout << "Da luu file thanh cong voi ten file la: " << filename << endl;
}

// thuat toan xep tui
void nhapSoLuong_GiaTri(dshoadon* ds)
{
  
  cout <<"So luong khach da dat don hang tai sieu thi:  ";
  cin >> n;
  cout << "Nhap khoi luong gioi han xe giao hang co the cho:  ";
  cin >> W;
  int i = 1;
  NodeBill* p = ds->head;
  do {
    cout <<"Khoi luong do vat thu " << i << ": " ;
    w[i] = p->totalQuantity;
    cout << p->totalQuantity << endl;
    cout <<"Gia tri cua do vat thu " << i << ": " ;
    v[i] = p->totalPrices;
    cout << p->totalPrices << endl;
    p = p->next;
    i++;
  } while (p != NULL);


}

// tìm gia tri lon nhat

int max(int a, int b){

return (a>b)?a:b;

}

// hàm tinh gia tri cua bang
// xuatHoaDon bang tinh
void xuatHoaDon_bangtinh(){
  cout <<"----------BANG TINH-------------------" << endl;
  for( int i=1; i<=n ; i++)
    {
      for(int j = 0; j<= W; j++)
        {
          cout << setw(5) << f[i][j] <<  " ";
        }
      cout << endl;
    }

}

void bangphuongan()
{
    for(i=0;i<=n;i++)
      {
        f[i][0]=0;
      }
     for(j=0;j<=W;j++)
     {
       f[0][j]=0;
     }
     for(i=1;i<=n;i++)
     {
       for(j=1;j<=W;j++)
       {
          if (w[i]>j)
          {
            f[i][j]=f[i-1][j];
          }
          else
          {
            f[i][j]=max(f[i-1][j],f[i-1][j-w[i]]+v[i]);
          }
        }
      }
}

// hàm tìm ket qua cua bai toan
void truyvet(){
      i=n;
      j=W;
  for(;i >0; i--)
    {
      if(f[i][j]!=f[i-1][j])
      {
        cout << i <<" ";
        j = j - w[i];
        GT = GT + v[i];
      }
    }
}

// thuat toan tim cay khung cuc tieu kruskal 
struct edge {
    // Dinh dau
    int u;
    // Dinh cuoi
    int v;
    // Do dai
    int w;
};

int number, m;
edge a[MAXM];
int parent[MAXN]; // tìm ra nút cha của một nút NodeBill nào đó


void docFileHoaDon_Kruskal() {
  cout << "Nhap ten file: ";
	string filename; 
  cin.ignore();
	getline(cin, filename);
	ifstream f(filename);
		if (!f.is_open()) 
			cout << "Co loi xay ra !! Vui long kiem tra lai.\n";
   
    f >> number >> m;
    int i, j;
    for (i = 1; i <= m; i++) 
        f >> a[i].u >> a[i].v >> a[i].w;
    f.close();
}

void SapXep() {
  edge tmp;
  int i, j;
  for (i = 1; i <= m - 1; i++)
    for (j = i + 1; j <= m; j++)
      if (a[i].w > a[j].w) {
        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
      }
}

int root(int x) {
  if (parent[x] == -1) 
    return x;
  else 
    return root(parent[x]);
}

void unify(int r1, int r2) { /// r1 khac r2
  if (r1 < r2) 
    parent[r2] = r1;
  else /// r1 > r2
    parent[r1] = r2;
}

void Kruskal() {
    SapXep();
    int i;
    for (i = 1; i <= number; i++) 
        parent[i] = -1;
    int dem = 0;
    int tong = 0;
    int x, y;
    int r1, r2;
    //f.open(fo, ios::out);
    for (i = 1; i <= m; i++) {
        if (dem == number - 1) break;
        x = a[i].u;
        y = a[i].v;

        r1 = root(x);
        r2 = root(y);

        if (r1 != r2) {
            cout << x << "   " << y << endl; /// end line
            dem++;
            tong = tong + a[i].w;
            unify(r1, r2);
        }
    }
    cout << "===> Gia tri cua cay khung be nhat la: " << tong << endl;

}

// QuickSortHoaDon theo gia tien cua san pham 
// 
// Ham kiem tra danh sach rong
bool isEmptyHoaDon(dshoadon*& l) {
	if (l->head == NULL) {
		return true;
	}
	else {
		return false;
	}
}
// them vao dau danh sach
void addHeadHoaDon(dshoadon*& l, NodeBill* temp) {
	if (isEmptyHoaDon(l)) {
		l->head = l->tail = temp;
	}
	else {
		temp->next = l->head; // con tro next cua p tro toi dia chi cua NodeBill head ban dau
		l->head = temp; // cap nhat NodeBill head (luc sau)
	}
}

void QuickSortHoaDon(dshoadon*& l) {
	dshoadon* l1, * l2;
	NodeBill* tag, * p, * temp;
	if (l->head == NULL || l->head == l->tail) {
		return;
	}
	else {
		dshoadon* l1 = createList();
		dshoadon* l2 = createList();
		tag = l->head;
		l->head = l->head->next;
		tag->next = NULL; // co lap tag
		while (l->head != NULL)
		{
			p = l->head;
			l->head = p->next;
			p->next = NULL;
			if (p->totalPrices <= tag->totalPrices) {
				addHeadHoaDon(l1, p);
			}
			else {
				addHeadHoaDon(l2, p);
			}
		}
		QuickSortHoaDon(l1);
		QuickSortHoaDon(l2);
		if (l1->head != NULL) {
			l->head = l1->head;
			l1->tail->next = tag;
		}
		else {
			l->head = tag;
		}
		tag->next = l2->head;
		if (l2->head != NULL) {
			l->tail = l2->tail;
		}
		else {
			l->tail = tag;
		}
	}
}

// tao menu
void Menu_Bill() {
	cout << "=================MENU================\n";
	cout << "1. Them hoa don\n";
	cout << "2. Sua hoa don\n";
	cout << "3. Xoa hoa don\n";
	cout << "4. In danh sach hoa don\n";
	cout << "5. Doc File\n";
	cout << "6. Ghi File\n";
  cout << "7. xuatHoaDon danh sach khach hang dat don hang\n";
	cout << "8. Sap xep hoa don theo gia tien giam dan - QuickSortHoaDon\n";
	cout << "9. Len danh sach cac don hang can giao - Xep balo\n";
	cout << "10. Len danh sach duong di ngan nhat - Kruskal\n";
	cout << "11. Thoat!!!\n";
  cout << "=====================================\n";
}

int ChonMenuHoaDon()
{
	int n = 0;
	cout << "\n\nMoi chon menu: ";
	cin >> n;
	if (n > 0 || n < 12)
		return n;
	else return ChonMenuHoaDon();
}
int main() {
  /*std::cout << "Hello World!\n";
  head = NULL;
  int amountBill;
  cout << "Nhap so hoa don can them: ";
  cin >> amountBill;
  
  // hàm thêm một bill mới;
  for (int i = 0; i < amountBill; i++) {
     int idBill, amount_items;
  cout << "Nhap id Bill: ";
  cin >> idBill;
  cout << "Nhap tong so vat pham: ";
  cin >> amount_items;
  Date date;
  date.inputDate();
  Time time;
  time.inputTime();
  vector<Items> listOfItems;
  for (int i = 0; i < amount_items; i++) {
    cout << "-- Vat pham so " << i << endl;
    string name_items;
    cout << "Nhap ten vat pham: ";
    cin.ignore();
    getline(cin, name_items);
    int quantity;
    cout << "Nhap so luong: ";
    cin >> quantity;
    cout << "Nhap gia tien: ";
    long price_items;
    cin >> price_items;
    
    Items items(name_items, quantity, price_items);
    listOfItems.push_back(items);   
  }
  insert_record(idBill, amount_items, date, time, listOfItems); 
  }
  cout << endl;
  show_record();*/

  /*
  // hoa don can xoa
  //nhap ma hoa don can xoa
  // cout << "\n Nhap ma hoa don can xoa: ";
  // int idBilldelete;
  // cin >> idBilldelete;
  // delete_record(idBilldelete);
  // cout << "Cac hoa don sau khi xoa la: \n";
  // show_record();*/

  /*
  // sua hoa don 
  cout << "Nhap hoa don can sua: ";
  int idBillmodify, ;
  cin >> idBillmodify;
  modify_record(idBillmodify);
  cout << "\nHoa don sau khi duoc sua la: ";
  show_record();*/

  /*
  // tim hoa don
  int idBillsearch;
  cout << "Nhap hoa don can tim: ";
  cin >> idBillsearch;
  search_record(idBillsearch);*/
 
  /*
  // docFileHoaDon va dua vao linked list
  dshoadon* ds = createList();
  docFileHoaDon(ds);
  cout << "Show record: \n";
  xuatHoaDon(ds);*/
  /*
  // thuat toan xep ba lo
  int D = W;
  nhapSoLuong_GiaTri(ds);
  bangphuongan();

  cout <<"Cac do vat duoc cho vao tui la: ";
  truyvet();
  cout <<"\nTong gia tri toi da cua tui la " << D << endl;
  cout <<"Tong gia tri cua do vat duoc cho vao tui la " << GT << endl;*/

  // ghi File va dua vao linked list
  
    while (true)
	{	
    Menu_Bill();
		int chon = ChonMenuHoaDon();
    dshoadon* ds = createList();
	  switch (chon)
    {
    case 1:		
      cout << "1. Them hoa don\n";
      head = NULL;
      int amountBill;
      cout << "Nhap so hoa don can them: ";
      cin >> amountBill;
    
      // hàm thêm một bill mới;
      for (int i = 0; i < amountBill; i++) {
        int idBill, amount_items;
        cout << "Nhap id Bill: ";
        cin >> idBill;
        cout << "Nhap tong so vat pham: ";
        cin >> amount_items;
        Date date;
        date.inputDate();
        Time time;
        time.inputTime();
        vector<Items> listOfItems;
        for (int i = 0; i < amount_items; i++) {
          cout << "-- Vat pham so " << i << endl;
          string name_items;
          cout << "Nhap ten vat pham: ";
          cin.ignore();
          getline(cin, name_items);
          int quantity;
          cout << "Nhap so luong: ";
          cin >> quantity;
          cout << "Nhap gia tien: ";
          long price_items;
          cin >> price_items;
          
          Items items(name_items, quantity, price_items);
          listOfItems.push_back(items);   
      }
      insert_record(ds, idBill, amount_items, date, time, listOfItems); 
      }
      cout << "Them hoa don thanh cong!!!\n";
      break;
    case 2:
      cout << "2. Sua hoa don\n";
      cout << "Nhap hoa don can sua: ";
      int idBillmodify;
      cin >> idBillmodify;
      modify_record(idBillmodify);
      cout << "\nHoa don sau khi duoc sua la: ";
      show_record();
      break;
    case 3:
      cout << "3. Xoa hoa don\n";
      cout << "\n Nhap ma hoa don can xoa: ";
      int idBilldelete;
      cin >> idBilldelete;
      delete_record(idBilldelete);
      cout << "Cac hoa don sau khi xoa la: \n";
      show_record();
      break;
    case 4:
      cout << "4. In danh sach hoa don\n";
      show_record();
      break;
    case 5:
      cout << "5. Doc File\n";
      // ds = createList();
      docFileHoaDon(ds);
      cout << "Show record: \n";
      xuatHoaDon(ds);
      break;
    case 6:
      cout << "6. Ghi File\n";
      ghiFileHoaDon(ds);
      break;
    case 7:
      cout << "7. xuatHoaDon danh sach khach hang dat don hang\n";
      docFileHoaDon(ds);
      xuatHoaDon(ds);
      break;
    case 8:
      cout << "8. Sap xep hoa don theo gia tien giam dan - QuickSortHoaDon\n";
      docFileHoaDon(ds);
      cout << "\n=======> Danh sach hoa don sau khi sap xep theo gia tien giam dan là: \n";
      QuickSortHoaDon(ds);
      xuatHoaDon(ds);
      break;
    case 9:
      cout << "9. Len danh sach cac don hang can giao - Xep balo\n";
      docFileHoaDon(ds);
      nhapSoLuong_GiaTri(ds);
      bangphuongan();
      cout <<"Cac do vat duoc cho vao tui la: ";
      truyvet();
      // cout <<"\nTong gia tri toi da cua tui la " << D << endl;
      cout <<"\nTong gia tri cua do vat duoc cho vao tui la " << GT << endl;
      break;
    case 10:
      cout << "10. Len danh sach duong di ngan nhat - Kruskal\n";
      docFileHoaDon_Kruskal();
      Kruskal();
      break;
    case 111:
      cout << "Thoat!!!\n";
      exit(1);
      break;
    }
	}
}