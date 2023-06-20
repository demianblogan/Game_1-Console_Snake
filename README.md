[![en](https://img.shields.io/badge/Language-English-red.svg)](https://github.com/demianblogan/Game-Console_Snake/edit/main/README.md)
[![ru](https://img.shields.io/badge/Language-Russian-blue.svg)](https://github.com/demianblogan/Game-Console_Snake/blob/main/README.ru.md)
[![ua](https://img.shields.io/badge/Language-Ukrainian-green.svg)](https://github.com/demianblogan/Game-Console_Snake/blob/main/README.ua.md)

# Brief description of the game
This is the second game for my portfolio. It's a classic Snake game with a few extra functions, such as menus, score tables, company with 5 levels, and graphics presets.

![1](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/6366a978-9c50-4139-8ec0-bc563450f89e)

## **Game controls (in menus):**<br />
Arrow up    -> Move cursor to upper item<br />
Arrow down  -> Move cursor to lower item<br />
Arrow left  -> Swipe left tutorial guide<br />
Arrow right -> Swipe right tutorial guide<br />
Enter       -> Select item<br />
Escape      -> Go to the main menu / Quit the game<br />

## **Game controls (in game):**<br />
Arrow up    -> Move snake up<br />
Arrow down  -> Move snake down<br />
Arrow left  -> Move snake left<br />
Arrow right -> Move snake right<br />
Escape      -> Go to the main menu<br />

## **How to play?**<br />
When you start the game, you'll see two start logos (my "company" logo and the game logo). You can skip them by clicking any key. Then you'll see the main menu. The game has two modes: classic and company. Classic - you play until you hit your part, and you can go through the walls. The company has 5 levels, and to pass every one of them, you need to collect 10 apples. You can't go through the walls so be aware!

## **How to create and build this project in Visual Studio?**<br />
NOTE: I need to have installed Visual Studio 2022, which supports C++17 standard. Google how to do it.<br />

1. Download this repository as a .zip file and extract it.<br />
![image](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/caa1594d-2431-4a75-9ac6-bdd0313911b8)

2. Create an empty C++ project in Visual Studio.<br />
![image](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/cbe4365d-a216-415e-be7a-3e93a2ca1325)

3. Open the project's folder in File Explorer and move all files from the archive into it.<br />
![image](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/68cf7224-f600-4c2a-835b-c407ccdc367d)

4. To make all those files visible in your project, click the button "Show all files" in Solution Explorer.<br />
![image](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/7e145faf-8aa6-4cef-8550-7dd5f16182b3)

5. Let's change the project's standard to C++17. Go to the project's properties. Select "All Configurations" and "All Platforms". In "Configuration Properties" go to the tab "General", find "C++ Language Standard" and select "ISO C++17 Standard (/std:c++17"<br />
![image](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/f468265d-2ad4-4c5a-9b53-4c942198646d)

6. That's it! Press "Apply". To compile & launch the game, press "Ctrl + F5".
