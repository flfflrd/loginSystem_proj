#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <openssl/sha.h>

using namespace std;

vector<pair<string, string>> userpass;

// Big thanks to Sithum and ChatGPT for this hasher. No idea how it works.
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
	for (const auto& pair : userpass) {
		userpass_db << pair.first << endl;
		userpass_db << pair.second << endl;
	}
	userpass_db.close();
	return 0;
}

int UserAccess(int option, string user, string pass) {
	switch (option) {
		case 0:
			pass = stringhasher(pass);
			for (const auto& pair : userpass) {
				if (pair.first == user && pair.second == pass) {
					cout << "Login successful\n";
					return 0;
				}
			}
			cout << "Incorrect username or password\n";
			return 1;
			break;
		case 1:
			string hashed_pass = stringhasher(pass);
			userpass.emplace_back(user, hashed_pass);
			return 0;
			break;
	}
	return 1;
}

int main(int argc, char* argv[]) {
	Read();

	if (argc == 3) {
		string username_input = argv[2];
		string password_input;
		cout << "Password: ";
		cin >> password_input;
		int option;
		if (!strcmp(argv[1], "-l"))
			option = 0;
		if (!strcmp(argv[1], "-r"))
			option = 1;
		UserAccess(option, username_input, password_input);
	} else {
		cout << "Usage: loginChecker [option] <username>\n";
		cout << "-h \t Shows this message\n";
		cout << "-l \t Login\n";
		cout << "-r \t Register\n";
	}

	Write();
	return 0;
}

