# 🧾 Sistema de Avaliação de Bolsas de Estudo (C)

Este projeto é um sistema em linguagem C que avalia se um candidato tem direito a uma **bolsa de estudos integral (100%)** ou **parcial (50%)**, com base em critérios como renda per capita, desempenho acadêmico e outros requisitos sociais.

## 🚀 Funcionalidades

- Coleta de dados do candidato via terminal
- Cálculo da renda per capita e nota final ponderada
- Avaliação automática conforme critérios definidos
- Registro de motivos de indeferimento (com mensagens específicas)
- Exibição clara dos resultados

## 📋 Critérios para Bolsa Integral (100%)

- Renda per capita **≤ R$800**
- Nota final **≥ 8.0**
- Candidato **com deficiência** ou **egresso da rede pública**
- Nenhum outro familiar bolsista
- Desejo explícito pela bolsa integral

## 📋 Critérios para Bolsa Parcial (50%)

Se a integral não for concedida, o sistema verifica a elegibilidade para bolsa parcial, onde:

- Renda per capita **≤ R$1600**
- Nota final mínima:
  - **6.0** se for deficiente ou da rede pública
  - **7.5** caso contrário
- No máximo **um familiar bolsista**
- Desejo explícito pela bolsa parcial

## 📦 Como Executar

1. Compile o código com `gcc` ou similar:

```
gcc bolsa.c -o bolsa
```
2. Execute no terminal:
```
./bolsa
```
