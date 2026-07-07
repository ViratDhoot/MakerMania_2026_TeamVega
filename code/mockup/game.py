import pygame, sys
import numpy as np
pygame.init()

WIDTH, HEIGHT = 800, 800
window = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("GAME")

arr = np.loadtxt('maze.txt').astype(np.uint8)

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
DIM = (100, 100)

def draw_maze(win, maze, ix, iy):
    x = WIDTH // 2 - ix
    y = HEIGHT // 2 - iy
    for i in range(max(int(ix//DIM[0])-5, 0), min(maze.shape[0], int(ix//DIM[0])+5)):
        for j in range(max(int(iy//DIM[1])-5, 0), min(maze.shape[1], int(iy//DIM[1])+5)):
            cell = maze[i, j]
            if (cell & SIDES['TOP']) == 0:
                pygame.draw.line(win, (10, 50, 10), (i*DIM[0] + x, j*DIM[1]+y), (i*DIM[0]+DIM[0]+x, j*DIM[1]+y), 5)
            if (cell & SIDES['LEFT']) == 0:
                pygame.draw.line(win, (10, 50, 10), (i*DIM[0]+x, j*DIM[1]+y), (i*DIM[0]+x, j*DIM[1]+DIM[1]+y), 5)
            if (i == maze.shape[0]-1):
                pygame.draw.line(win, (10, 50, 10), (i*DIM[0]+DIM[0]-1+x, j*DIM[1]+y), (i*DIM[0]+DIM[0]-1+x, j*DIM[1]+DIM[1]+y), 5)
            if (j == maze.shape[1]-1):
                pygame.draw.line(win, (10, 50, 10), (i*DIM[0]+x, j*DIM[1]+DIM[1]-1+y), (i*DIM[0]+DIM[0]+x, j*DIM[1]+DIM[1]-1+y), 5)

x, y = DIM[0] // 2, DIM[1] // 2
speed = 0.3
size = DIM[0] // 3

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                pygame.quit()
                sys.exit()
    
    window.fill((0, 0, 0))
    draw_maze(window, arr, x, y)
    keys = pygame.key.get_pressed()
    if keys[pygame.K_a]:
        x -= speed
    if keys[pygame.K_d]:
        x += speed
    if keys[pygame.K_w]:
        y -= speed
    if keys[pygame.K_s]:
        y += speed
    
    ix = int(x // DIM[0])
    iy = int(y // DIM[1])
    cell = arr[ix, iy]
    if (cell & SIDES["LEFT"] == 0) and (x-size < ix*DIM[0]+1):
        x = ix*DIM[0] + size + 1
    if (cell & SIDES["RIGHT"] == 0) and (x+size > (ix+1)*DIM[0]-1):
        x = (ix+1)*DIM[0] - size - 1
    if (cell & SIDES["TOP"] == 0) and (y-size < iy*DIM[1]+1):
        y = iy*DIM[1] + size + 1
    if (cell & SIDES["BOTTOM"] == 0) and (y+size > (iy+1)*DIM[1]-1):
        y = (iy+1)*DIM[1] - size - 1
    pygame.draw.aacircle(window, (255, 255, 255), (WIDTH // 2, HEIGHT // 2), size)
    arrow = [arr.shape[0]/2 - x / DIM[0], arr.shape[1]/2 - y / DIM[1]]
    mag = (arrow[0]**2 + arrow[1]**2)**0.5
    if abs(mag) > 3:
        arrow[0] /= mag
        arrow[1] /= mag
        arrow[0] *= WIDTH/2
        arrow[1] *= HEIGHT/2
        arrow[0] += WIDTH / 2
        arrow[1] += HEIGHT / 2
        pygame.draw.aacircle(window, (10, 50, 10), arrow, 10)
    pygame.display.update()