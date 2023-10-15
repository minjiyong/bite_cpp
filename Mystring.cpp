#include <iostream>
#include <string.h>
using namespace std;

// [씹어먹는 C++] 사이트 코딩 진행중 4 - 5 강 
// 표준 라이브러리에서 지원하는 string 이라는 문자열 클래스를
// Mystring 이라는 클래스로 비슷하게 구현해보기.


class Mystring {
    private:
    char* str;
    int strlength;
    int memory_capacity;    // 현재 할당된 메모리 용량

    public:
    Mystring(char c);
    Mystring(const char* word);
    Mystring(const Mystring& str);
    ~Mystring();

    int length() const;     // strlength 출력
    int capacity() const;   // memory_capacity 출력

    Mystring& assign(const Mystring& word);     // 현재 입력한 단어로 바꾸기
    Mystring& assign(const char* word);
    void reserve(int size);                     // 할당할 문자열의 크기를 미리 예약
    char at(int i) const;                       // 특정 위치의 문자를 받아옴

    void print();   // 출력

    char& operator[](const int index);  // []를 사용해 배열처럼 바로 찾을 수 있게 연산자 추가

    // loc 앞에 문자를 삽입
    Mystring& insert(int loc, const Mystring& word); 
    Mystring& insert(int loc, const char* word);
    Mystring& insert(int loc, char c);

    // loc 앞에서부터 num 개의 문자를 삭제
    Mystring& erase(int loc, int num);  

    // 문자열 검색
    int find(int find_from, Mystring& word) const;
    int find(int find_from, const char* word) const;
    int find(int find_from, const char c) const;     

    // 문자열 간의 크기(사전식 순서 배열)를 비교
    int compare(const Mystring& word) const;

};

Mystring::Mystring(char c){
    str = new char[1];
    str[0] = c;
    strlength = 1;
    memory_capacity = strlength;
}

Mystring::Mystring(const char* word){
    strlength = strlen(word);
    memory_capacity = strlength;
    str = new char[strlength];

    for(int i = 0; i < strlength; ++i)
        str[i] = word[i];
}

Mystring::Mystring(const Mystring& word) {
    strlength = word.strlength;
    memory_capacity = strlength;
    str = new char[strlength];

    for(int i = 0; i < strlength; ++i)
        str[i] = word.str[i];
}

Mystring::~Mystring(){
    delete[] str;
}

int Mystring::length() const { return strlength; }

int Mystring::capacity() const { return memory_capacity; }

Mystring& Mystring::assign(const Mystring& word) {
    if (strlength < word.strlength) {
        // 새로 입력되는 값이 더 클때만 다시 할당.
        delete[] str;

        str = new char[word.strlength];
        memory_capacity = word.strlength;
    }

    for (int i = 0; i < word.strlength; ++i) {
        str[i] = word.str[i];
    }

    strlength = word.strlength;

    return *this;
}

Mystring& Mystring::assign(const char* word) {
    int temp_strlength = strlen(word);
    
    if (strlength < temp_strlength) {
        // 새로 입력되는 값이 더 클때만 다시 할당.
        delete[] str;

        str = new char[temp_strlength];
        memory_capacity = temp_strlength;
    }

    for (int i = 0; i < temp_strlength; ++i) {
        str[i] = word[i];
    }

    strlength = temp_strlength;

    return *this;
}

void Mystring::reserve(int size) {
    if (memory_capacity < size) {
        // 예약하려는 size가 현재 memory_capacity보다 작다면 무시.
        char* prev_str = str;

        str = new char[size];
        memory_capacity = size;

        for(int i = 0; i < strlength; ++i) 
            str[i] = prev_str[i];

        delete[] prev_str;
    }
}

char Mystring::at(int i) const {
    if (i >= strlength || i < 0)
    // i가 전체 길이를 초과하거나 음수면 안됨.
        return 0;
    else
        return str[i]; 
}

void Mystring::print() {
    for(int i = 0; i < strlength; ++i)
        cout << str[i];
    cout << endl;
}

char& Mystring::operator[](const int index) {return str[index];}

