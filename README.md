## Atividade de Sistemas Operacionais

###### Nessa tarefa, com o objetivo de testar diferentes implementações de sincronismo, serão testados 3 programas com soluções ou não de sincronismo.

### Conceitos

#### Troca Involuntária
Ocorre quando o escalonador tira o processo de RUNNING de forma obrigatória. Isso pode ocorrer quando tal excede o tempo de execução ou perde prioridade. 
#### Troca Voluntária
Quando um processo por conta própria termina sua execução então libera o recurso ou entra no estado WAITING para aguardar uma I/O, por exemplo.

### Caso 1: Sem sincronismo
#### Para executar

`$ gcc printx.c -lpthread && ./a.out`

#### Resultado
Como era de se esperar, o "for" que possuia seção critica com condição de corrida entre as Threads  houve muita concorrência e o resultado foi incoerente. Cada execução soltou um valor diferente: 
###### Exemplos:
`Valor final de x: 22860`
`Valor final de x: 23799`
`Valor final de x: 30953`

	Voluntary context switches: 11
	Involuntary context switches: 1


### Caso 2: Com sincronismo do tipo lock com test_and_set
#### Para executar

`$ gcc printxLOCK.c -lpthread && ./a.out`

#### Resultado
Agora o valor foi coerente. O for executou fazendo o lock na seção crítica. Existiram menos trocas de contexto nos quatro núcleos da máquina.
###### Exemplos:
`Valor final de x: 50000`

	Voluntary context switches: 3
	Involuntary context switches: 3

### Caso 3: Com sincronismo do tipo fila de esperandos
#### Para executar

`$ gcc printxQUEUE.c -lpthread && ./a.out`

#### Resultado
Agora o valor foi coerente, diminui para 100 iterações para não ficar esperando muito tempo. Acredito que entrou no melhor caso e não teve trocas involuntárias.
###### Exemplos:
`Valor final de x: 500`

	Voluntary context switches: 9
	Involuntary context switches: 0



