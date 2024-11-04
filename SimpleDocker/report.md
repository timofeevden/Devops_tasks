# __Отчет по индивидуальному проекту SimpleDocker студента школы 21 turkatrj__

<a name="Contents"></a> 
## Оглавление

- [Part 1. Готовый докер](#Part 1)
- [Part 2. Операции с контейнером](#Part 2)
- [Part 3. Мини веб-сервер](#Part 3)
- [Part 4. Свой докер](#Part 4)
- [Part 5. Dockle](#Part 5)
- [Part 6. Базовый Docker Compose](#Part 6)

<a name="Part 1"></a> 
## Part 1. Готовый докер

### 1.1) Возьми официальный докер-образ с nginx и выкачай его при помощи docker pull.

Скачиваем официальный докер-образ с nginx при помощи команды `docker pull nginx` :

![screenshot](/src/images/1-1.png)

### 1.2) Проверь наличие докер-образа через docker images.

Используем команду `docker images` :

![screenshot](/src/images/1-2.png)

### 1.3) Запусти докер-образ через docker run -d [image_id|repository].

Флаг -d — это сокращение для --detach. Эта команда запускает контейнер в фоновом режиме. Это позволяет использовать терминал, из которого запущен контейнер, для выполнения других команд во время работы контейнера. `image_id = b690f5f0a2d5` (по информации из пункта 1.2).
Используем команду `docker run -d b690f5f0a2d5` :

![screenshot](/src/images/1-3.png)

### 1.4) Проверь, что образ запустился через docker ps.

Используем команду `docker ps` :

![screenshot](/src/images/1-4.png)

### 1.5) Посмотри информацию о контейнере через docker inspect [container_id|container_name].

`container_id = 505d5ff79318`. Используем команду `docker inspect 505d5ff79318` :

![screenshot](/src/images/1-5-1.png)

![screenshot](/src/images/1-5-2.png)

### 1.6) По выводу команды определи и помести в отчёт размер контейнера, список замапленных портов и ip контейнера.

Размер контейнера:

![screenshot](/src/images/1-6-1.png)

Список замапленных портов:

![screenshot](/src/images/1-6-2.png)

IP контейнера:

![screenshot](/src/images/1-6-3.png)


### 1.7) Останови докер образ через docker stop [container_id|container_name].

Останавливаем докер, обращаясь уже по названию командой `docker stop youthful_austin` :

![screenshot](/src/images/1-7.png)

### 1.8) Проверь, что образ остановился через docker ps.

Используем команду `docker ps` :

![screenshot](/src/images/1-8.png)

### 1.9) Запусти докер с портами 80 и 443 в контейнере, замапленными на такие же порты на локальной машине, через команду run.

Так как на данной машине 80 порт уже используется Apache2, необходимо его изменить в `/etc/apache2/ports.conf` на 8080 и перезапустить службу. Далее используем команду `docker run -p 80:80 -p 443:443 -d nginx` :

![screenshot](/src/images/1-9.png)

### 1.10) Проверь, что в браузере по адресу localhost:80 доступна стартовая страница nginx.

Открываем браузер и в адресной строке вводим `localhost:80` :

![screenshot](/src/images/1-10.png)

### 1.11) Перезапусти докер контейнер через docker restart [container_id|container_name].

Используем команду `docker restart ferent_ellis` :

![screenshot](/src/images/1-11.png)

### 1.12) Проверь любым способом, что контейнер запустился.

Используем команду `docker ps` :

![screenshot](/src/images/1-12.png)

[-> К оглавлению](#Contents)


<a name="Part 2"></a> 

## Part 2. Операции с контейнером


### 2.1) Прочитай конфигурационный файл nginx.conf внутри докер контейнера через команду exec.

Для удобства переименуем контейнер на `my_cont`. Далее используем команду `docker exec my_cont cat /etc/nginx/nginx.conf` :

![screenshot](/src/images/2-1.png)

### 2.2) Создай на локальной машине файл nginx.conf.

Используем команду `touch nginx.conf` :

![screenshot](/src/images/2-2.png)

### 2.3) Настрой в нем по пути /status отдачу страницы статуса сервера nginx.

Редакитуем файл командой `nano nginx.conf` :

![screenshot](/src/images/2-3.png)

### 2.4) Скопируй созданный файл nginx.conf внутрь докер-образа через команду docker cp.

Используем команду `docker cp nginx.conf my_cont:/etc/nginx/` :

![screenshot](/src/images/2-4.png)

### 2.5) Перезапусти nginx внутри докер-образа через команду exec.

Проверяем правильность синтаксиса файла командой `docker exec my_cont nginx -t`, далее используем команду `docker exec my_cont nginx -s reload` :

![screenshot](/src/images/2-5.png)

### 2.6) Проверь, что по адресу localhost:80/status отдается страничка со статусом сервера nginx.

В браузере проверяем вывод по адресу `localhost:80` и `localhost:80/status` :

![screenshot](/src/images/2-6.png)

### 2.7) Экспортируй контейнер в файл container.tar через команду export.

Используем команду `docker export my_cont > container.tar` :

![screenshot](/src/images/2-7.png)

### 2.8) Останови контейнер.

Используем команду `docker stop my_cont` :

![screenshot](/src/images/2-8.png)

### 2.9) Удали образ через docker rmi [image_id|repository], не удаляя перед этим контейнеры.

Используем команду `docker rmi -f nginx` :

![screenshot](/src/images/2-9.png)

### 2.10) Удали остановленный контейнер.

Используем команду `docker rm my_cont` :

![screenshot](/src/images/2-10.png)

### 2.11) Импортируй контейнер обратно через команду import.

Используем команду `docker import -c 'CMD ["nginx", "-g", "daemon off;"]' container.tar import_cont` :

![screenshot](/src/images/2-11.png)

### 2.12) Запусти импортированный контейнер.

Используем команду `docker run --name imp_cont -p 80:80 -p 443:443 -d import_cont` :

![screenshot](/src/images/2-12.png)

### 2.13) Проверь, что по адресу localhost:80/status отдается страничка со статусом сервера nginx.

В браузере проверяем вывод по адресу `localhost/status` :

![screenshot](/src/images/2-13.png)

[-> К оглавлению](#Contents)



<a name="Part 3"></a> 

## Part 3. Мини веб-сервер

### 3.1) Напиши мини-сервер на C и FastCgi, который будет возвращать простейшую страничку с надписью Hello World!.

Создаем файл с кодом `main.c`:

![screenshot](/src/images/3-1.png)

### 3.2) Запусти написанный мини-сервер через spawn-fcgi на порту 8080.

Устанавливаем необходимые пакеты `sudo apt-get install spawn-fcgi libfcgi-dev`.

![screenshot](/src/images/3-2-1.png)

Запускаем написанный мини-сервер через spawn-fcgi на порту 8080 командой `spawn-fcgi -p 8080 ./miniserver`, перед этим меняем занятый порт:

![screenshot](/src/images/3-2-2.png)

### 3.3) Напиши свой nginx.conf, который будет проксировать все запросы с 81 порта на 127.0.0.1:8080.

Содержимое файла nginx.conf:

![screenshot](/src/images/3-3.png)

Не забываем перезапустить `nginx -s reload`.

### 3.4) Проверь, что в браузере по localhost:81 отдается написанная тобой страничка.

Открываем в браузере `localhost:81`:

![screenshot](/src/images/3-4.png)

### 3.5) Положи файл nginx.conf по пути ./nginx/nginx.conf

Копируем nginx.conf командой `docker cp nginx.conf eloquent_mclean:/etc/nginx/` :

![screenshot](/src/images/3-5.png)

[-> К оглавлению](#Contents)



<a name="Part 4"></a> 

## Part 4. Свой докер

### 4.1) Напиши свой докер-образ, который:

1) собирает исходники мини сервера на FastCgi из Части 3;

2) запускает его на 8080 порту;

3) копирует внутрь образа написанный ./nginx/nginx.conf;

4) запускает nginx.

Содержимое docker-файла:

![screenshot](/src/images/4-1-1.png)

Содержимое скрипта `run_server.sh` :

![screenshot](/src/images/4-1-2.png)


### 4.2) Собери написанный докер-образ через docker build при этом указав имя и тег.

Используем команду `docker build <путь к докер-файлу> -t <имя>:<тег>` : 

![screenshot](/src/images/4-2.png)

### 4.3) Проверь через docker images, что все собралось корректно.

Проверяем командой `docker images`, что все собралось корректно:

![screenshot](/src/images/4-3.png)

### 4.4) Запусти собранный докер-образ с маппингом 81 порта на 80 на локальной машине и маппингом папки ./nginx внутрь контейнера по адресу, где лежат конфигурационные файлы nginx'а (см. Часть 2).

Запускаем собранный докер-образ с маппингом 81 порта на 80 на локальной машине и маппингом папки ./nginx внутрь контейнера командой `docker run --name serv -d -p 80:81 -v $PWD/part4/nginx/:/etc/nginx/ miniserver:part4` :

![screenshot](/src/images/4-4.png)

### 4.5) Проверь, что по localhost:80 доступна страничка написанного мини сервера.

Проверяем в браузере адрес `localhost:80` :

![screenshot](/src/images/4-5.png)

### 4.6) Допиши в ./nginx/nginx.conf проксирование странички /status, по которой надо отдавать статус сервера nginx.

Добавляем в `nginx.conf` проксирование странички /status:

![screenshot](/src/images/4-6.png)

### 4.7) Перезапусти докер-образ.

Перезапусткаем докер-образ командой `docker restart serv` :

![screenshot](/src/images/4-7-1.png)

Если всё сделано верно, то, после сохранения файла и перезапуска контейнера, конфигурационный файл внутри докер-образа должен обновиться самостоятельно без лишних действий. Проверяем командой `cat`:

![screenshot](/src/images/4-7-2.png)

### 4.8) Проверь, что теперь по localhost:80/status отдается страничка со статусом nginx

После перезапуска проверяем в браузере `localhost:80` и `localhost/status` :

![screenshot](/src/images/4-8.png)

[-> К оглавлению](#Contents)



<a name="Part 5"></a> 

## Part 5. Dockle

Для начала необходимо установить Dockle. Для этого понадобится сначала установить Homebrew:
- `sudo apt update`
- `sudo apt-get install build-essential`
- `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`
- `(echo; echo 'eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)"') >> /home/$USER/.bashrc`
- `eval "$(/home/linuxbrew/.linuxbrew/bin/brew shellenv)"`

Используем команду `brew install goodwithtech/r/dockle` :

![screenshot](/src/images/5-0.png)

### 5.1) Просканируй образ из предыдущего задания через dockle [image_id|repository].

Используем команду `dockle miniserver:part4` :

![screenshot](/src/images/5-1.png)

### 5.2) Исправь образ так, чтобы при проверке через dockle не было ошибок и предупреждений.

Для исправления первой ошибки необходимо указать образ не nginx, а ubuntu с его последующей установкой. Далее необходимо очистить директории после команды `apt update`. После необходимо создать нового пользовотеля. В процессе с помощью команды `docker logs <name>` помогаем себе в описках ошибок. Так же описание ошибок есть на https://github.com/goodwithtech/dockle/blob/master/CHECKPOINT.md.

Содержимое `dockerfile` :

![screenshot](/src/images/5-1-2.png)

Содержимое скрипта `run_server.sh` :

![screenshot](/src/images/5-2.png)

Собираем образ miniserver:part5 и используем команду `dockle miniserver:part5` :

![screenshot](/src/images/5-3.png)

После перезапуска проверяем в браузере `localhost:80` и `localhost/status` :

![screenshot](/src/images/5-4.png)



[-> К оглавлению](#Contents)




<a name="Part 6"></a> 

## Part 6. Базовый Docker Compose

### Напиши файл docker-compose.yml, с помощью которого:

### 6.1) Подними докер-контейнер из Части 5 (он должен работать в локальной сети, т.е. не нужно использовать инструкцию EXPOSE и мапить порты на локальную машину).

Поднимаем контейнер из 5 части без маппинга портов:

![screenshot](/src/images/6-1.png)

### 6.2) Подними докер-контейнер с nginx, который будет проксировать все запросы с 8080 порта на 81 порт первого контейнера.

Для начала необходимо отредактировать файл `nginx.conf`. Для проксирования необходимо узна IP-адресс первого контейнера с помощью команды `docker inspect -s | grep IP` :

![screenshot](/src/images/6-2.png)


Содержимое файла `nginx.conf` второго контейнера:

![screenshot](/src/images/6-3.png)

Содержимое файла `dockerfile` второго контейнера в директории `part6` :

![screenshot](/src/images/6-4.png)

Собираем второй контейнер nginx:

![screenshot](/src/images/6-5.png)


### 6.3) Замапь 8080 порт второго контейнера на 80 порт локальной машины.

Маппим 8080 порт второго контейнера на 80 порт локальной машины при запуске:

![screenshot](/src/images/6-6.png)


Проверяем страничку localhost:80 в браузере:

![screenshot](/src/images/6-7.png)

### 6.4) Останови все запущенные контейнеры.

Останавливаем запущенные контейнеры командой `docker stop <имя>` :

![screenshot](/src/images/6-8.png)

### 6.5) Собери и запусти проект с помощью команд docker-compose build и docker-compose up.

Чтобы успешно проксировать запросы необходимо отредактировать файл nginx.conf и вписать название "сервиса" miniserver:

![screenshot](/src/images/6-9-0.png)

Заходим в директорию Part6 командой `cd part6` и `выполняем docker-compose build` :

![screenshot](/src/images/6-9.png)

Далее используем команду `docker-compose up` :

![screenshot](/src/images/6-10.png)


### 6.6) Проверь, что в браузере по localhost:80 отдается написанная тобой страничка, как и ранее.

Проверяем в браузере `localhost:80` :

![screenshot](/src/images/6-11.png)

После чего останавливаем контейнеры командой `docker-compose down` или нажатием клавиш Ctrl + C в терминале.

[-> К оглавлению](#Contents)
