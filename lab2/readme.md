# Лабораторная работа №2

## Отчет

[Отчет в Google Documents](https://docs.google.com/document/d/16RQeVaUV1rXNvNktrJGhrDpSETnrBsfy/edit?usp=sharing&ouid=106682347432010536339&rtpof=true&sd=true) 

## Цель работы
Целью является приобретение практических навыков в:
+ Управление потоками в ОС
+ Обеспечение синхронизации между потоками

## Вариант задания

Составить программу на языке Си, обрабатывающую данные в многопоточном режиме. При обработки использовать стандартные средства создания потоков операционной системы (Windows/Unix). Ограничение максимального количества потоков, работающих в один момент времени, должно быть задано ключом запуска вашей программы.
Так же необходимо уметь продемонстрировать количество потоков, используемое вашей программой с помощью стандартных средств операционной системы.
В отчете привести исследование зависимости ускорения и эффективности алгоритма от входных данных и количества потоков. Получившиеся результаты необходимо объяснить.

***Вариант 17)***  Найти в большом целочисленном массиве минимальный и максимальный элементы

## Как запустить?

```shell
gcc main.c -o main
./main <кол-во потоков>
```
