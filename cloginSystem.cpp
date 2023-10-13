#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <openssl/sha.h>

using namespace std;

vector<pair<string, string>> userpass;

// big thanks to Sithum and ChatGPT
string stringhasher(const string& input) {
    unsigned char obuf[20];
    const unsigned char* ibuf = reinterpret_cast<const unsigned char*>(input.c_str());

    SHA1(ibuf, input.length(), obuf);

    string hashedString;
    for (int i = 0; i < 20; i++) {
        char buf[3];
        sprintf(buf, "%02x", obuf[i]);
        hashedString += buf;
    }

    return hashedString;
}

int Read() {
	string line, line2;
	ifstream userpass_db ("userpass_db");
	if (userpass_db.is_open()) {
		while (getline(userpass_db, line)) {
			getline(userpass_db, line2);
			userpass.emplace_back(line, line2);
		}
		userpass_db.close();
		return 0;
	}
	return 1;
}

int Write() {
	ofstream userpass_db ("userpass_db");
	for (int i=0; i<userpass.size(); i++) {
		userpass_db << userpass[i].first << endl;
		userpass_db << userpass[i].second << endl;
	}
	userpass_db.close();
	return 0;
}

int Login() {
	cout << "Username: ";
	string username_input;
	cin >> username_input;
	cout << "Password: ";
	string password_input;
	cin >> password_input;
	password_input = stringhasher(password_input);

	for (int i=0; i<userpass.size(); i++) {
		if (userpass[i].first == username_input) {
			if (userpass[i].second == password_input) {
				cout << "Login successful\n";
				return 0;
			}
		}
	}
	cout << "Incorrect username or password\n";
	return 1;
}

int NewUser() {
	
	cout << "Username: ";
	string username_input;
	cin >> username_input;
	cout << "Password: ";
	string password_input;
	cin >> password_input;
	password_input = stringhasher(password_input);

	userpass.emplace_back(username_input, password_input);

	return 0;

}

int main(int argc, char* argv[]) {
	Read();

	if (argc > 1) {
		if (!strcmp(argv[1], "-h")) {
			cout << "-h \t Shows this message\n";
			cout << "-l \t Login\n";
			cout << "-r \t Register\n";
		} else if (!strcmp(argv[1], "-l")) {
			Login();
		} else if (!strcmp(argv[1], "-r")) {
			NewUser();
		}
	}

	Write();
	return 0;
}

