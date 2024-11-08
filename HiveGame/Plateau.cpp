#include "Plateau.h"

void Plateau::ajouterInsecte(Insecte* insecte, Hexagon position) {

    if (nombreTours == 0) {
        std::cout << "Placement obligatoire du premier insecte." << std::endl;
        if (plateauMap.empty()) {
            plateauMap[position] = insecte;
            insectesSurPlateau.push_back(insecte);
            mettreAJourLimites();
            return;
        } else {
            std::cerr << "Erreur : placement initial incorrect." << std::endl;
            return;
        }
    }

    std::vector<Hexagon> emplacementsValides;

    if (nombreTours == 1){
        emplacementsValides = getVoisinsInsectePlateau(insecte);
    }
    else{
        emplacementsValides = insecte->placementsPossiblesDeBase(plateauMap);
    }

    bool positionValide = std::find(emplacementsValides.begin(), emplacementsValides.end(), position) != emplacementsValides.end();

    if (nombreTours == 4) {
        Insecte* reine = insecte->getOwner()->contientInsecte("Reine");
        if (reine && !plateauMap.count(reine->getCoords())) {
            if (positionValide) {
                plateauMap[position] = reine;
                insectesSurPlateau.push_back(reine);
                mettreAJourLimites();
                return;
            } else {
                std::cerr << "Erreur : emplacement invalide pour la Reine." << std::endl;
                return;
            }
        }
    }

    if (!positionValide) {
        std::cerr << "Erreur : emplacement invalide." << std::endl;
        return;
    }

    if (plateauMap.count(position)) {
        Insecte* insecteEnDessous = plateauMap[position];
        superposerInsecte(insecteEnDessous, insecte);
    } else {
        plateauMap[position] = insecte;
        insectesSurPlateau.push_back(insecte);
        mettreAJourLimites();
    }
}

void Plateau::afficherPossibiliteDeplacement(Insecte* insecte, const std::map<Hexagon, Insecte*>& plateau, Joueur* j1, Joueur* j2) {
    // Récupérer les déplacements possibles
    std::vector<Hexagon> deplacements = insecte->deplacementsPossibles(plateau);

    // Afficher les déplacements
    std::cout << "Déplacements possibles pour " << insecte->getNom() << " :\n";
    for (const Hexagon& hex : deplacements) {
        std::cout << "[" << hex.getQ() << ", " << hex.getR() << "]\n";
    }

    // Afficher visuellement sur le plateau si besoin
    afficherPlateauAvecPossibilites(deplacements, j1, j2);
}

void Plateau::afficherPossibilitePlacement(Insecte* insecte, Joueur* j1, Joueur* j2) {
    std::vector<Hexagon> placements;

    if (nombreTours == 1) {
        // Premier tour avec un insecte adverse placé : on place autour de cet insecte
        auto it = plateauMap.begin();
        placements = getVoisins(it->first);
    }else {
        placements = insecte->placementsPossiblesDeBase(plateauMap);
    }

    // Afficher le plateau avec les emplacements possibles marqués
    std::cout << "Emplacements possibles pour placer " << insecte->getNom() << " :\n";
    for (const Hexagon& hex : placements) {
        std::cout << "[" << hex.getQ() << ", " << hex.getR() << "]\n";
    }
    afficherPlateauAvecPossibilites(placements, j1, j2);
}

void Plateau::afficherPlateauAvecPossibilites(const std::vector<Hexagon>& emplacementsPossibles, Joueur* j1, Joueur* j2) {
    // Créer une copie temporaire du plateau pour l'affichage
    std::map<Hexagon, Insecte*> plateauTemp = plateauMap;
    Joueur* current = (getTour() % 2 == 0) ? j1 : j2;

    // Ajouter des insectes fictifs aux emplacements possibles dans le plateau temporaire
    for (const Hexagon& hex : emplacementsPossibles) {
        if (plateauTemp.find(hex) == plateauTemp.end()) {  // Si la position est vide
            plateauTemp[hex] = new InsecteFictif(hex, current);  // Ajouter un insecte fictif
        }
    }

    // Afficher le plateau avec les insectes fictifs en utilisant afficherPlateau
    std::swap(plateauMap, plateauTemp);  // Échange temporairement plateauMap et plateauTemp

    mettreAJourLimites();

    afficherPlateau(j1, j2);
    std::swap(plateauMap, plateauTemp);  // Restaure plateauMap

    // Nettoyer les insectes fictifs ajoutés dans le plateau temporaire
    for (const Hexagon& hex : emplacementsPossibles) {
        if (plateauTemp[hex]->getNom() == "?") {  // Vérifie si c'est un insecte fictif
            delete plateauTemp[hex];
            plateauTemp.erase(hex);
        }
    }
}


