[![en](https://img.shields.io/badge/Language-English-red.svg)](https://github.com/demianblogan/Game-Console_Snake/edit/main/README.md)
[![ru](https://img.shields.io/badge/Language-Russian-blue.svg)](https://github.com/demianblogan/Game-Console_Snake/blob/main/README.ru.md)
[![ua](https://img.shields.io/badge/Language-Ukrainian-green.svg)](https://github.com/demianblogan/Game-Console_Snake/blob/main/README.ua.md)

# Короткий опис гри
Це друга гра у моєму портфоліо. Це класична гра «Змійка» з кількома додатковими функціями, такими як меню, таблицею очок, компанія з 5 рівнями та графічніними налаштуваннями.

![1](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/6366a978-9c50-4139-8ec0-bc563450f89e)

## **Кнопки керування (в меню):**<br />
Стрілка вверх -> Перемістити курсор до верхнього пункту меню<br />
Стрілка вниз -> Перемістити курсор до нижнього пункту меню<br />
Стрілка вліво -> Перелистнути посібник гри вліво<br />
Стрілка вправо -> Перелистнути посібник гри вправо<br />
Enter -> Вибрати пункт меню<br />
Escape -> Перейти до головного меню / Вийти з гри<br />

## **Кнопки управління (у грі):**<br />
Стрілка вверх -> Направити змію вверх<br />
Стрілка вниз -> Направити змію вниз<br />
Стрілка вліво -> Направити змію вліво<br />
Стрілка вправо -> Направити змію вправо<br />
Escape -> Перейти до головного меню<br />

## **Як грати?**<br />
Під час запуску гри ви побачите дві заставки (логотип моєї "компанії" та логотип гри). Ви можете пропустити їх, натиснувши будь-яку клавішу. Потім ви побачите головне меню. У грі є два режими: класичний та кампанія. Класичний - граєш, поки не влучиш у частину свого тіла, також можна проходити крізь стіни. У компанії 5 рівнів, і щоб пройти кожен із них, потрібно зібрати 10 яблук. Ви не можете пройти крізь стіни, тож будьте обережні!

## **Як створити і скомпілювати цей проект у Visual Studio?**<br />
ЗАМІТКА: у вас має бути встановлена Visual Studio 2022, яка підтримує стандарт C++17. Гугліть, як її встановити.<br />

1. Скачайте цей репозиторій як .zip файл і розархівуйте його.<br />
![image](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/caa1594d-2431-4a75-9ac6-bdd0313911b8)

2. Створіть порожній C++ проект у Visual Studio.<br />
![image](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/cbe4365d-a216-415e-be7a-3e93a2ca1325)

3. Відкрийте папку проекту у провіднику та перемістіть усі файли з архіву туди.<br />
![image](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/68cf7224-f600-4c2a-835b-c407ccdc367d)

4. Щоб зробити всі ці файли видимими у вашому проекті, натисніть кнопку "Show all files" у Solution Explorer, після чого виберіть їх усіх і натисніть "Include in Project"<br />
![image](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/7e145faf-8aa6-4cef-8550-7dd5f16182b3)

5. Давайте змінимо страндарт проекту на C++17. Перейдіть до параметрів проекту. Виберіть "All Configurations" та "All Platforms". У "Configuration Properties" перейдіть до вкладки "General", знайдіть "C++ Language Standard" і виберіть "ISO C++17 Standard (/std:c++17")<br />
![image](https://github.com/demianblogan/Game-Console_Snake/assets/105989117/f468265d-2ad4-4c5a-9b53-4c942198646d)

6. Ось і все! Натисніть "Apply". Щоб скомпілювати та запустити гру, натисніть "Ctrl + F5".
