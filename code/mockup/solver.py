import pygame, sys, random, heapq
import numpy as np
pygame.init()

WIDTH, HEIGHT = 500, 500
window = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("MAZE")

arr = np.zeros((50, 50), dtype=np.uint8)
# Each number will have the following bit representation
# 0     0     0     0     0
# visit right left  top   bottom
SIDES = {
    "VISIT" : 0b10000, 
    "RIGHT" : 0b01000, 
    "LEFT"  : 0b00100, 
    "TOP"   : 0b00010, 
    "BOTTOM": 0b00001
}
MAPPING = [(1, 0), (-1, 0), (0, -1), (0, 1)]
OPPOSITE = {
    "RIGHT"  : "LEFT", 
    "LEFT"   : "RIGHT", 
    "TOP"    : "BOTTOM", 
    "BOTTOM" : "TOP"
}
DIM = (WIDTH / arr.shape[0], HEIGHT / arr.shape[1])

def draw_maze(win, maze):
    for i in range(maze.shape[0]):
        for j in range(maze.shape[1]):
            cell = maze[i, j]
            if (cell & SIDES['TOP']) == 0:
                pygame.draw.line(win, (10, 50, 10), (i*DIM[0], j*DIM[1]), (i*DIM[0]+DIM[0], j*DIM[1]))
            if (cell & SIDES['LEFT']) == 0:
                pygame.draw.line(win, (10, 50, 10), (i*DIM[0], j*DIM[1]), (i*DIM[0], j*DIM[1]+DIM[1]))
            if (i == arr.shape[0]-1):
                pygame.draw.line(win, (10, 50, 10), (i*DIM[0]+DIM[0]-1, j*DIM[1]), (i*DIM[0]+DIM[0]-1, j*DIM[1]+DIM[1]))
            if (j == arr.shape[1]-1):
                pygame.draw.line(win, (10, 50, 10), (i*DIM[0], j*DIM[1]+DIM[1]-1), (i*DIM[0]+DIM[0], j*DIM[1]+DIM[1]-1))

def get_neighbor(x, y, maze):
    n = []
    if x > 0 and maze[x-1, y] & SIDES["VISIT"] == 0:
        n.append((x-1, y, "LEFT"))
    if x < maze.shape[0]-1 and maze[x+1, y] & SIDES["VISIT"] == 0:
        n.append((x+1, y, "RIGHT"))
    if y > 0 and maze[x, y-1] & SIDES["VISIT"] == 0:
        n.append((x, y-1, "TOP"))
    if y < maze.shape[1]-1 and maze[x, y+1] & SIDES["VISIT"] == 0:
        n.append((x, y+1, "BOTTOM"))
    if n:
        return random.choice(n)
    else:
        return (-1, -1, "")
    
def heuristic(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])

def get_connected_neighbors(x, y, maze):
    neighbors = []
    cell = maze[x, y]

    if cell & SIDES["RIGHT"]:
        neighbors.append((x + 1, y))

    if cell & SIDES["LEFT"]:
        neighbors.append((x - 1, y))

    if cell & SIDES["TOP"]:
        neighbors.append((x, y - 1))

    if cell & SIDES["BOTTOM"]:
        neighbors.append((x, y + 1))

    return neighbors

def astar(start, goal, maze):
    open_set = []
    heapq.heappush(open_set, (0, start))

    came_from = {}

    g_score = {start: 0}
    f_score = {start: heuristic(start, goal)}

    while open_set:
        _, current = heapq.heappop(open_set)

        if current == goal:
            path = []
            while current in came_from:
                path.append(current)
                current = came_from[current]

            path.append(start)
            path.reverse()
            return path

        x, y = current

        for neighbor in get_connected_neighbors(x, y, maze):

            tentative_g = g_score[current] + 1

            if tentative_g < g_score.get(neighbor, float("inf")):

                came_from[neighbor] = current
                g_score[neighbor] = tentative_g

                f = tentative_g + heuristic(neighbor, goal)
                f_score[neighbor] = f

                heapq.heappush(open_set, (f, neighbor))

    return []

# x, y = 0, 0
# stack = []
# while True:
#     arr[x, y] |= SIDES["VISIT"]
#     current = arr[x, y]
#     nx, ny, direction = get_neighbor(x, y, arr)
#     if (nx != -1 and ny != -1):
#         arr[nx, ny] = arr[nx, ny] | SIDES["VISIT"]
#         stack.append((x, y))
#         arr[x, y] |= SIDES[direction]
#         arr[nx, ny] |= SIDES[OPPOSITE[direction]]
#         x, y = nx, ny
#     else:
#         if (len(stack) > 0):
#             x, y = stack.pop()
#         else:
#             break

