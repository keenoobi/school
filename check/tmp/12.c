#include <stdio.h>   //Для printf  и puts 
#include <unistd.h>  ////Для usleep
#include <ncurses.h>

#define MAX_speed 20
#define MIN_speed 1
#define speed 5
#define step 1












int main (void)
{    
    initscr();
    keypad(stdscr, true);   //Включаем режим чтения функциональных клавиш
    noecho();               //Выключаем отображение вводимых символов, нужно для getch()
    halfdelay(10);         //Устанавливаем ограничение по времени ожидания getch() в 10 сек

    int ch = getch();
    int acceleration;
    if (ch == '+' && speed < MAX_speed){
        acceleration = speed - step;
    }
    else if (ch == '-' && speed > MIN_speed){
        acceleration = speed + step;
    }
      

   int MyTik=0; //Счетчик приостановок работы
     
   //Вывод сообщения о приостановке работы
   puts ("Остановка работы на 100 миллисекунд");
   //Цикл на пять тактов
   while (1)  
   {    

      //Вывод оставшегося времени до возобновления работы
      printw ("     Осталось %d мсек.\n", 100-MyTik);
      //Приостановка работы на 1 миллисекунду
      usleep (1000/acceleration);
      //Увеличение на 1 счетчика приостановок
      MyTik++;

   }
   //Вывод сообщения о возобновлении работы
   puts ("Работа возобновлена");

   return 0;
}