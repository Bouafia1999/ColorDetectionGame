# ColorDetectionGame

## Description

`ColorDetectionGame` est un jeu simple développé en C++ utilisant la bibliothèque OpenCV. Dans ce jeu, des cercles verts tombent du haut de l'écran, et le joueur doit interagir avec eux lorsque la couleur rouge est détectée sur l'écran. Le score augmente chaque fois qu'un cercle touche une zone rouge. Le jeu se termine lorsque les cercles tombent hors de l'écran.

## Fonctionnalités

- **Détection de Couleurs :** Le jeu utilise OpenCV pour détecter la couleur rouge dans le flux vidéo de la caméra.
- **Interaction avec les Cercles :** Les cercles verts tombent du haut de l'écran, et le joueur gagne des points en détectant les cercles lorsqu'une couleur rouge est présente.
- **Interface Utilisateur :** Affichage en temps réel du score et du statut du jeu, avec un message "Game Over" lorsque le jeu se termine.

## Prérequis

Avant de commencer, assurez-vous d'avoir les outils suivants installés :

- [OpenCV](https://opencv.org/) (version 4.x ou supérieure)
- Un compilateur C++ compatible (comme GCC ou MSVC)
- [CMake](https://cmake.org/) pour la gestion de la construction (optionnel, selon votre configuration)

## Installation

1. **Cloner le dépôt :**

   ```bash
   git clone https://github.com/Bouafia1999/ColorDetectionGame.git
