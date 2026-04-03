# Chopper Survival Quest

A 2D helicopter survival game built with C++ and OpenGL (iGraphics framework). Navigate your chopper through increasingly difficult obstacles, dodge enemy planes, and survive as long as possible to set high scores.

## Gameplay

The player controls a helicopter that must avoid incoming obstacles. The game features three difficulty levels, each introducing new challenges:

- **Easy** - Dodge vertical pillars approaching from the right
- **Medium** - Pillars + floating brick walls for added complexity
- **Hard** - Enemy planes and missiles with aggressive movement patterns

You get **3 lives** per round. Collisions reduce your life count, and the game ends when all lives are lost. Your score increases over time, and high scores are saved per difficulty level.

## Screenshots

> **Note:** Game assets (BMP images) are located in `assets/images/`. Background images for each level, the main menu, score screen, and help screen are included.

## Controls

| Key | Action |
|-----|--------|
| `W` / `Up Arrow` | Move helicopter up |
| `S` / `Down Arrow` | Move helicopter down |
| `A` / `Left Arrow` | Move helicopter left |
| `D` / `Right Arrow` | Move helicopter right |
| `Enter` | Select menu option |
| `Backspace` | Go back to main menu |
| `M` | Mute audio |
| `C` | Unmute audio |
| `Q` | Quit game |

## Project Structure

```
Chopper-Survival-Quest/
├── src/
│   └── Chopper_Survival_Quest.cpp   # Main game source code
├── lib/
│   ├── iGraphics.h                  # iGraphics rendering framework
│   ├── graphics.h                   # WinBGI graphics header
│   └── OpenGL/                      # OpenGL dependencies
│       ├── dll/                     # Runtime DLLs (glut32, glu32, opengl32)
│       ├── include/                 # OpenGL headers (GL, GLU, GLUT, GLAUX)
│       └── lib/                     # Static libraries for linking
├── assets/
│   ├── images/                      # BMP sprites and backgrounds
│   │   ├── main_menu.bmp           # Main menu background
│   │   ├── level_easy.bmp          # Easy level background
│   │   ├── level_medium.bmp        # Medium level background
│   │   ├── level_hard.bmp          # Hard level background
│   │   ├── gameover.bmp            # Game over screen
│   │   ├── 0-9.bmp                 # Digit sprites for score display
│   │   └── ...                     # Other UI elements
│   ├── music/                       # Sound effects and background music
│   │   ├── menusfx.mp3             # Menu background music
│   │   ├── game_play.mp3           # Gameplay background music
│   │   ├── click.mp3               # Menu click sound
│   │   ├── optionchange.mp3        # Menu navigation sound
│   │   ├── singlecollide.mp3       # Collision sound effect
│   │   └── collison_sfx1.wav       # Game over collision sound
│   └── Highscore.txt               # Persistent high score storage
├── .gitignore
└── README.md
```

## Technical Details

- **Language:** C++ (compiled with GCC/MinGW)
- **Graphics:** OpenGL via the [iGraphics](http://www.interstupidity.com/) framework (GLUT-based 2D rendering library developed at BUET)
- **Audio:** Windows MCI (Media Control Interface) for MP3/WAV playback
- **Platform:** Windows (uses Win32 API for timers and audio)
- **IDE:** Code::Blocks (original development environment)

### Key Implementation Details

- **Game loop** driven by GLUT's idle function with double buffering for smooth rendering
- **Timer-based mechanics** using `iSetTimer()` for obstacle generation, gravity, scoring, and missile spawning
- **Collision detection** with bounding-box checks for helicopter vs. pillars, walls, planes, and missiles
- **Persistent high scores** stored in a text file, updated on game over
- **Custom helicopter rendering** built from geometric primitives (ellipses, rectangles, polygons)
- **Progressive difficulty** with obstacle speed increasing over time

## Build Instructions

### Prerequisites

- [Code::Blocks](http://www.codeblocks.org/) IDE with MinGW compiler (or any GCC-compatible toolchain)
- Windows OS (required for Win32 API dependencies)

### Steps

1. Clone this repository:
   ```bash
   git clone https://github.com/Musa-Tur-Farazi/C-Game.git
   ```

2. Open Code::Blocks and create a new empty project.

3. Add `src/Chopper_Survival_Quest.cpp` as the source file.

4. Configure the compiler:
   - **Include path:** `lib/OpenGL/include`
   - **Library path:** `lib/OpenGL/lib`
   - **Link libraries:** `Glaux`, `GLU32`, `glui32`, `glut32`, `OPENGL32`, `gdi32`, `winmm`

5. Copy `lib/OpenGL/dll/glut32.dll` to the build output directory.

6. Copy all files from `assets/images/` and `assets/music/` to the build output directory (the game expects them in the working directory).

7. Build and run.

## Authors

- **Musa Tur Farazi** (Student ID: 2005038)
- **Md. As-Aid Rahman** (Student ID: 2005039)

CSE'20, Lab Group A2 - Bangladesh University of Engineering and Technology (BUET)

*First-year (1-1) programming project*

## License

This project was developed as an academic assignment. The iGraphics framework was created by S. M. Shahriar Nirjon and later modified by Mohammad Saifur Rahman at BUET.
