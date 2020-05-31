import pygame
from pygame.locals import *

##Loading images
icon = pygame.image.load("images/maze.jpg")
white_square=pygame.image.load('images/white_square.jpg')
red_square=pygame.image.load('images/red_square.png')
green_square=pygame.image.load('images/green_square.png')
blue_square=pygame.image.load('images/blue_square.png')
gray_square=pygame.image.load('images/gray_square.png')

##images to proper format
blue_square=pygame.transform.scale(blue_square, (10,10))
white_square=pygame.transform.scale(white_square, (10,10))
red_square=pygame.transform.scale(red_square, (10,10))
green_square=pygame.transform.scale(green_square, (10,10))
gray_square=pygame.transform.scale(gray_square, (10,10))

def init_maze_window(mazesize):
    fenetre = pygame.display.set_mode((10*mazesize,10*mazesize))
    pygame.display.set_caption("Maze")
    pygame.display.set_icon(icon)
    
    return fenetre