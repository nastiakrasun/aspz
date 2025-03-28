Перед виконанням завдань було встановлено докер на систему: `sudo snap install docker`

## TASK 1:

Було запущено Docker-контейнер на основі образу Ubuntu для експериментів із максимальним лімітом відкритих файлів (ulimit). Усередині контейнера виконувалися команди для перегляду поточних та граничних значень (ulimit -n, ulimit -aS, ulimit -aH), зміни ліміту (ulimit -n 3000, ulimit -n 2000) і перевірки їх застосування. Потім ті ж дії були повторені з root-правами для аналізу відмінностей у доступних налаштуваннях.

## TASK 2:

Спершу я запустила Docker-контейнер з обмеженням у 1000МБ оперативної пам’яті (`docker run --rm -it --privileged --cap-add=SYS_ADMIN --memory=1000m debian bash`), після чого було встановлдено `perf` (`apt update && apt install -y linux-perf procps`) та `stress` (`apt update && apt install -y stress`). Stress використовувався для зручності тестування. Далі було проведено тестування впливу навантаження на пам’ять за допомогою `perf`, виконуючи команду `perf stat -e cache-misses stress --vm 1 --vm-bytes 50M --timeout 10s`, потім збільшивши обсяг до 500МБ і 5000МБ, для перевірки роботи `perf`.

## TASK 3:

Завдання було виконано шляхом створення програми на мові C, яка імітує кидання кубика та записує результати у файл до досягнення ліміту його розміру. Програма використовує стандартну бібліотеку для генерування випадкових чисел та перевірки розміру файлу. Для розгортання програми в Docker було створено `Dockerfile`, який компілює програму та запускає її у контейнері. Використовувались команди `docker build -t dice_simulator .` для створення образу та `docker run --rm dice_simulator` для запуску контейнера, що автоматично виконує програму.

## TASK 4:

Це завдання було виконане по аналогії до минулого. Було також створено програму на мові С, для розгортання у докері було додано `Dockerfile`. Програма на C імітує лотерею, вибираючи 7 різних чисел у діапазоні від 1 до 49 та 6 чисел із діапазону від 1 до 36. Вона має обмеження на час процесора (2 секунди), і якщо ліміт перевищено, програма зупиняється. Числа генеруються випадковим чином, і результати виводяться на екран.

## TASK 5:

Програма копіює вміст одного файлу в інший. Вона перевіряє, чи передано два аргументи, доступність першого файлу для читання та другого файлу для запису. Також обробляє ситуацію перевищення обмеження на розмір файлу (максимум 10 МБ) і виводить відповідні повідомлення про помилки. Щоб запустити потрібно створити Docker-образ з програмою, використовуючи команду `docker build -t file_copy .`, і запустити контейнер за допомогою `docker run --rm -v "$(pwd):/app" file_copy source.txt destination.txt`. Ця команда запустить програму, копіюючи вміст з `source.txt` до `destination.txt`, перевіряючи перед цим умови щодо кількості аргументів, доступності файлів і ліміту розміру файлу.

## TASK 6:

Програма на мові C демонструє використання обмеження розміру стека через рекурсивні виклики. Функція `recursiveFunction` викликає саму себе, збільшуючи глибину рекурсії, що призводить до постійного додавання нових фреймів в стек. Програма продовжує працювати до досягнення обмеження на розмір стека, після чого виникає помилка сегментації `(Segmentation fault)`, що вказує на переповнення стеку. Розмір стека можна обмежити через параметри операційної системи, використовуючи команду `ulimit`.

## TASK 7:

У цьому завданні була написана програма на мові C, яка створює багато потоків за допомогою бібліотеки `pthread`. Програма запускає нескінченний цикл створення потоків, де кожен потік просто працює в нескінченному циклі. Завдяки цьому демонструється вплив параметра `ulimit -u`, який обмежує кількість одночасно виконуваних процесів для користувача в операційній системі. При досягненні ліміту на кількість потоків програма припиняє створення нових потоків, і відображається повідомлення про помилку, що підтверджує обмеження кількості потоків, встановлене системою.