#include <iostream>

#include "string.hpp"

void dump_string(const String& s);

int main(){

    String s1;
    dump_string(s1);

    std::cout << "Is s1 empty? Answer = " << s1.empty() << '\n' << '\n';

    const String s2 {"Hello World"};
    dump_string(s2);

    String s3 = "Hello World";
    dump_string(s3);

    String s4("Hello World");
    s4 = s4;                                        // correct assignment
    dump_string(s4);

    String s5(4, 'd');
    dump_string(s5);

    String s6 {s2};                                 // correct copy
    dump_string(s6);

    String s7 {"Hello World", 4};
    dump_string(s7);

    String s8 {"Hello World", 6, 5};
    dump_string(s8);

    String s9 {s2, 4};
    dump_string(s9);

    String s10 {s2, 6, 5};
    dump_string(s10);

    s10 = s5;                                       // correct assignemnt
    dump_string(s10);

    // Concatenation tests

    String s11 = s3 + " lalala" + " !";             // correct: String + const char*
    dump_string(s11);

    String s12 = s3 + s5 + " " + s8;                // correct String + String
    dump_string(s12);

    const String s13 = s2 + s3;                     // correct: const String =  const String + String
    dump_string(s13);

    // Resize tests

    String s14 {"Bob"};
    dump_string(s14);
    s14.resize(5);
    dump_string(s14);

    String s15 {"Tol"};
    dump_string(s15);
    s15.resize(5, 'a');
    dump_string(s15);
    std::cout << "s15.front = " << s15.front() << ", s15.back = " << s15.back() << ", s15[3] = " << s15[3] << "\n\n";

    std::cout << "Test +=\n";
   String s16 {"Bob"};
   s16 += s16;
   dump_string(s16);
   s16.push_back('!');                              // correct push_back
   dump_string(s16);

   s3.insert(6, "My ");                              // correct insert
   dump_string(s3);

    String s17 = "Em!!my";
    s17.erase(2, 2);
    dump_string(s17);

    String s18 = "Hello";
    s18.insert(s18.length(), " World");
    dump_string(s18);
    s18.replace(6, 5, "Cpp");
    dump_string(s18);

    String s19 = "Hello_World_!!!";
    s19.replace(0, s19.size(), '_', ' ');
    dump_string(s19);

    String s20 = "Foma";
    String s21 = "Rumy";
    s20.swap(s21);
    dump_string(s20);
    //dump_string(s21);

    String s22 = "Cool#";
    s22.pop_back();
    dump_string(s22);

    String s23 = s20.substr(0, 3);
    dump_string(s23);

    std::cout << "Result of comparing = " << s19.compare(s18) << "\n\n" ;

    // Test empty string

    String s24;
    std::cout << "s24 is empty? " << s24.empty() << '\n';
    s24.push_back('A');
    dump_string(s24);
    s24.pop_back();
    dump_string(s24);
    s24 += s3;
    dump_string(s24);

    String str25;
    std::cin >> str25;
    dump_string(str25);
}

void dump_string(const String& s){

    std::cout << "size = " << s.size() << '\n';
    std::cout << "capacity = " << s.capacity() << '\n';
    std::cout << "string = " << s << '\n' << '\n';
}
