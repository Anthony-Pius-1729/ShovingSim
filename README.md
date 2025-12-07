# ShovingSim 🎱

A real-time 2D particle collision simulation built with **raylib**. Watch 200 balls bounce, collide, and shove each other around with realistic physics!

## Features

- **200 particles** simulated simultaneously
- **Elastic collision physics** with configurable restitution
- **Overlap resolution** to prevent balls from clipping through each other
- **Wall bouncing** with boundary detection
- Smooth **delta-time based movement** for consistent simulation speed
- Clean, minimal aesthetic with white balls on black background

## Screenshot

![ShovingSim Demo](assets/Screenshot%202025-12-07%20at%203.18.25%20PM.png)

## How It Works

The simulation implements:

1. **Collision Detection** - Uses distance-squared comparison for efficient O(n²) pairwise collision checks
2. **Overlap Resolution** - When balls overlap, they're pushed apart along the collision normal
3. **Impulse-Based Response** - Velocity exchange calculated using relative velocity and collision normal
4. **Restitution** - 0.8 coefficient for slightly inelastic collisions (energy loss on impact)

## Building

### Prerequisites

- [raylib](https://www.raylib.com/) installed on your system
- C compiler (gcc, clang, etc.)

### Compile

```bash
gcc shoving.c -o shoving -lraylib -lm -lpthread -ldl -lrt -lX11
```

On macOS:
```bash
gcc shoving.c -o shoving -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
```

### Run

```bash
./shoving
```

## Configuration

You can tweak these constants in `shoving.c`:

| Constant | Default | Description |
|----------|---------|-------------|
| `WIDTH` | 1200 | Window width in pixels |
| `HEIGHT` | 650 | Window height in pixels |
| `RADIUS` | 25 | Ball radius in pixels |
| `N` | 200 | Number of balls |
| `restitution` | 0.8 | Bounciness (0 = no bounce, 1 = perfect elastic) |

## Controls

- **ESC** or close window to exit

## License

MIT License - feel free to use and modify!

