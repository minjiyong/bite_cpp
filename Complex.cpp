#include <iostream>
#include <string.h>
using namespace std;

// [씹어먹는 C++] 사이트 코딩 진행중 5 - 1 강 
// 연산자 오버로딩을 이용해 복소수를 관리하는 클래스를 만들어보자


class Complex {
    private:
    // real 은 복소수의 실수 부분, img 은 허수 부분이다.
    double real, img;
    // 문자열로 된 복소수에서의 실수부와 허수부를 정수로 변환하는 함수
    double get_number(const char* str, int from, int to) const;

    public:
    Complex(double real, double img) : real(real), img(img) {};
    Complex(const Complex& c) {real = c.real, img = c.img;};
    Complex(const char* str);

    Complex& operator+=(const Complex& c);
    Complex& operator-=(const Complex& c);
    Complex& operator*=(const Complex& c);
    Complex& operator/=(const Complex& c);

    Complex& operator=(const Complex& c);

    friend Complex operator+(const Complex& a, const Complex& b);
    friend Complex operator-(const Complex& a, const Complex& b);
    friend Complex operator*(const Complex& a, const Complex& b);
    friend Complex operator/(const Complex& a, const Complex& b);

    friend ostream& operator<<(ostream& os, const Complex& c);

};


Complex operator+(const Complex& a, const Complex& b) {
    Complex temp(a.real + b.real, a.img + b.img);
    return temp;
}

Complex operator-(const Complex& a, const Complex& b) {
    Complex temp(a.real - b.real, a.img - b.img);
    return temp;
}

Complex operator*(const Complex& a, const Complex& b) {
    Complex temp(a.real * b.real - a.img * b.img, a.real * b.img + b.real * a.img);
    return temp;
}

Complex operator/(const Complex& a, const Complex& b) {
    Complex temp( 
        (a.real * b.real + a.img * b.img) / (b.real * b.real + b.img * b.img),
        (b.real * a.img - a.real * b.img) / (b.real * b.real + b.img * b.img) );
    return temp;
}

ostream& operator<<(ostream&os, const Complex& c) {
    os << "(" << c.real << ", " << c.img << ")";
    return os;
}

Complex::Complex(const char* str) {
    // 입력 받은 문자열을 분석하여 real(실수부) 부분과 img(허수부) 부분을 찾는다.
    // 문자열의 꼴은 "[부호](실수부)[부호]i(허수부)" 이다.
    // 이 때, 맨 앞의 부호는 + 일 시 생략이 가능하다.

    int begin = 0, end = strlen(str);
    img = 0.0;
    real = 0.0;

    // 먼저 기준이 되는 'i'의 위치를 찾는다.
    int pos_i = -1;
    for(int i = 0; i != end; ++i) {
        if(str[i] == 'i') {
            pos_i = i;
            break;
        }
    }

    // 만약 'i'가 없다면 이 수는 실수 뿐이다.
    if(pos_i == -1) {
        real = get_number(str, begin, end - 1);
        return;
    }

    // 만약 'i'가 있다면, get_number 함수로 실수부와 허수부를 나누어 처리한다.
    real = get_number(str, begin, pos_i - 1);
    img = get_number(str, pos_i + 1, end);

    // 이때, 허수부가 음수라면
    if(pos_i >= 1 && str[pos_i - 1] == '-') img *= -1.0;

}

double Complex::get_number(const char* str, int from, int to) const{
    bool minus = false;
    if(from > to) return 0;

    if(str[from] == '-')minus = true;
    if(str[from] == '-' || str[from] == '+') from++;    // 부호 다음 문자열부터 읽어야 하니까

    double num = 0.0;
    double decimal = 1.0;

    bool integer_part = true;
    for(int i = from; i <= to; ++i) {
        if(isdigit(str[i]) && integer_part) {
            // 123 이라는 문자열이라면 10배씩 해줌으로서 1 -> 12 -> 123 순서로 읽어짐.
            num *= 10.0;
            // 문자 '0'을 정수 0으로 바꾸는 보편적인 방법.
            // ASCII 상 0부터 9까지의 숫자들이 크기 순서로 연속적으로 배열되어 있기 때문에 가능하다.
            num += (str[i] - '0');

        } else if(str[i] == '.')
            // 중간에 '.'을 만났다면 실수 부분이 끝났다는 뜻.
            integer_part = false;
            
        else if (isdigit(str[i]) && !integer_part) {
            // 소수점 아래의 경우, 비슷하게 decimal 이라는 변수를 도입해서
            // 456 이라는 문자열을 0.4 -> 0.45 -> 0.456 식으로 읽을 수 있게 함.
            decimal /= 10.0;
            num += ((str[i] - '0') * decimal);
        } else
        break;
    }

    // 음수일 경우
    if(minus) num *= -1.0;

    return num;
}

Complex& Complex::operator+=(const Complex& c) {
    (*this) = (*this) + c;
    return *this;
}

Complex& Complex::operator-=(const Complex& c) {
    (*this) = (*this) - c;
    return *this;
}

Complex& Complex::operator*=(const Complex& c) {
    (*this) = (*this) * c;
    return *this;
}

Complex& Complex::operator/=(const Complex& c) {
    (*this) = (*this) / c;
    return *this;
}

Complex& Complex::operator=(const Complex& c) {
    real = c.real;
    img = c.img;
    return *this;
}

int main()
{
    Complex a(0, 0);
    a = "-1.1 + i3.923" + a;
    cout << "a 의 값은 : " << a << " 이다." << endl;

    return 0;
}