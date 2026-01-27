_Este proyecto ha sido creado como parte del currículo de 42 por matoledo, aosset-o_.

# Minishell

## Descripción

La Minishell es un proyecto destinado a un estudio profundo de Bash y su funcionamiento.

El objetivo es simular un terminal de Bash "limitada" con el uso de C. Gestionando problemas como: pipes de comunicación, ejecución de comandos (con argumentos y opciones), señales por teclado, etc.

De esta forma al acabar el proyecto debería ser capaz de ejecutar correctamente gran parte de los comandos en bash, desde _ls_, hasta combinaciones como _cat < input.txt | ls -l > output.txt_. Realizando correctamente tanto las tareas de parseo, de redirección y de ejecución.

## Instrucciones

Este proyecto cuenta con el uso de un archivo Makefile, de esta forma, el uso del comando _make_ desde la raiz del proyecto permite la compilación y puesta a punto para su uso facilmente.

Una vez compilado solo hay que ejecutar el programa resultante en la terminal, poniendo _./minishell_

## Recursos

Este proyecto ha sido desarrollado gracias a documentaciones como la [_documentación de Linux_](https://man7.org/index.html) y la [_documentación de GNU_](https://www.gnu.org/doc/doc.html) donde explican con detalle gran parte de las funciones necesarias y comportamiento de la terminal así como ejemplos de uso.

Para complementar esa información se ha usado la ayuda de agentes a los que se ha acudido con fines informativos (nunca pidiendo que crearan desde cero código, funcionalidades, etc.).

Por último, se ha hecho un gran uso de Youtube y tutoriales creados por la comunidad.