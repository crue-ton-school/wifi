/*
 * A easier interface for nmcli writtin in c++
 */

#include <iostream>
#include <string>

using namespace std;

int connect() {
  string ssid;
  string password;
  cout << "Enter WiFi SSID: ";
  cin >> ssid;
  cout << "Enter Password: ";
	getline(cin, password);

  #ifdef _WIN32
  string cmd = "netsh wlan connect " + ssid;
  system(cmd.c_str());
  #endif

  #ifdef linux
  if (password.empty()) {
    string cmd = "sudo nmcli d wifi connect " + ssid;
    system(cmd.c_str());
		return 0;
  } else {
    string cmd = "sudo nmcli d wifi connect " + ssid + " password " + password;
    system(cmd.c_str());
  }
  #endif
	return 0;
}

int testwifi() {
  string website = "https://www.gnu.org";
  bool askforinput = false;

  #ifdef _WIN32
  string cmd = "curl -s " + website + " >nul 2>&1";
  #endif
  #ifdef linux
  string cmd = "curl -s " + website + " >/dev/null";
  #endif

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

void get_networks() {
	string networks = exec("nmcli -t -f active,ssid dev wifi");
	networks = networks.substr(networks.find(":") + 1);
	cout << networks;
}

int main(int argc, char * argv[]) {
  for (int i = 0; i < argc; ++i) {
    if (string(argv[i]) == "-t") {
      testwifi();
    } else if (string(argv[i]) == "-d") {
      string currentConnection = exec("_c=$(nmcli -t -f active,ssid dev wifi | grep \"^yes\");echo ${_c##*:}");
      string cmd = "sudo nmcli con down id " + currentConnection;
      system(cmd.c_str());
    } else if (string(argv[i]) == "-c") {
      connect();
		} else if (string(argv[i]) == "-g") {
			get_networks();
    } else if (2 > argc) {
      cout << "All available flags:" << endl << "\t-t To test the WiFi connection using curl." << endl;
      cout << "\t-d disconnect from the WiFi [REQUIRES SUDO PASSWORD ON LINUX]" << endl;
      cout << "\t-c connect to WiFi [REQUIRES SUDO PASSWORD ON LINUX]" << endl;
    }
  }
}
