#include "Insecte.h"
#include "Joueur.h" // Ajoutez cette ligne

std::vector<Hexagon> getVoisins(const Hexagon& coords) {
    std::vector<Hexagon> voisins;
    int q = coords.getQ();
    int r = coords.getR();

    if (q % 2 == 0) {  // Colonne paire
        voisins = {
            Hexagon(q + 1, r),
            Hexagon(q + 1, r - 1),
            Hexagon(q, r - 1),
            Hexagon(q - 1, r),
            Hexagon(q - 1, r + 1),
            Hexagon(q, r + 1)
        };
    } else {  // Colonne impaire
        voisins = {
            Hexagon(q + 1, r),
            Hexagon(q + 1, r + 1),
            Hexagon(q, r - 1),
            Hexagon(q - 1, r),
            Hexagon(q - 1, r - 1),
            Hexagon(q, r + 1)
        };
    }

    return voisins;
}


std::vector<Hexagon> casesAdjacentesVides(Hexagon coords, std::map<Hexagon, Insecte*> p){
    std::vector<Hexagon> vides; //On d�clare la liste des hexagons adjacents vides, pour le moment elle ne contient rien
    std::vector<Hexagon> voisins = getVoisins(coords); //On d�clare la liste des voisins de l'hexagon cible
    for(size_t i=0; i<6; i++){
        for(size_t n=0; n<p.size(); n++){
            auto it = p.begin();
            std::advance(it, n); // On parcours chaque voisin et v�rifions si ses coordonn�es sont d�j� enregistr�es dans le plateau,
                                 //si c'est le cas cela signifie qu'il y a un insecte sur cette case
            if(it != p.end()){
                const Hexagon &hex = it->first;
                if(voisins.at(i).getQ() != hex.getQ() || voisins.at(i).getR()!=hex.getR()){
                    vides.push_back(voisins.at(i));
                }
            }
        }
    }
    return vides;
}

std::vector<Hexagon> casesAdjacentesOccupees(Hexagon coords, std::map<Hexagon, Insecte*> p){
    std::vector<Hexagon> occupees; //On d�clare la liste des hexagons adjacents occup�es, pour le moment elle ne contient rien
    std::vector<Hexagon> voisins = getVoisins(coords); //On d�clare la liste des voisins de l'hexagon cible
    std::vector<Hexagon> vides = casesAdjacentesVides(coords, p);
    for (size_t i=0; i<6; i++){
        for(size_t j=0; j<vides.size(); j++){
            if(voisins.at(i).getQ()!=vides.at(j).getQ() || voisins.at(i).getR()!=vides.at(j).getR()){
                occupees.push_back(voisins.at(i)); //On compare la liste des voisins et celle des cases adjacentes vides, la diff�rence correspond aux cases occup�es
            }
        }
    }
    return occupees;
}

std::vector<Hexagon> getLongueurChaine(Hexagon coords, std::map<Hexagon, Insecte*> p, std::vector<Hexagon> chemin){
    std::vector<Hexagon> voisinOccupee = casesAdjacentesOccupees(coords, p);
    for (size_t i=0; i<voisinOccupee.size(); i++){
        for(size_t j=0; j<chemin.size(); j++){
            if(voisinOccupee.at(i).getQ() != chemin.at(j).getQ() || voisinOccupee.at(i).getR() != chemin.at(j).getR()){
                chemin.push_back(voisinOccupee.at(i));
                chemin = getLongueurChaine(voisinOccupee.at(i), p, chemin);
            }
        }
    }
    return chemin;
}

bool getChaineBrisee(Hexagon coords, const  std::map<Hexagon, Insecte*> p, const  std::vector<Hexagon> chemin){
    std::map<Hexagon, Insecte*> p1 = p;
    p1.erase(coords);
    std::vector<Hexagon> l = getLongueurChaine(coords, p1, chemin);
    if (l.size() < p1.size()){
        return true;
    }
    return false;
}

