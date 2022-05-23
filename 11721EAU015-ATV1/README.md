# semb1-workspace
Sistemas Embarcados 1

Preparar ambiente para programar, seguindo o roteiro ATV a 1.pdf

Criando clone com o github
Estabelecendo conexão e compartilhando arquivos
Baixando arquivos de compilador e ferramentas ST-LINK

Seguindo o roteiro ATV a 1.pdf

Instalar USBIP no WSL2
Fazendo download do arquivo no windows

Criação de diretório de sistemas embarcados 1
Criação de diretório de 11721EAU015-ATV1
    
Criação dos arquivos a serem trabalhados
    main.c - arquivo em que será executado o código que será mandado para o stm32, 
todas as variáveis criadas precisam ser direcionadas a seus endereços de memórias, 
para evitar a sobreposição de variáveis e corromper uma entrada importante.

    startup.c - basicamente define os endereços
    iniciais da memoria ram para cada 
variável declarada seja colocada em seu endereço de memoria correspondente.
Define os vetores de endereços de rotinas de tratamentos, que são chamados para tratar algum erro do controlador.
Define variáveis que serão chamadas de arquilo linker script posteriormente. 
organiza os endereços de rotina na memoria Ram.
    Makefile - Automatiza a compilação de arquivos .c gerando arquivos objetos
    executáveis. 
