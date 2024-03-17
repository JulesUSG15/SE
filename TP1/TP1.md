# TP1 – Initiation à LINUX

## 1. Organisation de Dossiers et Fichiers

### Question 1 : 
- **`pwd`** : Affiche le chemin absolu du répertoire courant.
- **`cd [répertoire]`** : Change le répertoire courant pour `[répertoire]`. Si aucun répertoire n'est spécifié, il revient au répertoire personnel de l'utilisateur.
- **`ls [options]`** : Liste les fichiers et répertoires dans le répertoire courant. Les options `-a`, `-l` et `-al` permettent respectivement d'afficher les fichiers cachés, d'afficher les détails des fichiers et les deux combinés.
- **`touch [fichier]`** : Crée un fichier vide nommé `[fichier]`, ou met à jour la date de modification s'il existe déjà.
- **`cp [source] [destination]`** : Copie le fichier ou répertoire `[source]` vers `[destination]`.
- **`mv [source] [destination]`** : Déplace ou renomme le fichier ou répertoire `[source]` vers `[destination]`.
- **`mkdir [répertoire]`** : Crée un répertoire nommé `[répertoire]`.
- **`rmdir [répertoire]`** : Supprime un répertoire vide nommé `[répertoire]`.
- **`rm [fichier]`** : Supprime le fichier nommé `[fichier]`.

### Question 2 :
1. **Revenir à votre répertoire utilisateur** :
   - ```bash
     cd ~
     ```
   Ou, équivalently :
   - ```bash
     cd
     ```

2. **Créer un sous-répertoire `tpse`** :
   - ```bash
     mkdir tpse
     ```

3. **Dans ce répertoire, créer un fichier `texte.txt`** :
   - ```bash
     touch tpse/texte.txt
     ```

4. **Taper `ls`, puis `ls -a`, `ls -l` et `ls -al`** :
   - Pour lister les fichiers et répertoires :
     ```bash
     ls
     ```
   - Pour inclure les fichiers cachés :
     ```bash
     ls -a
     ```
   - Pour afficher les détails des fichiers, comme les permissions, le propriétaire, la taille, et la date de dernière modification :
     ```bash
     ls -l
     ```
   - Pour combiner les deux options précédentes et afficher à la fois les fichiers cachés et leurs détails :
     ```bash
     ls -al
     ```
### Question 3 :
1. **Modifiez le nom du fichier `texte.txt` en `texte2.txt`** :
   ```bash
   mv tpse/texte.txt tpse/texte2.txt
   ```

2. **Créez un deuxième répertoire `tests` dans votre répertoire racine, et deux sous-répertoires `t1` et `t2` dans le répertoire `tests`** :
   ```bash
   mkdir tests
   mkdir tests/t1
   mkdir tests/t2
   ```

3. **Déplacez le fichier `texte2.txt` précédent dans le répertoire `tests/t1`** :
   ```bash
   mv tpse/texte2.txt tests/t1/
   ```

4. **En utilisant la commande `cp`, copiez le fichier `texte2.txt` dans le répertoire `tpse`** :
   - Étant donné que nous avons déplacé `texte2.txt` dans `tests/t1`, nous devons d'abord le copier de là :
   ```bash
   cp tests/t1/texte2.txt tpse/
   ```

5. **Supprimez le répertoire `tests/t1` à l'aide de la commande `rmdir` et tapez `ls`** :
   ```bash
   rmdir tests/t1
   ```
   - Ensuite, vous pouvez vérifier si le répertoire a été supprimé en listant le contenu du répertoire parent :
   ```bash
   ls tests
   ```

6. **Pourquoi le répertoire `tests/t1` peut ne pas être supprimé avec `rmdir` ?**

