# Funzione per calcolare media aritmetica contenuta in una libreria statica e dinamica
Il metodo *double mean(double, double)* dati due numeri di tipo double ne restituisce la media.
Questo metodo è contenuto in una libreria statica e in una dinamica:
1. in mainStatic.cpp il metodo è contenuto nella libreria statica, quest'ultima viene inserita direttamente nell'eseguibile prima dell'esecuzione.
1. in mainDynamic.cpp il metodo è contenuto nella libreria dinamica, quest'ultima viene inserita in memoria, poi una volta che il programma viene eseguito farà riferimento ad essa al momento della chiamata al metodo mean();


