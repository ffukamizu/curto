#ifndef JOGADOR_9922593_H
#define JOGADOR_9922593_H

#include "../baralho.h"

const char *nome_jogador_9922593();
void iniciar_9922593(const int meu_id, const int total_jogadores);
void nova_rodada_9922593(const int rodada, const Carta carta_virada, const int n_cartas, Carta *minha_mao);
int apostar_9922593(const int *apostas);
int jogar_9922593(const Carta *mesa, const int num_na_mesa, const int vitorias);

#endif