La commande `rmdir` ne supprime que lesrmdir tests/t1 répertoires vides. Si `tests/t1` contient encore des fichiers ou des sous-répertoires (ce qui ne sera pas le cas ici puisque nous avons déplacé `texte2.txt` en dehors de celui-ci avant de tenter de le supprimer), la commande échouera en retournant une erreur indiquant que le répertoire n'est pas vide. Dans notre cas, comme `tests/t1` devrait être vide après le déplacement du fichier, `rmdir` devrait réussir à supprimer le répertoire.

### Question 4 :
```bash
rm -rf tests/t1
```

Cette commande supprime le répertoire `t1` ainsi que son contenu de manière récursive, sans demander de confirmation, même si le répertoire contient des fichiers ou des sous-répertoires.

**Explication :**

- `rm` : Commande pour supprimer des fichiers et répertoires.
- `-r` ou `-R` : Option pour supprimer de manière récursive le contenu des répertoires, c'est-à-dire supprimer le répertoire ainsi que tout son contenu, incluant d'autres sous-répertoires.
- `-f` : Option pour forcer la suppression sans demander de confirmation, même pour les fichiers en lecture seule.

## 2. Manipulation des Fichiers

### Question 1 :
- **`cat [fichier]`** : Affiche le contenu d'un fichier sur la console.
- **`less [fichier]`** : Affiche le contenu d'un fichier page par page.
- **`nl [fichier]`** : Affiche le contenu d'un fichier avec les lignes numérotées.

### Question 2 :
- **`head [options] [fichier]`** et **`tail [options] [fichier]`** : Affichent respectivement le début et la fin d'un fichier. L'option `-n [nombre]` permet de spécifier le nombre de lignes à afficher.
- **`ln [option] [source] [lien]`** : Crée un lien physique (sans option) ou symbolique (`-s`) nommé `[lien]` pointant vers `[source]`.

### Question 3 :
Pour afficher les lignes du fichier `/etc/passwd` en les numérotant, on utilise : 

```bash
nl /etc/passwd
```
### Question 4 :
Pour accomplir les tâches demandées, voici les étapes et les commandes correspondantes :

1. **Créez un fichier `fich1` dans le répertoire `tests/t2`** :
   ```bash
   touch tests/t2/fich1
   ```

2. **Utilisez la commande `ln` pour créer un lien physique nommé `fich2` pointant vers `fich1`** :
   ```bash
   ln tests/t2/fich1 tests/t2/fich2
   ```

3. **Créez un lien symbolique (ou un lien logique) nommé `fich3` pointant vers `fich1`** :
   ```bash
   ln -s tests/t2/fich1 tests/t2/fich3
   ```
4. **Explication : Que se passe-t-il si vous supprimez le fichier `fich1` ?**

- **Pour le lien physique (`fich2`)** : Les liens physiques pointent vers l'emplacement du contenu du fichier sur le disque. Ainsi, si vous supprimez `fich1`, `fich2` continuera d'accéder au contenu du fichier sans problème car le lien physique ne fait pas référence au nom du fichier mais directement à son contenu stocké sur le disque. Le contenu du fichier sera conservé tant qu'il existera au moins un lien physique pointant vers celui-ci. Le système ne libérera l'espace occupé par le fichier sur le disque que lorsque le dernier lien physique sera supprimé.

- **Pour le lien symbolique (`fich3`)** : Les liens symboliques pointent vers le nom du fichier et non vers son contenu direct sur le disque. Si vous supprimez `fich1`, le lien symbolique `fich3` deviendra un lien brisé (ou un lien mort), car il pointera vers un fichier qui n'existe plus. Vous ne pourrez pas utiliser `fich3` pour accéder au contenu de `fich1` après la suppression de ce dernier, car le lien symbolique ne pointe plus vers un fichier existant.

## 2.1 Manipulation des Données d'un Fichier

### Question 1 :
1. **Trouvez à l'aide de la commande `grep` les lignes du fichier `/etc/bash.bashrc` ne contenant pas l'un des mots true, True, TRUE** :
```bash
grep -v -E 'true|True|TRUE' /etc/bash.bashrc
```

