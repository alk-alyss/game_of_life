# Game of Life

By Alkinoos Alyssandrakis for University of Patras School of Electrical and Computer Engineering

An implementation of Conway's game of life and other life-like simulations written in C using the SDL2 graphics library

## Instructions

### Main menu:

- Random: Generate a random starting state and run the simulation

- Draw: Draw the desired starting state on an empty canvas

- Rule: Select from common rules or create a custom one

### Drawing screen:

- Left click on a cell to switch it from dead to alive and vice versa

- Right click and drag to move the view

- Zoom in and out with the scroll wheel

- Keybindings:

  - ENTER --> Start simulation

  - SPACE --> Step simulation

  - C --> Clear live cells

  - R --> Random generation of live cells

  - G --> Add Gosper Glider Gun at mouse position

  - ESC --> Exit to main menu

  (NOTE): Initial state is saved after exiting drawing screen and after selecting random generation

### Simulation screen:

- Right click and drag to move the view

- Zoom in and out with the scroll wheel

- Keybindings:

  - ENTER --> Start/Stop simulation

  - SPACE --> Step simulation if stopped

  - ESC --> Exit to main menu
