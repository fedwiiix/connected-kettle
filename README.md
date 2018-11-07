# Connected-kettle
Réalisation d'une bouilloire connecté

Le projet consiste à contrôler une bouilloire à distance en radio, bluetooth ou en Wi-Fi. Vous pouvez contrôler la température grâce au capteur présent dans la bouilloire.


<p align="center">
  <img src="https://github.com/fred-sjtm/connected-kettle/blob/master/kettle-img/71D21OsbV0L._SL1000_.jpg?raw=true" height="200">
  <img src="https://github.com/fred-sjtm/connected-kettle/blob/master/kettle-img/71GsK68r6uL._SL1000_.jpg?raw=true" height="200">
  <img src="https://github.com/fred-sjtm/connected-kettle/blob/master/kettle-img/71GyfNfFtbL._SL1000_.jpg?raw=true" height="200">
</p>


Cette bouilloire est réalisé à l'aide d'un récepteur/transmetteur radio 433 khz HC-12 et d'un pic 12f1840. La communication entre ces deux composants se fait en série donc le module radio peut être remplacé par un module bluetooth par exemple HC-06 ou un module Wi-Fi. L'alimentation 5v et le capteur de température sont déjà présents dans la bouilloire. la fonction de choix de température est donc géré par l'appui d'un des deux boutons.

<p align="center" style="float:left;">
  <img src="https://github.com/fred-sjtm/connected-kettle/blob/master/kettle-img/HTB1SPBIKFXXXXaEXFXXq6xXFXXXr.jpg?raw=true" height="100">
  <img src="https://github.com/fred-sjtm/connected-kettle/blob/master/kettle-img/images.jpg?raw=true" height="100">
  <img src="https://github.com/fred-sjtm/connected-kettle/blob/master/kettle-img/schema.jpg?raw=true" height="200">
</p>

Le principe est de bypasser les boutons avec le microcontrôleur. Un niveau 0 simule l'appuis d'un bouton reliées en pull-up. Le microcontrôleur ne donne pas la possibilité de sorties flottantes donc j'utilise deux résistances de 10k pour isoler les deux montages.

Les deux composants sont placés dans le manche de la bouilloire. L'optimisation de la place est primordiale. J'ai relié l'antenne radio à la partie métallique supérieure pour accroître la réception.

<p align="center">
  <img src="https://github.com/fred-sjtm/connected-kettle/blob/master/kettle-img/20180514_232752.jpg?raw=true" height="100">
  <img src="https://github.com/fred-sjtm/connected-kettle/blob/master/kettle-img/20180514_232808.jpg?raw=true" height="100">
  
  <img src="https://github.com/fred-sjtm/connected-kettle/blob/master/kettle-img/20180514_232903.jpg?raw=true" height="100">
  <img src="https://github.com/fred-sjtm/connected-kettle/blob/master/kettle-img/20180514_233135.jpg?raw=true" height="100">
  <img src="https://github.com/fred-sjtm/connected-kettle/blob/master/kettle-img/20180514_234006.jpg?raw=true" height="100">
  <img src="https://github.com/fred-sjtm/connected-kettle/blob/master/kettle-img/20180514_234149.jpg?raw=true" height="100">
</p>

# Control

Pour controler le système, vous pouvez envoyer les commandes suivantes par radio avec par exemple le sytème suivant.

<p align="center">
  <img src="https://github.com/fred-sjtm/connected-kettle/blob/master/kettle-img/600px-HC12_diagram.png" height="100">
</p>

Commandes:
  * |eau60|     
    * reponse:    |ok60|
  * |eau70|     
  ** reponse:    |ok70|
  * |eau80|     
    * reponse:    |ok80|
  * |eau90|     
    * reponse:    |ok90|
  * |eauon|    
    * reponse:    |okon|


