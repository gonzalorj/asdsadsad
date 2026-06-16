*This project has been created as part of the 42 curriculum by gorodrig and tdaroca.*

# cub3D

## Description

cub3D is a real-time, first-person 3D maze renderer written in C, reproducing the rendering technique used by early games such as Wolfenstein 3D. Starting from a 2D map described in a custom `.cub` file format, the program builds a textured first-person view of that maze using **raycasting**: for every column of the screen, a ray is cast from the player's position, and a Digital Differential Analyzer (DDA) walks the map grid to find exactly which wall it hits, at what distance, and which face of that wall is visible — from which the projected wall height and the correct texture (north/south/east/west) are derived.

The main goals of the project are:
- Implementing a raycasting engine from scratch, with no external 3D/game library (only [MiniLibX](https://github.com/42Paris/minilibx-linux) for windowing and pixel drawing).
- Parsing and strictly validating the custom `.cub` map format (textures, floor/ceiling colors, map grid, player spawn), rejecting malformed input with a clear error message.
- Rendering walls with the correct texture per orientation, with a perpendicular (fish-eye corrected) distance calculation.
- Real-time player movement, wall collision detection, and camera rotation.

## Instructions

### Dependencies

- A C compiler (`cc`)
- `make`
- X11 / Xext development headers (required by MiniLibX)

### Compilation

```bash
git clone <repository-url>
cd cub3d
make
```

This builds `libft`, the bundled MiniLibX library (under `mlx/`), and the final `cub3d` binary.

Other available targets:

| Target | Effect |
|---|---|
| `make` / `make all` | Build the `cub3d` binary |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and the binary |
| `make re` | `fclean` + `all` |
| `make norm` | Run the 42 norminette on `src/`, `include/` and `libft/` |

### Execution

```bash
./cub3d <path/to/map.cub>
```

The program expects **exactly one** argument: the path to a map file with a `.cub` extension.

### Map file format

A `.cub` file first declares the four wall textures and the floor/ceiling colors, then the map grid itself:

```
NO ./maps/textures/north.xpm
SO ./maps/textures/south.xpm
WE ./maps/textures/west.xpm
EA ./maps/textures/east.xpm
F 220,100,0
C 225,30,0

111111111
100000001
101100101
1000N0001
111111111
```

- `NO` / `SO` / `WE` / `EA`: path to the `.xpm` texture used for the north/south/west/east-facing walls.
- `F` / `C`: floor and ceiling colors, as `R,G,B` (each component between 0 and 255).
- The grid: `1` is a wall, `0` is open floor, and exactly one of `N`/`S`/`E`/`W` marks the player's starting tile and initial facing direction. The walkable area must be fully enclosed by walls.

Sample maps — both valid ones and intentionally broken ones used to test the parser's error handling — are available under `maps/`.

### Controls

| Key | Action |
|---|---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` / `→` | Rotate the camera left / right |
| `ESC` or the window's close button | Quit the program |

## Resources

- Lode Vandevenne — *Raycasting tutorial*: the classic reference for the DDA-based raycasting algorithm and the perpendicular (fish-eye corrected) wall-distance formula used in this project.
- F. Permadi — *Raycasting tutorial*: another widely used introduction to Wolfenstein-3D-style raycasting engines.
- Wikipedia — *Digital differential analyzer (graphics algorithm)*: background on the DDA technique used to step through the map grid ray by ray.
- [MiniLibX](https://github.com/42Paris/minilibx-linux) documentation (bundled in `mlx/README.md`): reference for the windowing/image API used to display each rendered frame.
- The 42 `cub3D` subject PDF: project requirements and grading scale.

**AI usage:** An AI assistant was used to draft and format this README.md file itself, based on the project's actual source code and Makefile. No project source code was written, generated, or modified by the AI; it was used purely as a learning and documentation-writing aid.