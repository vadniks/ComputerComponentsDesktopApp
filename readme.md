
```
 ____                                                               __               
/\  _`\                                                            /\ \__            
\ \ \/\_\    ___     ___ ___   _____     ___     ___      __    ___\ \ ,_\    __     
 \ \ \/_/_  / __`\ /' __` __`\/\ '__`\  / __`\ /' _ `\  /'__`\/' _ `\ \ \/  /'__`\   
  \ \ \L\ \/\ \L\ \/\ \/\ \/\ \ \ \L\ \/\ \L\ \/\ \/\ \/\  __//\ \/\ \ \ \_/\ \L\.\_ 
   \ \____/\ \____/\ \_\ \_\ \_\ \ ,__/\ \____/\ \_\ \_\ \____\ \_\ \_\ \__\ \__/.\_\
    \/___/  \/___/  \/_/\/_/\/_/\ \ \/  \/___/  \/_/\/_/\/____/\/_/\/_/\/__/\/__/\/_/
                                 \ \_\                                               
                                  \/_/                                               
```

This is a QT (C++) port of the [Mobile client](https://github.com/vadniks/ComputerComponentsAndroidApp) 
for desktop systems. The [Server](https://github.com/vadniks/ComputerComponentsWebApp2_back) 
is required for this client-side application.

## Build
To build the application with CLang compiler on Linux machine 
just execute the following commands from the repository root:
```shell
mkdir build && cd build
cmake .. && make all
chmod +x build/ccda
```
After successful build the executable will be located in the `build` folder.

## Screenshots
![Main page](screenshots/a.png "Main page")
![Select page](screenshots/b.png "Select page")
![Select page showing component details](screenshots/c.png "Select page showing component details")
![Expanded select page showing component details](screenshots/d.png "Expanded select page showing component details")
![About page](screenshots/e.png "About page")
![Login page](screenshots/f.png "Login page")
![Expanded login page](screenshots/g.png "Expanded login page")
![Expanded main page](screenshots/h.png "Expanded main page")
![Orders page](screenshots/i.png "Orders page")
![Orders page](screenshots/j.png "Orders page")
![Login page with credentials](screenshots/k.png "Login page with credentials")
