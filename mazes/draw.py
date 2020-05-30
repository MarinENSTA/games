#Useful global functions to draw mazes
import recursive_backtrack_maze as rbm
import pygame
from pygame.locals import *
import sys



def draw_maze(maze,mazesize):
    #Initialisation de la fenêtre
    fenetre = pygame.display.set_mode((10*mazesize,10*mazesize))
    pygame.display.set_caption("Maze")
    icon = pygame.image.load("maze.jpg")
    pygame.display.set_icon(icon)
    
    white_square=pygame.image.load('white_square.jpg').convert()
    white_square=pygame.transform.scale(white_square, (10,10))
    red_square=pygame.image.load('red_square.png').convert()
    red_square=pygame.transform.scale(red_square, (10,10))
    green_square=pygame.image.load('green_square.png').convert()
    green_square=pygame.transform.scale(green_square, (10,10))
    
    for i in maze:
        fenetre.blit(white_square,(int(i[0])*10,int(i[1])*10))
    
    fenetre.blit(green_square,(0,0))
    fenetre.blit(red_square,((mazesize-1)*10,(mazesize-1)*10))
    pygame.display.flip()
