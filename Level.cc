#include "Level.h"
#include "Cell.h"

Level::~Level() {

}

vector<shared_ptr<Cell>> Level::makeIBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 3, 'I'));
    cells.emplace_back(make_shared<Cell>(1, 3, 'I'));
    cells.emplace_back(make_shared<Cell>(2, 3, 'I'));
    cells.emplace_back(make_shared<Cell>(3, 3, 'I'));

    return cells;
}

vector<shared_ptr<Cell>> Level::makeJBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 1, 'J'));
    cells.emplace_back(make_shared<Cell>(1, 1, 'J'));
    cells.emplace_back(make_shared<Cell>(2, 1, 'J'));
    cells.emplace_back(make_shared<Cell>(1, 0, 'J'));

    return cells;
}

vector<shared_ptr<Cell>> Level::makeLBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 0, 'L'));
    cells.emplace_back(make_shared<Cell>(0, 1, 'L'));
    cells.emplace_back(make_shared<Cell>(1, 1, 'L'));
    cells.emplace_back(make_shared<Cell>(2, 1, 'L'));

    return cells;
}

vector<shared_ptr<Cell>> Level::makeOBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 0, 'O'));
    cells.emplace_back(make_shared<Cell>(1, 0, 'O'));
    cells.emplace_back(make_shared<Cell>(0, 1, 'O'));
    cells.emplace_back(make_shared<Cell>(1, 1, 'O'));

    return cells;}

vector<shared_ptr<Cell>> Level::makeSBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(2, 0, 'S'));
    cells.emplace_back(make_shared<Cell>(1, 0, 'S'));
    cells.emplace_back(make_shared<Cell>(1, 1, 'S'));
    cells.emplace_back(make_shared<Cell>(0, 1, 'S'));

    return cells;
}

vector<shared_ptr<Cell>> Level::makeZBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 0, 'Z'));
    cells.emplace_back(make_shared<Cell>(1, 0, 'Z'));
    cells.emplace_back(make_shared<Cell>(1, 1, 'Z'));
    cells.emplace_back(make_shared<Cell>(2, 1, 'Z'));

    return cells;
}

vector<shared_ptr<Cell>> Level::makeTBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 0, 'T'));
    cells.emplace_back(make_shared<Cell>(1, 0, 'T'));
    cells.emplace_back(make_shared<Cell>(2, 0, 'T'));
    cells.emplace_back(make_shared<Cell>(1, 1, 'T'));

    return cells;
}
