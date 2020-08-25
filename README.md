L'idea alla finale di questo progetto è la realizzazione di un dato a 6 facce "intelligente". 
Il cubo una volta che capisce di essere stato lanciato, genera in modo random un numero, tra 0 e n (con n da definire) usando l'accellerometro come seed. 
Una volta che il dato si ferma, capisce quale faccia è rivolta verso e l'alto e solo in quel lato mostra il risultato.

# Specifiche

Ho deciso di suddividere il progetto in n step:
1.  Funzione_1 del giroscopio e accellerometro (GY-521 MPU-6050 - Modulo a 3 assi) come seed per la generazione del numero rondom.
2.  Utilizzo dello shift register (74hc595) per il controllo del display a 1 bit, così da ridurre i pin da 10 a 3.
3.  Creazione della funzione che allo squotimento dell'accellerometro fa partire la funzione_1 e poi mostra il numero sul display.
4.  ...
