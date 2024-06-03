#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// str.find(int ch, int pos = 0); tìm ký tự ch kể từ vị trí pos đến cuối chuỗi str
// str.find(char *s, int pos = 0); tìm s (mảng ký tự kết thúc ‘\0’) kể từ vị trí pos đến cuối
// str.find(string& s, int pos = 0); tìm chuỗi s kể từ vị trí pos đến cuối chuỗi.
// Nếu không quy định giá trị pos thì hiểu mặc nhiên là 0; nếu tìm có thì phương thức trả về vị trí xuất hiện đầu tiên, ngược lại trả về giá trị -1.

// str.insert(int pos, char* s); chèn s (mảng ký tự kết thúc \0) vào vị trí pos của str;
// str.insert(int pos, string s); chèn chuỗi s (kiểu string) vào vị trí pos của chuỗi str;
// str.insert(int pos, int n, int ch); chèn n lần ký tự ch vào vị trí pos của chuỗi str;

// Phương thức replace() thay thế một đoạn con trong chuỗi str cho trước (đoạn con kể từ một vị trí pos và đếm tới nchar ký tự ký tự về phía cuối chuỗi) bởi một chuỗi s nào đó, hoặc bởi n ký tự ch nào đó. Có nhiều cách dùng, thứ tự tham số như sau:
// str.replace(int pos, int nchar, char *s);
// str.replace(int pos, int nchar, string s);
// str.replace(int pos, int nchar, int n, int ch);

// Hàm s.erase(x, n)
// Xóa n ký tự bắt đầu tại vị trí x.

void findSpace(int *&space, string s)
{
	int cnt = 0;
	for (int i = 0; i < s.size(); i++)
		if (s[i] == ' ')
			space[cnt++] = i;
}
void getMatrix(fstream& input, int**& a, int& row, int& col)
{
	input.open("data.txt", ios::in);
	input >> row >> col;
	a = new int* [row];
	for (int i = 0; i < row; i++)
		a[i] = new int[col];
	int *space = new int[col - 1];
	int dong = 0, cot = 0;
	input.ignore();
	while(!input.eof())
	{
		string s;
		getline(input, s);
		findSpace(space, s);
		a[dong][0] = stoi(s.substr(0, space[0]));
		for (int i = 1; i < col - 1; i++)
			a[dong][i] = stoi(s.substr(space[i - 1] + 1, space[i] - space[i - 1]));
		a[dong][col - 1] = stoi(s.substr(space[col - 2]));
		dong++;
	}
	input.close();
}
int main()
{

    return 0;
}