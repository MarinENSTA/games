#Useful global functions to draw mazes
import recursive_backtrack_maze as rbm
import pygame
from pygame.locals import *
from global_constants import *
import sys



def draw_maze(maze,mazesize):
    #initialisatio de la fenetre
    fenetre=init_maze_window(mazesize)
    
    for i in maze:
        fenetre.blit(white_square,(int(i[0])*10,int(i[1])*10))
    
    fenetre.blit(green_square,(0,0))
    fenetre.blit(red_square,((mazesize-1)*10,(mazesize-1)*10))
    pygame.display.flip()
    
    while True:
        for event in pygame.event.get():
                if event.type == pygame.QUIT: 
                    pygame.quit()
