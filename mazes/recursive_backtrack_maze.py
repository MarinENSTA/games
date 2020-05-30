#Maze generation algorithms using pygame

import pygame
from pygame.locals import *
from random import choice
import sys


##Recursive backtrack algorithm


def find_neigh(c_cell,u_cells,gridsize):
    x=c_cell[0]
    z=c_cell[1]
    
    search_list = []
    if x < gridsize-2:
        search_list.append([x+2,z])
    if x > 1:
        search_list.append([x-2,z])
    if z < gridsize-2:
        search_list.append([x,z+2])
    if z > 1:
        search_list.append([x,z-2])
    
    neighbours = []
    for i in search_list :
        if i in u_cells:
            neighbours.append(i)
    
    return neighbours
    
    

def recur_backtrack(c_cell,u_cells,v_cells,removed_walls,gridsize):
    v_cells.append(c_cell)
    
    while len(find_neigh(c_cell,u_cells,gridsize)) != 0:
        neighbours=find_neigh(c_cell,u_cells,gridsize)
        next_cell=choice(neighbours)
        
        #Some bias (working) ideas:
        #neighbours+=[neighbours[0]]*3
        #next_cell=find_neigh(c_cell,u_cells,gridsize)[-1]
        
        u_cells.remove(next_cell)
        wall=[(next_cell[0]-c_cell[0])/2+c_cell[0],(next_cell[1]-c_cell[1])/2+c_cell[1]]
        removed_walls.append(wall)
        u_cells,v_cells,removed_walls=recur_backtrack(next_cell,u_cells,v_cells,removed_walls,gridsize)
    
    return u_cells,v_cells,removed_walls

#Automated drawing of maze using the recursive backtrack algorithm
#NB : will look better with an odd number as an argument
def draw_recur_maze(gridsize):
    #Initialisation des variables, en fonction de la taille
    u_cells=[]
    A=range(int((gridsize+1)/2))
    for i in A:
        for j in A:
            u_cells.append([2*i,2*j])
    del u_cells[0]
    
    v_cells=[]
    c_cell=[0,0]
    removed_walls=[]
    
    u_cells,v_cells,removed_walls=recur_backtrack(c_cell,u_cells,v_cells,removed_walls,gridsize)
    white_cells=v_cells+removed_walls
    
    #Initialisation de la fenêtre
    fenetre = pygame.display.set_mode((10*gridsize,10*gridsize))
    pygame.display.set_caption("Maze")

    white_square=pygame.image.load('white_square.jpg').convert()
    new_white_square=pygame.transform.scale(white_square, (10,10))
    
    for i in white_cells:
        fenetre.blit(new_white_square,(int(i[0])*10,int(i[1])*10))
    pygame.display.flip()


def step_by_step_recur_backtrack(c_cell,u_cells,v_cells,removed_walls,gridsize,fenetre,white_square):
    v_cells.append(c_cell)
    
    while len(find_neigh(c_cell,u_cells,gridsize)) != 0:
        neighbours=find_neigh(c_cell,u_cells,gridsize)
        next_cell=choice(neighbours)
        
        #Some bias (working) ideas:
        #neighbours+=[neighbours[0]]*3
        #next_cell=find_neigh(c_cell,u_cells,gridsize)[-1]
        
        u_cells.remove(next_cell)
        wall=[(next_cell[0]-c_cell[0])/2+c_cell[0],(next_cell[1]-c_cell[1])/2+c_cell[1]]
        removed_walls.append(wall)
        
        white_cells=removed_walls+v_cells
        for i in white_cells:
            for event in pygame.event.get():
                    if event.type == pygame.QUIT: 
                        sys.exit(0)
            fenetre.blit(white_square,(int(i[0])*10,int(i[1])*10))
        pygame.display.flip()
        pygame.time.wait(10)
        
        u_cells,v_cells,removed_walls=step_by_step_recur_backtrack(next_cell,u_cells,v_cells,removed_walls,gridsize,fenetre,white_square)
        
        
    
    return u_cells,v_cells,removed_walls

def step_by_step_recur_backtrack_draw(gridsize):
    u_cells=[]
    A=range(int((gridsize+1)/2))
    for i in A:
        for j in A:
            u_cells.append([2*i,2*j])
    del u_cells[0]
    
    v_cells=[]
    c_cell=[0,0]
    removed_walls=[]
    
    fenetre = pygame.display.set_mode((10*gridsize,10*gridsize))
    pygame.display.set_caption("Maze")

    white_square=pygame.image.load('white_square.jpg').convert()
    white_square=pygame.transform.scale(white_square, (10,10))
    red_square=pygame.image.load('red_square.png').convert()
    red_square=pygame.transform.scale(red_square, (10,10))
    green_square=pygame.image.load('green_square.png').convert()
    green_square=pygame.transform.scale(green_square, (10,10))

    u_cells,v_cells,removed_walls=step_by_step_recur_backtrack(c_cell,u_cells,v_cells,removed_walls,gridsize,fenetre,white_square)
    
    fenetre.blit(green_square,(0,0))
    fenetre.blit(red_square,((gridsize-1)*10,(gridsize-1)*10))
    pygame.display.flip()
    
    
    
    
    
    
    