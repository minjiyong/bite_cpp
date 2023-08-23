#include <iostream>
using namespace std;

// [�þ�Դ� C++] ����Ʈ �ڵ� ������ 4 - 1 �� 
// Date Ŭ������ ��, ��, ���� ���ϴ� ��ŭ ���ϴ� �Լ� �����.
// 4 - 2 ��� ���� ver.

class Date {
	private:
	int year_;
	int month_;
	int day_;
	
	public:
    void set_date(int year, int month, int date);
    void add_day(int inc);
    void add_month(int inc);
    void add_year(int inc);

    // �ش� ���� �� �ϼ��� ���Ѵ�.
    int GetCurrentMonthTotalDays(int year, int month);

    void show_date();
};

void Date::set_date(int year, int month, int day) {
	year_ = year;
	month_ = month;
	day_ = day;
}

int Date::GetCurrentMonthTotalDays(int year, int month) {
    // �迭�� �ϳ� ���� 12�޿� ���� �ش�Ǵ� �ϼ��� ����.
    static int month_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month != 2) {
        return month_day[month - 1];
    } else if (year % 4 == 0 && year % 100 != 0) {
        return 29;  // ����
    } else {
        return 28;
  }
}
	
void Date::add_day(int inc) {
    while (true) {
        // ���� ���� �� �� ��
        int current_month_total_days = GetCurrentMonthTotalDays(year_, month_);

        // ���� �� �ȿ� ���´ٸ�;
        if (day_ + inc <= current_month_total_days) {
        day_ += inc;
        return;
    } else {
        // �����޷� �Ѿ�� �Ѵ�.
        inc -= (current_month_total_days - day_ + 1);
        day_ = 1;
        add_month(1);
    }
  }
}

void Date::add_month(int inc) {
	add_year((inc + month_ - 1) / 12);
    month_ = month_ + inc % 12; 
    if (month_ != 12) month_ = month_ % 12;
    else month_ == 12;
}

void Date::add_year(int inc) {
	year_ += inc;
}
	
void Date::show_date() {
	cout << "������ " << year_ << "�� " << month_ << "�� " << day_ << "�� �Դϴ�." << endl;
}

void show_menu() {
	cout << "[�ϰ���� �޴��� �������ּ���]" << endl;
	cout << "1. �޼� �ø���" << endl;
	cout << "2. ������ �ø���" << endl;
	cout << "3. �ϼ� �ø���" << endl;
}

int main()
{
	Date today;
	int today_year;
	int today_month;
	int today_day;
	
	cout << "������ ��� ��� ��ĥ�Դϱ�? : ";
	cin >> today_year >> today_month >> today_day;
	
	today.set_date(today_year, today_month, today_day);
	today.show_date();
	
	while(true) {
		show_menu();
		int num;
		int increase;
		cin >> num;
		
		switch(num) {
			case 1:
				cout << "�� �� �ø����?: ";
				cin >> increase;
				today.add_year(increase);
				break;
				
			case 2:
				cout << "�� ���� �ø����?: ";
				cin >> increase;
				today.add_month(increase);
				break;
				
			case 3:
				cout << "��ĥ�� �ø����?: ";
				cin >> increase;
				today.add_day(increase);
				break;
			
			case 5:
				return 0;
		}
		
		today.show_date();
	
	}
	
	return 0;
}