bool getGlissementPossible(Hexagon coords, const  std::map<Hexagon, Insecte*> p, const  Hexagon destination){
    int t =0;
    std::vector<Hexagon> voisinOccupeeDepart = casesAdjacentesOccupees(coords, p);
    std::vector<Hexagon> voisinOccupeeArrivee = casesAdjacentesOccupees(destination, p);
    for(size_t j=0; j<voisinOccupeeDepart.size(); j++){
        for(size_t k=0; k<voisinOccupeeArrivee.size(); k++){
            if (voisinOccupeeDepart.at(j).getQ()==voisinOccupeeArrivee.at(k).getQ() && voisinOccupeeDepart.at(j).getR()==voisinOccupeeArrivee.at(k).getR()){
                t++;
            }
        }
    }
    if(t>2){
        return false;
    }
    return true;
}

std::vector<Hexagon> deplacementsPossiblesReineAbeille(Hexagon coords, std::map<Hexagon, Insecte*> p){
    std::vector<Hexagon> deplacements;
    std::vector<Hexagon> chemin;
    std::vector<Hexagon> voisinsVides = casesAdjacentesVides(coords, p);
    if(getChaineBrisee(coords, p, chemin)){
        return deplacements;
    }
    for (size_t i = 0; i < voisinsVides.size();) {
        if (casesAdjacentesOccupees(voisinsVides.at(i), p).empty()) {
            voisinsVides.erase(voisinsVides.begin() + i);
        } else {
            ++i;
        }
    }
    for (size_t j = 0; j < voisinsVides.size();) {
        if (!getGlissementPossible(coords, p, voisinsVides.at(j))) {
            voisinsVides.erase(voisinsVides.begin() + j);
        } else {
            ++j;
        }
    }
    return voisinsVides;
}

std::vector<Hexagon> ReineAbeille::deplacementsPossibles(std::map<Hexagon, Insecte*> p){
    return deplacementsPossiblesReineAbeille(getCoords(), p);
}

std::vector<Hexagon> deplacementsPossiblesFourmi(Hexagon coords, std::map<Hexagon, Insecte*> p, std::vector<Hexagon>& cheminInsecte, std::set<Hexagon>& deplacements) {
    std::vector<Hexagon> cheminChaine;
    if(getChaineBrisee(coords, p, cheminChaine)){
        return std::vector<Hexagon>();
    }
    std::vector<Hexagon> voisinsVides = casesAdjacentesVides(coords, p);
    std::map<Hexagon, Insecte*> p1 = p;
    p1.erase(coords);
    for (size_t i = 0; i < voisinsVides.size();) {
        if (casesAdjacentesOccupees(voisinsVides[i], p1).empty() || !getGlissementPossible(coords, p, voisinsVides[i])) {
            voisinsVides.erase(voisinsVides.begin() + i);
        } else {
            ++i;
        }
    }
    cheminInsecte.push_back(coords);
    for (Hexagon voisin : voisinsVides) {
        if (std::find(cheminInsecte.begin(), cheminInsecte.end(), voisin) == cheminInsecte.end()) {
            deplacements.insert(voisin);
            deplacementsPossiblesFourmi(voisin, p1, cheminInsecte, deplacements);
        }
    }
    return std::vector<Hexagon>(deplacements.begin(), deplacements.end());
}

std::vector<Hexagon> Fourmi::deplacementsPossibles(std::map<Hexagon, Insecte*> p){
    std::vector<Hexagon> cheminInsecte;
    std::set<Hexagon> deplacements;
    return deplacementsPossiblesFourmi(getCoords(), p, cheminInsecte, deplacements);
}

std::vector<Hexagon> deplacementsPossiblesScarabee(Hexagon coords, std::map<Hexagon, Insecte*> p){
    std::vector<Hexagon> deplacements;
    std::vector<Hexagon> chemin;
    std::vector<Hexagon> voisins = getVoisins(coords);
    if(getChaineBrisee(coords, p, chemin)){
        return deplacements;
    }
    return voisins;
}

