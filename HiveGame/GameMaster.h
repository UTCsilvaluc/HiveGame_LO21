#ifndef GAMEMASTER_H
#define GAMEMASTER_H
#include <fstream>  // Ajout de l'en-tête pour la gestion des fichiers
#include "Joueur.h"
#include "Plateau.h"
#include "Action.h"
#include <iostream>
#include <memory>
#include <limits>
#include <stack>

int getInput(const std::string& prompt, int minValue, int maxValue);
bool positionEstValide(const Hexagon& position, const std::vector<Hexagon>& deplacementsPossibles);
class GameMaster {
private:
    Plateau plateau;
    Joueur *joueur1;
    Joueur *joueur2;
    unsigned int mode;
    unsigned int tour;
    void deplacerPion(Joueur* current);
    void placerPion(Joueur* current, bool b);
    std::stack<Action*> actionsPile;
    unsigned int maxRetourArriere;
    InsecteFactoryImpl insecteFactory;
    std::string toJson() const;
    void saveGame() const;
    void displaySaveGame();
    void undoLastTwoActions();
public:
    bool hasPlayQueen(Joueur *currentPlayer);
    GameMaster() : joueur1(nullptr), joueur2(nullptr) , mode(0) {}
    Insecte* selectionnerInsecte(Joueur* current);
    GameMaster(Plateau plateau, unsigned int maxRetourArriere = 5)
        : joueur1(nullptr), joueur2(nullptr), mode(0), tour(0), plateau(plateau), maxRetourArriere(maxRetourArriere) {}
    void startGame();
    void jouer();
    int getInputForAction(Joueur* current);
    bool detectWinner(Joueur *joueur1 , Joueur *joueur2);
    void choixExtensions() {
        // Afficher la liste des extensions disponibles
        while (true) {
            std::cout << "\n--- Liste des extensions disponibles ---\n";
            std::vector<std::string> extensionsDisponibles = insecteFactory.getInsecteExtensionsDisponibles();

            if (extensionsDisponibles.empty()) {
                std::cout << "Aucune extension disponible.\n";
                break;
            }

            for (size_t i = 0; i < extensionsDisponibles.size(); ++i) {
                std::string statut = insecteFactory.estExtensionActive(extensionsDisponibles[i]) ? "(Activée)" : "(Non activée)";
                std::cout << i + 1 << ". " << extensionsDisponibles[i] << " " << statut << std::endl;
            }
            std::cout << "\nEntrez le numéro de l'extension à activer/désactiver (0 pour quitter) : ";
            int choix;
            std::cin >> choix;
            if (choix == 0) {
                break;
            }

            if (choix < 1 || choix > extensionsDisponibles.size()) {
                std::cout << "Choix invalide. Veuillez entrer un numéro valide.\n";
                continue;
            }

            std::string extensionChoisie = extensionsDisponibles[choix - 1];
            bool estActive = insecteFactory.estExtensionActive(extensionChoisie);

            if (estActive) {
                std::cout << extensionChoisie << " est déjà activée. Vous voulez la désactiver ? (o/n) : ";
                char reponse;
                std::cin >> reponse;
                if (reponse == 'o' || reponse == 'O') {
                    insecteFactory.desactiverExtension(extensionChoisie);
                    std::cout << extensionChoisie << " a été désactivée.\n";
                }
            } else {
                std::cout << extensionChoisie << " n'est pas encore activée. Vous voulez l'activer ? (o/n) : ";
                char reponse;
                std::cin >> reponse;
                if (reponse == 'o' || reponse == 'O') {
                    insecteFactory.activerExtension(extensionChoisie);
                    std::cout << extensionChoisie << " a été activée.\n";
                }
            }
        }
    }
    void saveGame();
    bool verifierProprietairePion(Joueur* current, Insecte* insecte);
    bool verifierDeplacementsPossiblesPourTousLesInsectes(Joueur* current);
    bool verifierDeplacementPossibleDeInsecte(Insecte* currentInsecte);
    void undoLastAction();
    // Destructeur pour libérer la mémoire
    ~GameMaster();

    void testLoadAndDisplayHexagons(const std::string& saveFile) {
        // Charger le fichier JSON de sauvegarde en tant que texte
        std::ifstream file(saveFile);
        if (!file.is_open()) {
            std::cerr << "Erreur: Impossible d'ouvrir le fichier de sauvegarde." << std::endl;
            return;
        }
        // Lire le contenu du fichier JSON
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string jsonStr = buffer.str();

        // Extraire et afficher les hexagones
        size_t start = 0;
        size_t end = 0;
        size_t hexIndex = 0;

        // Trouver et extraire chaque hexagone dans le JSON brut
        while ((start = jsonStr.find("\"plateauMap\": {", end)) != std::string::npos) {
            end = jsonStr.find("}", start);
            std::string plateauMap = jsonStr.substr(start, end - start);

            // Traiter chaque hexagone dans "plateauMap"
            size_t hexStart = 0;
            size_t hexEnd = 0;
            while ((hexStart = plateauMap.find("{", hexEnd)) != std::string::npos) {
                hexEnd = plateauMap.find("}", hexStart);
                std::string hexagon = plateauMap.substr(hexStart, hexEnd - hexStart);

                // Extraire les coordonnées (q, r) et le nom
                size_t qStart = hexagon.find("\"q\":") + 4;
                size_t rStart = hexagon.find("\"r\":") + 4;
                size_t nomStart = hexagon.find("\"nom\":") + 7;
                size_t nomEnd = hexagon.find("\"", nomStart);

                // Récupérer les coordonnées et le nom
                int q = std::stoi(hexagon.substr(qStart, hexagon.find(",", qStart) - qStart));
                int r = std::stoi(hexagon.substr(rStart, hexagon.find(",", rStart) - rStart));
                std::string nom = hexagon.substr(nomStart, nomEnd - nomStart);

                // Afficher les informations sur l'hexagone
                std::cout << "Hexagone " << hexIndex++ << ": " << std::endl;
                std::cout << "  Nom: " << nom << std::endl;
                std::cout << "  Coordonnées: (" << q << ", " << r << ")" << std::endl;

                // Afficher les informations supplémentaires (par exemple le propriétaire)
                size_t ownerStart = hexagon.find("\"owner\":") + 9;
                if (ownerStart != std::string::npos) {
                    size_t ownerEnd = hexagon.find("\"", ownerStart);
                    std::string owner = hexagon.substr(ownerStart, ownerEnd - ownerStart);
                    std::cout << "  Propriétaire: " << owner << std::endl;
                }

                std::cout << std::endl;
            }
        }
    }

};



#endif // GAMEMASTER_H