2. **Quelle commande permet de connaître le nombre de lignes où le mot `return` apparaît dans le fichier `/etc/bash.bashrc` ?**
```bash
grep 'return' /etc/bash.bashrc | wc -l
```

### Question 2 :
```bash
find tests/t2 -type f -name "*fich*"
```

## 3. Utilisateurs et Droits

### Question 1 : 
```bash
ls -l tests/t2/fich2
```

Cette commande affichera une ligne de sortie avec plusieurs informations. Voici comment lire cette ligne :

- **Premier champ** : Il s'agit des droits d'accès au fichier. Il commence par un caractère indiquant le type de fichier (par exemple, `-` pour un fichier ordinaire, `d` pour un répertoire) suivi de trois groupes de trois permissions : pour le propriétaire (`rwx`), pour le groupe (`rwx`), et pour les autres (`rwx`). Chaque position indique respectivement le droit de lire (`r`), d'écrire (`w`), et d'exécuter (`x`) le fichier. Un tiret (`-`) à la place d'une lettre indique l'absence de cette permission.
  
- **Deuxième champ** : Nombre de liens physiques vers ce fichier.

- **Troisième champ** : Nom du propriétaire du fichier.

- **Quatrième champ** : Nom du groupe propriétaire du fichier.

- **Cinquième champ** : Taille du fichier en octets.

- **Sixième au huitième champ** : Date de dernière modification.

- **Neuvième champ** : Nom du fichier.

**Exemple :**
```
-rw-rw-r-- 2 jules jules 0 mars  15 14:28 tests/t2/fich2

```

- **Propriétaire du fichier** : `jules`
- **Groupe propriétaire** : `jules`
- **Droits d'accès** :
  - Pour le propriétaire (`utilisateur`): lire et écrire (`rw-`)
  - Pour le groupe (`groupe`): lire seulement (`rw-`)
  - Pour les autres utilisateurs: lire seulement (`r--`)

### Question 2 : 
```bash
chmod 766 tests/t2/fich2
```

**Explication de la commande :**

- `chmod` : Modifie les permissions d'un fichier ou répertoire.
- `766` : 
  - Le premier chiffre (7) définit les permissions pour le propriétaire. Le chiffre 7 est la somme de 4 (lecture), 2 (écriture), et 1 (exécution), donc cela donne au propriétaire le droit de lire, écrire et exécuter le fichier.
  - Le deuxième chiffre (6) définit les permissions pour le groupe. Le chiffre 6 est la somme de 4 (lecture) et 2 (écriture), donnant au groupe le droit de lire et écrire le fichier, mais pas de l'exécuter.
  - Le troisième chiffre (6) est pour les "autres" utilisateurs, avec les mêmes droits que le groupe : lecture et écriture.
- `tests/t2/fich2` : Chemin du fichier dont vous modifiez les permissions.

## 4. Flux de Redirection et Tubes

### Question 1 :
1. **Créer un fichier `batman.txt` contenant la phrase "Gotham City" dans le répertoire `tests/t2`** :
   ```bash
   echo "Gotham City" > tests/t2/batman.txt
   ```

2. **Copier le contenu de `batman.txt` dans un autre fichier nommé `robin.txt` sans utiliser la commande `cp` mais en utilisant un tube** :
   ```bash
   cat tests/t2/batman.txt | tee tests/t2/robin.txt > /dev/null
   ```
   Cette méthode avec `tee` permet de copier le contenu de `batman.txt` vers `robin.txt` et pourrait être utile dans des scripts ou des pipelines plus complexes où `tee` offre la flexibilité de copier les données vers plusieurs destinations à la fois ou de conserver la sortie dans le flux pour un traitement ultérieur.

### Question 2 :
La commande `wc -l /etc/passwd` compte le nombre de lignes présentes dans le fichier `/etc/passwd`. Ici, `wc` est la commande qui permet de compter le nombre de lignes, mots, et caractères dans les fichiers spécifiés, et l'option `-l` indique que nous sommes intéressés uniquement par le compte des lignes.

