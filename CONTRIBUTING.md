<p align="center"><img src="./Sources/imagenes/Logo_Final.png" width="216px"><p>

# Pautas de contribuyente

## Como contribuir:

1. Primero se debe seguir (*fork*) el repositorio principal, esto creará una copia en el repositorio personal.
2. Después se debe crear un *Issue* con la descripción de la modificación que se desea agregar o tomar un *Issue*, si este ya ha sido creado anteriormente. Al momento de que este *Issue* se crea, se le asigna un número de Referencia.
3. Después se debe crear un *branch* local a raíz del *origin/master* con el nombre *Issue-N* donde **N** es el número del *Issue* asignado.
4. En este Branch local realizar todas las modificaciones relacionadas al tema asignado (*Issue*) y asegurarse que este funciona correctamente.
5. Verificar si hay modificaciones en la raíz principal *master* y juntar (*merge*) con el branch local si asi lo fuese, de esta manera se pueden evitar conflictos al momento de agregar el Branch a la raíz principal.
6. Una ves finalizado se debe hacer un *push* al respositorio personal para posteriormente crear un *pull-request*, y asi solicitar que se agrege al *master*.

##### Nota:
- Si se utilizará Windows instalar [GitHub Desktop](https://desktop.github.com/)
- En este caso se debe sincronizar el *upstream/master* con el *master* local antes de crear un branch.

## Crear un Pull request
1. Primero se debe agregar los cambios (*Add*) y después comentarlos (*Commit*).
2. Segundo, subir los cambios al repositorio personal **../[nombre]/Proyecto1_GD** (*Push*)
3. Tercero, en la página principal del GitHub, ir al repositorio personal, ingresar a *Pull Request* y hacer click en **New pull request**.
4. En el lado izquierdo se muestra el repositorio base **e2innovation/Proyecto1_GD** (*master*) y en el lado derecho se selecciona el repositorio personal (*master*) por defecto, en caso de haber creado otro *branch* para realizar los cambios, seleccionar el branch adecuado.
5. Finalmente agregar un titulo y descripción al **Pull-request**.

### Extras

![](https://nvie.com/img/git-model@2x.png)

##### Clonar el repositorio principal
```
git clone git clone https://github.com/e2innovation/Proyecto1_GD.git

```
##### Agregar Repositorios remotos
```
git remote add <apellido> https://github.com/<user>/Proyecto1_GD.git
```
Para ver los repositorios agregados
```
git remote -v
```
Ejemplo:
```
git remote add zarate https://github.com/eduardo-zarate/Proyecto1_GD.git

```
