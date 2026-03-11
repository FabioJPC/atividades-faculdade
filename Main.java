package com.fabio;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scanner =new Scanner(System.in);
        exercicio01(scanner);
        exercicio02(scanner);
        exercicio03(scanner);
        exercicio04(scanner);
        exercicio05(scanner);
        exercicio06(scanner);
        exercicio07(scanner);
        exercicio08(scanner);
        exercicio09(scanner);
        exercicio10();
    }

    public static void exercicio01(Scanner scanner){

        int numero;

        System.out.println("Digite um número: ");
        numero = scanner.nextInt();
        int maior = numero;
        int menor = numero;

        for(int i=0; i<4; i++){
            System.out.println("Digite um número: ");
            numero = scanner.nextInt();
            if(numero > maior){
                maior = numero;
            }
            if(numero < menor){
                menor = numero;
            }
        }
        String mensagem = String.format("O maior numero foi %d, o menor foi %d.", maior, menor);
        System.out.println(mensagem);
    }

    public static void exercicio02(Scanner scanner){
        int soma = 0, numero;
        for(int i = 0; i<10; i++){
            System.out.println("Digite um número: ");
            numero = scanner.nextInt();
            if(numero % 2 == 0){
                soma += numero;
            }
        }
        System.out.println("A soma dos numeros pares foi: " + soma);
    }

    public static void exercicio03(Scanner scanner){
        float soma = 0f;
        for(int i=0; i<4; i++){
            System.out.println("Digite a nota do aluno: ");
            float num = scanner.nextFloat();
            while(num<0 || num>10){
                System.out.println("Valor inválido, digite entre 0 e 10: ");
                num = scanner.nextFloat();
            }
            soma += num;
        }
        float media = soma / 4.0f;
        String status = (media >= 6.0) ? "aprovado" : "reprovado";
        System.out.println("A média do aluno foi " + media + ", ele está " + status);
    }
    public static void exercicio04(Scanner scanner){
        System.out.println("Digite um numero para calcular o fatorial...");
        int num = scanner.nextInt();
        long resultado = 1;
        for(int i = num; i>0; i--){
            resultado *= i;
        }
        System.out.println("O fatorial é: " + resultado);
    }
    public static void exercicio05(Scanner scanner){
        System.out.println("Digite um numero para construir a sequencia de Fibonacci:");
        int num = scanner.nextInt();
        if (num <= 0){
            System.out.println("Numero inválido");
            return;
        }
        if (num == 1){
            System.out.println("A sequencia é: 0");
            return;
        }
        long[] fibo = new long[num];
        fibo[0] = 0;
        fibo[1] = 1;
        for(int i=2; i<num; i++){
            fibo[i] = fibo[i-1] + fibo[i-2];
        }

        System.out.println("Sequencia de Fibonacci com " + num + " números");
        for(int i=0; i<num; i++){
            System.out.print(fibo[i] + " ");
        }
    }

    public static void exercicio06(Scanner scanner){
        System.out.println("\nDigite um numero para ver se é primo: ");
        int num = scanner.nextInt();
        //Para ver se é primo não precisa multiplicar até o numero final, só até a raiz quadrada do numero
        int raiz = ((int)Math.sqrt(num)) + 1;

        //edge case
        if(num == 2){
            System.out.println("O numero "+ num + " é primo");
            return;
        }

        //fail fast
        if(num %2 == 0 || num <2){
            System.out.println("O número " + num + " não é primo ou é inválido(<2)");
            return;
        }
        int i = 3;
        while(i <= raiz){
            if(num % i == 0){
                System.out.println("O número " + num + " não é primo");
                return;
            }
            i+=2;
        }
        System.out.println("O numero "+ num + " é primo");
    }

    public static void exercicio07(Scanner scanner){
        int x = 1;
        while(true){
            double num1, num2;
            System.out.println("Selecione o tipo de operação:");
            System.out.println("1.Adição\n2.Subtração\n3.Multiplicação\n4.Divisão\n0.Sair");
            x = scanner.nextInt();

            if(x == 0) break;
            if(x>4 || x<1){
                System.out.println("Opção inválida, tente novamente...");
                continue;
            }

            System.out.println("Digite o primeiro número: ");
            num1 = scanner.nextDouble();
            System.out.println("Digite o segundo número: ");
            num2 = scanner.nextDouble();
            switch (x){
                case 1:
                    System.out.println("Resultado: " + (num1+num2));
                    break;
                case 2:
                    System.out.println("Resultado: " + (num1-num2));
                    break;
                case 3:
                    System.out.println("Resultado: " + (num1*num2));
                    break;
                case 4:
                    if (num2 == 0){
                        System.out.println("Divisão por zero não permitida!");
                    }
                    System.out.println("Resultado: " + (num1/num2));
                    break;
            }
        }
    }
    public static void exercicio08(Scanner scanner){
        int tamanho = 10;
        int negativos = 0;
        int positivos = 0;
        int zeros = 0;
        for(int i=0; i<tamanho; i++){
            System.out.println("Digite um número");
            double num = scanner.nextDouble();
            if(num == 0) zeros++;
            else if(num > 0) positivos++;
            else negativos++;
        }
        System.out.println("Resultados:");
        System.out.println("Zeros: "+ zeros + " Positivos: " +positivos+" Negativos: "+negativos);
    }

    public static void exercicio09(Scanner scanner){
        System.out.println("---Jogo da adivinhação---");
        System.out.println("Tente adivinhar o numero de 0 à 100.");
        int num = (int)(Math.random() * 100) + 1;
        int tentativa = -1;
        while(tentativa != num){
            System.out.println("dê seu palpite: ");
            tentativa = scanner.nextInt();
            if(tentativa == num){
                System.out.println("Parabéns você acertou!");
                break;
            }
            if(tentativa<num){
                System.out.println("O número secreto é maior");
                continue;
            }
            if(tentativa>num){
                System.out.println("O número secreto é menor");
                continue;
            }
        }
    }
    public static void exercicio10(){
        System.out.println("-----Tabuadas----");
        for(int i=1; i<11; i++){
            System.out.println("\nTabuada do "+ i);
            for(int j=1; j<11; j++){
                System.out.println(i +"X"+ j+"="+(i*j));
            }
        }
    }
}