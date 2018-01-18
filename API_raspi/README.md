# API_raspi

Sur la Raspberry Pi 3, plusieurs programmes sont implémentés en C. Attention, tout le code est contenu dans les dossiers MobleyProject/API_raspi, MobleyProject/GPS et MobleyProject/parser :
- l'interface graphique pour afficher des informations et permettre une sélection de l'utilisateur. Se trouve dans _API\_raspi/IHM_. **Nécessite l'installation de GTK 3.**
- le traitement des données GPS pour connaître la position de la voiture et calculer son azimut. Se trouve dans _GPS_. **Nécessite l'installation de gpsd et libgps-dev.**
- la régulation de la trajectoire pour permettre un déplacement autonome. Se trouve dans _GPS/Trajectoires.
- un parser de fichiers *.map* contenant les coordonnées GPS des points de destination, des points intermédiaires et la définition des segments. Se trouve dans _Parser_
- la communication CAN. Se trouve dans _API\_raspi/com\_CAN_.
- la gestion de la batterie. Se trouve dans _API\_raspi/IHM_.
