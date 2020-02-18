# Proyecto1_GD

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

##### Editar el usuario local
```
git config user.name "<Nombre> <Apellido>"
git config user.email "<email>"
```

##### Agregar los cambios en los programas
```
#Agregar todos los archivos
git add .
#Agregar solamente algunos archivos
git add <files>
```

##### Agregar un Comentario a los cambios
```
git commit -m "<mensaje>"
```

##### Subir las modificaciones
```
# Al repositorio principal
git push origin
# Al cualquier otro repositorio agregado
git push <repositio adicional>
```

#### Para poder crear una "pull-request"
##### En caso de Linux
Para poder usar *git pull-request* se debe instalar:
```
pip3 install git-pull-request
```
##### En caso de Windows
Utilizar Windows y crearlo directamente desde la página de [GitHub](https://github.com/).
#### Para Editar el usuario a utilizar
``
git config credential.username "new_username"
``

### Fuentes
- [git pull-request](https://pypi.org/project/git-pull-request/)
- [Pull Request](https://help.github.com/es/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request)
- [Como hacer Pull Request](https://github.com/omegaup/omegaup/wiki/C%C3%B3mo-Hacer-un-Pull-Request)
- [Pull Request](https://julien.danjou.info/git-pull-request-command-line-tool/i)
- [Aprovving a Pull Request](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/approving-a-pull-request-with-required-reviewsi)
- [Creatin a Pull Request](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request-from-a-fork)
- [Reset local branch](https://stackoverflow.com/questions/13103083/how-do-i-push-to-github-under-a-different-username)
- [How to change my Git username in terminal?](https://stackoverflow.com/questions/22844806/how-to-change-my-git-username-in-terminal)
