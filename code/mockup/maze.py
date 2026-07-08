import pygame, sys, random
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
    "BOTTOM": 0b00001, 
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
            if (i == maze.shape[0]-1):
                pygame.draw.line(win, (10, 50, 10), (i*DIM[0]+DIM[0]-1, j*DIM[1]), (i*DIM[0]+DIM[0]-1, j*DIM[1]+DIM[1]))
            if (j == maze.shape[1]-1):
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

x, y = 0, 0
stack = []
while True:
    arr[x, y] |= SIDES["VISIT"]
    current = arr[x, y]
    nx, ny, direction = get_neighbor(x, y, arr)
    if (nx != -1 and ny != -1):
        arr[nx, ny] = arr[nx, ny] | SIDES["VISIT"]
        stack.append((x, y))
        arr[x, y] |= SIDES[direction]
        arr[nx, ny] |= SIDES[OPPOSITE[direction]]
        x, y = nx, ny
    else:
        if (len(stack) > 0):
            x, y = stack.pop()
        else:
            break

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                pygame.quit()
                sys.exit()

    window.fill((255, 255, 255))
    draw_maze(window, arr)
    pygame.display.update()
