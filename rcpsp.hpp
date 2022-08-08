#ifndef PMM_HPP_INCLUDED
#define PMM_HPP_INCLUDED

#define MAX_QTD_RECURSO 10
#define MAX_QTD_TAREFAS 200
#define PESO_PENALIZACAO_PRECEDENCIA 1000
#define PESO_PENALIZACAO_RECURSOS 100
#define PESO_ALEATORIEDADE 3

#include <string>

typedef struct tSolucao
{
    int tarefasStartTime[2][MAX_QTD_TAREFAS];
    int qtdTarefas;
    int funObj;
    int makespan;
} Solucao;

//
typedef struct relacaoPrecedencia
{
    int qtdSucessores;
    int sucessores[MAX_QTD_TAREFAS];
} RelacaoPrecedencia;

// Variaveis leitura
char linha[100];
int qtdTarefas;
int qtdRecursos;
int duracao[MAX_QTD_TAREFAS];

/* TODO: Substituir esse cara pela matriz de baixo */
RelacaoPrecedencia relacoesPrecedencia[MAX_QTD_TAREFAS];
int matrizRelacoesPrecedencia[MAX_QTD_TAREFAS][MAX_QTD_TAREFAS];

int consumoRecursos[MAX_QTD_TAREFAS][MAX_QTD_RECURSO];

// Preenchido após ordenação
int tarefasStartTimeOrdenadaPrecedencia[2][MAX_QTD_TAREFAS];
int recursoDisponivel[MAX_QTD_RECURSO];

// Variaveis calculo FO
int tarefasStartTimeOrdenadaAposSolucao[2][MAX_QTD_TAREFAS];

void lerDados(std::string arq);
void getQtdTarefas(FILE *arquivo);
void getRelacoesPrecedencia(FILE *arquivo);
void getQtdRecursos(FILE *arquivo);
void getDuracaoTarefasEConsumoRecursos(FILE *arquivo);
void getQuantidadeCadaRecurso(FILE *arquivo);

// Heuristica construtiva
void heuristicaConstrutiva(Solucao &sol);
void heuristicaConstrutivaSemMovimentar(Solucao &sol);
void ordenarPrecedencia();
int getCalcularMaiorTempoTarefas();
void ordenarTarefasRecursos();
void setTarefasStartTimeOrdenadoPrecedenciaSolucaoEMakespan(Solucao &sol);


// Meta heuristica - Grasp
void heuristicaGrasp(Solucao &solGrasp, float LRC);
void heuristicaAleatoria(Solucao &solGrasp, float LRC);
void buscaLocal(Solucao &s);
void recalculoParaEscalonarSolucaoAleatoria(Solucao &s);

// Métodos para ler e escrever solução
Solucao solucaoLida;
void lerSolucao(std::string arq);
void escreverSolucao(Solucao &solucao, std::string arq);

// Metodos auxiliares
/* Verifica se esta contido no Vetor. */
void gerarSolucaoECalcularFO(Solucao &sol);
void calcularFOSolucaoLida();
int encontrarPosicaoTarefa(Solucao s, const int idTarefaProcurada);
int encontrarPrioridadeTarefa(Solucao s, const int idTarefaProcurada);
void ordenarParteTarefasPelasPrioridades(Solucao &s, const int inicio, const int fim);
void encaixarParteEstaticaNaAleatoria(Solucao sol, const int idInicioParteEstatica);

void gerarMetricasTrabalho1(Solucao &sol);
void gerarMetricasTrabalho2(Solucao &sol);
bool todosAnterioresOrdenadosJaEntraram(const int indiceTarefaAtual);
void reCalcularTempo(Solucao s, int idInicioReCalculo);
void copiarSolucao(Solucao &solucaoNova, Solucao &solucaoAntiga);
void ordenarSolucaoStartTime();


// Metodos calculo FO
void calcFO(Solucao &s);
void calcFOSemPenalizacaoPrecedencia(Solucao &s);
int calcularPenalizacaoEstouroRecurso(Solucao &s);
int calcularPenalizacaoPrecedencia(Solucao &s);
bool verificarSeEstaContidoVetor(const int value, const int quantidade, const int vetor[]);

#endif // PMM_HPP_INCLUDED
