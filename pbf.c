#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função genérica para ler e validar um número (inteiro ou float)
// tipo: 'f' para float, 'd' para int
void pergunta_numero(char tipo, void *num, const char *texto, int min, int max) {
    char input[50], *index;
    double numero;

    while (1) {
        printf("%s", texto);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Remove o caractere '\n' do final

        // Converte a entrada para float ou int, dependendo do tipo
        numero = (tipo == 'f') ? strtof(input, &index) : strtol(input, &index, 10);

        // Verifica se a entrada é válida e está na faixa permitida
        if (*index == '\0' && input[0] != '\0' && numero >= min && numero <= max) {
            if (tipo == 'f') 
                *(float *)num = numero;
            else 
                *(int *)num = (int)numero;
            return; // valor válido, retorna
        }

        printf("Entrada invalida! Certifique-se de que o numero esta entre %d e %d\n", min, max);
    }
}

// Função para registrar um motivo de indeferimento caso a condição seja verdadeira
void registra_motivo(int condicao, int *status, char *motivo, const char *mensagem) {
    if (condicao) {
        *status = 0; // define que a bolsa não será concedida
        strncat(motivo, mensagem, 200 - strlen(motivo)); // concatena motivo evitando overflow
    }
}

// Função principal de lógica para verificar se o aluno tem direito à bolsa
// Retorna: 1 (bolsa integral), 2 (parcial), 0 (nenhuma)
int calcula_bolsa(float rendaPerCapita, float notaFinal, int deficiente, int redePublica, int familiaresBolsistas, int tipoBolsaDesejada, char *motivoIntegral, char *motivoParcial) {
    int status = 1; // começa assumindo que a bolsa integral será concedida

    // Regras para bolsa integral
    registra_motivo(rendaPerCapita > 800, &status, motivoIntegral, "Renda mensal maior que 800\n");
    registra_motivo(notaFinal < 8, &status, motivoIntegral, "Nota final menor que 8\n");
    registra_motivo(!(deficiente || redePublica), &status, motivoIntegral, "Nao possui deficiencia ou nunca estudou em rede publica\n");
    registra_motivo(familiaresBolsistas > 0, &status, motivoIntegral, "Ja ha um familiar bolsista na familia\n");
    registra_motivo(tipoBolsaDesejada == 2, &status, motivoIntegral, "Voce optou pela bolsa de 50%\n");

    // Se a integral não for concedida, avalia-se a parcial
    if (status == 0) {
        status = 2;

        registra_motivo(rendaPerCapita > 1600, &status, motivoParcial, "Renda mensal maior que 1600\n");
        
        // Critério de nota muda se for deficiente ou de rede pública
        if (deficiente || redePublica)
            registra_motivo(notaFinal < 6, &status, motivoParcial, "Nota final menor que 6\n");
        else
            registra_motivo(notaFinal < 7.5, &status, motivoParcial, "Nota final menor que 7.5\n");

        registra_motivo(familiaresBolsistas > 1, &status, motivoParcial, "Ha mais de um familiar bolsista na familia\n");
        registra_motivo(tipoBolsaDesejada == 1, &status, motivoParcial, "Voce optou pela bolsa de 100%\n");
    }

    return status;
}

int main() {
    // Declaração das variáveis de entrada
    float rendaMensal, notaProcessoSeletivo, notaEnem, mediaEnsinoMedio;
    int deficiente, redePublica, pessoasNaFamilia, familiaresBolsistas, tipoBolsaDesejada;
    char curso[30] = "";

    // Coleta de dados do candidato
    pergunta_numero('f', &rendaMensal, "Digite a renda familiar mensal: ", 0, 999999999);
    pergunta_numero('f', &notaProcessoSeletivo, "Digite a nota do processo seletivo (0 a 10): ", 0, 10);
    pergunta_numero('f', &notaEnem, "Digite a nota do Enem (0 a 10): ", 0, 10);
    pergunta_numero('f', &mediaEnsinoMedio, "Digite a media geral do Ensino Medio (0 a 10): ", 0, 10);
    pergunta_numero('d', &deficiente, "Possui deficiencia? (1-Sim, 0-Nao): ", 0, 1);
    pergunta_numero('d', &redePublica, "e aluno da rede publica? (1-Sim, 0-Nao): ", 0, 1);
    pergunta_numero('d', &pessoasNaFamilia, "Numero de pessoas na familia: ", 1, 999999999);
    pergunta_numero('d', &familiaresBolsistas, "Numero de familiares bolsistas na universidade: ", 0, 999999999);
    pergunta_numero('d', &tipoBolsaDesejada, "Tipo de bolsa desejada (1 para INTEGRAL, 2 para PARCIAL): ", 1, 2);
    printf("Digite o curso pretendido: ");
    scanf("%[^\n]", curso); // lê até o \n

    // Cálculo da nota final ponderada
    float notaFinal = (notaProcessoSeletivo * 0.4) + (notaEnem * 0.3) + (mediaEnsinoMedio * 0.3);

    // Cálculo da renda per capita
    float rendaPerCapita = rendaMensal / (float)pessoasNaFamilia;

    // Vetores para armazenar os motivos de indeferimento
    char motivoIntegral[200] = "";
    char motivoParcial[174] = "";

    // Avaliação da bolsa
    int bolsaStatus = calcula_bolsa(rendaPerCapita, notaFinal, deficiente, redePublica, familiaresBolsistas, tipoBolsaDesejada, motivoIntegral, motivoParcial);

    // Limpa tela (somente Windows)
    system("cls");

    // Exibe dados preenchidos
    printf("==== RESULTADOS ====\n"
           "Curso pretendido: - - - - - - - - - - - - : %s\n"
           "Nota do processo seletivo: -------------- : %.2f\n"
           "Nota do Enem: - - - - - - - - - - - - - - : %.2f\n"
           "Media geral do Ensino Medio:  - - - - - - : %.2f\n"
           "Nota final: ----------------------------- : %.2f\n"
           "Renda mensal: - - - - - - - - - - - - - - : R$%.2f\n"
           "Renda Per Capita: - - - - - - - - - - - - : R$%.2f\n"
           "Possui deficiencia: --------------------- : %s\n"
           "Cursou em rede publica: - - - - - - - - - : %s\n"
           "Numero de pessoas na familia: - - - - - - : %d\n"
           "Numero de familiares bolsistas na familia : %d\n"
           "Tipo de bolsa desejada: - - - - - - - - - : %s\n\n",
           curso, notaProcessoSeletivo, notaEnem, mediaEnsinoMedio, notaFinal, rendaMensal, rendaPerCapita,
           deficiente ? "Sim" : "Nao", redePublica ? "Sim" : "Nao",
           pessoasNaFamilia, familiaresBolsistas, (tipoBolsaDesejada - 1) ? "Parcial" : "Integral");

    // Exibe resultado final da análise de bolsa
    switch (bolsaStatus) {
        case 1:
            printf("=== Bolsa 100%% CONCEDIDA! ===\n");
            break;
        case 2:
            printf("=== Bolsa 50%% CONCEDIDA! ===\n\n=== Indeferimento bolsa integral: ===\n%s\n", motivoIntegral);
            break;
        default:
            printf("=== CANDIDATURA INVALIDA! ===\n\n=== Indeferimento bolsa integral: ===\n%s\n=== Indeferimento bolsa parcial: ===\n%s\n", motivoIntegral, motivoParcial);
            break;
    }

    getchar(); getchar(); // Pausa para o usuário ver o resultado

    return 0;
}
