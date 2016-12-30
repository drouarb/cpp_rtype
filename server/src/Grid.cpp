//
// Created by lewis_e on 30/12/16.
//

#include "Entity.hh"
#include "Grid.hh"

using namespace server;

void Grid::remove(const Entity * entity)
{
    auto & cell = grid[static_cast<int>(entity->data.getPosY()) / GRID_CELL_SIZE][static_cast<int>(entity->data.getPosX()) / GRID_CELL_SIZE];
    for (int i = 0; i < cell.size(); ++i)
    {
        if (cell[i] == entity)
        {
            cell[i] = cell.back();
            cell.pop_back();
        }
    }
}

void Grid::add(Entity *entity)
{
    auto & cell = grid[static_cast<int>(entity->data.getPosY()) / GRID_CELL_SIZE][static_cast<int>(entity->data.getPosX()) / GRID_CELL_SIZE];
    cell.push_back(entity);
}

Grid::line_t & Grid::operator[](int index)
{
    return (grid[index]);
}

const Grid::line_t & Grid::operator[](int index) const
{
    return (grid[index]);
}


