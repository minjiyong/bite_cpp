#include <iostream>
#include <string.h>
using namespace std;

// [�þ�Դ� C++] ����Ʈ �ڵ� ������ 4 - 5 �� 
// ǥ�� ���̺귯������ �����ϴ� string �̶�� ���ڿ� Ŭ������
// Mystring �̶�� Ŭ������ ����ϰ� �����غ���.


class Mystring {
    private:
    char* str;
    int strlength;
    int memory_capacity;    // ���� �Ҵ�� �޸� �뷮

    public:
    Mystring(char c);
    Mystring(const char* word);
    Mystring(const Mystring& str);
    ~Mystring();

    int length() const;     // strlength ���
    int capacity() const;   // memory_capacity ���

    Mystring& assign(const Mystring& word);     // ���� �Է��� �ܾ�� �ٲٱ�
    Mystring& assign(const char* word);
    void reserve(int size);                     // �Ҵ��� ���ڿ��� ũ�⸦ �̸� ����
    char at(int i) const;                       // Ư�� ��ġ�� ���ڸ� �޾ƿ�

    void print();   // ���

    char& operator[](const int index);  // []�� ����� �迭ó�� �ٷ� ã�� �� �ְ� ������ �߰�

    // loc �տ� ���ڸ� ����
    Mystring& insert(int loc, const Mystring& word); 
    Mystring& insert(int loc, const char* word);
    Mystring& insert(int loc, char c);

    // loc �տ������� num ���� ���ڸ� ����
    Mystring& erase(int loc, int num);  

    // ���ڿ� �˻�
    int find(int find_from, Mystring& word) const;
    int find(int find_from, const char* word) const;
    int find(int find_from, const char c) const;     

    // ���ڿ� ���� ũ��(������ ���� �迭)�� ��
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
        // ���� �ԷµǴ� ���� �� Ŭ���� �ٽ� �Ҵ�.
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
        // ���� �ԷµǴ� ���� �� Ŭ���� �ٽ� �Ҵ�.
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
        // �����Ϸ��� size�� ���� memory_capacity���� �۴ٸ� ����.
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
    // i�� ��ü ���̸� �ʰ��ϰų� ������ �ȵ�.
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

// insert �Լ��� i �� ��ġ �ٷ� �տ� ���ڸ� �����Ѵ�.
// ���� ��� abc ��� ���ڿ��� insert(1, "d") �� �Ѵٸ� adbc �� �ȴ�.
Mystring& Mystring::insert(int loc, const Mystring& word) {
    if (loc < 0 || loc > strlength) return *this;
    
    if (strlength + word.strlength > memory_capacity) {

        // ���� �Ҵ��ؾ� �ϴ� �޸� ũ�Ⱑ ������ 2�� ���϶��,
        // �ƿ� 2�踦 �Ҵ��ع����� �ݺ� ���꿡 �����ϵ��� ��.
        if (memory_capacity * 2 > strlength + word.strlength)
            memory_capacity *= 2;
        else
            memory_capacity = strlength + word.strlength; 
        
        char* temp_str = str;
        str = new char[memory_capacity];

        // insert �Ǵ� �κ� �ٷ� �������� ���� ����
        int i;
        for (i = 0; i < loc; ++i)
            str[i] = temp_str[i];

        // ���� insert �Ǵ� ���ڿ�
        for (int j = 0; j < word.strlength; ++j)
            str[i + j] = word.str[j];

        // �� ���ڿ��� ������ �κ�
        for (; i < strlength; ++i)
            str[i + word.strlength] = temp_str[i];

        delete[] temp_str;

        strlength += word.strlength;
        return *this; 
    }

    // ���� strlength + word.strlength < memory_capacity ��� 
    // ���� �����Ҵ��� �� �ʿ䰡 ����.
    // ȿ�������� insert �ϱ� ���� �и��� �κ��� ���� �ڷ� �о������.

    for (int i = strlength - 1; i >= loc; i--) {
        // �ڷ� �б�. �� �� ������ ���ڿ� �����Ͱ� ������� �ʰ� ��.
        str[i + word.strlength] = str[i];
    }

    // insert �Ǵ� ���� �ٽ� ����ֱ�
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

// loc �տ������� num ���� ���ڸ� ����
Mystring& Mystring::erase(int loc, int num) {
    if (num > strlength - loc) return *this;

    for (int i = 0; i < strlength; ++i)
        str[loc + i] = str[loc + num + i];

    strlength -= num;
    return *this;
}

// find_from ���� �˻� ����, word ��� ���ڿ��� ã�´�.
int Mystring::find(int find_from, Mystring& word) const {
    int i, j;
    if(word.strlength == 0) return -1;

    for(i = find_from; i <= strlength - word.strlength; ++i) {
        for(j = 0; j < word.strlength; ++j) 
            // word �� ��ġ���� �ʴ� ���ڰ� �ִٸ� break
            if(str[i + j] != word.str[j]) break;

        // �Ϻ��� ��ġ�ߴٸ�    
        if(j == word.strlength) return i;
    }

    return -1;      // ���� Ž���ߴµ��� ã�� ���ߴٸ�
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
    // (*this) - (str) �� �����Ѵ�.
    // 1 �� (*this) �� ���������� �� �ڿ� �´ٴ� ��.
    // 0 �� �� ���ڿ��� ���ٴ� ��.
    // -1 �� (*this) �� ���������� �� �տ� �´ٴ� ��.

    for(int i = 0; i < min(strlength, word.strlength); ++i) {
        if(str[i] > word.str[i]) return 1;
        else if(str[i] < word.str[i]) return -1;
    }

    // ������� �ߴµ� ������ �ʾҴٸ� �� �κб��� ��� �Ȱ���.
    // ���ڿ� ���̱��� �Ȱ��ٸ� ������ ���� ���ڿ�
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
