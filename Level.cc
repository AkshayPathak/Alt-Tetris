#include "Level.h"

Level::~Level() {

}

vector<vector<shared_ptr<Cell>>> Level::makeIBlock() {
    vector<vector<shared_ptr<Cell>>> cells;

    cells.emplace_back(make_unique<Cell>(0, 3, "I"));
    cells.emplace_back(make_unique<Cell>(1, 3, "I"));
    cells.emplace_back(make_unique<Cell>(2, 3, "I"));
    cells.emplace_back(make_unique<Cell>(3, 3, "I"));

    return cells;
}

vector<vector<shared_ptr<Cell>>> Level::makeJBlock() {
    vector<vector<shared_ptr<Cell>>> cells;

    cells.emplace_back(make_unique<Cell>(0, 4, "J"));
    cells.emplace_back(make_unique<Cell>(1, 4, "J"));
    cells.emplace_back(make_unique<Cell>(2, 4, "J"));
    cells.emplace_back(make_unique<Cell>(1, 3, "J"));

    return cells;
}

vector<vector<shared_ptr<Cell>>> Level::makeLBlock() {
    vector<vector<shared_ptr<Cell>>> cells;

    cells.emplace_back(make_unique<Cell>(0, 3, "L"));
    cells.emplace_back(make_unique<Cell>(0, 4, "L"));
    cells.emplace_back(make_unique<Cell>(1, 4, "L"));
    cells.emplace_back(make_unique<Cell>(2, 4, "L"));

    return cells;
}

vector<vector<shared_ptr<Cell>>> Level::makeOBlock() {
    vector<vector<shared_ptr<Cell>>> cells;

    cells.emplace_back(make_unique<Cell>(0, 3, "O"));
    cells.emplace_back(make_unique<Cell>(1, 3, "O"));
    cells.emplace_back(make_unique<Cell>(0, 4, "O"));
    cells.emplace_back(make_unique<Cell>(1, 4, "O"));

    return cells;}

vector<vector<shared_ptr<Cell>>> Level::makeSBlock() {
    vector<vector<shared_ptr<Cell>>> cells;

    cells.emplace_back(make_unique<Cell>(2, 3, "S"));
    cells.emplace_back(make_unique<Cell>(1, 3, "S"));
    cells.emplace_back(make_unique<Cell>(1, 4, "S"));
    cells.emplace_back(make_unique<Cell>(0, 4, "S"));

    return cells;
}

vector<vector<shared_ptr<Cell>>> Level::makeZBlock() {
    vector<vector<shared_ptr<Cell>>> cells;

    cells.emplace_back(make_unique<Cell>(0, 3, "Z"));
    cells.emplace_back(make_unique<Cell>(1, 3, "Z"));
    cells.emplace_back(make_unique<Cell>(1, 4, "Z"));
    cells.emplace_back(make_unique<Cell>(2, 4, "Z"));

    return cells;
}

vector<vector<shared_ptr<Cell>>> Level::makeTBlock() {
    vector<vector<shared_ptr<Cell>>> cells;

    cells.emplace_back(make_unique<Cell>(0, 3, "T"));
    cells.emplace_back(make_unique<Cell>(1, 3, "T"));
    cells.emplace_back(make_unique<Cell>(2, 3, "T"));
    cells.emplace_back(make_unique<Cell>(1, 4, "T"));

    return cells;
}
