# Network Manager WiFi Interface

# ⚠️ THIS HAS BEEN MOVED TO [GITLAB](https://gitlab.com/crue-ton/wifi)! ⚠️

## Install
```sh
git clone https://github.com/crue-ton-school/wifi.git
cd wifi
sudo make install
```

## Uninstall
```sh
cd (repo directory)
sudo make uninstall
```

You can also pass "purge" which will remove the compiled wifi file where it was installed and get rid of the directory entirely
```sh
cd (repo directory)
sudo make purge
``` 

## Configuration
In the src directory when first cloning the repo, you will find two header files:
- `config.template.h`
- `config.def.h`

`config.template.h` is just for future reference and can be removed if you want.
`config.def.h` is just the file you want to make all your changes to.

### What you'll see in the config file

You will see something like this in the config.def.h file:
```cpp
// Known Networks //

/*
 * Leave Password field blank if there is no password for the connection
 *
*/

extern std::string knownNetworks[];
extern std::string networksPasswords[];

std::string knownNetworks[] = {
	"CafeWiFi",
	"HomeWiFi"
};

std::string networksPasswords[] = {
	"",
	"complicatedPassword"
};
```

The configuration gives you an example, which you should obviously change!

Basically, the first WiFi ssid is equal to the first password listed in the networksPasswords array.

## Usage

TODO: ADD MORE INFO

All basic usage flags:
```sh
wifi			| runs known networks funciton which are configured in config file
wifi -t 		| test wifi connection using curl
wifi -c			| Connect to WiFi `easier`
wifi -d 		| Disconnect from WiFi
wifi -g			| Get near WiFi networks
wifi -h			| Print help message
```
