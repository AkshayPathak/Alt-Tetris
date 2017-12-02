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

    cells.emplace_back(make_shared<Cell>(0, 4, 'J'));
    cells.emplace_back(make_shared<Cell>(1, 4, 'J'));
    cells.emplace_back(make_shared<Cell>(2, 4, 'J'));
    cells.emplace_back(make_shared<Cell>(1, 3, 'J'));

    return cells;
}

vector<shared_ptr<Cell>> Level::makeLBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 3, 'L'));
    cells.emplace_back(make_shared<Cell>(0, 4, 'L'));
    cells.emplace_back(make_shared<Cell>(1, 4, 'L'));
    cells.emplace_back(make_shared<Cell>(2, 4, 'L'));

    return cells;
}

vector<shared_ptr<Cell>> Level::makeOBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 3, 'O'));
    cells.emplace_back(make_shared<Cell>(1, 3, 'O'));
    cells.emplace_back(make_shared<Cell>(0, 4, 'O'));
    cells.emplace_back(make_shared<Cell>(1, 4, 'O'));

    return cells;}

vector<shared_ptr<Cell>> Level::makeSBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(2, 3, 'S'));
    cells.emplace_back(make_shared<Cell>(1, 3, 'S'));
    cells.emplace_back(make_shared<Cell>(1, 4, 'S'));
    cells.emplace_back(make_shared<Cell>(0, 4, 'S'));

    return cells;
}

vector<shared_ptr<Cell>> Level::makeZBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 3, 'Z'));
    cells.emplace_back(make_shared<Cell>(1, 3, 'Z'));
    cells.emplace_back(make_shared<Cell>(1, 4, 'Z'));
    cells.emplace_back(make_shared<Cell>(2, 4, 'Z'));

    return cells;
}

vector<shared_ptr<Cell>> Level::makeTBlock() {
    vector<shared_ptr<Cell>> cells;

    cells.emplace_back(make_shared<Cell>(0, 3, 'T'));
    cells.emplace_back(make_shared<Cell>(1, 3, 'T'));
    cells.emplace_back(make_shared<Cell>(2, 3, 'T'));
    cells.emplace_back(make_shared<Cell>(1, 4, 'T'));

    return cells;
}
