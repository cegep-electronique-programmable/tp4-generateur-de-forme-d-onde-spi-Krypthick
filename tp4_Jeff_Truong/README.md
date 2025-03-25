# TP4 - Générateur de forme d'onde SPI

## Objectif du laboratoire 
Créer un générateur de forme d'onde à l'aide d'un potentiomètre numérique.

## Description
Concevoir un circuit de générateur de fonction à l'aide d'un potentiomètre numérique MCP42010. Vous devez écrire un programme dans le PIC qui fonctionne de cette façon:
- Les réglages peuvent être changés sans arrêter les programmes;
- On peut générer des formes d’ondes sinusoïdale[S], carrée[C] ou triangulaire[T];
-	On peut varier la fréquence de 20 Hz à 100Hz (par incrément de 20Hz) à l’aide des touches [+] et [-];
-	Dès qu’un paramètre est modifié par l’usager, afficher sur le LCD le type de forme d’onde et la fréquence.<br/>

Une fois le programme fonctionnel, <strong>documenter les calculs, prendre une capture d’écran</strong> avec l’analyseur logique de la communication nécessaire pour changer la sortie du potentiomètre et <strong>décrire son fonctionnement</strong> de façon détaillée.

## Évaluation
### Faire vérifier
- Le fonctionnement sera vérifié au laboratoire.

### Remettre dans le répertoire GitHub
- Le programme bien commenté.
- Un fichier Word contenant
  - une page de présentation
  - Les détails des calculs effectués
  - la capture d'écran de l'analyseur logique demandée ainsi qu'une explication du rôle de chaque bits.

### Pondération
- 40% - Fonctionnement des 3 formes d'onde
- 40% - Fonctionnement de la variation en fréquence
- 10% - Calculs exacts
- 10% - Capture d'écran de l'analyseur logique

##  Manipulations
Voici les étapes à suivre afin de compléter le TP avec succès :
- Lire la datasheet du MCP42010 afin de déterminer comment bien brancher le composant.
- Relier la carte PIC au MCP42010 à l’aide de la plaquette de montage.
- Créer un nouveau projet à l’aide de MCC et configurer le périphérique MSSP en mode SPI à une vitesse raisonnable (par exemple 312.5kHz).
- Remplacer le contenu de « main.c » par le contenu du fichier fourni « TP4mainDepart.c ». Le code est fonctionnel sans aucune modification en autant que le MCC soit bien configuré.
- Rouler le programme sans modifier le code et mesurer afin d’observer une onde sinusoïdale.
- Si l’onde sinusoïdale n’est pas visible :
  - Il faut s’assurer que les branchements sont bien faits. Chaque broche du MCP reçoit le bon signal ? Le COMMAND BYTE du MCP42010 doit être bien compris pour s’assurer que le bon potentiomètre est utilisé…
  - Utiliser l’analyseur logique pour visualiser et décoder les signaux de communication envoyés au MCP42010.
- L’onde est visible, il faut maintenant trouver un moyen de changer la forme d’onde envoyé.
- Les 3 types de formes d’onde peuvent être envoyés, il faut trouver un moyen de contrôler le potentiomètre numérique moins fréquemment. En utilisant la routine d’interruption du timer 1 peut-être ?..
- Le TP est presque terminé, il faut s’assurer que tout ce qui est demandé dans la section « description » est réalisé.

## Pistes de solutions:
1. Tester et vérifier avec l’oscilloscope la génération de la forme d’onde sinusoïdale sur la pin 9 du MCP42010. Vérifier la fréquence de l’onde, qui devrait être la fréquence maximale si la fonction sinus est appelée en boucle dans le main.
2. Ajouter le Timer 1 avec interrupt pour contrôler la fréquence de l’onde. Suggestion, utilisez l’horloge de base sans prescaler pour la fréquence du Timer1 et entrez une valeur pour la période que vous voulez tester. N’oubliez pas les enable interrupt global et enable interupt peripheral !! Tester et vérifier la fréquence de l’onde.
3. Ajouter la fonction qui permet de charger le Timer dans la routine d’interruption du Timer afin de générer une onde ayant la fréquence requise.  Indices : si la fréquence doit être de 100Hz, la période est de 10ms. Si on génère l’onde avec 256 points, on doit modifier la valeur du potentiomètre chaque 10ms/256. 
