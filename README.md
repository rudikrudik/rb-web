
# Веб сервер "rbweb" на epoll сокетах

<b>Веб-сервер принимает и выполняет запросы от клиентов на получение статического содержимого HTML-страниц, файлов, изображений и видео. Обрабатывает только HTTP-запросы и ответы.</b>

## Требования
Для установки и запуска проекта, необходимо:
- ubuntu, centos
- gcc version > 11.4.0
- c++17


## Технологии
- linux epoll
- c++17


## Сборка из исходников:
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

## Установка rpm пакета
- Скопируйте последнюю версию пакета
```
wget https://github.com/rudikrudik/rb-web/releases
```

## To do
- Запуск в виде демона
- Обрабатывать ответы в многопоточном режиме

## Команда проекта
- Бахман Рудольф - software engineer
  - telegram - https://t.me/rudik_rudik
  - email - rudik.login@gmail.com

## Источники
- C10k problem



