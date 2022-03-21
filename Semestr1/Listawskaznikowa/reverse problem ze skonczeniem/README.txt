Mam tutaj problem z poprawnym ustawieniem wskaźników, gdy wyswietlam obrocona liste wskaznik l wskazuje o element
za daleko. Najprawdopodobniej muszę zmienić sposób przestawiania w funkcji Reverse().
Problemem tej implementacji listy jest to że początkowo wskaźnik l wskazuje na smieci przez co przy obracaniu
brane sa one pod uwagę, a tak na prawde pierwszym elementem w mojej liście jest l->next->element