// insert 함수는 i 의 위치 바로 앞에 문자를 삽입한다.
// 에를 들어 abc 라는 문자열에 insert(1, "d") 를 한다면 adbc 가 된다.
Mystring& Mystring::insert(int loc, const Mystring& word) {
    if (loc < 0 || loc > strlength) return *this;
    
    if (strlength + word.strlength > memory_capacity) {

        // 새로 할당해야 하는 메모리 크기가 기존의 2배 이하라면,
        // 아예 2배를 할당해버려서 반복 연산에 수월하도록 함.
        if (memory_capacity * 2 > strlength + word.strlength)
            memory_capacity *= 2;
        else
            memory_capacity = strlength + word.strlength; 
        
        char* temp_str = str;
        str = new char[memory_capacity];

        // insert 되는 부분 바로 전까지의 내용 복사
        int i;
        for (i = 0; i < loc; ++i)
            str[i] = temp_str[i];

        // 새로 insert 되는 문자열
        for (int j = 0; j < word.strlength; ++j)
            str[i + j] = word.str[j];

        // 원 문자열의 나머지 부분
        for (; i < strlength; ++i)
            str[i + word.strlength] = temp_str[i];

        delete[] temp_str;

        strlength += word.strlength;
        return *this; 
    }

    // 만약 strlength + word.strlength < memory_capacity 라면 
    // 굳이 동적할당을 할 필요가 없다.
    // 효율적으로 insert 하기 위해 밀리는 부분을 먼저 뒤로 밀어버린다.

    for (int i = strlength - 1; i >= loc; i--) {
        // 뒤로 밀기. 이 때 원래의 문자열 데이터가 사라지지 않게 함.
        str[i + word.strlength] = str[i];
    }

    // insert 되는 문자 다시 집어넣기
    for (int i = 0; i < word.strlength; ++i)
        str[i + loc] = word.str[i];

    strlength += word.strlength;
    return *this;
}

Mystring& Mystring::insert(int loc, const char* word){
    Mystring temp(word);
    return insert(loc, temp);
}

Mystring& Mystring::insert(int loc, char c) {
    Mystring temp(c);
    return insert(loc, temp);
}

// loc 앞에서부터 num 개의 문자를 삭제
Mystring& Mystring::erase(int loc, int num) {
    if (num > strlength - loc) return *this;

    for (int i = 0; i < strlength; ++i)
        str[loc + i] = str[loc + num + i];

    strlength -= num;
    return *this;
}

// find_from 부터 검색 시작, word 라는 문자열을 찾는다.
int Mystring::find(int find_from, Mystring& word) const {
    int i, j;
    if(word.strlength == 0) return -1;

    for(i = find_from; i <= strlength - word.strlength; ++i) {
        for(j = 0; j < word.strlength; ++j) 
            // word 와 일치하지 않는 글자가 있다면 break
            if(str[i + j] != word.str[j]) break;

        // 완벽히 일치했다면    
        if(j == word.strlength) return i;
    }

    return -1;      // 전부 탐색했는데도 찾지 못했다면
}

int Mystring::find(int find_from, const char* word) const {
    Mystring temp(word);
    return find(find_from, temp);
}

int Mystring::find(int find_from, const char c) const {
    Mystring temp(c);
    return find(find_from, temp);
}

int Mystring::compare(const Mystring& word) const {
    // (*this) - (str) 을 수행한다.
    // 1 은 (*this) 가 사전식으로 더 뒤에 온다는 뜻.
    // 0 은 두 문자열이 같다는 뜻.
    // -1 은 (*this) 가 사전식으로 더 앞에 온다는 뜻.

    for(int i = 0; i < min(strlength, word.strlength); ++i) {
        if(str[i] > word.str[i]) return 1;
        else if(str[i] < word.str[i]) return -1;
    }

    // 여기까지 했는데 끝나지 않았다면 앞 부분까지 모두 똑같다.
    // 문자열 길이까지 똑같다면 완전히 같은 문자열
    if(strlength == word.strlength) return 0;

    else if (strlength > word.strlength) return 1;

    return -1;
}

int main()
{
    Mystring str1("abcde");
    str1.print();
    str1.erase(3, 2);
    str1.print();
    str1[2] = 'z';
    str1.print();

    return 0;
}
