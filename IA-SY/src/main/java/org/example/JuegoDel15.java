package org.example;

import java.util.Scanner;

public class JuegoDel15 {

    Tablero tablero;
    public void iniciarJuego() {
    Scanner scanner = new Scanner(System.in);
    System.out.println("Ingrese el tamaño del tablero (entre 4 y 8):");
    int n = scanner.nextInt();
    while (n < 4 || n > 8) {
        System.out.println("Tamaño inválido. Ingrese un número entre 4 y 8:");
        n = scanner.nextInt();
    }
    tablero = new Tablero(n);
    System.out.println("Tablero inicial: (Guia para mover las piezas)");
    tablero.imprimirTablero();
    System.out.println("Tablero revuelto:");
    tablero.revolverTablero();
    tablero.imprimirTablero();

    while (!tablero.verificarGanador()) {
        System.out.println("Ingrese la dirección (w,a,s,d) o salir para terminar el juego:");
        String direccion = scanner.next();
        if (direccion.equals("salir")) {
            System.out.println("Juego terminado");
            break;
        }
        tablero.mover(direccion);
        tablero.imprimirTablero();
    }
}
}
