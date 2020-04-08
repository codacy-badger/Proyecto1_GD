<p align="center"><img src="Imagenes/Logo_Final.png" width="216px"><p>

# Pautas de contribuyente

## Como contribuir:
==========================================

1. Primero se debe seguir (*fork*) el repositorio principal, esto creará una copia en el repositorio personal.
2. Después se debe crear un *Issue* con la descripción de la modificación que se desea agregar o tomar un *Issue*, si este ya ha sido creado anteriormente. Al momento de que este *Issue* se crea, se le asigna un número de Referencia.
3. Después se debe crear un *branch* local a raíz del *origin/master* con el nombre *Issue-N* donde **N** es el número del *Issue* asignado.
4. En este Branch local realizar todas las modificaciones relacionadas al tema asignado (*Issue*) y asegurarse que este funciona correctamente.
5. Verificar si hay modificaciones en la raíz principal *master* y juntar (*merge*) con el branch local si asi lo fuese, de esta manera se pueden evitar conflictos al momento de agregar el Branch a la raíz principal.
6. Una ves finalizado se debe hacer un *push* al respositorio personal para posteriormente crear un *pull-request*, y asi solicitar que se agrege al *master*.

#### Nota:
- Si se utilizará Windows instalar [GitHub Desktop](https://desktop.github.com/)
- En este caso se debe sincronizar el *upstream/master* con el *master* local antes de crear un branch.

## Extras

##### Clonar el repositorio principal
```
git clone git clone https://github.com/e2innovation/Proyecto1_GD.git

```
##### Agregar Repositorios
```
git remote add <apellido> https://github.com/<user>/Proyecto1_GD.git
#Para ver los repositorios agregados
git remote -v
#Ejemplo
git remote add zarate https://github.com/eduardo-zarate/Proyecto1_GD.git

```
