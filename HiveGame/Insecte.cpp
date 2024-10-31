#include "Insecte.h"


std::vector<Hexagon> getVoisins(Hexagon coords){
        std::vector<Hexagon> voisins;
        voisins.push_back(Hexagon(coords.getQ()+1, coords.getR()));
        voisins.push_back(Hexagon(coords.getQ()-1, coords.getR()));
        voisins.push_back(Hexagon(coords.getQ()+1, coords.getR()-1));
        voisins.push_back(Hexagon(coords.getQ()-1, coords.getR()-1));
        voisins.push_back(Hexagon(coords.getQ(), coords.getR()-1));
        voisins.push_back(Hexagon(coords.getQ(), coords.getR()+1));
        return voisins;
    }

std::vector<Hexagon> casesAdjacentesVides(Hexagon coords, std::map<Hexagon, Insecte*> p){
    std::vector<Hexagon> vides; //On déclare la liste des hexagons adjacents vides, pour le moment elle ne contient rien
    std::vector<Hexagon> voisins = getVoisins(coords); //On déclare la liste des voisins de l'hexagon cible
    for(size_t i=0; i<6; i++){
        for(size_t n=0; n<p.size(); n++){
            auto it = p.begin();
            std::advance(it, n); // On parcours chaque voisin et vérifions si ses coordonnées sont déjà enregistrées dans le plateau,
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
    std::vector<Hexagon> occupees; //On déclare la liste des hexagons adjacents occupées, pour le moment elle ne contient rien
    std::vector<Hexagon> voisins = getVoisins(coords); //On déclare la liste des voisins de l'hexagon cible
    std::vector<Hexagon> vides = casesAdjacentesVides(coords, p);
    for (size_t i=0; i<6; i++){
        for(size_t j=0; j<vides.size(); j++){
            if(voisins.at(i).getQ()!=vides.at(j).getQ() || voisins.at(i).getR()!=vides.at(j).getR()){
                occupees.push_back(voisins.at(i)); //On compare la liste des voisins et celle des cases adjacentes vides, la différence correspond aux cases occupées
            }
        }
    }
    return occupees;
}

std::vector<Hexagon> getLongueurChaine(Insecte *i, std::map<Hexagon, Insecte*> p, std::vector<Hexagon> chemin){
    std::vector<Hexagon> voisinOccupee = casesAdjacentesOccupees(i->getCoords(), p);
    for (size_t i=0; i<voisinOccupee.size(); i++){
        for(size_t j=0; j<chemin.size(); j++){
            if(voisinOccupee.at(i).getQ() != chemin.at(j).getQ() || voisinOccupee.at(i).getR() != chemin.at(j).getR()){
                chemin.push_back(voisinOccupee.at(i));
                chemin = getLongueurChaine(p[voisinOccupee.at(i)], p, chemin);
            }
        }
    }
    return chemin;
}


bool getChaineBrisee(Insecte *i, std::map<Hexagon, Insecte*> p, std::vector<Hexagon> chemin){
    std::vector<Hexagon> l = getLongueurChaine(i, p, chemin);
    if (l.size() < p.size()){
        return true;
    }
    return false;
}















