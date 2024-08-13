
# Веб сервер "rbweb" на epoll сокетах

<b>Веб-сервер принимает и выполняет запросы от клиентов на получение статического содержимого HTML-страниц, файлов, изображений и видео. Обрабатывает только HTTP-запросы и ответы.</b>

## Содержание
- [Требования](#requirements)
- [Технологии](#technologies)
- [Сборка из исходников](#make)
- [Установка rpm пакета](#rpm_make)
- [To do](#todo)
- [Команда проекта](#command)
- [Источники](#sources)

## <a id="requirements">Требования</a>
Для установки и запуска проекта, необходимо:
- ubuntu, centos
- gcc version > 11.4.0
- c++17


## <a id="technologies">Технологии</a>
- linux epoll
- c++17


## <a id="make">Сборка из исходников:</a>
*Раздел в процессе уточнения

- Для начала работы скопируйте репозиторий:
```
git clone https://github.com/rudikrudik/rb-web.git
```
- Перейдите в каталог с исходным кодом и скомпилируйте код:
```
g++ src/main.cpp src/Config.cpp  src/Logger.cpp  src/ReadData.cpp  src/TcpListener.cpp  src/WebServer.cpp -o rbweb

```
- Запустите приложение с параметрами "-c путь_до_файла_конфигурации":
```
sudo ./rbweb -c config.ini
```

## <a id="rpm_make">Установка rpm пакета</a>
- Скопируйте последнюю версию пакета
```
wget https://github.com/rudikrudik/rb-web/releases/latest/download/rbweb-Linux.deb
```
- Установите пакет
```
apt install rbweb-Linux.deb
```
- Запустите сервер
```
sudo rbweb -c /usr/share/rbweb/config/config.ini
```

## <a id="todo">To do</a>
- Запуск в виде демона
- Обрабатывать ответы в многопоточном режиме

## <a id="command">Команда проекта</a>
- Бахман Рудольф - software engineer
  - telegram - https://t.me/rudik_rudik
  - email - rudik.login@gmail.com

## <a id="sources">Источники</a>
- C10k problem



