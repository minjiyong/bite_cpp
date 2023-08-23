#include <iostream>
using namespace std;

// [씹어먹는 C++] 사이트 코딩 진행중 4 - 3 강 
// String 이라는 문자열 클래스 완성하기.

class String {
	private:
	char* str;
	int len;
	

	public:
	String(char c, int n);	// 문자 c가 n개 있는 문자열로 정의
	String(const char* s);
	String(const String &s);
	~String();
	
	void add_string(const String &s);   // str 뒤에 s를 붙인다.
	void copy_string(const String &s);  // str에 s를 복사한다.
	void show_string();                 // string을 출력한다.
	int strlen();                       // 문자열 길이를 리턴한다.
};

String::String(char c, int n){
	str = new char[n + 1];
	for(int i = 0; i < n; ++i) str[i] = c;
	str[n] = '\0';
	len = n;
}

String::String(const char* s) {
	for(len = 0; s[len] != '\0'; ++len);
	str = new char[len + 1];
	for(int i = 0; i < len; ++i) str[i] = s[i];
}

String::String(const String &s) {
	len = s.len;
	str = new char[len + 1];
	for(int i = 0; i < len; ++i) str[i] = s.str[i];
}

String::~String() {
	if(str) delete[] str;
}

void String::add_string(const String &s) {
	char* temp = new char[len + s.len + 1];
	for(int i = 0; i < len; ++i) temp[i] = str[i];
	for(int i = 0; i < s.len; ++i) temp[len + i] = s.str[i];
	len = len + s.len;
	str = temp;
	str[len + 1] = '\0';
}

void String::copy_string(const String &s) {
	len = s.len;
	str = new char[len + 1];
	for(int i = 0; i < len; ++i) str[i] = s.str[i];
	str[len + 1] = '\0';
}

void String::show_string() {
	for(int i = 0; i < len; ++i) cout << str[i];
	cout << endl;
}

int String::strlen(){
	return len;
}


int main()
{
	String a('c', 3);
	String b('z', 4);
	
	a.show_string();
	b.show_string();
	cout << endl; 
	
	a.add_string(b);
	a.show_string();
	cout << endl;
	
	b.copy_string(a);
	b.show_string();
	
	return 0;
};