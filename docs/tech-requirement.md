1. Функциональность проекта

Проект выполняет функцию моделирования процесса жизни особей, размещаемых пользователем на  клеточном поле,  традиционно называемом вселенной. Каждая особь находится в отдельной клетке. Сменяемость поколений происходит по следующим правилам:

•	в пустой клетке, рядом с которой ровно три живые клетки, зарождается жизнь;

•	если у особи есть две или три живые соседки,  она продолжает жить; в противном случае (если соседей меньше двух или больше трёх) особь умирает («от одиночества» или «от перенаселённости»).

Управление:

•	выбор клетки при помощи стрелочек или букв (w, a, s, d)

•	изменение состояния текущей клетки – нажатие клавиши Enter) 

•	запуск автоматической смены поколений – клавиша R

•	пауза автоматической смены поколений – клавиша S

•	смена одного поколения – клавиша O

•	очистить поле – клавиша K

Основной функционал:

•	выбор стартовых  клеток с особями

•	смена поколений по правилам игры «Жизнь»

Дополнительный функционал:

•	Изменение настроек игры (размер поля, задержка между изменениями состояния поля, цвет мертвых и живых клеток)

•	Возможность запуска игры в браузере

•	ios версия для запуска на телефоне

•	Создание статистики

•	Сохранение состояний поля

•	Удаление сохранений

•	Загрузка сохраненной конфигурации поля

•	Выбор загружаемой конфигурации поля

•	Возможность изменять состояние клетки в процессе работы программы

•	Изменение состояний клеток при помощи мыши
 

2. Этапы разработки проекта
1.	Разработка черновой версии проекта без графической части (консольный вариант проекта):
•	Ввод стартовых клеток посредством ввода пар чисел (n; m), где n – номер строки; m – номер столбца. Пары чисел вводятся через Enter. Ввод оканчивается, когда вводится терминирующее значение (-1)
•	Программа работает только пошагово
•	Каждый шаг выводится булева таблица 9 на 9, где 1 – живая клетка, 0 - мертвая
•	Размер поля 9Х9
2.	Разработка дизайна интерфейса
3.	Внедрение графического интерфейса в черновую версию (используя SFML)
4.	Добавление в приложение окон меню, управлений сохранениями, загрузку сохранений
5.	Добавление возможности менять параметры приложения
6.	Тестирование приложения
 

3. Техническая часть
•	Логика работы основных функций (сменяемость поколений)
![logic](https://user-images.githubusercontent.com/108337603/236636846-6d1994b1-1ef7-4b19-9e9c-2aac60fb0346.png)

•	Связь элементов программы:

![Снимок экрана 2023-05-06 235602](https://user-images.githubusercontent.com/108337603/236637190-e8baf1c8-8f49-4c67-8940-cf175cf887af.png)

Данные:

•	текстовые файлы, хранящие состояния поля;

•	координаты «живых клеток», получаемые с устройства ввода;

•	Команды, получаемые с устройства ввода.

Файлы сохранений:
1.	Сохранения записываются через символ перевода каретки (/n)
2.	В строке хранятся записи – конфигурации поля.
3.	Записи отделяются друг от друга запятой.
4.	Первая запись в строке: матрица, записанная в формате: количество подряд идущих элементов матрицы-элемент, который повторяется в матрице + пробел. 
5.	Остальные записи должны начинаться с имени переменной+’=’+данные, например, map_size=60*40. Список возможных переменных представлен в следующем пункте
•	Связь окон графического интерфейса:
![maket](https://user-images.githubusercontent.com/108337603/236636945-742077a8-8a54-4f1f-a0c6-f43da95c2ee5.png)