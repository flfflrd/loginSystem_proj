# loginSystem

Written in C++, a basic project to start learning the language.
Basic syntax, object types and conversions, file operations, user io.

The program takes arguments listed in the -h help output, to register a new
user or login as existing, checking or saving the input to a text file.
Passwords will be encrypted. The program can be used entirely with command-line
arguments.

I had a lot of trouble implementing cryptography. Most stackoverflow posts were
outdated and well beyond my understanding. Type conversions, hash tables, etc.
After banging my head against the problem for three hours, my roommate Sithum
had a look and mentioned ChatGPT. Just fixed it straight up in a few minutes.
Im not proud of the solution, but it is done. And I know now what I have to
learn before I tackle this problem again.

g++ cloginSystem.cpp -o loginSystem -lcrypto -lssl
