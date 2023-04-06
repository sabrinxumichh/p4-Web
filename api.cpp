// Project UID c1f28c309e55405daf00c565d57ff9ad
#include <list>
#include <string>
#include <iostream>
#include "json.hpp"
using nlohmann::json;

using namespace std;

class OHQueue {
public:
  OHQueue() {
    size = 0;
  }
  void responses(string method, string path, OHQueue ohQ) {
     // cout << "in repoinses: "<<method<<","<<path<<endl;
      if (method == "GET" && path == "/api/") {
        string junk;
        for (int i = 0; i < 4; i++) {
          getline(cin, junk);
         //cout << "line: "<<junk<<endl;
        }
        get_api();
      }
      else if (method == "GET" && path == "/api/queue/head/") {
       // cout <<"here"<<endl;
        string junk;
        for (int i = 0; i < 4; i++) {
          getline(cin, junk);
         //cout << "line: "<<junk<<endl;
        }
        get_api_queue_head();
      }
      else if (method == "POST" && path == "/api/queue/tail/") {
        string junk;
        for (int i = 0; i < 4; i++) {
          getline(cin, junk);
         //cout << "line: "<<junk<<endl;
        }
        json j1;
        cin >> j1;
        post_api_queue_tail(j1);
        size++;
      }
      else if (method == "DELETE" && path == "/api/queue/head/") {
        string junk;
        for (int i = 0; i < 4; i++) {
          getline(cin, junk);
         //cout << "line: "<<junk<<endl;
        }
        delete_api_queue_head();
        size--;
      }
      else if (method == "GET" && path == "/api/queue/") {
        string junk;
        for (int i = 0; i < 4; i++) {
          getline(cin, junk);
         //cout << "line: "<<junk<<endl;
        }
        //cout << "here again" << endl;
        get_api_queue();
      }
    
  }
  
  void errors_handle() {
    cout << "HTTP/1.1 400 Bad Request" << endl;
    cout << "Content-Type: application/json; charset=utf-8" << endl;
    cout << "Content-Length: 0" << endl << endl;
  }

  void get_api() {
    cout << "HTTP/1.1 200 OK" << endl;
    cout << "Content-Type: application/json; charset=utf-8" << endl;
    json j = {
      {"queue_head_url", "http://localhost/queue/head/"},
      {"queue_list_url", "http://localhost/queue/"},
      {"queue_tail_url", "http://localhost/queue/tail/"}
    };
    string str2 = j.dump(4) + "\n";
    size_t content_length = str2.length();
    cout << "Content-Length: " << content_length << endl << endl;
    cout << str2;
  }

  void get_api_queue_head() {
    cout << "HTTP/1.1 200 OK" << endl;
    cout << "Content-Type: application/json; charset=utf-8" << endl;
    json j = {
      {"location", queue.begin()->location},
      {"position", 1},
      {"uniqname", queue.begin()->uniqname}
    };
    string str3 = j.dump(4) + "\n";
    size_t content_length = str3.length();
    cout << "Content-Length: " << content_length << endl << endl;
    cout << str3;
  }

  void get_api_queue() {
    //cout << "here" << endl;
    cout << "HTTP/1.1 200 OK" << endl;
    cout << "Content-Type: application/json; charset=utf-8" << endl;
    std::list <Student>::iterator it;
    json jn;
    json j;

    if (queue.size() == 0) {
      j["count"] = 0;
      j["results"] = "null";
    }
    else {
      for (it = queue.begin(); it != queue.end(); it++) {
        json j_entry = {
          {"location", it->location},
          {"position", it->position},
          {"uniqname", it->uniqname}
        };
        jn.push_back(j_entry);
      }
      json j = {
        {"count", jn.size()},
        {"results", jn}
      };
      string str5 = j.dump(4) + "\n";
      size_t content_length = str5.length();
      cout << "Content-Length: " << content_length << endl << endl;
      cout << str5;
    }
      
  }

  void post_api_queue_tail(json j1) {
    cout << "HTTP/1.1 201 Created" << endl;
    cout << "Content-Type: application/json; charset=utf-8" << endl;

    //cin >> j1;
    Student stu;
    stu.location = j1["location"];
    stu.uniqname = j1["uniqname"];
    stu.position = queue.size() + 1;

    queue.push_back(stu);

    json j = {
      {"location", stu.location},
      {"position", stu.position},
      {"uniqname", stu.uniqname}
    };
    string str4 = j.dump(4) + "\n";
    size_t content_length = str4.length();
    cout << "Content-Length: " << content_length << endl << endl;
    cout << str4;
  }

  void delete_api_queue_head() {
    if (queue.size() == 0) {
      errors_handle();
    }
    else {
      std::list <Student>::iterator it;
      queue.pop_front();
      for (it = queue.begin(); it != queue.end(); it++) {
        it->position--;
      }
      cout << "HTTP/1.1 204 No Content" << endl;
      cout << "Content-Type: application/json; charset=utf-8" << endl;
      cout << "Content-Length: 0" << endl << endl;
    }
  }

private:
  struct Student {
    string location;
    string uniqname;
    int position;
  };
  int size;
  std::list<Student> queue;
 
};

int main()
{
  OHQueue ohQ;
  string method;
  string path;
  string junk;
  string host;
  string content;
  string length;

  while (cin >> method >> path) {
    if ((path != "/api/") && (path != "/api/queue/") && 
    (path != "/api/queue/head/") && (path != "/api/queue/tail/")) {
      getline(cin, junk);
      getline(cin, host);
      getline(cin, content);
      getline(cin, length);
      
      ohQ.errors_handle();
    }
    else if (method == "GET" && ((path != "/api/") && 
    (path != "/api/queue/") && (path != "/api/queue/head/"))) {
      getline(cin, junk);
      getline(cin, host);
      getline(cin, content);
      getline(cin, length);
      ohQ.errors_handle();
    }
    else if (method == "POST" && path != "/api/queue/tail/") {
      getline(cin, junk);
      getline(cin, host);
      getline(cin, content);
      getline(cin, length);
      ohQ.errors_handle();
    }
    else if (method == "DELETE" && path != "/api/queue/head/") {
      getline(cin, junk);
      getline(cin, host);
      getline(cin, content);
      getline(cin, length);
      ohQ.errors_handle();
    }
    else {
      ohQ.responses(method, path, ohQ);
    }
  }
  return 0;
}