std::vector<Hexagon> Scarabee::deplacementsPossibles(std::map<Hexagon, Insecte*> p){
    return deplacementsPossiblesScarabee(getCoords(), p);
}

void deplacementsPossiblesCoccinelle(Hexagon coords, std::map<Hexagon, Insecte*> p, int i, std::vector<Hexagon>& cheminFinal){
    std::vector<Hexagon> deplacements;
    std::vector<Hexagon> chemin;
    std::vector<Hexagon> voisins = getVoisins(coords);
    if(getChaineBrisee(coords, p, chemin)){
        return;
    }
    if(i!=0){
        std::vector<Hexagon> voisinsOccupes = casesAdjacentesOccupees(coords, p);
        for (int j = 0; j<voisinsOccupes.size(); j++){
            deplacementsPossiblesCoccinelle(voisinsOccupes.at(i), p, i-1, cheminFinal);
        }
    }
    else{
        std::vector<Hexagon> voisinsVides = casesAdjacentesVides(coords, p);
        for(int k=0; k<voisinsVides.size(); k++){
            for(int l=0; l<cheminFinal.size(); l++){
                if(voisinsVides.at(k).getQ() != cheminFinal.at(l).getQ() || voisinsVides.at(k).getR() != cheminFinal.at(l).getR()){
                    cheminFinal.push_back(voisinsVides.at(k));
                }
            }
        }
    }
}


std::vector<Hexagon> Coccinelle::deplacementsPossibles(std::map<Hexagon, Insecte*> p){
    return deplacementsPossiblesReineAbeille(getCoords(), p);
}

std::vector<Hexagon> Sauterelle::deplacementsPossibles(std::map<Hexagon, Insecte*> p){
    return deplacementsPossiblesReineAbeille(getCoords(), p);
}

std::vector<Hexagon> Araignee::deplacementsPossibles(std::map<Hexagon, Insecte*> p){
    return deplacementsPossiblesReineAbeille(getCoords(), p);
}

std::vector<Hexagon> Moustique::deplacementsPossibles(std::map<Hexagon, Insecte*> p){
    return deplacementsPossiblesReineAbeille(getCoords(), p);
}

bool ReineAbeille::estEntouree(const std::map<Hexagon, Insecte*>& p) const {
    std::vector<Hexagon> voisins = getVoisins(getCoords());
    for (const Hexagon& voisin : voisins) {
        if (p.find(voisin) == p.end()) {
            return false; // Si une case voisine est vide, la reine n'est pas entourée
        }
    }
    return true;
}

std::string Insecte::toJson() const {
    std::stringstream jsonData;
    jsonData << "{\n";
    jsonData << "  \"nom\": \"" << nom << "\",\n";
    jsonData << "  \"coords\": " << coords.toJson() << ",\n";
    jsonData << "  \"owner\": \"" << (owner ? owner->getName() : "null") << "\",\n";
    jsonData << "  \"dessus\": " << (dessus ? "\"" + dessus->getNom() + "\"" : "null") << ",\n";
    jsonData << "  \"dessous\": " << (dessous ? "\"" + dessous->getNom() + "\"" : "null") << "\n";
    jsonData << "}";

    return jsonData.str();
}

std::vector<Hexagon> Insecte::placementsPossiblesDeBase(const std::map<Hexagon, Insecte*>& plateau) const {
    std::vector<Hexagon> positionsValides;
    for (const auto& [position, insecteSurCase] : plateau) {
        if (insecteSurCase->getOwner() == this->owner) {
            std::vector<Hexagon> videsAdjacents = casesAdjacentesVides(position, plateau);
            for (const Hexagon& caseVide : videsAdjacents) {
                bool caseValide = true;
                for (const Hexagon& voisin : getVoisins(caseVide)) {
                    if (plateau.count(voisin) > 0 && plateau.at(voisin)->getOwner() != this->owner) {
                        caseValide = false;
                        break;
                    }
                }
                if (caseValide) {
                    positionsValides.push_back(caseVide);
                }
            }
        }
    }
    return positionsValides;
}





