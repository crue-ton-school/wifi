/*
 * A easier interface for nmcli writtin in c++
 */

#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <string>

using namespace std;

string elvCmd;
void getsuper() {
	// Check if ran with sudo/doas
	string _c;
	auto privs = geteuid();

	if (privs != 0) { 
		cout << "Warning! Some flags require elevation!\n\n";
		if (!system("which sudo > /dev/null 2>&1") && !system("which doas > /dev/null 2>&1")) {
			cout << "sudo and doas found on system..." << endl << "Please choose one!" << endl;
			cout << "[1] sudo\n[2] doas\n" << "[1-2]: ";
			getline(cin, _c);
			if (_c == "1") { elvCmd = "sudo";
			} else if (_c == "2") { elvCmd = "doas";
			} else { cout << "not valid choice!"; }

		} else if (!system("which sudo > /dev/null 2>&1")) { 
			elvCmd = "sudo";
		} else if (!system("which doas > /dev/null 2>&1")) {
			elvCmd = "doas";
		} else {
			throw std::runtime_error("sudo nor doas found!\nRun with a similar program for some flags for them to work!\n\n");
		}
	}
}


string exec(string command) {
  char buffer[128];
  string result = "";

  // Open pipe to file
  FILE * pipe = popen(command.c_str(), "r");
  if (!pipe) {
    return "popen failed!";
  }

  // read till end of process:
  while (!feof(pipe)) {

    // use buffer to read and add to result
    if (fgets(buffer, 128, pipe) != NULL)
      result += buffer;
  }

  pclose(pipe);
  return result;
}

int connect() {
  string ssid;
  string password;
  cout << "Enter WiFi SSID: ";
	getline(cin, password);
  cout << "Enter Password: ";
	getline(cin, password);
	getsuper();

  if (password.empty()) {
    string cmd = elvCmd + " nmcli d wifi connect " + ssid;
    system(cmd.c_str());
		return 0;
  } else {
    string cmd = elvCmd + " nmcli d wifi connect " + ssid + " password " + password;
    system(cmd.c_str());
  }
	return 0;
}

int testwifi() {
  string website = "https://www.gnu.org";
  bool askforinput = false;
  string cmd = "curl -s " + website + " >/dev/null";

  if (askforinput == true) {
    cout << "Enter website of choice: ";
    cin >> website;
    int status = system(cmd.c_str());
    if (status == 0) {
      cout << "Connection is good!" << endl;
    } else {
			throw std::runtime_error("Connection seems to fail, check connections!\n");
    }

  } else if (askforinput == false) {
    int status = system(cmd.c_str());
    if (status == 0) {
      cout << "Connection is good!" << endl;
    } else {
			throw std::runtime_error("Connection seems to fail, check connections!\n");
    }
  }
	return 0;
}

void get_networks() {
	string networks = exec("nmcli -t -f active,ssid dev wifi");
	networks = networks.substr(networks.find(":") + 1);	
	cout << networks << endl;
}

void disconnect() {
	getsuper();
	string currentConnection = exec("nmcli -t -f active,ssid dev wifi|grep \"^yes:\"");
	currentConnection = currentConnection.substr(currentConnection.find("yes:") + 4);
  string cmd = elvCmd + " nmcli con down id " + currentConnection;
  system(cmd.c_str());
}

// add windows support to other flags
int main(int argc, char * argv[]) {
  for (int i = 0; i < argc; ++i) {
    if (string(argv[i]) == "-t") {
      testwifi();
    } else if (string(argv[i]) == "-d") {
			disconnect();
    } else if (string(argv[i]) == "-c") {
      connect();
		} else if (string(argv[i]) == "-g") {
			get_networks();
    } else if (2 > argc) {
      cout << "All available flags:" << endl << "\t-t To test the WiFi connection using curl." << endl;
      cout << "\t-d disconnect from the WiFi [requires su passwd" << endl;
      cout << "\t-c connect to WiFi [requires su passwd]" << endl;
    }
  }
}
