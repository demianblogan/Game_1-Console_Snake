[![en](https://img.shields.io/badge/Language-English-red.svg)](https://github.com/demianblogan/Game-Console_Snake/edit/main/README.md)
[![ru](https://img.shields.io/badge/Language-Russian-blue.svg)](https://github.com/demianblogan/Game-Console_Snake/blob/main/README.ru.md)
[![ua](https://img.shields.io/badge/Language-Ukrainian-green.svg)](https://github.com/demianblogan/Game-Console_Snake/blob/main/README.ua.md)

# Краткое описание игры
Это вторая игра в моем портфолио. Это классическая игра «Змейка» с несколькими дополнительными функциями, такими как меню, таблицы очков, компания с 5 уровнями и графические предустановки.

![1](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/6366a978-9c50-4139-8ec0-bc563450f89e)

## **Кнопки управления (в меню):**<br />
Стрелка вверх -> Переместить курсор на верхнему пункту меню<br />
Стрелка вниз -> Переместить курсор к нижнему пункту меню<br />
Стрелка влево -> Пролистать руководство по игре влево<br />
Стрелка вправо -> Пролистать руководство по игре вправо<br />
Enter -> Выбрать пункт меню<br />
Escape -> Перейти в главное меню / Выйти из игры<br />

## **Кнопки управления (в игре):**<br />
Стрелка вверх -> Направить змею вверх<br />
Стрелка вниз -> Направить змею вниз<br />
Стрелка влево -> Направить змею влево<br />
Стрелка вправо -> Направить змею вправо<br />
Escape -> Перейти в главное меню<br />

## **Как играть?**<br />
При запуске игры вы увидите две заставки (логотип моей "компании" и логотип игры). Вы можете пропустить их, нажав любую клавишу. Затем вы увидите главное меню. В игре есть два режима: классический и кампания. Классический — играешь, пока не попадешь в часть своего тела, также можно проходить сквозь стены. В компании 5 уровней, и чтобы пройти каждый из них, нужно собрать 10 яблок. Вы не можете пройти сквозь стены, так что будьте осторожны!

## **Как создать и скомпилировать этот проект в Visual Studio?**<br />
ЗАМЕТКА: у вас должна быть установлена Visual Studio 2022, которая поддерживает стандарт C++17. Гуглите, как её установить.<br />

1. Скачайте этот репозиторий как .zip файл и розархивируйте его.<br />
![image](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/caa1594d-2431-4a75-9ac6-bdd0313911b8)

2. Создайте пустой C++ проект в Visual Studio.<br />
![image](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/cbe4365d-a216-415e-be7a-3e93a2ca1325)

3. Откройте папку проекта в проводнике и переместите все файлы из архива туда.<br />
![image](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/68cf7224-f600-4c2a-835b-c407ccdc367d)

4. Чтобы сделать все эти файлы видимыми в вашем проекте, нажтиме на кнопку "Show all files" в Solution Explorer, после чего выберите их всех и нажмите "Include in Project"<br />
![image](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/7e145faf-8aa6-4cef-8550-7dd5f16182b3)

5. Давайте изменим страндарт проекта на C++17. Перейдите к настройкам проекта. Выберите "All Configurations" и "All Platforms". В "Configuration Properties" перейдите ко вкладке "General", найдите "C++ Language Standard" и выберите "ISO C++20 Standard (/std:c++17"<br />
![image](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/f468265d-2ad4-4c5a-9b53-4c942198646d)

6. Вот и всё! Нажмите "Apply". Чтобы скомпилировать и запустить игру, нажмите "Ctrl + F5".
