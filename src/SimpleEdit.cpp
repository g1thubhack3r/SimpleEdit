#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
string buffer;
void bhelp()
{
	cout << "Basic mode help:" << endl;
	cout << "o: (O)pen file" << endl;
	cout << "q: (Q)uit editor" << endl;
	cout << "e: (E)xit editor" << endl;
	cout << "h: Show (H)elp" << endl;
	cout << "?: Show help" << endl;
}
void fhelp()
{
	cout << "File mode help:" << endl;
	cout << "w: (W)rite a line" << endl;
	cout << "r: (R)ead the whole file" << endl;
	cout << "t: (T)ell the cursor's position" << endl;
	cout << "s: (S)eek the cursor and change its position" <<endl;
	cout << "f: Save the (F)ile" << endl;
	cout << "q: (Q)uit without save" << endl;
	cout << "e: (E)xit without save" << endl;
	cout << "d: (D)elete some character" << endl;
	cout << "h: Show (H)elp" << endl;
	cout << "?: Show help" << endl;
}
void fw()
{
	string line;
	cout << "Line:";
	getline(cin, line);
	getline(cin, line);
	buffer += line;
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	buffer += "\r\n";
	#elif __APPLE__
	buffer += "\r";
	#elif __linux__ || __unix__ || defined(_POSIX_VERSION)
	buffer += "\n";
	#else
	#error "Unknown platform, SimpleEdit supports Windows, Apple's OS, Linux, Unix and POSIX."
	#endif
}
void fr()
{
	cout << buffer << endl;
}
void ft(fstream &file)
{
	cout << "Cursor at position " << file.tellg() << endl;
}
void fs(fstream &file)
{
	cout << "Position:";
	int pos;
	cin >> pos;
	file.seekg(pos, ios::beg);
}
void ff(fstream &file, string filename)
{
	int tmppos = file.tellg();
	file.close();
	file.open(filename, ios::in | ios::out);
	string tmp = buffer;
	int find1, find2;
	do
	{
		#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
		find1 = tmp.find("\r\n");
		find2 = tmp.rfind("\r\n");
		#elif __APPLE__
		find1 = tmp.find("\r");
		find2 = tmp.rfind("\r");
		#elif __linux__ || __unix__ || defined(_POSIX_VERSION)
		find1 = tmp.find("\n");
		find2 = tmp.rfind("\n");
		#else
		#error "Unknown platform, SimpleEdit supports Windows, Apple's OS, Linux, Unix and POSIX."
		#endif
		file << tmp;
		tmp.erase(tmp.begin(), (string::iterator)(&tmp[find1]));
	}while (find1 != find2);
}                                                              
void fd(fstream &file, string filename)
{	
	cout << "Character number:";
	int cnum;
	cin >> cnum;
	if (cnum > buffer.size())
	{
		cout << "Delete character number > buffer character number, delete all(y/n, default n)?";
		char choose;
		cin >> choose;
		switch (choose)
		{
			case 'y':
			case 'Y':
				cnum = buffer.size();
				break;
			case 'n':
			case 'N':
			default:
				cnum = 0;
		}
	}
	for (int i = 1; i <= cnum; i++) buffer.erase(buffer.end() - 1);
	ff(file, filename);
}
void fmode()
{
	string filename;
	cout << "Enter filename:";
	cin >> filename;
	fstream file(filename, ios::in | ios::out | ios::app);
	while (!file.eof())
	{
		string tmp;
		file >> tmp;
		buffer += tmp;
	}
	while (true)
	{
		char c;
		cout << "Enter action(h for help):";
		cin >> c;
		switch (c)
		{
			case 'w':
			case 'W':
				fw();
				break;
			case 'r':
			case 'R':
				fr();
				break;
			case 't':
			case 'T':
				ft(file);
				break;
			case 's':
			case 'S':
				fs(file);
				break;
			case 'f':
			case 'F':
				ff(file, filename);
				break;
			case 'd':
			case 'D':
				fd(file, filename);
				break;
			case 'q':
			case 'Q':
				buffer.clear();
				return;
			case 'e':
			case 'E':
				buffer.clear();
				return;
			case 'h':
			case 'H':
				fhelp();
				break;
			case '?':
				fhelp();
				break;
			default:
				cout << "Unknown command, h for help" << endl;
		} 
	}
}
int main()
{
	cout << "Simple Editor" << endl;
	char c;
	while (true)
	{
		cout << "Enter action(h for help):";
		cin >> c;
		switch (c)
		{
			case 'o':
			case 'O':
				fmode();
				break;
			case 'q':
			case 'Q':
				return 0;
			case 'e':
			case 'E':
				return 0;
			case 'h':
			case 'H':
				bhelp();
				break;
			case '?':
				bhelp();
				break;
			default:
				cout << "Unknown command, h for help" << endl;
		} 
	}
    return 0;
}