def get_all_neighbors(x, y, maze):
    neighbors = []
    if x > 0:
        neighbors.append((x - 1, y, "LEFT"))
    if x < maze.shape[0] - 1:
        neighbors.append((x + 1, y, "RIGHT"))
    if y > 0:
        neighbors.append((x, y - 1, "TOP"))
    if y < maze.shape[1] - 1:
        neighbors.append((x, y + 1, "BOTTOM"))
    return neighbors

x, y = 0, 0
arr[x, y] |= SIDES["VISIT"]
frontier = []

# Add initial frontier cells
for nx, ny, _ in get_all_neighbors(x, y, arr):
    frontier.append((nx, ny))

while frontier:
    x, y = random.choice(frontier)
    frontier.remove((x, y))
    if arr[x, y] & SIDES["VISIT"]:
        continue
    
    visited_neighbors = []
    if x > 0 and arr[x - 1, y] & SIDES["VISIT"]:
        visited_neighbors.append((x - 1, y, "LEFT"))
    if x < arr.shape[0] - 1 and arr[x + 1, y] & SIDES["VISIT"]:
        visited_neighbors.append((x + 1, y, "RIGHT"))
    if y > 0 and arr[x, y - 1] & SIDES["VISIT"]:
        visited_neighbors.append((x, y - 1, "TOP"))
    if y < arr.shape[1] - 1 and arr[x, y + 1] & SIDES["VISIT"]:
        visited_neighbors.append((x, y + 1, "BOTTOM"))

    vx, vy, direction = random.choice(visited_neighbors)
    arr[x, y] |= SIDES["VISIT"]
    arr[x, y] |= SIDES[direction]
    arr[vx, vy] |= SIDES[OPPOSITE[direction]]

    for nx, ny, _ in get_all_neighbors(x, y, arr):
        if not (arr[nx, ny] & SIDES["VISIT"]):
            frontier.append((nx, ny))

cx = arr.shape[0] // 2
cy = arr.shape[1] // 2
for x in range(cx - 3, cx + 2):
    for y in range(cy - 3, cy + 2):

        # Connect right neighbor
        if x < cx + 1:
            arr[x, y] |= SIDES["RIGHT"]
            arr[x + 1, y] |= SIDES["LEFT"]

        # Connect bottom neighbor
        if y < cy + 1:
            arr[x, y] |= SIDES["BOTTOM"]
            arr[x, y + 1] |= SIDES["TOP"]

start_cell = None
goal_cell = None
path = []
path_color = (
    random.randint(50, 255),
    random.randint(50, 255),
    random.randint(50, 255)
)
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                pygame.quit()
                sys.exit()
            if event.key == pygame.K_SPACE:
                np.savetxt('maze.txt', arr)
        if event.type == pygame.MOUSEBUTTONDOWN:
            mx, my = pygame.mouse.get_pos()

            cx = int(mx // DIM[0])
            cy = int(my // DIM[1])

            if start_cell is None:
                start_cell = (cx, cy)

            elif goal_cell is None:
                goal_cell = (cx, cy)

                path = astar(start_cell, goal_cell, arr)

            else:
                start_cell = (cx, cy)
                goal_cell = None
                path = []

                path_color = (
                    random.randint(50, 255),
                    random.randint(50, 255),
                    random.randint(50, 255)
                )

    window.fill((255, 255, 255))
    draw_maze(window, arr)
    for x, y in path:
        pygame.draw.rect(
            window,
            path_color,
            (
                x * DIM[0] + 2,
                y * DIM[1] + 2,
                DIM[0] - 4,
                DIM[1] - 4
            )
        )
    if start_cell:
        pygame.draw.rect(
            window,
            (0, 255, 0),
            (
                start_cell[0] * DIM[0] + 2,
                start_cell[1] * DIM[1] + 2,
                DIM[0] - 4,
                DIM[1] - 4
            )
        )

    if goal_cell:
        pygame.draw.rect(
            window,
            (255, 0, 0),
            (
                goal_cell[0] * DIM[0] + 2,
                goal_cell[1] * DIM[1] + 2,
                DIM[0] - 4,
                DIM[1] - 4
            )
        )
    pygame.display.update()
