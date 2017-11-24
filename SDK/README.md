Pour avoir le SDK sur son PC (linux) et ainsi compiler avec les librairies de la raspi :

1. Executer le fichier poky-glibc-x86_64-gei-image-sato-cortexa7hf-neon-vfpv4-toolchain-2.3.2.sh
------------------------------------------------------------------------------------------------

Ce fichier bach (qui est en fait une archive + un script) copie toutes les librairies nécessaires sur le PC. Il demande de choisir l'emplacement, faire entrée puis Y pour avoir l'emplacement par défaut (/opt/poky/2.3.2) ou choisissez l'emplacement si celui-ci ne vous va pas

2. Aller dans /opt/poky/2.3.2 et exécuter cette ligne
-----------------------------------------------------

```
user@pc:~/projet5SIEC$ . /opt/poky/2.3.2/environment-setup-cortexa7hf-neon-vfpv4-poky-linux-gnueabi
```
pour initialiser les variables qu'on va utiliser pour compiler

3. Compiler
-----------

La commande d'avant a exporté la variable CC avec la commande qu'il faut pour cross-compiler (cad compiler utilisant la librairie de la raspi et non celle du PC). Pour info, CC vaut "arm-poky-linux-gnueabi-gcc  -march=armv7ve -marm -mfpu=neon-vfpv4  -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=$SDKTARGETSYSROOT"

Pour compiler le fichier main.c :

```
user@pc:~/projet5SIEC/API_raspi$ $CC main.c
```

Toutes les variables (pour compiler avec le g++ ou le gpp de la carte, pour débugger avec le gdb...) sont dans le fichier /opt/poky/2.3.2/environment-setup-cortexa7hf-neon-vfpv4-poky-linux-gnueabi.

4. Demandez le moi par clé USB le SDK fait 450 Mo
-------------------------------------------------
