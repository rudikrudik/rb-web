
# Веб сервер "rb-web" на epoll сокетах

---
<b>Веб-сервер принимает и выполняет запросы от клиентов на получение статического содержимого HTML-страниц, файлов, изображений и видео. Обрабатывает только HTTP-запросы и ответы.</b>

---
## Требования
Для установки и запуска проекта, необходимо:
- linux
- gcc version > 11.4.0
- c++17

---
## Технологии
- linux epoll
- c++17

---
## Сборка и запуск:

- Для начала работы скопируйте репозиторий:
```
$ git clone https://github.com/rudikrudik/rb-web.git
```
- Перейдите в каталог с исходным кодом и скомпилируйте код:
```
$ g++ src/main.cpp src/Config.cpp  src/Logger.cpp  src/ReadData.cpp  src/TcpListener.cpp  src/WebServer.cpp -o rb-web

```
- Запустите приложение с параметрами "-c путь_до_файла_конфигурации":
```
$ sudo ./rb-web -c config.ini
```
<br/>



---
<b>Пример файла конфигурации:</b>
```
[server]
## IP адрес сервера и порт
ip = 127.0.0.1
port = 8080

[file]
## путь к файлам html
wwwroot = /mnt/c/soft/cpp/webserver-linux/www/
## путь к странице 404.html
wwwerror = /mnt/c/soft/cpp/webserver-linux/error_directory/

[logs]
## путь к лог файлу
logfile = /mnt/c/soft/cpp/webserver-linux/logs/log.txt

## Уровни логирования:
## сonsole_log_level - вывод отладочной информации в stderr
## file_log_level - запись отладочной информации в лог файл
## 0 = DEBUG, 1 = INFO, 2 = WARNING, 3 = ERROR, 4 = CRITICAL
console_log_level = 0
file_log_level = 0
```

---
## To do
- Запуск в виде демона
- Обрабатывать ответы в многопоточном режиме
---
## Команда проекта
- Бахман Рудольф - software engineer
  - telegram - https://t.me/rudik_rudik
  - email - rudik.login@gmail.com
---
## Источники
- C10k problem



