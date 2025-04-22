## TASK 1:

Це завдання демонструє, як встановити Valgrind у Docker-контейнер із GCC, скомпілювати просту програму на C і перевірити її на витоки пам’яті.

Зібрати Docker-образ:
`docker build -t valgrind-test .`

Запустити контейнер:
`docker run --rm valgrind-test`