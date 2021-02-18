## Manual de Usuario

##### Editar el usuario local
```
git config user.name "<Nombre> <Apellido>"
git config user.email "<email>"
```

##### Agregar los cambios en los programas
Agregar todos los archivos
```
git add .
```
Agregar solamente algunos archivos
```
git add <files>
```

##### Agregar un comentario a los cambios
```
git commit -m "<mensaje>"
```

##### Subir las modificaciones

Al repositorio principal:

``
git push origin
``

Al cualquier otro repositorio agregado:

``
git push <repositio adicional>
``

#### Para poder crear una "pull-request"
##### En caso de Linux
Para poder usar *git pull-request* se debe instalar:
``
pip3 install git-pull-request
``
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
- [Approving a Pull Request](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/approving-a-pull-request-with-required-reviewsi)
- [Creating a Pull Request](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request-from-a-fork)
- [Reset local branch](https://stackoverflow.com/questions/13103083/how-do-i-push-to-github-under-a-different-username)
- [How to change my Git username in terminal?](https://stackoverflow.com/questions/22844806/how-to-change-my-git-username-in-terminal)
