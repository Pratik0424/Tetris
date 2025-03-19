#include "block.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = GetCellPositions();
    for (Position item : tiles)
    {
        DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]); // x y w h colr
    }
}

void Block::Move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}

std::vector<Position> Block::GetCellPositions() // me
{
    // Get the blocks cells in the current rotation state
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for (Position item : tiles) 
    {
        Position newPos = Position(item.row + rowOffset, item.column + columnOffset);// Calculate the new position
        movedTiles.push_back(newPos); // Add the translated position
    }
    return movedTiles; //absolute cell positions 
}

void Block::Rotate() // me
{
    rotationState++;
    if (rotationState == (int)cells.size()) 
    {
        rotationState = 0; // Reset to the first state if rotation exceeds the number of states
    }
}

void Block::UndoRotation() // me
{
    rotationState--;
    if (rotationState == -1) 
    {
        rotationState = cells.size() - 1;
    }
}