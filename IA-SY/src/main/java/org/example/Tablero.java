package org.example;

import java.util.*;

public class Tablero {
    private int[][] matriz;


    public Tablero(int n)
    {
        matriz = new int[n][n];
        int contador = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                matriz[i][j] = contador;
                if (contador == n * n)
                {
                    matriz[i][j] = 0;
                }
                contador++;
            }
        }
    }
    public void imprimirTablero() {
        for (int i = 0; i < matriz.length; i++) {
            for (int j = 0; j < matriz[i].length; j++) {
                System.out.printf("%4d", matriz[i][j]);
            }
            System.out.println();
        }
    }
    public void revolverTablero()
    {
        Random rand = new Random();
        for(int i = matriz.length -1; i>0; i--)
        {
            for(int j = matriz[i].length -1; j > 0; j--)
            {
                int m = rand.nextInt(i+1);
                int n = rand.nextInt(j+1);

                int temp = matriz[i][j];
                matriz[i][j] = matriz[m][n];
                matriz[m][n] = temp;
            }
        }
    }
    public void mover(String direccion)
    {
        int fila = 0;
        int columna = 0;
        for(int i = 0; i < matriz.length;i++)
        {
            for(int j = 0; j < matriz[i].length; j++)
            {
                if(matriz[i][j] == 0)
                {
                    fila = i;
                    columna = j;
                }
            }
        }

        if(direccion.equals("W") || direccion.equals("w"))
        {
            if(fila -1 >=0)
            {
                int temp = matriz[fila][columna];
                matriz[fila][columna] = matriz[fila-1][columna];
                matriz[fila-1][columna] = temp;
            }

        }
        else if(direccion.equals("S") || direccion.equals("s"))
        {
            if(fila +1 < matriz.length)
            {
                int temp = matriz[fila][columna];
                matriz[fila][columna] = matriz[fila+1][columna];
                matriz[fila+1][columna] = temp;
            }
        }
        else if(direccion.equals("A") || direccion.equals("a"))
        {
            if(columna -1 >=0)
            {
                int temp = matriz[fila][columna];
                matriz[fila][columna] = matriz[fila][columna-1];
                matriz[fila][columna-1] = temp;
            }
        }
        else if(direccion.equals("D") || direccion.equals("d"))
        {
            if(columna +1 < matriz.length)
            {
                int temp = matriz[fila][columna];
                matriz[fila][columna] = matriz[fila][columna+1];
                matriz[fila][columna+1] = temp;
            }
        }
        else if(direccion.equals("trap") || direccion.equals("T") || direccion.equals("t") || direccion.equals("TRAP") || direccion.equals("trap") || direccion.equals("Trap") || direccion.equals("TRAP") || direccion.equals("Trap"))
        {
            trap();
        }
    }

    public void solicitarMovimiento() {
        System.out.println("Ingrese el movimiento (arriba, abajo, izquierda, derecha):");
        Scanner scanner = new Scanner(System.in);
        String movimiento = scanner.nextLine();
        mover(movimiento);
        imprimirTablero();
    }

    public boolean verificarGanador()
    {
        int contador = 1;
        for(int i = 0; i < matriz.length; i++)
        {
            for(int j = 0; j < matriz[i].length; j++)
            {
                if(contador == matriz.length * matriz.length)
                {
                    System.out.println("¡Felicidades! Has ganado");
                    return true;
                }
                if(matriz[i][j] != contador)
                {
                    return false;
                }
                contador++;
            }
        }
        return false;
    }
    public void trap()
    {
        System.out.println("Elige los 2 numeros que quieres intercambiar");
        Scanner scanner = new Scanner(System.in);
        int num1 = scanner.nextInt();
        int num2 = scanner.nextInt();
        for(int i = 0; i < matriz.length; i++)
        {
            for(int j = 0; j < matriz[i].length; j++)
            {
                if(matriz[i][j] == num1)
                {
                    matriz[i][j] = num2;
                }
                else if(matriz[i][j] == num2)
                {
                    matriz[i][j] = num1;
                }
            }
        }
    }
}
