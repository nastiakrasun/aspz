#!/bin/bash

# 1. Перевірка, які бібліотеки використовуються програмами (ls та gcc)
echo "=== Бібліотеки для ls ==="
ldd /bin/ls

echo "\n=== Бібліотеки для gcc ==="
ldd $(which gcc)

# 2. Пошук бібліотеки з math-функціями
MATH_LIB=$(find /usr/lib -name "*math*" 2>/dev/null)
echo "\n=== Math-бібліотеки ==="
echo "$MATH_LIB"

# 3. Перевірка символів бібліотеки libm (math library)
if [ -f "/usr/lib/libm.so" ]; then
    echo "\n=== Символи в libm.so ==="
    nm -D /usr/lib/libm.so | grep -E "erf|sin|cos|exp"
else
    echo "\nlibm.so не знайдено у /usr/lib"
fi

# 4. Аналіз залежностей бібліотек у /usr/lib
echo "\n=== Аналіз залежностей бібліотек ==="
for lib in /usr/lib/*.so*; do
    echo "\nБібліотека: $lib"
    ldd "$lib" 2>/dev/null
done

# 5. Аналіз усіх бібліотек у /usr/lib на наявність функцій sin, cos, exp
echo "\n=== Пошук math-функцій у бібліотеках ==="
for lib in /usr/lib/*.so*; do
    echo "\nПеревірка $lib на наявність sin, cos, exp:"
    nm -D "$lib" 2>/dev/null | grep -E "sin|cos|exp"
done
