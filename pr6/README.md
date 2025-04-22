## TASK 1:

Це завдання демонструє, як встановити Valgrind у Docker-контейнер із GCC, скомпілювати просту програму на C і перевірити її на витоки пам’яті.

Зібрати Docker-образ:
`docker build -t valgrind-test .`

Запустити контейнер:
`docker run --rm valgrind-test`

## TASK 2:

Цей проєкт демонструє, як автоматизувати перевірку C-програм на витоки пам’яті та інші помилки за допомогою Valgrind у середовищі Docker.

**У Dockerfile:**
- Встановлюється Ubuntu 22.04
- Інсталюються gcc та valgrind
- Копіюється C-програма (main.c)
- Програма компілюється з дебаг-символами
- Запускається під Valgrind

Зібрати Docker-образ:
`docker build -t valgrind-test .`

Запустити контейнер:
`docker run --rm valgrind-test`