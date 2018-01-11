# Project_Car (C KEIL STM32)
Basé sur le projet réalisé par la team curtis en 2016. Modification du code de façon à y intégrer les modification hardware de la voiture (Bus CAN, Retour de direction, Capteur à ultrason).

Dysfonctionnements et bugs recensés mais non corrigés :
- Inversions momentanées (avant arrière uniquement) des capteurs à ultrason (aléatoire).
- Surchauffe fréquente sur la raspberry ( xserver + serveur video + service contrôle voiture)
- Grandeurs à calibrer voiture par voiture pour la direction et les valeurs batterie.
- Valeurs de vitesse et de distance actuellement envoyées en uint16 (non pertinent)
- Enable / Disable des moteurs ne semble avoir aucun impact
- Absence de boucle de courant
- Absence d’asservissement en position du volant
- Pas de vérification de l’asservissement des moteurs arrières
