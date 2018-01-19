# Projet Mobley 5SIEC 2017-2018 : GeoCar, le véhicule autonome


Ce document est à l'attention des développeurs qui reprendront le projet.


*Auteurs : Lucas Gissot, Léo Larsson, Délia Loupias, Eric Lubat, Volamiary Tamino - 5SIEC promo 51 - INSA Toulouse.*

## 1. Présentation du projet

Ce projet avait pour but d'implémenter un système qui permet à une petite voiture de se déplacer de façon autonome vers un lieu sur le campus choisi par l'utilisateur sur une interface, afin de guider celui-ci. GeoCar est équipée d'une Raspberry Pi 3, d'un STM 32, d'un GPS, d'un écran tactile, de 3 moteurs, d'une batterie et de capteurs de proximité ultrason. Plus d'informations sur <https://sites.google.com/site/projetsecinsa/projets-2017-2018/project-mobley>.

## 2. Architecture de GeoCar

### 2.1. Hardware

La RasPi contrôle les 2 moteurs des roues arrières et le moteur du volant. Elle est connectée aux 6 capteurs ultrasons (3 à l'avant et 3 à l'arrière). La RasPi a une interface sur l'écran tactile (un Raspbian tourne dessus). Le GPS/IMU est relié en USB dessus. Il est également possible de connecter un clavier et une souris. Un bus CAN via les ports série relie la RasPi et le STM.
Une caméra est installée à l'avant de la voiture mais nous ne l'avons pas utilisé.

### 2.2. Software

La RasPi envoie des ordres de déplacement au STM via les messages CAN. Par exemple, si la RasPi envoie l'ordre avancer, le STM va commander les moteurs.


Tout le code du STM est en C. Une régulation PI est implémentée pour commander la vitesse des moteurs arrières. Une régulation très simple existe pour la commande du moteur du volant. La carte transmet également le niveau de la batterie à la RasPi, et s'arrête en dessous d'un certain seuil après avoir demandé à l'autre carte d'arrêter de transmettre. Si le STM ne reçoit aucun ordre, la voiture restera dans le même état. Une partie du programme sert à envoyer et récupérer les messages CAN périodiquement.


Sur la RasPi, plusieurs programmes sont implémentés en C :
- l'interface graphique pour afficher des informations et permettre une sélection de l'utilisateur. **Nécessite l'installation de GTK 3.**
- le traitement des données GPS pour connaître la position de la voiture et calculer son azimut. **Nécessite l'installation de gpsd et libgps-dev.**
- la régulation de la trajectoire pour permettre un déplacement autonome.
- un parser de fichiers *.map* contenant les coordonnées GPS des points de destination, des points intermédiaires et la définition des segments.
- la communication CAN.
- la gestion de la batterie.

## 3. Structure du projet

### I- API_raspi

Contient le code sur la RasPi.

#### I.1- com_CAN

Contient le code pour la communication CAN.

#### I.2- IHM

Contient le code de l'IHM.

#### I.3- GPS

Contient le code pour traiter les données GPS et pour la régulation du cheminement.

#### I.4- parser

Contient le parseur des fichiers .map et ces derniers.

### II- API_STM32_Vx

Contient le code sur le STM32. Dernière version : API_STM32_VF1.

#### II.1- lib

Contient les drivers.

#### II.2- app

Contient le reste du code.

### III- SCADE

Contient le projet SCADE de surveillance des capteurs ultrason, et le code C généré (sous KCG). Créé avec SCADE Suite v19.2.

### IIII- convention.txt

Convention de codage adoptée.

## 4. Pistes d'amélioration et informations utiles

- Utiliser la caméra pour améliorer la régulation de trajectoire ou la détection d'obstacles.
- Augmenter la vitesse des moteurs arrières pour améliorer la précision du GPS/IMU.
- La Wi-Fi du raspbian ne fonctionne plus.
- Les ID des variables CAN sont indiqués dans le fichier API\_raspi/com\_CAN/can_var.h.