Quant à `cat /etc/passwd | wc -l`, cette commande fait essentiellement la même chose, mais de manière légèrement différente :
- `cat /etc/passwd` affiche le contenu du fichier `/etc/passwd`.
- Le pipe `|` passe ce contenu comme entrée à la commande suivante.
- `wc -l` compte alors le nombre de lignes de cette entrée.

## 5. Gestion des Processus

### Question 1 :
- **`ps [options]`** : Affiche les processus en cours d'exécution. Les options `-e` et `-f` affichent tous les processus et plus de détails, respectivement.
- **`top`** : Affiche les processus en temps réel, ainsi que des statistiques sur l'utilisation du système.
- **`kill [options] [PID]`** : Envoie un signal au processus identifié par `[PID]`. Sans option, envoie SIGTERM. L'option `-9` envoie SIGKILL, forçant l'arrêt du processus.

### Question 2 :
1. **Nombre de processus appartenant à root**
```bash
ps -ef | grep '^root' | wc -l
```
- `ps -ef` affiche tous les processus en cours d'exécution dans un format complet.
- `grep '^root'` filtre les lignes commençant par "root", correspondant aux processus dont l'UID est root.
- `wc -l` compte le nombre de lignes, qui représente le nombre de processus appartenant à root.

2. **Processus père de tous les autres**

Le processus père de tous les autres processus dans les systèmes Unix et Linux est généralement`systemd`. Son PID est généralement `1`.
```bash
ps -p 1
```
Cette commande affiche les informations du processus dont le PID est 1, qui est le premier processus lancé au démarrage du système et par conséquent le parent de tous les autres processus.

### Question 3 :
1. **Ouvrir `top`** :
   - Dans un terminal, tapez `top` et appuyez sur Entrée.

2. **Combien de processus sont présents actuellement sur votre ordinateur ?**
   - 326

3. **Combien sont prêts (état running / en cours) ?**
   - 1

4. **Combien sont bloqués (état sleeping / en veille) ?**
   - 325

5. **Combien de processus zombie y-a-t-il ?**
   - 0

## 5.1
### Question 1 :
1. **Lancer `xclock` en arrière-plan** :
   ```bash
   xclock &
   ```

2. **Utiliser `pstree` pour trouver l'instance de `xclock`** :
   ```bash
   pstree | grep xclock
   ```
### Question 2 :
- **SIGINT (signal numéro 2)** : Ce signal est généralement généré par l'utilisateur en appuyant sur Ctrl+C dans le terminal. Il indique au processus de s'interrompre, offrant une manière propre de terminer les programmes en cours d'exécution.

- **SIGQUIT (signal numéro 3)** : Généré par l'utilisateur en appuyant sur Ctrl+\ dans le terminal. Il indique au processus de quitter et de générer un fichier de core dump, ce qui peut être utile pour le débogage.

- **SIGTERM (signal numéro 15)** : C'est le signal par défaut utilisé par la commande `kill` pour terminer un processus. Il signale au processus de se terminer proprement. Les processus peuvent écouter ce signal et le gérer s'ils ont besoin de réaliser des opérations de nettoyage avant de s'arrêter.

- **SIGKILL (signal numéro 9)** : Ce signal force l'arrêt immédiat du processus. Contrairement à SIGTERM, le processus ne peut ni écouter ni intercepter ce signal. C'est un moyen infaillible de terminer un processus, mais il ne permet pas au processus de libérer ses ressources proprement.

**Pour envoyer un signal SIGKILL au processus `xclock` :**
D'abord, trouver l'ID du processus (PID) de `xclock`.
```bash
pgrep xclock
```

Ensuite, utilisez `kill` avec le PID pour envoyer SIGKILL à `xclock` :
```bash
kill -SIGKILL 6479
```

```bash
pkill -SIGKILL xclock
```

Cette commande enverra le signal SIGKILL à toutes les instances de `xclock` en cours d'exécution.