// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Klarc de Almeida Pereira
//  email: 20252160019@ifba.edu.br
//  Matrícula: 20252160019
//  Semestre: 2º

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021

// #################################################

#include <stdio.h>
#include "trabalho1.h"
#include <stdlib.h>

int somar(int x, int y)
{
    return x + y;
}

int fatorial(int x)
{
    int i, fat = 1;

    for (i = x; i > 1; i--)
        fat = fat * i;

    return fat;
}

// Q1
int q1(char data[])
{
    DataQuebrada dq = quebraData(data);
    int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if (dq.valido == 0)
        return 0;

    if (dq.iAno < 0)
        return 0;

    if (dq.iMes < 1 || dq.iMes > 12)
        return 0;

    if (dq.iDia < 1)
        return 0;

    if ((dq.iAno % 4 == 0 && dq.iAno % 100 != 0) || dq.iAno % 400 == 0)
        diasMes[1] = 29;

    if (dq.iDia > diasMes[dq.iMes - 1])
        return 0;

    return 1;
}

// Q2
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    DiasMesesAnos dma;
    DataQuebrada d1, d2;
    int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    dma.qtdDias = 0;
    dma.qtdMeses = 0;
    dma.qtdAnos = 0;

    if (q1(datainicial) == 0)
    {
        dma.retorno = 2;
        return dma;
    }

    if (q1(datafinal) == 0)
    {
        dma.retorno = 3;
        return dma;
    }

    d1 = quebraData(datainicial);
    d2 = quebraData(datafinal);

    if (
        d1.iAno > d2.iAno ||
        (d1.iAno == d2.iAno && d1.iMes > d2.iMes) ||
        (d1.iAno == d2.iAno && d1.iMes == d2.iMes && d1.iDia > d2.iDia)
    )
    {
        dma.retorno = 4;
        return dma;
    }

    if ((d2.iAno % 4 == 0 && d2.iAno % 100 != 0) || d2.iAno % 400 == 0)
        diasMes[1] = 29;

    if (d2.iDia < d1.iDia)
    {
        d2.iMes--;

        if (d2.iMes == 0)
        {
            d2.iMes = 12;
            d2.iAno--;
        }

        d2.iDia += diasMes[d2.iMes - 1];
    }

    dma.qtdDias = d2.iDia - d1.iDia;

    if (d2.iMes < d1.iMes)
    {
        d2.iMes += 12;
        d2.iAno--;
    }

    dma.qtdMeses = d2.iMes - d1.iMes;
    dma.qtdAnos = d2.iAno - d1.iAno;

    dma.retorno = 1;

    return dma;
}

// Q3
int q3(char *texto, char c, int isCaseSensitive)
{
    int i = 0;
    int qtdOcorrencias = 0;
    char atual;

    if (c >= 'A' && c <= 'Z' && isCaseSensitive != 1)
        c = c + 32;

    while (texto[i] != '\0')
    {
        atual = texto[i];

        if (atual >= 'A' && atual <= 'Z' && isCaseSensitive != 1)
            atual = atual + 32;

        if (atual == c)
            qtdOcorrencias++;

        i++;
    }

    return qtdOcorrencias;
}

// Q4
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int i, j;
    int qtdOcorrencias = 0;
    int encontrou;

    for (i = 0; strTexto[i] != '\0'; i++)
    {
        encontrou = 1;

        for (j = 0; strBusca[j] != '\0'; j++)
        {
            if (strTexto[i + j] != strBusca[j])
            {
                encontrou = 0;
                break;
            }
        }

        if (encontrou && strBusca[j] == '\0')
        {
            posicoes[qtdOcorrencias * 2] = i + 1;
            posicoes[qtdOcorrencias * 2 + 1] = i + j;
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}

// Q5
int q5(int num)
{
    int invertido = 0;
    int resto;

    while (num != 0)
    {
        resto = num % 10;
        invertido = invertido * 10 + resto;
        num = num / 10;
    }

    return invertido;
}

// Q6
int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;

    while (numerobase > 0)
    {
        if (numerobase % 10 == numerobusca)
            qtdOcorrencias++;

        numerobase = numerobase / 10;
    }

    return qtdOcorrencias;
}

// Q7
int q7(char matriz[8][10], char palavra[5])
{
    int i, j, k;
    int dx[] = {-1,-1,-1,0,0,1,1,1};
    int dy[] = {-1,0,1,-1,1,-1,0,1};

    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 10; j++)
        {
            for (k = 0; k < 8; k++)
            {
                int x = i;
                int y = j;
                int p;

                for (p = 0; palavra[p] != '\0'; p++)
                {
                    if (x < 0 || x >= 8 || y < 0 || y >= 10)
                        break;

                    if (matriz[x][y] != palavra[p])
                        break;

                    x += dx[k];
                    y += dy[k];
                }

                if (palavra[p] == '\0')
                    return 1;
            }
        }
    }

    return 0;
}

DataQuebrada quebraData(char data[])
{
    DataQuebrada dq;
    char sDia[3];
    char sMes[3];
    char sAno[5];
    int i;

    for (i = 0; data[i] != '/'; i++)
    {
        if (data[i] == '\0')
        {
            dq.valido = 0;
            return dq;
        }

        sDia[i] = data[i];
    }

    if (i == 1 || i == 2)
    {
        sDia[i] = '\0';
    }
    else
    {
        dq.valido = 0;
        return dq;
    }

    int j = i + 1;
    i = 0;

    for (; data[j] != '/'; j++)
    {
        if (data[j] == '\0')
        {
            dq.valido = 0;
            return dq;
        }

        sMes[i] = data[j];
        i++;
    }

    if (i == 1 || i == 2)
    {
        sMes[i] = '\0';
    }
    else
    {
        dq.valido = 0;
        return dq;
    }

    j++;
    i = 0;

    for (; data[j] != '\0'; j++)
    {
        sAno[i] = data[j];
        i++;
    }

    if (i == 2 || i == 4)
    {
        sAno[i] = '\0';
    }
    else
    {
        dq.valido = 0;
        return dq;
    }

    dq.iDia = atoi(sDia);
    dq.iMes = atoi(sMes);
    dq.iAno = atoi(sAno);

    if (i == 2)
        dq.iAno += 2000;

    dq.valido = 1;

    return dq;
}