#include <string>
#include <algorithm>
#include <vector>

using namespace std;

/*
    Format for messages in textfile:
    From: You
    "the text"
    Sent On: Fri, 26 Apr 2019 08:28:57 GMT


   The idea is to make use of that:
   1) every message is formatted in 3 lines as seen above
   2) every message ends with a timestamp

   A message struct is used.
   A vector containing objects of message struct is used.
   After reading both files, the messages are sorted with custom comparators.

*/

/* Cascade of boolean evaluations */
bool time_comp(const message& m1, const message& m2) {
 return month_comp(m1, m2);
}
bool month_comp(const message& m1, const message& m2) {
 if(m1.date.calenderMonth == m2.date.calenderMonth) return day_comp(m1, m2);
 return m1.date.calenderMonth < m2.date.calenderMonth;
}
bool day_comp(const message& m1, const message& m2) {
 if(m1.date.day == m2.date.day) return hour_comp(m1, m2);
 return m1.date.day < m2.date.day;
}
bool hour_comp(const message& m1, const message& m2) {
 if(m1.time.hour == m2.time.hour) return minute_comp(m1, m2);
 return m1.time.hour < m2.time.hour;
}
bool minute_comp(const message& m1, const message& m2) {
 if(m1.time.minute == m2.time.minute) return second_comp(m1, m2);
 return m1.time.minute < m2.time.minute;
}
bool second_comp(const message& m1, const message& m2) {
 return m1.time.second < m2.time.second;
}

struct message {
  string preface, text, sent, on, day, month;
  int calenderDay, hour, minute, second, year;
};


void read_file(const string& name, const string& filename, vector<message>& messages) {
  ifstream ifs(filename);
  string line;
  while(!ifs.eof()) {
    Message message;
    string l1, l2, l3; //A message is always 3 lines; l1 - preface, l2 - the text, l3 - timestamp
    getline(ifs, l1);
    getline(ifs, l2);
    getline(ifs, l3);
    if(name == Alice) { message.preface = "Alice:"; }
    if(name == Bob) { message.preface = "Bob:"; }
    message.preface = l1;
    message.text = l2;
    stringstream iss(l3);
    iss >> message.sent >> message.on >> message.day >> message.calenderDay
        >> message.month >> message.year;
    message.hour = stod(s.substr(25, 26));
    message.minute = stod(s.substr(29,30));
    message.second = stod(s.substr(32,33));
    messages.push_back(message);
  }
}

void print(vector<message> conversation) {
  for(auto it = conversation.begin(); it != conversation.end(); ++it) {
    Message m = conversation.at(it);
    cout << m.preface << "\n" << m.text << "\n"
    << m.sent << " " << m.on << " " << m.day << " " << m.calenderDay << " "
    << m.month << " " << m.year << " "
    << m.hour << ":" << m.minute << ":" << m.second << endl;
  }
}

int main() {
  string aliceFile = "alice.txt";
  string bobFile = "bob.txt";
  vector<message> conversation;
  read_file("alice", aliceFile, conversation);
  read_file("bob", bobFile, conversation);
  sort(conversation.begin(), conversation.end(), time_comp);
  print(conversation);
  // string ofname = "conversation.txt";
  // ostream_iterator<std::string> output_iterator(ofname, "\n");
  // copy(conversation.begin(), conversation.end(), )
}
