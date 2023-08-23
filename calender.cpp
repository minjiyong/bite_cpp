#include <iostream>
using namespace std;

// [씹어먹는 C++] 사이트 코딩 진행중 4 - 1 강 
// Date 클래스와 일, 월, 년을 원하는 만큼 더하는 함수 만들기.
// 4 - 2 답안 참조 ver.

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

    // 해당 월의 총 일수를 구한다.
    int GetCurrentMonthTotalDays(int year, int month);

    void show_date();
};

void Date::set_date(int year, int month, int day) {
	year_ = year;
	month_ = month;
	day_ = day;
}

int Date::GetCurrentMonthTotalDays(int year, int month) {
    // 배열을 하나 만들어서 12달에 각각 해당되는 일수를 설정.
    static int month_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month != 2) {
        return month_day[month - 1];
    } else if (year % 4 == 0 && year % 100 != 0) {
        return 29;  // 윤년
    } else {
        return 28;
  }
}
	
void Date::add_day(int inc) {
    while (true) {
        // 현재 달의 총 일 수
        int current_month_total_days = GetCurrentMonthTotalDays(year_, month_);

        // 같은 달 안에 들어온다면;
        if (day_ + inc <= current_month_total_days) {
        day_ += inc;
        return;
    } else {
        // 다음달로 넘어가야 한다.
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
	cout << "오늘은 " << year_ << "년 " << month_ << "월 " << day_ << "일 입니다." << endl;
}

void show_menu() {
	cout << "[하고싶은 메뉴를 선택해주세요]" << endl;
	cout << "1. 햇수 늘리기" << endl;
	cout << "2. 개월수 늘리기" << endl;
	cout << "3. 일수 늘리기" << endl;
}

int main()
{
	Date today;
	int today_year;
	int today_month;
	int today_day;
	
	cout << "오늘은 몇년 몇월 며칠입니까? : ";
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
				cout << "몇 년 늘릴까요?: ";
				cin >> increase;
				today.add_year(increase);
				break;
				
			case 2:
				cout << "몇 개월 늘릴까요?: ";
				cin >> increase;
				today.add_month(increase);
				break;
				
			case 3:
				cout << "며칠을 늘릴까요?: ";
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