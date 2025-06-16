#include <stdio.h>
#include <stdlib.h>
#include "jogador_9922593.h"
#include "../baralho.h"

static int id;
static int num_jogadores;
static Carta mao[6];
static int num_cartas;
static Valor manilha_atual;
static int aposta_atual = 0;
static int minhas_vitorias = 0;

const char *nome_jogador_9922593()
{
    return "fmizu"; 
}

void iniciar_9922593(const int meu_id, const int total_jogadores)
{
    id = meu_id;
    num_jogadores = total_jogadores;
}

void nova_rodada_9922593(const int rodada, const Carta carta_virada, const int n_cartas, Carta *minha_mao)
{
    manilha_atual = (carta_virada.valor + 1) % 10; 
    num_cartas = n_cartas;
    minhas_vitorias = 0;

    for (int i = 0; i < n_cartas; i++)
    {
        mao[i] = minha_mao[i];
    }
}

int apostar_9922593(const int *apostas)
{
    float score = 0;

    for (int i = 0; i < num_cartas; i++)
    {
        Valor v = mao[i].valor;
        if (v == manilha_atual)
            score += 2;
        else if (v == DOIS || v == TRES || v == AS)
            score += 1;
        else if (v == REI || v == VALETE)
            score += 0.5;
    }

    aposta_atual = (int)(score / 2);
    if (aposta_atual > num_cartas)
        aposta_atual = num_cartas;

    return aposta_atual;
}

int carta_mais_forte(Carta a, Carta b)
{
    if (a.valor == manilha_atual && b.valor != manilha_atual)
        return 1;
    if (b.valor == manilha_atual && a.valor != manilha_atual)
        return 0;
    if (a.valor == manilha_atual && b.valor == manilha_atual)
        return a.naipe > b.naipe;
    if (a.valor != b.valor)
        return a.valor > b.valor;
    return -1; 
}

int jogar_9922593(const Carta *mesa, const int num_na_mesa, const int vitorias)
{
    int i, melhor = -1;

    if (num_na_mesa == 0)
    {
        for (i = 0; i < num_cartas; i++)
        {
            if (!carta_foi_usada(mao[i]) && mao[i].valor != manilha_atual)
            {
                if (melhor == -1 || mao[i].valor < mao[melhor].valor)
                    melhor = i;
            }
        }
        if (melhor == -1)
        {
            for (i = 0; i < num_cartas; i++)
            {
                if (!carta_foi_usada(mao[i]) && (melhor == -1 || mao[i].valor < mao[melhor].valor))
                    melhor = i;
            }
        }
    }
    else
    {
        int mais_forte = 0;
        for (i = 1; i < num_na_mesa; i++)
        {
            if (carta_mais_forte(mesa[i], mesa[mais_forte]) == 1)
                mais_forte = i;
        }

        int venceu = 0;
        for (i = 0; i < num_cartas; i++)
        {
            if (!carta_foi_usada(mao[i]) && carta_mais_forte(mao[i], mesa[mais_forte]) == 1)
            {
                if (melhor == -1 || carta_mais_forte(mao[i], mao[melhor]) == 1)
                    melhor = i;
                venceu = 1;
            }
        }

        if (!venceu)
        {
            for (i = 0; i < num_cartas; i++)
            {
                if (!carta_foi_usada(mao[i]) && (melhor == -1 || mao[i].valor < mao[melhor].valor))
                    melhor = i;
            }
        }
    }

    if (melhor == -1)
    {
        for (i = 0; i < num_cartas; i++)
        {
            if (!carta_foi_usada(mao[i]))
            {
                melhor = i;
                break;
            }
        }
    }

    mao[melhor] = USADA;
    return melhor;
}
