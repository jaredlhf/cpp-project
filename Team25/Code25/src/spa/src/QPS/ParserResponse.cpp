#include "ParserResponse.h"

void ParserResponse::setDeclarations(std::vector<std::shared_ptr<Synonym>> declarations) {
    this->declarations = declarations;
    return;
}

void ParserResponse::setSelectSynonyms(std::vector<std::shared_ptr<Synonym>> synonyms) {
    this->selectSynonyms = synonyms;
    return;
}

void ParserResponse::setPatternClauses(std::vector<PatternClausePair> patternClauses) {
    this->patternClauses = patternClauses;
    return;
}

void ParserResponse::setSuchThatClauses(std::vector<std::shared_ptr<Clause>> suchThatClauses) {
    this->suchThatClauses = suchThatClauses;
    return;
}

void ParserResponse::setWithClauses(std::vector<std::shared_ptr<Clause>> withClauses) {
    this->withClauses = withClauses;
    return;
}

std::vector<std::shared_ptr<Synonym>> ParserResponse::getDeclarations() {
    return this->declarations;
}

std::vector<std::shared_ptr<Synonym>> ParserResponse::getSelectSynonyms() {
    return this->selectSynonyms;
}

std::vector<std::shared_ptr<Clause>> ParserResponse::getSuchThatClauses() {
    return this->suchThatClauses;
}

std::vector<std::shared_ptr<Clause>> ParserResponse::getWithClauses() {
    return this->withClauses;
}

std::vector<PatternClausePair> ParserResponse::getPatternClauses() {
    return this->patternClauses;
}

bool ParserResponse::compare(ParserResponse other) {

    std::vector<std::shared_ptr<Synonym>> otherDeclarations = other.getDeclarations();

    // compare declarations
    if (otherDeclarations.size() != this->declarations.size()) {
        return false;
    }

    for (int i = 0; i < otherDeclarations.size(); i++) {
        std::shared_ptr<Synonym> d = this->declarations[i];
        if (!otherDeclarations[i]->compare(d)) {
            return false;
        }
    }

    // if is an error
    if (other.getSelectSynonyms().empty() || this->selectSynonyms.empty()) {
        return false;
    }

    std::vector<std::shared_ptr<Synonym>> otherSynonyms = other.getSelectSynonyms();
    // compare synonyms
    if (otherSynonyms.size() != this->selectSynonyms.size()) {
        return false;
    }
    for (int i = 0; i < otherSynonyms.size(); i++) {
        std::shared_ptr<Synonym> d = this->selectSynonyms[i];
        if (!otherSynonyms[i]->compare(d)) {
            return false;
        }
    }

    // compare patterns


    if (!other.getPatternClauses().empty() && !this->patternClauses.empty()) {
        std::vector<PatternClausePair>  pc1 = other.getPatternClauses();
        std::vector<PatternClausePair>  pc2 = this->patternClauses;

        if (pc1.size() != pc2.size()) {
            return false;
        }

        for (int i = 0; i < pc1.size(); i++) {
            if (!pc1[i].first->compare(pc2[i].first)) {
                return false;
            }
            if (!pc1[i].second->compare(pc2[i].second)) {
                return false;
            }
        }
    }

    // compare such thats

    if (!other.getSuchThatClauses().empty() && !this->suchThatClauses.empty()) {
        std::vector<std::shared_ptr<Clause>> otherSuchThatClauses = other.getSuchThatClauses();

        if (otherSuchThatClauses.size() != this->suchThatClauses.size()) {
            return false;
        }

        for (int i = 0; i < otherSuchThatClauses.size(); i++) {
            std::shared_ptr<Clause> c = this->suchThatClauses[i];
            if (!otherSuchThatClauses[i]->compare(c)) {
                return false;
            }
        }
    }

    // compare with clauses

    if (!other.getWithClauses().empty() && !this->getWithClauses().empty()) {
        std::vector<std::shared_ptr<Clause>> otherWithClauses = other.getWithClauses();

        if (otherWithClauses.size() != this->withClauses.size()) {
            return false;
        }

        for (int i = 0; i < otherWithClauses.size(); i++) {
            std::shared_ptr<Clause> c = this->withClauses[i];
            if (!otherWithClauses[i]->compare(c)) {
                return false;
            }
        }
    }

    if (other.getDeclarations().size() != this->declarations.size()) {
        return false;
    }

    if (other.getSelectSynonyms().size() != this->getSelectSynonyms().size()) {
        return false;
    }

    if (other.getSuchThatClauses().size() != this->suchThatClauses.size()) {
        return false;
    }

    if (other.getWithClauses().size() != this->getWithClauses().size()) {
        return false;
    }

    if (other.getPatternClauses().size() != this->patternClauses.size()) {
        return false;
    }

    return true;
}